#pragma once
#include "Queue.h"
#include "Exceptions.h"
#define INIT_CAPACITY 3

template <typename TElem>
class QueueSLLA : public Queue<TElem>
{
private:
	TElem* elems;
	int* next;
	int capacity;
	int head;
	int tail;
	int firstEmpty;

public:
	//Constructor default
	QueueSLLA() : Queue<TElem>{} 
	{
		this->capacity = INIT_CAPACITY;
		this->elems = new TElem[this->capacity];
		this->next = new int[this->capacity];
		this->head = -1;
		this->tail = -1;
		
		for (int i = 0; i < this->capacity - 1; i++)
			this->next[i] = i + 1;

		this->next[this->capacity - 1] = -1; //last empty slot must have next as -1
		this->firstEmpty = 0; //indexing starts at 0
	}

	//Copy constructor, 'e' is the existing one having its fields assigned to something
	QueueSLLA(const QueueSLLA& e);

	//Destructor - deallocates elems and next dynamic arrays
	~QueueSLLA();

	/*
	When the queue is full we resize the dynamic arrays keeping the elements.
	We double the capacity and allocate TElem in memory.
	IN:-
	OUT:-
	*/
	void resize();

	/*
	Checks if the queue is empty.
	IN:-
	OUT: 1 if empty, 0 else
	*/
	bool isEmpty();

	/*
	Adds a new element to the rear part of the queue.
	At the end of the SLLA using tail.
	IN: TElem
	OUT:-
	*/
	void push(TElem t);

	/*
	Removes the element from the front of the queue.
	First element of the SLLA using head.
	IN:-
	OUT:value that the removed node had in it
	*/
	TElem pop();

	/*
	Returns the value of the element from the front of the stack.
	IN:-
	OUT: returns default constructor values for the object TElem if queue is empty
	if its not empty returns the information from the 'head' indicator
	*/
	TElem top();

};

template<typename TElem>
QueueSLLA<TElem>::QueueSLLA(const QueueSLLA & e)
{
	this->capacity = e.capacity;
	this->head = e.head;
	this->tail = e.tail;
	this->firstEmpty = e.firstEmpty;
	this->elems = new TElem[this->capacity]; //The copy has own memory/different elements
	this->next = new int[this->capacity];

	for (int i = 0; i < this->capacity; i++)
	{
		this->elems[i] = e.elems[i];
		this->next[i] = e.next[i];
	}
}

template<typename TElem>
QueueSLLA<TElem>::~QueueSLLA()
{
	delete[] this->elems;
	delete[] this->next;
}

template<typename TElem>
void QueueSLLA<TElem>::resize()
{
	TElem* newElems = new TElem[this->capacity * 2];
	int* newNext = new int[this->capacity * 2];

	for (int i = 0; i < this->capacity; i++)
	{
		newElems[i] = this->elems[i];
		newNext[i] = this->next[i];
	}

	//indexing starts at 0 so last element in for loop must be the penultimate
	for (int i = this->capacity; i < this->capacity * 2 - 1; i++)
	{
		newNext[i] = i + 1;
	}
	newNext[this->capacity * 2 - 1] = -1;

	//Deallocate smaller capacity arrays
	delete[] this->elems;
	delete[] this->next;

	this->elems = newElems;
	this->next = newNext;
	this->firstEmpty = this->capacity; // '+ 1' if it starts at index 1
	this->capacity *= 2;
}

template<typename TElem>
bool QueueSLLA<TElem>::isEmpty()
{
	if (this->head == -1)
		return true;

	return false;
}

template<typename TElem>
void QueueSLLA<TElem>::push(TElem e)
{
	//if it has as many elements as the capacity number
	if (this->firstEmpty == -1)
		this->resize();

	int newPos = this->firstEmpty; //position where the new element will be added
	
	this->elems[newPos] = e;
	this->firstEmpty = this->next[this->firstEmpty];
	this->next[newPos] = -1; // always assigned -1 because its added at the end

	//If the queue is empty
	if (this->isEmpty())
		this->head = newPos;
	else
	{
		this->next[this->tail] = newPos;
	}
	this->tail = newPos;
}

template<typename TElem>
TElem QueueSLLA<TElem>::pop()
{
	if (this->isEmpty()) //nothing to be poped
		throw UnderflowException("Underflow error! Tried to pop an empty queue.");

	TElem res = this->elems[this->head];
	int curNode = this->head;

	//if there is only 1 element existent
	if (this->tail == this->head)
		this->tail = -1;

	this->head = this->next[this->head]; //old head becomes now curNode
	this->next[curNode] = this->firstEmpty;
	this->firstEmpty = curNode;

	return res;
}

template<typename TElem>
TElem QueueSLLA<TElem>::top()
{
	if (this->isEmpty())
		throw UnderflowException("Underflow error! Tried to top an empty queue.");
	
	return this->elems[this->head];
}




