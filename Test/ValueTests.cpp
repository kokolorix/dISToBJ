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

namespace  tst
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
		// assert("42" == a2e);
		// String s_a2e = a2e;
	}

	void ptrTest()
	{
		ValuePtr a2e = Value::make(42);
	}
}
 using namespace tst;
srdev::TestResult srdev::Test::ValueTests::runTest()
{
	stackTest();
	ptrTest();
	return TestResult::Successful;
}
