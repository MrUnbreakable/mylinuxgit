#include <stdio.h>
#include <stdlib.h>
#include<sys/time.h>
#include "sqlite3.h" 
#define _DEBUG_
int main(void)
{
	sqlite3* db = NULL;
	char* zErrMsg = 0;
	int rc;
	//rc = sqlite3_open("hello.db", &db); //��ָ�������ݿ��ļ�,��������ڽ�����һ��ͬ�������ݿ��ļ�
	rc = sqlite3_open("hello.db", &db); //��ָ�������ݿ��ļ�,��������ڽ�����һ��ͬ�������ݿ��ļ�
	if (rc)
	{
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return 0;
	}
	else
	{
		printf("You have opened a sqlite3 database named hello.db successfully!\nCongratulations!\n");
	}//����һ����,����ñ���ڣ��򲻴�������������ʾ��Ϣ���洢�� zErrMsg ��
	char* sql = " CREATE TABLE StudentInformation(ID INTEGER PRIMARY KEY,SensorID INTEGER,Name VARCHAR,Sex TEXT CHECK(Sex In('M','F')),Country TEXT,Height REAL);";
	sqlite3_exec(db, sql, 0, 0, &zErrMsg);
#ifdef _DEBUG_
	printf("zErrMsg = %s \n", zErrMsg);
#endif

	//�������� 
	struct timeval start;
	struct timeval end;
	unsigned long timer;
        int i;
	sql = "INSERT INTO \"StudentInformation\" VALUES(NULL,1,'zhang san','M','China',1.76 ); ";
	sqlite3_exec(db, sql, 0, 0, &zErrMsg);

	sql = "INSERT INTO \"StudentInformation\" VALUES(NULL ,2,'li si','M','France',1.85 );";
	sqlite3_exec(db, sql, 0, 0, &zErrMsg);

	sql = "INSERT INTO \"StudentInformation\" VALUES(NULL ,3,'wang wu','F','America',1.66);";
	sqlite3_exec(db, sql, 0, 0, &zErrMsg);
	gettimeofday(&start, NULL);
	for (i = 0; i < 10000; i++)
	{
		sql = "INSERT INTO \"StudentInformation\" VALUES(NULL,1,'xiao zhang','F','China',1.70 ); ";
		sqlite3_exec(db, sql, 0, 0, &zErrMsg);
	}
	gettimeofday(&end, NULL);
	timer = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;
	int nrow = 0, ncolumn = 0;
	char** azResult; //��ά�����Ž��
	//��ѯ����
	sql = "SELECT * FROM StudentInformation ";
	sqlite3_get_table(db, sql, &azResult, &nrow, &ncolumn, &zErrMsg);
	/*printf("row:%d column=%d \n", nrow, ncolumn);
	printf("\nThe result of querying is : \n");
	for (i = 0; i < (nrow + 1) * ncolumn; i++)
		printf("azResult[%d] = %s\n", i, azResult[i]);
	*/
	//ɾ������
	sql = "DELETE FROM StudentInformation WHERE SensorID = 1 OR SensorID = 2;";
	sqlite3_exec(db, sql, 0, 0, &zErrMsg);
#ifdef _DEBUG_
	printf("zErrMsg = %s \n", zErrMsg);
#endif
	sql = "SELECT * FROM StudentInformation ";
	sqlite3_get_table(db, sql, &azResult, &nrow, &ncolumn, &zErrMsg);
	/*printf("\n\n\n\nrow:%d column=%d ", nrow, ncolumn);
	printf("\nAfter deleting , the result of querying is : \n");
	for (i = 0; i < (nrow + 1) * ncolumn; i++)
		printf("azResult[%d] = %s\n", i, azResult[i]);
	*/
	//�ͷŵ� azResult ���ڴ�ռ�
	sqlite3_free_table(azResult);
         printf("timer = %ld us\n", timer);

#ifdef _DEBUG_
	printf("zErrMsg = %s \n", zErrMsg);
#endif
	sqlite3_close(db); //�ر����ݿ�
	return 0;

}
