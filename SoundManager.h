#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <QMediaPlayer>
#include<QObject>

class SoundManager : public QObject {

    Q_OBJECT

public:
    explicit SoundManager(QObject *parent = nullptr);
    void playSound(const QString &soundPath);
    void playBackgroundMusic(const QString &musicPath);

private:

    QMediaPlayer *mediaPlayer;
    QMediaPlayer *backgroundMusicPlayer;
};

#endif // SOUNDMANAGER_H

