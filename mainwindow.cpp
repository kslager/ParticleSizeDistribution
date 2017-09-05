#include "mainwindow.h"

#include "psdwidget.h"

#include <QMenuBar>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setMinimumSize(1200, 800);

    setWindowTitle("Particle size distribution (beta)");

    createActions();
    createMenus();

    m_widget = new PSDWidget();
    setCentralWidget(m_widget);
}

void MainWindow::createActions()
{
    pdfAct = new QAction(tr("&Export PDF"), this);
//    pdfAct->setShortcuts(QKeySequence::);
    pdfAct->setStatusTip(tr("Export the PSD chart as pdf"));
//    connect(pdfAct, &QAction::triggered, MainWindow::view(), &PSDView::exportPDF );

    exitAct = new QAction(tr("&Quit"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    exitAct->setStatusTip(tr("Close the program"));
    connect(exitAct, &QAction::triggered, this, &MainWindow::close);
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(pdfAct);

    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);
}
