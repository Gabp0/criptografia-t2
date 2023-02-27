#include <cstring>
#include <string>
#include <cmath>
#include <iostream>
#include "shuffle.h"

using namespace std;

Deck::Deck(int size)
{
    this->size = size;
    deck = new int[size];

    for (int i = 0; i < size; i++)
    {
        deck[i] = i;
    }
}

Deck::~Deck()
{
    delete deck;
}

void Deck::printDeck()
{
    for (int i = 0; i < size; i++)
    {
        cout << deck[i] << " ";
    }
    cout << endl;
}

// int *initDeck(int size)
// {
//     int *deck = new int[size];

//     for (int i = 0; i < size; i++)
//     {
//         deck[i] = i;
//     }

//     return deck;
// }

void Deck::calculateOutShuffle(int itera)
{
    int *bufferDeck = new int[size];
    int half = floor(size / 2);

    for (int i = 0; i < itera; i++)
    {
        for (int a = 0; a < half; a++)
        {
            bufferDeck[a * 2] = deck[a];
        }
        for (int a = 0; a < half; a++)
        {
            bufferDeck[a * 2 + 1] = deck[half + a];
        }
        memcpy(deck, bufferDeck, size * sizeof(int));
    }

    delete bufferDeck;
}

int keyToInt(string key, int maxValue)
{
    int div = 55;
    float bufferKey = 987456.564654;
    int intKey;

    for (char i : key)
    {
        div += i;
        bufferKey += (i / div);
        div = div % 255 + 1;
    }

    int buffer = trunc(abs(bufferKey)) + 1;
    int buffer2 = trunc(maxValue / 2) + 1;

    intKey = buffer % buffer2;

    if (intKey == 0)
        return 1;

    return intKey;
}

// 4        2
// 8 	    3
// 24 	    11
// 52 	    8
// 100 	    30
// 1024 	10

struct sizes
{
    int minSize;
    int shuffleSize;
    float blockSize;

    sizes(int minSize, int shuffleSize, float blockSize) : minSize(minSize), shuffleSize(shuffleSize), blockSize(blockSize) {}
};

sizes sizesTable[] = {
    sizes(4, 2, 0),
    sizes(8, 3, 0),
    sizes(24, 11, 0),
    sizes(52, 8, 0),
    sizes(100, 30, 0),
    sizes(1024, 10, 0)};

sizes findSuitableBlockSize(int dataSize)
{
    sizes suitableSize = sizes(1, 1, dataSize);
    for (sizes s : sizesTable)
    {
        if (dataSize < s.minSize * 3)
        {
            break;
        }
        suitableSize = s;
    }
    suitableSize.blockSize = dataSize / suitableSize.minSize;

    return suitableSize;
}

string outShuffleCypher(string data, string key)
{
    int size = data.size();

    sizes shuffleSizes = findSuitableBlockSize(size);
    int keyInt = keyToInt(key, shuffleSizes.shuffleSize);
    cout << "Block Size: " << shuffleSizes.blockSize << " Deck Size: " << shuffleSizes.shuffleSize << endl;

    Deck deck = Deck(shuffleSizes.minSize);
    deck.calculateOutShuffle(keyInt);
    deck.printDeck();

    string dataBuffer;
    const char *dataChar = data.c_str();

    int blockQty = floor(size / shuffleSizes.blockSize);
    int blockSizes = size / blockQty;
    int index;

    for (int i = 0; i < blockQty; i++)
    {
        index = deck.deck[i] * blockSizes;
        for (int j = 0; j < blockSizes; j++)
        {
            dataBuffer += dataChar[index + j];
        }
    }

    return dataBuffer;
}

string outShuffleDeCypher(string data, string key)
{
    int size = data.size();

    sizes shuffleSizes = findSuitableBlockSize(size);
    int keyInt = shuffleSizes.shuffleSize - keyToInt(key, shuffleSizes.shuffleSize);
    cout << "Block Size: " << shuffleSizes.blockSize << " Deck Size: " << shuffleSizes.shuffleSize << endl;

    Deck deck = Deck(shuffleSizes.minSize);
    deck.calculateOutShuffle(keyInt);
    deck.printDeck();

    string dataBuffer;
    const char *dataChar = data.c_str();

    int blockQty = floor(size / shuffleSizes.blockSize);
    int blockSizes = size / blockQty;
    int index;

    for (int i = 0; i < blockQty; i++)
    {
        index = deck.deck[i] * blockSizes;
        for (int j = 0; j < blockSizes; j++)
        {
            dataBuffer += dataChar[index + j];
        }
    }

    return dataBuffer;
}