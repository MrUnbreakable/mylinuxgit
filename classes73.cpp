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
string str;

string returnstr73;
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

int i, j, k, ii;
int times = 2;									  //ÿtimes�ּ���һ������
int lu = 0;                                       //�༶��������
int ld = 0;                                       //�༶��������
int classroomlu = 0;                              //������������
int unadd = 0;                                    //��ͨ��������
int add = 0;                                      //�߰�ʱ���ӵİ༶��
int classsum = 0;                                 //�ܰ༶��
int bigclassmax = 65;							  //���������
int bigclassnum = 1;							  //����Ҹ���
const int NIND = 100;                             //��Ⱥ����
const int MAXGEN = 100;                           //�Ŵ�����
const double px = 0.97;                           //������
const double pm = 0.1;                            //������
const double GGAP = 0.9;                          //����

int complete = 0;                                 //�ְ���ɱ�־λ
int runsnumber = 0;                               //�㷨ִ�д���
int maxrunsnumber = 3;                            //����㷨ִ�д��� ���︳��ֵ ��gettools�����������߰������Զ��������¸�ֵ
int ** lists = new int *[2];                      //���������ְ����б�
int **out1 = new int *[2];                        //�涨�����������Ž��  out1[2][PRECI]  0�зŰ༶���� 1�з�����
string ** studentno;                              //����ѧ��������ѧ�ż�¼�� ����������ƥ����
string ** teacherno;
int teacher[7] = { 0,0,0,0,0,0,0 };
string ** classno;
int ** plotno;
int ** classroomno;
int * classname;
int ** classname1;
int ** shu;
int ** studentinformation;
int studentnumber;
int ** disclass;//����+�������
int allgocla = 0;//���߰���
int countq;
//************������������**********************************************
int ** gettools_7_3(int**stuinform, int stunum, int*randnumber);//��ȡ�̶�����Ϣ
int ** getstu1_7_3(int**stuinform, int **tools, int*randnumber);//��ȡ�߶�ѧ����Ϣ
int ** getstu2_7_3(int**stuinform, int **tools, int*randnumber);//��ȡ����ѧ����Ϣ
int ** sectionstu2_7_3(int**stu2, int**tools);//�����ְ࣬����ѧ���ְ���
int getstudentnumber_7_3();                   //��ȡѧ�����������ڴ�������
int getstudentnumberfromstring_7_3();                   //���ַ����л�ȡѧ�����������ڴ�������
int ** readFileJson_7_3(int studentnumber);                    //���ļ��ж�ȡJSON��һ���洢��JSON��ʽ�ַ������ļ�
int ** readJson_7_3(int studentnumber);                    //���ַ����ж�ȡJSON
int *swit_7_3(int p, int b[]);                //pΪ�γ�ID b����洢�γ̶�Ӧ��λ�����Ʊ���
int * translate_7_3(string volunteer);        //��ѡ������ĺ�����Ϸ����һ�����еĶ����Ʊ�ʾ
string translate2_7_3(int * b);               //��ѡ������Ķ����Ʒ�����ַ���
int ** updatepopulation_7_3(int ** pop, double * objv, int gen, int PRECI, int ** out); //������Ⱥ��������ѡ������塢���桢����
int cmp_7_3(const void *a, const void *b);    //�������� 
void rand_of_n_7_3(int a[], int n);           //���� 1-n ��������в��浽 a[] ��
double  ** ranking_7_3(int**stu1, int **tools, int ** pop);//��ȡ��Ӧ��ֵ
int ** genetic_7_3(int**stu1, int **tools); //�Ŵ��㷨
string writeFileJson_7_3(int** stu1out, int** stu2out, int** tools);   //����Ϣ����ΪJSON��ʽ 
void sectionclassroom_7_3(int **stu1out, int **stu2out, int**tools);   //����Ϣ����ΪJSON��ʽ 
//**********************************************************************
char * makeclass73json(char * inputstr)
{
	string strInput = inputstr;
	string outputStr = makeclass73(strInput);

	char *data;
	int len = outputStr.length();
	data = (char *)malloc((len + 1) * sizeof(char));
	outputStr.copy(data, len, 0);

	//char * strOutput = (char*)outputStr.data();
	return data;
}
string makeclass73(string inputstr)
{
	/********��json�ļ���ȡ**********/
	/******���ַ����ж�ȡ  �ַ���str��ȡ��txt**********/
	if (reader == 1)
	{
		str = inputstr;
		studentnumber = getstudentnumberfromstring_7_3();//���ַ����л�ȡѧ��������
		studentinformation = readJson_7_3(studentnumber);//��ȡѧ����Ϣ����ά����studentinformation
	}
	else if (reader == 0)
	{
		studentnumber = getstudentnumber_7_3();//��ȡѧ��������
		studentinformation = readFileJson_7_3(studentnumber);//��ȡѧ����Ϣ����ά����studentinformation
	}
	/*******************/

	if (choose != 0)
	{
		for (int i = 0; i < 5; i++)
		{
			if (plotno[i][0] == 1) lu = plotno[i][1];//ѡ���Ƿ�ʹ��ѧУ�����Ľ�������
			if (plotno[i][0] == 2) ld = plotno[i][1];//ѡ���Ƿ�ʹ��ѧУ�����Ľ�������
		}
	}
	for (int i = 0; i < 5; i++)
	{
		if (plotno[i][0] == 4) bigclassmax = plotno[i][1];//���������
		if (plotno[i][0] == 5) bigclassnum = plotno[i][1];//����Ҹ���
	}

	int *rand = new int[studentnumber]; //��������rand������������������ѧ����Ϣ˳��
	rand_of_n_7_3(rand, studentnumber);
	while (complete != 1)
	{

		if (runsnumber < maxrunsnumber)//������д���û������
		{
			cout << "���ڽ��зְ࣬���е�" << runsnumber + 1 << "�γ���" << endl;
			int ** tools = gettools_7_3(studentinformation, studentnumber, rand);//��ȡͳ�ƹ��Ĺ�������
			int ** stu2 = getstu2_7_3(studentinformation, tools, rand);//��ȡ����ѧ����Ϣ
			int ** stu1 = getstu1_7_3(studentinformation, tools, rand);//��ȡ����ѧ����Ϣ
			int ** stu2out = sectionstu2_7_3(stu2, tools);//��ȡ�����ְ���
			int ** stu1out = genetic_7_3(stu1, tools); //�Ŵ��㷨 ��ȡ�����ְ���
			runsnumber = runsnumber + 1;//��¼�㷨���д���
			if (complete == 1)//���������
			{
				sectionclassroom_7_3(stu1out, stu2out, tools);
				returnstr73 = writeFileJson_7_3(stu1out, stu2out, tools);
			}
		}
		else
		{
			cout << "�ְ�ʧ��" << endl;
			break;
		}
	}
	return returnstr73;
}
void sectionclassroom_7_3(int **stu1out, int **stu2out, int**tools)
{
	int PRECI = tools[4][5];           //��ȡ�����༶����

	int *classcontain = new int[PRECI];
	for (i = 0; i < PRECI; i++)
	{
		if (i < bigclassnum)classcontain[i] = bigclassmax;
		else classcontain[i] = lu;
	}
	//��ÿ��ѧ������༶,6�����δ�Ű༶���͡��༶���ơ�����Ӧ�÷ŵ����������������з��˵�������������������Ů����������
	int **stuplus = new int *[tools[4][3]];
	for (i = 0; i < tools[4][3]; i++)		stuplus[i] = new int[10];
	for (i = 0; i < tools[4][1]; i++)//���붨��ѧ����Ϣ
	{
		for (j = 0; j < 10; j++) stuplus[i][j] = stu2out[i][j];
	}
	for (i = tools[4][1]; i < tools[4][3]; i++)//���붨��ѧ����Ϣ
	{
		for (j = 0; j < 10; j++)
		{
			stuplus[i][j] = stu1out[i - tools[4][1]][j];
		}
	}
	int stu2num = tools[4][1];//��������
	int ss = tools[4][2];//��������
	int NUM = tools[4][2] + tools[4][5];//�ܰ༶����
	//int PRECI = tools[4][5];//������һ������
	int stu1num = tools[4][4];//��������
	disclass = new int *[6]; //
	for (i = 0; i < 6; i++)		disclass[i] = new int[NUM];
	classname = new int[tools[4][3]];//���������
	classname1 = new int *[2]; //�߰�������Ƿ��ѷ���
	for (i = 0; i < 2; i++)		classname1[i] = new int[tools[4][4]];
	for (i = 0; i < tools[4][4]; i++) classname1[1][i] = 0;//�ڶ������� ������¼�Ƿ�����
	for (i = 0; i < ss; i++)
	{
		disclass[0][i] = lists[0][i];//�̶�����
		disclass[2][i] = lists[1][i];//�̶�������
	}
	for (i = ss; i < NUM; i++)
	{
		disclass[0][i] = out1[0][i - ss];//�߰����
		disclass[2][i] = out1[1][i - ss];//�߰�����
	}
	for (j = 0; j < classroomno[1][5]; j++)
	{
		if (classroomno[j][4] == 2)    classroomno[j][4] = 0;
		else if (classroomno[j][4] == 3)    classroomno[j][4] = 1;
	}
	for (i = 0; i < NUM; i++)
	{
		int flag = 0;
		for (j = 0; j < classroomno[1][5]; j++)//���۶��� ȫ�������Ͻ���
		{
			if (classroomno[j][4] == 0 && flag == 0)//��ͨ����
			{
				disclass[1][i] = classroomno[j][1];//�������� �õĽ���id
				classroomno[j][4] = 2;
				flag = 1;
			}
		}
		//for (int j = 0; j < classroomno[1][5]; j++)
		//{
		//	if (classroomno[j][4] == 1 && flag == 0)
		//	{
		//		disclass[1][i] = classroomno[j][1];//�������� �õĽ���id
		//		classroomno[j][4] = 3;
		//		flag = 1;
		//	}		
		//}
		disclass[3][i] = 0;//
		disclass[4][i] = 0;//��
		disclass[5][i] = 0;//Ů
	}


	for (i = 0; i < tools[4][3]; i++)//����ѧ�� �ֶ��� ��Ů����
	{
		int aaa = 1;//��¼�ܷ�Ž�ȥ
		int bbb = -1;//��¼λ��
		int ccc;//��¼��С����
		if (bigclassnum != 0)
		{
			ccc = bigclassmax;
		}
		else
		{
			ccc = lu;
		}
		for (j = 0; j < NUM; j++)//�������а༶
		{
			aaa = stuplus[i][9] - disclass[0][j];//9����   �������
			if (aaa == 0)//����ܷŽ�ȥ
			{
				if (disclass[3][j] < disclass[2][j])//�����û��������༶
				{
					if (stuplus[i][8] == 1)//�����
					{
						if (disclass[4][j] < ccc)//�����С
						{
							bbb = j;//��¼λ��
							ccc = disclass[4][j];//��С����
						}
					}
					else
					{
						if (disclass[5][j] < ccc)
						{

							bbb = j;
							ccc = disclass[5][j];
						}
					}
				}
			}
		}
		classname[i] = disclass[1][bbb];//��¼���ѧ�����䵽���ĸ����ң���Ϊ��Ϣ���ʮ��
		if (stuplus[i][8] == 1)
		{
			disclass[4][bbb] = disclass[4][bbb] + 1;//�ж��Ա� 
		}
		else
		{
			disclass[5][bbb] = disclass[5][bbb] + 1;//
		}
		disclass[3][bbb] = disclass[4][bbb] + disclass[5][bbb];
	}


	int ** goone = new int *[9]; //�����߶�����ѧ��ͳ���б�
	for (i = 0; i < 9; i++)		goone[i] = new int[PRECI];//0 ���� 1�༶id 2����3��ѧ 4���� 5���� 6��ʷ 7����
	for (i = ss; i < NUM; i++)
	{
		goone[0][i - ss] = disclass[0][i];//���� ժ������
		goone[1][i - ss] = disclass[1][i];//�༶��
	}
	for (i = 2; i < 9; i++) //����
	{
		for (j = 0; j < PRECI; j++)
		{
			goone[i][j] = 0;
		}
	}
	for (i = 0; i < stu1num; i++)//����ѧ��
	{
		int ddd = 1;
		for (j = 0; j < PRECI; j++)//������༶
		{
			ddd = goone[1][j] - classname[i + tools[4][1]];//�����ѧ����������
			if (ddd == 0)
			{
				for (k = 0; k < 7; k++)
				{
					goone[k + 2][j] = goone[k + 2][j] + stuplus[i + tools[4][1]][k];//ͳ��ѧ����Ŀ 
				}
				break;
			}
		}
	}

	for (i = 2; i < 9; i++)//���㶨����Ĺ̶���Ŀ
	{
		for (j = 0; j < PRECI; j++)
		{
			int b[7];
			swit_7_3(goone[0][j], b);
			for (k = 0; k < 7; k++)
			{
				if (b[k] == 1) goone[k + 2][j] = 0;
			}
		}
	}
	for (j = 0; j < 9; j++)//************************************************************************
	{
		for (k = 0; k < PRECI; k++)
		{
			cout.width(3);
			cout << goone[j][k] << " ";
		}
		cout << endl;
	}





	int gocla[7];//�����߰���
	//cout << "��ʾ����Ŀ0-���� 1-��ѧ 2-���� 3-���� 4-��ʷ 5-����"<< endl;
	int subjecttotal[7] = { 0,0,0,0,0,0,0 };
	for (i = 0; i < 7; i++)
	{

		for (int j = 0; j < PRECI; j++)
		{
			subjecttotal[i] = subjecttotal[i] + goone[i + 2][j];
		}
		gocla[i] = ceil(subjecttotal[i] / (lu*1.0));
		string subtemp;
		if (i == 0) subtemp = "��";
		else if (i == 1) subtemp = "��";
		else if (i == 2) subtemp = "��";
		else if (i == 3) subtemp = "��";
		else if (i == 4) subtemp = "ʷ";
		else if (i == 5) subtemp = "��";
		else if (i == 6) subtemp = "��Ϣ";

		cout << "��Ŀ " << subtemp << " ���߰�����Ϊ" << subjecttotal[i] << "   ������" << gocla[i] << "��" << endl;
		allgocla = allgocla + gocla[i];
	}

	cout << "�����߰���Ϊ��" << allgocla << endl;

	int * shu1 = new int[NUM];
	for (j = 0; j < NUM; j++)
	{
		shu1[j] = -1;
	}
	countq = 0;
	int rn1[7] = { 0,0,0,0,0,0,0};
	for (j = 0; j < 7; j++)
	{
		rn1[j] = gocla[j];
	}


	while (allgocla)
	{
		if (countq < PRECI)
		{
			int aa = -1;
			int bb = -1;
			int cc = -1;
			for (j = 0; j < 7; j++)
			{
				for (k = 0; k < PRECI; k++)
				{
					if (goone[j + 2][k] > aa)
					{
						aa = goone[j + 2][k];
						bb = j;
						cc = k;
					}
				}
			}
			goone[bb + 2][cc] = -1;
			if (rn1[bb] > 0 && shu1[cc] == -1)
			{
				shu1[cc] = bb;
				rn1[bb] = rn1[bb] - 1;
				allgocla = allgocla - 1;
				countq = countq + 1;
				if (classcontain[cc] < subjecttotal[bb])
				{
					subjecttotal[bb] = subjecttotal[bb] - classcontain[cc];
					if (ceil(subjecttotal[bb] * 1.0 / lu) < rn1[bb])
					{
						gocla[bb] = gocla[bb] - 1;
						rn1[bb] = rn1[bb] - 1;
						allgocla = allgocla - 1;
					}
				}
			}

		}
		else if (countq >= PRECI)
		{
			for (j = 0; j < 7; j++)
			{
				if (rn1[j] != 0)
				{
					shu1[countq + 1] = j;
					rn1[j] = rn1[j] - 1;
					allgocla = allgocla - 1;
					countq = countq + 1;

					break;
				}
			}
		}
	}
	int *classcontain1 = new int[countq];
	for (j = 0; j < countq; j++)
	{
		if (j < bigclassnum)classcontain1[j] = bigclassmax;
		else classcontain1[j] = lu;
	}










	//�߰������Ҳ���	
	int * all = new int[7 * PRECI];//��Ÿ����߿�����
	for (i = 0; i < 7; i++)
	{
		for (j = 0; j < PRECI; j++)
		{
			all[i*PRECI + j] = goone[i + 2][j];//�����߿Ƶ���all
		}
	}
	int tempa;//����
	for (i = 0; i < 7 * PRECI; i++)
	{
		for (j = 1; j < 7 * PRECI - i; j++)
		{
			if (all[j] > all[j - 1])
			{
				tempa = all[j];
				all[j] = all[j - 1];
				all[j - 1] = tempa;
			}
		}
	}//all�������
	shu = new int *[3]; //��ŵ�һ�� ��� �ڶ���  �Ƿ񿪰�0δ�� 1 ��  ������ ����ʲô��
	for (i = 0; i < 3; i++)		shu[i] = new int[countq];
	for (i = 0; i < countq; i++)
	{
		shu[1][i] = 0;
		shu[2][i] = 7;
		if (i < PRECI)
		{
			shu[0][i] = goone[1][i]; //dingerzouyi
		}
		else
		{
			int flag2 = 0;
			for (int j = 0; j < classroomno[1][5]; j++)
			{
				if (classroomno[j][4] == 1 && flag2 == 0)
				{
					shu[0][i] = classroomno[j][1];//�������� �õĽ���id
					classroomno[j][4] = 3;
					flag2 = 1;
				}
			}
		}
	}

	int gocla1[7] = { 0,0,0,0,0,0,0 };//�����Ѿ�����ʲô��
	int * gocla2 = new int[PRECI];
	for (i = 0; i < PRECI; i++)
	{
		gocla2[i] = 1;
	}
	int ggg = -1, hhh = -1, js = 0, tt;
	for (int qr = 0; qr < 7 * PRECI; qr++)//����all
	{
		ggg = -1;
		hhh = -1;
		int flag1 = 0;
		for (i = 0; i < 7; i++)//����goone
		{
			for (j = 0; j < PRECI; j++)
			{
				if (gocla2[j] == 1)//�����໹û����
				{
					tt = goone[i + 2][j] - all[qr];//�˶��Ƿ�������ʵİ༶
					if (tt == 0 && gocla[i] - gocla1[i] != 0)
					{
						ggg = i; hhh = j;//��¼�� ��
						flag1 = 1;
						break;
					}
				}
			}
			if (flag1 == 1) { break; }
		}
		if (gocla[ggg] - gocla1[ggg] != 0 && ggg != -1)//�����û����
		{
			shu[1][hhh] = 1;
			shu[2][hhh] = ggg;
			gocla1[ggg] = gocla1[ggg] + 1;
			js = js + 1;
			gocla2[hhh] = 0;
		}
		if (js == PRECI)
		{
			break;
		}
	}

	if (countq - PRECI > 0)//�����add
	{
		for (i = 0; i < countq - PRECI; i++)//����add
		{
			for (j = 0; j < 7; j++)//��������ѧ��
			{
				if (gocla[j] - gocla1[j] != 0)//�����ĳ��Ŀû����
				{
					gocla1[j] = gocla1[j] + 1;
					shu[1][PRECI + i] = 1;
					shu[2][PRECI + i] = j;
					break;
				}
			}
		}
	}

	for (j = 0; j < countq; j++)
	{
		shu[1][j] = 0;//���� ��������
	}
	for (i = 0; i < stu1num; i++)
	{
		int classsubj = 7;//���ҿ�Ŀ
		int stusubj = 6;//ѧ����Ŀ
		int classsubjno = -1;
		for (j = 0; j < PRECI; j++)
		{
			if (classname[stu2num + i] == shu[0][j])
			{
				classsubj = shu[2][j];//����ԭ���ҵ��߰��
				classsubjno = j;
			}
		}
		int b[7];
		swit_7_3(stuplus[stu2num + i][9], b);
		for (j = 0; j < 7; j++)
		{
			if (stuplus[stu2num + i][j] - b[j] == 1) stusubj = j;//������Ҫ�ߵĿ�
		}
		if (stusubj == classsubj)//���ԭ����Է�
		{
			classname1[0][i] = classname[stu2num + i];//�ŵ�ԭ�༶
			classname1[1][i] = 1;
			shu[1][classsubjno] = shu[1][classsubjno] + 1;//����
		}
	}
	for (i = 0; i < stu1num; i++)//�������ж���ѧ��
	{
		if (classname1[1][i] == 0)//������ѧ����û����
		{
			int aaa = 1;//��¼�ܷ�Ž�ȥ
			int bbb = -1;//��¼λ��
			int ccc;
			if (bigclassnum != 0)
			{
				ccc = bigclassmax;
			}
			else
			{
				ccc = lu;
			}
			int stusubj = 7;//ѧ����Ŀ
			int b[7];
			swit_7_3(stuplus[stu2num + i][9], b);
			for (j = 0; j < 7; j++)
			{
				if (stuplus[stu2num + i][j] - b[j] == 1) stusubj = j;//������Ҫ�ߵĿ�
			}
			for (j = 0; j < countq; j++)
			{
				aaa = stusubj - shu[2][j];//   �������
				if (aaa == 0)//����ܷŽ�ȥ
				{
					if (shu[1][j] < classcontain1[j])//�����û��������༶**************************
					{
						if (shu[1][j] < ccc)//�����С
						{
							bbb = j;//��¼λ��
							ccc = shu[1][j];//��С����
						}
					}
				}
			}
			classname1[0][i] = shu[0][bbb];//��¼���ѧ�����䵽���ĸ�����
			classname1[1][i] = 1;
			shu[1][bbb] = shu[1][bbb] + 1;//����
		}
	}
	cout << "----------------------------------------------------------------" << endl;
	for (i = 0; i < 3; i++)/************************************************************/
	{
		if (i == 0) cout << " ��һ����:  ";
		else if (i == 1) cout << " �༶������ ";
		else if (i == 2) cout << " �������ͣ� ";
		for (j = 0; j < countq; j++)
		{
			cout.width(3);
			if (i < 2) cout << shu[i][j] << "  ";
			else if (i == 2)
			{
				if (shu[i][j] == 0) { cout.width(3); cout << "��   "; }
				else if (shu[i][j] == 1) { cout.width(3); cout << "��   "; }
				else if (shu[i][j] == 2) { cout.width(3); cout << "��   "; }
				else if (shu[i][j] == 3) { cout.width(3); cout << "��   "; }
				else if (shu[i][j] == 4) { cout.width(3); cout << "ʷ   "; }
				else if (shu[i][j] == 5) { cout.width(3); cout << "��   "; }
				else if (shu[i][j] == 6) { cout.width(3); cout << "��Ϣ   "; }
			}
		}
		cout << " \n";
	}
	cout << endl;

}
int **  genetic_7_3(int**stu1, int **tools)
{
	int gen = 0;                      //�Ŵ�����������
	int stu1numb = tools[4][4];       //��ȡ����ѧ������
	int PRECI = tools[4][5];           //��ȡ�����༶����

	int **pop = new int *[NIND];      //popΪ������Ⱥ pop[NIND][tools[4][5]]
	for (i = 0; i < NIND; i++)		pop[i] = new int[PRECI];


	for (i = 0; i < 2; i++)		    out1[i] = new int[PRECI];

	double **trace = new double *[2];     //���������ѷְ෽ʽ trace[2][MAXGEN]������������
	for (i = 0; i < 2; i++)		trace[i] = new double[MAXGEN];

	double *objv = new double[NIND];  //��Ӧ��ֵ

	double globalminobjv = 0.0; //��¼ȫ����С��Ӧ��ֵ

	int *stufinalclass = new int[stu1numb];  //���ڼ�¼ѧ������ѡ��

	int **stu1out = new int *[stu1numb];        //�����һ��ѧ��ѡ����Ϣ���ְ���
	for (i = 0; i < stu1numb; i++)		    stu1out[i] = new int[10];

	for (i = 0; i < NIND; i++)       //������ɳ�ʼ��Ⱥ
	{
		for (j = 0; j < PRECI; j++)
		{
			int randompop = rand();
			pop[i][j] = randompop % 21;           //����0-20�����������ʾ���ɵ����������һ�༶����
		}
	}

	while (gen < MAXGEN)                    //
	{

		double ** tools2 = ranking_7_3(stu1, tools, pop);     //��ȡ��Ӧ��ֵ�������ص������Ÿ�ѧ���ְ�ȥ���Լ���������

		for (int i = 0; i < NIND; i++)
		{
			double tempobjv = tools2[i][2];
			objv[i] = tempobjv;
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
				for (i = 0; i < stu1numb; i++)
				{
					stufinalclass[i] = tools2[i][0];   //��¼���Ž�ѧ���༶����
				}
				for (i = 0; i < PRECI; i++)
				{
					out1[0][i] = pop[minpos][i];       //ȫ�����Ÿ���id
					out1[1][i] = tools2[i][1];         //ȫ�����Ÿ������ѧ������
				}
			}
		}
		else//����ǵ�0�� ���¼0�����Ž�
		{
			globalminobjv = minobjv;             //��¼ȫ��������Ӧ��ֵ
			for (i = 0; i < stu1numb; i++)
			{
				stufinalclass[i] = tools2[i][0];    //��¼���Ž�ѧ���༶����
			}
			for (i = 0; i < PRECI; i++)
			{
				out1[0][i] = pop[minpos][i];      //ȫ�����Ÿ���id
				out1[1][i] = tools2[i][1];      //ȫ�����Ÿ������ѧ������
			}
		}

		pop = updatepopulation_7_3(pop, objv, gen, PRECI, out1);//ѡ�񽻲����

		gen = gen + 1;
	}


	if (globalminobjv < PRECI * 10)//�ж���Ӧ��ֵ�Ƿ���
	{
		complete = 1;   // �����Ӧ��ֵ��С������ɹ��ְࣩ�����־�ְ����
		cout << "----------------------------------------------------------------" << endl;
		cout << "��С��Ӧ��ֵ��" << globalminobjv << endl;

		for (i = 0; i < 2; i++)
		{
			if (i == 0) cout << "�����༶���ͣ�";
			else cout << "�����༶������";
			for (int j = 0; j < tools[4][2]; j++)
			{
				cout.width(3);
				cout << lists[i][j] << ' ';
			}
			cout << '\n' << endl;
		}

		for (i = 0; i < 2; i++)
		{
			if (i == 0) cout << "��һ�༶���ͣ�";
			else cout << "��һ�༶������";
			for (j = 0; j < PRECI; j++)
			{
				cout.width(3);
				cout << out1[i][j] << ' ';
			}
			cout << '\n' << endl;
		}
		int zongrenshu = 0;
		for (j = 0; j < PRECI; j++)
		{
			zongrenshu = zongrenshu + out1[1][j];
		}
		if (stu1numb - zongrenshu == 0) 	cout << "����ͬѧ���ѷְ����" << endl;
		else cout << "����ͬѧδ�ɹ�����༶" << endl;
		cout << "----------------------------------------------------------------" << endl;
		for (i = 0; i < stu1numb; i++)
		{
			for (j = 0; j < 9; j++)
			{
				stu1out[i][j] = stu1[i][j];
			}
			stu1out[i][9] = stufinalclass[i];
		}
		return stu1out;
	}
	return 0;
}
double  ** ranking_7_3(int**stu1, int **tools, int ** pop)
{

	double *objv = new double[NIND];  //��Ӧ��ֵ

	int stu1numb = tools[4][4];       //��ȡ����ѧ������
	int PRECI = tools[4][5];           //��ȡ�����༶����


	int *classcontain = new int[PRECI];
	for (i = 0; i < PRECI; i++)
	{
		if (i < bigclassnum)classcontain[i] = bigclassmax;
		else classcontain[i] = lu;
	}
	int total[7];                     //���ڼ���ʣ��δѡ��Ŀ����
	int total1[7];                    //ͳ���Ѿ������Ŀ������
	int total2[7];                    //��stu11���а������,ͳ�ƶ��������������

	int **class1 = new int *[stu1numb];      //��ÿ�����ɵĶ�����һ�༶���� num[NIND][tools[4][5]]
	for (i = 0; i < stu1numb; i++)		class1[i] = new int[NIND];

	int **num = new int *[NIND];      //��ÿ�����ɵĶ�����һ�༶���� num[NIND][tools[4][5]]
	for (i = 0; i < NIND; i++)		num[i] = new int[PRECI];

	int tools2line = stu1numb + NIND;
	double ** tools2 = new double*[tools2line];  //���ڼ�¼ѧ������ѡ��
	for (i = 0; i < tools2line; i++)		tools2[i] = new double[3];

	for (i = 0; i < 7; i++)//����
	{
		total[i] = 0;
		total1[i] = 0;
		total2[i] = 0;
	}
	for (i = 0; i < NIND; i++)
	{
		for (j = 0; j < PRECI; j++)
		{
			num[i][j] = 0;
		}
		for (j = 0; j < stu1numb; j++)
		{
			class1[j][i] = 0;
		}
	}




	for (i = 0; i < NIND; i++)         //������Ⱥÿһ�����壨ÿһ�ְ༶��ϣ�
	{
		for (j = 0; j < 7; j++)//����
		{
			total[j] = 0;
			total1[j] = 0;
			total2[j] = 0;
		}
		for (j = 0; j < 7; j++) //ͳ�ƶ��������������
		{
			for (k = 0; k < stu1numb; k++)
			{
				total2[j] = stu1[k][j] + total2[j];//���stu11������� ͳ�Ƹ��������ɣ�
			}
		}
		for (k = 0; k < stu1numb; k++)     //������������ѧ��   
		{
			int e = -1;                  //���ڼĴ���������İ༶��ţ������ж��Ƿ�Ž��˰༶��
			int f = 0;                   //���ڼĴ���������İ༶���������ٵİ༶ѧ�����������ȷ��룩
			if (bigclassnum > 0) f = bigclassmax;
			else f = lu;


			for (j = 0; j < PRECI; j++)    //����ÿ��������һ�༶      
			{

				int b[7];
				swit_7_3(pop[i][j], b);      //�������i�е�j���༶
				int p = 0;
				for (int q = 0; q < 7; q++)
				{

					if (b[q] - stu1[k][q] == 0)
					{
						p = p + 1;
					}
				}
				if (p == 6)
				{
					if (num[i][j] < classcontain[j]) //ÿ�ζ��ŵ��������ٵİ༶
					{
						if (num[i][j] < f)
						{
							e = j;
							f = num[i][j];
						}
					}
				}

			}

			if (e > -1)
			{
				num[i][e] = num[i][e] + 1; //��Ⱥ��ĳȾɫ�����+1
				class1[k][i] = pop[i][e];//��¼ѧ�����ֵ���ʲô�༶
			}
		}

		/*int **stu1outtemp = new int *[stu1numb];      //��ÿ�����ɵĶ�����һ�༶���� num[NIND][tools[4][5]]
		for (int j = 0; j < stu1numb; j++)		stu1outtemp[j] = new int[9];
		for (int j = 0; j < stu1numb; j++)
		{
			for (int k = 0; k < 8; k++)
			{
				stu1outtemp[j][k] = stu1[j][k];
			}
			stu1outtemp[j][8] = class1[j][i];
		}
		*/


		//��ÿ��ѧ������༶,6�����δ�Ű༶���͡��༶���ơ�����Ӧ�÷ŵ����������������з��˵�������������������Ů����������
		int **stuplus = new int *[tools[4][3]];
		for (ii = 0; ii < tools[4][3]; ii++)		stuplus[ii] = new int[10];

		for (ii = tools[4][1]; ii < tools[4][3]; ii++)//���붨��ѧ����Ϣ
		{
			for (j = 0; j < 9; j++)
			{
				stuplus[ii][j] = stu1[ii - tools[4][1]][j];
			}
			stuplus[ii][9] = class1[ii - tools[4][1]][i];
		}




		//int stu2num = tools[4][1];//��������
		int ss = tools[4][2];//��������
		int NUM = tools[4][2] + tools[4][5];//�ܰ༶����
		int stu1num = tools[4][4];//��������
		disclass = new int *[6]; //
		for (ii = 0; ii < 6; ii++)		disclass[ii] = new int[NUM];
		classname = new int[tools[4][3]];//���������
		for (ii = 0; ii < ss; ii++)
		{
			disclass[0][ii] = lists[0][ii];//�̶�����
			disclass[2][ii] = lists[1][ii];//�̶�������
		}
		for (j = ss; j < NUM; j++)
		{
			disclass[0][j] = pop[i][j - ss];//�߰����
			disclass[2][j] = num[i][j - ss];//�߰�����
		}
		for (j = 0; j < classroomno[1][5]; j++)
		{
			if (classroomno[j][4] == 2)    classroomno[j][4] = 0;
			else if (classroomno[j][4] == 3)    classroomno[j][4] = 1;
		}
		for (ii = 0; ii < NUM; ii++)
		{
			int flag = 0;
			for (j = 0; j < classroomno[1][5]; j++)//���۶��� ȫ�������Ͻ���
			{
				if (classroomno[j][4] == 0 && flag == 0)//��ͨ����
				{
					disclass[1][ii] = classroomno[j][1];//�������� �õĽ���id
					classroomno[j][4] = 2;
					flag = 1;
				}
			}

			disclass[3][ii] = 0;//
			disclass[4][ii] = 0;//��
			disclass[5][ii] = 0;//Ů
		}
		for (ii = tools[4][1]; ii < tools[4][3]; ii++)//����ѧ�� �ֶ��� ��Ů����
		{
			int aaa = 1;//��¼�ܷ�Ž�ȥ
			int bbb = -1;//��¼λ��
			int ccc = lu;//��¼��С����
			for (j = 0; j < NUM; j++)//�������а༶
			{
				aaa = stuplus[ii][9] - disclass[0][j];//8����   �������
				if (aaa == 0)//����ܷŽ�ȥ
				{
					if (disclass[3][j] < disclass[2][j])//�����û��������༶
					{
						if (stuplus[ii][8] == 1)//�����
						{
							if (disclass[4][j] < ccc)//�����С
							{
								bbb = j;//��¼λ��
								ccc = disclass[4][j];//��С����
							}
						}
						else
						{
							if (disclass[5][j] < ccc)
							{

								bbb = j;
								ccc = disclass[5][j];
							}
						}
					}
				}
			}
			classname[ii] = disclass[1][bbb];//��¼���ѧ�����䵽���ĸ����ң���Ϊ��Ϣ���ʮ��
			if (stuplus[ii][7] == 1)
			{
				disclass[4][bbb] = disclass[4][bbb] + 1;//�ж��Ա� 
			}
			else
			{
				disclass[5][bbb] = disclass[5][bbb] + 1;//
			}
			disclass[3][bbb] = disclass[4][bbb] + disclass[5][bbb];
		}


		int ** goone = new int *[9]; //�����߶�����ѧ��ͳ���б�
		for (ii = 0; ii < 9; ii++)		goone[ii] = new int[PRECI];//0 ���� 1�༶id 2����3��ѧ 4���� 5���� 6��ʷ 7����  8��Ϣ�Ƽ�
		for (ii = 0; ii < 9; ii++)
		{
			for (j = 0; j < PRECI; j++)
			{
				goone[ii][j] = 0;
			}
		}
		int ** goone1 = new int *[9]; //�����߶�����ѧ��ͳ���б�
		for (ii = 0; ii < 9; ii++)		goone1[ii] = new int[PRECI];//0 ���� 1�༶id 2����3��ѧ 4���� 5���� 6��ʷ 7����  8��Ϣ�Ƽ�
		for (ii = ss; ii < NUM; ii++)
		{
			goone[0][ii - ss] = disclass[0][ii];//���� ժ������
			goone[1][ii - ss] = disclass[1][ii];//�༶��
		}
		for (ii = 0; ii < stu1num; ii++)//����ѧ��
		{
			int ddd = 1;
			for (j = 0; j < PRECI; j++)//������༶
			{
				ddd = goone[1][j] - classname[ii + tools[4][1]];//�����ѧ����������
				if (ddd == 0)
				{
					for (k = 0; k < 7; k++)
					{
						goone[k + 2][j] = goone[k + 2][j] + stuplus[ii + tools[4][1]][k];//ͳ��ѧ����Ŀ 
					}
					break;
				}
			}
		}

		for (ii = 2; ii < 9; ii++)//���㶨����Ĺ̶���Ŀ
		{
			for (j = 0; j < PRECI; j++)
			{
				int b[7];
				swit_7_3(goone[0][j], b);
				for (k = 0; k < 7; k++)
				{
					if (b[k] == 1) goone[k + 2][j] = 0;
				}
			}
		}
		/*for (int j = 0; j < 8; j++)
		{
			for (int k = 0; k < PRECI; k++)
			{
				cout << goone[j][k] << ' ';
			}
			cout << '\n' << endl;
		}*/

		for (j = 0; j < 9; j++)
		{
			for (k = 0; k < PRECI; k++)
			{
				goone1[j][k] = goone[j][k];
			}
		}

		for (j = 0; j < PRECI; j++)
		{
			int b[7];
			swit_7_3(pop[i][j], b);
			for (k = 0; k < 7; k++)
			{
				total1[k] = total1[k] + num[i][j] * b[k]; //�Ž�ȥ�˵ĸ���Ŀ������
			}
		}
		for (j = 0; j < 7; j++)
		{
			total[j] = total2[j] - total1[j];//��ʣ��û�Ž�ȥ�ĸ���������
			//cout << total[j] << " " << total2[j] << " " << total1[j] << endl;
		}
		int meansum = 0;                   //�ѷ���༶��������
		int d1 = 0;                       //û�Ž�ȥ������


		for (j = 0; j < PRECI; j++)//��Ž�ȥ��������
		{
			meansum = meansum + num[i][j];
		}
		d1 = stu1numb - meansum;
		float mean = meansum / (PRECI*1.0);//ƽ����

		float sum1 = 0.0;
		for (j = 0; j < PRECI; j++)
		{
			sum1 = (num[i][j] - mean)*(num[i][j] - mean)*1.0 + sum1;
		}
		float s1 = sum1 / (PRECI*1.0);   //����
		int d2 = 0;                         //�����ж��Ƿ���������
		for (j = 0; j < PRECI; j++)     //���������������޶� �ͷ�
		{
			if (num[i][j] < ld)
			{
				d2 = d2 + ld - num[i][j];
			}
		}
		objv[i] = s1 + ad1 * d1 + ad2 * d2;
		int rn[7] = { 0,0,0,0,0,0,0 };

		if (objv[i] < 1000)
		{
			int q = 0;
			countq = 0;
			for (j = 0; j < 7; j++)
			{
				q = q + ceil(total[j] / (lu*1.0));
				rn[j] = ceil(total[j] / (lu*1.0));
			}

			int rn1[7];
			for (j = 0; j < 7; j++)
			{
				rn1[j] = rn[j];
			}

			int * shu1 = new int[NUM];
			for (j = 0; j < NUM; j++)
			{
				shu1[j] = -1;
			}

			while (q)
			{
				if (countq < PRECI)
				{
					int aa = -1;
					int bb = -1;
					int cc = -1;
					for (j = 0; j < 7; j++)
					{
						for (k = 0; k < PRECI; k++)
						{
							if (goone1[j + 2][k] > aa)
							{
								aa = goone1[j + 2][k];
								bb = j;
								cc = k;
							}
						}
					}
					goone1[bb + 2][cc] = -1;
					if (rn1[bb] > 0 && shu1[cc] == -1)
					{
						shu1[cc] = bb;
						rn1[bb] = rn1[bb] - 1;
						q = q - 1;
						countq = countq + 1;
						if (classcontain[cc] < total[bb])
						{
							total[bb] = total[bb] - classcontain[cc];
							if (ceil(total[bb] / lu) < rn1[bb])
							{
								rn[bb] = rn[bb] - 1;
								rn1[bb] = rn1[bb] - 1;
								q = q - 1;
							}
						}
					}

				}
				else if (countq >= PRECI)
				{
					for (j = 0; j < 7; j++)
					{
						if (rn1[j] != 0)
						{
							shu1[countq + 1] = j;
							rn1[j] = rn1[j] - 1;
							q = q - 1;
							countq = countq + 1;
							break;
						}
					}
				}
			}
			int d3 = 0;
			if (countq > (PRECI + add))
			{
				d3 = countq - (PRECI + add);
				objv[i] = objv[i] + ad3 * d3;
			}

			int d4 = 0;
			for (j = 0; j < 7; j++)
			{
				if (teacher[j] < rn[j])
				{
					d4 = d4 + (rn[j] - teacher[j]);
				}
			}
			objv[i] = objv[i] + ad4 * d4;

			int d5 = 0;//�����ж϶����༶��һ�����Ƿ���
			for (j = 0; j < tools[4][5]; j++)
			{
				int stuclass[7] = { 0,0,0,0,0,0,0 };
				for (k = 0; k < stu1numb; k++)
				{
					if (class1[k][i] == pop[i][j])
					{
						for (int kk = 0; kk < 7; kk++)
						{
							stuclass[kk] = stuclass[kk] + stu1[k][kk];
						}
					}
				}
				for (k = 0; k < 7; k++)
				{
					if (stuclass[k] != 0)
					{
						d5 = d5 + 1;
					}
				}
			}
			d5 = d5 - 2 * PRECI;
			objv[i] = objv[i] + ad5 * d5;
		}
		else
		{
			objv[i] = objv[i] * 2;
		}

		for (j = 0; j < tools[4][3]; j++)
		{
			delete[] stuplus[j];
		}
		delete[] stuplus;

		for (j = 0; j < 9; j++)
		{
			delete[] goone[j];
		}
		delete[] goone;

		for (j = 0; j < 9; j++)
		{
			delete[] goone1[j];
		}
		delete[] goone1;


	


	}


	//for (int j = 0; j <NIND; j++)//********************************************************************
	//{
	//	for (int k = 0; k <PRECI; k++)
	//	{
	//		cout << num[j][k] << " ";
	//	}
	//	cout << endl;
	//}

	for (i = 0; i < NIND; i++)
	{
		tools2[i][2] = objv[i]; //tools2[i][2]���뱾����Ӧ��ֵ
	}
	int minpos = (min_element(objv, objv + NIND) - objv);          //������Сֵ��λ�� 

	for (i = 0; i < stu1numb; i++)
	{
		tools2[i][0] = class1[i][minpos];// tools2[i][0]���뱾������ѧ���༶����
	}
	for (i = 0; i < PRECI; i++)
	{
		tools2[i][1] = num[minpos][i];// tools2[i][1]���뱾�����Ÿ���ѧ������
	}
	return tools2;
}
int ** updatepopulation_7_3(int ** pop, double * objv, int gen, int PRECI, int ** out)
{
	int **popnext = new int *[NIND];      //popnextΪ���º���Ⱥ popnext[NIND][tools[4][5]]
	for (i = 0; i < NIND; i++)		popnext[i] = new int[PRECI];

	for (i = 0; i < NIND; i++)
	{
		for (j = 0; j < PRECI; j++)
		{
			popnext[i][j] = pop[i][j];
		}
	}

	int *temp0 = new int[PRECI];
	for (i = 0; i < NIND; i++)                 // ���ݸ�����Ӧ�������򣻣�ð�ݷ���
	{
		for (j = 1; j < NIND - i; j++)
		{
			if (objv[j] < objv[j - 1])
			{
				for (k = 0; k < PRECI; k++)
				{
					temp0[k] = popnext[j][k];
					popnext[j][k] = popnext[j - 1][k];
					popnext[j - 1][k] = temp0[k];
				}
			}
		}
	}

	for (i = NIND * GGAP; i < NIND; i++)       //���մ����������Ƹ���
	{
		for (j = 0; j < PRECI; j++)
		{

			popnext[i][j] = popnext[NIND - i - 1][j];
		}
	}



	int *temp1 = new int[PRECI];
	for (i = 0; i < (NIND / 2); i++)
	{
		double random1 = (rand() % 10) / 10.0;  //����0-1�����С��,�����ж��Ƿ񽻲�
		if (random1 >= (1.0 - px))
		{
			int random2 = rand() % PRECI;                     // ������ɽ���λ�ã�����������0��PRECI֮�䣻
			for (j = random2; j < PRECI; j++)
			{
				temp1[j] = popnext[i * 2 + 1][j];
				popnext[i * 2 + 1][j] = popnext[i * 2][j];
				popnext[i * 2][j] = temp1[j];
			}
		}
	}

	for (i = 0; i<int(NIND*PRECI*pm); i++)                             //����
	{
		int col = rand() % PRECI;                            // �������Ҫ����Ļ���λ�ţ�
		int row = rand() % NIND;                             // �������Ҫ�����Ⱦɫ��ţ�
		popnext[row][col] = rand() % 21;                  //��0-20֮������任һ��
	}
	for (i = 0; i < PRECI; i++)                         //��ȫ�����Ų���
	{
		popnext[(NIND - 1)][i] = out[0][i];
	}


	return popnext;

}
int ** sectionstu2_7_3(int**stu2, int**tools)
{
	int num = tools[4][2];//���������
	int ** stu2out = new int *[tools[4][1]]; //���������ְ����б�
	for (i = 0; i < tools[4][1]; i++)		stu2out[i] = new int[10];

	for (i = 0; i < 2; i++)		lists[i] = new int[num];
	int knum = 0; //��ʼ��list������
	for (i = 0; i < 35; i++)//������ʮ�ְ���
	{
		if (tools[2][i] > 0)//�������
		{

			for (j = 0; j < tools[2][i]; j++)//��x����
			{

				lists[0][knum] = tools[0][i];

				lists[1][knum] = 0;
				knum++;
			}
		}
	}
	for (i = 0; i < tools[4][1]; i++)
	{
		int o[7];
		int e = -1;                  //���ڼĴ���������İ༶��ţ������ж��Ƿ�Ž��˰༶��
		int f = lu;                  //���ڼĴ���������İ༶���������ٵİ༶ѧ�����������ȷ��룩

		for (j = 0; j < 7; j++)
		{
			o[j] = stu2[i][j];
		}

		for (k = 0; k < tools[4][2]; k++)
		{
			int p = 0;
			for (int e = 0; e < 7; e++)
			{
				int b[7];
				swit_7_3(lists[0][k], b);
				if (o[e] - b[e] == 0)
				{
					p = p + 1;
				}
			}
			if ((p == 7) && ((lists[1][k]) < lu) && lists[1][k] < f)
			{
				e = k;
				f = lists[1][k];
			}
		}
		if (e > -1)
		{
			lists[1][e] = lists[1][e] + 1;
			stu2out[i][9] = lists[0][e];
		}

	}

	for (i = 0; i < tools[4][1]; i++)
	{
		for (j = 0; j < 9; j++)
		{
			stu2out[i][j] = stu2[i][j];
		}
	}
	return stu2out;
}
int ** getstu2_7_3(int**stuinform, int **tools, int*randnumber)
{
	int u[35][7];//�༶����Ƚ�ģ��
	for (i = 0; i < 35; i++)
	{
		int b[7];
		swit_7_3(tools[0][i], b);
		for (j = 0; j < 7; j++)
		{
			u[i][j] = b[j];                    //u[i][j]��ŵ�һ�ηֺ�ѡ����Ϣ�Ĺ̶��༶������
		}
	}

	int num2 = tools[4][1];//��������
	int **stu2 = new int *[num2];
	for (i = 0; i < num2; i++)		stu2[i] = new int[10];
	int y[35];
	int stu2num = 0;
	int stu2num2 = 0;
	for (i = 0; i < 35; i++)          y[i] = 0;
	for (i = 0; i < tools[4][3]; i++) //tools[4][3]��ѧ������
	{
		int f[10];//�ݴ�ʹ�õ�ѧ����Ϣ
		for (j = 0; j < 10; j++)
		{
			f[j] = stuinform[(randnumber[i] - 1)][j];       //ǧ��ע�������stu������ǰ���stu���������������ɣ������������ƥ�䲻�ϣ�������������
		}
		for (k = 0; k < 35; k++) //����20�ֿ��ܰ�
		{
			if (tools[2][k] > 0) //����п���
			{
				if (y[k] < tools[3][k]) //��û����
				{
					int h = 0; //�Ƚϼ���λ

					for (int g = 0; g < 7; g++)
					{
						if (f[g] - u[k][g] == 0)    h = h + 1;//ͳ����ͬλ����	
					}
					if (h == 7)          //ÿ��ѧ����̶��༶�Ŀ�Ŀ���бȽϣ����ϵľͷŽ�ȥ
					{
						for (int l = 0; l < 10; l++)  stu2[stu2num][l] = f[l];
						y[k] = y[k] + 1;
						stu2num = stu2num + 1;
						break;
					}

				}

			}

		}

	}
	return stu2;
}
int ** getstu1_7_3(int**stuinform, int **tools, int*randnumber)
{
	int u[35][7];//�༶����Ƚ�ģ��
	for (i = 0; i < 35; i++)
	{
		int b[7];
		swit_7_3(tools[0][i], b);
		for (j = 0; j < 7; j++)
		{
			u[i][j] = b[j];                    //u[i][j]��ŵ�һ�ηֺ�ѡ����Ϣ�Ĺ̶��༶������
		}
	}
	int num1 = tools[4][4];
	int **stu1 = new int *[num1];
	for (i = 0; i < num1; i++)		stu1[i] = new int[10];
	int y[35];
	for (i = 0; i < 35; i++)          y[i] = 0;
	int stunum = 0;
	int q = 0;//�Ƿ�ѡ�еı�־λ
	for (i = 0; i < tools[4][3]; i++) //tools[4][3]��ѧ������
	{
		q = 0;//�Ƿ�ѡ�еı�־λ
		int f[10];//�ݴ�ʹ�õ�ѧ����Ϣ
		for (j = 0; j < 10; j++)
		{
			f[j] = stuinform[(randnumber[i] - 1)][j];       //ǧ��ע�������stu������ǰ���stu���������������ɣ������������ƥ�䲻�ϣ�������������
		}
		for (k = 0; k < 35; k++) //����20�ֿ��ܰ�
		{
			if (tools[2][k] > 0) //����п���
			{
				if (y[k] < tools[3][k]) //��û����
				{
					int h = 0; //�Ƚϼ���λ

					for (int g = 0; g < 7; g++)
					{
						if (f[g] - u[k][g] == 0)    h = h + 1;//ͳ����ͬλ����	
					}
					if (h == 7)          //ÿ��ѧ����̶��༶�Ŀ�Ŀ���бȽϣ����ϵľͷŽ�ȥ
					{
						q = 1;
						y[k] = y[k] + 1;
						break;
					}
				}

			}
		}
		if (q == 0)//��û���Ž�ȥ�Ļ�
		{

			for (int l = 0; l < 10; l++) stu1[stunum][l] = f[l];
			stunum++;
		}
	}
	return stu1;
}
int ** gettools_7_3(int**stuinform, int stunum, int*randnumber)
{
	int  ** r;
	r = (int**)new int*[5];
	for (i = 0; i < 5; i++)
	{
		*(r + i) = new int[35];
	}
	for (i = 0; i < 35; i++)//��r0���տγ�ID����
	{
		r[0][i] = i + 21;
		r[1][i] = 0;
		r[2][i] = 0;
		r[3][i] = 0;
		r[4][i] = 0;
	}
	for (i = 0; i < stunum; i = i + 1) //ͳ�Ƹ���ѡ�����������
	{
		int o[7];
		for (int j = 0; j < 7; j++) 	o[j] = stuinform[(randnumber[i] - 1)][j];
		if ((o[0] + o[1] + o[2]) == 3)
		{
			r[1][0] = r[1][0] + 1;
		}
		else if ((o[0] + o[1] + o[3]) == 3)
		{
			r[1][1] = r[1][1] + 1;
		}
		else if ((o[0] + o[1] + o[4]) == 3)
		{
			r[1][2] = r[1][2] + 1;
		}
		else if ((o[0] + o[1] + o[5]) == 3)
		{
			r[1][3] = r[1][3] + 1;
		}
		else if ((o[0] + o[1] + o[6]) == 3)
		{
			r[1][4] = r[1][4] + 1;
		}
		else if ((o[0] + o[2] + o[3]) == 3)
		{
			r[1][5] = r[1][5] + 1;
		}
		else if ((o[0] + o[2] + o[4]) == 3)
		{
			r[1][6] = r[1][6] + 1;
		}
		else if ((o[0] + o[2] + o[5]) == 3)
		{
			r[1][7] = r[1][7] + 1;
		}
		else if ((o[0] + o[2] + o[6]) == 3)
		{
			r[1][8] = r[1][8] + 1;
		}
		else if ((o[0] + o[3] + o[4]) == 3)
		{
			r[1][9] = r[1][9] + 1;
		}
		else if ((o[0] + o[3] + o[5]) == 3)
		{
			r[1][10] = r[1][10] + 1;
		}
		else if ((o[0] + o[3] + o[6]) == 3)
		{
			r[1][11] = r[1][11] + 1;
		}
		else if ((o[0] + o[4] + o[5]) == 3)
		{
			r[1][12] = r[1][12] + 1;
		}
		else if ((o[0] + o[4] + o[6]) == 3)
		{
			r[1][13] = r[1][13] + 1;
		}
		else if ((o[0] + o[5] + o[6]) == 3)
		{
			r[1][14] = r[1][14] + 1;
		}
		else if ((o[1] + o[2] + o[3]) == 3)
		{
			r[1][15] = r[1][15] + 1;
		}
		else if ((o[1] + o[2] + o[4]) == 3)
		{
			r[1][16] = r[1][16] + 1;
		}
		else if ((o[1] + o[2] + o[5]) == 3)
		{
			r[1][17] = r[1][17] + 1;
		}
		else if ((o[1] + o[2] + o[6]) == 3)
		{
			r[1][18] = r[1][18] + 1;
		}
		else if ((o[1] + o[3] + o[4]) == 3)
		{
			r[1][19] = r[1][19] + 1;
		}
		else if ((o[1] + o[3] + o[5]) == 3)
		{
			r[1][20] = r[1][20] + 1;
		}
		else if ((o[1] + o[3] + o[6]) == 3)
		{
			r[1][21] = r[1][21] + 1;
		}
		else if ((o[1] + o[4] + o[5]) == 3)
		{
			r[1][22] = r[1][22] + 1;
		}
		else if ((o[1] + o[4] + o[6]) == 3)
		{
			r[1][23] = r[1][23] + 1;
		}
		else if ((o[1] + o[5] + o[6]) == 3)
		{
			r[1][24] = r[1][24] + 1;
		}
		else if ((o[2] + o[3] + o[4]) == 3)
		{
			r[1][25] = r[1][25] + 1;
		}
		else if ((o[2] + o[3] + o[5]) == 3)
		{
			r[1][26] = r[1][26] + 1;
		}
		else if ((o[2] + o[3] + o[6]) == 3)
		{
			r[1][27] = r[1][27] + 1;
		}
		else if ((o[2] + o[4] + o[5]) == 3)
		{
			r[1][28] = r[1][28] + 1;
		}
		else if ((o[2] + o[4] + o[6]) == 3)
		{
			r[1][29] = r[1][29] + 1;
		}
		else if ((o[2] + o[5] + o[6]) == 3)
		{
			r[1][30] = r[1][30] + 1;
		}
		else if ((o[3] + o[4] + o[5]) == 3)
		{
			r[1][31] = r[1][31] + 1;
		}
		else if ((o[3] + o[4] + o[6]) == 3)
		{
			r[1][32] = r[1][32] + 1;
		}
		else if ((o[3] + o[5] + o[6]) == 3)
		{
			r[1][33] = r[1][33] + 1;
		}
		else if ((o[4] + o[5] + o[6]) == 3)
		{
			r[1][34] = r[1][34] + 1;
		}
	}
	int c = 0;
	for (i = 0; i < 35; i++)
	{
		if (r[1][i] >= ld)
		{
			float rs = (r[1][i] * 1.0 / (lu*1.0));
			int rsint = r[1][i] / lu;
			int temp2 = rsint * (lu - ld) + r[1][i] - rsint * lu;
			if (temp2 >= ld)       rsint = rsint + 1;
			r[2][i] = rsint; //��rsint���༶
			c = c + 1;//���� �������̶ֹ��༶
		}
	}
	int numclassnumb = 0;
	if (runsnumber == 0)//�㷨��һ��ִ��
	{
		for (i = 0; i < 35; i++)
		{
			numclassnumb = numclassnumb + r[2][i];//ͳ�ư༶����
		}
		maxrunsnumber = times * (numclassnumb + 2);
	}

	if (runsnumber > 0)  //�����ηְ��޹� ÿ���μ���һ���̶��༶
	{
		int e = runsnumber / times; //������ٶ��ٸ��̶��࣬ÿ���μ���һ��
		for (i = 0; i < e; i++)
		{
			int a = 0;                //ͳ�Ƶ�ǰ��x�ֿ���
			for (j = 0; j < 35; j++)
			{
				if (r[2][j] > 0)
				{
					a = a + 1;
				}
			}
			if (a != 0) //������й̶���
			{
				int b = rand() % a + 1; //��Ŀǰ�ļ��ֿ�����ѡһ��
				int c = 0;
				for (j = 0; j < 35; j++) //������ʮ������
				{
					if (r[2][j] > 0) //���������
					{
						c = c + 1;         //����
						if (c == b)   //�ж��Ƿ��ǵ�d������
						{

							r[2][j] = r[2][j] - 1; //����� �����һ���̶���
						}
					}
				}
			}

		}
		int d = 0;
		for (j = 0; j < 35; j++)
		{

			d = d + r[2][j];

		}
	}

	for (i = 0; i < 35; i++)
	{
		if ((r[2][i])*lu < (r[1][i])) r[3][i] = (r[2][i])*lu;//����������ڿ�����������r3����Ϊ��ѡ������ε�ѧ��
		else r[3][i] = r[1][i]; //���ܷŽ�ȥ
	}

	int num1 = 0;
	int num2 = 0;
	for (i = 0; i < 35; i++) num1 = num1 + r[3][i];
	for (i = 0; i < 35; i++) num2 = num2 + r[2][i];
	r[4][1] = num1; //�̶��������
	r[4][2] = num2; //�̶���ĸ���
	r[4][3] = stunum;
	r[4][4] = stunum - num1;
	r[4][5] = classsum - num2;
	cout << "��ǰ�ⶨ�̶���������" << r[4][2] << endl;
	return r;

}
int getstudentnumber_7_3()
{
	Json::Reader reader;
	Json::Value root;
	Json::Value temp;
	int studentnumber;
	//���ļ��ж�ȡ����֤��ǰ�ļ���json�ļ�  
	ifstream in(jsonfilename, ios::binary);
	if (!in.is_open()) return 0;
	if (reader.parse(in, root))
	{

		for (i = 0; i < root.size(); i++)//����ÿһ��
		{
			if (root[i]["key"] == "Student")//�����Student
			{
				studentnumber = root[i]["value"].size();
			}
			if (root[i]["key"] == "Class")//�����Class ���ַ�����ʽ�洢���ҺͰ༶���� 0�н��� 1�а༶����
			{
				classsum = root[i]["value"].size();
			}
		}
		in.close();
		if (classsum < 10)
		{
			lu = (studentnumber / classsum) + 2;
			ld = (studentnumber / classsum) - 5;
		}
		else if (classsum < 20)
		{
			lu = (studentnumber / classsum) + 1;
			ld = (studentnumber / classsum) - 4;
		}
		else if (classsum < 30)
		{
			lu = (studentnumber / classsum) + 1;
			ld = (studentnumber / classsum) - 3;
		}
		else
		{
			lu = (studentnumber / classsum) + 1;
			ld = (studentnumber / classsum) - 2;
		}


		return studentnumber;
	}
	in.close();
	return 0;
}
int getstudentnumberfromstring_7_3()
{
	Json::Reader reader;
	Json::Value root;
	Json::Value temp;
	int studentnumber;

	if (reader.parse(str, root))
	{

		for (i = 0; i < root.size(); i++)//����ÿһ��
		{
			if (root[i]["key"] == "Student")//�����Student
			{
				studentnumber = root[i]["value"].size();
			}
			if (root[i]["key"] == "Class")//�����Class ���ַ�����ʽ�洢���ҺͰ༶���� 0�н��� 1�а༶����
			{
				classsum = root[i]["value"].size();
			}
		}
		if (classsum < 10)
		{
			lu = (studentnumber / classsum) + 2;
			ld = (studentnumber / classsum) - 5;
		}
		else if (classsum < 20)
		{
			lu = (studentnumber / classsum) + 1;
			ld = (studentnumber / classsum) - 4;
		}
		else if (classsum < 30)
		{
			lu = (studentnumber / classsum) + 1;
			ld = (studentnumber / classsum) - 3;
		}
		else
		{
			lu = (studentnumber / classsum) + 1;
			ld = (studentnumber / classsum) - 2;
		}


		return studentnumber;
	}
	return 0;
}
int ** readFileJson_7_3(int studentnumber)//���ļ��ж�ȡJSON  
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
		int ** arr = new int *[studentnumber];
		for (i = 0; i < studentnumber; i++)		 arr[i] = new int[10];
		for (i = 0; i < root.size(); i++)//����ÿһ��
		{
			if (root[i]["key"] == "Student")//�����Student
			{
				studentno = new string *[studentnumber]; //����ѧ���ַ������� 0��ѧ�� 1������
				for (j = 0; j < studentnumber; j++)		studentno[j] = new string[2];
				//��ȡ������Ϣ  
				for (unsigned int j = 0; j < root[i]["value"].size(); j++)
				{
					//ȡ��ѧ�ź����� ���ַ�����ʽ�洢
					int temp = root[i]["value"][j]["studentno"].asInt();
					stringstream s1;
					s1 << temp;
					string s11;
					s1 >> s11;
					studentno[j][0] = s11;
					studentno[j][1] = root[i]["value"][j]["name"].asString();
					//ȡ��־Ը������ ȡ���Ա� ѧ��  �����δ洢
					int *p;
					string ach = root[i]["value"][j]["vlounteer"].asString();//ȡ�����־Ը
					p = translate_7_3(ach);//����ת��Ϊ������b
					for (k = 0; k < 7; k++)
					{
						arr[j][k] = p[k];
					}
					arr[j][7] = root[i]["value"][j]["studentno"].asInt();//����ѧ��
					arr[j][8] = root[i]["value"][j]["sex"].asInt();//�����Ա�
					arr[j][9] = 0;//ռλ 
				}
			}
			if (root[i]["key"] == "Class")//�����Class ���ַ�����ʽ�洢���ҺͰ༶���� 0�н��� 1�а༶����
			{
				classno = new string *[root[i]["value"].size()];
				for (j = 0; j < root[i]["value"].size(); j++)		classno[j] = new string[2];
				for (j = 0; j < root[i]["value"].size(); j++)
				{
					int temp = root[i]["value"][j]["classroom"].asInt();
					stringstream s2;
					s2 << temp;
					string s22 = s2.str();
					classno[j][0] = s22;
					classno[j][1] = root[i]["value"][j]["name"].asString();
				}
			}
			if (root[i]["key"] == "Teacher")//�����Teacher  �ַ������� 0��id 1������ 2�� ѧ�� 3 ���Ա�
			{
				teacherno = new string *[root[i]["value"].size()];
				for (j = 0; j < root[i]["value"].size(); j++)		teacherno[j] = new string[4];
				for (j = 0; j < root[i]["value"].size(); j++)
				{
					int temp = root[i]["value"][j]["teacherno"].asInt();
					stringstream s3;
					s3 << temp;
					string s33 = s3.str();
					teacherno[j][0] = s33;
					teacherno[j][1] = root[i]["value"][j]["name"].asString();
					teacherno[j][2] = root[i]["value"][j]["subject"].asString();
					int temp2 = root[i]["value"][j]["sex"].asInt();
					stringstream s4;
					s4 << temp2;
					string s44 = s4.str();
					teacherno[j][3] = s44;
					if (teacherno[j][2] == "����") teacher[0] = teacher[0] + 1;
					else if (teacherno[j][2] == "��ѧ")teacher[1] = teacher[1] + 1;
					else if (teacherno[j][2] == "����")teacher[2] = teacher[2] + 1;
					else if (teacherno[j][2] == "����")teacher[3] = teacher[3] + 1;
					else if (teacherno[j][2] == "��ʷ")teacher[4] = teacher[4] + 1;
					else if (teacherno[j][2] == "����")teacher[5] = teacher[5] + 1;
					else if (teacherno[j][2] == "��Ϣ�Ƽ�")teacher[6] = teacher[6] + 1;
				}
			}
			if (root[i]["key"] == "Classroom")//�����Classroom 0 name(��������) 1id 2max 3 min 4type A-0 B-1 [1][5]�ܽ�������
			{
				classroomno = new int *[root[i]["value"].size()];
				for (j = 0; j < root[i]["value"].size(); j++)		classroomno[j] = new int[6];
				classroomno[1][5] = root[i]["value"].size();
				for (j = 0; j < root[i]["value"].size(); j++)
				{
					classroomno[j][0] = root[i]["value"][j]["name"].asInt();
					classroomno[j][1] = root[i]["value"][j]["id"].asInt();
					classroomno[j][2] = root[i]["value"][j]["max"].asInt();
					classroomlu = root[i]["value"][j]["max"].asInt();
					classroomno[j][3] = root[i]["value"][j]["min"].asInt();
					string temp = root[i]["value"][j]["type"].asString();
					if (temp == "A")
					{
						classroomno[j][4] = 0;
						unadd = unadd + 1;
					}
					else if (temp == "B")
					{
						classroomno[j][4] = 1;
						add = add + 1;
					}
				}
			}
			if (root[i]["key"] == "Plot")//�����Plot
			{
				plotno = new int *[root[i]["value"].size()];
				for (j = 0; j < root[i]["value"].size(); j++)		plotno[j] = new int[2];
				for (j = 0; j < root[i]["value"].size(); j++)
				{
					plotno[j][0] = root[i]["value"][j]["id"].asInt();
					plotno[j][1] = root[i]["value"][j]["value"].asInt();
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
int ** readJson_7_3(int studentnumber)//���ַ����ж�ȡJSON  
{
	Json::Reader reader;
	Json::Value root;
	Json::Value temp;


	if (reader.parse(str, root))
	{
		int ** arr = new int *[studentnumber]; //���������ְ����б�
		for (i = 0; i < studentnumber; i++)		 arr[i] = new int[10];
		for (i = 0; i < root.size(); i++)//����ÿһ��
		{
			if (root[i]["key"] == "Student")//�����Student
			{
				studentno = new string *[studentnumber]; //����ѧ���ַ������� 0��ѧ�� 1������
				for (j = 0; j < studentnumber; j++)		studentno[j] = new string[2];
				//��ȡ������Ϣ  
				for (unsigned int j = 0; j < root[i]["value"].size(); j++)
				{
					//ȡ��ѧ�ź����� ���ַ�����ʽ�洢
					int temp = root[i]["value"][j]["studentno"].asInt();
					stringstream s1;
					s1 << temp;
					string s11;
					s1 >> s11;
					studentno[j][0] = s11;
					studentno[j][1] = root[i]["value"][j]["name"].asString();
					//ȡ��־Ը������ ȡ���Ա� ѧ��  �����δ洢
					int *p;
					string ach = root[i]["value"][j]["vlounteer"].asString();//ȡ�����־Ը
					p = translate_7_3(ach);//����ת��Ϊ������b
					for (k = 0; k < 7; k++)
					{
						arr[j][k] = p[k];
					}
					arr[j][7] = root[i]["value"][j]["studentno"].asInt();//����ѧ��
					arr[j][8] = root[i]["value"][j]["sex"].asInt();//�����Ա�
					arr[j][9] = 0;//ռλ ���ڴ�Ű���
				}
			}
			if (root[i]["key"] == "Class")//�����Class ���ַ�����ʽ�洢���ҺͰ༶���� 0�н��� 1�а༶����
			{
				classno = new string *[root[i]["value"].size()];
				for (j = 0; j < root[i]["value"].size(); j++)		classno[j] = new string[2];
				for (j = 0; j < root[i]["value"].size(); j++)
				{
					int temp = root[i]["value"][j]["classroom"].asInt();
					stringstream s2;
					s2 << temp;
					string s22 = s2.str();
					classno[j][0] = s22;
					classno[j][1] = root[i]["value"][j]["name"].asString();
				}
			}
			if (root[i]["key"] == "Teacher")//�����Teacher  �ַ������� 0��id 1������ 2�� ѧ�� 3 ���Ա�
			{
				teacherno = new string *[root[i]["value"].size()];
				for (j = 0; j < root[i]["value"].size(); j++)		teacherno[j] = new string[4];
				for (j = 0; j < root[i]["value"].size(); j++)
				{
					int temp = root[i]["value"][j]["teacherno"].asInt();
					stringstream s3;
					s3 << temp;
					string s33 = s3.str();
					teacherno[j][0] = s33;
					teacherno[j][1] = root[i]["value"][j]["name"].asString();
					teacherno[j][2] = root[i]["value"][j]["subject"].asString();
					int temp2 = root[i]["value"][j]["sex"].asInt();
					stringstream s4;
					s4 << temp2;
					string s44 = s4.str();
					teacherno[j][3] = s44;
					if (teacherno[j][2] == "����") teacher[0] = teacher[0] + 1;
					else if (teacherno[j][2] == "��ѧ")teacher[1] = teacher[1] + 1;
					else if (teacherno[j][2] == "����")teacher[2] = teacher[2] + 1;
					else if (teacherno[j][2] == "����")teacher[3] = teacher[3] + 1;
					else if (teacherno[j][2] == "��ʷ")teacher[4] = teacher[4] + 1;
					else if (teacherno[j][2] == "����")teacher[5] = teacher[5] + 1;
					else if (teacherno[j][2] == "��Ϣ�Ƽ�")teacher[6] = teacher[6] + 1;
				}
			}
			if (root[i]["key"] == "Classroom")//�����Classroom 0 name(��������) 1id 2max 3 min 4type A-0 B-1 [1][5]�ܽ�������
			{
				classroomno = new int *[root[i]["value"].size()];
				for (j = 0; j < root[i]["value"].size(); j++)		classroomno[j] = new int[6];
				classroomno[1][5] = root[i]["value"].size();
				for (j = 0; j < root[i]["value"].size(); j++)
				{
					classroomno[j][0] = root[i]["value"][j]["name"].asInt();
					classroomno[j][1] = root[i]["value"][j]["id"].asInt();
					classroomno[j][2] = root[i]["value"][j]["max"].asInt();
					classroomlu = root[i]["value"][j]["max"].asInt();
					classroomno[j][3] = root[i]["value"][j]["min"].asInt();
					string temp = root[i]["value"][j]["type"].asString();
					if (temp == "A")
					{
						classroomno[j][4] = 0;
						unadd = unadd + 1;
					}
					else if (temp == "B")
					{
						classroomno[j][4] = 1;
						add = add + 1;
					}
				}
			}
			if (root[i]["key"] == "Plot")//�����Plot
			{
				plotno = new int *[root[i]["value"].size()];
				for (j = 0; j < root[i]["value"].size(); j++)		plotno[j] = new int[2];
				for (j = 0; j < root[i]["value"].size(); j++)
				{
					plotno[j][0] = root[i]["value"][j]["id"].asInt();
					plotno[j][1] = root[i]["value"][j]["value"].asInt();
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
string writeFileJson_7_3(int** stu1out, int** stu2out, int** tools)//����Ϣ����ΪJSON��ʽ 
{
	Json::Value jsonoutput;
	Json::Value student;
	student["key"] = Json::Value("Student");
	Json::Value value;
	for (i = 0; i < tools[4][1]; i++)//�������
	{
		value["studentno"] = Json::Value(stu2out[i][7]);
		value["sex"] = Json::Value(stu2out[i][8]);
		for (j = 0; j < tools[4][3]; j++)
		{
			stringstream s2;
			s2 << studentno[j][0];
			int iii;
			s2 >> iii;

			int bb = stu2out[i][7];
			int aa = iii;
			//cout << studentno[j][0] << endl;
			//cout << aa<<"-"<<bb<<"="<<aa-bb<< endl;
			if (aa - bb == 0)
			{
				value["name"] = Json::Value(studentno[j][1]);
			}
		}
		int b[7];
		for (j = 0; j < 7; j++)
		{
			b[j] = stu2out[i][j];
		}
		string subject = translate2_7_3(b);
		value["vlounteer"] = Json::Value(subject);
		value["class"] = Json::Value(classname[i]);
		value["shiftclass"] = Json::Value(0);
		student["value"].append(Json::Value(value));
	}
	for (i = 0; i < tools[4][4]; i++)//�������
	{
		value["studentno"] = Json::Value(stu1out[i][7]);
		value["sex"] = Json::Value(stu1out[i][8]);
		for (j = 0; j < tools[4][3]; j++)
		{
			stringstream s3;
			s3 << studentno[j][0];
			int ii;
			s3 >> ii;
			int bbb = stu1out[i][7];
			int aaa = ii;
			//cout << studentno[j][0] << endl;
			//cout << aa<<"-"<<bb<<"="<<aa-bb<< endl;
			if (aaa - bbb == 0)
			{
				value["name"] = Json::Value(studentno[j][1]);
			}
			//if (stu1out[i][6] == ii) value["name"] = Json::Value(studentno[j][1]);
		}
		int b[7];
		for (j = 0; j < 7; j++)
		{
			b[j] = stu1out[i][j];
		}
		string subject = translate2_7_3(b);
		value["vlounteer"] = Json::Value(subject);
		value["class"] = Json::Value(classname[tools[4][1] + i]);
		value["shiftclass"] = Json::Value(classname1[0][i]);
		student["value"].append(Json::Value(value));
	}
	jsonoutput.append(Json::Value(student));

	Json::Value classroom;
	classroom["key"] = Json::Value("classroom");
	Json::Value classroomvalue;
	for (i = tools[4][2]; i < tools[4][2] + countq; i++)//�������߰����
	{

		classroomvalue["classroomno"] = Json::Value(shu[0][i - tools[4][2]]);
		if (i < tools[4][5] + tools[4][2])
		{
			classroomvalue["type"] = Json::Value("A");
			classroomvalue["subject1"] = Json::Value(disclass[0][i]);
			classroomvalue["subject1num"] = Json::Value(disclass[3][i]);

			classroomvalue["subject2"] = Json::Value(shu[2][i - tools[4][2]]);
			classroomvalue["subject2num"] = Json::Value(shu[1][i - tools[4][2]]);
		}
		else
		{
			classroomvalue["type"] = Json::Value("B");
			classroomvalue["subject1"] = Json::Value("��");
			classroomvalue["subject1num"] = Json::Value("��");
			classroomvalue["subject2"] = Json::Value(shu[2][i - tools[4][2]]);
			classroomvalue["subject2num"] = Json::Value(shu[1][i - tools[4][2]]);
		}
		classroom["value"].append(Json::Value(classroomvalue));
	}
	for (i = 0; i < tools[4][2]; i++)//������Ϣ���
	{

		classroomvalue["classroomno"] = Json::Value(disclass[1][i]);
		classroomvalue["type"] = Json::Value("A");
		classroomvalue["subject1"] = Json::Value(disclass[0][i]);
		classroomvalue["subject1num"] = Json::Value(disclass[3][i]);
		classroomvalue["subject2"] = Json::Value("��");
		classroomvalue["subject2num"] = Json::Value("��");
		classroom["value"].append(Json::Value(classroomvalue));
	}
	jsonoutput.append(Json::Value(classroom));


	Json::StyledWriter sw;
	return sw.write(jsonoutput);
}
int *translate_7_3(string volunteer)   //json�������Ŀ�Ŀת�����������ʾ
{
	int b[7];
	for (int i = 0; i < 7; i++) b[i] = 0;//���b
	string a("�ﻯ������ʷ����");
	for (int i = 0; i < 7; i = i + 2)//ÿ�μ��һ����ÿ����������ַ� һ��������
	{
		size_t j = a.find(volunteer[i]);//���Ҳ����ص�һ�γ��ֵ�λ�ã������ַ�ÿ��ռ�����ֽ�
		switch (j)
		{
		case 0: b[0] = 1; break;//��������b�����һλ��1����������
		case 2: b[1] = 1; break;
		case 4: b[2] = 1; break;
		case 6: b[3] = 1; break;
		case 8: b[4] = 1; break;//��ʷ�����ֵĽ��һ������ͬѧУ������ʷ���ַ�ʽ��ʾ���ſ�
		case 10: b[4] = 1; break;
		case 12: b[5] = 1; break;
		case 14: b[6] = 1; break;
		}
	}
	return b;
}
string  translate2_7_3(int * b)//�������ƿ�Ŀ����Ϊ����
{
	string sub1 = "��";
	string sub2 = "��";
	string sub3 = "��";
	string sub4 = "��";
	string sub5 = "ʷ";
	string sub6 = "��";
	string sub7 = "��Ϣ";
	string sub8;
	if (b[0] == 1)   sub8 = sub8 + sub1;
	if (b[1] == 1)   sub8 = sub8 + sub2;
	if (b[2] == 1)   sub8 = sub8 + sub3;
	if (b[3] == 1)   sub8 = sub8 + sub4;
	if (b[4] == 1)   sub8 = sub8 + sub5;
	if (b[5] == 1)   sub8 = sub8 + sub6;
	if (b[6] == 1)   sub8 = sub8 + sub7;
	return sub8;

}
int *swit_7_3(int p, int b[])
{

	switch (p)
	{
	case 0: b[0] = 1, b[1] = 1, b[2] = 0, b[3] = 0, b[4] = 0, b[5] = 0, b[6] = 0; break;
	case 1: b[0] = 1, b[1] = 0, b[2] = 1, b[3] = 0, b[4] = 0, b[5] = 0, b[6] = 0; break;
	case 2: b[0] = 1, b[1] = 0, b[2] = 0, b[3] = 1, b[4] = 0, b[5] = 0, b[6] = 0; break;
	case 3: b[0] = 1, b[1] = 0, b[2] = 0, b[3] = 0, b[4] = 1, b[5] = 0, b[6] = 0; break;
	case 4: b[0] = 1, b[1] = 0, b[2] = 0, b[3] = 0, b[4] = 0, b[5] = 1, b[6] = 0; break;
	case 5: b[0] = 1, b[1] = 0, b[2] = 0, b[3] = 0, b[4] = 0, b[5] = 0, b[6] = 1; break;
	case 6: b[0] = 0, b[1] = 1, b[2] = 1, b[3] = 0, b[4] = 0, b[5] = 0, b[6] = 0; break;
	case 7: b[0] = 0, b[1] = 1, b[2] = 0, b[3] = 1, b[4] = 0, b[5] = 0, b[6] = 0; break;
	case 8: b[0] = 0, b[1] = 1, b[2] = 0, b[3] = 0, b[4] = 1, b[5] = 0, b[6] = 0; break;
	case 9: b[0] = 0, b[1] = 1, b[2] = 0, b[3] = 0, b[4] = 0, b[5] = 1, b[6] = 0; break;
	case 10: b[0] = 0, b[1] = 1, b[2] = 0, b[3] = 0, b[4] = 0, b[5] = 0, b[6] = 1; break;
	case 11: b[0] = 0, b[1] = 0, b[2] = 1, b[3] = 1, b[4] = 0, b[5] = 0, b[6] = 0; break;
	case 12: b[0] = 0, b[1] = 0, b[2] = 1, b[3] = 0, b[4] = 1, b[5] = 0, b[6] = 0; break;
	case 13: b[0] = 0, b[1] = 0, b[2] = 1, b[3] = 0, b[4] = 0, b[5] = 1, b[6] = 0; break;
	case 14: b[0] = 0, b[1] = 0, b[2] = 1, b[3] = 0, b[4] = 0, b[5] = 0, b[6] = 1; break;
	case 15: b[0] = 0, b[1] = 0, b[2] = 0, b[3] = 1, b[4] = 1, b[5] = 0, b[6] = 0; break;
	case 16: b[0] = 0, b[1] = 0, b[2] = 0, b[3] = 1, b[4] = 0, b[5] = 1, b[6] = 0; break;
	case 17: b[0] = 0, b[1] = 0, b[2] = 0, b[3] = 1, b[4] = 0, b[5] = 0, b[6] = 1; break;
	case 18: b[0] = 0, b[1] = 0, b[2] = 0, b[3] = 0, b[4] = 1, b[5] = 1, b[6] = 0; break;
	case 19: b[0] = 0, b[1] = 0, b[2] = 0, b[3] = 0, b[4] = 1, b[5] = 0, b[6] = 1; break;
	case 20: b[0] = 0, b[1] = 0, b[2] = 0, b[3] = 0, b[4] = 0, b[5] = 1, b[6] = 1; break;
	case 21: b[0] = 1, b[1] = 1, b[2] = 1, b[3] = 0, b[4] = 0, b[5] = 0, b[6] = 0; break;
	case 22: b[0] = 1, b[1] = 1, b[2] = 0, b[3] = 1, b[4] = 0, b[5] = 0, b[6] = 0; break;
	case 23: b[0] = 1, b[1] = 1, b[2] = 0, b[3] = 0, b[4] = 1, b[5] = 0, b[6] = 0; break;
	case 24: b[0] = 1, b[1] = 1, b[2] = 0, b[3] = 0, b[4] = 0, b[5] = 1, b[6] = 0; break;
	case 25: b[0] = 1, b[1] = 1, b[2] = 0, b[3] = 0, b[4] = 0, b[5] = 0, b[6] = 1; break;
	case 26: b[0] = 1, b[1] = 0, b[2] = 1, b[3] = 1, b[4] = 0, b[5] = 0, b[6] = 0; break;
	case 27: b[0] = 1, b[1] = 0, b[2] = 1, b[3] = 0, b[4] = 1, b[5] = 0, b[6] = 0; break;
	case 28: b[0] = 1, b[1] = 0, b[2] = 1, b[3] = 0, b[4] = 0, b[5] = 1, b[6] = 0; break;
	case 29: b[0] = 1, b[1] = 0, b[2] = 1, b[3] = 0, b[4] = 0, b[5] = 0, b[6] = 1; break;
	case 30: b[0] = 1, b[1] = 0, b[2] = 0, b[3] = 1, b[4] = 1, b[5] = 0, b[6] = 0; break;
	case 31: b[0] = 1, b[1] = 0, b[2] = 0, b[3] = 1, b[4] = 0, b[5] = 1, b[6] = 0; break;
	case 32: b[0] = 1, b[1] = 0, b[2] = 0, b[3] = 1, b[4] = 0, b[5] = 0, b[6] = 1; break;
	case 33: b[0] = 1, b[1] = 0, b[2] = 0, b[3] = 0, b[4] = 1, b[5] = 1, b[6] = 0; break;
	case 34: b[0] = 1, b[1] = 0, b[2] = 0, b[3] = 0, b[4] = 1, b[5] = 0, b[6] = 1; break;
	case 35: b[0] = 1, b[1] = 0, b[2] = 0, b[3] = 0, b[4] = 0, b[5] = 1, b[6] = 1; break;
	case 36: b[0] = 0, b[1] = 1, b[2] = 1, b[3] = 1, b[4] = 0, b[5] = 0, b[6] = 0; break;
	case 37: b[0] = 0, b[1] = 1, b[2] = 1, b[3] = 0, b[4] = 1, b[5] = 0, b[6] = 0; break;
	case 38: b[0] = 0, b[1] = 1, b[2] = 1, b[3] = 0, b[4] = 0, b[5] = 1, b[6] = 0; break;
	case 39: b[0] = 0, b[1] = 1, b[2] = 1, b[3] = 0, b[4] = 0, b[5] = 0, b[6] = 1; break;
	case 40: b[0] = 0, b[1] = 1, b[2] = 0, b[3] = 1, b[4] = 1, b[5] = 0, b[6] = 0; break;
	case 41: b[0] = 0, b[1] = 1, b[2] = 0, b[3] = 1, b[4] = 0, b[5] = 1, b[6] = 0; break;
	case 42: b[0] = 0, b[1] = 1, b[2] = 0, b[3] = 1, b[4] = 0, b[5] = 0, b[6] = 1; break;
	case 43: b[0] = 0, b[1] = 1, b[2] = 0, b[3] = 0, b[4] = 1, b[5] = 1, b[6] = 0; break;
	case 44: b[0] = 0, b[1] = 1, b[2] = 0, b[3] = 0, b[4] = 1, b[5] = 0, b[6] = 1; break;
	case 45: b[0] = 0, b[1] = 1, b[2] = 0, b[3] = 0, b[4] = 0, b[5] = 1, b[6] = 1; break;
	case 46: b[0] = 0, b[1] = 0, b[2] = 1, b[3] = 1, b[4] = 1, b[5] = 0, b[6] = 0; break;
	case 47: b[0] = 0, b[1] = 0, b[2] = 1, b[3] = 1, b[4] = 0, b[5] = 1, b[6] = 0; break;
	case 48: b[0] = 0, b[1] = 0, b[2] = 1, b[3] = 1, b[4] = 0, b[5] = 0, b[6] = 1; break;
	case 49: b[0] = 0, b[1] = 0, b[2] = 1, b[3] = 0, b[4] = 1, b[5] = 1, b[6] = 0; break;
	case 50: b[0] = 0, b[1] = 0, b[2] = 1, b[3] = 0, b[4] = 1, b[5] = 0, b[6] = 1; break;
	case 51: b[0] = 0, b[1] = 0, b[2] = 1, b[3] = 0, b[4] = 0, b[5] = 1, b[6] = 1; break;
	case 52: b[0] = 0, b[1] = 0, b[2] = 0, b[3] = 1, b[4] = 1, b[5] = 1, b[6] = 0; break;
	case 53: b[0] = 0, b[1] = 0, b[2] = 0, b[3] = 1, b[4] = 1, b[5] = 0, b[6] = 1; break;
	case 54: b[0] = 0, b[1] = 0, b[2] = 0, b[3] = 1, b[4] = 0, b[5] = 1, b[6] = 1; break;
	case 55: b[0] = 0, b[1] = 0, b[2] = 0, b[3] = 0, b[4] = 1, b[5] = 1, b[6] = 1; break;
	}
	return(b);
}
void rand_of_n_7_3(int a[], int n)
{
	int i;
	struct element ele[MAX];
	srand((int)time(0));  // ��ʼ����������� 
	for (i = 0; i < n; i++)
	{
		ele[i].data = rand();  // �������һ���� 
		ele[i].index = i + 1;
	}
	qsort(ele, n, sizeof(ele[0]), cmp_7_3);  //���� 
	for (i = 0; i < n; i++)
	{
		a[i] = ele[i].index;
	}
}
int cmp_7_3(const void *a, const void *b)   // ��������
{
	return((struct element*)a)->data - ((struct element*)b)->data;
}