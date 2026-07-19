#include "mainwindow.h"


void MainWindow::handleNextSong() {
    const Song* newSong = playlist_.next();
    currSongTitle_->setText(QString::fromStdString(newSong->name));
    audio_.setSource(newSong->file_path_as_string);
    audio_.play();
}

void MainWindow::updateSongProgress(int pos) {
    songProgress->blockSignals(true);
    audio_.getPlayer()->setPosition(pos);
    songProgress->blockSignals(false);
}

void MainWindow::handlePrevSong() {
    const Song* newSong = playlist_.prev();

    currSongTitle_->setText(QString::fromStdString(newSong->file_path_as_string));
    audio_.setSource(newSong->file_path_as_string);
    audio_.play();
}

MainWindow::MainWindow(QWidget *parent) 
: QMainWindow(parent), audio_(this), playlist_("C:/Users/koopa/personal projects/MP3_Player/audio files") {
    QWidget* centralWidget = new QWidget(this);

    QPushButton *playButton = new QPushButton("Play/Pause", centralWidget);
    QPushButton *loopButton = new QPushButton("Loop me", centralWidget);
    QPushButton *autoButton = new QPushButton("Auto Next", centralWidget);
    //QPushButton *pauseButton = new QPushButton("Pause me", centralWidget);
    QPushButton *quitButton = new QPushButton("Quit me", centralWidget);
    QPushButton *nextButton = new QPushButton("Next", centralWidget);
    QPushButton *prevButton = new QPushButton("Previous", centralWidget);

    currSongTitle_ = new QLabel(QString::fromStdString(playlist_.getSong()->name), centralWidget);
    currSongTitle_->setAlignment(Qt::AlignCenter);

    QSlider *volumeSlider = new QSlider(Qt::Vertical, centralWidget);
    volumeSlider->setRange(0,100);
    volumeSlider->setValue(10);

    songProgress = new QSlider(Qt::Horizontal, centralWidget);
    songProgress->setRange(0, audio_.getDur());
    songProgress->setValue(0);

    audio_.setSource(playlist_.getSong()->file_path_as_string);

    
    QObject::connect(playButton, &QPushButton::clicked, this, [this]() {
        if (audio_.isPlaying()) {
            audio_.pause();
        } else {
            audio_.play();
        }
    });
    //QObject::connect(pauseButton, &QPushButton::clicked, &audio_,&AudioHandler::pause);
    QObject::connect(quitButton, &QPushButton::clicked, this, &MainWindow::close);
    QObject::connect(loopButton, &QPushButton::clicked, this, [this, loopButton]() {
        audio_.loop();
        if (audio_.isLooping()) {
            loopButton->setStyleSheet(
                "QPushButton { background-color : #0078D7 }"
            );
        } else {
            loopButton->setStyleSheet(
                ""
            );
        }
    });
    QObject::connect(autoButton, &QPushButton::clicked, this, [this, autoButton]() {
        playlist_.autoNext();
        std::cout << playlist_.isAutoNext() << std::endl;
        if (playlist_.isAutoNext()) {
            autoButton->setStyleSheet(
                "QPushButton { background-color : #0078D7 }"
            );
        } else {
            autoButton->setStyleSheet(
                ""
            );
        } 
    });


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

    QVBoxLayout *midlayout = new QVBoxLayout(centralWidget);

    

    QWidget *playListWidget = new QWidget;
    QVBoxLayout *playlistLayout = new QVBoxLayout(playListWidget);
    QScrollArea *scrollArea = new QScrollArea(centralWidget);
    scrollArea->setWidget(playListWidget);
    scrollArea->setWidgetResizable(true);


    layoutHorizontal->addWidget(loopButton);
    layoutHorizontal->addWidget(prevButton);
    layoutHorizontal->addLayout(midlayout);
    layoutHorizontal->addWidget(nextButton);
    layoutHorizontal->addWidget(autoButton);
    layoutHorizontal->addWidget(volumeSlider);

    layoutHorizontal->addWidget(scrollArea);
    
    midlayout->addWidget(currSongTitle_);
    midlayout->addWidget(playButton);
    //layout->addWidget(pauseButton);
    midlayout->addWidget(songProgress);

    for (auto song : *playlist_.getPlaylist()) {
        QLabel *songOption = new QLabel(QString::fromStdString(song.name), playListWidget);
        playlistLayout->addWidget(songOption);
    }

    setCentralWidget(centralWidget);
}
MainWindow::~MainWindow() {}