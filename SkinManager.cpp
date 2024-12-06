#include "SkinManager.h"
#include<QDir>
QString SkinManager::frontSkinPath = ":/front_skins/resourses/images/cards_skins/default/face_side";
QString SkinManager::backSkinPath = ":/back_skins/resourses/images/cards_skins/version_4/back_side/back_1.png";

QString SkinManager::getFrontSkin(const QString &rank, const QString &suit) {
    return frontSkinPath + "/" + rank + "_of_" + suit + ".png";
}
QString SkinManager::getBackSkin() {
    if (backSkinPath.isEmpty()) {
        qWarning() << "Back skin path is empty.";
        return "";
    }
    return backSkinPath;
}

void SkinManager::setFrontSkinPath(const QString &path) {
    if (QDir(path).exists()) {
        frontSkinPath = path;
    } else {
        qWarning() << "Invalid front skin path:" << path;
    }
}

void SkinManager::setBackSkinPath(const QString &path) {
    backSkinPath = path;
}
