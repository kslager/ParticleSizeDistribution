#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAction>

#include "psdwidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    PSDView * view() { return m_widget->view(); }

private:
    void createActions();
    void createMenus();

    PSDWidget * m_widget;

    QMenu *fileMenu;

    QAction *pdfAct;

    QAction *exitAct;

signals:

public slots:

private slots:
};

#endif // MAINWINDOW_H
