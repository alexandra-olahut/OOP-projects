#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Hybris.h"

class Hybris : public QMainWindow
{
	Q_OBJECT

public:
	Hybris(QWidget *parent = Q_NULLPTR);

private:
	Ui::HybrisClass ui;
};
