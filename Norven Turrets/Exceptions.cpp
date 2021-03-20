#include "Exceptions.h"
#include <string>

using namespace std;

void TurretValidator::validate(const Turret& turret)
{
	string errors;
	if (turret.get_auraLevel() < 0)
		errors += string("The turret's aura level can't be less than 0!\n");
	if (turret.get_separateParts() < 0)
		errors += string("The quantity of separate parts can't be less than 0!\n");

	if (errors.size() > 0)
		throw ValidationException(errors);
}



std::string ValidationException::get_message() const
{
	string full_message;
	//full_message += string("   ! Validation error: \n");
	full_message += this->message;
	return full_message;
}

std::string RepositoryException::get_message() const
{
	string full_message;
	//full_message += string("   ! Repository error: \n");
	full_message += this->message;
	return full_message;
}

std::string ServiceException::get_message() const
{
	string full_message;
	//full_message += string("   ! Service error: \n");
	full_message += this->message;
	return full_message;
}

std::string UIException::get_message() const
{
	string full_message;
	//full_message += string("   ! Input error: \n");
	full_message += this->message;
	return full_message;
}

std::string UndoRedoException::get_message() const
{
	return this->message;
}
