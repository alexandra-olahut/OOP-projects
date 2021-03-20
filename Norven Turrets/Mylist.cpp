#include "Mylist.h"
#include "Exceptions.h"

void MemoryMyList::add(const Turret& turret)
{
	for (auto active_turret : active_turrets)
		if (active_turret == turret)
			throw RepositoryException("This turret has already been activated\n");
	active_turrets.push_back(turret);
}

void MemoryMyList::remove(const Turret& turret)
{
	int position = search(turret);

	if (position == -1)
		throw MyListException("This turret was not saved");
	this->active_turrets.erase(this->active_turrets.begin() + position);
}

int MemoryMyList::search(const Turret& turret)
{
	std::vector<Turret>::iterator iterator_at_turret;
	iterator_at_turret = std::find(this->active_turrets.begin(), this->active_turrets.end(), turret);

	if (iterator_at_turret == this->active_turrets.end())
		return -1;

	// Get index of element from iterator
	int index = std::distance(this->active_turrets.begin(), iterator_at_turret);
	return index;
}
