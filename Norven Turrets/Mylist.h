#pragma once

#include "Domain.h"

#include <vector>

class MyList
{
public:

	virtual void add(const Turret& turret) = 0;
	virtual void remove(const Turret& turret) = 0;
//	virtual void update(const Turret& turret) = 0;
	
	virtual int search(const Turret& turret) = 0;
	virtual std::vector<Turret> get_all() = 0;


	virtual void set_location(std::string file_location) = 0;
	virtual void open_file() = 0;
};


class MemoryMyList :public MyList
{
private:
	std::vector<Turret> active_turrets;

public:

	void add(const Turret& turret);
	void remove(const Turret& turret);
//	void update(const Turret& turret);

	int search(const Turret& turret);
	std::vector<Turret> get_all() { return active_turrets; };

	void set_location(std::string file_location) {};
	void open_file() {};
};