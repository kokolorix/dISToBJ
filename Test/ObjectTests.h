//---------------------------------------------------------------------------
#ifndef ObjectTestsH
#define ObjectTestsH
//---------------------------------------------------------------------------
#include "Test.h"

namespace srdev
{
	namespace Test
	{
		struct ObjectTests : public Case
		{
			virtual TestResult runTest() override;

			void ptrTest();

		};
	}
}

#endif
