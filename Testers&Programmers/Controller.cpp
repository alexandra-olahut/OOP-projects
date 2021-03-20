#include "Controller.h"
#include "Exception.h"
#include <fstream>

using namespace std;

std::vector<User> Controller::getUsers()
{
	std::vector<User> users = this->load_users();
	return users;
}

std::vector<Issue> Controller::getIssues()
{
	std::vector<Issue> issues = this->load_issues();
	return issues;
}

std::vector<Issue> Controller::getIssuesSorted()
{
	std::vector<Issue> issues = this->load_issues();

	sort(issues.begin(), issues.end(), [](Issue a, Issue b) {
		if (a.getStatus() > b.getStatus())
			return true;
		else if (a.getStatus() == b.getStatus())
			return a.getDescription() < b.getDescription();
		return false; });

	return issues;
}

Issue Controller::searchIssue(std::string description)
{
	issues = this->load_issues();
	for (auto issue : issues)
		if (issue.getDescription() == description)
			return issue;
}

void Controller::removeIssue(Issue issue)
{
	issues = this->load_issues();
	auto it = std::find(issues.begin(), issues.end(), issue);
	if (it != issues.end())
		issues.erase(it);

	this->save_issues(issues);
	this->notify();
}

void Controller::resolveIssue(Issue issue, std::string user)
{
	std::vector<Issue> issues = this->load_issues();
	for(auto& i : issues)
		if (i == issue)
		{
			i.setStatus("closed");
			i.setSolver(user);
		}
	this->save_issues(issues);
	this->notify();
}

void Controller::addIssue(std::string description, std::string user)
{
	std::vector<Issue> issues = this->load_issues();

	for (auto is : issues)
		if (is.getDescription() == description)
			throw Exceptions("This issue has already been reported");

	Issue issue{ description, "open", user, "-" };
	issues.push_back(issue);
	this->save_issues(issues);

	this->notify();
}

std::vector<User> Controller::load_users()
{
	std::vector<User> users;
	User user;

	ifstream file{ this->userFile };
	while (file >> user)
		users.push_back(user);

	file.close();
	return users;
}

std::vector<Issue> Controller::load_issues()
{
	std::vector<Issue> issues;
	Issue issue;

	ifstream file{ this->issueFile };
	while (file >> issue)
		issues.push_back(issue);

	file.close();
	return issues;
}

void Controller::save_users(std::vector<User> users)
{
	ofstream file{ this->userFile };
	for (const auto& user : users)
		file << user << endl;
	file.close();
}

void Controller::save_issues(std::vector<Issue> issues)
{
	ofstream file{ this->issueFile };
	for (const auto& issue : issues)
		file << issue << endl;
	file.close();
}
