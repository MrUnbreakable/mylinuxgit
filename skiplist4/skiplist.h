#include<vector>
#include<iostream>
#include <stdlib.h> 
#include <time.h> 
#include <cmath>
//#include "skipnode.h"
using namespace std;

//构造跳跃表节点结构
struct Skipnode
{
    int data;//节点的值
    int level;//节点层数
    vector<Skipnode* >p;//存储节点指针
    Skipnode(int datain = 0, int levelin = 1)
    {
        setnode(datain, levelin);
    }
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
public:
    Skiplist(int tailkeyin = 1000000, int inmaxlevel = 30)
    {//构造函数，构造一个空跳跃表
	level = 1;
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
        clear();
	delete head;
	delete tail;
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
    int getlevel();
    void clear();
    void print();
    int setgrade(float);
    void insert(int, float); 
    bool exist(int);
    void remove(int);
private:
    int level, maxlevel;
    int tailkey;
    Skipnode* head;
    Skipnode* tail;
};
