#include<vector>
#include<iostream>
#include <stdlib.h> 
#include <time.h> 
#include <cmath>
//#include "skipnode.h"
using namespace std;

struct skipnode//±í???????á?????á????
{
    int data;//????????
    int level;//????
    vector<skipnode* >p;//???á??????????×é
    skipnode(int datain = 0, int levelin = 1)
    {//???ì????
        setnode(datain, levelin);
    }
    void setnode(int datain = 0, int levelin = 1)
    {//?è?????????±???è????×ép???¤????????????????
        data = datain;
        level = levelin;
        while (!p.empty())
            p.pop_back();
        for (int i = 0; i < level; i++) 
        {   
            p.push_back(NULL);
        }   
    }      
};


class skiplist
{
    int level, maxlevel;
    int tailkey;
    skipnode* head;
    skipnode* tail;
public:
    skiplist(int tailkeyin = 2000, int inmaxlevel = 30) 
    {//¹¹Ôìº¯Êı£¬¹¹ÔìÒ»¸ö¿ÕÌøÔ¾±í
        level = 1;
        //cout <<"Hello World" <<"\n" ;
        tailkey = tailkeyin;
        maxlevel = inmaxlevel;
        head = new skipnode(-1, maxlevel + 1);
        tail = new skipnode(tailkeyin, maxlevel + 1);
        for (int i = 0; i < maxlevel; i++) 
        {
            head->p.at(i) = tail;
        }    
    }
    ~skiplist() 
    {//Îö¹¹º¯Êı
        //cout <<"~skiplist" << "\n";
	//getlevel();
	//print();
	clear();
	delete head;
	delete tail;
    }
    int getlevel() 
    {//»ñÈ¡µ±Ç°ÌøÔ¾±íµÄ²ãÊı
        print();
	return level;
    }
    void clear() 
    {//Çå¿ÕÌøÔ¾±í
        //cout <<"clear" << "\n";
	if (head->p.at(0) != tail) 
        {
	    skipnode* ptr = head->p.at(0);//ÓÎ±ê
	    while (ptr->p.at(0) != tail) 
            {
	        skipnode* qian = ptr;
		ptr = ptr->p.at(0);
		delete qian;
	    }
	for (int i = 0; i < maxlevel; i++) 
        {
	    head->p.at(i) = tail;
	}
	level = 1;
		}
	}
    void print() 
    {//ÏÔÊ¾ÌøÔ¾±íµÄÄÚÈİ
        //cout <<"print" << "\n";
	//cout << level << "\n";
	for (int i = 0; i < level; i++) 
        {
	    skipnode* ptr;//ÓÎ±ê
	    ptr = head;
	    cout << "No" << i << "level  head->";
	    while (ptr->p.at(i) != tail) 
            {
	        cout << ptr->p.at(i)->data << "->";
		ptr = ptr->p.at(i);
	    }
	    cout << "tail" << endl;
	}
    }
    int setgrade(float p = 0.5) 
    {//Éú³ÉĞÂµãµÄ²ãÊı£¬Ä¬ÈÏµÄ¸ÅÂÊÒò×ÓÎª0.5
        //cout <<"set grade" << "\n";
	int grade = 1;
	float r;
	float m = RAND_MAX;
	while (true) 
        {
	    r = rand() / m;
	    if (r < p)
	    {
                grade++;
            }
	    else 
            {
            break;
            }
	}
	if (grade > maxlevel) grade = maxlevel;
	return grade;
    }
    void insert(int indata = 0, float p2 = 0.5) 
    {//²åÈëĞÂµã
        int inlev = setgrade(p2);
	if (level < inlev) level = inlev;
	skipnode* ptr;//ÓÎ±êÖ¸Õë
	ptr = head;//³õÊ¼»¯ÓÎ±êÖ¸Õë
	vector<skipnode* >location;//ÓÃÀ´´æ²åÈëµÄÎ»ÖÃµÄÖ¸ÕëÊı×é
	location.resize(inlev);
	int kk = 0;
	for (kk = level - 1; kk > inlev - 1;) 
        {
	    if (indata < ptr->p.at(kk)->data) 
            {//ÏòÏÂËÑË÷
	        kk--;
	    }
	    else 
            {//ÏòÓÒËÑË÷
	        ptr = ptr->p.at(kk);
	    }
        }
	for (; kk >= 0;) 
        {
	    if (indata < ptr->p.at(kk)->data) 
            {//ÏòÏÂËÑË÷
	        location.at(kk) = ptr;
		kk--;
	    }
	    else 
            {//ÏòÓÒËÑË÷
	        ptr = ptr->p.at(kk);
	    }
        }
	skipnode* n1;
	n1 = new skipnode(indata, inlev);
	for (int i = 0; i < inlev; i++) 
        {
	    n1->p.at(i) = location.at(i)->p.at(i);
	    location.at(i)->p.at(i) = n1;
        }
    }
    bool exist(int indata) 
    {//¼ì²éÒ»¸öµãÊÇ·ñ´æÔÚ
        bool exi = false;
	skipnode* ptr;//ÓÎ±êÖ¸Õë
	ptr = head;//³õÊ¼»¯ÓÎ±êÖ¸Õë
	for (int kk = level - 1; kk >= 0;) 
        {
	    if (indata == ptr->p.at(kk)->data) 
            {//Í£Ö¹ËÑË÷
	        exi = true;
		break;
	    }
	    else if (indata < ptr->p.at(kk)->data) 
            {//ÏòÏÂËÑË÷
	        kk--;
	    }
	    else
            {//ÏòÓÒËÑË÷
	        ptr = ptr->p.at(kk);
	    }
	}
		return exi;
    }
    skipnode* search(int indata) 
    {//·µ»ØÒª²éÕÒµÄµãµÄÖ¸Õë£¬Èç¹û²»´æÔÚÔò·µ»ØÎ²Ö¸Õë
        skipnode* ptr;//ÓÎ±êÖ¸Õë
	ptr = head;//³õÊ¼»¯ÓÎ±êÖ¸Õë
	for (int kk = level - 1; kk >= 0;) 
        {
	    if (indata == ptr->p.at(kk)->data) 
            {//Í£Ö¹ËÑË÷
	        return ptr->p.at(kk);
	    }
	    else if (indata < ptr->p.at(kk)->data) 
            {//ÏòÏÂËÑË÷
		kk--;
	    }
	    else 
            {//ÏòÓÒËÑË÷
	        ptr = ptr->p.at(kk);
	    }
        }//Èç¹û²»´æÔÚÔò·µ»ØÎ²½áµãµÄÖ¸Õë
	return tail;
    }
    void remove(int indata) 
    {//É¾³ı½áµã
        skipnode* ptr;//ÓÎ±êÖ¸Õë
	ptr = head;//³õÊ¼»¯ÓÎ±êÖ¸Õë
	skipnode* d1;
	int kk = 0;
	for (kk = level - 1; kk >= 0;) 
        {
	    if (indata == ptr->p.at(kk)->data) 
            {//Í£Ö¹ËÑË÷
                d1 = ptr->p.at(kk);
		ptr->p.at(kk) = ptr->p.at(kk)->p.at(kk);// 
		kk--;
	    }
	    else if (indata < ptr->p.at(kk)->data) 
            {//ÏòÏÂËÑË÷
		kk--;
	    }
	    else 
            {//ÏòÓÒËÑË÷
		ptr = ptr->p.at(kk);
	    }
	}
	delete d1;
	for (kk = level - 1; kk >= 0; kk--) 
        {
	    if (head->p.at(kk) == tail) 
            {
                level--;
            }
	    else 
            {
                break;
            }
        }
    }
};
