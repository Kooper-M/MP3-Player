#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include "audioHandler.h"

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
    private: 
        UI::MainWIndow *ui;
        AudioHandler audio_;
};
#endif 