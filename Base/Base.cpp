//---------------------------------------------------------------------------
#include "pch.h"
#pragma hdrstop
#include "Base.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

using namespace srdev;

namespace impl
{
	StringMultiMap appArguments;
}
const StringMultiMap& srdev::AppArguments = impl::appArguments;


