#include "InfoTableModel.h"

InfoTableModel::InfoTableModel(QString n, QObject *parent) :
    QAbstractTableModel(parent)
{
	dataList = new QMap<QString, QString>();
}
int InfoTableModel::rowCount(const QModelIndex &parent) const
{
	return dataList->size();
}
int InfoTableModel::columnCount(const QModelIndex &parent) const
{
    return 2;
}

QVariant InfoTableModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole) {
        if (index.column() == 0)
        {
			return dataList->keys().at(index.row());
        }
        if (index.column() == 1)
        {
			return dataList->values().at(index.row());
        }
    }
    return QVariant();
}

void InfoTableModel::updateData(QPair<QString, QString> incomingData)
{
	dataList->insert(incomingData.first, incomingData.second);
}