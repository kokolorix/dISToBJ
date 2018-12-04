//---------------------------------------------------------------------------

#pragma hdrstop
#include "pch.h"
#include "Test.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

#include <map>
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <regex>
#include <chrono>

#include "Cast.h"

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
	StringVector labels = { "Test name","Buildup (ms)","Test result","Test (ms)","Breakdown (ms)", "Total (ms)" };
	VectorOfStringVectors outputs = { labels };
	//writeOutput(labels);

	NameChecker check(testPattern);
	for (CaseMap::value_type& entry : getCaseMap())
	{
		const String& name = entry.first;
		Test::CasePtr pTest = entry.second;
		if (check(name))
		{

			StringVector values; 
			values.reserve(labels.size());
			values.push_back(name);
			try
			{
				auto start = std::chrono::high_resolution_clock::now();
				{
//					out << "Buildup Test: " << name << std::endl;
					auto start = std::chrono::high_resolution_clock::now();
					pTest->buildUp();
					auto end = std::chrono::high_resolution_clock::now();
					std::chrono::duration<double, std::milli> elapsed = end - start;
					values.push_back(cast<String>(elapsed.count()));
				}
				{
					//				out << "Run Test: " << name << std::endl;
					auto start = std::chrono::high_resolution_clock::now();
					switch (pTest->runTest())
					{
					case TestResult::Successful:
						values.push_back("Succeed");
						//out << "Test " << name << " successfully completed" << std::endl;
						break;
					case TestResult::Failed:
						values.push_back("Failed");
						//out << "Test " << name << " failed" << std::endl;
						break;
					default:
						values.push_back("Error");
						//out << "Test " << name << " failed with unexpected result" << std::endl;
						break;
					}
					auto end = std::chrono::high_resolution_clock::now();
					std::chrono::duration<double, std::milli> elapsed = end - start;
					values.push_back(cast<String>(elapsed.count()));
				}

				{
					//out << "Breakdown Test: " << name << std::endl;
					auto start = std::chrono::high_resolution_clock::now();
					pTest->breakDown();
					auto end = std::chrono::high_resolution_clock::now();
					std::chrono::duration<double, std::milli> elapsed = end - start;
					values.push_back(cast<String>(elapsed.count()));
				}
				auto end = std::chrono::high_resolution_clock::now();
				std::chrono::duration<double, std::milli> elapsed = end - start;
				values.push_back(cast<String>(elapsed.count()));
				outputs.push_back(values);
			}
			catch (std::exception &e)
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

	writeOutput(outputs);

	return TestResult::Successful;
}

void srdev::writeOutput(const VectorOfStringVectors& outputs)
{
	if(outputs.size() > 1) // if 1, no tests were performed
	{
		const StringVector& labels = outputs.front();
		for (const StringVector& values : outputs)
		{
			for (size_t i=0; i < labels.size(); ++i)
			{
				const String label = labels.at(i);
				if (values.size() > i)
				{
					String value = values.at(i);
					if (value.length() > label.length())
						value.erase(label.size());
					else if (value.length() < label.length())
						value += String(label.length() - value.length(), ' ');
					out << value << "\t";
				}
				else
				{
					String value(label.size(), ' ');
					out << value << "\t";
				}
			}
			out << endl;
		}
	}
}

bool srdev::Test::addTestCase(CasePtr pTest, const String& name)
{
	auto res = getCaseMap().insert(make_pair(name, pTest));
	return res.second;
}
