//---------------------------------------------------------------------------
#ifndef JsonH
#define JsonH
//---------------------------------------------------------------------------

#include "Object.h"
#pragma warning(push)
#pragma warning(disable:4003)
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
