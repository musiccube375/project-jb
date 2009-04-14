// sql_01.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <mysql++.h>

#include <iomanip>
#include <iostream>

using namespace std;
using namespace mysqlpp;

#pragma comment(lib,"libmysql")
#pragma comment(lib,"mysqlpp")


int _tmain(int argc, _TCHAR* argv[])
{
	Connection con("gamedata","127.0.0.1","root","46EkdzhRl20");

	// -------------------------------------------------------

	Query query = con.query();
	query << "show databases";
	cout << "Query: " << query.preview() << endl;

	Result res = query.store();
	cout << "Databases found: " << res.size() << endl;

	Row row;
	cout.setf(ios::left);
	Result::iterator i;
	for (i = res.begin(); i != res.end(); ++i) {
		row = *i;
		cout << '\t' << setw(17) << row.raw_data(0) << endl ;
	}

	// -------------------------------------------------------

	con.select_db("gamedata");

	query.reset();
	query << "show tables";
	cout << "Query: " << query.preview() << endl;

	res = query.store();
	cout << "Tables found: " << res.size() << endl;

	cout.setf(ios::left);
	for (i = res.begin(); i != res.end(); ++i) {
		row = *i;
		cout << '\t' << setw(17) << (string)row.raw_data(0) << endl;
	}

	// -------------------------------------------------------

	query.reset();
	query << "select * from playerinfo";

	res = query.store();
	int columns = res.num_fields();
	cout << "fields = " << res.num_fields() << ", rows = " <<
			res.size() << endl;
	
	volatile MYSQL_RES* ress = res.raw_result();
	if (!ress)
		return -1;
	
	for (i = res.begin(); i != res.end(); ++i) {
		for (int counter = 0; counter < columns; counter++) {
			cout << string( (*i).at(counter)) << "  ";
		}
		cout << endl;
	}

	// -------------------------------------------------------

	return 0;
}