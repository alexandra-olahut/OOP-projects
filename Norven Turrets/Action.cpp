#include "Action.h"

void AddAction::undo_action()
{
	this->repository->remove_turret(turret.get_location());
}

void AddAction::redo_action()
{
	this->repository->add_turret(turret);
}

void DeleteAction::undo_action()
{
	this->repository->add_turret(turret);
}

void DeleteAction::redo_action()
{
	this->repository->remove_turret(turret.get_location());
}

void UpdateAction::undo_action()
{
	this->repository->update_turret(old_turret);
}

void UpdateAction::redo_action()
{
	this->repository->update_turret(new_turret);
}

void SaveAction::undo_action()
{
	this->mylist->remove(this->turret);
}

void SaveAction::redo_action()
{
	this->mylist->add(this->turret);
}
