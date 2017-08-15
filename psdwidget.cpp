#include "psdwidget.h"

#include <QHBoxLayout>

PSDWidget::PSDWidget(QWidget *parent) : QWidget(parent)
{
    QHBoxLayout *layout = new QHBoxLayout();

    layout->addWidget(new PSDView());


    setLayout(layout);
}
