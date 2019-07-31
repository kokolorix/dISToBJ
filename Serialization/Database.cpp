//---------------------------------------------------------------------------
#include "pch.h"
#define OTL_ODBC // Compile OTL 4.0/ODBC
// #define OTL_ODBC_UNIX // uncomment this line if UnixODBC is used
#define OTL_STL // Turn on STL features
#define OTL_CPP_17_ON

#pragma warning(push)
#pragma warning(disable: 5051) // attribute 'nodiscard' requires at least '/std:c++17'; ignored
#pragma warning(disable:26451) // Arithmetic overflow : Using operator '-' on a 4 byte value and then casting the result to a 8 byte value.Cast the value to the wider type before calling operator '-' to avoid overflow(io.2).
#include <otl/otlv4.h> // include the OTL 4.0 header file
#pragma warning(pop)

#pragma hdrstop

#include "Database.h"
#include "Value.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

using namespace srdev;
using namespace srdev::db;

namespace
{
	struct DbConnectionImpl : public DbConnection
	{
		DbConnectionImpl(String dbConnectionString)
		{
			otl_connect::otl_initialize(); // initialize ODBC environment

			connect_.rlogon(dbConnectionString.c_str());
		}
		virtual ~DbConnectionImpl() noexcept {}

		otl_connect connect_; // connect object


		virtual String toString() const override
		{
			throw std::logic_error("The method or operation is not implemented.");
		}


		virtual bool operator <(const Base& other) const override
		{
			throw std::logic_error("The method or operation is not implemented.");
		}

	};
	using DbConnectionImplPtr = shared_ptr<DbConnectionImpl>;
}

auto srdev::db::connectToDb(String dbConnectionString) -> DbConnectionPtr
{
	return make_shared<DbConnectionImpl>(dbConnectionString);
}

void srdev::db::checkObjectDbStructure(DbConnectionPtr dbConnection)
{

}

auto srdev::db::readObject(DbConnectionPtr dbConnection, String dbQuery) -> ObjectPtr
{
	DbConnectionImplPtr impl = dynamic_pointer_cast<DbConnectionImpl>(dbConnection);
	otl_stream s(50, dbQuery.c_str(), impl->connect_);

	int desc_len;
	otl_column_desc* desc = s.describe_select(desc_len);

	for (int n = 0; n < desc_len; ++n) {
		//cout << "========== COLUMN #" << n + 1 << " ===========" << endl;
		//cout << "name=" << desc[n].name << endl;
		//cout << "dbtype=" << desc[n].dbtype << endl;
		//cout << "otl_var_dbtype=" << desc[n].otl_var_dbtype << endl;
		//cout << "dbsize=" << desc[n].dbsize << endl;
		//cout << "scale=" << desc[n].scale << endl;
		//cout << "prec=" << desc[n].prec << endl;
		//cout << "nullok=" << desc[n].nullok << endl;
	}
	return ObjectPtr();
}

auto srdev::db::readObjects(DbConnectionPtr dbConnection, String dbQuery) -> ObjectPtrVector
{
	return ObjectPtrVector();
}
