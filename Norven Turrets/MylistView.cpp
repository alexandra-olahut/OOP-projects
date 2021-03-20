#include "MylistView.h"
#include "PictureDelegate.h"

MylistView::MylistView(MylistModel* model, QWidget *parent)
	: QWidget(parent), model(model)
{
	ui.setupUi(this);

	ui.mylist_tableView->setModel(this->model);

	ui.mylist_tableView->setItemDelegate(new PictureDelegate {} );
	ui.mylist_tableView->resizeColumnsToContents();
	ui.mylist_tableView->resizeRowsToContents();
}

MylistView::~MylistView()
{
}

void MylistView::update_model()
{
	this->model->update();
	ui.mylist_tableView->resizeColumnsToContents();
	ui.mylist_tableView->resizeRowsToContents();
}
