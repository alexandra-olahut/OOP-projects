#include "Domain.h"

#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

std::ostream& operator<<(std::ostream& os, const User& user)
{
	os << user.name << ',' << user.type;
	return os;
}

std::istream& operator>>(std::istream& is, User& user)
{
	user.resetUser();
	std::string line{};
	getline(is, line);

	vector<string> parameters;
	stringstream lineStream(line);
	string param;
	while (getline(lineStream, param, ','))
		parameters.push_back(param);

	if (parameters.size() == 0)
		return is;

	user.name = parameters[0];
	user.type = parameters[1];

	return is;
}

std::ostream& operator<<(std::ostream& os, const Issue& issue)
{
	os << issue.description << ',';
	os << issue.status << ',';
	os << issue.reporter << ',';
	os << issue.solver;
	return os;
}

std::istream& operator>>(std::istream& is, Issue& issue)
{
	issue.resetIssue();
	std::string line{};
	getline(is, line);

	vector<string> parameters;
	stringstream lineStream(line);
	string param;
	while (getline(lineStream, param, ','))
		parameters.push_back(param);

	if (parameters.size() == 0)
		return is;

	issue.description = parameters[0];
	issue.status = parameters[1];
	issue.reporter = parameters[2];
	issue.solver = parameters[3];

	return is;
}
