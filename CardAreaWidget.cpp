#include "CardAreaWidget.h"
#include <QFile>
#include "SkinManager.h"
CardAreaWidget::CardAreaWidget(QWidget *parent) : QGraphicsView(parent), scene(new QGraphicsScene(this)) {

    setScene(scene);
    const int fixedWidth = 500;
    const int fixedHeight = 200;
    setFixedSize(fixedWidth, fixedHeight);
    scene->setSceneRect(0, 0, fixedWidth, fixedHeight);

}

void CardAreaWidget::displayCards(const std::vector<std::shared_ptr<Card>> &cards) {

    scene->clear();
    cardItems.clear();

    int offset = 0;


    for (size_t i = 0; i < cards.size(); ++i) {
        QPixmap pixmap;

        if (!cards[i]) {
            //при умові якщо карта є скритою: перша карта ділера
            pixmap = QPixmap(SkinManager::getBackSkin());
        } else {
            pixmap = QPixmap(loadCardImage(*cards[i]));
        }

        if (pixmap.isNull()) {
            qWarning() << "Failed to load card image.";
            continue;
        }

        auto *item = scene->addPixmap(pixmap.scaled(100, 150, Qt::KeepAspectRatio));
        item->setPos(offset, 0);
        cardItems.push_back(item);
        offset += 110;
    }
}

void CardAreaWidget::displayBackSide() {

    scene->clear();

    const int cardWidth = 100;
    const int cardHeight = 150;

    QPixmap backSkin(SkinManager::getBackSkin());
    if (backSkin.isNull()) {
        qWarning() << "Failed to load back side skin.";
        return;
    }

    QPixmap scaledPixmap = backSkin.scaled(cardWidth, cardHeight, Qt::KeepAspectRatio);

    QGraphicsPixmapItem *item = scene->addPixmap(scaledPixmap);

    item->setPos(200, 25);
}

QString CardAreaWidget::loadCardImage(const Card &card) {
    QString rankStr;
    Card::Rank rank = card.getRank();

    switch (rank) {
    case Card::Rank::Ace:
        rankStr = "ace";
        break;
    case Card::Rank::Jack:
        rankStr = "jack";
        break;
    case Card::Rank::Queen:
        rankStr = "queen";
        break;
    case Card::Rank::King:
        rankStr = "king";
        break;
    default:
        rankStr = QString::number(static_cast<int>(rank)); // для 1...10
        break;
    }

    QString suitStr;

    switch (card.getSuit()) {
    case Card::Suit::Hearts: suitStr = "hearts"; break;
    case Card::Suit::Diamonds: suitStr = "diamonds"; break;
    case Card::Suit::Clubs: suitStr = "clubs"; break;
    case Card::Suit::Spades: suitStr = "spades"; break;
    }

    return SkinManager::getFrontSkin(rankStr, suitStr);
}
