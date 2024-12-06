#include "deck.h"

Deck::Deck() : currentIndex(0) {
    for (int suit = 0; suit < 4; ++suit) {
        for (int rank = 2; rank <= 14; ++rank) {
            cards.emplace_back(std::make_shared<Card>(
                static_cast<Card::Suit>(suit),
                static_cast<Card::Rank>(rank)
                ));
        }
    }
}

void Deck::shuffle() {
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(cards.begin(), cards.end(), g);
    currentIndex = 0;
}

std::shared_ptr<Card> Deck::dealCard() {
    if (currentIndex < cards.size()) {
        return cards[currentIndex++];
    }
    else {
        shuffle();
        currentIndex = 0;
        return dealCard();
    }
}
