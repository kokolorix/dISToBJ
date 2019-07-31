//---------------------------------------------------------------------------
#include "pch.h"
#pragma hdrstop
#include "Base.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

using namespace srdev;
namespace srdev
{

	namespace impl { StringMultiMap appArguments; }
	boost::uuids::random_generator generateId;
	boost::uuids::nil_generator generateNullId;
	boost::uuids::string_generator generateIdFromString;

}
const StringMultiMap& srdev::AppArguments = srdev::impl::appArguments;


