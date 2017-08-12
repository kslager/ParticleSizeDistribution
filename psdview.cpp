#include "psdview.h"
#include <QtCharts/QChart>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QtCharts/QLogValueAxis>

#include <QDebug>

PSDView::PSDView(QWidget *parent) : QGraphicsView(new QGraphicsScene, parent),
    _chart(0)
{
    _chart = new QChart();
    _chart->setMinimumSize(400, 300);
    _chart->setBackgroundVisible(false);
    //_chart->setTitle("Hover the line to show callout. Click the line to make it stay");
    _chart->legend()->hide();

    QLineSeries *series = new QLineSeries;
    series->append(1, 0);
    series->append(4, 1);
    series->append(5, 0.4);
    series->append(7, 0.6);
    series->append(11, 0);
    _chart->addSeries(series);

    QLogValueAxis *axisX = new QLogValueAxis;
    axisX->setRange(0.001,1000);
//    axisX->setVisible(false);
    _chart->addAxis(axisX, Qt::AlignBottom);

    QValueAxis *axisY = new QValueAxis;
    axisY->setRange(0.0,1.0);
    axisY->setTickCount(11);
    _chart->addAxis(axisY, Qt::AlignLeft);

    series->attachAxis(axisX);
    series->attachAxis(axisY);

    setRenderHint(QPainter::Antialiasing);

    for (double sieve : _sieves)
    {
        _sieveGridLines.append( scene()->addLine(0.0, 0.0, 0.0, 0.0) );
//        p1 = _chart->mapToPosition(QPointF(sieve, 0.0));
//        p2 = _chart->mapToPosition(QPointF(sieve, 1.0));
//        scene()->addLine(p1.x(), p1.y(), p2.x(), p2.y());
    }

    for (QGraphicsLineItem *item : _sieveGridLines)
    {
        item->setPen( axisX->gridLinePen() );
    }

    scene()->addItem(_chart);
}

void PSDView::resizeEvent(QResizeEvent *event)
{
    if (scene()) {
        scene()->setSceneRect(QRect(QPoint(0, 0), event->size()));

        double barHeight = 1.0/7.0, chartHeight = 1.0 - 2*barHeight;

        // Resize the chart to leave a bottom and top bar of 20% empty space
        _chart->resize(event->size().width(), event->size().height()*chartHeight);
        _chart->setPos(0, event->size().height()*barHeight);

        // Adjust the sieve grid lines
        for (uint i = 0; i<_sieves.size(); i++)
        {
            QPointF p1, p2;
            p1 = _chart->mapToPosition(QPointF(_sieves[i], 0.01));
            p1.setY( p1.y() + barHeight*event->size().height() );
            p2 = _chart->mapToPosition(QPointF(_sieves[i], 0.99));
            p2.setY( p2.y() + barHeight*event->size().height() );
            _sieveGridLines[i]->setLine(p1.x(), p1.y(), p2.x(), p2.y());
        }

        //m_coordX->setPos(m_chart->size().width()/2 - 50, m_chart->size().height() - 20);
         //m_coordY->setPos(m_chart->size().width()/2 + 50, m_chart->size().height() - 20);
         //foreach (Callout *callout, m_callouts)
         //    callout->updateGeometry();
    }
    QGraphicsView::resizeEvent(event);
}

