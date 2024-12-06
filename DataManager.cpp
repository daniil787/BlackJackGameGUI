#include"DataManager.h"


void DataManager::saveStatistics (const QString &path, const QJsonObject &data)
    {
    QFile file(path);
        if(!file.open(QIODevice::WriteOnly)) return;

        QJsonDocument doc(data);
        file.write(doc.toJson());

    }

   /* QJsonObject DataManager::loadStatistics(const QString &path){

    QFile file(path);
        if(!file.open(QIODevice::ReadOnly)) return {};

        QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
        return doc.object();
    }
*/

