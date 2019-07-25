#include<vector>
#include<iostream>
#include<stdlib.h> 
#include<time.h> 
#include<cmath>
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
    void setnode(int, int);//设置数据成员，设置数组p的长度并在里面赋空值     
};


class Skiplist
{
public:
    Skiplist(int, int);//构造函数，创建一个空跳跃表
    ~Skiplist();//析构函数
    int getlevel();//获取当前跳跃表的层数
    void clear();//清空跳跃表
    void print();//显示跳跃表的内容
    int setgrade(float);//生成新点的层数，默认的概率因子为0.5
    void insert(int, float);//插入新点
    Skipnode* search(int);//返回要查找的点的指针，如果不存在则返回尾指针
    bool exist(int);//检查一个点是否存在
    void remove(int);//删除结点
private:
    int level, maxlevel;
    int tailkey;
    Skipnode* head;
    Skipnode* tail;
};
