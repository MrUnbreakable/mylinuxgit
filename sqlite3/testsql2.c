#include <stdio.h>   

#include <string.h>   

#include <sqlite3.h>   


/* callback函数中： 
 
 * arg: 是从主函数传进来的参数 
 
 * values: 是查询结果的值 
 
 * names: 查询结果列的名字 
 
 */  

int wf_callback(void *arg, int nr, char **values, char **names)

{  
    
    int i;  
   
    FILE *fd;  
    
    char str[128];  
    
    fd = (FILE *)arg; //将void *的参数强制转换为FILE *   
    
    for (i=0; i<nr; i++) 
    { //将查询结果写入到文件中   
        
        memset(str, '\0', 128);  
        
        sprintf(str, "\t%s\t", values[i]);  
        
        fwrite(str, sizeof(char), sizeof(str), fd);  
    
    }  
    
    memset(str, '\0', 128);  
    
    fwrite("\n", sizeof(char), 2, fd); //写完一条记录换行   
    
    return 0;  //callback函数正常返回0   

}  




int main()  

{  
    
    char sql[128];  
    
    sqlite3 *db;  
    
    FILE *fd;  


    
    sqlite3_open("test.db", &db);  //打开（或新建）一个数据库   
    
    memset(sql, '\0', 128);  
    
    /* 新建一张表 */  
    
    strcpy(sql, "create table tb(id INTEGER PRIMARY KEY, data TEXT)");  
    
    sqlite3_exec(db, sql, NULL, NULL, NULL);  

 
       
    /* 新建一个文件，把数据库的查询结果保存在该文件中 */  
    
    fd = fopen("test", "w");  
    
    fwrite("Result: \n", sizeof(char), 10, fd);  
    
    memset(sql, '\0', 128);  
    
    strcpy(sql, "select * from tb");  
    
    sqlite3_exec(db, sql, wf_callback, fd, NULL);  
    
    fclose(fd); 
 

   
     sqlite3_close(db); //关闭数据库   
   
     return 0;  

} 