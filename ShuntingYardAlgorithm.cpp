#include "ShuntingYardAlgorithm.h"
#include <iostream>

using namespace std;

ShuntingYardAlgorithm::ShuntingYardAlgorithm() {}

bool ShuntingYardAlgorithm::isOperator(const char c)
{
	if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^')
		return true;
	return false;
}

bool ShuntingYardAlgorithm::hasPrecedence(const char op1, const char op2)
{
	if (op2 == '(' || op2 == ')')
		return false;

	if (op1 == '^' && op2 == '^')
		return false;

	if (op1 == '^' && (op2 == '*' || op2 == '/' || op2 == '+' || op2 == '-'))
		return false;

	if((op1 == '*' || op1 == '/') && (op2 == '+' || op2 == '-'))
		return false;

	return true;
}

int ShuntingYardAlgorithm::powerOperation(int n, int p)
{
	//divide result by 1 if p is negative
	if (p == 0)
		return 1;
	if (p == 1)
		return n;
	if (p % 2 == 0)
		return powerOperation( n * n, p / 2 );
	//no need for else statement, 'return' stops
	//the function
	return powerOperation(n  * n, p / 2) * n; //if power is odd 
}

int ShuntingYardAlgorithm::applyOperator(const char op, int a, int b)
{
	switch (op)
	{
	case '+':
		return a + b;

	case '-':
		return a - b;

	case '*':
		return a * b;

	case '/':
		if (b == 0)
			throw DivisionByZeroException();
		return a / b;

	case '^':
		return powerOperation(a, b);

	default:
		throw UnsupportedOperationException(); //inexistent operation
	}
}

QueueSLLA<string> ShuntingYardAlgorithm::infixToPostfix(std::string expression)
{
	StackSLL<string> operationsStack;
	QueueSLLA<string> postfixForm;
	string number = "";

	for (unsigned i = 0; i < expression.size(); i++)
	{
		string currentToken = ""; //can be operand or operator
		currentToken = expression[i];
		//Skip blank spaces
		if (currentToken == " ")
			continue;

		if (currentToken[0] >= 48 and currentToken[0] <= 57)
		{
			number += currentToken; //adding digits as we identify them
		}
		else
		{
			//we found an operator, so there was a number before which must be added
			//we check if its empty in case of 2 consecutive operators "(2+3)-4"
			if (number != "")
				postfixForm.push(number);
			number = "";

			//is operator
			if (currentToken == "(")
				operationsStack.push(currentToken);
			else if (currentToken == ")")
			{
				while (operationsStack.top() != "(")
					postfixForm.push((operationsStack.pop())); //remove top from stack and add it to queue
				operationsStack.pop(); //remove the open bracket
			}
			else if (isOperator(currentToken[0]))
			{
				// While top of 'operationsStack' has same or greater precedence to current
				// token, which is an operator. Take the operator from the top of the stack
				// and add it to the queue
				while (!operationsStack.isEmpty() && hasPrecedence(currentToken[0], operationsStack.top()[0]))
					postfixForm.push((operationsStack.pop()));

				operationsStack.push(currentToken); //the current operator "replaces" those with higher 
				//precedence at the top of the stack
			}
			else
				throw UnsupportedOperationException();//inexistent operator
		}
	}

	//if it ends with closed bracket no need to push, else we enter the 'if' 
	//2+3 , number = "3"
	//(2+3), number = ""
	if (number != "")
		postfixForm.push(number);

	// The expression has been parsed. Now there can be remaining operators in the stack
	while (!operationsStack.isEmpty())
		postfixForm.push((operationsStack.pop()));

	return postfixForm;
}

int ShuntingYardAlgorithm::evaluate(std::string expression)
{
	// + ^ 2 3 * 44 ^ 2 12 -> each element is a string
	//exception - there can be open parantheses
	QueueSLLA<string> postfixForm = infixToPostfix(expression);
	StackSLL<int> resultStack;

	while (!postfixForm.isEmpty())
	{
		string currentElement = postfixForm.pop();

		if (currentElement == "(")
			throw OpenBracketException();

		//either is number or operator, other characters errors are throwed in infixToPostfix function
		if (!isOperator(currentElement[0]))
		{
			int number = stoi(currentElement);
			resultStack.push(number);
		}
		else
		{
			int number1;
			int number2;

			number2 = resultStack.pop();
			number1 = resultStack.pop();

			//in input expression we cannot have negative numbers -> currentElement[0] is always operator
			resultStack.push(applyOperator(currentElement[0], number1, number2));
		}
	}

	return resultStack.top();
}

string ShuntingYardAlgorithm::showPostfixForm(std::string expression)
{
	QueueSLLA<string> postfixForm = infixToPostfix(expression);
	string result = "";
	while (!postfixForm.isEmpty())
	{
		result += postfixForm.pop();
	}
	return result;
}


