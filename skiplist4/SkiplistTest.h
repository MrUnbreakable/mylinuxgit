#include<vector>
#include<iostream>
#include<stdlib.h> 
#include<time.h> 
#include<cmath>
using namespace std;

//构造跳跃表节点结构
struct Skipnode
{
    int nodeData;//节点的值
    int nodeLevel;//节点层数
    vector<Skipnode* >point;//存储节点指针的数组
    Skipnode(int dataInial = 0, int levelInial = 1)
    {
        Setnode(dataInial, levelInial);
    }
    void Setnode(int, int);//设置数据成员，设置数组p的长度并在里面赋空值     
};


class Skiplist
{
public:
    Skiplist(int, int);//构造函数，创建一个空跳跃表
    ~Skiplist();//析构函数
    int Getlevel();//获取当前跳跃表的层数
    void Clear();//清空跳跃表
    void Print();//显示跳跃表的内容
    int Setgrade(float);//生成新点的层数，默认的概率因子为0.5
    void Insert(int, float);//插入新点
    Skipnode* Search(int);//返回要查找的点的指针，如果不存在则返回尾指针
    bool Exist(int);//检查一个点是否存在
    void Remove(int);//删除结点
private:
    int m_level, m_maxLevel;
    int m_tailKey;
    Skipnode* head;
    Skipnode* tail;
};
