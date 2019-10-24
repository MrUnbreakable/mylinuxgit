// testJson.cpp : �������̨Ӧ�ó������ڵ㡣
//



#include "stdafx.h"
#include <sstream>
#include <iostream>
#include <ctime>
#include <fstream>
#include <string>  
#include <vector>
#include <algorithm>
#include <stdio.h>
//�����Ҫ��ͷ�ļ�
#include "include/json/json.h"
#define MAX 25000
#pragma warning(disable : 4996)
using namespace std;

//������Ҫ�Ŀ��ļ�
#ifdef _DEBUG
#pragma comment(lib,"json_vc71_libmtd_d.lib")
#else
#pragma comment(lib,"json_vc71_libmtd.lib")
#endif


//************��Ҫ��ȡ��json�ļ������ļ�Ӧ�÷��ڹ����ļ��¡�************
const string  jsonfilename = "a.json";
const string  txtfilename = "a.txt";
string str7;
string returnstr;

const int reader = 1;                      //0 ��ȡjson �ļ�    1��ȡ�ַ��� str
const int choose = 1;                      //0 ��ʹ��ѧУ���������� 1ʹ��ѧУ����������
const int ad1 = 1000;                      // ÿ��δ�ŵ��༶���˵ĳͷ�ֵ
const int ad2 = 10;                        // �༶�����������ٵĳͷ�ֵ
const int ad3 = 1000;					   // ÿ�������༶�������޵ĳͷ�ֵ
const int ad4 = 1000;					   // ÿ��������ʦ�������޵ĳͷ�ֵ
const double ad5 = 0.1;                       // ÿ�������༶����һ�����͵ĳͷ�ֵ
struct element {                           //������������ݽṹ 
	int data;                              // ���� 
	int index;                             // ��� 
};

int i6, j6, k6, ii6;
int times_6_3 = 2;									  //ÿtimes�ּ���һ������
int lu_6_3 = 0;                                       //�༶��������
int ld_6_3 = 0;                                       //�༶��������
int classroomlu_6_3 = 0;                              //������������
int unadd_6_3 = 0;                                    //��ͨ��������
int add_6_3 = 0;                                      //�߰�ʱ���ӵİ༶��
int classsum_6_3 = 0;                                 //�ܰ༶��
int bigclassmax_6_3 = 0;							  //���������
int bigclassnum_6_3 = 0;							  //����Ҹ���
const int NIND = 100;                             //��Ⱥ����
const int MAXGEN = 100;                           //�Ŵ�����
const double px = 0.97;                           //������
const double pm = 0.1;                            //������
const double GGAP = 0.9;                          //����

int complete_6_3 = 0;                                 //�ְ���ɱ�־λ
int runsnumber_6_3 = 0;                               //�㷨ִ�д���
int maxrunsnumber_6_3 = 3;                            //����㷨ִ�д��� ���︳��ֵ ��gettools�����������߰������Զ��������¸�ֵ
int** lists_6_3 = new int* [2];                      //���������ְ����б�
int** out1_6_3 = new int* [2];                        //�涨�����������Ž��  out1_6_3[2][PRECI]  0�зŰ༶���� 1�з�����
string** studentno_6_3;                              //����ѧ��������ѧ�ż�¼�� ����������ƥ����
string** teacherno_6_3;
int teacher_6_3[6] = { 0,0,0,0,0,0 };
string** classno_6_3;
int** plotno_6_3;
int** classroomno_6_3;
int* classname_6_3;
int** classname1_6_3;
int** shu_6_3;
int** studentinformation_6_3;
int studentnumber_6_3;
int** disclass_6_3;//����+�������
int allgocla_6_3 = 0;//���߰���
int countq_6_3;//���߰���
//************������������**********************************************
int** gettools(int** stuinform, int stunum, int* randnumber);//��ȡ�̶�����Ϣ
int** getstu1(int** stuinform, int** tools, int* randnumber);//��ȡ�߶�ѧ����Ϣ
int** getstu2(int** stuinform, int** tools, int* randnumber);//��ȡ����ѧ����Ϣ
int** sectionstu2(int** stu2, int** tools);//�����ְ࣬����ѧ���ְ���
int getstudentnumber();                   //��ȡѧ�����������ڴ�������
int getstudentnumberfromstring();                   //���ַ����л�ȡѧ�����������ڴ�������
int** readFileJson(int studentnumber_6_3);                    //���ļ��ж�ȡJSON��һ���洢��JSON��ʽ�ַ������ļ�
int** readJson(int studentnumber_6_3);                    //���ַ����ж�ȡJSON
int* swit(int p, int b[]);                //pΪ�γ�ID b����洢�γ̶�Ӧ��λ�����Ʊ���
int* translate(string volunteer);        //��ѡ������ĺ�����Ϸ����һ�����еĶ����Ʊ�ʾ
string translate2(int* b);               //��ѡ������Ķ����Ʒ�����ַ���
int** updatepopulation(int** pop, double* objv, int gen, int PRECI, int** out); //������Ⱥ��������ѡ������塢���桢����
int cmp(const void* a, const void* b);    //�������� 
void rand_of_n(int a[], int n);           //���� 1-n ��������в��浽 a[] ��
double** ranking(int** stu1, int** tools, int** pop);//��ȡ��Ӧ��ֵ
int** genetic(int** stu1, int** tools); //�Ŵ��㷨
string writeFileJson(int** stu1out, int** stu2out, int** tools);   //����Ϣ����ΪJSON��ʽ 
void sectionclassroom(int** stu1out, int** stu2out, int** tools);   //����Ϣ����ΪJSON��ʽ 
//string makeclass(string str);
//**********************************************************************

string makeclass(string inputstr)
{
	/********��json�ļ���ȡ**********/
	/******���ַ����ж�ȡ  �ַ���str��ȡ��txt**********/
	if (reader == 1)
	{
		str7 = inputstr;
		studentnumber_6_3 = getstudentnumberfromstring();//���ַ����л�ȡѧ��������
		studentinformation_6_3 = readJson(studentnumber_6_3);//��ȡѧ����Ϣ����ά����studentinformation
	}
	else if (reader == 0)
	{
		studentnumber_6_3 = getstudentnumber();//��ȡѧ��������
		studentinformation_6_3 = readFileJson(studentnumber_6_3);//��ȡѧ����Ϣ����ά����studentinformation
	}
	/*******************/

	if (choose != 0)
	{
		for (int i6 = 0; i6 < 5; i6++)
		{
			if (plotno_6_3[i6][0] == 1) lu_6_3 = plotno_6_3[i6][1];//ѡ���Ƿ�ʹ��ѧУ�����Ľ�������
			if (plotno_6_3[i6][0] == 2) ld_6_3 = plotno_6_3[i6][1];//ѡ���Ƿ�ʹ��ѧУ�����Ľ�������

		}
	}
	for (int i6 = 0; i6 < 5; i6++)
	{
		if (plotno_6_3[i6][0] == 4) bigclassmax_6_3 = plotno_6_3[i6][1];//���������
		if (plotno_6_3[i6][0] == 5) bigclassnum_6_3 = plotno_6_3[i6][1];//����Ҹ���
	}

	int* rand = new int[studentnumber_6_3]; //��������rand������������������ѧ����Ϣ˳��
	rand_of_n(rand, studentnumber_6_3);
	while (complete_6_3 != 1)
	{

		if (runsnumber_6_3 < maxrunsnumber_6_3)//������д���û������
		{
			cout << "���ڽ��зְ࣬���е�" << runsnumber_6_3 + 1 << "�γ���" << endl;
			int** tools = gettools(studentinformation_6_3, studentnumber_6_3, rand);//��ȡͳ�ƹ��Ĺ�������
			int** stu2 = getstu2(studentinformation_6_3, tools, rand);//��ȡ����ѧ����Ϣ
			int** stu1 = getstu1(studentinformation_6_3, tools, rand);//��ȡ����ѧ����Ϣ
			int** stu2out = sectionstu2(stu2, tools);//��ȡ�����ְ���
			int** stu1out = genetic(stu1, tools); //�Ŵ��㷨 ��ȡ�����ְ���
			runsnumber_6_3 = runsnumber_6_3 + 1;//��¼�㷨���д���
			if (complete_6_3 == 1)//���������
			{
				sectionclassroom(stu1out, stu2out, tools);
				returnstr = writeFileJson(stu1out, stu2out, tools);
			}
		}
		else
		{
			cout << "�ְ�ʧ��" << endl;
			break;
		}
	}
	return returnstr;
}
void sectionclassroom(int** stu1out, int** stu2out, int** tools)
{
	int PRECI = tools[4][5];           //��ȡ�����༶����

	int* classcontain = new int[PRECI];
	for (i6 = 0; i6 < PRECI; i6++)
	{
		if (i6 < bigclassnum_6_3)classcontain[i6] = bigclassmax_6_3;
		else classcontain[i6] = lu_6_3;
	}
	//��ÿ��ѧ������༶,6�����δ�Ű༶���͡��༶���ơ�����Ӧ�÷ŵ����������������з��˵�������������������Ů����������
	int** stuplus = new int* [tools[4][3]];
	for (i6 = 0; i6 < tools[4][3]; i6++)		stuplus[i6] = new int[9];
	for (i6 = 0; i6 < tools[4][1]; i6++)//���붨��ѧ����Ϣ
	{
		for (j6 = 0; j6 < 9; j6++) stuplus[i6][j6] = stu2out[i6][j6];
	}
	for (i6 = tools[4][1]; i6 < tools[4][3]; i6++)//���붨��ѧ����Ϣ
	{
		for (j6 = 0; j6 < 9; j6++)
		{
			stuplus[i6][j6] = stu1out[i6 - tools[4][1]][j6];
		}
	}
	int stu2num = tools[4][1];//��������
	int ss = tools[4][2];//��������
	int NUM = tools[4][2] + tools[4][5];//�ܰ༶����
	//int PRECI = tools[4][5];//������һ������
	int stu1num = tools[4][4];//��������
	disclass_6_3 = new int* [6]; //
	for (i6 = 0; i6 < 6; i6++)		disclass_6_3[i6] = new int[NUM];
	classname_6_3 = new int[tools[4][3]];//���������
	classname1_6_3 = new int* [2]; //�߰�������Ƿ��ѷ���
	for (i6 = 0; i6 < 2; i6++)		classname1_6_3[i6] = new int[tools[4][4]];
	for (i6 = 0; i6 < tools[4][4]; i6++) classname1_6_3[1][i6] = 0;//�ڶ������� ������¼�Ƿ�����
	for (i6 = 0; i6 < ss; i6++)
	{
		disclass_6_3[0][i6] = lists_6_3[0][i6];//�̶�����
		disclass_6_3[2][i6] = lists_6_3[1][i6];//�̶�������
	}
	for (i6 = ss; i6 < NUM; i6++)
	{
		disclass_6_3[0][i6] = out1_6_3[0][i6 - ss];//�߰����
		disclass_6_3[2][i6] = out1_6_3[1][i6 - ss];//�߰�����
	}
	for (j6 = 0; j6 < classroomno_6_3[1][5]; j6++)
	{
		if (classroomno_6_3[j6][4] == 2)    classroomno_6_3[j6][4] = 0;
		else if (classroomno_6_3[j6][4] == 3)    classroomno_6_3[j6][4] = 1;
	}
	for (i6 = 0; i6 < NUM; i6++)
	{
		int flag = 0;
		for (j6 = 0; j6 < classroomno_6_3[1][5]; j6++)//���۶��� ȫ�������Ͻ���
		{
			if (classroomno_6_3[j6][4] == 0 && flag == 0)//��ͨ����
			{
				disclass_6_3[1][i6] = classroomno_6_3[j6][1];//�������� �õĽ���id
				classroomno_6_3[j6][4] = 2;
				flag = 1;
			}
		}
		//for (int j6 = 0; j6 < classroomno_6_3[1][5]; j6++)
		//{
		//	if (classroomno_6_3[j6][4] == 1 && flag == 0)
		//	{
		//		disclass_6_3[1][i6] = classroomno_6_3[j6][1];//�������� �õĽ���id
		//		classroomno_6_3[j6][4] = 3;
		//		flag = 1;
		//	}		
		//}
		disclass_6_3[3][i6] = 0;//
		disclass_6_3[4][i6] = 0;//��
		disclass_6_3[5][i6] = 0;//Ů
	}


	for (i6 = 0; i6 < tools[4][3]; i6++)//����ѧ�� �ֶ��� ��Ů����
	{
		int aaa = 1;//��¼�ܷ�Ž�ȥ
		int bbb = -1;//��¼λ��
		int ccc = lu_6_3;//��¼��С����
		for (j6 = 0; j6 < NUM; j6++)//�������а༶
		{
			aaa = stuplus[i6][8] - disclass_6_3[0][j6];//8����   �������
			if (aaa == 0)//����ܷŽ�ȥ
			{
				if (disclass_6_3[3][j6] < disclass_6_3[2][j6])//�����û��������༶
				{
					if (stuplus[i6][7] == 1)//�����
					{
						if (disclass_6_3[4][j6] < ccc)//�����С
						{
							bbb = j6;//��¼λ��
							ccc = disclass_6_3[4][j6];//��С����
						}
					}
					else
					{
						if (disclass_6_3[5][j6] < ccc)
						{

							bbb = j6;
							ccc = disclass_6_3[5][j6];
						}
					}
				}
			}
		}
		classname_6_3[i6] = disclass_6_3[1][bbb];//��¼���ѧ�����䵽���ĸ����ң���Ϊ��Ϣ���ʮ��
		if (stuplus[i6][7] == 1)
		{
			disclass_6_3[4][bbb] = disclass_6_3[4][bbb] + 1;//�ж��Ա� 
		}
		else
		{
			disclass_6_3[5][bbb] = disclass_6_3[5][bbb] + 1;//
		}
		disclass_6_3[3][bbb] = disclass_6_3[4][bbb] + disclass_6_3[5][bbb];
	}


	int** goone = new int* [8]; //�����߶�����ѧ��ͳ���б�
	for (i6 = 0; i6 < 8; i6++)		goone[i6] = new int[PRECI];//0 ���� 1�༶id 2����3��ѧ 4���� 5���� 6��ʷ 7����
	for (i6 = ss; i6 < NUM; i6++)
	{
		goone[0][i6 - ss] = disclass_6_3[0][i6];//���� ժ������
		goone[1][i6 - ss] = disclass_6_3[1][i6];//�༶��
	}
	for (i6 = 2; i6 < 8; i6++) //����
	{
		for (j6 = 0; j6 < PRECI; j6++)
		{
			goone[i6][j6] = 0;
		}
	}
	for (i6 = 0; i6 < stu1num; i6++)//����ѧ��
	{
		int ddd = 1;
		for (j6 = 0; j6 < PRECI; j6++)//������༶
		{
			ddd = goone[1][j6] - classname_6_3[i6 + tools[4][1]];//�����ѧ����������
			if (ddd == 0)
			{
				for (k6 = 0; k6 < 6; k6++)
				{
					goone[k6 + 2][j6] = goone[k6 + 2][j6] + stuplus[i6 + tools[4][1]][k6];//ͳ��ѧ����Ŀ 
				}
				break;
			}
		}
	}

	for (i6 = 2; i6 < 8; i6++)//���㶨����Ĺ̶���Ŀ
	{
		for (j6 = 0; j6 < PRECI; j6++)
		{
			int b[6];
			swit(goone[0][j6], b);
			for (k6 = 0; k6 < 6; k6++)
			{
				if (b[k6] == 1) goone[k6 + 2][j6] = 0;
			}
		}
	}
	for (j6 = 0; j6 < 8; j6++)//************************************************************************
	{
		for (k6 = 0; k6 < PRECI; k6++)
		{
			cout.width(3);
			cout << goone[j6][k6] << " ";
		}
		cout << endl;
	}





	int gocla[6];//�����߰���
	//cout << "��ʾ����Ŀ0-���� 1-��ѧ 2-���� 3-���� 4-��ʷ 5-����"<< endl;
	int subjecttotal[6] = { 0,0,0,0,0,0 };
	for (i6 = 0; i6 < 6; i6++)
	{

		for (int j6 = 0; j6 < PRECI; j6++)
		{
			subjecttotal[i6] = subjecttotal[i6] + goone[i6 + 2][j6];
		}
		gocla[i6] = ceil(subjecttotal[i6] / (lu_6_3 * 1.0));
		string subtemp;
		if (i6 == 0) subtemp = "��";
		else if (i6 == 1) subtemp = "��";
		else if (i6 == 2) subtemp = "��";
		else if (i6 == 3) subtemp = "��";
		else if (i6 == 4) subtemp = "ʷ";
		else if (i6 == 5) subtemp = "��";

		cout << "��Ŀ " << subtemp << " ���߰�����Ϊ" << subjecttotal[i6] << "   ������" << gocla[i6] << "��" << endl;
		allgocla_6_3 = allgocla_6_3 + gocla[i6];
	}

	cout << "�����߰���Ϊ��" << allgocla_6_3 << endl;

	int* shu1 = new int[NUM];
	for (j6 = 0; j6 < NUM; j6++)
	{
		shu1[j6] = -1;
	}
	countq_6_3 = 0;
	int rn1[6] = { 0,0,0,0,0,0 };
	for (j6 = 0; j6 < 6; j6++)
	{
		rn1[j6] = gocla[j6];
	}


	while (allgocla_6_3)
	{
		if (countq_6_3 < PRECI)
		{
			int aa = -1;
			int bb = -1;
			int cc = -1;
			for (j6 = 0; j6 < 6; j6++)
			{
				for (k6 = 0; k6 < PRECI; k6++)
				{
					if (goone[j6 + 2][k6] > aa)
					{
						aa = goone[j6 + 2][k6];
						bb = j6;
						cc = k6;
					}
				}
			}
			goone[bb + 2][cc] = -1;
			if (rn1[bb] > 0 && shu1[cc] == -1)
			{
				shu1[cc] = bb;
				rn1[bb] = rn1[bb] - 1;
				allgocla_6_3 = allgocla_6_3 - 1;
				countq_6_3 = countq_6_3 + 1;
				if (classcontain[cc] < subjecttotal[bb])
				{
					subjecttotal[bb] = subjecttotal[bb] - classcontain[cc];
					if (ceil(subjecttotal[bb] * 1.0 / lu_6_3) < rn1[bb])
					{
						gocla[bb] = gocla[bb] - 1;
						rn1[bb] = rn1[bb] - 1;
						allgocla_6_3 = allgocla_6_3 - 1;
					}
				}
			}

		}
		else if (countq_6_3 >= PRECI)
		{
			for (j6 = 0; j6 < 6; j6++)
			{
				if (rn1[j6] != 0)
				{
					shu1[countq_6_3 + 1] = j6;
					rn1[j6] = rn1[j6] - 1;
					allgocla_6_3 = allgocla_6_3 - 1;
					countq_6_3 = countq_6_3 + 1;

					break;
				}
			}
		}
	}
	int* classcontain1 = new int[countq_6_3];
	for (j6 = 0; j6 < countq_6_3; j6++)
	{
		if (j6 < bigclassnum_6_3)classcontain1[j6] = bigclassmax_6_3;
		else classcontain1[j6] = lu_6_3;
	}

	//�߰������Ҳ���	
	int* all = new int[6 * PRECI];//��Ÿ����߿�����
	for (i6 = 0; i6 < 6; i6++)
	{
		for (j6 = 0; j6 < PRECI; j6++)
		{
			all[i6 * PRECI + j6] = goone[i6 + 2][j6];//�����߿Ƶ���all
		}
	}
	int tempa;//����
	for (i6 = 0; i6 < 6 * PRECI; i6++)
	{
		for (j6 = 1; j6 < 6 * PRECI - i6; j6++)
		{
			if (all[j6] > all[j6 - 1])
			{
				tempa = all[j6];
				all[j6] = all[j6 - 1];
				all[j6 - 1] = tempa;
			}
		}
	}//all�������
	shu_6_3 = new int* [3]; //��ŵ�һ�� ��� �ڶ���  �Ƿ񿪰�0δ�� 1 ��  ������ ����ʲô��
	for (i6 = 0; i6 < 3; i6++)		shu_6_3[i6] = new int[countq_6_3];
	for (i6 = 0; i6 < countq_6_3; i6++)
	{
		shu_6_3[1][i6] = 0;
		shu_6_3[2][i6] = 6;
		if (i6 < PRECI)
		{
			shu_6_3[0][i6] = goone[1][i6]; //dingerzouyi
		}
		else
		{
			int flag2 = 0;
			for (int j6 = 0; j6 < classroomno_6_3[1][5]; j6++)
			{
				if (classroomno_6_3[j6][4] == 1 && flag2 == 0)
				{
					shu_6_3[0][i6] = classroomno_6_3[j6][1];//�������� �õĽ���id
					classroomno_6_3[j6][4] = 3;
					flag2 = 1;
				}
			}
		}
	}

	int gocla1[6] = { 0,0,0,0,0,0 };//�����Ѿ�����ʲô��
	int* gocla2 = new int[PRECI];
	for (i6 = 0; i6 < PRECI; i6++)
	{
		gocla2[i6] = 1;
	}
	int ggg = -1, hhh = -1, js = 0, tt;
	for (int qr = 0; qr < 6 * PRECI; qr++)//����all
	{
		ggg = -1;
		hhh = -1;
		int flag1 = 0;
		for (i6 = 0; i6 < 6; i6++)//����goone
		{
			for (j6 = 0; j6 < PRECI; j6++)
			{
				if (gocla2[j6] == 1)//�����໹û����
				{
					tt = goone[i6 + 2][j6] - all[qr];//�˶��Ƿ�������ʵİ༶
					if (tt == 0 && gocla[i6] - gocla1[i6] != 0)
					{
						ggg = i6; hhh = j6;//��¼�� ��
						flag1 = 1;
						break;
					}
				}
			}
			if (flag1 == 1) { break; }
		}
		if (gocla[ggg] - gocla1[ggg] != 0 && ggg != -1)//�����û����
		{
			shu_6_3[1][hhh] = 1;
			shu_6_3[2][hhh] = ggg;
			gocla1[ggg] = gocla1[ggg] + 1;
			js = js + 1;
			gocla2[hhh] = 0;
		}
		if (js == PRECI)
		{
			break;
		}
	}

	if (countq_6_3 - PRECI > 0)//�����add
	{
		for (i6 = 0; i6 < countq_6_3 - PRECI; i6++)//����add
		{
			for (j6 = 0; j6 < 6; j6++)//��������ѧ��
			{
				if (gocla[j6] - gocla1[j6] != 0)//�����ĳ��Ŀû����
				{
					gocla1[j6] = gocla1[j6] + 1;
					shu_6_3[1][PRECI + i6] = 1;
					shu_6_3[2][PRECI + i6] = j6;
					break;
				}
			}
		}
	}

	for (j6 = 0; j6 < countq_6_3; j6++)
	{
		shu_6_3[1][j6] = 0;//���� ��������
	}
	for (i6 = 0; i6 < stu1num; i6++)
	{
		int classsubj = 7;//���ҿ�Ŀ
		int stusubj = 6;//ѧ����Ŀ
		int classsubjno = -1;
		for (j6 = 0; j6 < PRECI; j6++)
		{
			if (classname_6_3[stu2num + i6] == shu_6_3[0][j6])
			{
				classsubj = shu_6_3[2][j6];//����ԭ���ҵ��߰��
				classsubjno = j6;
			}
		}
		int b[6];
		swit(stuplus[stu2num + i6][8], b);
		for (j6 = 0; j6 < 6; j6++)
		{
			if (stuplus[stu2num + i6][j6] - b[j6] == 1) stusubj = j6;//������Ҫ�ߵĿ�
		}
		if (stusubj == classsubj)//���ԭ����Է�
		{
			classname1_6_3[0][i6] = classname_6_3[stu2num + i6];//�ŵ�ԭ�༶
			classname1_6_3[1][i6] = 1;
			shu_6_3[1][classsubjno] = shu_6_3[1][classsubjno] + 1;//����
		}
	}
	for (i6 = 0; i6 < stu1num; i6++)//�������ж���ѧ��
	{
		if (classname1_6_3[1][i6] == 0)//������ѧ����û����
		{
			int aaa = 1;//��¼�ܷ�Ž�ȥ
			int bbb = -1;//��¼λ��
			int ccc;
			if (bigclassnum_6_3 != 0)
			{
				ccc = bigclassmax_6_3;
			}
			else
			{
				ccc = lu_6_3;
			}
			int stusubj = 6;//ѧ����Ŀ
			int b[6];
			swit(stuplus[stu2num + i6][8], b);
			for (j6 = 0; j6 < 6; j6++)
			{
				if (stuplus[stu2num + i6][j6] - b[j6] == 1) stusubj = j6;//������Ҫ�ߵĿ�
			}
			for (j6 = 0; j6 < countq_6_3; j6++)
			{
				aaa = stusubj - shu_6_3[2][j6];//   �������
				if (aaa == 0)//����ܷŽ�ȥ
				{
					if (shu_6_3[1][j6] < classcontain1[j6])//�����û��������༶**************************
					{
						if (shu_6_3[1][j6] < ccc)//�����С
						{
							bbb = j6;//��¼λ��
							ccc = shu_6_3[1][j6];//��С����
						}
					}
				}
			}
			classname1_6_3[0][i6] = shu_6_3[0][bbb];//��¼���ѧ�����䵽���ĸ�����
			classname1_6_3[1][i6] = 1;
			shu_6_3[1][bbb] = shu_6_3[1][bbb] + 1;//����
		}
	}
	cout << "----------------------------------------------------------------" << endl;
	for (i6 = 0; i6 < 3; i6++)/************************************************************/
	{
		if (i6 == 0) cout << " ��һ����:  ";
		else if (i6 == 1) cout << " �༶������ ";
		else if (i6 == 2) cout << " �������ͣ� ";
		for (j6 = 0; j6 < countq_6_3; j6++)
		{
			cout.width(3);
			if (i6 < 2) cout << shu_6_3[i6][j6] << "  ";
			else if (i6 == 2)
			{
				if (shu_6_3[i6][j6] == 0) { cout.width(3); cout << "��   "; }
				else if (shu_6_3[i6][j6] == 1) { cout.width(3); cout << "��   "; }
				else if (shu_6_3[i6][j6] == 2) { cout.width(3); cout << "��   "; }
				else if (shu_6_3[i6][j6] == 3) { cout.width(3); cout << "��   "; }
				else if (shu_6_3[i6][j6] == 4) { cout.width(3); cout << "ʷ   "; }
				else if (shu_6_3[i6][j6] == 5) { cout.width(3); cout << "��   "; }
			}
		}
		cout << " \n";
	}
	cout << endl;

}
int** genetic(int** stu1, int** tools)
{
	int gen = 0;                      //�Ŵ�����������
	int stu1numb = tools[4][4];       //��ȡ����ѧ������
	int PRECI = tools[4][5];           //��ȡ�����༶����

	int** pop = new int* [NIND];      //popΪ������Ⱥ pop[NIND][tools[4][5]]
	for (i6 = 0; i6 < NIND; i6++)		pop[i6] = new int[PRECI];


	for (i6 = 0; i6 < 2; i6++)		    out1_6_3[i6] = new int[PRECI];

	double** trace = new double* [2];     //���������ѷְ෽ʽ trace[2][MAXGEN]������������
	for (i6 = 0; i6 < 2; i6++)		trace[i6] = new double[MAXGEN];

	double* objv = new double[NIND];  //��Ӧ��ֵ

	double globalminobjv = 0.0; //��¼ȫ����С��Ӧ��ֵ

	int* stufinalclass = new int[stu1numb];  //���ڼ�¼ѧ������ѡ��

	int** stu1out = new int* [stu1numb];        //�����һ��ѧ��ѡ����Ϣ���ְ���
	for (i6 = 0; i6 < stu1numb; i6++)		    stu1out[i6] = new int[9];

	for (i6 = 0; i6 < NIND; i6++)       //������ɳ�ʼ��Ⱥ
	{
		for (j6 = 0; j6 < PRECI; j6++)
		{
			int randompop = rand();
			pop[i6][j6] = randompop % 15;           //����0-14�����������ʾ���ɵ����������һ�༶����
		}
	}

	while (gen < MAXGEN)                    //
	{

		double** tools2 = ranking(stu1, tools, pop);     //��ȡ��Ӧ��ֵ�������ص������Ÿ�ѧ���ְ�ȥ���Լ���������

		for (int i6 = 0; i6 < NIND; i6++)
		{
			double tempobjv = tools2[i6][2];
			objv[i6] = tempobjv;
		}

		double minobjv = (*min_element(objv, objv + NIND)); //��С��Ӧ��ֵ
		int minpos = (min_element(objv, objv + NIND) - objv); //��Сֵ��λ��  ����

		trace[0][gen] = minobjv; //���ڹ۲���Ӧ��ֵ�仯 ��¼ÿ����С��Ӧ��ֵ
		trace[1][gen] = gen;     // ��n��

		if (gen > 0)
		{
			if (minobjv < globalminobjv)               //�����ȫ������
			{
				globalminobjv = minobjv;               //��¼ȫ��������Ӧ��ֵ
				for (i6 = 0; i6 < stu1numb; i6++)
				{
					stufinalclass[i6] = tools2[i6][0];   //��¼���Ž�ѧ���༶����
				}
				for (i6 = 0; i6 < PRECI; i6++)
				{
					out1_6_3[0][i6] = pop[minpos][i6];       //ȫ�����Ÿ���id
					out1_6_3[1][i6] = tools2[i6][1];         //ȫ�����Ÿ������ѧ������
				}
			}
		}
		else//����ǵ�0�� ���¼0�����Ž�
		{
			globalminobjv = minobjv;             //��¼ȫ��������Ӧ��ֵ
			for (i6 = 0; i6 < stu1numb; i6++)
			{
				stufinalclass[i6] = tools2[i6][0];    //��¼���Ž�ѧ���༶����
			}
			for (i6 = 0; i6 < PRECI; i6++)
			{
				out1_6_3[0][i6] = pop[minpos][i6];      //ȫ�����Ÿ���id
				out1_6_3[1][i6] = tools2[i6][1];      //ȫ�����Ÿ������ѧ������
			}
		}

		pop = updatepopulation(pop, objv, gen, PRECI, out1_6_3);//ѡ�񽻲����

		gen = gen + 1;
	}


	if (globalminobjv < PRECI * 10)//�ж���Ӧ��ֵ�Ƿ���
	{
		complete_6_3 = 1;   // �����Ӧ��ֵ��С������ɹ��ְࣩ�����־�ְ����
		cout << "----------------------------------------------------------------" << endl;
		cout << "��С��Ӧ��ֵ��" << globalminobjv << endl;

		for (i6 = 0; i6 < 2; i6++)
		{
			if (i6 == 0) cout << "�����༶���ͣ�";
			else cout << "�����༶������";
			for (int j6 = 0; j6 < tools[4][2]; j6++)
			{
				cout.width(3);
				cout << lists_6_3[i6][j6] << ' ';
			}
			cout << '\n' << endl;
		}

		for (i6 = 0; i6 < 2; i6++)
		{
			if (i6 == 0) cout << "��һ�༶���ͣ�";
			else cout << "��һ�༶������";
			for (j6 = 0; j6 < PRECI; j6++)
			{
				cout.width(3);
				cout << out1_6_3[i6][j6] << ' ';
			}
			cout << '\n' << endl;
		}
		int zongrenshu = 0;
		for (j6 = 0; j6 < PRECI; j6++)
		{
			zongrenshu = zongrenshu + out1_6_3[1][j6];
		}
		if (stu1numb - zongrenshu == 0) 	cout << "����ͬѧ���ѷְ����" << endl;
		else cout << "����ͬѧδ�ɹ�����༶" << endl;
		cout << "----------------------------------------------------------------" << endl;
		for (i6 = 0; i6 < stu1numb; i6++)
		{
			for (j6 = 0; j6 < 8; j6++)
			{
				stu1out[i6][j6] = stu1[i6][j6];
			}
			stu1out[i6][8] = stufinalclass[i6];
		}
		return stu1out;
	}
	return 0;
}
double** ranking(int** stu1, int** tools, int** pop)
{

	double* objv = new double[NIND];  //��Ӧ��ֵ

	int stu1numb = tools[4][4];       //��ȡ����ѧ������
	int PRECI = tools[4][5];           //��ȡ�����༶����


	int* classcontain = new int[PRECI];
	for (i6 = 0; i6 < PRECI; i6++)
	{
		if (i6 < bigclassnum_6_3)classcontain[i6] = bigclassmax_6_3;
		else classcontain[i6] = lu_6_3;
	}
	int total[6];                     //���ڼ���ʣ��δѡ��Ŀ����
	int total1[6];                    //ͳ���Ѿ������Ŀ������
	int total2[6];                    //��stu11���а������,ͳ�ƶ��������������

	int** class1 = new int* [stu1numb];      //��ÿ�����ɵĶ�����һ�༶���� num[NIND][tools[4][5]]
	for (i6 = 0; i6 < stu1numb; i6++)		class1[i6] = new int[NIND];

	int** num = new int* [NIND];      //��ÿ�����ɵĶ�����һ�༶���� num[NIND][tools[4][5]]
	for (i6 = 0; i6 < NIND; i6++)		num[i6] = new int[PRECI];

	int tools2line = stu1numb + NIND;
	double** tools2 = new double* [tools2line];  //���ڼ�¼ѧ������ѡ��
	for (i6 = 0; i6 < tools2line; i6++)		tools2[i6] = new double[3];

	for (i6 = 0; i6 < 6; i6++)//����
	{
		total[i6] = 0;
		total1[i6] = 0;
		total2[i6] = 0;
	}
	for (i6 = 0; i6 < NIND; i6++)
	{
		for (j6 = 0; j6 < PRECI; j6++)
		{
			num[i6][j6] = 0;
		}
		for (j6 = 0; j6 < stu1numb; j6++)
		{
			class1[j6][i6] = 0;
		}
	}




	for (i6 = 0; i6 < NIND; i6++)         //������Ⱥÿһ�����壨ÿһ�ְ༶��ϣ�
	{
		for (j6 = 0; j6 < 6; j6++)//����
		{
			total[j6] = 0;
			total1[j6] = 0;
			total2[j6] = 0;
		}
		for (j6 = 0; j6 < 6; j6++) //ͳ�ƶ��������������
		{
			for (k6 = 0; k6 < stu1numb; k6++)
			{
				total2[j6] = stu1[k6][j6] + total2[j6];//���stu11������� ͳ�Ƹ��������ɣ�
			}
		}
		for (k6 = 0; k6 < stu1numb; k6++)     //������������ѧ��   
		{
			int e = -1;                  //���ڼĴ���������İ༶��ţ������ж��Ƿ�Ž��˰༶��
			int f = 0;                   //���ڼĴ���������İ༶���������ٵİ༶ѧ�����������ȷ��룩
			if (bigclassnum_6_3 > 0) f = bigclassmax_6_3;
			else f = lu_6_3;


			for (j6 = 0; j6 < PRECI; j6++)    //����ÿ��������һ�༶      
			{

				int b[6];
				swit(pop[i6][j6], b);      //�������i�е�j���༶
				int p = 0;
				for (int q = 0; q < 6; q++)
				{

					if (b[q] - stu1[k6][q] == 0)
					{
						p = p + 1;
					}
				}
				if (p == 5)
				{
					if (num[i6][j6] < classcontain[j6]) //ÿ�ζ��ŵ��������ٵİ༶
					{
						if (num[i6][j6] < f)
						{
							e = j6;
							f = num[i6][j6];
						}
					}
				}

			}

			if (e > -1)
			{
				num[i6][e] = num[i6][e] + 1; //��Ⱥ��ĳȾɫ�����+1
				class1[k6][i6] = pop[i6][e];//��¼ѧ�����ֵ���ʲô�༶
			}
		}

		/*int **stu1outtemp = new int *[stu1numb];      //��ÿ�����ɵĶ�����һ�༶���� num[NIND][tools[4][5]]
		for (int j6 = 0; j6 < stu1numb; j6++)		stu1outtemp[j6] = new int[9];
		for (int j6 = 0; j6 < stu1numb; j6++)
		{
			for (int k6 = 0; k6 < 8; k6++)
			{
				stu1outtemp[j6][k6] = stu1[j6][k6];
			}
			stu1outtemp[j6][8] = class1[j6][i6];
		}
		*/


		//��ÿ��ѧ������༶,6�����δ�Ű༶���͡��༶���ơ�����Ӧ�÷ŵ����������������з��˵�������������������Ů����������
		int** stuplus = new int* [tools[4][3]];
		for (ii6 = 0; ii6 < tools[4][3]; ii6++)		stuplus[ii6] = new int[9];

		for (ii6 = tools[4][1]; ii6 < tools[4][3]; ii6++)//���붨��ѧ����Ϣ
		{
			for (j6 = 0; j6 < 8; j6++)
			{
				stuplus[ii6][j6] = stu1[ii6 - tools[4][1]][j6];
			}
			stuplus[ii6][8] = class1[ii6 - tools[4][1]][i6];
		}




		//int stu2num = tools[4][1];//��������
		int ss = tools[4][2];//��������
		int NUM = tools[4][2] + tools[4][5];//�ܰ༶����
		int stu1num = tools[4][4];//��������
		disclass_6_3 = new int* [6]; //
		for (ii6 = 0; ii6 < 6; ii6++)		disclass_6_3[ii6] = new int[NUM];
		classname_6_3 = new int[tools[4][3]];//���������
		for (ii6 = 0; ii6 < ss; ii6++)
		{
			disclass_6_3[0][ii6] = lists_6_3[0][ii6];//�̶�����
			disclass_6_3[2][ii6] = lists_6_3[1][ii6];//�̶�������
		}
		for (j6 = ss; j6 < NUM; j6++)
		{
			disclass_6_3[0][j6] = pop[i6][j6 - ss];//�߰����
			disclass_6_3[2][j6] = num[i6][j6 - ss];//�߰�����
		}
		for (j6 = 0; j6 < classroomno_6_3[1][5]; j6++)
		{
			if (classroomno_6_3[j6][4] == 2)    classroomno_6_3[j6][4] = 0;
			else if (classroomno_6_3[j6][4] == 3)    classroomno_6_3[j6][4] = 1;
		}
		for (ii6 = 0; ii6 < NUM; ii6++)
		{
			int flag = 0;
			for (j6 = 0; j6 < classroomno_6_3[1][5]; j6++)//���۶��� ȫ�������Ͻ���
			{
				if (classroomno_6_3[j6][4] == 0 && flag == 0)//��ͨ����
				{
					disclass_6_3[1][ii6] = classroomno_6_3[j6][1];//�������� �õĽ���id
					classroomno_6_3[j6][4] = 2;
					flag = 1;
				}
			}

			disclass_6_3[3][ii6] = 0;//
			disclass_6_3[4][ii6] = 0;//��
			disclass_6_3[5][ii6] = 0;//Ů
		}
		for (ii6 = tools[4][1]; ii6 < tools[4][3]; ii6++)//����ѧ�� �ֶ��� ��Ů����
		{
			int aaa = 1;//��¼�ܷ�Ž�ȥ
			int bbb = -1;//��¼λ��
			int ccc = lu_6_3;//��¼��С����
			for (j6 = 0; j6 < NUM; j6++)//�������а༶
			{
				aaa = stuplus[ii6][8] - disclass_6_3[0][j6];//8����   �������
				if (aaa == 0)//����ܷŽ�ȥ
				{
					if (disclass_6_3[3][j6] < disclass_6_3[2][j6])//�����û��������༶
					{
						if (stuplus[ii6][7] == 1)//�����
						{
							if (disclass_6_3[4][j6] < ccc)//�����С
							{
								bbb = j6;//��¼λ��
								ccc = disclass_6_3[4][j6];//��С����
							}
						}
						else
						{
							if (disclass_6_3[5][j6] < ccc)
							{

								bbb = j6;
								ccc = disclass_6_3[5][j6];
							}
						}
					}
				}
			}
			classname_6_3[ii6] = disclass_6_3[1][bbb];//��¼���ѧ�����䵽���ĸ����ң���Ϊ��Ϣ���ʮ��
			if (stuplus[ii6][7] == 1)
			{
				disclass_6_3[4][bbb] = disclass_6_3[4][bbb] + 1;//�ж��Ա� 
			}
			else
			{
				disclass_6_3[5][bbb] = disclass_6_3[5][bbb] + 1;//
			}
			disclass_6_3[3][bbb] = disclass_6_3[4][bbb] + disclass_6_3[5][bbb];
		}


		int** goone = new int* [8]; //�����߶�����ѧ��ͳ���б�
		for (ii6 = 0; ii6 < 8; ii6++)		goone[ii6] = new int[PRECI];//0 ���� 1�༶id 2����3��ѧ 4���� 5���� 6��ʷ 7����
		for (ii6 = 0; ii6 < 8; ii6++)
		{
			for (j6 = 0; j6 < PRECI; j6++)
			{
				goone[ii6][j6] = 0;
			}
		}
		int** goone1 = new int* [8]; //�����߶�����ѧ��ͳ���б�
		for (ii6 = 0; ii6 < 8; ii6++)		goone1[ii6] = new int[PRECI];//0 ���� 1�༶id 2����3��ѧ 4���� 5���� 6��ʷ 7����
		for (ii6 = ss; ii6 < NUM; ii6++)
		{
			goone[0][ii6 - ss] = disclass_6_3[0][ii6];//���� ժ������
			goone[1][ii6 - ss] = disclass_6_3[1][ii6];//�༶��
		}
		for (ii6 = 0; ii6 < stu1num; ii6++)//����ѧ��
		{
			int ddd = 1;
			for (j6 = 0; j6 < PRECI; j6++)//������༶
			{
				ddd = goone[1][j6] - classname_6_3[ii6 + tools[4][1]];//�����ѧ����������
				if (ddd == 0)
				{
					for (k6 = 0; k6 < 6; k6++)
					{
						goone[k6 + 2][j6] = goone[k6 + 2][j6] + stuplus[ii6 + tools[4][1]][k6];//ͳ��ѧ����Ŀ 
					}
					break;
				}
			}
		}

		for (ii6 = 2; ii6 < 8; ii6++)//���㶨����Ĺ̶���Ŀ
		{
			for (j6 = 0; j6 < PRECI; j6++)
			{
				int b[6];
				swit(goone[0][j6], b);
				for (k6 = 0; k6 < 6; k6++)
				{
					if (b[k6] == 1) goone[k6 + 2][j6] = 0;
				}
			}
		}
		/*for (int j6 = 0; j6 < 8; j6++)
		{
			for (int k6 = 0; k6 < PRECI; k6++)
			{
				cout << goone[j6][k6] << ' ';
			}
			cout << '\n' << endl;
		}*/

		for (j6 = 0; j6 < 8; j6++)
		{
			for (k6 = 0; k6 < PRECI; k6++)
			{
				goone1[j6][k6] = goone[j6][k6];
			}
		}

		for (j6 = 0; j6 < PRECI; j6++)
		{
			int b[6];
			swit(pop[i6][j6], b);
			for (k6 = 0; k6 < 6; k6++)
			{
				total1[k6] = total1[k6] + num[i6][j6] * b[k6]; //�Ž�ȥ�˵ĸ���Ŀ������
			}
		}
		for (j6 = 0; j6 < 6; j6++)
		{
			total[j6] = total2[j6] - total1[j6];//��ʣ��û�Ž�ȥ�ĸ���������
			//cout << total[j6] << " " << total2[j6] << " " << total1[j6] << endl;
		}
		int meansum = 0;                   //�ѷ���༶��������
		int d1 = 0;                       //û�Ž�ȥ������


		for (j6 = 0; j6 < PRECI; j6++)//��Ž�ȥ��������
		{
			meansum = meansum + num[i6][j6];
		}
		d1 = stu1numb - meansum;
		float mean = meansum / (PRECI * 1.0);//ƽ����

		float sum1 = 0.0;
		for (j6 = 0; j6 < PRECI; j6++)
		{
			sum1 = (num[i6][j6] - mean) * (num[i6][j6] - mean) * 1.0 + sum1;
		}
		float s1 = sum1 / (PRECI * 1.0);   //����
		int d2 = 0;                         //�����ж��Ƿ���������
		for (j6 = 0; j6 < PRECI; j6++)     //���������������޶� �ͷ�
		{
			if (num[i6][j6] < ld_6_3)
			{
				d2 = d2 + ld_6_3 - num[i6][j6];
			}
		}
		objv[i6] = s1 + ad1 * d1 + ad2 * d2;
		int rn[6] = { 0,0,0,0,0,0 };

		if (objv[i6] < 1000)
		{
			int q = 0;
			countq_6_3 = 0;
			for (j6 = 0; j6 < 6; j6++)
			{
				q = q + ceil(total[j6] / (lu_6_3 * 1.0));
				rn[j6] = ceil(total[j6] / (lu_6_3 * 1.0));
			}

			int rn1[6];
			for (j6 = 0; j6 < 6; j6++)
			{
				rn1[j6] = rn[j6];
			}

			int* shu1 = new int[NUM + add_6_3];
			for (j6 = 0; j6 < NUM + add_6_3; j6++)
			{
				shu1[j6] = -1;
			}

			while (q)
			{
				if (countq_6_3 < PRECI)
				{
					int aa = -1;
					int bb = -1;
					int cc = -1;
					for (j6 = 0; j6 < 6; j6++)
					{
						for (k6 = 0; k6 < PRECI; k6++)
						{
							if (goone1[j6 + 2][k6] > aa)
							{
								aa = goone1[j6 + 2][k6];
								bb = j6;
								cc = k6;
							}
						}
					}
					goone1[bb + 2][cc] = -1;
					if (rn1[bb] > 0 && shu1[cc] == -1)
					{
						shu1[cc] = bb;
						rn1[bb] = rn1[bb] - 1;
						q = q - 1;
						countq_6_3 = countq_6_3 + 1;
						if (classcontain[cc] < total[bb])
						{
							total[bb] = total[bb] - classcontain[cc];
							if (ceil(total[bb] / (lu_6_3 * 1.0)) < rn1[bb])
							{
								rn[bb] = rn[bb] - 1;
								rn1[bb] = rn1[bb] - 1;
								q = q - 1;
							}
						}
					}

				}
				else if (countq_6_3 >= PRECI)
				{
					for (j6 = 0; j6 < 6; j6++)
					{
						if (rn1[j6] != 0)
						{
							shu1[countq_6_3 + 1] = j6;
							rn1[j6] = rn1[j6] - 1;
							q = q - 1;
							countq_6_3 = countq_6_3 + 1;
							break;
						}
					}
				}
			}
			int d3 = 0;
			if (countq_6_3 > (PRECI + add_6_3))
			{
				d3 = countq_6_3 - (PRECI + add_6_3);
				objv[i6] = objv[i6] + ad3 * d3;
			}

			int d4 = 0;
			for (j6 = 0; j6 < 6; j6++)
			{
				if (teacher_6_3[j6] < rn[j6])
				{
					d4 = d4 + (rn[j6] - teacher_6_3[j6]);
				}
			}
			objv[i6] = objv[i6] + ad4 * d4;

			int d5 = 0;//�����ж϶����༶��һ�����Ƿ���
			for (j6 = 0; j6 < tools[4][5]; j6++)
			{
				int stuclass[6] = { 0,0,0,0,0,0 };
				for (k6 = 0; k6 < stu1numb; k6++)
				{
					if (class1[k6][i6] == pop[i6][j6])
					{
						for (int kk = 0; kk < 6; kk++)
						{
							stuclass[kk] = stuclass[kk] + stu1[k6][kk];
						}
					}
				}
				for (k6 = 0; k6 < 6; k6++)
				{
					if (stuclass[k6] != 0)
					{
						d5 = d5 + 1;
					}
				}
			}
			d5 = d5 - 2 * PRECI;
			objv[i6] = objv[i6] + ad5 * d5;
		}
		else
		{
			objv[i6] = objv[i6] * 2;
		}

		for (j6 = 0; j6 < tools[4][3]; j6++)
		{
			delete[] stuplus[j6];
		}
		delete[] stuplus;
		for (j6 = 0; j6 < 8; j6++)
		{
			delete[] goone[j6];
		}
		for (j6 = 0; j6 < 8; j6++)
		{
			delete[] goone1[j6];
		}


		delete[] disclass_6_3;
		delete[] goone;
		delete[] goone1;
	}


	//for (int j6 = 0; j6 <NIND; j6++)//********************************************************************
	//{
	//	for (int k6 = 0; k6 <PRECI; k6++)
	//	{
	//		cout << num[j6][k6] << " ";
	//	}
	//	cout << endl;
	//}

	for (i6 = 0; i6 < NIND; i6++)
	{
		tools2[i6][2] = objv[i6]; //tools2[i6][2]���뱾����Ӧ��ֵ
	}
	int minpos = (min_element(objv, objv + NIND) - objv);          //������Сֵ��λ�� 

	for (i6 = 0; i6 < stu1numb; i6++)
	{
		tools2[i6][0] = class1[i6][minpos];// tools2[i6][0]���뱾������ѧ���༶����
	}
	for (i6 = 0; i6 < PRECI; i6++)
	{
		tools2[i6][1] = num[minpos][i6];// tools2[i6][1]���뱾�����Ÿ���ѧ������
	}
	return tools2;
}
int** updatepopulation(int** pop, double* objv, int gen, int PRECI, int** out)
{
	int** popnext = new int* [NIND];      //popnextΪ���º���Ⱥ popnext[NIND][tools[4][5]]
	for (i6 = 0; i6 < NIND; i6++)		popnext[i6] = new int[PRECI];

	for (i6 = 0; i6 < NIND; i6++)
	{
		for (j6 = 0; j6 < PRECI; j6++)
		{
			popnext[i6][j6] = pop[i6][j6];
		}
	}

	int* temp0 = new int[PRECI];
	for (i6 = 0; i6 < NIND; i6++)                 // ���ݸ�����Ӧ�������򣻣�ð�ݷ���
	{
		for (j6 = 1; j6 < NIND - i6; j6++)
		{
			if (objv[j6] < objv[j6 - 1])
			{
				for (k6 = 0; k6 < PRECI; k6++)
				{
					temp0[k6] = popnext[j6][k6];
					popnext[j6][k6] = popnext[j6 - 1][k6];
					popnext[j6 - 1][k6] = temp0[k6];
				}
			}
		}
	}

	for (i6 = NIND * GGAP; i6 < NIND; i6++)       //���մ����������Ƹ���
	{
		for (j6 = 0; j6 < PRECI; j6++)
		{

			popnext[i6][j6] = popnext[NIND - i6 - 1][j6];
		}
	}



	int* temp1 = new int[PRECI];
	for (i6 = 0; i6 < (NIND / 2); i6++)
	{
		double random1 = (rand() % 10) / 10.0;  //����0-1�����С��,�����ж��Ƿ񽻲�
		if (random1 >= (1.0 - px))
		{
			int random2 = rand() % PRECI;                     // ������ɽ���λ�ã�����������0��PRECI֮�䣻
			for (j6 = random2; j6 < PRECI; j6++)
			{
				temp1[j6] = popnext[i6 * 2 + 1][j6];
				popnext[i6 * 2 + 1][j6] = popnext[i6 * 2][j6];
				popnext[i6 * 2][j6] = temp1[j6];
			}
		}
	}

	for (i6 = 0; i6<int(NIND * PRECI * pm); i6++)                             //����
	{
		int col = rand() % PRECI;                            // �������Ҫ����Ļ���λ�ţ�
		int row = rand() % NIND;                             // �������Ҫ�����Ⱦɫ��ţ�
		popnext[row][col] = rand() % 15;                  //��0-14֮������任һ��
	}
	for (i6 = 0; i6 < PRECI; i6++)                         //��ȫ�����Ų���
	{
		popnext[(NIND - 1)][i6] = out[0][i6];
	}


	return popnext;

}
int** sectionstu2(int** stu2, int** tools)
{
	int num = tools[4][2];//���������
	int** stu2out = new int* [tools[4][1]]; //���������ְ����б�
	for (i6 = 0; i6 < tools[4][1]; i6++)		stu2out[i6] = new int[9];

	for (i6 = 0; i6 < 2; i6++)		lists_6_3[i6] = new int[num];
	int knum = 0; //��ʼ��list������
	for (i6 = 0; i6 < 20; i6++)//������ʮ�ְ���
	{
		if (tools[2][i6] > 0)//�������
		{

			for (j6 = 0; j6 < tools[2][i6]; j6++)//��x����
			{

				lists_6_3[0][knum] = tools[0][i6];

				lists_6_3[1][knum] = 0;
				knum++;
			}
		}
	}
	for (i6 = 0; i6 < tools[4][1]; i6++)
	{
		int o[6];
		int e = -1;                  //���ڼĴ���������İ༶��ţ������ж��Ƿ�Ž��˰༶��
		int f = lu_6_3;                  //���ڼĴ���������İ༶���������ٵİ༶ѧ�����������ȷ��룩

		for (j6 = 0; j6 < 6; j6++)
		{
			o[j6] = stu2[i6][j6];
		}

		for (k6 = 0; k6 < tools[4][2]; k6++)
		{
			int p = 0;
			for (int e = 0; e < 6; e++)
			{
				int b[6];
				swit(lists_6_3[0][k6], b);
				if (o[e] - b[e] == 0)
				{
					p = p + 1;
				}
			}
			if ((p == 6) && ((lists_6_3[1][k6]) < lu_6_3) && lists_6_3[1][k6] < f)
			{
				e = k6;
				f = lists_6_3[1][k6];
			}
		}
		if (e > -1)
		{
			lists_6_3[1][e] = lists_6_3[1][e] + 1;
			stu2out[i6][8] = lists_6_3[0][e];
		}

	}

	for (i6 = 0; i6 < tools[4][1]; i6++)
	{
		for (j6 = 0; j6 < 8; j6++)
		{
			stu2out[i6][j6] = stu2[i6][j6];
		}
	}
	return stu2out;
}
int** getstu2(int** stuinform, int** tools, int* randnumber)
{
	int u[20][6];//�༶����Ƚ�ģ��
	for (i6 = 0; i6 < 20; i6++)
	{
		int b[6];
		swit(tools[0][i6], b);
		for (j6 = 0; j6 < 6; j6++)
		{
			u[i6][j6] = b[j6];                    //u[i6][j6]��ŵ�һ�ηֺ�ѡ����Ϣ�Ĺ̶��༶������
		}
	}

	int num2 = tools[4][1];//��������
	int** stu2 = new int* [num2];
	for (i6 = 0; i6 < num2; i6++)		stu2[i6] = new int[9];
	int y[20];
	int stu2num = 0;
	int stu2num2 = 0;
	for (i6 = 0; i6 < 20; i6++)          y[i6] = 0;
	for (i6 = 0; i6 < tools[4][3]; i6++) //tools[4][3]��ѧ������
	{
		int f[9];//�ݴ�ʹ�õ�ѧ����Ϣ
		for (j6 = 0; j6 < 9; j6++)
		{
			f[j6] = stuinform[(randnumber[i6] - 1)][j6];       //ǧ��ע�������stu������ǰ���stu���������������ɣ������������ƥ�䲻�ϣ�������������
		}
		for (k6 = 0; k6 < 20; k6++) //����20�ֿ��ܰ�
		{
			if (tools[2][k6] > 0) //����п���
			{
				if (y[k6] < tools[3][k6]) //��û����
				{
					int h = 0; //�Ƚϼ���λ

					for (int g = 0; g < 6; g++)
					{
						if (f[g] - u[k6][g] == 0)    h = h + 1;//ͳ����ͬλ����	
					}
					if (h == 6)          //ÿ��ѧ����̶��༶�Ŀ�Ŀ���бȽϣ����ϵľͷŽ�ȥ
					{
						for (int l = 0; l < 9; l++)  stu2[stu2num][l] = f[l];
						y[k6] = y[k6] + 1;
						stu2num = stu2num + 1;
						break;
					}

				}

			}

		}

	}
	return stu2;
}
int** getstu1(int** stuinform, int** tools, int* randnumber)
{
	int u[20][6];//�༶����Ƚ�ģ��
	for (i6 = 0; i6 < 20; i6++)
	{
		int b[6];
		swit(tools[0][i6], b);
		for (j6 = 0; j6 < 6; j6++)
		{
			u[i6][j6] = b[j6];                    //u[i6][j6]��ŵ�һ�ηֺ�ѡ����Ϣ�Ĺ̶��༶������
		}
	}
	int num1 = tools[4][4];
	int** stu1 = new int* [num1];
	for (i6 = 0; i6 < num1; i6++)		stu1[i6] = new int[9];
	int y[20];
	for (i6 = 0; i6 < 20; i6++)          y[i6] = 0;
	int stunum = 0;
	int q = 0;//�Ƿ�ѡ�еı�־λ
	for (i6 = 0; i6 < tools[4][3]; i6++) //tools[4][3]��ѧ������
	{
		q = 0;//�Ƿ�ѡ�еı�־λ
		int f[9];//�ݴ�ʹ�õ�ѧ����Ϣ
		for (j6 = 0; j6 < 9; j6++)
		{
			f[j6] = stuinform[(randnumber[i6] - 1)][j6];       //ǧ��ע�������stu������ǰ���stu���������������ɣ������������ƥ�䲻�ϣ�������������
		}
		for (k6 = 0; k6 < 20; k6++) //����20�ֿ��ܰ�
		{
			if (tools[2][k6] > 0) //����п���
			{
				if (y[k6] < tools[3][k6]) //��û����
				{
					int h = 0; //�Ƚϼ���λ

					for (int g = 0; g < 6; g++)
					{
						if (f[g] - u[k6][g] == 0)    h = h + 1;//ͳ����ͬλ����	
					}
					if (h == 6)          //ÿ��ѧ����̶��༶�Ŀ�Ŀ���бȽϣ����ϵľͷŽ�ȥ
					{
						q = 1;
						y[k6] = y[k6] + 1;
						break;
					}
				}

			}
		}
		if (q == 0)//��û���Ž�ȥ�Ļ�
		{

			for (int l = 0; l < 9; l++) stu1[stunum][l] = f[l];
			stunum++;
		}
	}
	return stu1;
}
int** gettools(int** stuinform, int stunum, int* randnumber)
{
	int** r;
	r = (int**)new int* [5];
	for (i6 = 0; i6 < 5; i6++)
	{
		*(r + i6) = new int[20];
	}
	for (i6 = 0; i6 < 20; i6++)//��r0���տγ�ID����
	{
		r[0][i6] = i6 + 15;
		r[1][i6] = 0;
		r[2][i6] = 0;
		r[3][i6] = 0;
		r[4][i6] = 0;
	}
	for (i6 = 0; i6 < stunum; i6 = i6 + 1) //ͳ�Ƹ���ѡ�����������
	{
		int o[6];
		for (int j6 = 0; j6 < 6; j6++) 	o[j6] = stuinform[(randnumber[i6] - 1)][j6];
		if ((o[0] + o[1] + o[2]) == 3)              r[1][0] = r[1][0] + 1;
		else if ((o[0] + o[1] + o[3]) == 3)			r[1][1] = r[1][1] + 1;
		else if ((o[0] + o[1] + o[4]) == 3)			r[1][2] = r[1][2] + 1;
		else if ((o[0] + o[1] + o[5]) == 3)			r[1][3] = r[1][3] + 1;
		else if ((o[0] + o[2] + o[3]) == 3)			r[1][4] = r[1][4] + 1;
		else if ((o[0] + o[2] + o[4]) == 3)			r[1][5] = r[1][5] + 1;
		else if ((o[0] + o[2] + o[5]) == 3)			r[1][6] = r[1][6] + 1;
		else if ((o[0] + o[3] + o[4]) == 3)			r[1][7] = r[1][7] + 1;
		else if ((o[0] + o[3] + o[5]) == 3)			r[1][8] = r[1][8] + 1;
		else if ((o[0] + o[4] + o[5]) == 3)			r[1][9] = r[1][9] + 1;
		else if ((o[1] + o[2] + o[3]) == 3)			r[1][10] = r[1][10] + 1;
		else if ((o[1] + o[2] + o[4]) == 3)			r[1][11] = r[1][11] + 1;
		else if ((o[1] + o[2] + o[5]) == 3)			r[1][12] = r[1][12] + 1;
		else if ((o[1] + o[3] + o[4]) == 3)			r[1][13] = r[1][13] + 1;
		else if ((o[1] + o[3] + o[5]) == 3)			r[1][14] = r[1][14] + 1;
		else if ((o[1] + o[4] + o[5]) == 3)			r[1][15] = r[1][15] + 1;
		else if ((o[2] + o[3] + o[4]) == 3)			r[1][16] = r[1][16] + 1;
		else if ((o[2] + o[3] + o[5]) == 3)			r[1][17] = r[1][17] + 1;
		else if ((o[2] + o[4] + o[5]) == 3)			r[1][18] = r[1][18] + 1;
		else if ((o[3] + o[4] + o[5]) == 3)			r[1][19] = r[1][19] + 1;
	}
	int c = 0;
	for (i6 = 0; i6 < 20; i6++)
	{
		if (r[1][i6] >= ld_6_3)
		{
			float rs = (r[1][i6] * 1.0 / (lu_6_3 * 1.0));
			int rsint = r[1][i6] / lu_6_3;
			int temp2 = rsint * (lu_6_3 - ld_6_3) + r[1][i6] - rsint * lu_6_3;
			if (temp2 >= ld_6_3)       rsint = rsint + 1;
			r[2][i6] = rsint; //��rsint���༶
			c = c + 1;//���� �������̶ֹ��༶
		}
	}
	int numclassnumb = 0;
	if (runsnumber_6_3 == 0)//�㷨��һ��ִ��
	{
		for (i6 = 0; i6 < 20; i6++)
		{
			numclassnumb = numclassnumb + r[2][i6];//ͳ�ư༶����
		}
		maxrunsnumber_6_3 = times_6_3 * (numclassnumb + 2);
	}

	if (runsnumber_6_3 > 0)  //�����ηְ��޹� ÿ���μ���һ���̶��༶
	{
		int e = runsnumber_6_3 / times_6_3; //������ٶ��ٸ��̶��࣬ÿ���μ���һ��
		for (i6 = 0; i6 < e; i6++)
		{
			int a = 0;                //ͳ�Ƶ�ǰ��x�ֿ���
			for (j6 = 0; j6 < 20; j6++)
			{
				if (r[2][j6] > 0)
				{
					a = a + 1;
				}
			}
			if (a != 0) //������й̶���
			{
				int b = rand() % a + 1; //��Ŀǰ�ļ��ֿ�����ѡһ��
				int c = 0;
				for (j6 = 0; j6 < 20; j6++) //������ʮ������
				{
					if (r[2][j6] > 0) //���������
					{
						c = c + 1;         //����
						if (c == b)   //�ж��Ƿ��ǵ�d������
						{

							r[2][j6] = r[2][j6] - 1; //����� �����һ���̶���
						}
					}
				}
			}

		}
		int d = 0;
		for (j6 = 0; j6 < 20; j6++)
		{

			d = d + r[2][j6];

		}
	}

	for (i6 = 0; i6 < 20; i6++)
	{
		if ((r[2][i6]) * lu_6_3 < (r[1][i6])) r[3][i6] = (r[2][i6]) * lu_6_3;//����������ڿ�����������r3����Ϊ��ѡ������ε�ѧ��
		else r[3][i6] = r[1][i6]; //���ܷŽ�ȥ
	}

	int num1 = 0;
	int num2 = 0;
	for (i6 = 0; i6 < 20; i6++) num1 = num1 + r[3][i6];
	for (i6 = 0; i6 < 20; i6++) num2 = num2 + r[2][i6];
	r[4][1] = num1; //�̶��������
	r[4][2] = num2; //�̶���ĸ���
	r[4][3] = stunum;
	r[4][4] = stunum - num1;
	r[4][5] = classsum_6_3 - num2;
	cout << "��ǰ�ⶨ�̶���������" << r[4][2] << endl;
	return r;

}
int getstudentnumber()
{
	Json::Reader reader;
	Json::Value root;
	Json::Value temp;
	int studentnumber_6_3;
	//���ļ��ж�ȡ����֤��ǰ�ļ���json�ļ�  
	ifstream in(jsonfilename, ios::binary);
	if (!in.is_open()) return 0;
	if (reader.parse(in, root))
	{

		for (i6 = 0; i6 < root.size(); i6++)//����ÿһ��
		{
			if (root[i6]["key"] == "Student")//�����Student
			{
				studentnumber_6_3 = root[i6]["value"].size();
			}
			if (root[i6]["key"] == "Class")//�����Class ���ַ�����ʽ�洢���ҺͰ༶���� 0�н��� 1�а༶����
			{
				classsum_6_3 = root[i6]["value"].size();
			}
		}
		in.close();
		if (classsum_6_3 < 10)
		{
			lu_6_3 = (studentnumber_6_3 / classsum_6_3) + 2;
			ld_6_3 = (studentnumber_6_3 / classsum_6_3) - 5;
		}
		else if (classsum_6_3 < 20)
		{
			lu_6_3 = (studentnumber_6_3 / classsum_6_3) + 1;
			ld_6_3 = (studentnumber_6_3 / classsum_6_3) - 4;
		}
		else if (classsum_6_3 < 30)
		{
			lu_6_3 = (studentnumber_6_3 / classsum_6_3) + 1;
			ld_6_3 = (studentnumber_6_3 / classsum_6_3) - 3;
		}
		else
		{
			lu_6_3 = (studentnumber_6_3 / classsum_6_3) + 1;
			ld_6_3 = (studentnumber_6_3 / classsum_6_3) - 2;
		}


		return studentnumber_6_3;
	}
	in.close();
	return 0;
}
int getstudentnumberfromstring()
{
	Json::Reader reader;
	Json::Value root;
	Json::Value temp;
	int studentnumber_6_3;

	if (reader.parse(str7, root))
	{

		for (i6 = 0; i6 < root.size(); i6++)//����ÿһ��
		{
			if (root[i6]["key"] == "Student")//�����Student
			{
				studentnumber_6_3 = root[i6]["value"].size();
			}
			if (root[i6]["key"] == "Class")//�����Class ���ַ�����ʽ�洢���ҺͰ༶���� 0�н��� 1�а༶����
			{
				classsum_6_3 = root[i6]["value"].size();
			}
		}
		if (classsum_6_3 < 10)
		{
			lu_6_3 = (studentnumber_6_3 / classsum_6_3) + 2;
			ld_6_3 = (studentnumber_6_3 / classsum_6_3) - 5;
		}
		else if (classsum_6_3 < 20)
		{
			lu_6_3 = (studentnumber_6_3 / classsum_6_3) + 1;
			ld_6_3 = (studentnumber_6_3 / classsum_6_3) - 4;
		}
		else if (classsum_6_3 < 30)
		{
			lu_6_3 = (studentnumber_6_3 / classsum_6_3) + 1;
			ld_6_3 = (studentnumber_6_3 / classsum_6_3) - 3;
		}
		else
		{
			lu_6_3 = (studentnumber_6_3 / classsum_6_3) + 1;
			ld_6_3 = (studentnumber_6_3 / classsum_6_3) - 2;
		}


		return studentnumber_6_3;
	}
	return 0;
}
int** readFileJson(int studentnumber_6_3)//���ļ��ж�ȡJSON  
{
	Json::Reader reader;
	Json::Value root;
	Json::Value temp;

	//���ļ��ж�ȡ����֤��ǰ�ļ���json�ļ�  
	ifstream in(jsonfilename, ios::binary);
	if (!in.is_open())
	{
		cout << "Error opening file\n" << endl;
		return 0;
	}

	if (reader.parse(in, root))     //if(reader.parse(str,root))
	{
		int** arr = new int* [studentnumber_6_3];
		for (i6 = 0; i6 < studentnumber_6_3; i6++)		 arr[i6] = new int[9];
		for (i6 = 0; i6 < root.size(); i6++)//����ÿһ��
		{
			if (root[i6]["key"] == "Student")//�����Student
			{
				studentno_6_3 = new string * [studentnumber_6_3]; //����ѧ���ַ������� 0��ѧ�� 1������
				for (j6 = 0; j6 < studentnumber_6_3; j6++)		studentno_6_3[j6] = new string[2];
				//��ȡ������Ϣ  
				for (unsigned int j6 = 0; j6 < root[i6]["value"].size(); j6++)
				{
					//ȡ��ѧ�ź����� ���ַ�����ʽ�洢
					int temp = root[i6]["value"][j6]["studentno_6_3"].asInt();
					stringstream s1;
					s1 << temp;
					string s11;
					s1 >> s11;
					studentno_6_3[j6][0] = s11;
					studentno_6_3[j6][1] = root[i6]["value"][j6]["name"].asString();
					//ȡ��־Ը������ ȡ���Ա� ѧ��  �����δ洢
					int* p;
					string ach = root[i6]["value"][j6]["vlounteer"].asString();//ȡ�����־Ը
					p = translate(ach);//����ת��Ϊ������b
					for (k6 = 0; k6 < 10; k6++)
					{
						arr[j6][k6] = p[k6];
					}
					arr[j6][6] = root[i6]["value"][j6]["studentno_6_3"].asInt();//����ѧ��
					arr[j6][7] = root[i6]["value"][j6]["sex"].asInt();//�����Ա�
					arr[j6][8] = 0;//ռλ 
				}
			}
			if (root[i6]["key"] == "Class")//�����Class ���ַ�����ʽ�洢���ҺͰ༶���� 0�н��� 1�а༶����
			{
				classno_6_3 = new string * [root[i6]["value"].size()];
				for (j6 = 0; j6 < root[i6]["value"].size(); j6++)		classno_6_3[j6] = new string[2];
				for (j6 = 0; j6 < root[i6]["value"].size(); j6++)
				{
					int temp = root[i6]["value"][j6]["classroom"].asInt();
					stringstream s2;
					s2 << temp;
					string s22 = s2.str();
					classno_6_3[j6][0] = s22;
					classno_6_3[j6][1] = root[i6]["value"][j6]["name"].asString();
				}
			}
			if (root[i6]["key"] == "Teacher_6_3")//�����Teacher  �ַ������� 0��id 1������ 2�� ѧ�� 3 ���Ա�
			{
				teacherno_6_3 = new string * [root[i6]["value"].size()];
				for (j6 = 0; j6 < root[i6]["value"].size(); j6++)		teacherno_6_3[j6] = new string[4];
				for (j6 = 0; j6 < root[i6]["value"].size(); j6++)
				{
					int temp = root[i6]["value"][j6]["teacherno_6_3"].asInt();
					stringstream s3;
					s3 << temp;
					string s33 = s3.str();
					teacherno_6_3[j6][0] = s33;
					teacherno_6_3[j6][1] = root[i6]["value"][j6]["name"].asString();
					teacherno_6_3[j6][2] = root[i6]["value"][j6]["subject"].asString();
					int temp2 = root[i6]["value"][j6]["sex"].asInt();
					stringstream s4;
					s4 << temp2;
					string s44 = s4.str();
					teacherno_6_3[j6][3] = s44;
					if (teacherno_6_3[j6][2] == "����") teacher_6_3[0] = teacher_6_3[0] + 1;
					else if (teacherno_6_3[j6][2] == "��ѧ")teacher_6_3[1] = teacher_6_3[1] + 1;
					else if (teacherno_6_3[j6][2] == "����")teacher_6_3[2] = teacher_6_3[2] + 1;
					else if (teacherno_6_3[j6][2] == "����")teacher_6_3[3] = teacher_6_3[3] + 1;
					else if (teacherno_6_3[j6][2] == "��ʷ")teacher_6_3[4] = teacher_6_3[4] + 1;
					else if (teacherno_6_3[j6][2] == "����")teacher_6_3[5] = teacher_6_3[5] + 1;
				}
			}
			if (root[i6]["key"] == "Classroom")//�����Classroom 0 name(��������) 1id 2max 3 min 4type A-0 B-1 [1][5]�ܽ�������
			{
				classroomno_6_3 = new int* [root[i6]["value"].size()];
				for (j6 = 0; j6 < root[i6]["value"].size(); j6++)		classroomno_6_3[j6] = new int[6];
				classroomno_6_3[1][5] = root[i6]["value"].size();
				for (j6 = 0; j6 < root[i6]["value"].size(); j6++)
				{
					classroomno_6_3[j6][0] = root[i6]["value"][j6]["name"].asInt();
					classroomno_6_3[j6][1] = root[i6]["value"][j6]["id"].asInt();
					classroomno_6_3[j6][2] = root[i6]["value"][j6]["max"].asInt();
					classroomlu_6_3 = root[i6]["value"][j6]["max"].asInt();
					classroomno_6_3[j6][3] = root[i6]["value"][j6]["min"].asInt();
					string temp = root[i6]["value"][j6]["type"].asString();
					if (temp == "A")
					{
						classroomno_6_3[j6][4] = 0;
						unadd_6_3 = unadd_6_3 + 1;
					}
					else if (temp == "B")
					{
						classroomno_6_3[j6][4] = 1;
						add_6_3 = add_6_3 + 1;
					}
				}
			}
			if (root[i6]["key"] == "Plot")//�����Plot
			{
				plotno_6_3 = new int* [root[i6]["value"].size()];
				for (j6 = 0; j6 < root[i6]["value"].size(); j6++)		plotno_6_3[j6] = new int[2];
				for (j6 = 0; j6 < root[i6]["value"].size(); j6++)
				{
					plotno_6_3[j6][0] = root[i6]["value"][j6]["id"].asInt();
					plotno_6_3[j6][1] = root[i6]["value"][j6]["value"].asInt();
				}
			}

		}
		in.close();
		return arr;
	}
	else
	{
		cout << "parse error\n" << endl;
		in.close();
		//return 0;
	}
	return 0;

}
int** readJson(int studentnumber_6_3)//���ַ����ж�ȡJSON  
{
	Json::Reader reader;
	Json::Value root;
	Json::Value temp;


	if (reader.parse(str7, root))
	{
		int** arr = new int* [studentnumber_6_3]; //���������ְ����б�
		for (i6 = 0; i6 < studentnumber_6_3; i6++)		 arr[i6] = new int[9];
		for (i6 = 0; i6 < root.size(); i6++)//����ÿһ��
		{
			if (root[i6]["key"] == "Student")//�����Student
			{
				studentno_6_3 = new string * [studentnumber_6_3]; //����ѧ���ַ������� 0��ѧ�� 1������
				for (j6 = 0; j6 < studentnumber_6_3; j6++)		studentno_6_3[j6] = new string[2];
				//��ȡ������Ϣ  
				for (unsigned int j6 = 0; j6 < root[i6]["value"].size(); j6++)
				{
					//ȡ��ѧ�ź����� ���ַ�����ʽ�洢
					int temp = root[i6]["value"][j6]["studentno_6_3"].asInt();
					stringstream s1;
					s1 << temp;
					string s11;
					s1 >> s11;
					studentno_6_3[j6][0] = s11;
					studentno_6_3[j6][1] = root[i6]["value"][j6]["name"].asString();
					//ȡ��־Ը������ ȡ���Ա� ѧ��  �����δ洢
					int* p;
					string ach = root[i6]["value"][j6]["vlounteer"].asString();//ȡ�����־Ը
					p = translate(ach);//����ת��Ϊ������b
					for (k6 = 0; k6 < 10; k6++)
					{
						arr[j6][k6] = p[k6];
					}
					arr[j6][6] = root[i6]["value"][j6]["studentno_6_3"].asInt();//����ѧ��
					arr[j6][7] = root[i6]["value"][j6]["sex"].asInt();//�����Ա�
					arr[j6][8] = 0;//ռλ ���ڴ�Ű���
				}
			}
			if (root[i6]["key"] == "Class")//�����Class ���ַ�����ʽ�洢���ҺͰ༶���� 0�н��� 1�а༶����
			{
				classno_6_3 = new string * [root[i6]["value"].size()];
				for (j6 = 0; j6 < root[i6]["value"].size(); j6++)		classno_6_3[j6] = new string[2];
				for (j6 = 0; j6 < root[i6]["value"].size(); j6++)
				{
					int temp = root[i6]["value"][j6]["classroom"].asInt();
					stringstream s2;
					s2 << temp;
					string s22 = s2.str();
					classno_6_3[j6][0] = s22;
					classno_6_3[j6][1] = root[i6]["value"][j6]["name"].asString();
				}
			}
			if (root[i6]["key"] == "Teacher_6_3")//�����Teacher  �ַ������� 0��id 1������ 2�� ѧ�� 3 ���Ա�
			{
				teacherno_6_3 = new string * [root[i6]["value"].size()];
				for (j6 = 0; j6 < root[i6]["value"].size(); j6++)		teacherno_6_3[j6] = new string[4];
				for (j6 = 0; j6 < root[i6]["value"].size(); j6++)
				{
					int temp = root[i6]["value"][j6]["teacherno_6_3"].asInt();
					stringstream s3;
					s3 << temp;
					string s33 = s3.str();
					teacherno_6_3[j6][0] = s33;
					teacherno_6_3[j6][1] = root[i6]["value"][j6]["name"].asString();
					teacherno_6_3[j6][2] = root[i6]["value"][j6]["subject"].asString();
					int temp2 = root[i6]["value"][j6]["sex"].asInt();
					stringstream s4;
					s4 << temp2;
					string s44 = s4.str();
					teacherno_6_3[j6][3] = s44;
					if (teacherno_6_3[j6][2] == "����")teacher_6_3[0] = teacher_6_3[0] + 1;
					else if (teacherno_6_3[j6][2] == "��ѧ")teacher_6_3[1] = teacher_6_3[1] + 1;
					else if (teacherno_6_3[j6][2] == "����")teacher_6_3[2] = teacher_6_3[2] + 1;
					else if (teacherno_6_3[j6][2] == "����")teacher_6_3[3] = teacher_6_3[3] + 1;
					else if (teacherno_6_3[j6][2] == "��ʷ")teacher_6_3[4] = teacher_6_3[4] + 1;
					else if (teacherno_6_3[j6][2] == "����")teacher_6_3[5] = teacher_6_3[5] + 1;
				}
			}
			if (root[i6]["key"] == "Classroom")//�����Classroom 0 name(��������) 1id 2max 3 min 4type A-0 B-1 [1][5]�ܽ�������
			{
				classroomno_6_3 = new int* [root[i6]["value"].size()];
				for (j6 = 0; j6 < root[i6]["value"].size(); j6++)		classroomno_6_3[j6] = new int[6];
				classroomno_6_3[1][5] = root[i6]["value"].size();
				for (j6 = 0; j6 < root[i6]["value"].size(); j6++)
				{
					classroomno_6_3[j6][0] = root[i6]["value"][j6]["name"].asInt();
					classroomno_6_3[j6][1] = root[i6]["value"][j6]["id"].asInt();
					classroomno_6_3[j6][2] = root[i6]["value"][j6]["max"].asInt();
					classroomlu_6_3 = root[i6]["value"][j6]["max"].asInt();
					classroomno_6_3[j6][3] = root[i6]["value"][j6]["min"].asInt();
					string temp = root[i6]["value"][j6]["type"].asString();
					if (temp == "A")
					{
						classroomno_6_3[j6][4] = 0;
						unadd_6_3 = unadd_6_3 + 1;
					}
					else if (temp == "B")
					{
						classroomno_6_3[j6][4] = 1;
						add_6_3 = add_6_3 + 1;
					}
				}
			}
			if (root[i6]["key"] == "Plot")//�����Plot
			{
				plotno_6_3 = new int* [root[i6]["value"].size()];
				for (j6 = 0; j6 < root[i6]["value"].size(); j6++)		plotno_6_3[j6] = new int[2];
				for (j6 = 0; j6 < root[i6]["value"].size(); j6++)
				{
					plotno_6_3[j6][0] = root[i6]["value"][j6]["id"].asInt();
					plotno_6_3[j6][1] = root[i6]["value"][j6]["value"].asInt();
				}
			}

		}
		//in.close();
		return arr;
	}
	else
	{
		cout << "parse error\n" << endl;
		//return 0;
	}
	return 0;

}
string writeFileJson(int** stu1out, int** stu2out, int** tools)//����Ϣ����ΪJSON��ʽ 
{
	Json::Value jsonoutput;
	Json::Value student;
	student["key"] = Json::Value("Student");
	Json::Value value;
	for (i6 = 0; i6 < tools[4][1]; i6++)//�������
	{
		value["studentno_6_3"] = Json::Value(stu2out[i6][6]);
		value["sex"] = Json::Value(stu2out[i6][7]);
		for (j6 = 0; j6 < tools[4][3]; j6++)
		{
			stringstream s2;
			s2 << studentno_6_3[j6][0];
			int iii;
			s2 >> iii;

			int bb = stu2out[i6][6];
			int aa = iii;
			//cout << studentno_6_3[j6][0] << endl;
			//cout << aa<<"-"<<bb<<"="<<aa-bb<< endl;
			if (aa - bb == 0)
			{
				value["name"] = Json::Value(studentno_6_3[j6][1]);
			}
		}
		int b[6];
		for (j6 = 0; j6 < 6; j6++)
		{
			b[j6] = stu2out[i6][j6];
		}
		string subject = translate2(b);
		value["vlounteer"] = Json::Value(subject);
		value["class"] = Json::Value(classname_6_3[i6]);
		value["shiftclass"] = Json::Value(0);
		student["value"].append(Json::Value(value));
	}
	for (i6 = 0; i6 < tools[4][4]; i6++)//�������
	{
		value["studentno_6_3"] = Json::Value(stu1out[i6][6]);
		value["sex"] = Json::Value(stu1out[i6][7]);
		for (j6 = 0; j6 < tools[4][3]; j6++)
		{
			stringstream s3;
			s3 << studentno_6_3[i6][0];
			int ii6;
			s3 >> ii6;
			int bbb = stu1out[i6][6];
			int aaa = ii6;
			//cout << studentno_6_3[j6][0] << endl;
			//cout << aa<<"-"<<bb<<"="<<aa-bb<< endl;
			if (aaa - bbb == 0)
			{
				value["name"] = Json::Value(studentno_6_3[j6][1]);
			}
			//if (stu1out[i6][6] == ii6) value["name"] = Json::Value(studentno_6_3[j6][1]);
		}
		int b[6];
		for (j6 = 0; j6 < 6; j6++)
		{
			b[j6] = stu1out[i6][j6];
		}
		string subject = translate2(b);
		value["vlounteer"] = Json::Value(subject);
		value["class"] = Json::Value(classname_6_3[tools[4][1] + i6]);
		value["shiftclass"] = Json::Value(classname1_6_3[0][i6]);
		student["value"].append(Json::Value(value));
	}
	jsonoutput.append(Json::Value(student));

	Json::Value classroom;
	classroom["key"] = Json::Value("classroom");
	Json::Value classroomvalue;
	for (i6 = tools[4][2]; i6 < tools[4][2] + countq_6_3; i6++)//�������߰����
	{

		classroomvalue["classroomno_6_3"] = Json::Value(shu_6_3[0][i6 - tools[4][2]]);
		if (i6 < tools[4][5] + tools[4][2])
		{
			classroomvalue["type"] = Json::Value("A");
			classroomvalue["subject1"] = Json::Value(disclass_6_3[0][i6]);
			classroomvalue["subject1num"] = Json::Value(disclass_6_3[3][i6]);

			classroomvalue["subject2"] = Json::Value(shu_6_3[2][i6 - tools[4][2]]);
			classroomvalue["subject2num"] = Json::Value(shu_6_3[1][i6 - tools[4][2]]);
		}
		else
		{
			classroomvalue["type"] = Json::Value("B");
			classroomvalue["subject1"] = Json::Value("��");
			classroomvalue["subject1num"] = Json::Value("��");
			classroomvalue["subject2"] = Json::Value(shu_6_3[2][i6 - tools[4][2]]);
			classroomvalue["subject2num"] = Json::Value(shu_6_3[1][i6 - tools[4][2]]);
		}
		classroom["value"].append(Json::Value(classroomvalue));
	}
	for (i6 = 0; i6 < tools[4][2]; i6++)//������Ϣ���
	{

		classroomvalue["classroomno_6_3"] = Json::Value(disclass_6_3[1][i6]);
		classroomvalue["type"] = Json::Value("A");
		classroomvalue["subject1"] = Json::Value(disclass_6_3[0][i6]);
		classroomvalue["subject1num"] = Json::Value(disclass_6_3[3][i6]);
		classroomvalue["subject2"] = Json::Value("��");
		classroomvalue["subject2num"] = Json::Value("��");
		classroom["value"].append(Json::Value(classroomvalue));
	}
	jsonoutput.append(Json::Value(classroom));


	//cout << "�ְ���JSON�ļ��Ѿ����������Ŀ¼��" << endl;
	//cout << "�ְ����ļ���Ϊ��" << endl;
	//Json::StyledWriter sw;//�������
	////cout << sw.write(jsonoutput) << endl << endl;  //���ַ�����ʽ������
	//time_t nowtime = time(NULL); //��ȡʱ����Ϣ
	//struct tm* p;
	//p = gmtime(&nowtime);
	//char timeinfo[256] = { 0 };
	//sprintf(timeinfo, "%d-%d-%d`%02d`%02d.json", 1 + p->tm_mon, p->tm_mday, 8 + p->tm_hour, p->tm_min, p->tm_sec);
	//puts(timeinfo);
	Json::StyledWriter sw;
	return sw.write(jsonoutput);
	//ofstream os;	//������ļ�
	//os.open(timeinfo);
	//if (!os.is_open())
	//{
	//	cout << "CANNOT OPEN" << endl;
	//}
	//os << sw.write(jsonoutput);
	//os.close();
}
int* translate(string volunteer)   //json�������Ŀ�Ŀת�����������ʾ
{
	int b[6];
	for (int i6 = 0; i6 < 6; i6++) b[i6] = 0;//���b
	string a("�ﻯ������ʷ��");
	for (int i6 = 0; i6 < 6; i6 = i6 + 2)//ÿ�μ��һ����ÿ����������ַ� һ��������
	{
		size_t j6 = a.find(volunteer[i6]);//���Ҳ����ص�һ�γ��ֵ�λ�ã������ַ�ÿ��ռ�����ֽ�
		switch (j6)
		{
		case 0: b[0] = 1; break;//��������b�����һλ��1����������
		case 2: b[1] = 1; break;
		case 4: b[2] = 1; break;
		case 6: b[3] = 1; break;
		case 8: b[4] = 1; break;//��ʷ�����ֵĽ��һ������ͬѧУ������ʷ���ַ�ʽ��ʾ���ſ�
		case 10: b[4] = 1; break;
		case 12: b[5] = 1; break;
		}
	}
	return b;
}
string  translate2(int* b)//�������ƿ�Ŀ����Ϊ����
{
	string sub1 = "��";
	string sub2 = "��";
	string sub3 = "��";
	string sub4 = "��";
	string sub5 = "ʷ";
	string sub6 = "��";
	string sub7;
	if (b[0] == 1)   sub7 = sub7 + sub1;
	if (b[1] == 1)   sub7 = sub7 + sub2;
	if (b[2] == 1)   sub7 = sub7 + sub3;
	if (b[3] == 1)   sub7 = sub7 + sub4;
	if (b[4] == 1)   sub7 = sub7 + sub5;
	if (b[5] == 1)   sub7 = sub7 + sub6;
	return sub7;

}
int* swit(int p, int b[])
{

	switch (p)
	{
	case 0: b[0] = 1, b[1] = 1, b[2] = 0, b[3] = 0, b[4] = 0, b[5] = 0; break;
	case 1: b[0] = 1, b[1] = 0, b[2] = 1, b[3] = 0, b[4] = 0, b[5] = 0; break;
	case 2: b[0] = 1, b[1] = 0, b[2] = 0, b[3] = 1, b[4] = 0, b[5] = 0; break;
	case 3: b[0] = 1, b[1] = 0, b[2] = 0, b[3] = 0, b[4] = 1, b[5] = 0; break;
	case 4: b[0] = 1, b[1] = 0, b[2] = 0, b[3] = 0, b[4] = 0, b[5] = 1; break;
	case 5: b[0] = 0, b[1] = 1, b[2] = 1, b[3] = 0, b[4] = 0, b[5] = 0; break;
	case 6: b[0] = 0, b[1] = 1, b[2] = 0, b[3] = 1, b[4] = 0, b[5] = 0; break;
	case 7: b[0] = 0, b[1] = 1, b[2] = 0, b[3] = 0, b[4] = 1, b[5] = 0; break;
	case 8: b[0] = 0, b[1] = 1, b[2] = 0, b[3] = 0, b[4] = 0, b[5] = 1; break;
	case 9: b[0] = 0, b[1] = 0, b[2] = 1, b[3] = 1, b[4] = 0, b[5] = 0; break;
	case 10: b[0] = 0, b[1] = 0, b[2] = 1, b[3] = 0, b[4] = 1, b[5] = 0; break;
	case 11: b[0] = 0, b[1] = 0, b[2] = 1, b[3] = 0, b[4] = 0, b[5] = 1; break;
	case 12: b[0] = 0, b[1] = 0, b[2] = 0, b[3] = 1, b[4] = 1, b[5] = 0; break;
	case 13: b[0] = 0, b[1] = 0, b[2] = 0, b[3] = 1, b[4] = 0, b[5] = 1; break;
	case 14: b[0] = 0, b[1] = 0, b[2] = 0, b[3] = 0, b[4] = 1, b[5] = 1; break;
	case 15: b[0] = 1, b[1] = 1, b[2] = 1, b[3] = 0, b[4] = 0, b[5] = 0; break;
	case 16: b[0] = 1, b[1] = 1, b[2] = 0, b[3] = 1, b[4] = 0, b[5] = 0; break;
	case 17: b[0] = 1, b[1] = 1, b[2] = 0, b[3] = 0, b[4] = 1, b[5] = 0; break;
	case 18: b[0] = 1, b[1] = 1, b[2] = 0, b[3] = 0, b[4] = 0, b[5] = 1; break;
	case 19: b[0] = 1, b[1] = 0, b[2] = 1, b[3] = 1, b[4] = 0, b[5] = 0; break;
	case 20: b[0] = 1, b[1] = 0, b[2] = 1, b[3] = 0, b[4] = 1, b[5] = 0; break;
	case 21: b[0] = 1, b[1] = 0, b[2] = 1, b[3] = 0, b[4] = 0, b[5] = 1; break;
	case 22: b[0] = 1, b[1] = 0, b[2] = 0, b[3] = 1, b[4] = 1, b[5] = 0; break;
	case 23: b[0] = 1, b[1] = 0, b[2] = 0, b[3] = 1, b[4] = 0, b[5] = 1; break;
	case 24: b[0] = 1, b[1] = 0, b[2] = 0, b[3] = 0, b[4] = 1, b[5] = 1; break;
	case 25: b[0] = 0, b[1] = 1, b[2] = 1, b[3] = 1, b[4] = 0, b[5] = 0; break;
	case 26: b[0] = 0, b[1] = 1, b[2] = 1, b[3] = 0, b[4] = 1, b[5] = 0; break;
	case 27: b[0] = 0, b[1] = 1, b[2] = 1, b[3] = 0, b[4] = 0, b[5] = 1; break;
	case 28: b[0] = 0, b[1] = 1, b[2] = 0, b[3] = 1, b[4] = 1, b[5] = 0; break;
	case 29: b[0] = 0, b[1] = 1, b[2] = 0, b[3] = 1, b[4] = 0, b[5] = 1; break;
	case 30: b[0] = 0, b[1] = 1, b[2] = 0, b[3] = 0, b[4] = 1, b[5] = 1; break;
	case 31: b[0] = 0, b[1] = 0, b[2] = 1, b[3] = 1, b[4] = 1, b[5] = 0; break;
	case 32: b[0] = 0, b[1] = 0, b[2] = 1, b[3] = 1, b[4] = 0, b[5] = 1; break;
	case 33: b[0] = 0, b[1] = 0, b[2] = 1, b[3] = 0, b[4] = 1, b[5] = 1; break;
	case 34: b[0] = 0, b[1] = 0, b[2] = 0, b[3] = 1, b[4] = 1, b[5] = 1; break;
	}
	return(b);
}
void rand_of_n(int a[], int n)
{
	int i6;
	struct element ele[MAX];
	srand((int)time(0));  // ��ʼ����������� 
	for (i6 = 0; i6 < n; i6++)
	{
		ele[i6].data = rand();  // �������һ���� 
		ele[i6].index = i6 + 1;
	}
	qsort(ele, n, sizeof(ele[0]), cmp);  //���� 
	for (i6 = 0; i6 < n; i6++)
	{
		a[i6] = ele[i6].index;
	}
}
int cmp(const void* a, const void* b)   // ��������
{
	return((struct element*)a)->data - ((struct element*)b)->data;
}
