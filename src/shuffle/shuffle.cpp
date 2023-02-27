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
    if(deck == NULL)
    return;
    delete[] deck;
    deck = NULL;
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
    int bufferDeck[size];
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
    int deckSize;
    int outShuffles;
    float blockSize;

    sizes(int deckSize, int outShuffles, float blockSize) : deckSize(deckSize), outShuffles(outShuffles), blockSize(blockSize) {}
};

sizes sizesTable[] = {
    sizes(4, 2, 0),      // 4 DeckSize          2 OutShuffles
    sizes(8, 3, 0),      // 8 DeckSize 	        3 OutShuffles
    sizes(24, 11, 0),    // 24 DeckSize 	    11 OutShuffles
    sizes(52, 8, 0),     // 52 DeckSize 	    8 OutShuffles
    sizes(100, 30, 0),   // 100 DeckSize        30 OutShuffles
    sizes(1024, 10, 0)}; // 1024 DeckSize  	    10 OutShuffles

sizes findSuitableBlockSize(int dataSize)
{
    sizes suitableSize = sizes(1, 1, dataSize);
    for (sizes s : sizesTable)
    {
        if (dataSize < s.deckSize * 3)
        {
            break;
        }
        suitableSize = s;
    }
    suitableSize.blockSize = floor(dataSize / suitableSize.deckSize);

    return suitableSize;
}

string outShuffle(string data, string key, bool decypher)
{
    if(data.size() < 2){
        return data;
    }

    int size = data.size();

    sizes shuffleSizes = findSuitableBlockSize(size);
    int keyInt = keyToInt(key, shuffleSizes.outShuffles);
    if(decypher){
        keyInt = shuffleSizes.outShuffles - keyInt;
    }
    
    Deck deck = Deck(shuffleSizes.deckSize);
    deck.calculateOutShuffle(keyInt);

    string dataBuffer;
    const char *dataChar = data.c_str();
    string blockBuffer;

    int index;

    for (int i = 0; i < shuffleSizes.deckSize; i++)
    {
        blockBuffer = "";
        index = deck.deck[i] * shuffleSizes.blockSize;
        for (int j = 0; j < shuffleSizes.blockSize; j++)
        {
            // blockBuffer += dataChar[index + j];
            // dataBuffer += outShuffle(blockBuffer, key, decypher);
            dataBuffer += dataChar[index + j];
        }
    }

    return dataBuffer;
}