#include<stdio.h>
#include<stdlib.h>
#include<sqlite3.h>

int main(void)
{
    sqlite3 *db = NULL;
    char *zErrMsg = 0;
    int rc;
    rc = sqlite3_open("hello.db",&db);
    if(rc)
    {
        fprintf(stderr,"Can't open database:%s\n,sqlite3_errmsg(db)");
        sqlite3_close(db);
        exit(1);    
    }
    else
    {
    printf("You have opened a sqlite3 database named hello.db successfully!\nCongratulations!\nHave fun!\n");
    }
    sqlite3_close(db);//guanbishujuku
    return 0;
}
