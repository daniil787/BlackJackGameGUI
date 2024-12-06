#include "SkinGalleryDialog.h"
#include <QVBoxLayout>
#include <QDir>
#include <QPixmap>
#include <QIcon>
#include <QMessageBox>
#include<QTabWidget>
#include"SkinManager.h"

SkinGalleryDialog::SkinGalleryDialog(QWidget *parent)
    : QDialog(parent), selectedFrontSkin(""), selectedBackSkin("") {

    setWindowTitle(tr("Choose Card Skins"));
    resize(800, 600);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);


    QTabWidget *tabWidget = new QTabWidget(this);
    mainLayout->addWidget(tabWidget);

     //вкладка для скінів передніх сторін карток
    QWidget *frontTab = new QWidget();
    QVBoxLayout *frontTabLayout = new QVBoxLayout(frontTab);
    tabWidget->addTab(frontTab, tr("Front Skins"));

    QScrollArea *frontScrollArea = new QScrollArea(this);
    QWidget *frontContainer = new QWidget();
    frontGridLayout = new QGridLayout(frontContainer);

    frontButtonGroup = new QButtonGroup(this);
    loadSkins(":/front_skins/resourses/images/cards_skins", frontGridLayout, frontButtonGroup, false);

    frontScrollArea->setWidget(frontContainer);
    frontTabLayout->addWidget(frontScrollArea);

    //вкладка для скінів задніх сторін
    QWidget *backTab = new QWidget();
    QVBoxLayout *backTabLayout = new QVBoxLayout(backTab);
    tabWidget->addTab(backTab, tr("Back Skins"));

    QScrollArea *backScrollArea = new QScrollArea(this);
    QWidget *backContainer = new QWidget();
    backGridLayout = new QGridLayout(backContainer);

    backButtonGroup = new QButtonGroup(this);
    loadSkins(":/back_skins/resourses/images/cards_skins", backGridLayout, backButtonGroup, true);

    backScrollArea->setWidget(backContainer);
    backTabLayout->addWidget(backScrollArea);

    //кнопка для вибору скіна
    QPushButton *applyButton = new QPushButton(tr("Apply"));
    connect(applyButton, &QPushButton::clicked, this, [this]() {
        if (!selectedFrontSkin.isEmpty()) {
            SkinManager::setFrontSkinPath(selectedFrontSkin);
        }
        if (!selectedBackSkin.isEmpty()) {
            SkinManager::setBackSkinPath(selectedBackSkin);
        }
        accept();
    });
    mainLayout->addWidget(applyButton);

}

void SkinGalleryDialog::loadSkins(const QString &basePath, QGridLayout *layout, QButtonGroup *buttonGroup, bool isBackSide) {
    QDir baseDir(basePath);
    if (!baseDir.exists()) {
        QMessageBox::warning(this, tr("Error"), tr("Skin base path not found: %1").arg(basePath));
        return;
    }

    QString filter = isBackSide ? "back_side" : "face_side";
    QStringList versions = baseDir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
    int row = 0, col = 0;

    for (const QString &version : versions) {
        QDir versionDir(baseDir.filePath(version + "/" + filter));
        if (!versionDir.exists()) continue;

        QStringList images = versionDir.entryList(QStringList() << "*.png", QDir::Files);
        for (const QString &image : images) {
            QPushButton *btn = new QPushButton(this);
            QPixmap pixmap(versionDir.filePath(image));
            btn->setIcon(QIcon(pixmap));
            btn->setIconSize(QSize(100, 150));
            layout->addWidget(btn, row, col++);
            int id = buttonGroup->buttons().size();
            buttonGroup->addButton(btn, id);

            connect(btn, &QPushButton::clicked, this, [this, versionDir, image, isBackSide]() {
                QString path = versionDir.filePath(image);
                qDebug() << "Selected skin path:" << path;

                if (isBackSide) {
                    selectedBackSkin = path;
                } else {
                    selectedFrontSkin = path;
                }
            });

            if (col == 4) {
                col = 0;
                ++row;
            }
        }
    }
}

QString SkinGalleryDialog::getSelectedFrontSkin() const {
    return selectedFrontSkin;
}

QString SkinGalleryDialog::getSelectedBackSkin() const {
    return selectedBackSkin;
}

void SkinGalleryDialog::selectFrontSkin(int id) {

    if (frontButtonGroup) {
        QPushButton *button = qobject_cast<QPushButton *>(frontButtonGroup->button(id));
        if (button) {
            selectedFrontSkin = button->property("skinPath").toString();
        }
    }
}

void SkinGalleryDialog::selectBackSkin(int id) {

    if (backButtonGroup) {
        QPushButton *button = qobject_cast<QPushButton *>(backButtonGroup->button(id));
        if (button) {
            selectedBackSkin = button->property("skinPath").toString();
        }
    }
}
