//---------------------------------------------------------------------------
#include "pch.h"
#pragma hdrstop
#include "Base.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

using namespace srdev;
namespace srdev
{
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
 * \subsection Namespaces
 * 
 * srdev::Test is the namespace where all test are in
 *
 * \subsection Classes
 *
 * Base is the base class of everything.
 * 
 * Value is the base of all supported value types.
 * 
 * Property modulates a the Property from an Object
 * 
 * \htmlonly
 * <a href="inherits.html">Go to the graphical class hierarchy</a>
 * \endhtmlonly
*/
namespace impl { StringMultiMap appArguments; }
}
const StringMultiMap& srdev::AppArguments = srdev::impl::appArguments;


