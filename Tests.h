#pragma once
#include "ShuntingYardAlgorithm.h"
#include <assert.h>

class Tests
{
private:
	static void testNode();
	static void testStackSLL();
	static void testQueueSLLA();
	static void testShuntingYardAlgorithm();

public:
	static void testAll();
};