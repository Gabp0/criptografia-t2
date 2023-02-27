#include <iostream>
#include <iterator>
#include <string>
#include <algorithm>
#include "abcspie/abcspie.h"
#include "vigenererss/vigenere.h"
#include "vigenererss/vigenereDiferente.h"
#include "shuffle/shuffle.h"

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
    string text = string("hamburguerdebatatacomfritasdefrangofritocommostardas");
    cout << text << endl;
    string cypher = outShuffleCypher(text, "key");
    cout << cypher << endl;
    string deCypher = outShuffleDeCypher(cypher, "key");
    cout << deCypher << endl;

    // string output;
    // string key = "nerfthis";

    // bool decypher = cmdOptionExists(argv, argc, "-d");
    // bool cypher = cmdOptionExists(argv, argc, "-c");
    // bool vigenereDiferente = cmdOptionExists(argv, argc, "-v");

    // if (decypher && cypher)
    // {
    //     perror("Opção '-d' e '-c' não podem ser utilizadas juntas");
    //     exit(EXIT_FAILURE);
    // }
    // if (!decypher && !cypher)
    // {
    //     perror("Faltando opção '-d' ou '-c");
    //     exit(EXIT_FAILURE);
    // }

    // if (cmdOptionExists(argv, argc, "-k"))
    // {
    //     key = getCmdOption(argv, argc, "-k");
    // }

    // istreambuf_iterator<char> begin(std::cin), end;
    // string input(begin, end);
    // input.pop_back();

    // if (cypher)
    // {
    //     if (vigenereDiferente)
    //     {
    //         output = cryptDiferente(input);
    //         output = ABCS31427::encode(output, key);
    //     }
    //     else
    //     {
    //         output = ABCS31427::encode(input, key);
    //         output = crypt(output, key, 5);
    //     }
    //     cout << output << endl;
    // }

    // if (decypher)
    // {
    //     if (vigenereDiferente)
    //     {
    //         output = ABCS31427::decode(input, key);
    //         output = decryptDiferente(output);
    //     }
    //     else
    //     {
    //         output = decrypt(input, key, 5);
    //         output = ABCS31427::decode(output, key);
    //     }
    //     cout << output << endl;
    // }

    return EXIT_SUCCESS;
}