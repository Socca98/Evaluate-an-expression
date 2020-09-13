#pragma once
#include "Stack.h"
#include "Node.h"
#include "Exceptions.h"

template <typename TElem>
class StackSLL: public Stack<TElem>
{
private:
	Node<TElem>* head;

public:
	//Constructor default SLL
	StackSLL() : Stack<TElem>{} 
	{
		this->head = nullptr;
	}

	//Destructor - deletes every node from linked list
	~StackSLL();

	/*
	Adds a new element at the top of the stack.
	IN: TElem
	OUT:-
	*/
	void push(TElem t);

	/*
	Removes the element(node) from the top of the stack.
	IN:-
	OUT:value that the removed node had in it
	*/
	TElem pop();

	/*
	Returns the value of the element(node) from the top of the stack.
	IN:-
	OUT: return default constructor values for the object TElem if stack is empty
	if its not empty returns the information from the Node 'head'
	*/
	TElem top();

	/*
	Checks if the stack is empty.
	IN:-
	OUT: 1 if empty, 0 else
	*/
	bool isEmpty();
};

template<typename TElem>
StackSLL<TElem>::~StackSLL()
{
	while (this->head != nullptr)
		this->pop();
}

template<typename TElem>
bool StackSLL<TElem>::isEmpty()
{
	if (this->head == nullptr)
		return true;

	return false;
}

template<typename TElem>
void StackSLL<TElem>::push(TElem t)
{
	Node<TElem>* newNode = new Node<TElem>{};
	newNode->setInfo(t);
	newNode->setNext(this->head);
	this->head = newNode;
}

template<typename TElem>
TElem StackSLL<TElem>::pop()
{
	//to avoid rest of the code we use this if
	if (this->isEmpty())
		throw UnderflowException("Underflow error! Tried to pop an empty stack.");

	Node<TElem>* temp = this->head;
	TElem res = temp->getInfo();
	this->head = this->head->getNext();
	
	delete temp; //deallocate removed node
	return res;
}

template<typename TElem>
TElem StackSLL<TElem>::top()
{
	if (this->isEmpty())
		throw UnderflowException("Underflow error! Tried to top an empty stack.");

	return this->head->getInfo();
}


