#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "gamecontroller.h"
#include <QBoxLayout>
#include "CardAreaWidget.h"
#include <QTranslator>
#include<QMenuBar>
#include <QButtonGroup>
#include "DeckWidget.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onHitButtonClicked();
    void onStandButtonClicked();
    void updateUI();
    void showGameOver(const QString &winner);
    void loadLanguage(const QString &languageCode);
    void increaseBet();
    void decreaseBet();
    void animateCard(QWidget *widget, QPoint startPoint, QPoint endPoint);
    void selectFrontSkin(int id);
    void selectBackSkin(int id);

private:

    Ui::MainWindow *ui;
    GameController *gameController;
    CardAreaWidget *playerCardAreaWidget;
    CardAreaWidget *dealerCardAreaWidget;
     DeckWidget *deckWidget;
    QTranslator translator;
    QButtonGroup *frontButtonGroup; //група кнопок для передніх сторін карток
    QButtonGroup *backButtonGroup;  //група кнопок для задніх сторін

};

#endif // MAINWINDOW_H
