//---------------------------------------------------------------------------

#ifndef BaseH
#define BaseH
#include <sstream>
#include <iostream>
#include <typeinfo>
#include <memory>
#include <functional>
#include <vector>
#include <map>
//#include <m>
//---------------------------------------------------------------------------
namespace srdev
{
	using ::std::istringstream;
	using ::std::ostringstream;
	using ::std::shared_ptr;
	using ::std::make_shared;

	using String = std::string;
	using StringVector = std::vector<String>;
	using VectorOfStringVectors = std::vector<StringVector>;
	using StringMap = std::map<String,String>;
	using StringMultiMap = std::multimap<String, String>;
}

namespace srdev
{
	extern const StringMultiMap& AppArguments;
}
#endif