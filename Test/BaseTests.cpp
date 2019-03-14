//---------------------------------------------------------------------------
#include "pch.h"
#pragma hdrstop

#include "BaseTests.h"
#include <iostream>
#include <chrono>
#include <thread>

#ifdef __BORLANDC__

#define __TEMP1__ __BORLANDC__
#undef __BORLANDC__
#define __TEMP2__ __CODEGEARC__
#undef __CODEGEARC__

#define _MSC_VER 1914
#define _MSVC_LANG 201704L
#define _M_AMD64 100


//#include <boost\date_time.hpp>

//
//#define __BORLANDC__  __TEMP1__
//#undef  __TEMP1__
//#define __CODEGEARC__  __TEMP2__
//#undef  __TEMP2__

#endif
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

//	using namespace boost::gregorian;

	//typeid(*this).name();  type_info_t* p;

//	date today = day_clock::local_day();
//	partial_date new_years_day(1, Jan);
//	//Subtract two dates to get a duration
//	days days_since_year_start = today - new_years_day.get_date(today.year());
//	std::cout << "Days since Jan 1: " << days_since_year_start.days()
//			  << std::endl;
//
//	days days_until_year_start = new_years_day.get_date(today.year() + 1) - today;
//	std::cout << "Days until next Jan 1: " << days_until_year_start.days()
//			  << std::endl;

	return TestResult::Successful;
}
