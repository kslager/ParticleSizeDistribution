#ifndef SOILMODEL_H
#define SOILMODEL_H

#include <QAbstractListModel>

#include "soil.h"

#include <QDebug>

class SoilModel : public QAbstractListModel
{
    Q_OBJECT

public:
    SoilModel(QObject *parent = 0);

    int rowCount( const QModelIndex & parent = QModelIndex() ) const;

    QVariant data( const QModelIndex & index, int role = Qt::DisplayRole ) const;

private:
    QVector<Soil *> soils;

};

#endif // SOILMODEL_H
