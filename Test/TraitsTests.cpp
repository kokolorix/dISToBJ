//---------------------------------------------------------------------------
#include "pch.h"
#pragma hdrstop

#include "TraitsTests.h"
#include "Object.h"
#include "BaseTypes.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
using namespace srdev;

namespace
{
	bool test = Test::addTestCase(make_shared<Test::TraitsTests>(), "TraitsTests");
}

namespace
{
	void typeTest();
}

srdev::TestResult srdev::Test::TraitsTests::runTest()
{
	typeTest();

	return TestResult::Successful;
}

namespace
{
	void typeTest()
	{
		auto objectType = System::ObjectType::make();
		String name = objectType->getName();
		objectType->setName("nonsense");
		name = objectType->getName();
		//Vector propertyTypes = {System::PropertyType::make()};
		//objectType->setPropertyTypes(propertyTypes);
	}

}
