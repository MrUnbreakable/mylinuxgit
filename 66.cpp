// testJson.cpp : 定义控制台应用程序的入口点。
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
//添加需要的头文件
#include "include/json/json.h"
#define MAX 25000
#pragma warning(disable : 4996)
using namespace std;

//链接需要的库文件
#ifdef _DEBUG
#pragma comment(lib,"json_vc71_libmtd_d.lib")
#else
#pragma comment(lib,"json_vc71_libmtd.lib")
#endif


//************↓要读取的json文件名，文件应该放在工程文件下↓************
const string  jsonfilename = "a.json";
const string  txtfilename = "a.txt";
string str7;
string returnstr;

const int reader = 1;                      //0 读取json 文件    1读取字符串 str
const int choose = 1;                      //0 不使用学校给出上下限 1使用学校给出上下限
const int ad1 = 1000;                      // 每个未排到班级的人的惩罚值
const int ad2 = 10;                        // 班级出现人数过少的惩罚值
const int ad3 = 1000;					   // 每个超出班级数量上限的惩罚值
const int ad4 = 1000;					   // 每个超出教师数量上限的惩罚值
const double ad5 = 0.1;                       // 每个定二班级中走一班类型的惩罚值
struct element {                           //用来排序的数据结构 
	int data;                              // 数据 
	int index;                             // 序号 
};

int i6, j6, k6, ii6;
int times_6_3 = 2;									  //每times轮减少一个定班
int lu_6_3 = 0;                                       //班级人数上限
int ld_6_3 = 0;                                       //班级人数下限
int classroomlu_6_3 = 0;                              //教室人数上限
int unadd_6_3 = 0;                                    //普通教室数量
int add_6_3 = 0;                                      //走班时增加的班级数
int classsum_6_3 = 0;                                 //总班级数
int bigclassmax_6_3 = 0;							  //大教室上限
int bigclassnum_6_3 = 0;							  //大教室个数
const int NIND = 100;                             //种群数量
const int MAXGEN = 100;                           //遗传代数
const double px = 0.97;                           //交叉率
const double pm = 0.1;                            //变异率
const double GGAP = 0.9;                          //代沟

int complete_6_3 = 0;                                 //分班完成标志位
int runsnumber_6_3 = 0;                               //算法执行次数
int maxrunsnumber_6_3 = 3;                            //最大算法执行次数 这里赋初值 在gettools函数里会根据走班数量自动计算重新赋值
int** lists_6_3 = new int* [2];                      //创建定三分班结果列表
int** out1_6_3 = new int* [2];                        //存定二最后输出最优结果  out1_6_3[2][PRECI]  0行放班级类型 1行放人数
string** studentno_6_3;                              //创建学生姓名、学号记录表 用于最后输出匹配用
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
int** disclass_6_3;//定三+定二结果
int allgocla_6_3 = 0;//总走班数
int countq_6_3;//总走班数
//************↓函数声明↓**********************************************
int** gettools(int** stuinform, int stunum, int* randnumber);//获取固定班信息
int** getstu1(int** stuinform, int** tools, int* randnumber);//获取走二学生信息
int** getstu2(int** stuinform, int** tools, int* randnumber);//获取定三学生信息
int** sectionstu2(int** stu2, int** tools);//定三分班，返回学生分班结果
int getstudentnumber();                   //获取学生数量，用于创建数组
int getstudentnumberfromstring();                   //在字符串中获取学生数量，用于创建数组
int** readFileJson(int studentnumber_6_3);                    //从文件中读取JSON，一个存储了JSON格式字符串的文件
int** readJson(int studentnumber_6_3);                    //从字符串中读取JSON
int* swit(int p, int b[]);                //p为课程ID b数组存储课程对应六位二进制编码
int* translate(string volunteer);        //把选课情况的汉字组合翻译成一行六列的二进制表示
string translate2(int* b);               //把选课情况的二进制翻译成字符串
int** updatepopulation(int** pop, double* objv, int gen, int PRECI, int** out); //更新种群，包括挑选优秀个体、交叉、变异
int cmp(const void* a, const void* b);    //升序排列 
void rand_of_n(int a[], int n);           //产生 1-n 的随机排列并存到 a[] 中
double** ranking(int** stu1, int** tools, int** pop);//获取适应度值
int** genetic(int** stu1, int** tools); //遗传算法
string writeFileJson(int** stu1out, int** stu2out, int** tools);   //将信息保存为JSON格式 
void sectionclassroom(int** stu1out, int** stu2out, int** tools);   //将信息保存为JSON格式 
//string makeclass(string str);
//**********************************************************************

string makeclass(string inputstr)
{
	/********从json文件读取**********/
	/******从字符串中读取  字符串str读取于txt**********/
	if (reader == 1)
	{
		str7 = inputstr;
		studentnumber_6_3 = getstudentnumberfromstring();//在字符串中获取学生总人数
		studentinformation_6_3 = readJson(studentnumber_6_3);//获取学生信息到二维数组studentinformation
	}
	else if (reader == 0)
	{
		studentnumber_6_3 = getstudentnumber();//获取学生总人数
		studentinformation_6_3 = readFileJson(studentnumber_6_3);//获取学生信息到二维数组studentinformation
	}
	/*******************/

	if (choose != 0)
	{
		for (int i6 = 0; i6 < 5; i6++)
		{
			if (plotno_6_3[i6][0] == 1) lu_6_3 = plotno_6_3[i6][1];//选择是否使用学校给出的教室上限
			if (plotno_6_3[i6][0] == 2) ld_6_3 = plotno_6_3[i6][1];//选择是否使用学校给出的教室下限

		}
	}
	for (int i6 = 0; i6 < 5; i6++)
	{
		if (plotno_6_3[i6][0] == 4) bigclassmax_6_3 = plotno_6_3[i6][1];//大教室上限
		if (plotno_6_3[i6][0] == 5) bigclassnum_6_3 = plotno_6_3[i6][1];//大教室个数
	}

	int* rand = new int[studentnumber_6_3]; //创建数组rand存放乱序序号用来打乱学生信息顺序
	rand_of_n(rand, studentnumber_6_3);
	while (complete_6_3 != 1)
	{

		if (runsnumber_6_3 < maxrunsnumber_6_3)//如果运行次数没到上限
		{
			cout << "正在进行分班，进行第" << runsnumber_6_3 + 1 << "次尝试" << endl;
			int** tools = gettools(studentinformation_6_3, studentnumber_6_3, rand);//获取统计过的工具数组
			int** stu2 = getstu2(studentinformation_6_3, tools, rand);//获取定三学生信息
			int** stu1 = getstu1(studentinformation_6_3, tools, rand);//获取定二学生信息
			int** stu2out = sectionstu2(stu2, tools);//获取定三分班结果
			int** stu1out = genetic(stu1, tools); //遗传算法 获取定二分班结果
			runsnumber_6_3 = runsnumber_6_3 + 1;//记录算法运行次数
			if (complete_6_3 == 1)//如果分完了
			{
				sectionclassroom(stu1out, stu2out, tools);
				returnstr = writeFileJson(stu1out, stu2out, tools);
			}
		}
		else
		{
			cout << "分班失败" << endl;
			break;
		}
	}
	return returnstr;
}
void sectionclassroom(int** stu1out, int** stu2out, int** tools)
{
	int PRECI = tools[4][5];           //获取定二班级数量

	int* classcontain = new int[PRECI];
	for (i6 = 0; i6 < PRECI; i6++)
	{
		if (i6 < bigclassnum_6_3)classcontain[i6] = bigclassmax_6_3;
		else classcontain[i6] = lu_6_3;
	}
	//给每个学生分配班级,6行依次存放班级类型、班级名称、本来应该放的人数、操作过程中放了的人数、男生的人数、女生的人数。
	int** stuplus = new int* [tools[4][3]];
	for (i6 = 0; i6 < tools[4][3]; i6++)		stuplus[i6] = new int[9];
	for (i6 = 0; i6 < tools[4][1]; i6++)//放入定三学生信息
	{
		for (j6 = 0; j6 < 9; j6++) stuplus[i6][j6] = stu2out[i6][j6];
	}
	for (i6 = tools[4][1]; i6 < tools[4][3]; i6++)//放入定二学生信息
	{
		for (j6 = 0; j6 < 9; j6++)
		{
			stuplus[i6][j6] = stu1out[i6 - tools[4][1]][j6];
		}
	}
	int stu2num = tools[4][1];//定三人数
	int ss = tools[4][2];//定三班数
	int NUM = tools[4][2] + tools[4][5];//总班级数量
	//int PRECI = tools[4][5];//定二走一班数量
	int stu1num = tools[4][4];//定二人数
	disclass_6_3 = new int* [6]; //
	for (i6 = 0; i6 < 6; i6++)		disclass_6_3[i6] = new int[NUM];
	classname_6_3 = new int[tools[4][3]];//行政班班名
	classname1_6_3 = new int* [2]; //走班班名和是否已分配
	for (i6 = 0; i6 < 2; i6++)		classname1_6_3[i6] = new int[tools[4][4]];
	for (i6 = 0; i6 < tools[4][4]; i6++) classname1_6_3[1][i6] = 0;//第二行清零 用来记录是否分配过
	for (i6 = 0; i6 < ss; i6++)
	{
		disclass_6_3[0][i6] = lists_6_3[0][i6];//固定班型
		disclass_6_3[2][i6] = lists_6_3[1][i6];//固定班容量
	}
	for (i6 = ss; i6 < NUM; i6++)
	{
		disclass_6_3[0][i6] = out1_6_3[0][i6 - ss];//走班班型
		disclass_6_3[2][i6] = out1_6_3[1][i6 - ss];//走班容量
	}
	for (j6 = 0; j6 < classroomno_6_3[1][5]; j6++)
	{
		if (classroomno_6_3[j6][4] == 2)    classroomno_6_3[j6][4] = 0;
		else if (classroomno_6_3[j6][4] == 3)    classroomno_6_3[j6][4] = 1;
	}
	for (i6 = 0; i6 < NUM; i6++)
	{
		int flag = 0;
		for (j6 = 0; j6 < classroomno_6_3[1][5]; j6++)//无论定走 全都分配上教室
		{
			if (classroomno_6_3[j6][4] == 0 && flag == 0)//普通教室
			{
				disclass_6_3[1][i6] = classroomno_6_3[j6][1];//教室命名 用的教室id
				classroomno_6_3[j6][4] = 2;
				flag = 1;
			}
		}
		//for (int j6 = 0; j6 < classroomno_6_3[1][5]; j6++)
		//{
		//	if (classroomno_6_3[j6][4] == 1 && flag == 0)
		//	{
		//		disclass_6_3[1][i6] = classroomno_6_3[j6][1];//教室命名 用的教室id
		//		classroomno_6_3[j6][4] = 3;
		//		flag = 1;
		//	}		
		//}
		disclass_6_3[3][i6] = 0;//
		disclass_6_3[4][i6] = 0;//男
		disclass_6_3[5][i6] = 0;//女
	}


	for (i6 = 0; i6 < tools[4][3]; i6++)//遍历学生 分定三 男女均分
	{
		int aaa = 1;//记录能否放进去
		int bbb = -1;//记录位置
		int ccc = lu_6_3;//记录最小上限
		for (j6 = 0; j6 < NUM; j6++)//遍历所有班级
		{
			aaa = stuplus[i6][8] - disclass_6_3[0][j6];//8班型   班型相减
			if (aaa == 0)//如果能放进去
			{
				if (disclass_6_3[3][j6] < disclass_6_3[2][j6])//如果还没放满这个班级
				{
					if (stuplus[i6][7] == 1)//如果男
					{
						if (disclass_6_3[4][j6] < ccc)//如果最小
						{
							bbb = j6;//记录位置
							ccc = disclass_6_3[4][j6];//最小更新
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
		classname_6_3[i6] = disclass_6_3[1][bbb];//记录这个学生分配到了哪个教室，视为信息表第十列
		if (stuplus[i6][7] == 1)
		{
			disclass_6_3[4][bbb] = disclass_6_3[4][bbb] + 1;//判断性别 
		}
		else
		{
			disclass_6_3[5][bbb] = disclass_6_3[5][bbb] + 1;//
		}
		disclass_6_3[3][bbb] = disclass_6_3[4][bbb] + disclass_6_3[5][bbb];
	}


	int** goone = new int* [8]; //创建走二各班学科统计列表
	for (i6 = 0; i6 < 8; i6++)		goone[i6] = new int[PRECI];//0 班型 1班级id 2物理3化学 4生物 5政治 6历史 7地理
	for (i6 = ss; i6 < NUM; i6++)
	{
		goone[0][i6 - ss] = disclass_6_3[0][i6];//班型 摘出定二
		goone[1][i6 - ss] = disclass_6_3[1][i6];//班级名
	}
	for (i6 = 2; i6 < 8; i6++) //清零
	{
		for (j6 = 0; j6 < PRECI; j6++)
		{
			goone[i6][j6] = 0;
		}
	}
	for (i6 = 0; i6 < stu1num; i6++)//遍历学生
	{
		int ddd = 1;
		for (j6 = 0; j6 < PRECI; j6++)//遍历班班级
		{
			ddd = goone[1][j6] - classname_6_3[i6 + tools[4][1]];//如果这学生是这个班的
			if (ddd == 0)
			{
				for (k6 = 0; k6 < 6; k6++)
				{
					goone[k6 + 2][j6] = goone[k6 + 2][j6] + stuplus[i6 + tools[4][1]][k6];//统计学生科目 
				}
				break;
			}
		}
	}

	for (i6 = 2; i6 < 8; i6++)//清零定二班的固定科目
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





	int gocla[6];//各科走班数
	//cout << "提示：科目0-物理 1-化学 2-生物 3-政治 4-历史 5-地理"<< endl;
	int subjecttotal[6] = { 0,0,0,0,0,0 };
	for (i6 = 0; i6 < 6; i6++)
	{

		for (int j6 = 0; j6 < PRECI; j6++)
		{
			subjecttotal[i6] = subjecttotal[i6] + goone[i6 + 2][j6];
		}
		gocla[i6] = ceil(subjecttotal[i6] / (lu_6_3 * 1.0));
		string subtemp;
		if (i6 == 0) subtemp = "物";
		else if (i6 == 1) subtemp = "化";
		else if (i6 == 2) subtemp = "生";
		else if (i6 == 3) subtemp = "政";
		else if (i6 == 4) subtemp = "史";
		else if (i6 == 5) subtemp = "地";

		cout << "科目 " << subtemp << " 拟走班人数为" << subjecttotal[i6] << "   共开班" << gocla[i6] << "个" << endl;
		allgocla_6_3 = allgocla_6_3 + gocla[i6];
	}

	cout << "总拟走班数为：" << allgocla_6_3 << endl;

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

	//走班分配教室部分	
	int* all = new int[6 * PRECI];//存放各班走科排序
	for (i6 = 0; i6 < 6; i6++)
	{
		for (j6 = 0; j6 < PRECI; j6++)
		{
			all[i6 * PRECI + j6] = goone[i6 + 2][j6];//所有走科导入all
		}
	}
	int tempa;//排序
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
	}//all排序完成
	shu_6_3 = new int* [3]; //存放第一行 班号 第二行  是否开班0未开 1 开  第三行 开了什么班
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
					shu_6_3[0][i6] = classroomno_6_3[j6][1];//教室命名 用的教室id
					classroomno_6_3[j6][4] = 3;
					flag2 = 1;
				}
			}
		}
	}

	int gocla1[6] = { 0,0,0,0,0,0 };//计数已经开了什么班
	int* gocla2 = new int[PRECI];
	for (i6 = 0; i6 < PRECI; i6++)
	{
		gocla2[i6] = 1;
	}
	int ggg = -1, hhh = -1, js = 0, tt;
	for (int qr = 0; qr < 6 * PRECI; qr++)//遍历all
	{
		ggg = -1;
		hhh = -1;
		int flag1 = 0;
		for (i6 = 0; i6 < 6; i6++)//遍历goone
		{
			for (j6 = 0; j6 < PRECI; j6++)
			{
				if (gocla2[j6] == 1)//定二班还没分配
				{
					tt = goone[i6 + 2][j6] - all[qr];//核对是否是最合适的班级
					if (tt == 0 && gocla[i6] - gocla1[i6] != 0)
					{
						ggg = i6; hhh = j6;//记录行 列
						flag1 = 1;
						break;
					}
				}
			}
			if (flag1 == 1) { break; }
		}
		if (gocla[ggg] - gocla1[ggg] != 0 && ggg != -1)//如果还没开满
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

	if (countq_6_3 - PRECI > 0)//如果有add
	{
		for (i6 = 0; i6 < countq_6_3 - PRECI; i6++)//遍历add
		{
			for (j6 = 0; j6 < 6; j6++)//遍历六个学科
			{
				if (gocla[j6] - gocla1[j6] != 0)//如过有某科目没开完
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
		shu_6_3[1][j6] = 0;//清零 用来计数
	}
	for (i6 = 0; i6 < stu1num; i6++)
	{
		int classsubj = 7;//教室科目
		int stusubj = 6;//学生科目
		int classsubjno = -1;
		for (j6 = 0; j6 < PRECI; j6++)
		{
			if (classname_6_3[stu2num + i6] == shu_6_3[0][j6])
			{
				classsubj = shu_6_3[2][j6];//该生原教室的走班课
				classsubjno = j6;
			}
		}
		int b[6];
		swit(stuplus[stu2num + i6][8], b);
		for (j6 = 0; j6 < 6; j6++)
		{
			if (stuplus[stu2num + i6][j6] - b[j6] == 1) stusubj = j6;//该生需要走的课
		}
		if (stusubj == classsubj)//如果原班可以放
		{
			classname1_6_3[0][i6] = classname_6_3[stu2num + i6];//放到原班级
			classname1_6_3[1][i6] = 1;
			shu_6_3[1][classsubjno] = shu_6_3[1][classsubjno] + 1;//计数
		}
	}
	for (i6 = 0; i6 < stu1num; i6++)//遍历所有定二学生
	{
		if (classname1_6_3[1][i6] == 0)//如果这个学生还没放置
		{
			int aaa = 1;//记录能否放进去
			int bbb = -1;//记录位置
			int ccc;
			if (bigclassnum_6_3 != 0)
			{
				ccc = bigclassmax_6_3;
			}
			else
			{
				ccc = lu_6_3;
			}
			int stusubj = 6;//学生科目
			int b[6];
			swit(stuplus[stu2num + i6][8], b);
			for (j6 = 0; j6 < 6; j6++)
			{
				if (stuplus[stu2num + i6][j6] - b[j6] == 1) stusubj = j6;//该生需要走的课
			}
			for (j6 = 0; j6 < countq_6_3; j6++)
			{
				aaa = stusubj - shu_6_3[2][j6];//   班型相减
				if (aaa == 0)//如果能放进去
				{
					if (shu_6_3[1][j6] < classcontain1[j6])//如果还没放满这个班级**************************
					{
						if (shu_6_3[1][j6] < ccc)//如果最小
						{
							bbb = j6;//记录位置
							ccc = shu_6_3[1][j6];//最小更新
						}
					}
				}
			}
			classname1_6_3[0][i6] = shu_6_3[0][bbb];//记录这个学生分配到了哪个教室
			classname1_6_3[1][i6] = 1;
			shu_6_3[1][bbb] = shu_6_3[1][bbb] + 1;//计数
		}
	}
	cout << "----------------------------------------------------------------" << endl;
	for (i6 = 0; i6 < 3; i6++)/************************************************************/
	{
		if (i6 == 0) cout << " 走一教室:  ";
		else if (i6 == 1) cout << " 班级人数： ";
		else if (i6 == 2) cout << " 开班类型： ";
		for (j6 = 0; j6 < countq_6_3; j6++)
		{
			cout.width(3);
			if (i6 < 2) cout << shu_6_3[i6][j6] << "  ";
			else if (i6 == 2)
			{
				if (shu_6_3[i6][j6] == 0) { cout.width(3); cout << "物   "; }
				else if (shu_6_3[i6][j6] == 1) { cout.width(3); cout << "化   "; }
				else if (shu_6_3[i6][j6] == 2) { cout.width(3); cout << "生   "; }
				else if (shu_6_3[i6][j6] == 3) { cout.width(3); cout << "政   "; }
				else if (shu_6_3[i6][j6] == 4) { cout.width(3); cout << "史   "; }
				else if (shu_6_3[i6][j6] == 5) { cout.width(3); cout << "地   "; }
			}
		}
		cout << " \n";
	}
	cout << endl;

}
int** genetic(int** stu1, int** tools)
{
	int gen = 0;                      //遗传代数计数器
	int stu1numb = tools[4][4];       //获取定二学生数量
	int PRECI = tools[4][5];           //获取定二班级数量

	int** pop = new int* [NIND];      //pop为生成种群 pop[NIND][tools[4][5]]
	for (i6 = 0; i6 < NIND; i6++)		pop[i6] = new int[PRECI];


	for (i6 = 0; i6 < 2; i6++)		    out1_6_3[i6] = new int[PRECI];

	double** trace = new double* [2];     //存放历代最佳分班方式 trace[2][MAXGEN]用于生成曲线
	for (i6 = 0; i6 < 2; i6++)		trace[i6] = new double[MAXGEN];

	double* objv = new double[NIND];  //适应度值

	double globalminobjv = 0.0; //记录全局最小适应度值

	int* stufinalclass = new int[stu1numb];  //用于记录学生最终选择

	int** stu1out = new int* [stu1numb];        //存放走一班学生选课信息及分班结果
	for (i6 = 0; i6 < stu1numb; i6++)		    stu1out[i6] = new int[9];

	for (i6 = 0; i6 < NIND; i6++)       //随机生成初始种群
	{
		for (j6 = 0; j6 < PRECI; j6++)
		{
			int randompop = rand();
			pop[i6][j6] = randompop % 15;           //生成0-14的随机数，表示生成的随机定二走一班级类型
		}
	}

	while (gen < MAXGEN)                    //
	{

		double** tools2 = ranking(stu1, tools, pop);     //获取适应度值，并返回单词最优各学生分班去向以及各班人数

		for (int i6 = 0; i6 < NIND; i6++)
		{
			double tempobjv = tools2[i6][2];
			objv[i6] = tempobjv;
		}

		double minobjv = (*min_element(objv, objv + NIND)); //最小适应度值
		int minpos = (min_element(objv, objv + NIND) - objv); //最小值的位置  ？？

		trace[0][gen] = minobjv; //用于观察适应度值变化 记录每代最小适应度值
		trace[1][gen] = gen;     // 第n代

		if (gen > 0)
		{
			if (minobjv < globalminobjv)               //如果是全局最优
			{
				globalminobjv = minobjv;               //记录全局最优适应度值
				for (i6 = 0; i6 < stu1numb; i6++)
				{
					stufinalclass[i6] = tools2[i6][0];   //记录最优解学生班级归属
				}
				for (i6 = 0; i6 < PRECI; i6++)
				{
					out1_6_3[0][i6] = pop[minpos][i6];       //全局最优个体id
					out1_6_3[1][i6] = tools2[i6][1];         //全局最优个体各班学生数量
				}
			}
		}
		else//如果是第0代 则记录0代最优解
		{
			globalminobjv = minobjv;             //记录全局最优适应度值
			for (i6 = 0; i6 < stu1numb; i6++)
			{
				stufinalclass[i6] = tools2[i6][0];    //记录最优解学生班级归属
			}
			for (i6 = 0; i6 < PRECI; i6++)
			{
				out1_6_3[0][i6] = pop[minpos][i6];      //全局最优个体id
				out1_6_3[1][i6] = tools2[i6][1];      //全局最优个体各班学生数量
			}
		}

		pop = updatepopulation(pop, objv, gen, PRECI, out1_6_3);//选择交叉变异

		gen = gen + 1;
	}


	if (globalminobjv < PRECI * 10)//判断适应度值是否达标
	{
		complete_6_3 = 1;   // 如果适应度值较小（代表成功分班），则标志分班完成
		cout << "----------------------------------------------------------------" << endl;
		cout << "最小适应度值：" << globalminobjv << endl;

		for (i6 = 0; i6 < 2; i6++)
		{
			if (i6 == 0) cout << "定三班级类型：";
			else cout << "定三班级人数：";
			for (int j6 = 0; j6 < tools[4][2]; j6++)
			{
				cout.width(3);
				cout << lists_6_3[i6][j6] << ' ';
			}
			cout << '\n' << endl;
		}

		for (i6 = 0; i6 < 2; i6++)
		{
			if (i6 == 0) cout << "走一班级类型：";
			else cout << "走一班级人数：";
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
		if (stu1numb - zongrenshu == 0) 	cout << "所有同学均已分班完成" << endl;
		else cout << "仍有同学未成功分配班级" << endl;
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

	double* objv = new double[NIND];  //适应度值

	int stu1numb = tools[4][4];       //获取定二学生数量
	int PRECI = tools[4][5];           //获取定二班级数量


	int* classcontain = new int[PRECI];
	for (i6 = 0; i6 < PRECI; i6++)
	{
		if (i6 < bigclassnum_6_3)classcontain[i6] = bigclassmax_6_3;
		else classcontain[i6] = lu_6_3;
	}
	int total[6];                     //用于计算剩余未选科目人数
	int total1[6];                    //统计已经放入科目的人数
	int total2[6];                    //对stu11进行按列相加,统计定二班各科总人数

	int** class1 = new int* [stu1numb];      //放每个生成的定二走一班级人数 num[NIND][tools[4][5]]
	for (i6 = 0; i6 < stu1numb; i6++)		class1[i6] = new int[NIND];

	int** num = new int* [NIND];      //放每个生成的定二走一班级人数 num[NIND][tools[4][5]]
	for (i6 = 0; i6 < NIND; i6++)		num[i6] = new int[PRECI];

	int tools2line = stu1numb + NIND;
	double** tools2 = new double* [tools2line];  //用于记录学生最终选择
	for (i6 = 0; i6 < tools2line; i6++)		tools2[i6] = new double[3];

	for (i6 = 0; i6 < 6; i6++)//清零
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




	for (i6 = 0; i6 < NIND; i6++)         //计算种群每一个个体（每一种班级组合）
	{
		for (j6 = 0; j6 < 6; j6++)//清零
		{
			total[j6] = 0;
			total1[j6] = 0;
			total2[j6] = 0;
		}
		for (j6 = 0; j6 < 6; j6++) //统计定二班各科总人数
		{
			for (k6 = 0; k6 < stu1numb; k6++)
			{
				total2[j6] = stu1[k6][j6] + total2[j6];//存放stu11按列相加 统计各科数量吧？
			}
		}
		for (k6 = 0; k6 < stu1numb; k6++)     //遍历定二所有学生   
		{
			int e = -1;                  //用于寄存符合条件的班级序号（用于判断是否放进了班级）
			int f = 0;                   //用于寄存符合条件的班级中人数最少的班级学生数量（优先放入）
			if (bigclassnum_6_3 > 0) f = bigclassmax_6_3;
			else f = lu_6_3;


			for (j6 = 0; j6 < PRECI; j6++)    //遍历每个定二走一班级      
			{

				int b[6];
				swit(pop[i6][j6], b);      //翻译出第i行第j个班级
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
					if (num[i6][j6] < classcontain[j6]) //每次都放到人数最少的班级
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
				num[i6][e] = num[i6][e] + 1; //种群中某染色体计数+1
				class1[k6][i6] = pop[i6][e];//记录学生被分到了什么班级
			}
		}

		/*int **stu1outtemp = new int *[stu1numb];      //放每个生成的定二走一班级人数 num[NIND][tools[4][5]]
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


		//给每个学生分配班级,6行依次存放班级类型、班级名称、本来应该放的人数、操作过程中放了的人数、男生的人数、女生的人数。
		int** stuplus = new int* [tools[4][3]];
		for (ii6 = 0; ii6 < tools[4][3]; ii6++)		stuplus[ii6] = new int[9];

		for (ii6 = tools[4][1]; ii6 < tools[4][3]; ii6++)//放入定二学生信息
		{
			for (j6 = 0; j6 < 8; j6++)
			{
				stuplus[ii6][j6] = stu1[ii6 - tools[4][1]][j6];
			}
			stuplus[ii6][8] = class1[ii6 - tools[4][1]][i6];
		}




		//int stu2num = tools[4][1];//定三人数
		int ss = tools[4][2];//定三班数
		int NUM = tools[4][2] + tools[4][5];//总班级数量
		int stu1num = tools[4][4];//定二人数
		disclass_6_3 = new int* [6]; //
		for (ii6 = 0; ii6 < 6; ii6++)		disclass_6_3[ii6] = new int[NUM];
		classname_6_3 = new int[tools[4][3]];//行政班班名
		for (ii6 = 0; ii6 < ss; ii6++)
		{
			disclass_6_3[0][ii6] = lists_6_3[0][ii6];//固定班型
			disclass_6_3[2][ii6] = lists_6_3[1][ii6];//固定班容量
		}
		for (j6 = ss; j6 < NUM; j6++)
		{
			disclass_6_3[0][j6] = pop[i6][j6 - ss];//走班班型
			disclass_6_3[2][j6] = num[i6][j6 - ss];//走班容量
		}
		for (j6 = 0; j6 < classroomno_6_3[1][5]; j6++)
		{
			if (classroomno_6_3[j6][4] == 2)    classroomno_6_3[j6][4] = 0;
			else if (classroomno_6_3[j6][4] == 3)    classroomno_6_3[j6][4] = 1;
		}
		for (ii6 = 0; ii6 < NUM; ii6++)
		{
			int flag = 0;
			for (j6 = 0; j6 < classroomno_6_3[1][5]; j6++)//无论定走 全都分配上教室
			{
				if (classroomno_6_3[j6][4] == 0 && flag == 0)//普通教室
				{
					disclass_6_3[1][ii6] = classroomno_6_3[j6][1];//教室命名 用的教室id
					classroomno_6_3[j6][4] = 2;
					flag = 1;
				}
			}

			disclass_6_3[3][ii6] = 0;//
			disclass_6_3[4][ii6] = 0;//男
			disclass_6_3[5][ii6] = 0;//女
		}
		for (ii6 = tools[4][1]; ii6 < tools[4][3]; ii6++)//遍历学生 分定三 男女均分
		{
			int aaa = 1;//记录能否放进去
			int bbb = -1;//记录位置
			int ccc = lu_6_3;//记录最小上限
			for (j6 = 0; j6 < NUM; j6++)//遍历所有班级
			{
				aaa = stuplus[ii6][8] - disclass_6_3[0][j6];//8班型   班型相减
				if (aaa == 0)//如果能放进去
				{
					if (disclass_6_3[3][j6] < disclass_6_3[2][j6])//如果还没放满这个班级
					{
						if (stuplus[ii6][7] == 1)//如果男
						{
							if (disclass_6_3[4][j6] < ccc)//如果最小
							{
								bbb = j6;//记录位置
								ccc = disclass_6_3[4][j6];//最小更新
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
			classname_6_3[ii6] = disclass_6_3[1][bbb];//记录这个学生分配到了哪个教室，视为信息表第十列
			if (stuplus[ii6][7] == 1)
			{
				disclass_6_3[4][bbb] = disclass_6_3[4][bbb] + 1;//判断性别 
			}
			else
			{
				disclass_6_3[5][bbb] = disclass_6_3[5][bbb] + 1;//
			}
			disclass_6_3[3][bbb] = disclass_6_3[4][bbb] + disclass_6_3[5][bbb];
		}


		int** goone = new int* [8]; //创建走二各班学科统计列表
		for (ii6 = 0; ii6 < 8; ii6++)		goone[ii6] = new int[PRECI];//0 班型 1班级id 2物理3化学 4生物 5政治 6历史 7地理
		for (ii6 = 0; ii6 < 8; ii6++)
		{
			for (j6 = 0; j6 < PRECI; j6++)
			{
				goone[ii6][j6] = 0;
			}
		}
		int** goone1 = new int* [8]; //创建走二各班学科统计列表
		for (ii6 = 0; ii6 < 8; ii6++)		goone1[ii6] = new int[PRECI];//0 班型 1班级id 2物理3化学 4生物 5政治 6历史 7地理
		for (ii6 = ss; ii6 < NUM; ii6++)
		{
			goone[0][ii6 - ss] = disclass_6_3[0][ii6];//班型 摘出定二
			goone[1][ii6 - ss] = disclass_6_3[1][ii6];//班级名
		}
		for (ii6 = 0; ii6 < stu1num; ii6++)//遍历学生
		{
			int ddd = 1;
			for (j6 = 0; j6 < PRECI; j6++)//遍历班班级
			{
				ddd = goone[1][j6] - classname_6_3[ii6 + tools[4][1]];//如果这学生是这个班的
				if (ddd == 0)
				{
					for (k6 = 0; k6 < 6; k6++)
					{
						goone[k6 + 2][j6] = goone[k6 + 2][j6] + stuplus[ii6 + tools[4][1]][k6];//统计学生科目 
					}
					break;
				}
			}
		}

		for (ii6 = 2; ii6 < 8; ii6++)//清零定二班的固定科目
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
				total1[k6] = total1[k6] + num[i6][j6] * b[k6]; //放进去了的各科目人数？
			}
		}
		for (j6 = 0; j6 < 6; j6++)
		{
			total[j6] = total2[j6] - total1[j6];//还剩下没放进去的各科人数、
			//cout << total[j6] << " " << total2[j6] << " " << total1[j6] << endl;
		}
		int meansum = 0;                   //已放入班级的总人数
		int d1 = 0;                       //没放进去的人数


		for (j6 = 0; j6 < PRECI; j6++)//求放进去的总人数
		{
			meansum = meansum + num[i6][j6];
		}
		d1 = stu1numb - meansum;
		float mean = meansum / (PRECI * 1.0);//平均数

		float sum1 = 0.0;
		for (j6 = 0; j6 < PRECI; j6++)
		{
			sum1 = (num[i6][j6] - mean) * (num[i6][j6] - mean) * 1.0 + sum1;
		}
		float s1 = sum1 / (PRECI * 1.0);   //方差
		int d2 = 0;                         //用于判断是否人数过少
		for (j6 = 0; j6 < PRECI; j6++)     //如果人数不够最低限度 惩罚
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

			int d5 = 0;//用于判断定二班级走一类型是否少
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
		tools2[i6][2] = objv[i6]; //tools2[i6][2]存入本次适应度值
	}
	int minpos = (min_element(objv, objv + NIND) - objv);          //单次最小值的位置 

	for (i6 = 0; i6 < stu1numb; i6++)
	{
		tools2[i6][0] = class1[i6][minpos];// tools2[i6][0]存入本次最优学生班级归属
	}
	for (i6 = 0; i6 < PRECI; i6++)
	{
		tools2[i6][1] = num[minpos][i6];// tools2[i6][1]存入本次最优各班学生数量
	}
	return tools2;
}
int** updatepopulation(int** pop, double* objv, int gen, int PRECI, int** out)
{
	int** popnext = new int* [NIND];      //popnext为更新后种群 popnext[NIND][tools[4][5]]
	for (i6 = 0; i6 < NIND; i6++)		popnext[i6] = new int[PRECI];

	for (i6 = 0; i6 < NIND; i6++)
	{
		for (j6 = 0; j6 < PRECI; j6++)
		{
			popnext[i6][j6] = pop[i6][j6];
		}
	}

	int* temp0 = new int[PRECI];
	for (i6 = 0; i6 < NIND; i6++)                 // 根据个体适应度来排序；（冒泡法）
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

	for (i6 = NIND * GGAP; i6 < NIND; i6++)       //按照代沟保留优势个体
	{
		for (j6 = 0; j6 < PRECI; j6++)
		{

			popnext[i6][j6] = popnext[NIND - i6 - 1][j6];
		}
	}



	int* temp1 = new int[PRECI];
	for (i6 = 0; i6 < (NIND / 2); i6++)
	{
		double random1 = (rand() % 10) / 10.0;  //产生0-1的随机小数,用来判断是否交叉
		if (random1 >= (1.0 - px))
		{
			int random2 = rand() % PRECI;                     // 随机生成交叉位置，交叉点控制在0到PRECI之间；
			for (j6 = random2; j6 < PRECI; j6++)
			{
				temp1[j6] = popnext[i6 * 2 + 1][j6];
				popnext[i6 * 2 + 1][j6] = popnext[i6 * 2][j6];
				popnext[i6 * 2][j6] = temp1[j6];
			}
		}
	}

	for (i6 = 0; i6<int(NIND * PRECI * pm); i6++)                             //变异
	{
		int col = rand() % PRECI;                            // 随机产生要变异的基因位号；
		int row = rand() % NIND;                             // 随机产生要变异的染色体号；
		popnext[row][col] = rand() % 15;                  //在0-14之间随机变换一种
	}
	for (i6 = 0; i6 < PRECI; i6++)                         //把全局最优插入
	{
		popnext[(NIND - 1)][i6] = out[0][i6];
	}


	return popnext;

}
int** sectionstu2(int** stu2, int** tools)
{
	int num = tools[4][2];//定三班个数
	int** stu2out = new int* [tools[4][1]]; //创建定三分班结果列表
	for (i6 = 0; i6 < tools[4][1]; i6++)		stu2out[i6] = new int[9];

	for (i6 = 0; i6 < 2; i6++)		lists_6_3[i6] = new int[num];
	int knum = 0; //初始化list计数器
	for (i6 = 0; i6 < 20; i6++)//遍历二十种班型
	{
		if (tools[2][i6] > 0)//如果开班
		{

			for (j6 = 0; j6 < tools[2][i6]; j6++)//开x个班
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
		int e = -1;                  //用于寄存符合条件的班级序号（用于判断是否放进了班级）
		int f = lu_6_3;                  //用于寄存符合条件的班级中人数最少的班级学生数量（优先放入）

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
	int u[20][6];//班级编码比较模板
	for (i6 = 0; i6 < 20; i6++)
	{
		int b[6];
		swit(tools[0][i6], b);
		for (j6 = 0; j6 < 6; j6++)
		{
			u[i6][j6] = b[j6];                    //u[i6][j6]存放第一次分好选课信息的固定班级的类型
		}
	}

	int num2 = tools[4][1];//定三人数
	int** stu2 = new int* [num2];
	for (i6 = 0; i6 < num2; i6++)		stu2[i6] = new int[9];
	int y[20];
	int stu2num = 0;
	int stu2num2 = 0;
	for (i6 = 0; i6 < 20; i6++)          y[i6] = 0;
	for (i6 = 0; i6 < tools[4][3]; i6++) //tools[4][3]是学生总数
	{
		int f[9];//暂存使用的学生信息
		for (j6 = 0; j6 < 9; j6++)
		{
			f[j6] = stuinform[(randnumber[i6] - 1)][j6];       //千万注意这里的stu必须是前面的stu，不能再重新生成，否则会和所求的匹配不上！！！！！！！
		}
		for (k6 = 0; k6 < 20; k6++) //遍历20种可能班
		{
			if (tools[2][k6] > 0) //如果有开班
			{
				if (y[k6] < tools[3][k6]) //还没放满
				{
					int h = 0; //比较计数位

					for (int g = 0; g < 6; g++)
					{
						if (f[g] - u[k6][g] == 0)    h = h + 1;//统计相同位个数	
					}
					if (h == 6)          //每个学生与固定班级的科目进行比较，符合的就放进去
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
	int u[20][6];//班级编码比较模板
	for (i6 = 0; i6 < 20; i6++)
	{
		int b[6];
		swit(tools[0][i6], b);
		for (j6 = 0; j6 < 6; j6++)
		{
			u[i6][j6] = b[j6];                    //u[i6][j6]存放第一次分好选课信息的固定班级的类型
		}
	}
	int num1 = tools[4][4];
	int** stu1 = new int* [num1];
	for (i6 = 0; i6 < num1; i6++)		stu1[i6] = new int[9];
	int y[20];
	for (i6 = 0; i6 < 20; i6++)          y[i6] = 0;
	int stunum = 0;
	int q = 0;//是否选中的标志位
	for (i6 = 0; i6 < tools[4][3]; i6++) //tools[4][3]是学生总数
	{
		q = 0;//是否选中的标志位
		int f[9];//暂存使用的学生信息
		for (j6 = 0; j6 < 9; j6++)
		{
			f[j6] = stuinform[(randnumber[i6] - 1)][j6];       //千万注意这里的stu必须是前面的stu，不能再重新生成，否则会和所求的匹配不上！！！！！！！
		}
		for (k6 = 0; k6 < 20; k6++) //遍历20种可能班
		{
			if (tools[2][k6] > 0) //如果有开班
			{
				if (y[k6] < tools[3][k6]) //还没放满
				{
					int h = 0; //比较计数位

					for (int g = 0; g < 6; g++)
					{
						if (f[g] - u[k6][g] == 0)    h = h + 1;//统计相同位个数	
					}
					if (h == 6)          //每个学生与固定班级的科目进行比较，符合的就放进去
					{
						q = 1;
						y[k6] = y[k6] + 1;
						break;
					}
				}

			}
		}
		if (q == 0)//还没被放进去的话
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
	for (i6 = 0; i6 < 20; i6++)//给r0按照课程ID编码
	{
		r[0][i6] = i6 + 15;
		r[1][i6] = 0;
		r[2][i6] = 0;
		r[3][i6] = 0;
		r[4][i6] = 0;
	}
	for (i6 = 0; i6 < stunum; i6 = i6 + 1) //统计各种选课情况的人数
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
			r[2][i6] = rsint; //开rsint个班级
			c = c + 1;//计数 开多少种固定班级
		}
	}
	int numclassnumb = 0;
	if (runsnumber_6_3 == 0)//算法第一次执行
	{
		for (i6 = 0; i6 < 20; i6++)
		{
			numclassnumb = numclassnumb + r[2][i6];//统计班级总数
		}
		maxrunsnumber_6_3 = times_6_3 * (numclassnumb + 2);
	}

	if (runsnumber_6_3 > 0)  //如果多次分班无果 每三次减少一个固定班级
	{
		int e = runsnumber_6_3 / times_6_3; //计算减少多少个固定班，每两次减少一个
		for (i6 = 0; i6 < e; i6++)
		{
			int a = 0;                //统计当前有x种开班
			for (j6 = 0; j6 < 20; j6++)
			{
				if (r[2][j6] > 0)
				{
					a = a + 1;
				}
			}
			if (a != 0) //如果还有固定班
			{
				int b = rand() % a + 1; //在目前的几种开班里选一种
				int c = 0;
				for (j6 = 0; j6 < 20; j6++) //遍历二十个班型
				{
					if (r[2][j6] > 0) //如果开班了
					{
						c = c + 1;         //计数
						if (c == b)   //判断是否是第d个班型
						{

							r[2][j6] = r[2][j6] - 1; //如果是 则减少一个固定班
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
		if ((r[2][i6]) * lu_6_3 < (r[1][i6])) r[3][i6] = (r[2][i6]) * lu_6_3;//如果人数多于开班容量上限r3更新为能选到这个课的学生
		else r[3][i6] = r[1][i6]; //都能放进去
	}

	int num1 = 0;
	int num2 = 0;
	for (i6 = 0; i6 < 20; i6++) num1 = num1 + r[3][i6];
	for (i6 = 0; i6 < 20; i6++) num2 = num2 + r[2][i6];
	r[4][1] = num1; //固定班的人数
	r[4][2] = num2; //固定班的个数
	r[4][3] = stunum;
	r[4][4] = stunum - num1;
	r[4][5] = classsum_6_3 - num2;
	cout << "当前拟定固定班数量：" << r[4][2] << endl;
	return r;

}
int getstudentnumber()
{
	Json::Reader reader;
	Json::Value root;
	Json::Value temp;
	int studentnumber_6_3;
	//从文件中读取，保证当前文件有json文件  
	ifstream in(jsonfilename, ios::binary);
	if (!in.is_open()) return 0;
	if (reader.parse(in, root))
	{

		for (i6 = 0; i6 < root.size(); i6++)//遍历每一块
		{
			if (root[i6]["key"] == "Student")//如果是Student
			{
				studentnumber_6_3 = root[i6]["value"].size();
			}
			if (root[i6]["key"] == "Class")//如果是Class 以字符串形式存储教室和班级名称 0列教室 1列班级名称
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

		for (i6 = 0; i6 < root.size(); i6++)//遍历每一块
		{
			if (root[i6]["key"] == "Student")//如果是Student
			{
				studentnumber_6_3 = root[i6]["value"].size();
			}
			if (root[i6]["key"] == "Class")//如果是Class 以字符串形式存储教室和班级名称 0列教室 1列班级名称
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
int** readFileJson(int studentnumber_6_3)//从文件中读取JSON  
{
	Json::Reader reader;
	Json::Value root;
	Json::Value temp;

	//从文件中读取，保证当前文件有json文件  
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
		for (i6 = 0; i6 < root.size(); i6++)//遍历每一块
		{
			if (root[i6]["key"] == "Student")//如果是Student
			{
				studentno_6_3 = new string * [studentnumber_6_3]; //创建学生字符串数组 0列学号 1列姓名
				for (j6 = 0; j6 < studentnumber_6_3; j6++)		studentno_6_3[j6] = new string[2];
				//读取数组信息  
				for (unsigned int j6 = 0; j6 < root[i6]["value"].size(); j6++)
				{
					//取出学号和姓名 以字符串形式存储
					int temp = root[i6]["value"][j6]["studentno_6_3"].asInt();
					stringstream s1;
					s1 << temp;
					string s11;
					s1 >> s11;
					studentno_6_3[j6][0] = s11;
					studentno_6_3[j6][1] = root[i6]["value"][j6]["name"].asString();
					//取出志愿并翻译 取出性别 学号  以整形存储
					int* p;
					string ach = root[i6]["value"][j6]["vlounteer"].asString();//取出择课志愿
					p = translate(ach);//中文转换为二进制b
					for (k6 = 0; k6 < 10; k6++)
					{
						arr[j6][k6] = p[k6];
					}
					arr[j6][6] = root[i6]["value"][j6]["studentno_6_3"].asInt();//存入学号
					arr[j6][7] = root[i6]["value"][j6]["sex"].asInt();//存入性别
					arr[j6][8] = 0;//占位 
				}
			}
			if (root[i6]["key"] == "Class")//如果是Class 以字符串形式存储教室和班级名称 0列教室 1列班级名称
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
			if (root[i6]["key"] == "Teacher_6_3")//如果是Teacher  字符串数组 0列id 1列姓名 2列 学科 3 列性别
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
					if (teacherno_6_3[j6][2] == "物理") teacher_6_3[0] = teacher_6_3[0] + 1;
					else if (teacherno_6_3[j6][2] == "化学")teacher_6_3[1] = teacher_6_3[1] + 1;
					else if (teacherno_6_3[j6][2] == "生物")teacher_6_3[2] = teacher_6_3[2] + 1;
					else if (teacherno_6_3[j6][2] == "政治")teacher_6_3[3] = teacher_6_3[3] + 1;
					else if (teacherno_6_3[j6][2] == "历史")teacher_6_3[4] = teacher_6_3[4] + 1;
					else if (teacherno_6_3[j6][2] == "地理")teacher_6_3[5] = teacher_6_3[5] + 1;
				}
			}
			if (root[i6]["key"] == "Classroom")//如果是Classroom 0 name(教室名称) 1id 2max 3 min 4type A-0 B-1 [1][5]总教室数量
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
			if (root[i6]["key"] == "Plot")//如果是Plot
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
int** readJson(int studentnumber_6_3)//从字符串中读取JSON  
{
	Json::Reader reader;
	Json::Value root;
	Json::Value temp;


	if (reader.parse(str7, root))
	{
		int** arr = new int* [studentnumber_6_3]; //创建定三分班结果列表
		for (i6 = 0; i6 < studentnumber_6_3; i6++)		 arr[i6] = new int[9];
		for (i6 = 0; i6 < root.size(); i6++)//遍历每一块
		{
			if (root[i6]["key"] == "Student")//如果是Student
			{
				studentno_6_3 = new string * [studentnumber_6_3]; //创建学生字符串数组 0列学号 1列姓名
				for (j6 = 0; j6 < studentnumber_6_3; j6++)		studentno_6_3[j6] = new string[2];
				//读取数组信息  
				for (unsigned int j6 = 0; j6 < root[i6]["value"].size(); j6++)
				{
					//取出学号和姓名 以字符串形式存储
					int temp = root[i6]["value"][j6]["studentno_6_3"].asInt();
					stringstream s1;
					s1 << temp;
					string s11;
					s1 >> s11;
					studentno_6_3[j6][0] = s11;
					studentno_6_3[j6][1] = root[i6]["value"][j6]["name"].asString();
					//取出志愿并翻译 取出性别 学号  以整形存储
					int* p;
					string ach = root[i6]["value"][j6]["vlounteer"].asString();//取出择课志愿
					p = translate(ach);//中文转换为二进制b
					for (k6 = 0; k6 < 10; k6++)
					{
						arr[j6][k6] = p[k6];
					}
					arr[j6][6] = root[i6]["value"][j6]["studentno_6_3"].asInt();//存入学号
					arr[j6][7] = root[i6]["value"][j6]["sex"].asInt();//存入性别
					arr[j6][8] = 0;//占位 用于存放班型
				}
			}
			if (root[i6]["key"] == "Class")//如果是Class 以字符串形式存储教室和班级名称 0列教室 1列班级名称
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
			if (root[i6]["key"] == "Teacher_6_3")//如果是Teacher  字符串数组 0列id 1列姓名 2列 学科 3 列性别
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
					if (teacherno_6_3[j6][2] == "物理")teacher_6_3[0] = teacher_6_3[0] + 1;
					else if (teacherno_6_3[j6][2] == "化学")teacher_6_3[1] = teacher_6_3[1] + 1;
					else if (teacherno_6_3[j6][2] == "生物")teacher_6_3[2] = teacher_6_3[2] + 1;
					else if (teacherno_6_3[j6][2] == "政治")teacher_6_3[3] = teacher_6_3[3] + 1;
					else if (teacherno_6_3[j6][2] == "历史")teacher_6_3[4] = teacher_6_3[4] + 1;
					else if (teacherno_6_3[j6][2] == "地理")teacher_6_3[5] = teacher_6_3[5] + 1;
				}
			}
			if (root[i6]["key"] == "Classroom")//如果是Classroom 0 name(教室名称) 1id 2max 3 min 4type A-0 B-1 [1][5]总教室数量
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
			if (root[i6]["key"] == "Plot")//如果是Plot
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
string writeFileJson(int** stu1out, int** stu2out, int** tools)//将信息保存为JSON格式 
{
	Json::Value jsonoutput;
	Json::Value student;
	student["key"] = Json::Value("Student");
	Json::Value value;
	for (i6 = 0; i6 < tools[4][1]; i6++)//定三输出
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
	for (i6 = 0; i6 < tools[4][4]; i6++)//定二输出
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
	for (i6 = tools[4][2]; i6 < tools[4][2] + countq_6_3; i6++)//定二和走班教室
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
			classroomvalue["subject1"] = Json::Value("无");
			classroomvalue["subject1num"] = Json::Value("无");
			classroomvalue["subject2"] = Json::Value(shu_6_3[2][i6 - tools[4][2]]);
			classroomvalue["subject2num"] = Json::Value(shu_6_3[1][i6 - tools[4][2]]);
		}
		classroom["value"].append(Json::Value(classroomvalue));
	}
	for (i6 = 0; i6 < tools[4][2]; i6++)//定三信息输出
	{

		classroomvalue["classroomno_6_3"] = Json::Value(disclass_6_3[1][i6]);
		classroomvalue["type"] = Json::Value("A");
		classroomvalue["subject1"] = Json::Value(disclass_6_3[0][i6]);
		classroomvalue["subject1num"] = Json::Value(disclass_6_3[3][i6]);
		classroomvalue["subject2"] = Json::Value("无");
		classroomvalue["subject2num"] = Json::Value("无");
		classroom["value"].append(Json::Value(classroomvalue));
	}
	jsonoutput.append(Json::Value(classroom));


	//cout << "分班结果JSON文件已经输出到工程目录下" << endl;
	//cout << "分班结果文件名为：" << endl;
	//Json::StyledWriter sw;//缩进输出
	////cout << sw.write(jsonoutput) << endl << endl;  //以字符串形式输出结果
	//time_t nowtime = time(NULL); //获取时间信息
	//struct tm* p;
	//p = gmtime(&nowtime);
	//char timeinfo[256] = { 0 };
	//sprintf(timeinfo, "%d-%d-%d`%02d`%02d.json", 1 + p->tm_mon, p->tm_mday, 8 + p->tm_hour, p->tm_min, p->tm_sec);
	//puts(timeinfo);
	Json::StyledWriter sw;
	return sw.write(jsonoutput);
	//ofstream os;	//输出到文件
	//os.open(timeinfo);
	//if (!os.is_open())
	//{
	//	cout << "CANNOT OPEN" << endl;
	//}
	//os << sw.write(jsonoutput);
	//os.close();
}
int* translate(string volunteer)   //json数据中文科目转二进制数组表示
{
	int b[6];
	for (int i6 = 0; i6 < 6; i6++) b[i6] = 0;//清空b
	string a("物化生政历史地");
	for (int i6 = 0; i6 < 6; i6 = i6 + 2)//每次检查一个，每次向后两个字符 一共三个字
	{
		size_t j6 = a.find(volunteer[i6]);//查找并返回第一次出现的位置，中文字符每个占两个字节
		switch (j6)
		{
		case 0: b[0] = 1; break;//如果是物，那b数组第一位赋1，下面类推
		case 2: b[1] = 1; break;
		case 4: b[2] = 1; break;
		case 6: b[3] = 1; break;
		case 8: b[4] = 1; break;//历史两个字的结果一样，不同学校用历、史两种方式表示这门课
		case 10: b[4] = 1; break;
		case 12: b[5] = 1; break;
		}
	}
	return b;
}
string  translate2(int* b)//将二进制科目翻译为汉字
{
	string sub1 = "物";
	string sub2 = "化";
	string sub3 = "生";
	string sub4 = "政";
	string sub5 = "史";
	string sub6 = "地";
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
	srand((int)time(0));  // 初始化随机数种子 
	for (i6 = 0; i6 < n; i6++)
	{
		ele[i6].data = rand();  // 随机生成一个数 
		ele[i6].index = i6 + 1;
	}
	qsort(ele, n, sizeof(ele[0]), cmp);  //排序 
	for (i6 = 0; i6 < n; i6++)
	{
		a[i6] = ele[i6].index;
	}
}
int cmp(const void* a, const void* b)   // 升序排序
{
	return((struct element*)a)->data - ((struct element*)b)->data;
}
