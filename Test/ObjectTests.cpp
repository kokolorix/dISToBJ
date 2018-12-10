//---------------------------------------------------------------------------
#include "pch.h"
#pragma hdrstop

#include "ObjectTests.h"
#include "Object.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
using namespace srdev;

namespace
{
bool test = Test::addTestCase(make_shared<Test::ObjectTests>(), "ObjectTests");
}
namespace
{
	void ptrTest()
	{
		ValuePtr a2e = Value::make(42);
		PropertyPtr Name = Property::make("Name", Value::make("TheFirstObject"));
		PropertyPtr A2E = Property::make("AnswerToEverything", a2e);
		PropertyPtr Pi = Property::make("Pi", 3.14);
		//PropertyPtr Id = Property::make("Id", generateId());
		ObjectPtr obj = Object::make({ Name, A2E, Pi });
		assert(obj["Name"] == "TheFirstObject");
		double pi = obj["Pi"];
		assert(pi == 3.14);
		assert(obj["Pi"] == 3.14);
		obj["Nr"] = 13;
		assert(obj["Nr"] == 13);

		obj["Child1"] = Object::make({ std::make_pair("Name", "Child1") });
		assert(obj["Child1"]["Name"] == "Child1");
		obj["Child2"]["Name"] = "Child2";
		assert(obj["Child2"]["Name"] == "Child2");
	}
}
srdev::TestResult srdev::Test::ObjectTests::runTest()
{
	ptrTest();
	return TestResult::Successful;
}
