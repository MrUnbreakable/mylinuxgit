#include<vector>
#include<iostream>
#include <stdlib.h> 
#include <time.h> 
#include <cmath>
//#include "skipnode.h"
using namespace std;

//the struct of a node
struct Skipnode
{
    int data;//the value of node
    int level;//the level of node
    vector<Skipnode* >p;//pointer of the node
    Skipnode(int datain = 0, int levelin = 1)
    {
        setnode(datain, levelin);
    }
    //set the member of the node
    void setnode(int datain = 0, int levelin = 1)
    {
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


class Skiplist
{
    int level, maxlevel;
    int tailkey;
    Skipnode* head;
    Skipnode* tail;
public:
    Skiplist(int tailkeyin = 2000, int inmaxlevel = 30) 
    {//构造函数，构造一个空跳跃表
        level = 1;
        //cout <<"Hello World" <<"\n" ;
        tailkey = tailkeyin;
        maxlevel = inmaxlevel;
        head = new Skipnode(-1, maxlevel + 1);
        tail = new Skipnode(tailkeyin, maxlevel + 1);
        for (int i = 0; i < maxlevel; i++) 
        {
            head->p.at(i) = tail;
        }    
    }
    ~Skiplist() 
    {//析构函数
        //cout <<"~skiplist" << "\n";
	//getlevel();
	//print();
	clear();
	delete head;
	delete tail;
    }
    int getlevel() 
    {//获取当前跳跃表的层数
        print();
	return level;
    }
    void clear() 
    {//清空跳跃表
        //cout <<"clear" << "\n";
	if (head->p.at(0) != tail) 
        {
	    Skipnode* ptr = head->p.at(0);//游标
	    while (ptr->p.at(0) != tail) 
            {
	        Skipnode* qian = ptr;
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
    {//显示跳跃表的内容
        //cout <<"print" << "\n";
	//cout << level << "\n";
	for (int i = 0; i < level; i++) 
        {
	    Skipnode* ptr;//游标
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
    {//生成新点的层数，默认的概率因子为0.5
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
    {//插入新点
        int inlev = setgrade(p2);
	if (level < inlev) level = inlev;
	Skipnode* ptr;//游标指针
	ptr = head;//初始化游标指针
	vector<Skipnode* >location;//用来存插入的位置的指针数组
	location.resize(inlev);
	int kk = 0;
	for (kk = level - 1; kk > inlev - 1;) 
        {
	    if (indata < ptr->p.at(kk)->data) 
            {//向下搜索
	        kk--;
	    }
	    else 
            {//向右搜索
	        ptr = ptr->p.at(kk);
	    }
        }
	for (; kk >= 0;) 
        {
	    if (indata < ptr->p.at(kk)->data) 
            {//向下搜索
	        location.at(kk) = ptr;
		kk--;
	    }
	    else 
            {//向右搜索
	        ptr = ptr->p.at(kk);
	    }
        }
	Skipnode* n1;
	n1 = new Skipnode(indata, inlev);
	for (int i = 0; i < inlev; i++) 
        {
	    n1->p.at(i) = location.at(i)->p.at(i);
	    location.at(i)->p.at(i) = n1;
        }
    }
    bool exist(int indata) 
    {//检查一个点是否存在
        bool exi = false;
	Skipnode* ptr;//游标指针
	ptr = head;//初始化游标指针
	for (int kk = level - 1; kk >= 0;) 
        {
	    if (indata == ptr->p.at(kk)->data) 
            {//停止搜索
	        exi = true;
		break;
	    }
	    else if (indata < ptr->p.at(kk)->data) 
            {//向下搜索
	        kk--;
	    }
	    else
            {//向右搜索
	        ptr = ptr->p.at(kk);
	    }
	}
		return exi;
    }
    Skipnode* search(int indata) 
    {//返回要查找的点的指针，如果不存在则返回尾指针
        Skipnode* ptr;//游标指针
	ptr = head;//初始化游标指针
	for (int kk = level - 1; kk >= 0;) 
        {
	    if (indata == ptr->p.at(kk)->data) 
            {//停止搜索
	        return ptr->p.at(kk);
	    }
	    else if (indata < ptr->p.at(kk)->data) 
            {//向下搜索
		kk--;
	    }
	    else 
            {//向右搜索
	        ptr = ptr->p.at(kk);
	    }
        }//如果不存在则返回尾结点的指针
	return tail;
    }
    void remove(int indata) 
    {//删除结点
        Skipnode* ptr;//游标指针
	ptr = head;//初始化游标指针
	Skipnode* d1;
	int kk = 0;
	for (kk = level - 1; kk >= 0;) 
        {
	    if (indata == ptr->p.at(kk)->data) 
            {//停止搜索
                d1 = ptr->p.at(kk);
		ptr->p.at(kk) = ptr->p.at(kk)->p.at(kk);// 
		kk--;
	    }
	    else if (indata < ptr->p.at(kk)->data) 
            {//向下搜索
		kk--;
	    }
	    else 
            {//向右搜索
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
