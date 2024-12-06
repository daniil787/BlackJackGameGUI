#include "DeckWidget.h"
#include <QGraphicsPixmapItem>
#include <QPixmap>

DeckWidget::DeckWidget(QWidget *parent) : QWidget(parent) {
    deckView = new QGraphicsView(this);
    deckScene = new QGraphicsScene(deckView);
    deckView->setScene(deckScene);

    deckView->setStyleSheet("background-color: transparent; border: none;");
    deckView->setFixedSize(100, 150); //розмір для колоди
}

void DeckWidget::updateDeck(const QString &backSkinPath, int cardCount) {
    deckScene->clear();
    QPixmap backPixmap(backSkinPath);

    for (int i = 0; i < cardCount; ++i) {
        auto *item = new QGraphicsPixmapItem(backPixmap.scaled(80, 120, Qt::KeepAspectRatio));
        item->setOffset(i * 2, -i * 2); //сміщення для карт колоди
        deckScene->addItem(item);
    }
}
