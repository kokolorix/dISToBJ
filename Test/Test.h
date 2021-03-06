//---------------------------------------------------------------------------
#ifndef TestH
#define TestH
//---------------------------------------------------------------------------
#include <windows.h>
#include <assert.h>
#include "Base.h"

namespace srdev
{
	enum struct TestResult
	{
		Successful, Failed, Exception, Unexpected
	};

	TestResult runTests(const String& testPattern = "*");
	void writeOutput(const VectorOfStringVectors& outputs);

	namespace Test
	{
		struct Case
		{
			virtual ~Case() = default;
			virtual void buildUp() {}
			virtual TestResult runTest() = 0;
			virtual void breakDown() {}

		};
		using CasePtr = std::shared_ptr<Case>;
		bool addTestCase(CasePtr pTest, const String& name);
	}
}

namespace srdev
{
	template<typename Elem>
	inline void flush(std::basic_string<Elem>& msg)
	{
		if (msg.empty())
			return;

		std::cout << msg << std::endl;
		if (::IsDebuggerPresent())
		{
			OutputDebugStringA(msg.c_str());
			OutputDebugStringA("\n");
		}
	}

	template<>
	inline void flush(std::basic_string<wchar_t>& msg)
	{
		if (msg.empty())
			return;

		std::wcout << msg << std::endl;
		if (::IsDebuggerPresent())
		{
			OutputDebugStringW(msg.c_str());
			OutputDebugStringW(L"\n");
		}
	}

	template<typename Elem>
	class outputbuf : public std::basic_streambuf<Elem>
	{
	private:
		typedef typename std::basic_streambuf<Elem>::int_type int_type;
		std::basic_string<Elem> msg;	///< buffer for current log message

		void flushMsg()
		{
			if (msg.length() > 0)
			{
				flush(msg);
				msg.erase();	// erase message buffer
			}
		}

	public:
		outputbuf() { };
		~outputbuf() { flushMsg(); }

	protected:
		virtual int_type overflow(int_type c)
		{
			std::basic_ostream<Elem> tmp(this);
			if (c == tmp.widen('\n'))
			{
				flushMsg();
			}
			else
			{
				msg += c;
			}
			return c == -1 ? -1 : ' ';
		}

	private:
		outputbuf(outputbuf const&);                 // disallow copy construction
		void operator= (outputbuf const&);           // disallow copy assignment
	};

	template<typename Elem>
	class output_stream
		: private outputbuf<Elem>
		, public std::basic_ostream<Elem>
	{
	public:
		explicit output_stream() : std::basic_ostream<Elem>(this) { }
	};

	using OutputStream = output_stream<char>;
	extern 	OutputStream out;
}

#endif
