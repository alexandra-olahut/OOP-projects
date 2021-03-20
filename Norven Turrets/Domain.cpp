#include "Domain.h"

#include <string>
#include <vector>
#include <sstream>
#include <fstream>

using namespace std;

Turret::Turret()
{
	this->location = "";
	this->size = "";
	this->auraLevel = 0;
	this->separateParts = 0;
	this->vision = "";
}

Turret::Turret(const std::string& location, const std::string& size, int auraLevel, int separateParts, const std::string& vision)
{
	this->location = location;
	this->size = size;
	this->auraLevel = auraLevel;
	this->separateParts = separateParts;
	this->vision = vision;
}

std::string Turret::turn_to_string()
{
	return "Location: "+this->get_location() + ", " + "Size: "+this->get_size() + ", " + "Aura level: "+std::to_string(this->get_auraLevel()) + ", " + "Separate parts: "+std::to_string(this->get_separateParts()) + ", " + "Vision: "+this->get_vision();
}

bool Turret::operator==(const Turret& turret)
{
	return (this->location == turret.location);
}

bool Turret::is_identical(const Turret& turret)
{
	return (this->location == turret.location) || (this->size == turret.size) || (this->auraLevel == turret.auraLevel) || (this->separateParts == turret.separateParts) || (this->vision == turret.vision);
}




std::string Turret::turn_to_html()
{
	string html_format;
	html_format = "<tr>\n<td>"+this->location+"</td>\n<td>"+this->size+"</td>\n<td>"+ std::to_string(this->auraLevel) + "</td>\n<td>" + std::to_string(this->separateParts) + "</td>\n<td>" +this->vision + "</td>\n</tr>";
	return html_format;
}

void Turret::reset_turret()
{
	this->location = "";
	this->size = "";
	this->auraLevel = 0;
	this->separateParts = 0;
	this->vision = "";
}

std::istream& operator>>(std::istream& stream, Turret& turret)
{
	turret.reset_turret();

	std::string line{};
	getline(stream, line);

	// split the line in turret parameters using a stream
	vector <string> parameters;
	stringstream line_stream(line);
	string parameter;
	while (getline(line_stream, parameter, ','))
		parameters.push_back(parameter);

	if (parameters.size() == 0)
		return stream;
	
	turret.location = parameters[LOCATION_INDEX];
	turret.size = parameters[SIZE_INDEX];
	turret.auraLevel = stoi(parameters[AURALEVEL_INDEX]);
	turret.separateParts = stoi(parameters[SEPARATEPARTS_INDEX]);
	turret.vision = parameters[VISION_INDEX];

	return stream;
}

std::ostream& operator<<(std::ostream& stream, const Turret& turret)
{
	stream << turret.location << ',';
	stream << turret.size << ',';
	stream << turret.auraLevel << ',';
	stream << turret.separateParts << ',';
	stream << turret.vision;

	return stream;
}
