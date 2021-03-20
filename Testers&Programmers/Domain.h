#pragma once

#include <string>

class User
{
private:
	std::string name;
	std::string type;  //tester/programmer

public:
	std::string getName() { return name; }
	std::string getType() { return type; }

	void resetUser() { name = ""; type = ""; }
	friend std::ostream& operator<<(std::ostream& os, const User& user);
	friend std::istream& operator>>(std::istream& is, User& user);
};


class Issue
{
private:
	std::string description;
	std::string status; //open or closed
	std::string reporter;
	std::string solver;

public:
	Issue() {}
	Issue(std::string d, std::string st, std::string r, std::string so) : description(d), status(st), reporter(r), solver(so) {}

	std::string getDescription() { return description; }
	std::string getStatus() { return status; }
	std::string getReporter() { return reporter; }
	std::string getSolver() { return solver; }

	void setStatus(std::string status) { this->status = status; }
	void setSolver(std::string solver) { this->solver = solver; }
	void setReporter(std::string rep) { this->reporter = rep; }

	void resetIssue() { description = ""; status = ""; reporter = ""; solver = ""; }
	friend std::ostream& operator<<(std::ostream& os, const Issue& issue);
	friend std::istream& operator>>(std::istream& is, Issue& issue);

	bool operator==(const Issue& other) { return this->description == other.description; }
	std::string toString() {return description+" | "+status+" | "+reporter + " | " +
	solver;}
};