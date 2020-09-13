#pragma once
#include "StackSLL.h"
#include "QueueSLLA.h"
#include <string>

/*
Solves an arithmetic expression which may contain the operators +,-,*,/,^,(,) and multiple
digits operands.
*/
class ShuntingYardAlgorithm
{
public:
	//Constructors
	ShuntingYardAlgorithm();

	/*
	Checks if a character from the expression is an operator, but not a parantheses.
	IN: char
	OUT: true if its +,-,*,/,^  , false otherwise
	Throws:-
	*/
	static bool isOperator(const char c);

	/*
	Returns true if 'op1' has lower or same precedence as 'op2'
	This is the order of precedence from lowest to highest: +,-,*,/,^
	IN: char, char
	OUT: true if 'op2' has higher precedence
	Throws:-
	*/
	static bool hasPrecedence(const char op1, const char op2);

	/*
	Raises the number n at the power p (n^p) in logarithmic time.
	Returns the result.
	IN: int, int
	OUT: int - the result of n^p
	Throws:-
	*/
	static int powerOperation(int n, int p);

	/*
	A utility method to apply an operator 'op' on operands 'a' and 'b'
	IN: char, int, int
	OUT: int - the result of 'a op b'
	Throws: UnsupportedOperationException - if b is 0
	*/
	static int applyOperator(const char op, int a, int b);

	/*
	Transforms an arithmetic expression from infix form notation to postfix form (or Reverse Polish
	Notation). Its stored in a queue of strings. When its evaluated, we just pop strings and convert
	to numbers the operands.
	IN: string
	OUT: 
	Throws: exception - if the parantheses are not
	*/
	static QueueSLLA<std::string> infixToPostfix(std::string expression);

	/*
	Returns the result of the arithmetic expression (as an integer).
	IN: string
	OUT: integer
	Throws:-
	*/
	static int evaluate(std::string expression);

	/*
	Returns a string representing the postfix form of an arithmetic expression in infix form.
	IN: string
	OUT: string
	Throws: -
	*/
	static std::string showPostfixForm(std::string expression);
};