#pragma hdrstop
#include "Pch\pch.h"
#pragma argsused

#include <iostream>
#include "Test.h"

using namespace srdev;

int main(int argc, char* argv[])
{
	TestResult r = TestResult::Successful;
	if (argc > 1)
	{
		for (int i = 1; i < argc; ++i)
		{
			r = runTests(argv[i]);
			if (r != TestResult::Successful)
				return static_cast<int>(r);
		}
	}
	else
	{
		r = runTests();
	}
	return static_cast<int>(r);
}
