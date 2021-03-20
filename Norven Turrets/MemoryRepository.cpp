#include "MemoryRepository.h"
#include <iostream>

using namespace std;


void MemoryRepository::add_turret(const Turret& turret)
{
	int index = this->get_position_of_turret(turret);
	if (index != -1)
		throw RepositoryException("A turret already exists in this location\n");
	this->turrets.push_back(turret);
}

void MemoryRepository::update_turret(const Turret& turret)
{
	int index = this->get_position_of_turret(turret);	
	if (index == -1)
		throw RepositoryException("There is no turret in this location\n");
	this->turrets[index] = turret;
}

void MemoryRepository::remove_turret(const std::string& location)
{
	Turret turret_location{ location, "", 0, 0, "" };
	int position = this->get_position_of_turret(turret_location);
	if (position == -1)
		throw RepositoryException("There is no turret in this location\n");
	this->turrets.erase(this->turrets.begin() + position);
}




int MemoryRepository::get_position_of_turret(const Turret& turret)
{
	std::vector<Turret>::iterator iterator_at_turret;
	iterator_at_turret = std::find(this->turrets.begin(), this->turrets.end(), turret);

	if (iterator_at_turret == this->turrets.end())
		return -1;
	
	// Get index of element from iterator
	int index = std::distance(this->turrets.begin(), iterator_at_turret);
	return index;
}

Turret MemoryRepository::get_turret_by_location(std::string location)
{
	Turret turret{ location, "", 0, 0, "" };
	int position = get_position_of_turret(turret);
	return get_all()[position];
}






Turret MemoryRepository::get_current_turret()
{
	return this->turrets[this->index];
}

void MemoryRepository::next_turret()
{
	this->index++;
	if (this->index == this->get_all().size())
		this->index = 0;
}
