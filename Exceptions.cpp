#include "Exceptions.h"
using namespace std;

UnderflowException::UnderflowException(const std::string & msg) : message(msg)
{
}

const char * UnderflowException::what()
{
	return this->message.c_str();
}

const char * UnsupportedOperationException::what()
{
	return "This operator does not exist!";
}

const char * OpenBracketException::what()
{
	return "Too many open brackets!";
}

ExpressionException::ExpressionException()
{
}

const char * ExpressionException::what()
{
	return this->message.c_str();
}

const char * DivisionByZeroException::what()
{
	return "Cannot divide by 0!";
}
