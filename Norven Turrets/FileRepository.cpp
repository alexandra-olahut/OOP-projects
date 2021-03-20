#include "FileRepository.h"

#include <string>
#include <fstream>
using namespace std;

void FileRepository::set_file(std::string file_name)
{
	this->file_name = file_name;
}

std::vector<Turret> FileRepository::load_file()
{
	std::vector<Turret> turrets;
	Turret turret;

	ifstream file{ this->file_name };
	while (file >> turret)
		turrets.push_back(turret);

	file.close();
	return turrets;
}

void FileRepository::save_file(std::vector<Turret> turrets)
{
	ofstream file{ this->file_name };
	for (const auto& turret : turrets)
		file << turret<<endl;
	file.close();
}





void FileRepository::add_turret(const Turret& turret)
{
	vector<Turret> turrets = this->load_file();

	int index = this->search_turret(turrets, turret);
	if (index != -1)
		throw RepositoryException("Location occupied by another turret\n");
	turrets.push_back(turret);

	this->save_file(turrets);
}

void FileRepository::update_turret(const Turret& turret)
{
	vector<Turret> turrets = this->load_file();

	int index = this->search_turret(turrets, turret);
	if (index == -1)
		throw RepositoryException("There is no turret in this location\n");
	turrets[index] = turret;

	this->save_file(turrets);
}

void FileRepository::remove_turret(const std::string& location)
{
	vector<Turret> turrets = this->load_file();

	Turret turret_location{ location, "", 0, 0, "" };
	int position = this->search_turret(turrets, turret_location);
	if (position == -1)
		throw RepositoryException("There is no turret in this location\n");
	turrets.erase(turrets.begin() + position);

	this->save_file(turrets);
}




int FileRepository::get_position_of_turret(const Turret& turret)
{
	std::vector<Turret> turrets = this->load_file();
	std::vector<Turret>::iterator iterator_at_turret;
	iterator_at_turret = std::find(turrets.begin(), turrets.end(), turret);

	if (iterator_at_turret == turrets.end())
		return -1;

	// Get index of element from iterator
	auto index = std::distance(turrets.begin(), iterator_at_turret);
	return index;
}

Turret FileRepository::get_turret_by_location(std::string location)
{
	Turret turret{ location, "", 0, 0, "" };
	int position = get_position_of_turret(turret);
	return get_all()[position];
}




std::vector<Turret> FileRepository::get_all()
{
	vector<Turret> turrets = this->load_file();
	return turrets;
}



Turret FileRepository::get_current_turret()
{
	vector<Turret> turrets = this->load_file();
	return turrets[this->index];
}

void FileRepository::next_turret()
{
	this->index++;
	if (this->index == this->get_all().size())
		this->index = 0;
}




int FileRepository::search_turret(vector<Turret> turrets, const Turret& turret)
{
	std::vector<Turret>::iterator iterator_at_turret;
	iterator_at_turret = std::find(turrets.begin(), turrets.end(), turret);

	if (iterator_at_turret == turrets.end())
		return -1;

	// Get index of element from iterator
	auto index = std::distance(turrets.begin(), iterator_at_turret);
	return index;
}
