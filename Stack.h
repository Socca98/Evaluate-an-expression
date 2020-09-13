#pragma once

template <typename TElem>
class Stack
{
public:
	Stack() {}
	virtual ~Stack() {}

	virtual void push(TElem t) = 0;
	virtual TElem pop() = 0;
	virtual TElem top() = 0;
	virtual bool isEmpty() = 0;
};