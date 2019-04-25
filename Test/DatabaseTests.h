//---------------------------------------------------------------------------
#ifndef DatabaseTestsH
#define DatabaseTestsH
//---------------------------------------------------------------------------
#include "Test.h"

namespace srdev
{
	namespace Test
	{
		struct DatabaseTests : public Case
		{
			virtual TestResult runTest() override;
		};
	}
}

#endif
