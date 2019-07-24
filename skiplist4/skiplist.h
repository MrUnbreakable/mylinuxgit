#include<vector>
#include<iostream>
#include <stdlib.h> 
#include <time.h> 
#include <cmath>
//#include "skipnode.h"
using namespace std;

struct skipnode//��???????�?????�????
{
    int data;//????????
    int level;//????
    vector<skipnode* >p;//???�??????????��
    skipnode(int datain = 0, int levelin = 1)
    {//???�????
        setnode(datain, levelin);
    }
    void setnode(int datain = 0, int levelin = 1)
    {//?�?????????�???�????��p???�????????????????
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
    {//���캯��������һ������Ծ��
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
    {//��������
        //cout <<"~skiplist" << "\n";
	//getlevel();
	//print();
	clear();
	delete head;
	delete tail;
    }
    int getlevel() 
    {//��ȡ��ǰ��Ծ��Ĳ���
        print();
	return level;
    }
    void clear() 
    {//�����Ծ��
        //cout <<"clear" << "\n";
	if (head->p.at(0) != tail) 
        {
	    skipnode* ptr = head->p.at(0);//�α�
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
    {//��ʾ��Ծ�������
        //cout <<"print" << "\n";
	//cout << level << "\n";
	for (int i = 0; i < level; i++) 
        {
	    skipnode* ptr;//�α�
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
    {//�����µ�Ĳ�����Ĭ�ϵĸ�������Ϊ0.5
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
    {//�����µ�
        int inlev = setgrade(p2);
	if (level < inlev) level = inlev;
	skipnode* ptr;//�α�ָ��
	ptr = head;//��ʼ���α�ָ��
	vector<skipnode* >location;//����������λ�õ�ָ������
	location.resize(inlev);
	int kk = 0;
	for (kk = level - 1; kk > inlev - 1;) 
        {
	    if (indata < ptr->p.at(kk)->data) 
            {//��������
	        kk--;
	    }
	    else 
            {//��������
	        ptr = ptr->p.at(kk);
	    }
        }
	for (; kk >= 0;) 
        {
	    if (indata < ptr->p.at(kk)->data) 
            {//��������
	        location.at(kk) = ptr;
		kk--;
	    }
	    else 
            {//��������
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
    {//���һ�����Ƿ����
        bool exi = false;
	skipnode* ptr;//�α�ָ��
	ptr = head;//��ʼ���α�ָ��
	for (int kk = level - 1; kk >= 0;) 
        {
	    if (indata == ptr->p.at(kk)->data) 
            {//ֹͣ����
	        exi = true;
		break;
	    }
	    else if (indata < ptr->p.at(kk)->data) 
            {//��������
	        kk--;
	    }
	    else
            {//��������
	        ptr = ptr->p.at(kk);
	    }
	}
		return exi;
    }
    skipnode* search(int indata) 
    {//����Ҫ���ҵĵ��ָ�룬����������򷵻�βָ��
        skipnode* ptr;//�α�ָ��
	ptr = head;//��ʼ���α�ָ��
	for (int kk = level - 1; kk >= 0;) 
        {
	    if (indata == ptr->p.at(kk)->data) 
            {//ֹͣ����
	        return ptr->p.at(kk);
	    }
	    else if (indata < ptr->p.at(kk)->data) 
            {//��������
		kk--;
	    }
	    else 
            {//��������
	        ptr = ptr->p.at(kk);
	    }
        }//����������򷵻�β����ָ��
	return tail;
    }
    void remove(int indata) 
    {//ɾ�����
        skipnode* ptr;//�α�ָ��
	ptr = head;//��ʼ���α�ָ��
	skipnode* d1;
	int kk = 0;
	for (kk = level - 1; kk >= 0;) 
        {
	    if (indata == ptr->p.at(kk)->data) 
            {//ֹͣ����
                d1 = ptr->p.at(kk);
		ptr->p.at(kk) = ptr->p.at(kk)->p.at(kk);// 
		kk--;
	    }
	    else if (indata < ptr->p.at(kk)->data) 
            {//��������
		kk--;
	    }
	    else 
            {//��������
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
