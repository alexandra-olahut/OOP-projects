#pragma once
#include <qabstractitemmodel.h>

#include "Mylist.h"


class MylistModel : public QAbstractTableModel
{
private:
	MyList& repository;

public:
	MylistModel(MyList& repo) : repository(repo) {}

	int rowCount(const QModelIndex& parent = QModelIndex()) const;
	int columnCount(const QModelIndex& parent = QModelIndex()) const;

	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

	void update();



//	bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole);
//	Qt::ItemFlags flags(const QModelIndex& index) const;
};

