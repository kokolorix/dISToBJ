//---------------------------------------------------------------------------
#include "pch.h"
#pragma hdrstop

#include "BaseTests.h"
#include <iostream>
#include <chrono>
#include <thread>

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/mem_fun.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/sequenced_index.hpp>
#include <boost/multi_index/random_access_index.hpp>
#include <boost/multi_index/composite_key.hpp>
#include <boost/multi_index/global_fun.hpp>

#include <boost\algorithm\string.hpp>
#include <boost\date_time.hpp>


//---------------------------------------------------------------------------
#pragma package(smart_init)

using namespace srdev;

namespace
{
bool test = Test::addTestCase(std::make_shared<Test::BaseTests>(), "BaseTests");
}
	struct TestThing 
	{
		int32_t getIndex() const { return index_; }
	private:
		int32_t index_;
		friend srdev::TestResult srdev::Test::BaseTests::runTest();
	};
	using TestThingPtr = shared_ptr<TestThing>;

srdev::TestResult srdev::Test::BaseTests::runTest()
{
	using namespace boost;
	using namespace boost::multi_index;


	using TestThingTable = multi_index_container<
		TestThingPtr,
		indexed_by<
		ordered_unique<tag<int32_t>, multi_index::const_mem_fun<TestThing, int32_t, & TestThing::getIndex> >,
		ordered_non_unique<tag<int32_t>, member<TestThing, int32_t, &TestThing::index_> >,
		random_access<>
		>
	>;

	//typedef multi_index_container<
	//	CProjectGoblinIDMapEntry,
	//	indexed_by <
	//	sequenced<>,
	//	ordered_unique<tag<GoblinID>, const_mem_fun<CProjectGoblinIDMapEntry, IIPGoblinID, & CProjectGoblinIDMapEntry::GetGoblinID> >,
	//	ordered_non_unique<tag<ProjectGoblinID>, member<CProjectGoblinIDMapEntry, IIPGoblinID, & CProjectGoblinIDMapEntry::projectGoblinID> >
	//	>
	//> CProjectGoblinIDMap;
	//std::this_thread::sleep_for(std::chrono::seconds(2));
 /*
	using namespace boost::gregorian;

	typeid(*this).name();

	date today = day_clock::local_day();
	partial_date new_years_day(1, Jan);
	//Subtract two dates to get a duration
	auto days_since_year_start = today - new_years_day.get_date(2019);
	std::cout << "Days since Jan 1: " << today.day_of_year() << std::endl;

//	days days_until_year_start = new_years_day.get_date(today.year() + 1) - today;
//	std::cout << "Days until next Jan 1: " << days_until_year_start.days()
//			  << std::endl;
									 */
	return TestResult::Successful;
}
