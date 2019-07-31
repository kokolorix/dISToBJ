//---------------------------------------------------------------------------
#ifndef JsonH
#define JsonH
//---------------------------------------------------------------------------

#include "Object.h"
#pragma warning(push)
#pragma warning(disable:26451) // Arithmetic overflow : Using operator '-' on a 4 byte value and then casting the result to a 8 byte value.Cast the value to the wider type before calling operator '-' to avoid overflow(io.2).
#pragma warning(disable:28020) // The expression '0<=_Param_(1)&&_Param_(1)<=400-1' is not true at this call.
#pragma warning(disable:26495) // C	Variable 'nlohmann::basic_json<std::map,std::vector,std::basic_string<char,std::char_traits<char>,std::allocator<char> >,bool,__int64,unsigned __int64,double,std::allocator,nlohmann::adl_serializer>::m_type' is uninitialized.Always initialize a member variable(type.6).


#include <nlohmann/json.hpp>
#pragma warning(pop)

namespace srdev
{
using Json = nlohmann::json;

namespace js
{
ObjectPtr readJson(const Json& j);
ObjectPtr readFile(const Path& filePath);
ObjectPtr readString(const String& jsonString);
Json writeJson(ObjectPtr object);
void writeFile(const Path& filePath, ObjectPtr object);
String writeString(ObjectPtr object);
}//json
}//obj
#endif
