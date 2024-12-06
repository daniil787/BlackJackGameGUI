#ifndef CARD_H
#define CARD_H

#include <string>

class Card {
public:

    enum class Suit { Hearts, Diamonds, Clubs, Spades };
    enum class Rank { Two = 2, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Jack = 11, Queen = 12, King = 13, Ace = 14 };

    Card(Suit suit, Rank rank) : suit(suit), rank(rank) {}

    Suit getSuit() const { return suit; }
    Rank getRank() const { return rank; }
    int getValue() const { return rank == Rank::Ace ? 11 : static_cast<int>(rank); }

    std::string toString() const;

private:
    Suit suit;
    Rank rank;
};

#endif
