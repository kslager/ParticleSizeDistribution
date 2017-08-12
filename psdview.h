#ifndef PSDVIEW_H
#define PSDVIEW_H

#include <QtWidgets/QGraphicsView>
#include <QtCharts/QChartGlobal>

QT_CHARTS_BEGIN_NAMESPACE
class QChart;
QT_CHARTS_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE

class PSDView : public QGraphicsView
{
    Q_OBJECT

public:
    PSDView(QWidget *parent = 0);

protected:
    void resizeEvent(QResizeEvent *event);
//    void mouseMoveEvent(QMouseEvent *event);

private:
    QChart *_chart;
    QList<QGraphicsLineItem *> _sieveGridLines;
    std::vector<double> _sieves = {0.063, 0.090, 0.125, 0.180, 0.250, 0.355, 0.5, 0.710, 1.0, 1.4, 2.0, 2.8, 4.0};
};

#endif // PSDVIEW_H
