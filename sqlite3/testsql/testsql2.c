#include <stdio.h>   

#include <string.h>   

#include <sqlite3.h>   


/* callback�����У� 
 
 * arg: �Ǵ��������������Ĳ��� 
 
 * values: �ǲ�ѯ�����ֵ 
 
 * names: ��ѯ����е����� 
 
 */  

int wf_callback(void *arg, int nr, char **values, char **names)

{  
    
    int i;  
   
    FILE *fd;  
    
    char str[128];  
    
    fd = (FILE *)arg; //��void *�Ĳ���ǿ��ת��ΪFILE *   
    
    for (i=0; i<nr; i++) 
    { //����ѯ���д�뵽�ļ���   
        
        memset(str, '\0', 128);  
        
        sprintf(str, "\t%s\t", values[i]);  
        
        fwrite(str, sizeof(char), sizeof(str), fd);  
    
    }  
    
    memset(str, '\0', 128);  
    
    fwrite("\n", sizeof(char), 2, fd); //д��һ����¼����   
    
    return 0;  //callback������������0   

}  




int main()  

{  
    
    char sql[128];  
    
    sqlite3 *db;  
    
    FILE *fd;  


    
    sqlite3_open("test.db", &db);  //�򿪣����½���һ�����ݿ�   
    
    memset(sql, '\0', 128);  
    
    /* �½�һ�ű� */  
    
    strcpy(sql, "create table tb(id INTEGER PRIMARY KEY, data TEXT)");  
    
    sqlite3_exec(db, sql, NULL, NULL, NULL);  

 
       
    /* �½�һ���ļ��������ݿ�Ĳ�ѯ��������ڸ��ļ��� */  
    
    fd = fopen("test", "w");  
    
    fwrite("Result: \n", sizeof(char), 10, fd);  
    
    memset(sql, '\0', 128);  
    
    strcpy(sql, "select * from tb");  
    
    sqlite3_exec(db, sql, wf_callback, fd, NULL);  
    
    fclose(fd); 
 

   
     sqlite3_close(db); //�ر����ݿ�   
   
     return 0;  

} 