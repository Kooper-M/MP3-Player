#include "audioHandler.h"

AudioHandler::AudioHandler(const QString& path, QObject *parent) : dir_(path), QObject(parent), playListPos_(0) {
    dir_ = QDir(path);
    if (!dir_.exists()) {
        qWarning() << "Path does not exist" << path;
        return;
    }
    QFileInfoList list = dir_.entryInfoList(QDir::Filter::NoDotAndDotDot | QDir::Filter::AllEntries);
    for (auto file : list) {
        filePathList_ << file.absoluteFilePath();
        //std::cout << file.absoluteFilePath().toStdString() << std::endl;
    }

    player_ = new QMediaPlayer;
    audioOutput_ = new QAudioOutput;
    //ai written debug statement 
    QObject::connect(player_, &QMediaPlayer::errorOccurred, [](QMediaPlayer::Error error, const QString &errorString) {
    std::cout << "player error: " << error << " " << errorString.toStdString() << std::endl;
    });

    player_->setAudioOutput(audioOutput_);
    player_->setSource(filePathList_.at(playListPos_));
    audioOutput_->setVolume(1.0);
}

void AudioHandler::play() {
    player_->play();
}

void AudioHandler::pause() {
    player_->pause();
}
/*
void AudioHandler::updateUrl(QUrl audioFilePath) {
    url_ = audioFilePath;
    player_->setSource(url_);
}
*/
void AudioHandler::next() {
    playListPos_ = (1 + playListPos_) % (filePathList_.size());
    player_->setSource(filePathList_.at(playListPos_));
    player_->play();
}

void AudioHandler::prev() {
    std::cout << playListPos_ << std::endl;
    if (playListPos_ == 0) {
        playListPos_ = filePathList_.size() - 1;
    } else {
        --playListPos_;
    }
    std::cout << playListPos_ << std::endl;
    player_->setSource(filePathList_.at(playListPos_));
    player_->play();
}