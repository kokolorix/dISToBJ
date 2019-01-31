
//---------------------------------------------------------------------------
#include "pch.h"
#pragma hdrstop

#include "SerializationTests.h"
#include "Json.h"
#include "Xml.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
using namespace srdev;

using namespace srdev;
using namespace srdev::js;

namespace
{
bool test = Test::addTestCase(make_shared<Test::SerializationTests>(), "SerializationTests");
}

namespace serialT
{
void jsonTest();
void xmlTest();
}

srdev::TestResult srdev::Test::SerializationTests::runTest()
{
	using namespace serialT;

	jsonTest();
	xmlTest();

	return TestResult::Successful;
}
namespace serialT
{
void jsonTest()
{
	{
		ObjectPtr obj = js::readJson(Json({ {"Wert1", 77 } }));
		String str = js::writeJson(obj).dump();
	}
	Json j1 =
	{
		{ "pi", 3.141 },
	{ "happy", true },
	{ "name", "Niels" },
	{ "nothing", nullptr },
	{ "answer",{
		{ "everything", 42 }
	} },
	{ "list",{ 1, 0, 2 } },
	{ "object",{
		{ "currency", "USD" },
	{ "value", 42.99 }
	} }
	};
	String s1 = j1.dump(4);
	auto j3 = Json::parse(s1);
	String s3 = j3.dump(4);
	assert(s1 == s3);
	ObjectPtr obj = js::readJson(j1);
	Json j2 = js::writeJson(obj);
	String s2 = j2.dump(4);
	assert(s2 == s1);
}
void xmlTest()
{
	Json j1 =
	{
		{ "pi", 3.141 },
	{ "happy", true },
	{ "name", "Niels" },
	{ "nothing", nullptr },
	{ "answer",{
		{ "everything", 42 }
	} },
	{ "list",{ 1, 0, 2 } },
	{ "object",{
		{ "currency", "USD" },
	{ "value", 42.99 }
	} }
	};
	ObjectPtr obj1 = js::readJson(j1);	
	String s1 = xml::writeString(obj1);
	ObjectPtr obj2 = xml::readString(s1);
	String s2 = xml::writeString(obj2);
	assert(s1 == s2);
}
}
