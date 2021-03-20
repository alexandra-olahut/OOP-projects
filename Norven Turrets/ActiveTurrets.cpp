#include "ActiveTurrets.h"
#include "Exceptions.h"
// #include "DynamicVectorTemplate.h"
#include <string>
#include <fstream>
#include <Windows.h>

#define NUMBER_OF_LINES_UNTIL_TABLE_CONTENT 13
#define CELL_CONTENT_START_INDEX 4
#define NUMBER_OF_SPECIAL_CHARACTERS 9

using namespace std;


void ActiveTurrets::add(const Turret& turret)
{
	vector<Turret> active_turrets = this->load_file();
	
	for (auto active_turret : active_turrets)
		if (active_turret == turret)
			throw RepositoryException("This turret has already been activated\n");
	active_turrets.push_back(turret);
	
	this->save_file(active_turrets);
}

void ActiveTurrets::remove(const Turret& turret)
{
	vector<Turret> active_turrets = this->load_file();

	int position = search(turret);

	if (position == -1)
		throw MyListException("This turret was not saved");
	active_turrets.erase(active_turrets.begin() + position);

	this->save_file(active_turrets);
}

int ActiveTurrets::search(const Turret& turret)
{
	vector<Turret> active_turrets = this->load_file();

	std::vector<Turret>::iterator iterator_at_turret;
	iterator_at_turret = std::find(active_turrets.begin(), active_turrets.end(), turret);

	if (iterator_at_turret == active_turrets.end())
		return -1;

	// Get index of element from iterator
	int index = std::distance(active_turrets.begin(), iterator_at_turret);
	return index;
}

vector<Turret> ActiveTurrets::get_all()
{
	vector<Turret> active_turrets = this->load_file();
	return active_turrets;
}

void ActiveTurrets::set_location(std::string file_location)
{
	this->file_location = file_location;
}





std::vector<Turret> CSVmylist::load_file()
{
	std::vector<Turret> turrets;
	Turret turret;

	ifstream file{ this->file_location };
	while (file >> turret)
		turrets.push_back(turret);

	file.close();
	return turrets;
}

void CSVmylist::open_file()
{
	ShellExecuteA(NULL, NULL, "notepad.exe", this->file_location.c_str(), NULL, SW_SHOWNORMAL);
}

void CSVmylist::save_file(std::vector<Turret> turrets)
{
	ofstream file{ this->file_location };
	for (const auto& turret : turrets)
		file << turret << endl;
	file.close();
}





void HTMLmylist::save_file(std::vector<Turret> turrets)
{
	ofstream file{ this->file_location };
	
	file << "<!DOCTYPE html>\n<html>\n<head>\n";          //beginning of html document
	file << "<title>Activated Turrets</title>\n";         //title
	file << "</head>\n<body>\n<table border=\"1\"\n";     //table

	// table header
	file << "<tr>\n<td>Location</td>\n<td>Size</td>\n<td>Aura Level</td>\n<td>Separate Parts</td>\n<td>Vision</td>\n</tr>\n";

	// table content
	for (auto turret : turrets)
		file << turret.turn_to_html() << endl;

	//ending of html document
	file << "</table>\n</body>\n</html>";

	file.close();

}

std::vector<Turret> HTMLmylist::load_file()
{
	std::vector<Turret> active_turrets;
	
	ifstream file{ this->file_location };
	string line, header;
	string location, size, auraLevel, separateParts, vision;

	for (int i = 0; i <= NUMBER_OF_LINES_UNTIL_TABLE_CONTENT; i++)
		getline(file, line);


	getline(file, line);  // <tr>
	while (line == "<tr>")
	// we're inside a table row so we're reading a turret
	{
		getline(file, line);
		location = line.substr(CELL_CONTENT_START_INDEX, line.size() - NUMBER_OF_SPECIAL_CHARACTERS);
		getline(file, line);
		size = line.substr(CELL_CONTENT_START_INDEX, line.size() - NUMBER_OF_SPECIAL_CHARACTERS);
		getline(file, line);
		auraLevel = line.substr(CELL_CONTENT_START_INDEX, line.size() - NUMBER_OF_SPECIAL_CHARACTERS);
		getline(file, line);
		separateParts = line.substr(CELL_CONTENT_START_INDEX, line.size() - NUMBER_OF_SPECIAL_CHARACTERS);
		getline(file, line);
		vision = line.substr(CELL_CONTENT_START_INDEX, line.size() - NUMBER_OF_SPECIAL_CHARACTERS);

		Turret turret{ location, size, stoi(auraLevel), stoi(separateParts), vision };
		active_turrets.push_back(turret);

		getline(file, line);  //</tr>

		getline(file, line);  //<tr>
								// the last will be </table> ->stops the while
	}
	
	file.close();
	return active_turrets;
}

void HTMLmylist::open_file()
{
	ShellExecuteA(NULL, NULL, "chrome.exe", this->file_location.c_str(), NULL, SW_SHOWMAXIMIZED);
}
