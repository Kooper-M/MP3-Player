#include "mainwindow.h"
#include <QTextStream>

void MainWindow::handleNextSong() {
    Song newSong = playlist_.next();
    currSongTitle_->setText(QString::fromStdString(newSong.name));
    audio_.setSource(newSong);
    audio_.play();
}

void MainWindow::updateSongProgress(int pos) {
    songProgress->blockSignals(true);
    audio_.getPlayer()->setPosition(pos);
    songProgress->blockSignals(false);
}

void MainWindow::handlePrevSong() {
    Song newSong = playlist_.prev();
    currSongTitle_->setText(QString::fromStdString(newSong.name));
    audio_.setSource(newSong);
    audio_.play();
}

MainWindow::MainWindow(QWidget *parent) 
: QMainWindow(parent), audio_(this), playlist_("C:/Users/koopa/personal projects/MP3_Player/audio files") {
    QWidget *centralWidget = new QWidget(this);

    QPushButton *playButton = new QPushButton("Play me", centralWidget);
    QPushButton *loopButton = new QPushButton("Loop me", centralWidget);
    QPushButton *autoButton = new QPushButton("Auto Next", centralWidget);
    QPushButton *pauseButton = new QPushButton("Pause me", centralWidget);
    QPushButton *quitButton = new QPushButton("Quit me", centralWidget);
    QPushButton *nextButton = new QPushButton("Next", centralWidget);
    QPushButton *prevButton = new QPushButton("Previous", centralWidget);

    currSongTitle_ = new QLabel(QString::fromStdString(playlist_.getSong().name), centralWidget);
    currSongTitle_->setAlignment(Qt::AlignCenter);

    QSlider *volumeSlider = new QSlider(Qt::Vertical, centralWidget);
    volumeSlider->setRange(0,100);
    volumeSlider->setValue(10);

    songProgress = new QSlider(Qt::Horizontal, centralWidget);
    songProgress->setRange(0, audio_.getDur());
    songProgress->setValue(0);

    audio_.setSource(playlist_.getSong());

    
    QObject::connect(playButton, &QPushButton::clicked, &audio_, &AudioHandler::play);
    QObject::connect(pauseButton, &QPushButton::clicked, &audio_,&AudioHandler::pause);
    QObject::connect(quitButton, &QPushButton::clicked, this, &MainWindow::close);
    QObject::connect(loopButton, &QPushButton::clicked, &audio_, &AudioHandler::loop);
    QObject::connect(autoButton, &QPushButton::clicked, &playlist_, &Playlist::flipAutoNext);


    QObject::connect(nextButton, &QPushButton::clicked, this, &MainWindow::handleNextSong);

    QObject::connect(prevButton, &QPushButton::clicked, this, &MainWindow::handlePrevSong);

    QObject::connect(volumeSlider, &QSlider::sliderMoved, &audio_, &AudioHandler::setVolume);

    //song progress bar
    QObject::connect(audio_.getPlayer(), &QMediaPlayer::durationChanged, songProgress, &QSlider::setMaximum);
    QObject::connect(audio_.getPlayer(), &QMediaPlayer::positionChanged, songProgress, &QSlider::setValue);

    QObject::connect(audio_.getPlayer(), &QMediaPlayer::mediaStatusChanged, this, [this](QMediaPlayer::MediaStatus status) {
        if (status == QMediaPlayer::EndOfMedia) {
            if (audio_.isLooping()) {
                audio_.play();
            } else if (playlist_.isAutoNext()) {
                handleNextSong();
            } else {
                ; // do nothing
            }
        }
    });

    QObject::connect(songProgress, &QSlider::sliderMoved, this, &MainWindow::updateSongProgress);

    //layout
    QHBoxLayout *layoutHorizontal = new QHBoxLayout(centralWidget);

    QVBoxLayout *layout = new QVBoxLayout(centralWidget);



    layoutHorizontal->addWidget(loopButton);
    layoutHorizontal->addWidget(prevButton);
    layoutHorizontal->addLayout(layout);
    layoutHorizontal->addWidget(nextButton);
    layoutHorizontal->addWidget(autoButton);
    layoutHorizontal->addWidget(volumeSlider);
    
    layout->addWidget(currSongTitle_);
    layout->addWidget(playButton);
    layout->addWidget(pauseButton);
    layout->addWidget(songProgress);

    setCentralWidget(centralWidget);
}
MainWindow::~MainWindow() {}