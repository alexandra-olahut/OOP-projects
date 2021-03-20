#pragma once
#include "Repository.h"

#include <vector>
#include <iterator>

class MemoryRepository: public Repository
{
private:
	std::vector<Turret> turrets;
	int index = 0;

public:
	
	// adds a new turret in the vector
	void add_turret(const Turret& turret);

	// updates a turret from the vector
	void update_turret(const Turret& turret);

	// removes a turret from the vector
	void remove_turret(const std::string& location);


	int get_position_of_turret(const Turret& turret);
	Turret get_turret_by_location(std::string location);
	std::vector<Turret> get_all() { return turrets; }
	



	// Returns the current turret displayed
	Turret get_current_turret();

	// Jumps to the next turret in the repository 
	void next_turret();


	void set_file(std::string file) {};
};