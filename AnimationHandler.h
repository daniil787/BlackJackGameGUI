#ifndef ANIMATIONHANDLER_H
#define ANIMATIONHANDLER_H

#include <QObject>
#include <QPropertyAnimation>
#include <QWidget>

class AnimationHandler : public QObject {
    Q_OBJECT

public:
    explicit AnimationHandler(QObject *parent = nullptr);
    void animateCard(QWidget *card, const QPoint &start, const QPoint &end);

private:
    QPropertyAnimation *animation;
};

#endif // ANIMATIONHANDLER_H
