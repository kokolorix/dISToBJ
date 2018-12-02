//---------------------------------------------------------------------------

#ifndef BaseTestsH
#define BaseTestsH
//---------------------------------------------------------------------------
#include "Test.h"

namespace srdev
{
	namespace Test
	{
		struct BaseTests : public Case
		{
			virtual TestResult runTest() override;
		};
	}
}

#endif
