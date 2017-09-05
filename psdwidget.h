#ifndef PSDWIDGET_H
#define PSDWIDGET_H

#include <QWidget>

#include "psdview.h"

class PSDWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PSDWidget(QWidget *parent = nullptr);
    PSDView *view() { return this->m_view; };

private:
    PSDView *m_view;

signals:

public slots:

};

#endif // PSDWIDGET_H
