#include "PictureDelegate.h"
#include <QPixmap>
#include <QPainter>
#include <qdebug.h>

PictureDelegate::PictureDelegate(QWidget* parent) : QStyledItemDelegate{ parent }
{
}

void PictureDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
	QString vision = index.model()->data(index, Qt::EditRole).toString();

	// show a picture only in the second column; the other columns remain unchanged
	if (index.column() != 4)
	{
		QStyledItemDelegate::paint(painter, option, index);
		return;
	}

	QPixmap pixMap(vision);
	painter->drawPixmap(option.rect, pixMap);

}

QSize PictureDelegate::sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const
{
	// show a picture only in the second column; the other columns remain unchanged
	if (index.column() == 4)
	{
		return QSize(120, 100);
	}

	return QStyledItemDelegate::sizeHint(option, index);
}
