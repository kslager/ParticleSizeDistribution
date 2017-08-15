#include "soilmodel.h"

#include <QColor>

SoilModel::SoilModel(QObject *parent) : QAbstractListModel(parent)
{
    soils.append(new Soil("Fine sand"));
    soils.append(new Soil("Medium fine sand"));
    soils.append(new Soil("Coarse sand"));
    soils.append(new Soil("Coarse sand and gravel"));
    soils.append(new Soil("Gravel"));
}

int SoilModel::rowCount( const QModelIndex & ) const
{
    return soils.count();
}

QVariant SoilModel::data( const QModelIndex & index, int role ) const
{
    if (!index.isValid())
    {
        return QVariant();
    }

    if ( role == Qt::DisplayRole )
    {
        return QString::fromStdString( soils[ index.row() ]->name() );
    }
    else if (role == Qt::CheckStateRole) {
        return soils[index.row()]->visible() ? Qt::Checked : Qt::Unchecked;
    }
    else if (role == Qt::DecorationRole) {
        return QColor(Qt::gray);
    }

    return QVariant();
}
