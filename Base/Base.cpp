//---------------------------------------------------------------------------
#include "pch.h"
#pragma hdrstop
#include "Base.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

using namespace srdev;
//---------------------------------------------------------------------------
/*! \mainpage A quick start in dISToBJ
 *
 * \section intro_sec Overview
 *
 * The most important constructs.
 *
 * \subsection Globals
 *
 * with srdev::cast it exists a consistent way to cast one type to another.
 *
 * \subsection Classes
 *
 * srdev::Base is the base class of all.
 * srdev::Value is the base of all supported value types.
 * srdev::Property modulates a the Property from an srdev::Object
*/
namespace impl
{
	StringMultiMap appArguments;
}
const StringMultiMap& srdev::AppArguments = impl::appArguments;


