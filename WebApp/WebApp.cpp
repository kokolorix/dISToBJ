//---------------------------------------------------------------------------
#include "pch.h"
#pragma hdrstop
#include "WebApp.h"
//---------------------------------------------------------------------------
#pragma argsused

using namespace srdev;
namespace srdev
{
	namespace impl { extern StringMultiMap appArguments; }
}
int main(int argc, char* argv[])
{
	if (argc > 1)
	{
		for (int i = 1; i < argc; ++i)
		{
			std::istringstream is(argv[i]);
			String key, val;
			std::getline(is, key, '=');
			std::getline(is, val);
			impl::appArguments.insert(std::make_pair(key, val));
		}
	}
	else
	{
	}
	return 0;
}
