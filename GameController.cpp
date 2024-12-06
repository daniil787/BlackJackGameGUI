#include "GameController.h"
GameController::GameController(QObject *parent) : QObject(parent), deck(), soundManager(new SoundManager(this)) {}

void GameController::startGame() {

    playerHand.clear();
    dealerHand.clear();

    deck.shuffle();

    playerHand.push_back(deck.dealCard());
    playerHand.push_back(deck.dealCard());

    dealerHand.push_back(deck.dealCard());
    dealerHand.push_back(deck.dealCard());

    dealerCardRevealed = false; //карта ділера схована
    isStandPressed = false; // зброс стану після натискання Stand

    enum class GameResult { PlayerWin, DealerWin, Tie, None };
    GameResult checkGameStatus{}; // Проверка состояния игры

    emit updateUI();
}

void GameController::playerHit() {
    //для анімації
    QWidget *newCardWidget = new QWidget();
    QPoint startPosition(-200, -200);
    QPoint targetPosition(200, 200);

    emit animateCard(newCardWidget, startPosition, targetPosition);
    soundManager->playSound(":/sounds/resourses/sounds/hit.wav");

    playerHand.push_back(deck.dealCard());

    soundManager->playSound(":/sounds/resourses/sounds/stand.wav");
    if (calculateScore(playerHand) > 21 || calculateScore((dealerHand)) > 21) {
        QString winner = determineWinner();
        emit gameOver(winner);
    }

     emit updateUI();
}

const std::vector<std::shared_ptr<Card>>& GameController::getPlayerHand() const{

    return playerHand;
}
const std::vector<std::shared_ptr<Card>>& GameController::getDealerHand() const{

    return dealerHand;
}

void GameController::playerStand() {

    soundManager->playSound(":/sounds/resourses/sounds/stand.wav");

    dealerCardRevealed = true;

    dealerTurn();

    //анімація для карток ділера
    QWidget *newCardWidget = new QWidget();
    QPoint startPosition(300, -200);
    QPoint targetPosition(400, 200);

    emit animateCard(newCardWidget, startPosition, targetPosition);

    QString winner = determineWinner();

    emit gameOver(winner);
}

QString GameController::determineWinner() {
    int playerScore = calculateScore(playerHand);
    int dealerScore = calculateScore(dealerHand);

    if (playerScore > 21) {
        balance -= bet;
        return "Dealer";
    }
    if (dealerScore > 21) {
        balance += bet;
        return "Player";
    }
    if (playerScore == 21 && playerHand.size() == 2) {
        balance += bet * 1.5;
        return "Player (Blackjack)";
    }
    if (playerScore > dealerScore) {
        balance += bet;
        return "Player";
    }
    if (dealerScore > playerScore) {
        balance -= bet;
        return "Dealer";
    }

    return "Draw";
}

int GameController::getPlayerScore() const {
    return calculateScore(playerHand);
}

int GameController::getDealerScore() const {
    return calculateScore(dealerHand);
}

int GameController::getBalance()const{return balance;}

int GameController::getBet() const {
    return bet;
}

bool GameController::isGameOver() const {
    return calculateScore(playerHand) > 21;
}

int GameController::calculateScore(const std::vector<std::shared_ptr<Card>> &hand) const {
    int score = 0;
    int aces = 0;

    for (const auto &card : hand) {
        score += card->getValue();
        if (card->getRank() == Card::Rank::Ace) {
            ++aces;
        }
    }
    while (score > 21 && aces > 0) {
        score -= 10;
        --aces;
    }

    return score;
}

bool GameController::isDealerCardRevealed()const{
    return dealerCardRevealed;
}

std::vector<std::shared_ptr<Card>> GameController::getDealerRevealedHand() const {
    if (!dealerCardRevealed && !dealerHand.empty()) {
        auto revealedHand = dealerHand;
        revealedHand[0] = nullptr;
        return revealedHand;
    }
    return dealerHand;
}

void GameController::revealDealerCards() {
    dealerCardRevealed = true;
    emit updateUI();
}

void GameController::increaseBet(){
    if (bet+ 5 <= balance ) bet +=5;
}

void GameController::decreaseBet(){
    if(bet - 5 >= 5) bet -=5;
}

SoundManager* GameController::getSoundManager() const {
    return soundManager;
}

void GameController::dealerTurn() {
    while (calculateScore(dealerHand) < 17) {
        dealerHand.push_back(deck.dealCard());
        emit updateUI();
    }
}
