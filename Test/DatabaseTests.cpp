//---------------------------------------------------------------------------
#include "pch.h"
#include <ctime>
#include <stdlib.h>
#include <stdio.h>
#pragma hdrstop

#include "DatabaseTests.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
using namespace srdev;
using std::cerr;
using std::cout;
using std::endl;


#define OTL_ODBC // Compile OTL 4.0/ODBC
// #define OTL_ODBC_UNIX // uncomment this line if UnixODBC is used
#define OTL_STL // Turn on STL features
#include <otl/otlv4.h> // include the OTL 4.0 header file


namespace
{
	bool test = Test::addTestCase(make_shared<Test::DatabaseTests>(), "DatabaseTests");
}

namespace
{
	void testSQLite();
	void testMSSQL();
	void TestTable(otl_connect& db);

	void testReadTables();
}

srdev::TestResult srdev::Test::DatabaseTests::runTest()
{
	testSQLite();
	testMSSQL();

	testReadTables();

	return TestResult::Successful;
}
namespace
{

	void testSQLite()
	{
		otl_connect db; // connect object
		otl_connect::otl_initialize(); // initialize ODBC environment
		try {

			db.rlogon("Driver={SQLite3 ODBC Driver};database=Test/testSQLite.db3");
			otl_cursor::direct_exec(db, "SELECT name FROM sqlite_master WHERE(type = 'table')");

			TestTable(db);
		}

		catch (otl_exception & p) { // intercept OTL exceptions
			cerr << p.msg << endl; // print out error message
			cerr << p.stm_text << endl; // print out SQL that caused the error
			cerr << p.sqlstate << endl; // print out SQLSTATE message
			cerr << p.var_info << endl; // print out the variable that caused the error
		}

		//db.commit();
		//db.

//		db.logoff(); // disconnect from the database
	}

	void testMSSQL()
	{
		otl_connect db; // connect object
		otl_connect::otl_initialize(); // initialize ODBC environment
		try {
			db.rlogon("Driver={SQL Server};server=.;trusted_connection=Yes;;database=testMSSQL");
	
			TestTable(db);
		}
		catch (otl_exception & p) { // intercept OTL exceptions
			cerr << p.msg << endl; // print out error message
			cerr << p.stm_text << endl; // print out SQL that caused the error
			cerr << p.sqlstate << endl; // print out SQLSTATE message
			cerr << p.var_info << endl; // print out the variable that caused the error
		}
	}

	void TestTable(otl_connect& db)
	{
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
			sprintf(tmp, "Name%d", i);
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

	struct table_info
	{
		String tableName, columnName, columnType, foreignKeyTable, foreignKeyColumn;
		using input_iterator = otl_input_iterator<table_info, ptrdiff_t>;
	};
	using table_info_vector = std::vector<table_info>;
	// redefined operator>> for reading row& from otl_stream
	otl_stream& operator>>(otl_stream& s, table_info& row)
	{
		s >> row.tableName >> row.columnName >> row.columnType >> row.foreignKeyTable >> row.foreignKeyColumn;
		return s;
	}

	void testReadTables()
	{
		otl_connect db; // connect object
		otl_connect::otl_initialize(); // initialize ODBC environment
		String dbConnectionString = "Driver={SQLite3 ODBC Driver};database=Test/testSQLite-Objects.db3";
		String dbQuery =
			"SELECT t.name AS tableName, c.name AS columnName, c.type AS columnType, c.[table] AS foreignKeyTable, c.[to] AS foreignKeyColumn "
			" FROM sqlite_master t "
			"       LEFT JOIN "
			"       ( "
			"           SELECT DISTINCT ti.name, ti.type, fk.[table], fk.[to] FROM (  SELECT *  FROM pragma_table_info('value')  ) ti "
			"                  LEFT JOIN "
			"                  ( SELECT * FROM pragma_foreign_key_list('value')  ) "
			"                  fk ON fk.[from] = ti.name "
			"       ) c "
			" WHERE t.type = 'table' " 
			;		
		
		db.rlogon(dbConnectionString.c_str());
		otl_stream inputStream(50, dbQuery.c_str(), db);
		table_info::input_iterator begin(inputStream), end;
		table_info_vector tableInfos;
		std::copy(begin, end, std::inserter(tableInfos, tableInfos.end()));
	}

}
