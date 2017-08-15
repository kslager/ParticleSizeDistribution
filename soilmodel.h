#ifndef SOILMODEL_H
#define SOILMODEL_H

#include <QAbstractListModel>

#include <QDebug>

class SoilModel : public QAbstractListModel
{
public:
    SoilModel();

    int rowCount( const QModelIndex & parent = QModelIndex() ) const { return 5; }
    QVariant data( const QModelIndex & index, int role = Qt::DisplayRole ) const
    {
        if ( role == Qt::DisplayRole )
        {
            switch ( index.row() )
            {
                case 0:
                    return "Fine sand";
                case 1:
                    return "Medium fine sand";
                case 2:
                    return "Coarse sand";
                case 3:
                    return "Coarse sand and gravel";
                case 4:
                    return "Gravel";
                default:
                    return "some sand";
            }
        }
        return QVariant();
    }
};

#endif // SOILMODEL_H
