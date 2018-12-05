//---------------------------------------------------------------------------
#include "pch.h"
#pragma hdrstop

#include "BaseTests.h"
#include <iostream>
#include <chrono>
#include <thread>
//---------------------------------------------------------------------------
#pragma package(smart_init)
using namespace srdev;

namespace
{
bool test = Test::addTestCase(make_shared<Test::BaseTests>(), "BaseTests");
}

srdev::TestResult srdev::Test::BaseTests::runTest()
{
	std::this_thread::sleep_for(std::chrono::seconds(2));
	return TestResult::Successful;
}
