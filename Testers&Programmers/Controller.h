#pragma once

#include "Domain.h"
#include "Observer.h"

class Controller : public Subject
{
private:
	std::vector<User> users;
	std::vector<Issue> issues;

	std::string userFile;
	std::string issueFile;

public:
	Controller() {}
	Controller(std::string file1, std::string file2) : userFile(file1), issueFile(file2) {}
	~Controller() {}

	std::vector<User> getUsers();
	std::vector<Issue> getIssues();
	std::vector<Issue> getIssuesSorted();

	Issue searchIssue(std::string description);
	void removeIssue(Issue issue);
	void resolveIssue(Issue issue, std::string user);
	void addIssue(std::string description, std::string user);

private:
	std::vector<User> load_users();
	std::vector<Issue> load_issues();

	void save_users(std::vector<User> users);
	void save_issues(std::vector<Issue> issues);
};