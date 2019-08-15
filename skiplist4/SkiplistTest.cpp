#include<iostream>
#include<vector>
#include<cmath>
#include<time.h>
#include<algorithm>
#include<numeric>
#include"SkiplistTest.h"
using namespace std;
#define E exp(1)

//设置节点
void Skipnode::Setnode(int dataInial = 0, int levelInial = 1)
    {   
        nodeData = dataInial;
        nodeLevel = levelInial;
        while (!point.empty())
            point.pop_back();
        for (int i = 0; i < nodeLevel; i++)
        {
            point.push_back(NULL);
        }
    }
//返回要查找的点的指针，如果不存在则返回尾指针
Skipnode* Skiplist::Search(int inialNumber)
{
    Skipnode* ptr;//游标指针
    ptr = head;//初始化游标指针
    for (int j = m_level - 1; j >= 0;)
    {
        if (inialNumber == ptr->point.at(j)->nodeData)
        {
            return ptr->point.at(j);//停止搜索
        }
        else if (inialNumber < ptr->point.at(j)->nodeData)
        {
            j--;//向下搜索
        }
        else
        {
            ptr = ptr->point.at(j);//向右搜索
        }
    }
    return tail;//如果不存在则返回尾结点的指针
}
//构造函数，创建一个空跳跃表
Skiplist::Skiplist(int tailKeyInial = 2000000, int maxLevelInial = 30)
{
    m_level = 1;
    m_tailKey = tailKeyInial;
    m_maxLevel = maxLevelInial;
    head = new Skipnode(-1, m_maxLevel + 1);
    tail = new Skipnode(tailKeyInial, m_maxLevel + 1);
    for (int i = 0; i < m_maxLevel; i++)
    {
        head->point.at(i) = tail;
    }
}
Skiplist::~Skiplist()    //析构函数
{
    Clear();
    delete head;
    delete tail;
}
int Skiplist::Getlevel() 
{
    //Print();
    return m_level;
}
//清空跳跃表
void Skiplist::Clear() 
{
    if (head->point.at(0) != tail) 
    {
        Skipnode* ptr = head->point.at(0);//游标
	while (ptr->point.at(0) != tail) 
	    {
	        Skipnode* qian = ptr;
		ptr = ptr->point.at(0);
		delete qian;
	    }
	for (int i = 0; i < m_maxLevel; i++) 
	    {
	        head->point.at(i) = tail;
	    }
	m_level = 1;
    }
}
//显示跳跃表的内容
void Skiplist::Print() 
{
    for (int i = 0; i < m_level; i++) 
    {
        Skipnode* ptr;//游标
	ptr = head;
	cout << "第" << i << "层： head->";
	while (ptr->point.at(i) != tail) 
	{
	    cout << ptr->point.at(i)->nodeData << "->";
	    ptr = ptr->point.at(i);
	}
	    cout << "tail" << endl;
    }
}
//生成新点的层数，默认的概率因子为0.5
int Skiplist::Setgrade(float setgradeProbability = 0.5) 
{
    int grade = 1;
    float r;
    float m = RAND_MAX;
    while (true) 
    {
        r = rand() / m;
	if (r < setgradeProbability)
        {
            grade++;
        }
	else 
        {
            break;
        }
    }
    if (grade > m_maxLevel) grade = m_maxLevel;
    return grade;
}
//插入新点
void Skiplist::Insert(int inialNumber = 0,float insertProbability = 0.5) 
{
    int inialListLevel = Setgrade(insertProbability);
    if (m_level < inialListLevel) m_level = inialListLevel;
    Skipnode* ptr;//游标指针
    ptr = head;//初始化游标指针
    vector<Skipnode* >location;//用来存插入的位置的指针数组
    location.resize(inialListLevel);
    int j = 0;
    for (j = m_level - 1; j > inialListLevel - 1;) 
    {
        if (inialNumber < ptr->point.at(j)->nodeData)
	{
	    j--;//向下搜索
	}
	else 
	{
	    ptr = ptr->point.at(j);//向右搜索
	}
    }
    for (; j >= 0;) 
    {
	if (inialNumber < ptr->point.at(j)->nodeData) 
	{
	    location.at(j) = ptr;
	    j--;//向下搜索
	}
	else 
	    {
	        ptr = ptr->point.at(j);//向右搜索
	    }
	}
	Skipnode* insertNode;
	insertNode = new Skipnode(inialNumber, inialListLevel);
	for (int i = 0; i < inialListLevel; i++) 
	{
	    insertNode->point.at(i) = location.at(i)->point.at(i);
	    location.at(i)->point.at(i) = insertNode;
	}
}
//检查一个节点是否存在	
bool Skiplist::Exist(int inialNumber) 
{
        bool exi = false;
	Skipnode* ptr;//游标指针
	ptr = head;//初始化游标指针
	for (int j = m_level - 1; j >= 0;) 
	{
		if (inialNumber == ptr->point.at(j)->nodeData) 
		{
			exi = true;//停止搜索
			break;
		}
		else if (inialNumber < ptr->point.at(j)->nodeData) 
		{
			j--;//向下搜索
		}
		else 
		{
			ptr = ptr->point.at(j);//向右搜索
		}
	}
		return exi;
}
//删除节点
void Skiplist::Remove(int inialNumber) 
{
	Skipnode* ptr;//游标指针
	ptr = head;//初始化游标指针
	Skipnode* removeNode;
	int j = 0;
	for (j = m_level - 1; j >= 0;) 
	{
		if (inialNumber == ptr->point.at(j)->nodeData) 
		{
			removeNode = ptr->point.at(j);
			ptr->point.at(j) = ptr->point.at(j)->point.at(j);
			j--;//停止搜索
		}
		else if (inialNumber < ptr->point.at(j)->nodeData) 
		{
			j--;//向下搜索
		}
		else 
		{
			ptr = ptr->point.at(j);//向右搜索
		}
	}
	delete removeNode;
	for (j = m_level - 1; j >= 0; j--) 
	{
		if (head->point.at(j) == tail)
			m_level--;
		else break;
	}
}

int main() 
{
    vector<double>insertTime, searchTime, removeTime;
    vector<int>listLevel;
    float p = 1.0 / E;//概率因子
    int testTimes = 1;//测试次数
    int nodeNumber = 1000000;//跳跃表的节点总数
    int i = 0;
    for (int j = 1; j <= testTimes; j++) 
    {
        Skiplist list;
	srand((int)time(NULL));
	vector<int>number;
	for (i = 1; i <= nodeNumber; i++) 
        {
	    number.push_back(i);
	}
	random_shuffle(number.begin(), number.end());//create number from 1 to n
	double start, end, cost;
	start = clock();
	for (i = 0; i < number.size(); i++) 
        {
	    list.Insert(number.at(i), p);
	}
	end = clock();
	cost = end - start;
	//cout<<"insert time cost"<<cost<<" ms"<<endl;
	//cout<<"level of skip list:"<<list.getlevel()<<"level"<<endl;
	insertTime.push_back(cost);
	listLevel.push_back(list.Getlevel());
	random_shuffle(number.begin(), number.end());//create number from 1 to n
	start = clock();
	for (i = 0; i < number.size(); i++) 
        {
	    list.Search(number.at(i));
	}
	end = clock();
	cost = end - start;
	//cout<<"search time cost "<<cost<<" ms"<<endl;
	searchTime.push_back(cost);
	random_shuffle(number.begin(), number.end());//create number from 1 to n
	start = clock();
	for (i = 0; i < number.size(); i++) 
        {
	    list.Remove(number.at(i));
	}
	    end = clock();
	    cost = end - start;
	    //cout<<"delete time cost "<<cost<<" ms"<<endl;
	    removeTime.push_back(cost);
	}
	double insertTimeMean, searchTimeMean, removeTimeMean, levelMean;
	double zero = 0;
	double size = testTimes;
	insertTimeMean = accumulate(insertTime.begin(), insertTime.end(), zero) / size;
	levelMean = accumulate(listLevel.begin(), listLevel.end(), zero) / size;
	searchTimeMean = accumulate(searchTime.begin(), searchTime.end(), zero) / size;
	removeTimeMean = accumulate(removeTime.begin(), removeTime.end(), zero) / size;
	cout << "probility = " << p << endl;
        cout << "nodenumber = "<< nodeNumber << endl;
	cout << "test " << testTimes << " times" << endl;
	cout << "mean insert time " << insertTimeMean << " us" << endl;
	cout << "mean skip level " << levelMean << " times" << endl;
	cout << "mean search time " << searchTimeMean << " us" << endl;
	cout << "mean remove time " << removeTimeMean << " us" << endl;
	return 0;
}
