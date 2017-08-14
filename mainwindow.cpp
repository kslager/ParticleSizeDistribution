#include "mainwindow.h"

#include "psdview.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setMinimumSize(1024, 768);

    setWindowTitle("Particle size distribution (beta)");
    setCentralWidget(new PSDView());
}
