#include "GUI.h"
#include "Exceptions.h"
#include <qlayout.h>
#include <qformlayout>
#include <qmessagebox.h>

#include <vector>

using namespace std;

GUI::GUI(Service& service, MylistView* list_view) : service(service), mylist_view(list_view)
{
	this->initGUI();
	this->populate_list();
	this->populate_mylist();

	this->undoA = new QShortcut(QKeySequence(QKeySequence::Undo), this->modeA);
	this->redoA = new QShortcut(QKeySequence(QKeySequence::Redo), this->modeA);
	this->undoB = new QShortcut(QKeySequence(QKeySequence::Undo), this->modeB);
	this->redoB = new QShortcut(QKeySequence(QKeySequence::Redo), this->modeB);

	this->make_connections();
}

void GUI::initGUI()
{
	// MODE A
	this->turrets_listWidget = new QListWidget{};

	this->location_lineEdit = new QLineEdit{};
	this->size_lineEdit = new QLineEdit{};
	this->auraLevel_lineEdit = new QLineEdit{};
	this->separateParts_lineEdit = new QLineEdit{};
	this->vision_lineEdit = new QLineEdit{};

	this->add_button = new QPushButton{ "Add" };
	this->delete_button = new QPushButton{ "Delete" };
	this->update_button = new QPushButton{ "Update" };

	this->clear_button = new QPushButton{ "Clear" };

//	add_button->setStyleSheet("background-color:#c5f7f3;");
//	update_button->setStyleSheet("background-color:#c5f7f3;");
//	delete_button->setStyleSheet("background-color:#c5f7f3;");

	this->undo_button = new QPushButton{ "Undo" };
	this->redo_button = new QPushButton{ "Redo" };

	QFont bold_font("Arial", 12, QFont::Bold);

	QHBoxLayout* A_main_layout = new QHBoxLayout{};

	QVBoxLayout* A_left_side = new QVBoxLayout{};
	QVBoxLayout* A_right_side = new QVBoxLayout{};


	QLabel* title_label = new QLabel{ "List of turrets" };
	title_label->setAlignment(Qt::AlignCenter);
	title_label->setFont(bold_font);

	A_right_side->addWidget(title_label);
	A_right_side->addWidget(this->turrets_listWidget);


	QLabel* empty = new QLabel{ "" };

	QFormLayout* turretsProperties_layout = new QFormLayout{};
	turretsProperties_layout->addRow("Location", this->location_lineEdit);
	turretsProperties_layout->addRow("Size", this->size_lineEdit);
	turretsProperties_layout->addRow("Aura Level", this->auraLevel_lineEdit);
	turretsProperties_layout->addRow("Nr separate parts", this->separateParts_lineEdit);
	turretsProperties_layout->addRow("Vision", this->vision_lineEdit);

	QGridLayout* buttons_layout = new QGridLayout{};
	buttons_layout->addWidget(this->add_button, 0, 1);
	buttons_layout->addWidget(this->update_button, 0, 2);
	buttons_layout->addWidget(this->delete_button, 0, 3);

	QGridLayout* undo_redo = new QGridLayout{};
	undo_redo->addWidget(this->undo_button, 0, 1);
	undo_redo->addWidget(this->redo_button, 0, 2);


	A_left_side->addWidget(empty);
	A_left_side->addLayout(turretsProperties_layout);
	A_left_side->addWidget(this->clear_button);
	A_left_side->addWidget(empty);
	A_left_side->addLayout(buttons_layout);
	A_left_side->addLayout(undo_redo);

	A_main_layout->addLayout(A_left_side);
	A_main_layout->addLayout(A_right_side);


	//MODE B

	QLabel* mylist_label = new QLabel{ "Activated turrets" };
	mylist_label->setAlignment(Qt::AlignCenter);
	mylist_label->setFont(bold_font);
	QLabel* filteredList_label = new QLabel{ "Filtered list" };
	filteredList_label->setAlignment(Qt::AlignCenter);
	filteredList_label->setFont(bold_font);

	this->next_button = new QPushButton{ "Next" };
	this->save_button = new QPushButton{ "Save" };
	this->open_button = new QPushButton{ "Open" };
	this->filter_button = new QPushButton{ "Filter" };

	this->open_view = new QPushButton{ "View" };

	this->MYundo_button = new QPushButton{ "Undo" };
	this->MYredo_button = new QPushButton{ "Redo" };


	this->mylist_listWidget = new QListWidget{};
	this->filtered_listWidget = new QListWidget{};

	this->filter_size = new QLineEdit{};
	this->filter_separateParts = new QLineEdit{};
	this->current_turret = new QLineEdit{};
	current_turret->setCursorPosition(0);


	QGridLayout* my_undo_redo = new QGridLayout{};
	my_undo_redo->addWidget(MYundo_button, 0, 0);
	my_undo_redo->addWidget(MYredo_button, 0, 1);


	QGridLayout* next_save = new QGridLayout{};
	next_save->addWidget(next_button, 0, 0);
	next_save->addWidget(save_button, 0, 1);
	
	QVBoxLayout* next_save_current = new QVBoxLayout{};
	next_save_current->setAlignment(Qt::AlignHCenter);
	next_save_current->addWidget(current_turret);
	next_save_current->addLayout(next_save);
	next_save_current->addLayout(my_undo_redo);

	
	QFormLayout* filter_buttons = new QFormLayout{};
	filter_buttons->addRow("Size: ", filter_size);
	filter_buttons->addRow("Minimum nr. parts: ", filter_separateParts);
	
	QVBoxLayout* filter = new QVBoxLayout{};
	filter->setAlignment(Qt::AlignCenter);
	filter->addLayout(filter_buttons);
	filter->addWidget(filter_button);

	QGridLayout* display = new QGridLayout{};
	display->addWidget(open_button);
	display->addWidget(open_view);

	QVBoxLayout* mylist_window = new QVBoxLayout{};
	QVBoxLayout* filtered_window = new QVBoxLayout{};
	mylist_window->addWidget(mylist_label);
	mylist_window->addWidget(mylist_listWidget);
	mylist_window->addLayout(display);
	filtered_window->addWidget(filteredList_label);
	filtered_window->addWidget(filtered_listWidget);
	
	
	QVBoxLayout* B_main_layout = new QVBoxLayout{};
	QHBoxLayout* B_up = new QHBoxLayout{};
	QHBoxLayout* B_down = new QHBoxLayout{};

	B_up->addLayout(next_save_current);
	B_up->addLayout(mylist_window);

	B_down->addLayout(filter);
	B_down->addLayout(filtered_window);


	B_main_layout->addLayout(B_up);
	B_main_layout->addLayout(B_down);

	// whole program
	this->modeA = new QWidget{};
	modeA->setLayout(A_main_layout);

	this->modeB = new QWidget{};
	modeB->setLayout(B_main_layout);


	QTabWidget* tab_widget = new QTabWidget{};
	tab_widget->addTab(modeA, "Watch Officer");
	tab_widget->addTab(modeB, "Watchman");

	QVBoxLayout* main_layout = new QVBoxLayout{ this };
	main_layout->addWidget(tab_widget);
}







void GUI::populate_list()
{
	this->turrets_listWidget->clear();

	vector<Turret> all_turrets = this->service.get_all_turrets();
	for (auto turret : all_turrets)
		this->turrets_listWidget->addItem(QString::fromStdString(turret.turn_to_string()));
}

void GUI::populate_mylist()
{
	this->mylist_listWidget->clear();

	vector<Turret> saved_turrets = this->service.get_all_activeTurrets();
	if (saved_turrets.size()>0)
		for (auto turret : saved_turrets)
			this->mylist_listWidget->addItem(QString::fromStdString(turret.turn_to_string()));
}

void GUI::make_connections()
{
	QObject::connect(this->turrets_listWidget, &QListWidget::itemSelectionChanged, [this]() {
			
		int selected_index = this->get_selected_index();
		if (selected_index < 0)
			return;

		Turret selected_turret = this->service.get_all_turrets()[selected_index];
		this->location_lineEdit->setText(QString::fromStdString(selected_turret.get_location()));
		this->size_lineEdit->setText(QString::fromStdString(selected_turret.get_size()));
		this->auraLevel_lineEdit->setText(QString::fromStdString(std::to_string(selected_turret.get_auraLevel())));
		this->separateParts_lineEdit->setText(QString::fromStdString(std::to_string(selected_turret.get_separateParts())));
		this->vision_lineEdit->setText(QString::fromStdString(selected_turret.get_vision()));

		});

	QObject::connect(this->add_button, &QPushButton::clicked, this, &GUI::add_turret);
	QObject::connect(this->update_button, &QPushButton::clicked, this, &GUI::update_turret);
	QObject::connect(this->delete_button, &QPushButton::clicked, this, &GUI::delete_turret);
	QObject::connect(this->clear_button, &QPushButton::clicked, this, &GUI::clear_lineEdits);

	QObject::connect(this->next_button, &QPushButton::clicked, this, &GUI::next_turret);
	QObject::connect(this->save_button, &QPushButton::clicked, this, &GUI::save_turret);
	QObject::connect(this->open_button, &QPushButton::clicked, this, &GUI::open_mylist);
	QObject::connect(this->filter_button, &QPushButton::clicked, this, &GUI::filter_list);


	QObject::connect(this->undo_button, &QPushButton::clicked, this, &GUI::undo);
	QObject::connect(this->redo_button, &QPushButton::clicked, this, &GUI::redo);

	QObject::connect(this->MYundo_button, &QPushButton::clicked, this, &GUI::my_undo);
	QObject::connect(this->MYredo_button, &QPushButton::clicked, this, &GUI::my_redo);

	QObject::connect(this->undoA, &QShortcut::activated, this, &GUI::undo);
	QObject::connect(this->redoA, &QShortcut::activated, this, &GUI::redo);
	QObject::connect(this->undoB, &QShortcut::activated, this, &GUI::my_undo);
	QObject::connect(this->redoB, &QShortcut::activated, this, &GUI::my_redo);

	QObject::connect(this->open_view, &QPushButton::clicked, this, &GUI::open_listView);
}

void GUI::clear_lineEdits()
{
	this->location_lineEdit->clear();
	this->size_lineEdit->clear();
	this->auraLevel_lineEdit->clear();
	this->separateParts_lineEdit->clear();
	this->vision_lineEdit->clear();
}

int GUI::get_selected_index()
{
	QModelIndexList selected_indexes = this->turrets_listWidget->selectionModel()->selectedIndexes();
	if (selected_indexes.size() == 0)
	{
		this->location_lineEdit->clear();
		this->size_lineEdit->clear();
		this->auraLevel_lineEdit->clear();
		this->separateParts_lineEdit->clear();
		this->vision_lineEdit->clear();
		return -1;
	}
	int selected_index = selected_indexes.at(0).row();
	return selected_index;
}

void GUI::add_turret()
{
	string location = this->location_lineEdit->text().toStdString();
	string auraLevel_string = this->auraLevel_lineEdit->text().toStdString();
	string separateParts_string = this->separateParts_lineEdit->text().toStdString();
	string size = this->size_lineEdit->text().toStdString();
	string vision = this->vision_lineEdit->text().toStdString();

	if (location.size() == 0 || auraLevel_string.size() == 0 || separateParts_string.size() == 0 || size.size() == 0 || vision.size() == 0)
	{
		QMessageBox::critical(this, "Wrong input", "Please provide all attributes for a turret");
		return;
	}
	int auraLevel, separateParts;

	try
	{
		auraLevel = stoi(this->auraLevel_lineEdit->text().toStdString());
		separateParts = stoi(this->separateParts_lineEdit->text().toStdString());
	}
	catch (exception& ex)
	{
		QMessageBox::critical(this, "Wrong input", "Aura level and numbr of separate parts must be integers");
		return;
	}

	
	try
	{
		this->service.add_turret_to_repository(location, size, auraLevel, separateParts, vision);
	}
	catch (Exceptions& exception)
	{
		QMessageBox::warning(this, QString::fromStdString(exception.get_type()), QString::fromStdString(exception.get_message()));
	}
	this->populate_list();
}

void GUI::update_turret()
{
	int selected_index = this->get_selected_index();
	if (selected_index < 0)
	{
		QMessageBox::critical(this, "Wrong input", "Please select a turret to update");
		return;
	}
	Turret turret = this->service.get_all_turrets()[selected_index];

	string location = turret.get_location();

	string auraLevel_string = this->auraLevel_lineEdit->text().toStdString();
	string separateParts_string = this->separateParts_lineEdit->text().toStdString();
	string size = this->size_lineEdit->text().toStdString();
	string vision = this->vision_lineEdit->text().toStdString();

	if (auraLevel_string.size() == 0 || separateParts_string.size() == 0 || size.size() == 0 || vision.size() == 0)
	{
		QMessageBox::critical(this, "Wrong input", "Please provide all attributes for a turret");
		return;
	}
	int auraLevel, separateParts;

	try
	{
		auraLevel = stoi(this->auraLevel_lineEdit->text().toStdString());
		separateParts = stoi(this->separateParts_lineEdit->text().toStdString());
	}
	catch (exception& ex)
	{
		QMessageBox::critical(this, "Wrong input", "Aura level and numbr of separate parts must be integers");
		return;
	}

	
	try
	{
		this->service.update_turret_in_repository(location, size, auraLevel, separateParts, vision);
	}
	catch (Exceptions& exception)
	{
		QMessageBox::warning(this, QString::fromStdString(exception.get_type()), QString::fromStdString(exception.get_message()));
	}
	this->populate_list();
}

void GUI::delete_turret()
{
	int selected_index = this->get_selected_index();
	if (selected_index < 0)
	{
		QMessageBox::critical(this, "Wrong input", "Please select a turret to remove");
		return;
	}
	Turret turret = this->service.get_all_turrets()[selected_index];
	this->service.remove_turret_from_repository(turret.get_location());
	
	this->populate_list();
}

void GUI::next_turret()
{
	Turret current = this->service.next();
	this->current_turret->setText(QString::fromStdString(current.get_location()));
}

void GUI::save_turret()
{
	std::string current_location = this->current_turret->text().toStdString();

	if (current_location.size() == 0)
	{
		QMessageBox::information(this, "Oops", "You are currently not watching any turret");
		return;
	}

	try
	{
		this->service.activate_turret(current_location);
		this->populate_mylist();
		this->mylist_view->update_model();
	}
	catch (Exceptions& exception)
	{
		QMessageBox::warning(this, QString::fromStdString(exception.get_type()), QString::fromStdString(exception.get_message()));
	}
}

void GUI::open_mylist()
{
	this->service.open_file();
}

void GUI::filter_list()
{
	if (filter_size->text().toStdString().size() == 0 || filter_separateParts->text().toStdString().size() == 0)
	{
		QMessageBox::critical(this, "Wrong input", "Please provide the size and minimum number of parts of the turrets you want to see");
		return;
	}

	std::string size = this->filter_size->text().toStdString();
	try
	{
		int separateParts = stoi(this->filter_separateParts->text().toStdString());
		try
		{
			std::vector<Turret> filtered = this->service.filter_by_size_and_parts(size, separateParts);
			for (auto turret : filtered)
			{
				this->filtered_listWidget->addItem(QString::fromStdString(turret.turn_to_string()));
			}
		}
		catch (Exceptions& exception)
		{
			QMessageBox::information(this, "Oops", QString::fromStdString(exception.get_message()));
		}
	}
	catch(exception& ex)
	{
		QMessageBox::critical(this, "Wrong input", "Minimum number of separate parts must be an integer");
		return;
	}

}

void GUI::undo()
{
	try
	{
		this->service.undo();
		this->populate_list();
	}
	catch (Exceptions& exception)
	{
		QMessageBox::critical(this, QString::fromStdString(exception.get_type()), QString::fromStdString(exception.get_message()));
	}
}

void GUI::redo()
{
	try
	{
		this->service.redo();
		this->populate_list();
	}
	catch (Exceptions& exception)
	{
		QMessageBox::critical(this, QString::fromStdString(exception.get_type()), QString::fromStdString(exception.get_message()));
	}
}

void GUI::my_undo()
{
	try
	{
		this->service.MYundo();
		this->populate_mylist();
		this->mylist_view->update_model();
	}
	catch (Exceptions& exception)
	{
		QMessageBox::critical(this, QString::fromStdString(exception.get_type()), QString::fromStdString(exception.get_message()));
	}
}

void GUI::my_redo()
{
	try
	{
		this->service.MYredo();
		this->populate_mylist();
		this->mylist_view->update_model();
	}
	catch (Exceptions& exception)
	{
		QMessageBox::critical(this, QString::fromStdString(exception.get_type()), QString::fromStdString(exception.get_message()));
	}
}

void GUI::open_listView()
{
	this->mylist_view->show();
}


