#include "abcspie.h"
#include <iostream>
#include <math.h>
#include <algorithm>
#include <gmp.h>
#include <string>
#include <map>

using namespace std;

string ABCS31427::encode(string plaintext, string key)
{
    string output;

    // inicializacoes
    plaintext = treatment(plaintext);
    initSBox(key);
    key = convertKey(key);
    initIrrPower(stoi(key.substr(0, 2)));
    ABCS31427::f_offset = stoi(key.substr(2, 5));

    for (size_t i = 0; i < ((plaintext.size() / BLOCK_SIZE) + 1); i++)
    { // separa em blocos de tamanho BLOCK_SIZE no maximo
        string sub = plaintext.substr(i * BLOCK_SIZE, BLOCK_SIZE);

        for (size_t j = 0; j < ITR_NUM; j++)
        {
            unsigned int off_mod_pi = offsetModE(j);
            unsigned int off_mod_e = offsetModE(j);

            sub = shiftRowsE(sub, off_mod_e, 1);
            sub = roundSBox(sub);
            sub = encryptRailfence(sub, railfenceKey(off_mod_e));
            sub = roundOffset(sub, off_mod_pi, 1);
            sub = shiftRowsPi(sub, off_mod_pi, 1);
        }
        output += sub;
    }

    return output;
}

string ABCS31427::decode(string cypheredtext, string key)
{
    string output;

    // inicializacoes
    initSBox(key);
    key = convertKey(key);
    initIrrPower(stoi(key.substr(0, 2)));
    ABCS31427::f_offset = stoi(key.substr(2, 5));

    for (size_t i = 0; i < ((cypheredtext.size() / BLOCK_SIZE) + 1); i++)
    { // separa em blocos de tamanho BLOCK_SIZE no maximo
        string sub = cypheredtext.substr(i * BLOCK_SIZE, BLOCK_SIZE);

        for (int j = ITR_NUM - 1; j >= 0; j--)
        { // ITR_NUM rodadas
            unsigned int off_mod_pi = offsetModE(j);
            unsigned int off_mod_e = offsetModE(j);

            sub = shiftRowsPi(sub, off_mod_e, -1);
            sub = roundOffset(sub, off_mod_pi, -1);
            sub = decryptRailfence(sub, railfenceKey(off_mod_e));
            sub = roundSBox(sub);
            sub = shiftRowsE(sub, off_mod_e, -1);
        }

        output += sub;
    }

    return output;
}

unsigned int ABCS31427::offsetModE(int round)
{
    // inicializa lib gmp
    mpz_t offset;
    mpz_init(offset);
    mpz_t ep_pos;
    mpz_init(ep_pos);

    // calcula a key da rodada atual
    mpz_set_ui(offset, abs(~ABCS31427::f_offset)); // modulo do inverso do offset
    mpz_pow_ui(offset, offset, pow(2, round));
    mpz_mod_ui(ep_pos, offset, ep.size() - 3);

    return mpz_get_ui(ep_pos);
}

unsigned int ABCS31427::offsetModPi(int round)
{
    // inicializa lib gmp
    mpz_t offset;
    mpz_init(offset);
    mpz_t pip_pos;
    mpz_init(pip_pos);

    // calcula o offset da rodada atual
    mpz_set_ui(offset, ABCS31427::f_offset);
    mpz_pow_ui(offset, offset, pow(2, round));
    mpz_mod_ui(pip_pos, offset, pip.size());

    return mpz_get_ui(pip_pos);
}

string shiftRows(string sub, unsigned int shift, int s)
{
    shift = shift % sub.size();

    if (s > 0)
    {
        string start = sub.substr(0, shift);
        sub.erase(0, shift);
        sub += start;
    }
    else
    {
        string end = sub.substr(sub.size() - shift, shift);
        sub.erase(sub.size() - shift, shift);
        sub = end + sub;
    }

    return sub;
}

string ABCS31427::shiftRowsE(string sub, unsigned int offset, int s)
{
    // calcula o shift
    offset = ep.size() - offset;
    unsigned int shift = (ep[offset] - '0') * 100 + (ep[offset - 1] - '0') * 10 + (ep[offset - 2] - '0');
    shift = shift % sub.size();

    return shiftRows(sub, shift, s);
}

string ABCS31427::shiftRowsPi(string sub, unsigned int offset, int s)
{
    // calcula o shift
    offset = pip.size() - offset;
    unsigned int shift = (pip[offset] - '0') * 100 + (pip[offset - 1] - '0') * 10 + (pip[offset - 2] - '0');
    shift = shift % sub.size();

    return shiftRows(sub, shift, s);
}

int ABCS31427::railfenceKey(unsigned int off_mod)
{
    return (ep[off_mod % ep.size()] - '0') * 10 + (ep[(off_mod % ep.size()) + 1] - '0') + 2;
}

string ABCS31427::encryptRailfence(string sub, int key)
{
    int sl = sub.length();
    string cipheredtext = "";

    // cria e inicializa a rail
    char *rail = new char[sl * key];
    fill(rail, rail + (sl * key), 0);

    bool down = false;
    int row = 0, col = 0;

    for (int i = 0; i < sl; i++)
    {
        // muda a direção
        if (row == 0 || row == key - 1)
        {
            down = !down;
        }

        rail[row * sl + col] = sub[i];

        col++;
        down ? row++ : row--;
    }

    // constroi o texto cifrado
    for (int i = 0; i < key; i++)
    {
        for (int j = 0; j < sl; j++)
        {
            if (rail[(i * sl) + j])
            {
                cipheredtext += rail[i * sl + j];
            }
        }
    }

    delete[] rail;

    return cipheredtext;
}

string ABCS31427::decryptRailfence(string sub, int key)
{
    int sl = sub.length();
    string plaintext = "";

    // cria e inicializa a rail
    char *rail = new char[sl * key];
    fill(rail, rail + (sl * key), 0);

    bool down = false;
    int row = 0, col = 0;
    for (int i = 0; i < sl; i++)
    {
        // muda a direcao
        if (row == 0 || row == key - 1)
        {
            down = !down;
        }

        // coloca o marcador
        rail[row * sl + col] = MARKER;
        col++;

        down ? row++ : row--;
    }

    // preenche o rail com o texto cifrado
    int k = 0;
    for (int i = 0; i < key; i++)
    {
        for (int j = 0; j < sl; j++)
        {
            if (rail[i * sl + j] == MARKER && k < sl)
            {
                rail[i * sl + j] = sub[k++];
            }
        }
    }

    row = 0, col = 0;
    down = false;
    // reconstroi o texto plano
    for (int i = 0; i < sl; i++)
    {
        // muda a direcao
        if (row == 0 || row == key - 1)
        {
            down = !down;
        }

        if (rail[row * sl + col] != MARKER)
        {
            plaintext += rail[row * sl + col];
            col++;
        }

        down ? row++ : row--;
    }

    delete[] rail;

    return plaintext;
}

string ABCS31427::roundOffset(string sub, unsigned int offset, int s)
// faz o offset do bloco
{

    for (size_t k = 0; k < sub.size(); k++)
    { // faz o offset da letra
        int coff = pip[(offset + k) % pip.size()] - '0';
        sub[k] = offsetChar(sub[k], coff * s);
    }

    return sub;
}

string ABCS31427::roundSBox(string sub)
// passa o bloco pela s-box
{
    for (size_t k = 0; k < sub.size(); k++)
    {
        sub[k] = ABCS31427::sbox[sub[k]];
    }

    return sub;
}

void ABCS31427::initSBox(string key)
// gera a sbox
{
    string ascii(key);

    for (string::size_type i = 0; i < ascii.size(); i++)
    { // remove chars repetidos da chave
        string::size_type j = i + 1;
        while (j < ascii.size())
        {
            if (ascii[i] == ascii[j])
            {
                ascii.erase(j, 1);
            }
            else
            {
                ++j;
            }
        }
    }

    for (size_t i = ASCII_L; i < (ASCII_U + 1); i++)
    { // completa o resto da tabela ascii
        if (key.find(i) == string::npos)
        {
            ascii += i;
        }
    }

    size_t asize = ASCII_U - ASCII_L + 1;
    for (size_t i = 0; i < asize; i++)
    { // gera o mapa
        ABCS31427::sbox[ascii[i]] = ascii[gf[i]];
    }
}

string ABCS31427::convertKey(string key)
// converte os valores em ascii dos caracteres da chave
{
    string int_key;
    size_t i = 0;
    while (int_key.size() < KEY_SIZE)
    {
        int_key += to_string(key[i] - '0');
        i++;
    }

    return int_key;
}

void ABCS31427::initIrrPower(int pow)
// gera a potencia de pi
{
    char pip_char[PIP_MAX];

    mpz_t irr; // inicializa gmp (beeg pi)
    mpz_init(irr);
    mpz_set_str(irr, pi_str, 10);

    mpz_pow_ui(irr, irr, pow);      // pi^key[0:1]
    mpz_get_str(pip_char, 10, irr); // converte novamente para char

    ABCS31427::pip = pip_char;

    mpz_set_str(irr, e_str, 10); // set o e

    mpz_pow_ui(irr, irr, pow);      // e^key[0:1]
    mpz_get_str(pip_char, 10, irr); // converte novamente para char

    ABCS31427::ep = pip_char;
}

string ABCS31427::treatment(string input)
// substitui characteres nao visiveis ou unicode
{
    for (char i : input)
    {
        if ((i > ASCII_U) || (i < ASCII_L))
        {
            replace(input.begin(), input.end(), i, 'X');
        }
    }

    return input;
}

char ABCS31427::offsetChar(char c, int offset)
// offset dentro do range 22 a 126 da tabela ascii
{
    int out = c + offset;
    if (out > ASCII_U)
    {
        out = (out - (ASCII_U + 1)) + ASCII_L;
    }
    else if (out < ASCII_L)
    {
        out = (out - ASCII_L) + (ASCII_U + 1);
    }
    return out;
}
