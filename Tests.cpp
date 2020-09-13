#include "Tests.h"
#include <iostream>
using namespace std;

void Tests::testNode()
{
	Node<int> n;
	Node<int> n2;

	//test getters and setters
	n.setInfo(4);
	n.setNext(&n2);
	assert(n.getInfo() == 4);
	assert(n.getNext() == &n2);

	//what happens if the next of a node is not assigned/is NULL 
	//(should be some values indicating errors)
	Node<int> n3;
	assert(n3.getNext()->getInfo() == 0); //default constructor for int is 0
	assert(n3.getNext()->getNext() == nullptr);
}

void Tests::testStackSLL()
{
	StackSLL<int> st;
	bool errored = false;

	//is empty and push
	assert(st.isEmpty() == true);
	st.push(1);
	assert(st.isEmpty() == false);

	//pop
	int temp = st.pop();
	assert(temp == 1);
	//we pop an empty stack
	try
	{
		st.pop();
	}
	catch (UnderflowException&)
	{
		errored = true;
	}
	assert(errored == true);

	//top
	errored = false;
	try
	{
		st.top(); //the stack is empty, we cannot top
	}
	catch (UnderflowException&)
	{
		errored = true;
	}
	assert(errored == true);

	//check the LIFO property
	st.push(2);
	st.push(3);
	assert(st.top() == 3);
}

void Tests::testQueueSLLA()
{
	QueueSLLA<int> q;
	bool errored = false;

	//is empty and push
	assert(q.isEmpty() == true);
	q.push(1);
	assert(q.isEmpty() == false);

	//pop
	int temp = q.pop(); //we also return the poped element
	assert(temp == 1);

	errored = false; //it must be true at the end
	try
	{
		q.pop();
	}
	catch (UnderflowException& e)
	{
		errored = true;
		assert(!strcmp(e.what(), "Underflow error! Tried to pop an empty queue."));
	}
	assert(errored);

	//top
	//check if we get error for top an empty queue
	errored = false;
	try
	{
		q.top();
	}
	catch (UnderflowException&)
	{
		errored = true;
	}
	assert(errored);

	//check the FIFO property
	q.push(2);
	q.push(3);
	assert(q.top() == 2);

	//resize - initial capacity is 3, already 2 elements in it, we exceed the capacity so it must double
	q.push(4);
	q.push(5);
	assert(q.top() == 2);
}

void Tests::testShuntingYardAlgorithm()
{
	ShuntingYardAlgorithm sya;

	//isOperator()
	assert(sya.isOperator('+'));
	assert(sya.isOperator('-'));
	assert(sya.isOperator('*'));
	assert(sya.isOperator('/'));
	assert(sya.isOperator('^'));
	assert(sya.isOperator('(') == false);

	//hasPrecedence() - true if the right one must be evaluated first
	//for 3+5-2 the right one is + (old one)
	assert( sya.hasPrecedence('+', '+') ); //if they are the same precedence
	assert(!sya.hasPrecedence('*', '+')); 
	assert(!sya.hasPrecedence('^', '-'));
	assert(!sya.hasPrecedence('^', '/'));
	//exception:for power operator we evaluate from right to left
	assert(sya.hasPrecedence('^', '^') == false);
	//for parantheses we do not check precedence
	assert(sya.hasPrecedence('*', ')') == false);

	//powerOperation()
	assert(sya.powerOperation(3, 0) == 1);
	assert(sya.powerOperation(3, 1) == 3);
	assert(sya.powerOperation(3, 7) == 2187);
	assert(sya.powerOperation(3, 14) == 4782969);

	//applyOperator(op, a, b) -> a op b
	assert(sya.applyOperator('+', 2, 3) == 5);
	assert(sya.applyOperator('*', 2, 3) == 6);
	assert(sya.applyOperator('-', 2, 3) == -1);
	assert(sya.applyOperator('/', 5, 2) == 2);
	assert(sya.applyOperator('^', 2, 3) == 8);
	
	bool errored = false;
	//divide by 0 error
	try
	{
		sya.applyOperator('/', 2, 0);
	}
	catch (DivisionByZeroException& e)
	{
		assert(e.what() == "Cannot divide by 0!");
		errored = true;
	}
	assert(errored);
	//apply unsupported operator error
	try
	{
		errored = false;
		sya.applyOperator('&', 2, 0);
	}
	catch (UnsupportedOperationException& e)
	{
		assert(e.what() == "This operator does not exist!");
		errored = true;
	}
	assert(errored);
	
	//infixToPostfix() - convert infix expression to postfix form
	QueueSLLA<string> t = sya.infixToPostfix("(2 + 3) * 55 + 1");
	string rez = "";
	while (!t.isEmpty())
		rez += t.pop();
	assert(rez == "23+55*1+"); //multiple digits operands will be sticked for the sake of this assert
	try
	{
		errored = false;
		sya.infixToPostfix("2$3");
	}
	catch (UnsupportedOperationException&)
	{
		errored = true;
	}
	assert(errored);

	//evaluate() - print the result of an expression
	//512 - 600
	int res = sya.evaluate("2^3^2-(10/5+1)*200");
	assert(res == -88);
	
	//Check if there are too many open brackets. The only error we can get, since others are handled
	//in infixToPostfix() or stack and queue functions
	try
	{
		errored = false;
		sya.evaluate("2^3^2-(10/5+1)*(200");
	}
	catch (OpenBracketException& e) //could have been written OpenBracketException
	{
		errored = true;
		assert(e.what() == "Too many open brackets!");
	}
	assert(errored);

	ExpressionException e{ "This is a test for the exception" };
	//strcmp return 0 if they are the same
	assert(strcmp(e.what(), "This is a test for the exception") == 0); 

	//showPostfixForm()
	assert(sya.showPostfixForm("2+3") == "23+");
}

void Tests::testAll()
{
	testNode();
	testStackSLL();
	testQueueSLLA();
	testShuntingYardAlgorithm();
}
