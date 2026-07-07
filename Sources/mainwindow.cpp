#include "mainwindow.h"
#include <QPushButton>
#include <QWidget> 
#include <QVBoxLayout>
#include <QLabel>
#include <QSlider>
#include <QSpinBox>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QUrl>
MainWindow::MainWindow(QWidget *parent) 
: QMainWindow(parent), audio_(QUrl::fromLocalFile("C:/Users/koopa/personal projects/MP3_Player/audio files/nemocircusahbeat.mp3")) {
    QWidget *centralWidget = new QWidget(this);

    QPushButton *button1 = new QPushButton("Play me", centralWidget);
    QPushButton *button2 = new QPushButton("Pause me", centralWidget);
    QPushButton *button3 = new QPushButton("Quit me", centralWidget);
    QObject::connect(button3, &QPushButton::clicked, this, &MainWindow::close);
    QObject::connect(button1, &QPushButton::clicked, this, [this]() {
        audio_.play();
    });

    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    layout->addWidget(button3);

    layout->addWidget(button1);
    layout->addWidget(button2);

    setCentralWidget(centralWidget);
}
MainWindow::~MainWindow() {}