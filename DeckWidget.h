#ifndef DECKWIDGET_H
#define DECKWIDGET_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>

class DeckWidget : public QWidget {
    Q_OBJECT
public:
    explicit DeckWidget(QWidget *parent = nullptr);
    void updateDeck(const QString &backSkinPath, int cardCount = 5);

private:
    QGraphicsView *deckView;
    QGraphicsScene *deckScene;
};

#endif // DECKWIDGET_H
