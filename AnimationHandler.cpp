#include "AnimationHandler.h"

AnimationHandler::AnimationHandler(QObject *parent)
    : QObject(parent), animation(new QPropertyAnimation(this)) {}

//метод для анімації переміщення карт
void AnimationHandler::animateCard(QWidget *card, const QPoint &start, const QPoint &end) {
    animation->setTargetObject(card);
    animation->setPropertyName("pos");
    animation->setStartValue(start); //початкова позиція
    animation->setEndValue(end); //кінцева позиція
    animation->setDuration(500); // Тривалість анімації
    animation->start();
}
