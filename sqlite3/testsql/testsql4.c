#include <stdio.h>
#include <stdlib.h>
#include "sqlite3.h" 
#define _DEBUG_
int main( void )
{
    sqlite3 *db=NULL;
    char *zErrMsg = 0;
    int rc;
    int i = 0;
    rc = sqlite3_open("hello.db", &db); //��ָ�������ݿ��ļ�,��������ڽ�����һ��ͬ�������ݿ��ļ�
    if( rc )
    {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 0;
    }
    else
    {
        printf("You have opened a sqlite3 database named hello.db successfully!\nCongratulations! Have fun ! ^-^ \n");
    } 
//����һ����,����ñ���ڣ��򲻴�������������ʾ��Ϣ���洢�� zErrMsg ��
    char *sql = " CREATE TABLE SensorData(ID INTEGER PRIMARY KEY,SensorID INTEGER,SiteNum INTEGER,Time VARCHAR(12),SensorParameter REAL);" ;
    sqlite3_exec( db , sql , 0 , 0 , &zErrMsg );

    #ifdef _DEBUG_
        printf("zErrMsg = %s \n", zErrMsg);
    #endif

//�������� 
    for(i = 0; i < 10000; i++)
    {
    sql = "INSERT INTO \"SensorData\" VALUES(NULL , 1 , 1 , '201609121301', 18.9 );" ;
    sqlite3_exec( db , sql , 0 , 0 , &zErrMsg );
    }

    sql = "INSERT INTO \"SensorData\" VALUES(NULL , 23 , 45 , '201609121302', 16.4 );" ;
    sqlite3_exec( db , sql , 0 , 0 , &zErrMsg );

    sql = "INSERT INTO \"SensorData\" VALUES(NULL , 34 , 45 , '201609121303', 15.4 );" ;
    sqlite3_exec( db , sql , 0 , 0 , &zErrMsg );


    int nrow = 0, ncolumn = 0;
    char **azResult; //��ά�����Ž��
//��ѯ����
    sql = "SELECT * FROM SensorData ";
    sqlite3_get_table( db , sql , &azResult , &nrow , &ncolumn , &zErrMsg );
    printf( "row:%d column=%d \n" , nrow , ncolumn );
    printf( "\nThe result of querying is : \n" );
    for( i=0 ; i<( nrow + 1 ) * ncolumn ; i++ )
    printf( "azResult[%d] = %s\n", i , azResult[i] );
//ɾ������
    sql = "DELETE FROM SensorData WHERE SensorID = 1 ;" ;
sqlite3_exec( db , sql , 0 , 0 , &zErrMsg );
    #ifdef _DEBUG_
        printf("zErrMsg = %s \n", zErrMsg);
    #endif
    sql = "SELECT * FROM SensorData ";
    sqlite3_get_table( db , sql , &azResult , &nrow , &ncolumn , &zErrMsg );
    printf( "\n\n\n\nrow:%d column=%d " , nrow , ncolumn );
    printf( "\nAfter deleting , the result of querying is : \n" );
    for( i=0 ; i<( nrow + 1 ) * ncolumn ; i++ )
    printf( "azResult[%d] = %s\n", i , azResult[i] );

//�ͷŵ� azResult ���ڴ�ռ�
    sqlite3_free_table( azResult );

    #ifdef _DEBUG_
        printf("zErrMsg = %s \n", zErrMsg);
    #endif
    sqlite3_close(db); //�ر����ݿ�
    return 0;
}
