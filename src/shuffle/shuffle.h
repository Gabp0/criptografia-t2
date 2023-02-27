#ifndef __SHUFFLE__
#define __SHUFFLE__

#include <string>

struct Deck
{
    int *deck;
    int size;

    Deck(int size);
    ~Deck();
    void printDeck();
    void calculateOutShuffle(int itera);
};

// int *initDeck(int size);
std::string outShuffleCypher(std::string data, std::string key);
std::string outShuffleDeCypher(std::string data, std::string key);

#endif // !__SHUFFLE__