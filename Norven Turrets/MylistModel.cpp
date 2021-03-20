#include "MylistModel.h"

#define FIELDS_NUMBER 5

int MylistModel::rowCount(const QModelIndex& parent) const
{
	return this->repository.get_all().size();
}

int MylistModel::columnCount(const QModelIndex& parent) const
{
	return FIELDS_NUMBER;
}

QVariant MylistModel::data(const QModelIndex& index, int role) const
{
	int row = index.row();
	int column = index.column();
	Turret current_turret = this->repository.get_all()[row];

	if (role == Qt::DisplayRole || role == Qt::EditRole)
	{
		switch (column)
		{
		case 0:
			return QString::fromStdString(current_turret.get_location());
		case 1:
			return QString::fromStdString(current_turret.get_size());
		case 2:
			return QString::number(current_turret.get_auraLevel());
		case 3:
			return QString::number(current_turret.get_separateParts());
		case 4:
			return QString::fromStdString(current_turret.get_vision());
		}
	}

	return QVariant();
}

QVariant MylistModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (role == Qt::DisplayRole)
	{
		if (orientation == Qt::Horizontal)
		{
			switch (section)
			{
			case 0:
				return QString("LOCATION");
			case 1:
				return QString("SIZE");
			case 2:
				return QString("AURA LEVEL");
			case 3:
				return QString("NR SEPARATE PARTS");
			case 4:
				return QString("VISION");
			}
		}
	}
	return QVariant();
}

void MylistModel::update()
{
	emit layoutAboutToBeChanged();
	emit layoutChanged();
}


/*
bool MylistModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
	if (role != Qt::EditRole)
		return false;

	int row = index.row();
	int col = index.column();

	Turret& current_turret = this->repository.get_all()[row];

	return false;
}

Qt::ItemFlags MylistModel::flags(const QModelIndex& index) const
{
	if (index.column() == 0)
		return Qt::ItemFlags{};
	return Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled;
}
*/