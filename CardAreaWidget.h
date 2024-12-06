#ifndef CARDAREAWIDGET_H
#define CARDAREAWIDGET_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <vector>
#include <memory>
#include "card.h"

class CardAreaWidget : public QGraphicsView {
    Q_OBJECT

public:
    explicit CardAreaWidget(QWidget *parent = nullptr);
    void displayCards(const std::vector<std::shared_ptr<Card>> &cards);
    void displayBackSide();

private:
    QGraphicsScene *scene;
    QString loadCardImage(const Card &card);
    std::vector<QGraphicsPixmapItem*> cardItems;
};

#endif // CARDAREAWIDGET_H
