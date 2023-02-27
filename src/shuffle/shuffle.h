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
std::string outShuffle(std::string data, std::string key, bool decypher = false);

#endif // !__SHUFFLE__