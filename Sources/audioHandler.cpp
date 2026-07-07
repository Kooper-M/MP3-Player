#include "audioHandler.h"
#include <iostream>
#include <QDebug>
#include <stdexcept>

AudioHandler::AudioHandler(QUrl audioFilePath) : url_(audioFilePath) {
    player_ = new QMediaPlayer;
    audioOutput_ = new QAudioOutput;
    //ai written debug statement
    QObject::connect(player_, &QMediaPlayer::errorOccurred, [](QMediaPlayer::Error error, const QString &errorString) {
    std::cout << "player error: " << error << " " << errorString.toStdString() << std::endl;
});
    player_->setAudioOutput(audioOutput_);
    player_->setSource(url_);
    audioOutput_->setVolume(1.0);
}

void AudioHandler::play() {
    //std::cout << "we tryna play" << std::endl;
    player_->play();
    //std::cout << (player_->mediaStatus());
}