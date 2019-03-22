//---------------------------------------------------------------------------
#ifndef CompareH
#define CompareH
#include "Base.h"
#include <algorithm>
//---------------------------------------------------------------------------
namespace srdev
{
	using std::equal;
	using std::find_if;
}
namespace srdev
{
	template<typename compareT, typename firstT>
	inline bool is_one_of(compareT toCompare, firstT firstOne)
	{
		return toCompare == firstOne;
	}
	template<typename compareT, typename firstT, class... ArgsT>
	inline bool is_one_of(compareT toCompare, firstT firstOne, ArgsT&& ... args)
	{
		return toCompare == firstOne || is_one_of(toCompare, args...);
	}

	inline bool iequal(const String& str1, const String& str2)
	{
		return ((str1.size() == str2.size()) &&
			equal(str1.begin(), str1.end(), str2.begin(), [](const char& c1, const char& c2) {
				return (c1 == c2 || std::toupper(c1) == std::toupper(c2));
				}));
	}

	inline bool isDecNumber(const String & str)
	{
		if (str.empty())
			return false;

		auto begin = str.begin();
		if (*begin == '-' || *begin == '+')
			begin = std::next(begin);

		auto pos = find_if(begin, str.end(),
			[](String::value_type c) { return !std::isdigit(c); });

		if (pos == str.end())
			return true;
		else
			return false;
	}

	inline bool isHexNumber(const String & str)
	{
		if (str.empty())
			return false;

		auto begin = str.begin();
		if (*begin != '0')
			return false;
		begin = std::next(begin);

		if (std::toupper(*begin) != 'X')
			return false;
		begin = std::next(begin);

		auto pos = find_if(begin, str.end(),
			[](String::value_type c) { return !(std::isdigit(c) || is_one_of(std::toupper(c),'A','B','C','D','E','F')); });

		if (pos == str.end())
			return true;
		else
			return false;
		//if (str.find_first_not_of("0123456789aAbBcCdDeEfF", begin) == str.size())
		//	return true;
		//else
		//	return false;
	}

	inline bool isFloatingPointNumber(const String& str)
	{
		if (str.empty())
			return false;

		auto begin = str.begin();
		if (*begin == '-' || *begin == '+')
			begin = std::next(begin);

		auto points = std::count_if(begin, str.end(),
			[](String::value_type c) { return is_one_of(c, '.', ','); });

		if (points != 1)
			return false;

		return true;
	}
}
#endif