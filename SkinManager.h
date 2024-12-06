#ifndef SKINMANAGER_H
#define SKINMANAGER_H

#include <QString>

class SkinManager {
public:
    static QString getFrontSkin(const QString &rank, const QString &suit);
    static QString getBackSkin();

    static void setFrontSkinPath(const QString &path);
    static void setBackSkinPath(const QString &path);

private:
    static QString frontSkinPath;
    static QString backSkinPath;
};

#endif // SKINMANAGER_H
