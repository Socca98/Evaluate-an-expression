#pragma once

template <typename TElem>
class Queue
{
public:
	Queue() {}
	virtual ~Queue() {}

	virtual void push(TElem t) = 0;
	virtual TElem pop() = 0;
	virtual TElem top() = 0;
	virtual bool isEmpty() = 0;
};