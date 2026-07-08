#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) 
: QMainWindow(parent), 
    audio_(QString("C:/Users/koopa/personal projects/MP3_Player/audio files"), this) {
    QWidget *centralWidget = new QWidget(this);

    QPushButton *playButton = new QPushButton("Play me", centralWidget);
    QPushButton *pauseButton = new QPushButton("Pause me", centralWidget);
    QPushButton *quitButton = new QPushButton("Quit me", centralWidget);
    QPushButton *nextButton = new QPushButton("Next", centralWidget);
    QPushButton *prevButton = new QPushButton("Previous", centralWidget);

    
    QObject::connect(playButton, &QPushButton::clicked, &audio_, &AudioHandler::play);
    QObject::connect(pauseButton, &QPushButton::clicked, &audio_,&AudioHandler::pause);
    QObject::connect(quitButton, &QPushButton::clicked, this, &MainWindow::close);
    QObject::connect(nextButton, &QPushButton::clicked, &audio_, &AudioHandler::next);
    QObject::connect(prevButton, &QPushButton::clicked, &audio_, &AudioHandler::prev);

    QHBoxLayout *layoutHorizontal = new QHBoxLayout(centralWidget);

    QVBoxLayout *layout = new QVBoxLayout(centralWidget);



    
    layoutHorizontal->addWidget(prevButton);
    layoutHorizontal->addLayout(layout);
    layoutHorizontal->addWidget(nextButton);

    layout->addWidget(playButton);
    layout->addWidget(pauseButton);

    setCentralWidget(centralWidget);
}
MainWindow::~MainWindow() {}