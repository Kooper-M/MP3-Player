#include "mainwindow.h"

#include <QApplication>
#include <QPushButton>
#include <iostream>

int main(int argc, char *arv[]) {
    QApplication app(argc, arv); 

    MainWindow w;
    w.show();
    return app.exec();
}