//---------------------------------------------------------------------------
#ifndef BaseH
#define BaseH
#include <sstream>
#include <iostream>
#include <typeinfo>
#include <memory>
#include <algorithm>
#include <functional>
#include <vector>
#include <map>
//---------------------------------------------------------------------------
namespace srdev
{
	using std::istringstream;
	using std::ostringstream;
	using std::shared_ptr;
	using std::make_shared;
	using std::dynamic_pointer_cast;
	using std::function;

	using String = std::string;
	using StringVector = std::vector<String>;
	using VectorOfStringVectors = std::vector<StringVector>;
	using StringMap = std::map<String, String>;
	using StringMultiMap = std::multimap<String, String>;
	
	using Path = std::string;
}

namespace srdev
{
	extern const StringMultiMap& AppArguments;
}
namespace srdev
{
	struct Exception : public std::exception
	{
		Exception(const char *msg) : msg_(msg) {}
		Exception(const String& msg) : msg_(msg) {}
		virtual const char *what() const noexcept override { return msg_.c_str(); }

	private:
		String msg_;
	};
	struct NotImplementetException : public Exception { using Exception::Exception; };
	struct NotFoundException : public Exception { using Exception::Exception; };
	struct ImpossibleCastException : public Exception { using Exception::Exception; };
	struct ImpossibleCompareException : public Exception { using Exception::Exception; };
}
namespace srdev
{
	class Base
	{
	public:
		virtual ~Base() {}

		virtual String toString() const
		{
			ostringstream os;
			os << typeid(*this).name() << " (" << std::hex << this << ")";
			return os.str();
		}
		virtual bool operator < (const Base& other) const
		{
			return this < &other;
		}

	protected:

	private:
	};
}

#endif
