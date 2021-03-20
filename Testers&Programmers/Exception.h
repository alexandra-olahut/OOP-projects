#pragma once

#include <string>

class Exceptions
{
private:
	std::string message;

public:
	Exceptions(std::string msg) : message(msg) {}
	std::string get_message() const { return message; }
};
