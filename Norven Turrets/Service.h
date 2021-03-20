#pragma once

#include "Exceptions.h"
#include "Repository.h"
#include "ActiveTurrets.h"
#include "Action.h"

#include <vector>
#include <memory>

class Service
{
private:
	TurretValidator& validator;

	Repository& repository;
	MyList& active_turrets;

	std::vector<std::unique_ptr<Action>> undo_stack;
	std::vector<std::unique_ptr<Action>> redo_stack;

	std::vector<std::unique_ptr<Action>> MYundo_stack;
	std::vector<std::unique_ptr<Action>> MYredo_stack;


public:
	Service(Repository& new_repository, TurretValidator& validator, MyList& mylist) : repository{ new_repository }, validator{ validator }, active_turrets{ mylist } {}
	~Service();


	// Sets the file in which the data is kept
	void set_file_location(std::string file_location);
	// Sets location to keep the saved data
//	void set_mylist_location(std::string mylist_location);

	void open_file();




	//						     REPOSITORY

	// Returns a vector of all the turrets
	std::vector<Turret> get_all_turrets() const;


	/*
		Adds a turret to the repository
			Parameters: properties of a turret: location, size, aura level, separate parts and vision
			Returns: (turret is added)
	*/
	void add_turret_to_repository(const std::string& location, const std::string& size, int auraLevel, int separateParts, const std::string& vision);

	/*
		Updates a turret in the repository based on new data
			Parameters: the new properties with which we update
			Returns: (turret is updated)
	*/
	void update_turret_in_repository(const std::string& location, const std::string& size, int auraLevel, int separateParts, const std::string& vision);

	/*
		Removed a turret from repository
			Parameter: position from which we remove the turret
			Returns: (turret is removed)
	*/
	void remove_turret_from_repository(const std::string& location);




	// Returns the turrets with a given size and minimum number of parts
	std::vector<Turret> filter_by_size_and_parts(const std::string& given_size, const int minimum_parts);


	//	Returns the current turret in repository and jumps to the next
	// (if it reaches the end it goes back to the beginning
	Turret next();




	//				     ACTIVE TURRETS COLLECTION


	/*
		Adds a turret to the collection of activated turrets
			Parameters: the turret to activate
			Returns: (turret is activated)
	*/
	void activate_turret(const std::string& location);


	// Return a dynamic vector of all turrets saved in acive turrets
	std::vector<Turret> get_all_activeTurrets();



	void undo();
	void redo();

	void MYundo();
	void MYredo();
};
