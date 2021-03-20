#pragma once
#include "Repository.h"

#include <vector>
#include <iterator>
#include <string>

class FileRepository : public Repository
{
private:
	
	std::string file_name;
	int index;

public:
//	FileRepository(std::string file_name) : file_name(file_name) {}

	// adds a new turret in the file
	void add_turret(const Turret& turret);

	// updates a turret from the file
	void update_turret(const Turret& turret);

	// removes a turret from the file
	void remove_turret(const std::string& location);


	
	// Searches a turret in the file
	// Returns its position / -1 (if not found)
	int get_position_of_turret(const Turret& turret);

	Turret get_turret_by_location(std::string location);

	// Returns a vector of all turrets in the file
	std::vector<Turret> get_all();
	



	// Returns the current turret displayed
	Turret get_current_turret();

	// Jumps to the next turret in the repository 
	void next_turret();


	// Function that sets the path for the file to save the data in
	void set_file(std::string file_name);


private:

	// Function tha reads all data from the file and returns a vector of the turrets
	std::vector<Turret> load_file();
	// Function that writes all the turrets from given vector into the file
	void save_file(std::vector<Turret> turrets);

	// Searches a turret in the file
	// Returns its position / -1 (if not found)
// same with get_position_of_turret but doesn't have to load the entire file
	int search_turret(std::vector<Turret> turrets, const Turret& turret);

};