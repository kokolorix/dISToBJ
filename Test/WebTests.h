//---------------------------------------------------------------------------
#ifndef WebTestsH
#define WebTestsH
//---------------------------------------------------------------------------
#include "Test.h"

namespace srdev
{
	namespace Test
	{
		struct WebTests : public Case
		{
			virtual TestResult runTest() override;
		};
	}
}

#endif
