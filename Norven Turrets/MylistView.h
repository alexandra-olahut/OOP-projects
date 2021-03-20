#pragma once

#include <QWidget>
#include "ui_MylistView.h"
#include "MylistModel.h"

class MylistView : public QWidget
{
	Q_OBJECT

public:
	MylistView(MylistModel* model, QWidget *parent = Q_NULLPTR);
	~MylistView();

private:
	Ui::MylistView ui;
	MylistModel* model;

public:
	void update_model();
};
