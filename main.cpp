/*
Project 20 SDA - evaluate arithmetic expression
Socaciu Mihai 812
*/
#include <iostream>
#include <Windows.h>
#include <crtdbg.h>
#include "StackSLL.h"
#include "QueueSLLA.h"
#include "Tests.h"
#include "ShuntingYardAlgorithm.h"

using namespace std;

/*
User interface for the application that calls the algorithm.
*/
void run()
{
	cout << "Write 0 to exit.";
	while (1)
	{
		try
		{
			string expression = "0";
			int result = 0;
			cout << endl << "\nGive the arithmetic expression: \n\t";
			getline(cin, expression);

			if (expression == "0")
				break;

			result = ShuntingYardAlgorithm::evaluate(expression);

			cout << "\nResult: " << result << endl;

			cout << "\nPostfix form: " << ShuntingYardAlgorithm::showPostfixForm(expression) << endl;
		}
		catch (UnderflowException& e)
		{
			//errors for stack and queue
			//operations are not between operands!
			cout << e.what();
			cout << endl << "The expression is not written arithmetically correct.";
		}
		catch (ExpressionException& e)
		{
			//errors for expression
			cout << e.what();
		}
		catch (exception& e)
		{
			cout << endl << e.what();
		}
	}
}

int main()
{
	Tests::testAll(); //asserts the program's functions

	run();

	if (_CrtDumpMemoryLeaks())
		cout << "\nThere are memory leaks!" << endl;

	system("pause");
	return 0;
}