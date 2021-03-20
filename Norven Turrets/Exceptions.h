#pragma once

#include "Domain.h"

///      VALIDATOR

class TurretValidator
{
public:
	static void validate(const Turret& turret);
};


///      EXCEPTION

class Exceptions
{
public:
	virtual std::string get_message() const = 0;
	virtual std::string get_type() const = 0;
};


class ValidationException : public Exceptions
{
private:
	std::string message;

public:
	ValidationException(std::string _message) { this->message = _message; }
	std::string get_message() const;
	std::string get_type() const { return "Validation error"; }
};


class RepositoryException : public Exceptions
{
private:
	std::string message;

public:
	RepositoryException(std::string _message) { this->message = _message; }
	std::string get_message() const;
	std::string get_type() const { return "Repository error"; }
};


class ServiceException : public Exceptions
{
private:
	std::string message;

public:
	ServiceException(std::string _message) { this->message = _message; }
	std::string get_message() const;
	std::string get_type() const { return "Service error"; }
};


class UIException : public Exceptions
{
private:
	std::string message;

public:
	UIException(std::string _message) { this->message = _message; }
	std::string get_message() const;
};


class UndoRedoException : public Exceptions
{
private:
	std::string message;

public:
	UndoRedoException(std::string message) { this->message = message; }
	std::string get_message() const;
	std::string get_type() const { return "Undo error"; }
};

class MyListException : public Exceptions
{
private:
	std::string message;

public:
	MyListException(std::string message) { this->message = message; }
	std::string get_message() const { return message; }
	std::string get_type() const { return "Undo error"; }
};