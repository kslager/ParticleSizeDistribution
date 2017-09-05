#include "psdview.h"
#include <QtCharts/QChart>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QValueAxis>
#include <QtCharts/QLogValueAxis>
#include <QPrinter>

#include <QTextBlockFormat>
#include <QTextCursor>

#include <QDebug>

PSDView::PSDView(QWidget *parent) : QGraphicsView(new QGraphicsScene, parent),
    _chart(0)
{
    _chart = new QChart();
    _chart->setMinimumSize(400, 300);
    _chart->setBackgroundVisible(false);
    //_chart->setTitle("Hover the line to show callout. Click the line to make it stay");
    _chart->legend()->hide();

    /*QLineSeries *series = new QLineSeries;
    series->append(0.063,0.0);
    series->append(0.0746,0.1);
    series->append(0.0909,0.2);
    series->append(0.1134,0.3);
    series->append(0.1417,0.4);
    series->append(0.1748,0.5);
    series->append(0.2044,0.6);
    series->append(0.2346,0.7);
    series->append(0.2726,0.8);
    series->append(0.3293,0.9);
    series->append(1.0000,1.0);*/

    QSplineSeries *series = new QSplineSeries;
    series->append(0.0336309228718879, 0.0);
    series->append(0.0595849288565138, 0.1);
    series->append(0.0784757163748353, 0.2);
    series->append(0.0900605761092338, 0.3);
    series->append(0.096991665042042, 0.4);
    series->append(0.103355633357786, 0.5);
    series->append(0.108976770650809, 0.6);
    series->append(0.114903621173393, 0.7);
    series->append(0.122442856675688, 0.8);
    series->append(0.137572925508522, 0.9);
    series->append(0.195133363519118, 1.0);
    _chart->addSeries(series);

    QLogValueAxis *axisX = new QLogValueAxis;
    axisX->setRange(MIN_D,MAX_D);
    axisX->setVisible(false);
    _chart->addAxis(axisX, Qt::AlignBottom);

    QValueAxis *axisY = new QValueAxis;
    axisY->setRange(0.0,1.0);
    axisY->setTickCount(11);
    axisY->setTitleText("Mass percentage passing sieve");
    axisY->setLabelsVisible(false);
    _chart->addAxis(axisY, Qt::AlignLeft);

    series->attachAxis(axisX);
    series->attachAxis(axisY);

    setRenderHint(QPainter::Antialiasing);

    std::vector<double> NEN2560 = {0.045, 0.063, 0.090, 0.125, 0.180, 0.250, 0.355, 0.500, 0.710, 1, 1.4, 2, 2.8, 4, 5.6, 8, 11.2, 16, 22.4, 31.5, 45, 63, 90, 125};
    QFont sieveFont;
    sieveFont.setPointSize(8);

    for (double item : NEN2560)
    {
        sieve tmp;

        tmp.size = item;
        tmp.gridLine = scene()->addLine(0.0, 0.0, 0.0, 0.0);
        tmp.gridLine->setPen(axisX->gridLinePen());

        tmp.label = scene()->addText(printDiameter(tmp.size), sieveFont);
        tmp.label->setRotation(-90);

        _sieves.push_back(tmp);
    }

    QFont font;
    font.setBold(true);
    _sieveClassLabel = scene()->addText("Sieves according to NEN 2560", font);

    scene()->addItem(_chart);

    // Soil classification

    _soilClassificationLabel = scene()->addText("Soil classification NEN 5104", font);

    _soilClass.bottomLine = scene()->addLine(0.0, 0.0, 0.0, 0.0);
    _soilClass.bottomLine->setPen(axisX->gridLinePen());
    _soilClass.middleLine = scene()->addLine(0.0, 0.0, 0.0, 0.0);
    _soilClass.middleLine->setPen(axisX->gridLinePen());

    _soilClass.intervals = { MIN_D, 0.002, 0.063, 2.0, 63.0, 200.0, 650.0, MAX_D};
    std::vector<std::string> labels = { "lutum", "silt", "zand", "grind", "stenen", "keien", "blokken" };
//    std::vector<std::string> labels = { "clay", "silt", "sand", "gravel", "stones", "cobbles", "blocks" };

    for(uint i = 1; i < _soilClass.intervals.size()-1; i++)
    {
        _soilClass.intervalLines.push_back( scene()->addLine(0.0, 0.0, 0.0, 0.0) );
        _soilClass.intervalLines.at(i-1)->setPen(axisX->gridLinePen());
    }

    font.setBold(false);
    font.setPointSize(8);
    QTextBlockFormat format;
    format.setAlignment(Qt::AlignCenter);
    QTextCursor cursor; // = tmp->textCursor();

    for(uint i = 0; i < labels.size(); i++)
    {
        _soilClass.intervalLabels.push_back( scene()->addText( QString::fromStdString(labels[i]) ) );
        _soilClass.intervalLabels[i]->setFont(font);
        cursor = _soilClass.intervalLabels[i]->textCursor();
        cursor.select(QTextCursor::Document);
        cursor.mergeBlockFormat(format);
        cursor.clearSelection();
        _soilClass.intervalLabels[i]->setTextCursor(cursor);
    }

    _soilClass.subintervals = { MIN_D, 0.002, 0.063, 0.150, 0.300, 2.0, 5.6, 16.0, 63.0, 200.0, 650.0, MAX_D };
    std::vector<std::string> sublabels = { "", "", "fijn", "middel", "grof", "fijn", "matig grof", "grof", "", "", "" };
//    std::vector<std::string> sublabels = { "", "", "fine", "medium", "coarse", "fine", "medium coarse", "coarse", "", "", "" };

    for(uint i = 1; i < _soilClass.subintervals.size()-1; i++)
    {
        _soilClass.subintervalLines.push_back( scene()->addLine(0.0, 0.0, 0.0, 0.0) );
        _soilClass.subintervalLines.at(i-1)->setPen(axisX->gridLinePen());
    }

    font.setPointSize(7);
    for(uint i = 0; i< sublabels.size(); i++)
    {
        _soilClass.subintervalLabels.push_back( scene()->addText( QString::fromStdString(sublabels[i]) ) );
        _soilClass.subintervalLabels[i]->setFont(font);
        cursor = _soilClass.subintervalLabels[i]->textCursor();
        cursor.select(QTextCursor::Document);
        cursor.mergeBlockFormat(format);
        cursor.clearSelection();
        _soilClass.subintervalLabels[i]->setTextCursor(cursor);
    }

    font.setPointSize(6);
    for(uint i = 1; i < _soilClass.subintervals.size()-1; i++)
    {
        _soilClass.limitLabels.push_back( scene()->addText( printDiameter(_soilClass.subintervals[i]) ) );
        _soilClass.limitLabels[i-1]->setFont(font);
    }

    font.setPointSize(8);
    for(int i = 0; i <= 100; i += 10 )
    {
        _yAxisLabels.push_back(scene()->addText( QString("%1%").arg(QString::number(i), 3, ' ') ));
        _yAxisLabels[i/10]->setFont(font);
    }
}

void PSDView::resizeEvent(QResizeEvent *event)
{
    if (scene()) {
        QSize sceneSize = event->size();

        // Adjust chart to have constant size ratio, same as A4 paper
        if ( sceneSize.width()*210 > sceneSize.height()*297 )
        {
            sceneSize.setWidth( sceneSize.height() * 297 / 210 );
        } else {
            sceneSize.setHeight( sceneSize.width() * 210 / 297 );
        }

        scene()->setSceneRect(QRect(QPoint(0, 0), sceneSize ));

        double barHeight = 1.0/7.0, chartHeight = 1.0 - 2*barHeight;

        // Resize the chart to leave a bottom and top bar of 20% empty space
        _chart->resize(sceneSize.width(), sceneSize.height()*chartHeight);
        _chart->setPos(0, sceneSize.height()*barHeight);

        // Adjust the sieve grid lines and the labels
        QPointF p1, p2;
        for (uint i = 0; i<_sieves.size(); i++)
        {
            // Points for general use
            p1 = _chart->mapToPosition(QPointF(_sieves[i].size, 0.01));
            p1.setY( p1.y() + barHeight*sceneSize.height() );
            p2 = _chart->mapToPosition(QPointF(_sieves[i].size, 0.99));
            p2.setY( p2.y() + barHeight*sceneSize.height() );

            // position lines
            _sieves[i].gridLine->setLine(p1.x(), p1.y(), p2.x(), p2.y());

            // position label
            p2 = _chart->mapToPosition(QPointF(_sieves[i].size, 1.01));
            p2.setY( p2.y() + barHeight*sceneSize.height() );
            p2.setX(p2.x() - _sieves[i].label->boundingRect().height()*0.5);
            _sieves[i].label->setPos(p2);
        }

        p1 = _chart->mapToPosition(QPointF(_sieves[0].size, 1.17));
        p1.setY(p1.y() + barHeight*sceneSize.height());
        _sieveClassLabel->setPos(p1);

        // Adjust the soil class bar
        p1 = _chart->mapToPosition(QPointF(MIN_D, -0.2));
        p1.setY(p1.y() + barHeight*sceneSize.height());
        p2 = _chart->mapToPosition(QPointF(MAX_D, -0.2));
        p2.setY(p2.y() + barHeight*sceneSize.height());
        _soilClass.bottomLine->setLine(p1.x(), p1.y(), p2.x(), p2.y());

        p1 = _chart->mapToPosition(QPointF(MIN_D, -0.15));
        p1.setY(p1.y() + barHeight*sceneSize.height());
        p2 = _chart->mapToPosition(QPointF(MAX_D, -0.15));
        p2.setY(p2.y() + barHeight*sceneSize.height());
        _soilClass.middleLine->setLine(p1.x(), p1.y(), p2.x(), p2.y());

        // Interval lines
        for(uint i = 1; i < _soilClass.intervals.size()-1; i++)
        {
            p1 = _chart->mapToPosition(QPointF(_soilClass.intervals[i], -0.2));
            p1.setY(p1.y() + barHeight*sceneSize.height());
            p2 = _chart->mapToPosition(QPointF(_soilClass.intervals[i], -0.15));
            p2.setY(p2.y() + barHeight*sceneSize.height());
            _soilClass.intervalLines[i-1]->setLine(p1.x(), p1.y(), p2.x(), p2.y());
        }

        // Interval labels, centered
        for(uint i = 0; i < _soilClass.intervals.size()-1; i++)
        {
            p1 = _chart->mapToPosition(QPointF(_soilClass.intervals[i], -0.15));
            p1.setY(p1.y() + barHeight*sceneSize.height());
            p2 = _chart->mapToPosition(QPointF(_soilClass.intervals[i+1], -0.2));
            p2.setY(p2.y() + barHeight*sceneSize.height());

            int offset = p2.y() - p1.y() - _soilClass.intervalLabels[i]->boundingRect().height();
            p1.setY( p1.y() + offset/2);
            _soilClass.intervalLabels[i]->setPos(p1);
            _soilClass.intervalLabels[i]->setTextWidth( p2.x() - p1.x() );
        }

        // subinterval lines
        for(uint i = 1; i < _soilClass.subintervals.size()-1; i++)
        {
            p1 = _chart->mapToPosition(QPointF(_soilClass.subintervals[i], -0.15));
            p1.setY(p1.y() + barHeight*sceneSize.height());
            p2 = _chart->mapToPosition(QPointF(_soilClass.subintervals[i], -0.10));
            p2.setY(p2.y() + barHeight*sceneSize.height());
            _soilClass.subintervalLines[i-1]->setLine(p1.x(), p1.y(), p2.x(), p2.y());
        }

        // Interval labels, centered
        for(uint i = 0; i < _soilClass.subintervals.size()-1; i++)
        {
            p1 = _chart->mapToPosition(QPointF(_soilClass.subintervals[i], -0.10));
            p1.setY(p1.y() + barHeight*sceneSize.height());
            p2 = _chart->mapToPosition(QPointF(_soilClass.subintervals[i+1], -0.15));
            p2.setY(p2.y() + barHeight*sceneSize.height());

            int offset = p2.y() - p1.y() - _soilClass.subintervalLabels[i]->boundingRect().height();
            p1.setY( p1.y() + offset/2);
            _soilClass.subintervalLabels[i]->setPos(p1);
            _soilClass.subintervalLabels[i]->setTextWidth( p2.x() - p1.x() );
        }

        // limit labels
        for(uint i = 0; i < _soilClass.subintervals.size()-2; i++)
        {
            //_soilClass.limitLabels.push_back( scene()->addText( printDiameter(_soilClass.subintervals[i]) ) );
            //_soilClass.limitLabels[i]->setFont(font);
            p1 = _chart->mapToPosition(QPointF(_soilClass.subintervals[i+1], -0.10));
            p1.setY(p1.y() + barHeight*sceneSize.height() - _soilClass.limitLabels[i]->boundingRect().height());
            p1.setX(p1.x() - 0.5*_soilClass.limitLabels[i]->boundingRect().width());

            _soilClass.limitLabels[i]->setPos(p1);
        }

        p1 = _chart->mapToPosition(QPointF(_soilClass.intervals[0], -0.23));
        p1.setY(p1.y() + barHeight*sceneSize.height());
        _soilClassificationLabel->setPos(p1);

        // y-axis labels
        for(int i=0; i<=10; i++)
        {
            p1 = _chart->mapToPosition(QPointF(MIN_D, i/10.0));
            p1.setY(p1.y() + barHeight*sceneSize.height() - _yAxisLabels[i]->boundingRect().height()*0.5);
            p1.setX(p1.x() - _yAxisLabels[i]->boundingRect().width() - 4);
            _yAxisLabels[i]->setPos(p1);

        }
    }

    QGraphicsView::resizeEvent(event);
}

QString PSDView::printDiameter(double d)
{
    QString result;

    // Distinghish between micrometers and millimeters
    if (d < 1.0)
    {
        // Display in micrometer units
        result = QString("%1 μm").arg(QString::number(d*1000));
    }
    else
    {
        // Display in millimeter units, adjust precision to match significance
        if (d < 100)
        {
            result = QString("%1 mm").arg(QString::number(d, 'f', 1));
        }
        else
        {
            result = QString("%1 mm").arg(QString::number(d, 'f', 0));
        }
    }

    return result;
}

void PSDView::exportPDF()
{
    qDebug() << "Start of exportPDF() function";

    QPrinter printer(QPrinter::HighResolution);
    printer.setPaperSize(QPrinter::A4);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName("test.pdf");

    QPainter painter(&printer);

    scene()->render(&painter);
    painter.end();

    qDebug() << "End of exportPDF() function";
}





