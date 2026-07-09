#include "mainwindow.h"
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent) 
: QMainWindow(parent), 
    audio_(QString("C:/Users/koopa/personal projects/MP3_Player/audio files"), this) {
    QWidget *centralWidget = new QWidget(this);

    QPushButton *playButton = new QPushButton("Play me", centralWidget);
    QPushButton *pauseButton = new QPushButton("Pause me", centralWidget);
    QPushButton *quitButton = new QPushButton("Quit me", centralWidget);
    QPushButton *nextButton = new QPushButton("Next", centralWidget);
    QPushButton *prevButton = new QPushButton("Previous", centralWidget);

    QLabel *SongTitle = new QLabel(audio_.getSongTitle(), centralWidget);
    SongTitle->setAlignment(Qt::AlignCenter);

    QSlider *volumeSlider = new QSlider(Qt::Vertical, centralWidget);
    volumeSlider->setRange(0,100);
    volumeSlider->setValue(100);

    
    QObject::connect(playButton, &QPushButton::clicked, &audio_, &AudioHandler::play);
    QObject::connect(pauseButton, &QPushButton::clicked, &audio_,&AudioHandler::pause);
    QObject::connect(quitButton, &QPushButton::clicked, this, &MainWindow::close);

    QObject::connect(nextButton, &QPushButton::clicked, this, [this, SongTitle]() {
        audio_.next();
        SongTitle->setText(audio_.getSongTitle());
    });

    QObject::connect(prevButton, &QPushButton::clicked, &audio_, &AudioHandler::prev);

    QObject::connect(volumeSlider, &QSlider::valueChanged, &audio_, &AudioHandler::setVolume);

    QHBoxLayout *layoutHorizontal = new QHBoxLayout(centralWidget);

    QVBoxLayout *layout = new QVBoxLayout(centralWidget);



    
    layoutHorizontal->addWidget(prevButton);
    layoutHorizontal->addLayout(layout);
    layoutHorizontal->addWidget(nextButton);
    layoutHorizontal->addWidget(volumeSlider);
    
    layout->addWidget(SongTitle);
    layout->addWidget(playButton);
    layout->addWidget(pauseButton);

    setCentralWidget(centralWidget);
}
MainWindow::~MainWindow() {}