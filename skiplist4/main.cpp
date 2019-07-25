#include<iostream>
#include<vector>
#include<cmath>
#include<time.h>
#include<algorithm>
#include<numeric>
#include"skiplist.h"
using namespace std;
#define E exp(1)

//获取当前跳跃表的层数
int Skiplist::getlevel() 
{
    //print();
    return level;
}
//清空跳跃表
void Skiplist::clear() 
{
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
//显示跳跃表的内容
void Skiplist::print() 
{
    for (int i = 0; i < level; i++) 
    {
        Skipnode* ptr;//游标
	ptr = head;
	cout << "第" << i << "层： head->";
	while (ptr->p.at(i) != tail) 
	{
	    cout << ptr->p.at(i)->data << "->";
	    ptr = ptr->p.at(i);
	}
	    cout << "tail" << endl;
    }
}
//生成新点的层数，默认的概率因子为0.5
int Skiplist::setgrade(float p = 0.5) 
{
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
//插入新点
void Skiplist::insert(int indata = 0,float p2 = 0.5) 
{
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
	{
	    kk--;//向下搜索
	}
	else 
	{
	    ptr = ptr->p.at(kk);//向右搜索
	}
    }
    for (; kk >= 0;) 
    {
	if (indata < ptr->p.at(kk)->data) 
	{
	    location.at(kk) = ptr;
	    kk--;//向下搜索
	}
	else 
	    {
	        ptr = ptr->p.at(kk);//向右搜索
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
//检查一个节点是否存在	
bool Skiplist::exist(int indata) 
{
        bool exi = false;
	Skipnode* ptr;//游标指针
	ptr = head;//初始化游标指针
	for (int kk = level - 1; kk >= 0;) 
	{
		if (indata == ptr->p.at(kk)->data) 
		{
			exi = true;//停止搜索
			break;
		}
		else if (indata < ptr->p.at(kk)->data) 
		{
			kk--;//向下搜索
		}
		else 
		{
			ptr = ptr->p.at(kk);//向右搜索
		}
	}
		return exi;
}
//删除节点
void Skiplist::remove(int indata) 
{
	Skipnode* ptr;//游标指针
	ptr = head;//初始化游标指针
	Skipnode* d1;
	int kk = 0;
	for (kk = level - 1; kk >= 0;) 
	{
		if (indata == ptr->p.at(kk)->data) 
		{
			d1 = ptr->p.at(kk);
			ptr->p.at(kk) = ptr->p.at(kk)->p.at(kk);
			kk--;//停止搜索
		}
		else if (indata < ptr->p.at(kk)->data) 
		{
			kk--;//向下搜索
		}
		else 
		{
			ptr = ptr->p.at(kk);//向右搜索
		}
	}
	delete d1;
	for (kk = level - 1; kk >= 0; kk--) 
	{
		if (head->p.at(kk) == tail)
			level--;
		else break;
	}
}

/*Skipnode* search(int indata)
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
*/

int main() 
{
    vector<double>inserttime, searchtime, removetime;
    vector<int>levellist;
    float p = 1.0 / E;//概率因子
    int ntime = 100;//测试次数
    int nodenumber = 100000;//跳跃表的节点总数
    int i = 0;
    for (int kk = 1; kk <= ntime; kk++) 
    {
        Skiplist list;
	srand((int)time(NULL));
	vector<int>number;
	for (i = 1; i <= nodenumber; i++) 
        {
	    number.push_back(i);
	}
	random_shuffle(number.begin(), number.end());//create number from 1 to n
	double start, end, cost;
	start = clock();
	for (i = 0; i < number.size(); i++) 
        {
	    list.insert(number.at(i), p);
	}
	end = clock();
	cost = end - start;
	//cout<<"insert time cost"<<cost<<" ms"<<endl;
	//cout<<"level of skip list:"<<list.getlevel()<<"level"<<endl;
	inserttime.push_back(cost);
	levellist.push_back(list.getlevel());
	random_shuffle(number.begin(), number.end());//create number from 1 to n
	start = clock();
	for (i = 0; i < number.size(); i++) 
        {
	    list.search(number.at(i));
	}
	end = clock();
	cost = end - start;
	//cout<<"search time cost "<<cost<<" ms"<<endl;
	searchtime.push_back(cost);
	random_shuffle(number.begin(), number.end());//create number from 1 to n
	start = clock();
	for (i = 0; i < number.size(); i++) 
        {
	    list.remove(number.at(i));
	}
	    end = clock();
	    cost = end - start;
	    //cout<<"delete time cost "<<cost<<" ms"<<endl;
	    removetime.push_back(cost);
	}
	double inserttimemean, searchtimemean, removetimemean, levelmean;
	double zero = 0;
	double size = ntime;
	inserttimemean = accumulate(inserttime.begin(), inserttime.end(), zero) / size;
	levelmean = accumulate(levellist.begin(), levellist.end(), zero) / size;
	searchtimemean = accumulate(searchtime.begin(), searchtime.end(), zero) / size;
	removetimemean = accumulate(removetime.begin(), removetime.end(), zero) / size;
	cout << "probility = " << p << endl;
	cout << "test " << ntime << " times" << endl;
	cout << "mean insert time " << inserttimemean << " ms" << endl;
	cout << "mean skip level " << levelmean << " times" << endl;
	cout << "mean search time " << searchtimemean << " ms" << endl;
	cout << "mean remove time " << removetimemean << " ms" << endl;
	return 0;
}
