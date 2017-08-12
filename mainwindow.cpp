#include "mainwindow.h"

#include "psdview.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setMinimumSize(1024, 768);

    setCentralWidget(new PSDView());
}
