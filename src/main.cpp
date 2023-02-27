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
    // string text = string("Proin dui quam, laoreet quis lectus nec, vestibulum mattis libero. Phasellus ut tincidunt arcu, vestibulum tempor erat. Nulla blandit nisl nibh, non malesuada arcu ultrices a. Phasellus nisl magna, vehicula quis fringilla ut, aliquet vitae ligula. Aenean sit amet lectus mi. Nullam blandit lectus non ultricies dignissim. Fusce congue arcu felis, in gravida est dapibus vel. Nunc eleifend porttitor augue at fringilla. Nulla vehicula porttitor eleifend. Phasellus at velit vulputate erat accumsan lobortis. Phasellus eu metus id lorem ornare blandit. In neque ex, aliquet in arcu vitae, eleifend interdum ipsum. Sed nulla turpis, condimentum id nisl sed, semper semper nulla. Praesent et lacus consequat odio maximus tincidunt rutrum id lacus.");
    // cout << text << endl;
    // string ahhh = outShuffle(text, "key");
    // cout << ahhh << endl;
    // string deCypher = outShuffle(ahhh, "key", true);
    // cout << deCypher << endl;

    // cout << (text == deCypher) << endl;
    // return 0;

    string output;
    string key = "nerfthis";

    bool decypher = cmdOptionExists(argv, argc, "-d");
    bool cypher = cmdOptionExists(argv, argc, "-c");
    bool vigenereDiferente = cmdOptionExists(argv, argc, "-v");
    bool shuffle = cmdOptionExists(argv, argc, "-s");
    bool help = cmdOptionExists(argv, argc, "-h");

    if (help)
    {
        cout << "Opções para uso do software:"
             << "\nEscolhas de modo: (Obrigatorio)"
             << "\n\t-c - cypher"
             << "\n\t-d - decipher"
             << "\nEscolhas de algoritmo: (Opcional)"
             << "\n\t-v - substitui o algoritmo de vingenere por uma versão modificada"
             << "\n\t-s - apenas utiliza o algoritmo de out-shuffle"
             << "\nUtilidades:"
             << "\n\t-h - apresenta essa tela" << endl;
        return EXIT_SUCCESS;
    }

    if (decypher && cypher)
    {
        perror("Opção '-d' e '-c' não podem ser utilizadas juntas\n\tUtilize -h para help");
        exit(EXIT_FAILURE);
    }
    if (!decypher && !cypher)
    {
        perror("Faltando opção '-d' ou '-c\n\tUtilize -h para help");
        exit(EXIT_FAILURE);
    }

    if (vigenereDiferente && shuffle)
    {
        perror("Opção '-v' e '-s' não podem ser utilizadas juntas\n\tUtilize -h para help");
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
            output = outShuffle(input, key);
            output = cryptDiferente(output);
            output = ABCS31427::encode(output, key);
        }
        else if (shuffle)
        {
        }
        else
        {
            output = outShuffle(input, key);
            output = ABCS31427::encode(output, key);
            output = crypt(output, key, 5);
        }
        cout << output << endl;
    }

    if (decypher)
    {
        if (vigenereDiferente)
        {
            output = ABCS31427::decode(input, key);
            output = decryptDiferente(output);
            output = outShuffle(output, key, true);
        }
        else
        {
            output = decrypt(input, key, 5);
            output = ABCS31427::decode(output, key);
            output = outShuffle(output, key, true);
        }
        cout << output << endl;
    }

    return EXIT_SUCCESS;
}