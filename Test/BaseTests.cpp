//---------------------------------------------------------------------------

#pragma hdrstop
#include "Pch\pch.h"

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
//	using namespace std::chrono_literals;
	out << "Hello waiter" << std::endl; // flush is intentional
    auto start = std::chrono::high_resolution_clock::now();
	std::this_thread::sleep_for(std::chrono::seconds(2));
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed = end-start;
	std::cout << "Waited " << elapsed.count() << " ms\n";
//	out << "Hello World" << std::endl;
	return TestResult::Successful;
}
