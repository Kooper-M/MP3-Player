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

class AudioHandler : public QObject {
    Q_OBJECT
    public: 
        explicit AudioHandler(const QString& filePath, QObject *parent = nullptr);
    private:
        QMediaPlayer *player_;
        QAudioOutput *audioOutput_;
        QDir dir_; 
        QStringList filePathList_;
        int playListPos_;
        size_t playListSize_;
    signals:
        void close();
    public slots:
        //void updateUrl(QUrl);
        void play();
        void pause();
        void next();
        void prev();
};

