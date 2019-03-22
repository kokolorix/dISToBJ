// ---------------------------------------------------------------------------
#include "pch.h"
#pragma hdrstop

#include "ValueTests.h"

#include "Value.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)

using namespace srdev;

namespace
{
	bool test = Test::addTestCase(make_shared<Test::ValueTests>(), "ValueTests");
}

namespace
{
	void stackTest()
	{
		Int32Value a2e(42);
		assert(42 == a2e);
		assert(43 > a2e);
		assert(41 < a2e);

		assert(a2e == 42);
		assert(a2e < 43);
		assert(a2e > 41);
		assert("42" == a2e);
		String s_a2e = a2e;
	}

	void ptrTest()
	{
		ValuePtr a2e = Value::make(42);

	}

	void parseTest()
	{
		assert(dynamic_pointer_cast<const Int32Value>(Value::parse("42")));
		assert(dynamic_pointer_cast<const UInt32Value>(Value::parse("0x2a")));
		assert(dynamic_pointer_cast<const UInt64Value>(Value::parse("0xfffffffffff")));
		assert(dynamic_pointer_cast<const Int64Value>(Value::parse("17592186044415")));
		assert(dynamic_pointer_cast<const BooleanValue>(Value::parse("true")));
		assert(dynamic_pointer_cast<const DoubleValue>(Value::parse("1.7e+3")));
		assert(dynamic_pointer_cast<const StringValue>(Value::parse("Lorem Ipsum is simply dummy text of the printing and typesetting.")));
	}
}

srdev::TestResult srdev::Test::ValueTests::runTest()
{
	stackTest();
	ptrTest();
	parseTest();
	return TestResult::Successful;
}
