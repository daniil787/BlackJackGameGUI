#ifndef DATAMANAGER_H
#define DATAMANAGER_H
#include<QFile>
#include<QJsonDocument>


class DataManager {
public:
    void saveStatistics(const QString &path, const QJsonObject &data);
   // QJsonObject loadStatistics(const QString &path);

};

#endif // DATAMANAGER_H
