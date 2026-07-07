#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) 
: QMainWindow(parent), 
    audio_(QString("C:/Users/koopa/personal projects/MP3_Player/audio files")) {
    QWidget *centralWidget = new QWidget(this);

    QPushButton *button1 = new QPushButton("Play me", centralWidget);
    QPushButton *button2 = new QPushButton("Pause me", centralWidget);
    QPushButton *button3 = new QPushButton("Quit me", centralWidget);
    QPushButton *button4 = new QPushButton("Next", centralWidget);

    
    QObject::connect(button1, &QPushButton::clicked, this, [this]() {
        audio_.play();
    });
    QObject::connect(button2, &QPushButton::clicked, this, [this]() {
        audio_.pause();
    });
    QObject::connect(button3, &QPushButton::clicked, this, &MainWindow::close);
    QObject::connect(button4, &QPushButton::clicked, this, [this]() {
        audio_.next();
    });

    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    layout->addWidget(button1);
    layout->addWidget(button2);
    layout->addWidget(button3);

    setCentralWidget(centralWidget);
}
MainWindow::~MainWindow() {}