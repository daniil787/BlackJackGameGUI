#ifndef DECK_H
#define DECK_H

#include "card.h"
#include <vector>
#include <memory>
#include <algorithm>
#include <random>

class Deck {
public:
    Deck();
    void shuffle();
    std::shared_ptr<Card> dealCard();


private:
    std::vector<std::shared_ptr<Card>> cards;
    size_t currentIndex;
};

#endif // DECK_H
