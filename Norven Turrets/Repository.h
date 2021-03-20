#pragma once 

#include <vector>
#include <string>

#include "Domain.h"
#include "Exceptions.h"

class Repository
{

public:

	/*
		Adds a turret in the repository
			Parameter: turret - the new turret
			Return: - (the turret is added to the repository)
		Throws exception if turret with same location exists
	*/
	virtual void add_turret(const Turret& turret) = 0;

	/*
		Updates a turret with given new fields
			Parameter: turret - with the new fields
			Return: - (the turret is updated)
		Throws exception if the element to update does not exists
	*/
	virtual void update_turret(const Turret& turret) = 0;

	/*
		Deletes a turret from the repository
			Parameter: position to delete
			Return: - (the turret is removed)
		Throws exception if position is not in repository
	*/
	virtual void remove_turret(const std::string& location) = 0;



	// Return the position of a turret
	virtual int get_position_of_turret(const Turret& turret) = 0;

	// Returns the turret at a given location
	virtual Turret get_turret_by_location(std::string location) = 0;

	//	Returns the vector of all turrets
	virtual std::vector<Turret> get_all() = 0;




	// Returns the current turret displayed
	virtual Turret get_current_turret() = 0;

	// Jumps to the next turret in the repository 
	virtual void next_turret() = 0;


	
	virtual void set_file(std::string file_name) = 0;
};