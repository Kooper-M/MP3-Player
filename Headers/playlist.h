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
#include <filesystem>
#include <stdexcept>
#include <cmath>
#include <audioHandler.h>
#include "song.h"
#include <array>


class Playlist : public QObject {
    Q_OBJECT
    public:
        explicit Playlist(std::filesystem::path dir);
        Song getSong() const;
        bool isAutoNext();

    public slots:
        Song next();
        Song prev();
        void flipAutoNext();

    private:
        std::filesystem::path dir_; 
        int playListPos_ = 0;
        size_t playListSize_;
        std::vector<Song> playlist_;
        bool autoNext;


};