#include "windowcontrol.h"

WindowControl::WindowControl(QObject *parent)
    : QAbstractItemModel(parent)
{
}

QVariant WindowControl::headerData(int section, Qt::Orientation orientation, int role) const
{
    // FIXME: Implement me!
}

QModelIndex WindowControl::index(int row, int column, const QModelIndex &parent) const
{
    // FIXME: Implement me!
}

QModelIndex WindowControl::parent(const QModelIndex &index) const
{
    // FIXME: Implement me!
}

int WindowControl::rowCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return 0;

    // FIXME: Implement me!
}

int WindowControl::columnCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return 0;

    // FIXME: Implement me!
}

QVariant WindowControl::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    // FIXME: Implement me!
    return QVariant();
}
