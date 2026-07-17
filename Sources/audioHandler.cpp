#include "audioHandler.h"
#include <print>

AudioHandler::AudioHandler(QObject *parent) : QObject(parent) {
    player_ = new QMediaPlayer(this);
    audioOutput_ = new QAudioOutput(this);
    //ai written debug statement 
    QObject::connect(player_, &QMediaPlayer::errorOccurred, [](QMediaPlayer::Error error, const QString &errorString) {
    std::cout << "player error: " << error << " " << errorString.toStdString() << std::endl;
    });

    player_->setAudioOutput(audioOutput_);
    audioOutput_->setVolume(.1);
}

void AudioHandler::play() {
    player_->play();
}

void AudioHandler::pause() {
    player_->pause();
}

int AudioHandler::getDur() {
    return player_->duration();
}

void AudioHandler::loop() {
    player_->Infinite;
    looping = !looping;
}

bool AudioHandler::isLooping() {
    return looping; 
}

QMediaPlayer* AudioHandler::getPlayer() {
    return player_;
}

void AudioHandler::setVolume(int volume) {
    audioOutput_->setVolume(volume/100.0);
}

void AudioHandler::setSource(Song song) {
    player_->setSource(QUrl::fromLocalFile(QString::fromStdString(song.file_path_as_string)));
}

