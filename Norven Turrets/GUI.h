#pragma once
#include <qwidget.h>
#include <qlistwidget.h>
#include <qlineedit.h>
#include <qlabel.h>
#include <qpushbutton.h>
#include <qshortcut.h>

#include "Service.h"
#include "Exceptions.h"
#include "MylistView.h"

class GUI :
	public QWidget
{
private:
	Service& service;
	MylistView* mylist_view;

	QShortcut* undoA;
	QShortcut* redoA;
	QShortcut* undoB;
	QShortcut* redoB;

	QWidget* modeA;
	QWidget* modeB;

	// elements A
	QListWidget* turrets_listWidget;

	QLineEdit* location_lineEdit;
	QLineEdit* size_lineEdit;
	QLineEdit* auraLevel_lineEdit;
	QLineEdit* separateParts_lineEdit;
	QLineEdit* vision_lineEdit;

	QPushButton* add_button;
	QPushButton* delete_button;
	QPushButton* update_button;

	QPushButton* clear_button;

	QPushButton* undo_button;
	QPushButton* redo_button;

	// elements B
	QListWidget* mylist_listWidget;
	QListWidget* filtered_listWidget;

	QPushButton* next_button;
	QPushButton* save_button;
	QPushButton* open_button;
	QPushButton* filter_button;

	QLineEdit* current_turret;
	QLineEdit* filter_size;
	QLineEdit* filter_separateParts;

	QPushButton* MYundo_button;
	QPushButton* MYredo_button;


	QPushButton* open_view;


public:
	GUI(Service& service, MylistView* list_view);

private:
	void initGUI();
	void populate_list();
	void populate_mylist();
	void make_connections();
	void clear_lineEdits();

	int get_selected_index();

	void add_turret();
	void update_turret();
	void delete_turret();

	void next_turret();
	void save_turret();
	void open_mylist();
	void filter_list();

	void undo();
	void redo();

	void my_undo();
	void my_redo();


	void open_listView();
};

