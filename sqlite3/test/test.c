#include <stdio.h>
//#include <windows.h>
#include "sqlite3.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>

//±‡“Î tcc 0.9.25
// tcc sqltest.c sqlite3.c

static int commit_capture_count = 0;
int commit_capture(void* __unused)
{
	const int continue_commit = 0;
	++commit_capture_count;
        //printf("Hello! commit = %d\n",commit_capture_count);
	return continue_commit;
}

int
insert_table_data(sqlite3* db, int uid, int mh, int ml, int p1, int p2)
{
	char sqlStr[128];
	sqlite3_stmt* vm;
	const char* tail;
	int rc;

	memset(sqlStr, 0, sizeof(sqlStr));
	snprintf(sqlStr, sizeof(sqlStr) - 1,
		"insert into memdata (userid, mach_h, mach_l, port1, port2) values (%d, %d, %d, %d, %d);",
		uid, mh, ml, p1, p2);

	rc = sqlite3_prepare_v2(db, sqlStr, -1, &vm, &tail);
	if (rc != SQLITE_OK)
	{
		fprintf(stderr, "prepare_v2 err: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		exit(1);
	}

	rc = sqlite3_step(vm);
	if (rc != SQLITE_DONE)
	{
		fprintf(stderr, "step err: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		exit(1);
	}
	//    else
	//    {
	//        fprintf (stderr, "insert %d rows\n", sqlite3_changes(db));
	//    }

	sqlite3_finalize(vm);

	return 0;
}

sqlite3_stmt* prepare_insert(sqlite3* db)
{
	char sqlStr[128];
	sqlite3_stmt* vm = NULL;
	const char* tail;
	int rc;

	memset(sqlStr, 0, sizeof(sqlStr));
	snprintf(sqlStr, sizeof(sqlStr) - 1,
		"insert into memdata (userid, mach_h, mach_l, port1, port2) values (?, ?, ?, ?, ?);");

	rc = sqlite3_prepare_v2(db, sqlStr, -1, &vm, &tail);
	if (rc != SQLITE_OK)
	{
		fprintf(stderr, "prepare_v2 err: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		exit(1);
	}

	return vm;
}

int end_insert(sqlite3_stmt* vm)
{
	if (vm)
		sqlite3_finalize(vm);
}

int do_insert(sqlite3* db, sqlite3_stmt* vm, int uid, int mh, int ml, int p1, int p2)
{
	int rc;

	if (!vm)
	{
		fprintf(stderr, "insert error\n");
		return 0;
	}

	int count = sqlite3_bind_parameter_count(vm);

	rc = sqlite3_bind_int(vm, 1, uid);
	if (rc != SQLITE_OK)
	{
		fprintf(stderr, "bind 1 err: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		exit(1);
	}

	rc = sqlite3_bind_int(vm, 2, mh);
	if (rc != SQLITE_OK)
	{
		fprintf(stderr, "bind 2 err: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		exit(1);
	}

	rc = sqlite3_bind_int(vm, 3, ml);
	if (rc != SQLITE_OK)
	{
		fprintf(stderr, "bind 3 err: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		exit(1);
	}

	rc = sqlite3_bind_int(vm, 4, p1);
	if (rc != SQLITE_OK)
	{
		fprintf(stderr, "bind 4 err: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		exit(1);
	}

	rc = sqlite3_bind_int(vm, 5, p2);
	if (rc != SQLITE_OK)
	{
		fprintf(stderr, "bind 5 err: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		exit(1);
	}

	rc = sqlite3_step(vm);
	if (rc != SQLITE_DONE)
	{
		fprintf(stderr, "step err: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		exit(1);
	}

	rc = sqlite3_reset(vm);
	if (rc != SQLITE_DONE && rc != SQLITE_ROW && rc != SQLITE_OK)
	{
		fprintf(stderr, "reset err: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		exit(1);
	}

	return 0;
}

int main(int argc, char** argv)
{
	sqlite3* db;
	char* errmsg = 0;
	int rc, numcols, i;
	sqlite3_stmt* vm;
	const char* tail;

	/*if (argc == 4 || argc == 5)
	{
		printf("Param1:dbname\n");
		printf("Param2:insert mode;0:no bind  1:bind\n");
		printf("Param3:trans node;0:auto 1:sqlite3_exe\n");
		printf("Param4:count\n");
	}
        */

	if (argc != 4 && argc != 5)
	{
		printf("test <uri> <mode> <trans> <count>\n");
		return;
	}

	rc = sqlite3_open(argv[1], &db);
	if (rc)
	{
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		exit(1);
	}

	char* createTable = "create table memdata (userid int, mach_h int, mach_l int, port1 int, port2 int, \
                            constraint pk_memtab primary key(userid, mach_h, mach_l))";

	rc = sqlite3_prepare_v2(db, createTable, -1, &vm, &tail);
	if (rc != SQLITE_OK)
	{
		fprintf(stderr, "prepare_v2 err: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		exit(1);
	}

	rc = sqlite3_step(vm);
	if (rc != SQLITE_DONE)
	{
		fprintf(stderr, "step err: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		exit(1);
	}

	// sqlite3_exec(db, "PRAGMA page_szie=81920", 0, 0, 0);
	sqlite3_finalize(vm);

	int uid = 1;
	int mh = 10000;
	int ml = 30000;
	int p1 = 1000;
	int p2 = 3000;

	sqlite3_commit_hook(db, commit_capture, NULL);

	int repeat = 100000;
	if (argv[3][0] > '0')
		repeat = 1000000;
	int use_trans = 0;
	if (argv[3][0] > '0')
		use_trans = 1;
	if (argc == 5)
		repeat = atoi(argv[4]);
	int each_prepare = 0;
	if (argv[2][0] > '0')
		each_prepare = 1;
	printf("repeat insert %d times, "
		"in %s, "
		"with %s\n",
		repeat,
		(each_prepare) ? "each stmt prepared" : "1 stmt prepared",
		(use_trans) ? "1 trans" : "auto trans(s)");
	if (argv[3][0] > '0')
	{
		rc = sqlite3_exec(db, "BEGIN;", NULL, NULL, &errmsg);
		if (rc != SQLITE_OK)
		{
			sqlite3_free(errmsg);
			sqlite3_close(db);
			exit(1);
		}
	}

	clock_t t = clock();
	//SYSTEMTIME curtime;
	//GetLocalTime(&curtime);
	//fprintf(stderr, "%02d:%02d:%02d\n", curtime.wHour, curtime.wMinute, curtime.wSecond);

	if (argv[2][0] == '0')
	{
		vm = prepare_insert(db);

		//insert 1000000 18√Î
		for (i = 0; i < repeat; i++)
		{
			do_insert(db, vm, uid++, mh++, ml++, p1++, p2++);
		}

		end_insert(vm);
	}

	if (argv[2][0] > '0')
		// insert 1000000 58√Î
	{
		for (i = 0; i < repeat; i++)
		{
			insert_table_data(db, uid++, mh++, ml++, p1++, p2++);
		}
	}


	//GetLocalTime(&curtime);
	//fprintf(stderr, "%02d:%02d:%02d\n", curtime.wHour, curtime.wMinute, curtime.wSecond);
	fprintf(stderr, "%5.2fs\n", (clock() - t) / ((float)CLOCKS_PER_SEC));

	if (argv[3][0] > '0')
	{
		rc = sqlite3_exec(db, "COMMIT;", NULL, NULL, &errmsg);
		if (rc != SQLITE_OK)
		{
			sqlite3_free(errmsg);
			sqlite3_close(db);
			exit(1);
		}
	}

	//GetLocalTime(&curtime);
	//fprintf(stderr, "%02d:%02d:%02d\n", curtime.wHour, curtime.wMinute, curtime.wSecond);
	fprintf(stderr, "%5.2fs\n", (clock() - t) / ((float)CLOCKS_PER_SEC));
	fprintf(stderr, "commit: %d\n", commit_capture_count);

	// getchar ();

	sqlite3_close(db);
	return 0;
}
