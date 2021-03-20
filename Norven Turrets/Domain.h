#pragma once
#include <iostream>

#define LOCATION_INDEX 0
#define SIZE_INDEX 1
#define AURALEVEL_INDEX 2
#define SEPARATEPARTS_INDEX 3
#define VISION_INDEX 4


class Turret
{
private:
	std::string location;
	std::string size;
	int auraLevel;
	int separateParts;
	std::string vision;

public:
	// Default constructor for a Norven Turret
	Turret();

	// Constructor with parameters
	//    Parameters: location, size, aura level, separate parts and vision
	Turret(const std::string& location, const std::string& size, int auraLevel, int separateParts, const std::string& vision);

	// Getters for properties
	std::string get_location() const { return location; }
	std::string get_size() const { return size; }
	int get_auraLevel() const { return auraLevel; }
	int get_separateParts() const { return separateParts; }
	std::string get_vision() const { return vision; }

	// Turns a turret into string form in order to print it
	std::string turn_to_string();

	// == operator checks if two turrets have the same location (id)
	bool operator==(const Turret& turret);
	
	// function that checks if two turrets are identica by all fields
	bool is_identical(const Turret& turret);


	// function that turns a turret into format suitable for html file writing
	std::string turn_to_html();


	// reset a turret to default one
	void reset_turret();

	// extraction operator
	friend std::istream& operator>>(std::istream& stream, Turret& turret);

	// insertion operator
	friend std::ostream& operator<<(std::ostream& stream, const Turret& turret);
};
	