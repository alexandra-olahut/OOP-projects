#pragma once
#include "Domain.h"
#include "Mylist.h"
#include <vector>

// Abstract class
class ActiveTurrets : public MyList
{
protected:
	std::string file_location;

public:
	/*
		Adds a new turret to the wall
			Parameter: the new turret
	*/
	void add(const Turret& turret);
	void remove(const Turret& turret);

	int search(const Turret& turret);

	// Returns all activated turrets kept in this collection
	std::vector<Turret> get_all();


	void set_location(std::string file_location);


	virtual void save_file(std::vector<Turret> turrets) = 0;
	virtual std::vector<Turret> load_file() = 0;

	virtual void open_file() = 0;


	virtual ~ActiveTurrets() {};
};


class CSVmylist : public ActiveTurrets
{
public:
	CSVmylist(std::string file) { this->file_location = file; }

	void save_file(std::vector<Turret> turrets) override;
	std::vector<Turret> load_file() override;

	void open_file() override;

	~CSVmylist() {};
};

class HTMLmylist : public ActiveTurrets
{
public:
	HTMLmylist(std::string file) { this->file_location = file; }

	void save_file(std::vector<Turret> turrets) override;
	std::vector<Turret> load_file() override;

	void open_file() override;

	~HTMLmylist() {};
};


