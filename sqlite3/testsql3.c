#include <stdio.h>

#include <sqlite3.h>

#include <stdlib.h>
 

void create_table(sqlite3 *db)

{
    
    char *sql;
    
    char *errmsg;
    
    int ret;
 
	
    sql = "create table if not exists mytable (id integer primary key,name text);";
 
	
    ret = sqlite3_exec(db,sql,NULL,NULL,&errmsg);
 
	
    if(ret != SQLITE_OK)
	
    {
		
        printf("create table error : %s\n",errmsg);
		
        exit(-1);
	
    }

}
 


void insert_record(sqlite3 *db)

{
    
    char sql[100];
    
    char *errmsg;
    
    int ret;
	
    int id;
	
    char name[20];
 
	
    printf("please input id and name:\n");
 
	
    scanf("%d%s",&id,name);
 
	
    sprintf(sql,"insert into mytable (id,name)values(%d,'%s');",id,name);
 
	
    ret = sqlite3_exec(db,sql,NULL,NULL,&errmsg);
 
	
    if(ret != SQLITE_OK)
	
    {
		
        printf("insert record  error : %s\n",errmsg);
		
        exit(-1);
	
    }

#if 0	
	
    sql = "insert into mytable (id,name)values(NULL,'zhang');";
 
	
    ret = sqlite3_exec(db,sql,NULL,NULL,&errmsg);
 
	
    if(ret != SQLITE_OK)
	
    {
		
        printf("insert record  error : %s\n",errmsg);
		
        exit(-1);
	
    }
	
	
    sql = "insert into mytable (id,name)values(NULL,'lin');";
 
	
    ret = sqlite3_exec(db,sql,NULL,NULL,&errmsg);
 
	
    if(ret != SQLITE_OK)
	
    {
		
        printf("insert record  error : %s\n",errmsg);
		
        exit(-1);
	
    }

#endif

}
 


int displaycb(void *para,int ncolumn,char ** columnvalue,char *columnname[])

{
	
    int i;	
    printf("total column is %d\n",ncolumn);
 
	
    for(i = 0;i < ncolumn; i++)
	
    {
		
        printf("col_name:%s----> clo_value:%s\n",columnname[i],columnvalue[i]);
	
    }
	
    printf("===========================\n");
 
	
    return 0;

}
 


void inquire_usecb(sqlite3 * db)

{
    
    char *sql;
    
    char *errmsg;
    
    int ret;
 
	
    sql = "select * from mytable;";
 
	
    ret = sqlite3_exec(db,sql,displaycb,NULL,&errmsg);
 
	
    if(ret != SQLITE_OK)
	
    {
		
        printf("select error : %s\n",errmsg);
		
        exit(-1);
	
    }
 

}
 


        void inquire_nocb(sqlite3 *db)

{
    
    int nrow,ncolumn;
	
    char **azresult;
	
    char *sql;
	
    char *errmsg;
	
    int ret;
	
    int i;
 
	
    sql = "select * from mytable;";
 
    
    ret = sqlite3_get_table(db,sql,&azresult,&nrow,&ncolumn,&errmsg);
 
    
    if(ret != SQLITE_OK)
	
    {
		
        printf("get table error:%s",errmsg);
		
        exit(-1);
	
    }
 
	
    printf("nrow = %d,column = %d\n",nrow,ncolumn);

 
	
    sqlite3_free_table(azresult);

}
 

int main()
{
    sqlite3 *db;
    int ret;
    ret = sqlite3_open("mydatabase.db",&db);
    if(ret != SQLITE_OK)
    {
        printf("open database error : %s\n",sqlite3_errmsg(db));
        exit(-1);
    }
    else
    {
        printf("you have opened a database succefully!\n");
    }
    create_table(db);
    insert_record(db);
    inquire_usecb(db);
    inquire_nocb(db);
    sqlite3_close(db);
    return 0;

}
