//---------------------------------------------------------------------------
#ifndef SerializationTestsH
#define SerializationTestsH
//---------------------------------------------------------------------------

#include "Test.h"

namespace srdev
{
	namespace Test
	{
		struct SerializationTests : public Case
		{
			virtual TestResult runTest() override;
		};
	}
}
#endif