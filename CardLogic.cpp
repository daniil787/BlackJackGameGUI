#include "card.h"
#include <sstream>

std::string Card::toString() const {
    std::ostringstream oss;

    if (rank == Rank::Ace) {
        oss << "ace";
    } else if (rank == Rank::Jack) {
        oss << "jack";
    } else if (rank == Rank::Queen) {
        oss << "queen";
    } else if (rank == Rank::King) {
        oss << "king";
    } else {
        oss << static_cast<int>(rank);
    }

    oss << "_of_";

    switch (suit) {
    case Suit::Hearts: oss << "hearts.png"; break;
    case Suit::Diamonds: oss << "diamonds.png"; break;
    case Suit::Clubs: oss << "clubs.png"; break;
    case Suit::Spades: oss << "spades.png"; break;
    }

    return oss.str();
}
