#include "Service.h"

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


Service::~Service()
{
//	delete active_turrets;
}

void Service::set_file_location(string file_location)
{
	this->repository.set_file(file_location);
}

/*
void Service::set_mylist_location(std::string mylist_location)
{
	if (mylist_location == "memory")
	{
		this->active_turrets = new MemoryMyList{};
		return;
	}

	string extension = mylist_location.substr(mylist_location.size() - 4);
	
	if (extension == ".csv")
	{
		this->active_turrets = new CSVmylist{};
	}
	else if (extension == "html")
	{
		this->active_turrets = new HTMLmylist{};
	}
	else throw ServiceException(" Invalid file for my list\n");

	this->active_turrets.set_location(mylist_location);
}
*/

void Service::open_file()
{
	this->active_turrets.open_file();
}



vector<Turret> Service::get_all_turrets() const
{
	return this->repository.get_all();
}


void Service::add_turret_to_repository(const std::string& location, const std::string& size, int auraLevel, int separateParts, const std::string& vision)
{
	Turret new_turret{ location, size, auraLevel, separateParts, vision };
	this->validator.validate(new_turret);
	this->repository.add_turret(new_turret);

	this->undo_stack.push_back(make_unique<AddAction>(&this->repository, new_turret));
	this->redo_stack.clear();
}

void Service::update_turret_in_repository(const std::string& location, const std::string& size, int auraLevel, int separateParts, const std::string& vision)
{
	Turret old_turret = this->repository.get_turret_by_location(location);
	Turret updated_turret{ location, size, auraLevel, separateParts, vision };
	this->validator.validate(updated_turret);
	this->repository.update_turret(updated_turret);

	this->undo_stack.push_back(make_unique<UpdateAction>(&this->repository, old_turret, updated_turret));
	this->redo_stack.clear();
}

void Service::remove_turret_from_repository(const std::string& location)
{
	Turret deleted_turret = this->repository.get_turret_by_location(location);
	this->repository.remove_turret(location);

	this->undo_stack.push_back(make_unique<DeleteAction>(&this->repository, deleted_turret));
	this->redo_stack.clear();
}



vector<Turret> Service::filter_by_size_and_parts(const std::string& given_size, const int minimum_parts)
{
	vector<Turret> all_turrets = this->repository.get_all();
	vector<Turret> filtered_list(all_turrets.size());

	auto it = std::copy_if(all_turrets.begin(), all_turrets.end(), filtered_list.begin(), [given_size, minimum_parts](Turret turret) {return (turret.get_size() == given_size && turret.get_separateParts() >= minimum_parts); });
	filtered_list.resize(std::distance(filtered_list.begin(), it));  // shrink container to new size

	if (filtered_list.size() == 0)
		throw ServiceException("No matching turrets\n");

	return filtered_list;
}



Turret Service::next()
{
	Turret current_turret = this->repository.get_current_turret();
	this->repository.next_turret();
	return current_turret;
}



void Service::activate_turret(const std::string& location)
{
	Turret turret_by_location{ location, "", 0, 0, "" };
	int position_in_repository = this->repository.get_position_of_turret(turret_by_location);
	if (position_in_repository == -1)
		throw ServiceException("Can't activate: there is no turret with this location\n");
	
	Turret saved_turret = this->repository.get_all()[position_in_repository];
	this->active_turrets.add(saved_turret);

	this->MYundo_stack.push_back(make_unique<SaveAction>(&this->active_turrets, saved_turret));
	this->MYredo_stack.clear();
}

vector<Turret> Service::get_all_activeTurrets()
{
	return this->active_turrets.get_all();
}


void Service::undo()
{
	if (this->undo_stack.empty())
		throw UndoRedoException("No more undo's");
	auto action = move(this->undo_stack.back());
	
	this->undo_stack.pop_back();
	action->undo_action();
	this->redo_stack.push_back(move(action));
}

void Service::redo()
{
	if (this->redo_stack.empty())
		throw UndoRedoException("No more redo's");
	auto action = move(this->redo_stack.back());

	this->redo_stack.pop_back();
	action->redo_action();
	this->undo_stack.push_back(move(action));
}

void Service::MYundo()
{
	if (this->MYundo_stack.empty())
		throw UndoRedoException("No more undo's here");
	auto action = move(this->MYundo_stack.back());

	this->MYundo_stack.pop_back();
	action->undo_action();
	this->MYredo_stack.push_back(move(action));
}

void Service::MYredo()
{
	if (this->MYredo_stack.empty())
		throw UndoRedoException("No more redo's here");
	auto action = move(this->MYredo_stack.back());

	this->MYredo_stack.pop_back();
	action->redo_action();
	this->MYundo_stack.push_back(move(action));
}
