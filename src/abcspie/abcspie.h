
#ifndef __SBCSPI__
#define __SBCSPI__

#include <string>
#include <map>

using namespace std;

class ABCS31427
{
private:
    static const int BLOCK_SIZE = 128; // tamanho maximo do bloco de texto
    static const int KEY_SIZE = 7;     // tamanho minimo da chave
    static const int ITR_NUM = 16;     // numero de iteracoes (24 ITR -> 10 segundos)
    static const int PIP_MAX = 39650;  // numero maximo de characteres do pip
    static const int ASCII_L = 32;     // lower bound dos caracteres visiveis da ascii
    static const int ASCII_U = 126;    // upper bound dos caracteres visiveis da ascii
    static const short MARKER = 1;     // marcador usado no railfence

    // aproximacao dos digitos de pi ate a 400 casa decimal (fonte wikipedia)
    inline static const char *pi_str = "31415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679821480865132823066470938446095505822317253594081284811174502841027019385211055596446229489549303819644288109756659334461284756482337867831652712019091456485669234603486104543266482133936072602491412737245870066063155881748815209209628292540917153643678925903600113305305488204665213841469519415116094";

    // aproximacao dos digitos de e ate a 400 casa decimal (fonte https://www.math.utah.edu/~pa/math/e.html)
    inline static const char *e_str = "27182818284590452353602874713526624977572470936999595749669676277240766303535475945713821785251664274274663919320030599218174135966290435729003342952605956307381323286279434907632338298807531952510190115738341879307021540891499348841675092447614606680822648001684774118537423454424371075390777449920695517027618386062613313845830007520449338265602976067371132007093287091274437470472306969772093101416";

    // inverso multiplicativo do GF(95)
    inline static int gf[] = {0, 1, 48, 32, 24, 5, 16, 68, 12, 74, 10, 26, 8, 22, 34, 15, 6, 28, 37, 19, 20, 86, 13, 62, 4, 25, 11, 88, 17, 59, 30, 46, 3, 72, 14, 35, 66, 18, 38, 39, 40, 51, 43, 42, 54, 45, 31, 93, 2, 64, 50, 41, 53, 52, 44, 55, 56, 57, 77, 29, 60, 81, 23, 92, 49, 65, 36, 78, 7, 84, 70, 91, 33, 82, 9, 75, 76, 58, 67, 89, 80, 61, 73, 87, 69, 85, 21, 83, 27, 79, 90, 71, 63, 47, 94};

    inline static map<char, char> sbox; // substitution box
    inline static string pip;           // potencia de pi
    inline static string ep;            // potencia de e
    inline static int f_offset;         // offset inicial na potencia de pi

    // funcoes auxiliares
    static string treatment(string input);
    static void initIrrPower(int pow);
    static string convertKey(string key);
    static unsigned int offsetModE(int round);
    static unsigned int offsetModPi(int round);

    static void initSBox(string key);

    static string shiftRowsE(string sub, unsigned int offset, int s);
    static string shiftRowsPi(string sub, unsigned int offset, int s);

    static string decryptRailfence(string sub, int key);
    static string encryptRailfence(string sub, int key);
    static int railfenceKey(unsigned int off_mod);

    static string roundOffset(string sub, unsigned int offset, int s);
    static string roundSBox(string sub);

    static char offsetChar(char c, int offset);

    ABCS31427() {}

public:
    static string encode(string plaintext, string key);
    static string decode(string cypheredtext, string key);
};

#endif
