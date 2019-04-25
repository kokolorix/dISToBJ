//---------------------------------------------------------------------------
#define _CRT_SECURE_NO_WARNINGS
#include "pch.h"
#include <ctime>
#pragma hdrstop

#include "DatabaseTests.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
using namespace srdev;
using std::cerr;
using std::cout;
using std::endl;

#include <stdlib.h>

#define OTL_ODBC // Compile OTL 4.0/ODBC
// #define OTL_ODBC_UNIX // uncomment this line if UnixODBC is used
#include <otl/otlv4.h> // include the OTL 4.0 header file


namespace
{
	bool test = Test::addTestCase(make_shared<Test::DatabaseTests>(), "DatabaseTests");
}

namespace
{
	void testSQLite();
	void testMSSQL();

}

srdev::TestResult srdev::Test::DatabaseTests::runTest()
{
	testSQLite();
	testMSSQL();

	return TestResult::Successful;
}
namespace
{
	void testSQLite()
	{
		otl_connect db; // connect object
		otl_connect::otl_initialize(); // initialize ODBC environment
		try {

			db.rlogon("Driver={SQLite3 ODBC Driver};database=testSQLite.db3");
			//otl_cursor::direct_exec(db, "SELECT name FROM sqlite_master WHERE(type = 'table')");

			otl_cursor::direct_exec
			(
				db,
				"drop table test_tab",
				otl_exception::disabled // disable OTL exceptions
			); // drop table

			otl_cursor::direct_exec
			(
				db,
				"create table test_tab(f1 int, f2 varchar(30), f3 varchar(30))"
			);  // create table

			otl_stream
				o(50, // stream buffer size
					"insert into test_tab values(:f1<int>,:f2<char[31]>,:f3<char[31]>)",
					// SQL statement
					db  // connect object
				);
			char tmp[32];
			for (int i = 1; i <= 100; ++i) {
				sprintf_s(tmp, "Name%d", i);
				std::time_t result = std::time(nullptr);
				o << i << tmp << std::asctime(std::localtime(&result));
			}
			otl_stream i(50, // buffer size may be > 1
				"select * from test_tab "
				"where f1>=:f11<int> "
				"  and f1<=:f12<int>*2",
				// SELECT statement
				db // connect object
			);
			// create select stream

			int f1;
			char f2[31];
			char f3[31];

			i << 8 << 8; // Writing input values into the stream
			while (!i.eof()) { // while not end-of-data
				i >> f1;
				cout << "f1=" << f1 << ", f2=";
				i >> f2; i >> f3;
				if (i.is_null())
					cout << "NULL";
				else
					cout << f2;
				cout << endl;
			}
		}

		catch (otl_exception & p) { // intercept OTL exceptions
			cerr << p.msg << endl; // print out error message
			cerr << p.stm_text << endl; // print out SQL that caused the error
			cerr << p.sqlstate << endl; // print out SQLSTATE message
			cerr << p.var_info << endl; // print out the variable that caused the error
		}

		//db.commit();
		//db.

		db.logoff(); // disconnect from the database
	}

	void testMSSQL()
	{
		otl_connect db; // connect object
		otl_connect::otl_initialize(); // initialize ODBC environment
		try {
			db.rlogon("Driver={SQL Server};server=.\mssql;trusted_connection=Yes;app=Microsoft® Visual Studio®;wsid=VM-02;database=master");
			otl_stream dbs(10, "SELECT name FROM databases WHERE(name = :f1<varchar_long>)", db);
			dbs << "testMSSQL";
			if (dbs.eof())
			{
				otl_cursor::direct_exec(db, "CREATE DATABASE testMSSQL");
			}

		}
		catch (otl_exception & p) { // intercept OTL exceptions
			cerr << p.msg << endl; // print out error message
			cerr << p.stm_text << endl; // print out SQL that caused the error
			cerr << p.sqlstate << endl; // print out SQLSTATE message
			cerr << p.var_info << endl; // print out the variable that caused the error
		}
	}
}
