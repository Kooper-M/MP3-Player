#pragma once

#include <QObject>
#include <QString>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QUrl>
#include <QDir>
#include <iostream>
#include <QDebug>
#include <QFileInfo>
#include <QFileInfoList>
#include <stdexcept>
#include <cmath>
#include "song.h"

class AudioHandler : public QObject {
    Q_OBJECT
    public: 
        explicit AudioHandler(QObject *parent = nullptr);
        void setSource(Song);
        QMediaPlayer* getPlayer();
        bool isLooping();
    
    private:
        QMediaPlayer *player_;
        QAudioOutput *audioOutput_;
        bool looping = false;
    signals:
        void close();
    public slots:
        //void updateUrl(QUrl);
        void play();
        void loop();
        void pause();
        void setVolume(int);
        int getDur();
};

