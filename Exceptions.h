#pragma once
#include <exception>
#include <string>

//exception for stack and queue pop and top
class UnderflowException : public std::exception
{
protected:
	std::string message;

public:
	UnderflowException(const std::string& msg);
	virtual const char* what();
};

//exceptions that check if an arithmetic operation is valid
class ExpressionException : public std::exception
{
protected:
	std::string message;

public:
	ExpressionException();
	ExpressionException(std::string msg) : message(msg) {}
	virtual ~ExpressionException() {}
	virtual const char* what();
};

class OpenBracketException : public ExpressionException
{
public:
	const char* what();
};

class UnsupportedOperationException : public ExpressionException
{
public:
	const char* what();
};

class DivisionByZeroException : public ExpressionException
{
public:
	const char* what();
};

/*
error for () empty brackets
*/

