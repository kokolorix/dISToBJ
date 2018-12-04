#pragma hdrstop
#include "pch.h"
#pragma argsused

#include "Test.h"

using namespace srdev;
namespace impl { extern StringMultiMap appArguments; }

int main(int argc, char* argv[])
{
	TestResult r = TestResult::Successful;
	if (argc > 1)
	{
		for (int i = 1; i < argc; ++i)
		{
			std::istringstream is(argv[i]);
			String key, val;
			std::getline(is, key, '=');
			std::getline(is, val);
			impl::appArguments.insert(std::make_pair(key,val));

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
