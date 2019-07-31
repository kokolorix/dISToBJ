//---------------------------------------------------------------------------
#ifndef DatabaseH
#define DatabaseH
//---------------------------------------------------------------------------

#include "Object.h"

namespace srdev
{
	namespace db
	{
		class DbConnection : public Base
		{
		};
		using DbConnectionPtr = shared_ptr<DbConnection>;
	}
	namespace db
	{
		auto connectToDb(String dbConnectionString) -> DbConnectionPtr;
		void checkObjectDbStructure(DbConnectionPtr dbConnection);
		auto readObject(DbConnectionPtr dbConnection, String dbQuery) -> ObjectPtr;
		auto readObjects(DbConnectionPtr dbConnection, String dbQuery) -> ObjectPtrVector;
	}
}
#endif