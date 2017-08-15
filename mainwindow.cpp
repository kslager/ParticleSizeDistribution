#include "mainwindow.h"

#include "psdwidget.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setMinimumSize(1280, 768);

    setWindowTitle("Particle size distribution (beta)");
    setCentralWidget(new PSDWidget());
}
