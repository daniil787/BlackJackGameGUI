#ifndef SKINGALLERYDIALOG_H
#define SKINGALLERYDIALOG_H

#include <QDialog>
#include <QGridLayout>
#include <QScrollArea>
#include <QLabel>
#include <QPushButton>
#include <QButtonGroup>

class SkinGalleryDialog : public QDialog {
    Q_OBJECT

public:
    explicit SkinGalleryDialog(QWidget *parent = nullptr);
    QString getSelectedFrontSkin() const;
    QString getSelectedBackSkin() const;

private slots:
    void selectFrontSkin(int id);
    void selectBackSkin(int id);

private:
    QGridLayout *frontGridLayout;
    QGridLayout *backGridLayout;
    QButtonGroup *frontButtonGroup;
    QButtonGroup *backButtonGroup;

    QString selectedFrontSkin;
    QString selectedBackSkin;

    void loadSkins(const QString &path, QGridLayout *layout, QButtonGroup *buttonGroup, bool isBackSide);
};

#endif // SKINGALLERYDIALOG_H
