//---------------------------------------------------------------------------

#pragma hdrstop
#include "Pch\pch.h"
#include "Test.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

#include <map>
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <regex>


using std::endl;

using namespace srdev;

OutputStream srdev::out;



namespace
{
	using CaseMap = std::map<String, srdev::Test::CasePtr>;
	CaseMap& getCaseMap()
	{
		static CaseMap caseMap;
		return caseMap;
	}

	struct NameChecker
	{
		NameChecker(const String& pattern) : _pattern(pattern) {}
		bool operator()(const String& name);
		String _pattern;
	};


	bool NameChecker::operator()(const String & name)
	{
		if (_pattern == "*")
			return true;

		if(_pattern == name)
			return true;

		std::regex rx(_pattern);
		if (std::regex_match(name, rx))
			return true;
		else
			return false;
	}

}



srdev::TestResult srdev::runTests(const String& testPattern /*= "*"*/)
{

	NameChecker check(testPattern);
	for (CaseMap::value_type& entry : getCaseMap())
	{
		const String& name = entry.first;
		Test::CasePtr pTest = entry.second;
		if (check(name))
		{
			try
			{
				pTest->buildUp();
				out << "Run Test: " << name << std::endl;
				switch (pTest->runTest())
				{
				case TestResult::Successful:
					out << "Test " << name << " successfully completed" << std::endl;
					break;
				case TestResult::Failed:
					out << "Test " << name << " failed" << std::endl;
					break;
				default:
					out << "Test " << name << " failed with unexpected result" << std::endl;
					break;
				}

				pTest->breakDown();
			}
			catch (std::exception& e)
			{
				out << "Test " << name << " failed: " << e.what() << std::endl;
				return TestResult::Exception;
			}
			catch (...)
			{
				out << "Test " << name << " failed with unexpected exception" << std::endl;
				return TestResult::Unexpected;
			}
		}
	}
	return TestResult::Successful;
}


bool srdev::Test::addTestCase(CasePtr pTest, const String& name)
{
	auto res = getCaseMap().insert(make_pair(name, pTest));
	return res.second;
}
