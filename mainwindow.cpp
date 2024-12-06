#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QMenu>
#include <QAction>
#include <QFileDialog>
#include "SkinManager.h"
#include "SkinGalleryDialog.h"
#include "DeckWidget.h"
MainWindow::MainWindow(QWidget *parent) :

    QMainWindow(parent),
    ui(new Ui::MainWindow),

    gameController(new GameController(this)), //для відображення ігрового процесу: рахунок, баланс, ставки тощо
    playerCardAreaWidget(new CardAreaWidget(this)),// "рука" гравця
    dealerCardAreaWidget(new CardAreaWidget(this)),// "рука" ділера

    frontButtonGroup(new QButtonGroup(this)),//для вибору скіна передньої сторони карти
    backButtonGroup(new QButtonGroup(this)),//для вибору скіна задньої сторони карти
    deckWidget(new DeckWidget(this))

{
    ui->setupUi(this);
    gameController->getSoundManager()->playBackgroundMusic(":/music/resourses/music/background1.mp3");

    //відображення карт гравця та ділера
    ui->playerLayout->addWidget(playerCardAreaWidget);
    ui->dealerLayout->addWidget(dealerCardAreaWidget);

    //відображення колоди
    deckWidget->updateDeck(SkinManager::getBackSkin());
    ui->deckLayout->addWidget(deckWidget);

    //прив'язка логіки до кнопок
    connect(ui->hitButton, &QPushButton::clicked, this, &MainWindow::onHitButtonClicked);
    connect(ui->standButton, &QPushButton::clicked, this, &MainWindow::onStandButtonClicked);

    connect(ui->increaseBetBtn, &QPushButton::clicked, this, &MainWindow::increaseBet);
    connect(ui->decreaseBetBtn, &QPushButton::clicked, this, &MainWindow::decreaseBet);

    connect(ui->exitButton, &QPushButton::clicked, this, &MainWindow::close);

    //для анімації
    connect(gameController, &GameController::animateCard, this, &MainWindow::animateCard);

    setFixedSize(1200, 700); // розмір вікна гри

    //вибір мови
    QMenu *langMenu = menuBar()->addMenu(tr("Language"));
    QAction *ukrainianAct = langMenu->addAction("Українська");
    QAction *englishAct = langMenu -> addAction ("English");

    connect(ukrainianAct, &QAction::triggered, this, [this](){loadLanguage("uk_UA");} );
    connect(englishAct, &QAction::triggered, this, [this](){loadLanguage("en_Eng");});

    QMenu *settingsMenu = menuBar()  ->addMenu(tr("Settings"));
    QAction *changeSkinAct = settingsMenu->addAction("Change Cards Skins");

    //зміна скіна через галерею
    connect(changeSkinAct, &QAction::triggered, this, [this]() {
        SkinGalleryDialog dialog(this);
        if (dialog.exec() == QDialog::Accepted) {
            QString frontSkin = dialog.getSelectedFrontSkin();
            QString backSkin = dialog.getSelectedBackSkin();

            // підтвердження вибору
            if (!frontSkin.isEmpty() || !backSkin.isEmpty()) {
                QMessageBox::StandardButton reply = QMessageBox::question(
                    this, tr("Confirm Skin Change"),
                    tr("Do you want to apply the selected skins?"),
                    QMessageBox::Yes | QMessageBox::No
                    );

                if (reply == QMessageBox::Yes) {
                    if (!frontSkin.isEmpty()) SkinManager::setFrontSkinPath(frontSkin);
                    if (!backSkin.isEmpty()) SkinManager::setBackSkinPath(backSkin);

                    updateUI(); //після підтвердження скін зміниться
                }
            }
        }
    });

    connect(gameController, &GameController::updateUI, this, &MainWindow::updateUI);
    connect(gameController, &GameController::gameOver, this, &MainWindow::showGameOver);

    gameController->startGame();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::onHitButtonClicked() {
    gameController->getSoundManager()->playSound(":/sounds/resourses/sounds/hit.wav");
    gameController->playerHit();
}

void MainWindow::onStandButtonClicked() {
    gameController->getSoundManager()->playSound(":/sounds/resourses/sounds/stand.wav");
    gameController->playerStand();
}

void MainWindow::increaseBet(){
    gameController->increaseBet();
    updateUI();
}

void MainWindow::decreaseBet(){
    gameController->decreaseBet();
    updateUI();
}

void MainWindow::animateCard(QWidget *widget, QPoint startPoint, QPoint endPoint) {
    AnimationHandler animationHandler(this);
    animationHandler.animateCard(widget, startPoint, endPoint);
}

void MainWindow::updateUI() {
    // оновлення тексту міток: баланса, ставки, рахунку
    deckWidget->updateDeck(SkinManager::getBackSkin());
    ui->ballanceLbl->setText(tr("Your Balance: %1").arg(gameController->getBalance()));
    ui->betLbl->setText(tr("Bet: %1").arg(gameController->getBet()));

    ui->playerScoreLbl->setText(tr("Your Score: %1").arg(gameController->getPlayerScore()));
    ui->dealerScoreLbl->setText(tr("Dealer Score: %1").arg(gameController->getDealerScore()));

    playerCardAreaWidget->displayCards(gameController->getPlayerHand());

    if (gameController->isDealerCardRevealed()) {
        dealerCardAreaWidget->displayCards(gameController->getDealerHand());
    } else {
        dealerCardAreaWidget->displayCards(gameController->getDealerRevealedHand());
    }

    // ui->cardAreaWidget->displayCards(gameController->getPlayerHand());
}

void MainWindow::selectFrontSkin(int id) {

    QPushButton *button = qobject_cast<QPushButton *>(frontButtonGroup->button(id));
    if (button) {
        QString skinPath = button->property("skinPath").toString();
        SkinManager::setFrontSkinPath(skinPath);
        updateUI();
    }
}

void MainWindow::selectBackSkin(int id) {

    QPushButton *button = qobject_cast<QPushButton *>(backButtonGroup->button(id));
    if (button) {
        QString skinPath = button->property("skinPath").toString();
        SkinManager::setBackSkinPath(skinPath);
        updateUI();
    }
}

void MainWindow::showGameOver(const QString &winner) {
    gameController->revealDealerCards();

    QMessageBox::information(this, tr("Game Over"), tr("Winner: %1").arg(winner));
    gameController->startGame();
}

void MainWindow::loadLanguage(const QString &langCode) {
    qApp->removeTranslator(&translator);

    if (translator.load(":/translations/language_" + langCode + ".qm")) {
        qApp->installTranslator(&translator);
        ui->retranslateUi(this); // оновленння тексту новим перекладом
    }
    else {
        QMessageBox::warning(this, tr("Error"), tr("Translation file not found for language: %1").arg(langCode));
    }
}
