#include "mainwindow.h"

#include "psdwidget.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setMinimumSize(1024, 768);

    setWindowTitle("Particle size distribution (beta)");
    setCentralWidget(new PSDWidget());
}
