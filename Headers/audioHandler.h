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
    private:
        QMediaPlayer *player_;
        QAudioOutput *audioOutput_;
    signals:
        void close();
    public slots:
        //void updateUrl(QUrl);
        void play();
        void pause();
        void setVolume(int);
};

