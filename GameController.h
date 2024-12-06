#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "Deck.h"
#include <vector>
#include <QObject>
#include <memory>
#include <QString>
#include "AnimationHandler.h"
#include "SoundManager.h"
#include <QPoint>

class GameController : public QObject{

    Q_OBJECT

public:

    explicit GameController(QObject *parent = nullptr);

    void startGame();
    void playerHit();
    void playerStand();
    int getBet() const;
    int getDealerScore() const;
    int getPlayerScore() const;
    void increaseBet();
    void decreaseBet();
    bool isDealerCardRevealed() const;
    int getBalance ()const;
    void revealDealerCards();
    void playGameSound(const QString &soundPath);


    const std::vector<std::shared_ptr<Card>> & getPlayerHand() const;
    const std::vector<std::shared_ptr<Card>> & getDealerHand() const;
    std::vector<std::shared_ptr<Card>> getDealerRevealedHand() const;

    bool isGameOver()const;
    QString determineWinner();
    SoundManager* getSoundManager() const;

signals:
    void updateUI();
    void gameOver(const QString &winner);
    void animateCard(QWidget *widget, QPoint startPoint, QPoint endPoint);

private:
    SoundManager *soundManager;
    Deck deck;
    std::vector<std::shared_ptr<Card>> playerHand;
    std::vector<std::shared_ptr<Card>> dealerHand;

    int balance = 500;
    int bet = 10;
    bool isStandPressed = false;
    bool dealerCardRevealed = false;

    int calculateScore(const std::vector<std::shared_ptr<Card>> &hand) const;
    void dealerTurn();
};

#endif // GAMECONTROLLER_H
