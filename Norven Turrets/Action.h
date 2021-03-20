#pragma once

#include "Repository.h"
#include "Mylist.h"
#include "Domain.h"

class Action
{
public:
	virtual void undo_action() = 0;
	virtual void redo_action() = 0;

	virtual ~Action() {}
};


class AddAction : public Action
{
private:
	Repository* repository;
	Turret turret;
public:
	AddAction(Repository* repository, const Turret& turret) :repository(repository), turret(turret) {}
	~AddAction() {}

	void undo_action() override;
	void redo_action() override;
};

class DeleteAction : public Action
{
private:
	Repository* repository;
	Turret turret;
public:
	DeleteAction(Repository* repository, const Turret& turret) :repository(repository), turret(turret) {}
	~DeleteAction() {}

	void undo_action() override;
	void redo_action() override;
};

class UpdateAction : public Action
{
private:
	Repository* repository;
	Turret old_turret, new_turret;
public:
	UpdateAction(Repository* repository, const Turret& old, const Turret& new_) : repository(repository), new_turret(new_), old_turret(old) {}
	~UpdateAction() {}

	void undo_action() override;
	void redo_action() override;
};



class SaveAction : public Action
{
private:
	MyList* mylist;
	Turret turret;
public:
	SaveAction(MyList* mylist, Turret turret) : mylist(mylist), turret(turret) {}
	~SaveAction() {}

	void undo_action() override;
	void redo_action() override;
};