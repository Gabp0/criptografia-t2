#include <iostream>
#include <iterator>
#include <string>
#include <algorithm>
#include "sbcspi/sbcspi.h"
#include "vigenererss/vigenere.h"
#include "vigenererss/vigenereDiferente.h"

using namespace std;

char *getCmdOption(char **begin, size_t size, const string &option)
{
    char **itr = find(begin, (begin + size), option);
    if (itr != (begin + size) && ++itr != (begin + size))
    {
        return *itr;
    }
    return 0;
}

bool cmdOptionExists(char **begin, int size, const string &option)
{
    return find(begin, begin + size, option) != (begin + size);
}

int main(int argc, char *argv[])
{
    string output;
    string key = "nerfthis";

    bool decypher = cmdOptionExists(argv, argc, "-d");
    bool cypher = cmdOptionExists(argv, argc, "-c");
    bool vigenereDiferente = cmdOptionExists(argv, argc, "-v");

    if (decypher && cypher)
    {
        perror("Opção '-d' e '-c' não podem ser utilizadas juntas");
        exit(EXIT_FAILURE);
    }
    if (!decypher && !cypher)
    {
        perror("Faltando opção '-d' ou '-c");
        exit(EXIT_FAILURE);
    }

    if (cmdOptionExists(argv, argc, "-k"))
    {
        key = getCmdOption(argv, argc, "-k");
    }

    istreambuf_iterator<char> begin(std::cin), end;
    string input(begin, end);
    input.pop_back();

    if (cypher)
    {
        if (vigenereDiferente)
        {
            output = cryptDiferente(input);
            output = SBCS314::encode(output, key);
        }
        else
        {
            output = SBCS314::encode(input, key);
            output = crypt(output, key, 5);
        }
        cout << output << endl;
    }

    if (decypher)
    {
        if (vigenereDiferente)
        {
            output = SBCS314::decode(input, key);
            output = decryptDiferente(output);
        }
        else
        {
            output = decrypt(input, key, 5);
            output = SBCS314::decode(output, key);
        }
        cout << output << endl;
    }

    return EXIT_SUCCESS;
}