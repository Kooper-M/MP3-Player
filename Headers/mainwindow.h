#pragma once

#include <QMainWindow>
#include <QApplication>
#include "audioHandler.h"
#include <QPushButton>
#include <QWidget> 
#include <QVBoxLayout>
#include <QLabel>
#include <QSlider>
#include <QDir>
#include <QSpinBox>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QUrl>
#include <QString>
#include <QSlider>
#include <QSpinBox>
#include <QProgressBar>
#include <QTextStream>
#include <QScrollArea>
#include "playlist.h"

QT_BEGIN_NAMESPACE
namespace UI {
    class MainWIndow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

    public:
        MainWindow(QWidget *parent = nullptr);
        ~MainWindow();
    private slots:
        void handleNextSong();
        void handlePrevSong();
        void updateSongProgress(int pos);

    private: 
        UI::MainWIndow *ui;
        AudioHandler audio_;
        Playlist playlist_;
        QLabel *currSongTitle_;
        QSlider *songProgress;
};
