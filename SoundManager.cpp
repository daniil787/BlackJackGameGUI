#include "SoundManager.h"
#include <QFile>
SoundManager::SoundManager(QObject *parent): mediaPlayer(new QMediaPlayer(this)), backgroundMusicPlayer(new QMediaPlayer(this)) {}


void SoundManager::playSound(const QString &soundPath){

    if (!QFile::exists(soundPath)) {
        qWarning() << "Sound file not found:" << soundPath;
        return;
    }

    mediaPlayer->setSource(QUrl::fromLocalFile((soundPath)));
    mediaPlayer->play();
}

void SoundManager::playBackgroundMusic(const QString &musicPath) {
    if (!QFile::exists(musicPath)) {
        qWarning() << "Music file not found:" << musicPath;
        return;
    }

    backgroundMusicPlayer->setSource(QUrl::fromLocalFile(musicPath));
    backgroundMusicPlayer->setLoops(QMediaPlayer::Infinite);
    backgroundMusicPlayer->play();
}
