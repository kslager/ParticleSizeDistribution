#ifndef PSDVIEW_H
#define PSDVIEW_H

#include <QtWidgets/QGraphicsView>
#include <QtCharts/QChartGlobal>

QT_CHARTS_BEGIN_NAMESPACE
class QChart;
QT_CHARTS_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE

struct sieve {
    double size;
    QGraphicsLineItem * gridLine;
    QGraphicsTextItem * label;
};

struct soilClassification {
    QGraphicsLineItem * bottomLine;
    QGraphicsLineItem * middleLine;

    std::vector<double> intervals;
    std::vector<QGraphicsLineItem *> intervalLines;
    std::vector<QGraphicsTextItem *> intervalLabels;

    std::vector<double> subintervals;
    std::vector<QGraphicsLineItem *> subintervalLines;
    std::vector<QGraphicsTextItem *> subintervalLabels;

    std::vector<QGraphicsTextItem *> limitLabels;
};

class PSDView : public QGraphicsView
{
    Q_OBJECT

public:
    PSDView(QWidget *parent = 0);

    QString printDiameter(double d);

protected:
    void resizeEvent(QResizeEvent *event);
//    void mouseMoveEvent(QMouseEvent *event);

private:
    QChart *_chart;
    std::vector<sieve> _sieves;
    QGraphicsTextItem * _sieveClassLabel;
    soilClassification _soilClass;
    QGraphicsTextItem * _soilClassificationLabel;
};

#endif // PSDVIEW_H
