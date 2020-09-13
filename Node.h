#pragma once

/*
Node is composed of a generic value 'TElem' and a pointer to another object Node.
*/
template <typename TElem>
class Node
{
private:
	TElem info;
	Node* next;

public:
	//Default constructor
	Node();

	//Getter function
	TElem getInfo() const;
	Node* getNext() const;
	
	//Setter function
	void setInfo(TElem v) { this->info = v; }
	void setNext(Node* v) { this->next = v; }
};

template <typename TElem>
Node<TElem>::Node()
{
	this->next = nullptr;
}

template <typename TElem>
TElem Node<TElem>::getInfo() const
{
	//if head is NIL then it does not have ->info
	if (this == nullptr)
		return TElem{};

	return this->info;
}

template <typename TElem>
Node<TElem>* Node<TElem>::getNext() const
{
	//if head is NIL then it does not have ->next
	if (this == nullptr)
		return nullptr;

	return this->next;
}