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
string str;

string returnstr73;
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

int i, j, k, ii;
int times = 2;									  //每times轮减少一个定班
int lu = 0;                                       //班级人数上限
int ld = 0;                                       //班级人数下限
int classroomlu = 0;                              //教室人数上限
int unadd = 0;                                    //普通教室数量
int add = 0;                                      //走班时增加的班级数
int classsum = 0;                                 //总班级数
int bigclassmax = 65;							  //大教室上限
int bigclassnum = 1;							  //大教室个数
const int NIND = 100;                             //种群数量
const int MAXGEN = 100;                           //遗传代数
const double px = 0.97;                           //交叉率
const double pm = 0.1;                            //变异率
const double GGAP = 0.9;                          //代沟

int complete = 0;                                 //分班完成标志位
int runsnumber = 0;                               //算法执行次数
int maxrunsnumber = 3;                            //最大算法执行次数 这里赋初值 在gettools函数里会根据走班数量自动计算重新赋值
int ** lists = new int *[2];                      //创建定三分班结果列表
int **out1 = new int *[2];                        //存定二最后输出最优结果  out1[2][PRECI]  0行放班级类型 1行放人数
string ** studentno;                              //创建学生姓名、学号记录表 用于最后输出匹配用
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
int ** disclass;//定三+定二结果
int allgocla = 0;//总走班数
int countq;
//************↓函数声明↓**********************************************
int ** gettools_7_3(int**stuinform, int stunum, int*randnumber);//获取固定班信息
int ** getstu1_7_3(int**stuinform, int **tools, int*randnumber);//获取走二学生信息
int ** getstu2_7_3(int**stuinform, int **tools, int*randnumber);//获取定三学生信息
int ** sectionstu2_7_3(int**stu2, int**tools);//定三分班，返回学生分班结果
int getstudentnumber_7_3();                   //获取学生数量，用于创建数组
int getstudentnumberfromstring_7_3();                   //在字符串中获取学生数量，用于创建数组
int ** readFileJson_7_3(int studentnumber);                    //从文件中读取JSON，一个存储了JSON格式字符串的文件
int ** readJson_7_3(int studentnumber);                    //从字符串中读取JSON
int *swit_7_3(int p, int b[]);                //p为课程ID b数组存储课程对应六位二进制编码
int * translate_7_3(string volunteer);        //把选课情况的汉字组合翻译成一行六列的二进制表示
string translate2_7_3(int * b);               //把选课情况的二进制翻译成字符串
int ** updatepopulation_7_3(int ** pop, double * objv, int gen, int PRECI, int ** out); //更新种群，包括挑选优秀个体、交叉、变异
int cmp_7_3(const void *a, const void *b);    //升序排列 
void rand_of_n_7_3(int a[], int n);           //产生 1-n 的随机排列并存到 a[] 中
double  ** ranking_7_3(int**stu1, int **tools, int ** pop);//获取适应度值
int ** genetic_7_3(int**stu1, int **tools); //遗传算法
string writeFileJson_7_3(int** stu1out, int** stu2out, int** tools);   //将信息保存为JSON格式 
void sectionclassroom_7_3(int **stu1out, int **stu2out, int**tools);   //将信息保存为JSON格式 
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
	/********从json文件读取**********/
	/******从字符串中读取  字符串str读取于txt**********/
	if (reader == 1)
	{
		str = inputstr;
		studentnumber = getstudentnumberfromstring_7_3();//在字符串中获取学生总人数
		studentinformation = readJson_7_3(studentnumber);//获取学生信息到二维数组studentinformation
	}
	else if (reader == 0)
	{
		studentnumber = getstudentnumber_7_3();//获取学生总人数
		studentinformation = readFileJson_7_3(studentnumber);//获取学生信息到二维数组studentinformation
	}
	/*******************/

	if (choose != 0)
	{
		for (int i = 0; i < 5; i++)
		{
			if (plotno[i][0] == 1) lu = plotno[i][1];//选择是否使用学校给出的教室上限
			if (plotno[i][0] == 2) ld = plotno[i][1];//选择是否使用学校给出的教室下限
		}
	}
	for (int i = 0; i < 5; i++)
	{
		if (plotno[i][0] == 4) bigclassmax = plotno[i][1];//大教室上限
		if (plotno[i][0] == 5) bigclassnum = plotno[i][1];//大教室个数
	}

	int *rand = new int[studentnumber]; //创建数组rand存放乱序序号用来打乱学生信息顺序
	rand_of_n_7_3(rand, studentnumber);
	while (complete != 1)
	{

		if (runsnumber < maxrunsnumber)//如果运行次数没到上限
		{
			cout << "正在进行分班，进行第" << runsnumber + 1 << "次尝试" << endl;
			int ** tools = gettools_7_3(studentinformation, studentnumber, rand);//获取统计过的工具数组
			int ** stu2 = getstu2_7_3(studentinformation, tools, rand);//获取定三学生信息
			int ** stu1 = getstu1_7_3(studentinformation, tools, rand);//获取定二学生信息
			int ** stu2out = sectionstu2_7_3(stu2, tools);//获取定三分班结果
			int ** stu1out = genetic_7_3(stu1, tools); //遗传算法 获取定二分班结果
			runsnumber = runsnumber + 1;//记录算法运行次数
			if (complete == 1)//如果分完了
			{
				sectionclassroom_7_3(stu1out, stu2out, tools);
				returnstr73 = writeFileJson_7_3(stu1out, stu2out, tools);
			}
		}
		else
		{
			cout << "分班失败" << endl;
			break;
		}
	}
	return returnstr73;
}
void sectionclassroom_7_3(int **stu1out, int **stu2out, int**tools)
{
	int PRECI = tools[4][5];           //获取定二班级数量

	int *classcontain = new int[PRECI];
	for (i = 0; i < PRECI; i++)
	{
		if (i < bigclassnum)classcontain[i] = bigclassmax;
		else classcontain[i] = lu;
	}
	//给每个学生分配班级,6行依次存放班级类型、班级名称、本来应该放的人数、操作过程中放了的人数、男生的人数、女生的人数。
	int **stuplus = new int *[tools[4][3]];
	for (i = 0; i < tools[4][3]; i++)		stuplus[i] = new int[10];
	for (i = 0; i < tools[4][1]; i++)//放入定三学生信息
	{
		for (j = 0; j < 10; j++) stuplus[i][j] = stu2out[i][j];
	}
	for (i = tools[4][1]; i < tools[4][3]; i++)//放入定二学生信息
	{
		for (j = 0; j < 10; j++)
		{
			stuplus[i][j] = stu1out[i - tools[4][1]][j];
		}
	}
	int stu2num = tools[4][1];//定三人数
	int ss = tools[4][2];//定三班数
	int NUM = tools[4][2] + tools[4][5];//总班级数量
	//int PRECI = tools[4][5];//定二走一班数量
	int stu1num = tools[4][4];//定二人数
	disclass = new int *[6]; //
	for (i = 0; i < 6; i++)		disclass[i] = new int[NUM];
	classname = new int[tools[4][3]];//行政班班名
	classname1 = new int *[2]; //走班班名和是否已分配
	for (i = 0; i < 2; i++)		classname1[i] = new int[tools[4][4]];
	for (i = 0; i < tools[4][4]; i++) classname1[1][i] = 0;//第二行清零 用来记录是否分配过
	for (i = 0; i < ss; i++)
	{
		disclass[0][i] = lists[0][i];//固定班型
		disclass[2][i] = lists[1][i];//固定班容量
	}
	for (i = ss; i < NUM; i++)
	{
		disclass[0][i] = out1[0][i - ss];//走班班型
		disclass[2][i] = out1[1][i - ss];//走班容量
	}
	for (j = 0; j < classroomno[1][5]; j++)
	{
		if (classroomno[j][4] == 2)    classroomno[j][4] = 0;
		else if (classroomno[j][4] == 3)    classroomno[j][4] = 1;
	}
	for (i = 0; i < NUM; i++)
	{
		int flag = 0;
		for (j = 0; j < classroomno[1][5]; j++)//无论定走 全都分配上教室
		{
			if (classroomno[j][4] == 0 && flag == 0)//普通教室
			{
				disclass[1][i] = classroomno[j][1];//教室命名 用的教室id
				classroomno[j][4] = 2;
				flag = 1;
			}
		}
		//for (int j = 0; j < classroomno[1][5]; j++)
		//{
		//	if (classroomno[j][4] == 1 && flag == 0)
		//	{
		//		disclass[1][i] = classroomno[j][1];//教室命名 用的教室id
		//		classroomno[j][4] = 3;
		//		flag = 1;
		//	}		
		//}
		disclass[3][i] = 0;//
		disclass[4][i] = 0;//男
		disclass[5][i] = 0;//女
	}


	for (i = 0; i < tools[4][3]; i++)//遍历学生 分定三 男女均分
	{
		int aaa = 1;//记录能否放进去
		int bbb = -1;//记录位置
		int ccc;//记录最小上限
		if (bigclassnum != 0)
		{
			ccc = bigclassmax;
		}
		else
		{
			ccc = lu;
		}
		for (j = 0; j < NUM; j++)//遍历所有班级
		{
			aaa = stuplus[i][9] - disclass[0][j];//9班型   班型相减
			if (aaa == 0)//如果能放进去
			{
				if (disclass[3][j] < disclass[2][j])//如果还没放满这个班级
				{
					if (stuplus[i][8] == 1)//如果男
					{
						if (disclass[4][j] < ccc)//如果最小
						{
							bbb = j;//记录位置
							ccc = disclass[4][j];//最小更新
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
		classname[i] = disclass[1][bbb];//记录这个学生分配到了哪个教室，视为信息表第十列
		if (stuplus[i][8] == 1)
		{
			disclass[4][bbb] = disclass[4][bbb] + 1;//判断性别 
		}
		else
		{
			disclass[5][bbb] = disclass[5][bbb] + 1;//
		}
		disclass[3][bbb] = disclass[4][bbb] + disclass[5][bbb];
	}


	int ** goone = new int *[9]; //创建走二各班学科统计列表
	for (i = 0; i < 9; i++)		goone[i] = new int[PRECI];//0 班型 1班级id 2物理3化学 4生物 5政治 6历史 7地理
	for (i = ss; i < NUM; i++)
	{
		goone[0][i - ss] = disclass[0][i];//班型 摘出定二
		goone[1][i - ss] = disclass[1][i];//班级名
	}
	for (i = 2; i < 9; i++) //清零
	{
		for (j = 0; j < PRECI; j++)
		{
			goone[i][j] = 0;
		}
	}
	for (i = 0; i < stu1num; i++)//遍历学生
	{
		int ddd = 1;
		for (j = 0; j < PRECI; j++)//遍历班班级
		{
			ddd = goone[1][j] - classname[i + tools[4][1]];//如果这学生是这个班的
			if (ddd == 0)
			{
				for (k = 0; k < 7; k++)
				{
					goone[k + 2][j] = goone[k + 2][j] + stuplus[i + tools[4][1]][k];//统计学生科目 
				}
				break;
			}
		}
	}

	for (i = 2; i < 9; i++)//清零定二班的固定科目
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





	int gocla[7];//各科走班数
	//cout << "提示：科目0-物理 1-化学 2-生物 3-政治 4-历史 5-地理"<< endl;
	int subjecttotal[7] = { 0,0,0,0,0,0,0 };
	for (i = 0; i < 7; i++)
	{

		for (int j = 0; j < PRECI; j++)
		{
			subjecttotal[i] = subjecttotal[i] + goone[i + 2][j];
		}
		gocla[i] = ceil(subjecttotal[i] / (lu*1.0));
		string subtemp;
		if (i == 0) subtemp = "物";
		else if (i == 1) subtemp = "化";
		else if (i == 2) subtemp = "生";
		else if (i == 3) subtemp = "政";
		else if (i == 4) subtemp = "史";
		else if (i == 5) subtemp = "地";
		else if (i == 6) subtemp = "信息";

		cout << "科目 " << subtemp << " 拟走班人数为" << subjecttotal[i] << "   共开班" << gocla[i] << "个" << endl;
		allgocla = allgocla + gocla[i];
	}

	cout << "总拟走班数为：" << allgocla << endl;

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










	//走班分配教室部分	
	int * all = new int[7 * PRECI];//存放各班走科排序
	for (i = 0; i < 7; i++)
	{
		for (j = 0; j < PRECI; j++)
		{
			all[i*PRECI + j] = goone[i + 2][j];//所有走科导入all
		}
	}
	int tempa;//排序
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
	}//all排序完成
	shu = new int *[3]; //存放第一行 班号 第二行  是否开班0未开 1 开  第三行 开了什么班
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
					shu[0][i] = classroomno[j][1];//教室命名 用的教室id
					classroomno[j][4] = 3;
					flag2 = 1;
				}
			}
		}
	}

	int gocla1[7] = { 0,0,0,0,0,0,0 };//计数已经开了什么班
	int * gocla2 = new int[PRECI];
	for (i = 0; i < PRECI; i++)
	{
		gocla2[i] = 1;
	}
	int ggg = -1, hhh = -1, js = 0, tt;
	for (int qr = 0; qr < 7 * PRECI; qr++)//遍历all
	{
		ggg = -1;
		hhh = -1;
		int flag1 = 0;
		for (i = 0; i < 7; i++)//遍历goone
		{
			for (j = 0; j < PRECI; j++)
			{
				if (gocla2[j] == 1)//定二班还没分配
				{
					tt = goone[i + 2][j] - all[qr];//核对是否是最合适的班级
					if (tt == 0 && gocla[i] - gocla1[i] != 0)
					{
						ggg = i; hhh = j;//记录行 列
						flag1 = 1;
						break;
					}
				}
			}
			if (flag1 == 1) { break; }
		}
		if (gocla[ggg] - gocla1[ggg] != 0 && ggg != -1)//如果还没开满
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

	if (countq - PRECI > 0)//如果有add
	{
		for (i = 0; i < countq - PRECI; i++)//遍历add
		{
			for (j = 0; j < 7; j++)//遍历六个学科
			{
				if (gocla[j] - gocla1[j] != 0)//如过有某科目没开完
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
		shu[1][j] = 0;//清零 用来计数
	}
	for (i = 0; i < stu1num; i++)
	{
		int classsubj = 7;//教室科目
		int stusubj = 6;//学生科目
		int classsubjno = -1;
		for (j = 0; j < PRECI; j++)
		{
			if (classname[stu2num + i] == shu[0][j])
			{
				classsubj = shu[2][j];//该生原教室的走班课
				classsubjno = j;
			}
		}
		int b[7];
		swit_7_3(stuplus[stu2num + i][9], b);
		for (j = 0; j < 7; j++)
		{
			if (stuplus[stu2num + i][j] - b[j] == 1) stusubj = j;//该生需要走的课
		}
		if (stusubj == classsubj)//如果原班可以放
		{
			classname1[0][i] = classname[stu2num + i];//放到原班级
			classname1[1][i] = 1;
			shu[1][classsubjno] = shu[1][classsubjno] + 1;//计数
		}
	}
	for (i = 0; i < stu1num; i++)//遍历所有定二学生
	{
		if (classname1[1][i] == 0)//如果这个学生还没放置
		{
			int aaa = 1;//记录能否放进去
			int bbb = -1;//记录位置
			int ccc;
			if (bigclassnum != 0)
			{
				ccc = bigclassmax;
			}
			else
			{
				ccc = lu;
			}
			int stusubj = 7;//学生科目
			int b[7];
			swit_7_3(stuplus[stu2num + i][9], b);
			for (j = 0; j < 7; j++)
			{
				if (stuplus[stu2num + i][j] - b[j] == 1) stusubj = j;//该生需要走的课
			}
			for (j = 0; j < countq; j++)
			{
				aaa = stusubj - shu[2][j];//   班型相减
				if (aaa == 0)//如果能放进去
				{
					if (shu[1][j] < classcontain1[j])//如果还没放满这个班级**************************
					{
						if (shu[1][j] < ccc)//如果最小
						{
							bbb = j;//记录位置
							ccc = shu[1][j];//最小更新
						}
					}
				}
			}
			classname1[0][i] = shu[0][bbb];//记录这个学生分配到了哪个教室
			classname1[1][i] = 1;
			shu[1][bbb] = shu[1][bbb] + 1;//计数
		}
	}
	cout << "----------------------------------------------------------------" << endl;
	for (i = 0; i < 3; i++)/************************************************************/
	{
		if (i == 0) cout << " 走一教室:  ";
		else if (i == 1) cout << " 班级人数： ";
		else if (i == 2) cout << " 开班类型： ";
		for (j = 0; j < countq; j++)
		{
			cout.width(3);
			if (i < 2) cout << shu[i][j] << "  ";
			else if (i == 2)
			{
				if (shu[i][j] == 0) { cout.width(3); cout << "物   "; }
				else if (shu[i][j] == 1) { cout.width(3); cout << "化   "; }
				else if (shu[i][j] == 2) { cout.width(3); cout << "生   "; }
				else if (shu[i][j] == 3) { cout.width(3); cout << "政   "; }
				else if (shu[i][j] == 4) { cout.width(3); cout << "史   "; }
				else if (shu[i][j] == 5) { cout.width(3); cout << "地   "; }
				else if (shu[i][j] == 6) { cout.width(3); cout << "信息   "; }
			}
		}
		cout << " \n";
	}
	cout << endl;

}
int **  genetic_7_3(int**stu1, int **tools)
{
	int gen = 0;                      //遗传代数计数器
	int stu1numb = tools[4][4];       //获取定二学生数量
	int PRECI = tools[4][5];           //获取定二班级数量

	int **pop = new int *[NIND];      //pop为生成种群 pop[NIND][tools[4][5]]
	for (i = 0; i < NIND; i++)		pop[i] = new int[PRECI];


	for (i = 0; i < 2; i++)		    out1[i] = new int[PRECI];

	double **trace = new double *[2];     //存放历代最佳分班方式 trace[2][MAXGEN]用于生成曲线
	for (i = 0; i < 2; i++)		trace[i] = new double[MAXGEN];

	double *objv = new double[NIND];  //适应度值

	double globalminobjv = 0.0; //记录全局最小适应度值

	int *stufinalclass = new int[stu1numb];  //用于记录学生最终选择

	int **stu1out = new int *[stu1numb];        //存放走一班学生选课信息及分班结果
	for (i = 0; i < stu1numb; i++)		    stu1out[i] = new int[10];

	for (i = 0; i < NIND; i++)       //随机生成初始种群
	{
		for (j = 0; j < PRECI; j++)
		{
			int randompop = rand();
			pop[i][j] = randompop % 21;           //生成0-20的随机数，表示生成的随机定二走一班级类型
		}
	}

	while (gen < MAXGEN)                    //
	{

		double ** tools2 = ranking_7_3(stu1, tools, pop);     //获取适应度值，并返回单词最优各学生分班去向以及各班人数

		for (int i = 0; i < NIND; i++)
		{
			double tempobjv = tools2[i][2];
			objv[i] = tempobjv;
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
				for (i = 0; i < stu1numb; i++)
				{
					stufinalclass[i] = tools2[i][0];   //记录最优解学生班级归属
				}
				for (i = 0; i < PRECI; i++)
				{
					out1[0][i] = pop[minpos][i];       //全局最优个体id
					out1[1][i] = tools2[i][1];         //全局最优个体各班学生数量
				}
			}
		}
		else//如果是第0代 则记录0代最优解
		{
			globalminobjv = minobjv;             //记录全局最优适应度值
			for (i = 0; i < stu1numb; i++)
			{
				stufinalclass[i] = tools2[i][0];    //记录最优解学生班级归属
			}
			for (i = 0; i < PRECI; i++)
			{
				out1[0][i] = pop[minpos][i];      //全局最优个体id
				out1[1][i] = tools2[i][1];      //全局最优个体各班学生数量
			}
		}

		pop = updatepopulation_7_3(pop, objv, gen, PRECI, out1);//选择交叉变异

		gen = gen + 1;
	}


	if (globalminobjv < PRECI * 10)//判断适应度值是否达标
	{
		complete = 1;   // 如果适应度值较小（代表成功分班），则标志分班完成
		cout << "----------------------------------------------------------------" << endl;
		cout << "最小适应度值：" << globalminobjv << endl;

		for (i = 0; i < 2; i++)
		{
			if (i == 0) cout << "定三班级类型：";
			else cout << "定三班级人数：";
			for (int j = 0; j < tools[4][2]; j++)
			{
				cout.width(3);
				cout << lists[i][j] << ' ';
			}
			cout << '\n' << endl;
		}

		for (i = 0; i < 2; i++)
		{
			if (i == 0) cout << "走一班级类型：";
			else cout << "走一班级人数：";
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
		if (stu1numb - zongrenshu == 0) 	cout << "所有同学均已分班完成" << endl;
		else cout << "仍有同学未成功分配班级" << endl;
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

	double *objv = new double[NIND];  //适应度值

	int stu1numb = tools[4][4];       //获取定二学生数量
	int PRECI = tools[4][5];           //获取定二班级数量


	int *classcontain = new int[PRECI];
	for (i = 0; i < PRECI; i++)
	{
		if (i < bigclassnum)classcontain[i] = bigclassmax;
		else classcontain[i] = lu;
	}
	int total[7];                     //用于计算剩余未选科目人数
	int total1[7];                    //统计已经放入科目的人数
	int total2[7];                    //对stu11进行按列相加,统计定二班各科总人数

	int **class1 = new int *[stu1numb];      //放每个生成的定二走一班级人数 num[NIND][tools[4][5]]
	for (i = 0; i < stu1numb; i++)		class1[i] = new int[NIND];

	int **num = new int *[NIND];      //放每个生成的定二走一班级人数 num[NIND][tools[4][5]]
	for (i = 0; i < NIND; i++)		num[i] = new int[PRECI];

	int tools2line = stu1numb + NIND;
	double ** tools2 = new double*[tools2line];  //用于记录学生最终选择
	for (i = 0; i < tools2line; i++)		tools2[i] = new double[3];

	for (i = 0; i < 7; i++)//清零
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




	for (i = 0; i < NIND; i++)         //计算种群每一个个体（每一种班级组合）
	{
		for (j = 0; j < 7; j++)//清零
		{
			total[j] = 0;
			total1[j] = 0;
			total2[j] = 0;
		}
		for (j = 0; j < 7; j++) //统计定二班各科总人数
		{
			for (k = 0; k < stu1numb; k++)
			{
				total2[j] = stu1[k][j] + total2[j];//存放stu11按列相加 统计各科数量吧？
			}
		}
		for (k = 0; k < stu1numb; k++)     //遍历定二所有学生   
		{
			int e = -1;                  //用于寄存符合条件的班级序号（用于判断是否放进了班级）
			int f = 0;                   //用于寄存符合条件的班级中人数最少的班级学生数量（优先放入）
			if (bigclassnum > 0) f = bigclassmax;
			else f = lu;


			for (j = 0; j < PRECI; j++)    //遍历每个定二走一班级      
			{

				int b[7];
				swit_7_3(pop[i][j], b);      //翻译出第i行第j个班级
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
					if (num[i][j] < classcontain[j]) //每次都放到人数最少的班级
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
				num[i][e] = num[i][e] + 1; //种群中某染色体计数+1
				class1[k][i] = pop[i][e];//记录学生被分到了什么班级
			}
		}

		/*int **stu1outtemp = new int *[stu1numb];      //放每个生成的定二走一班级人数 num[NIND][tools[4][5]]
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


		//给每个学生分配班级,6行依次存放班级类型、班级名称、本来应该放的人数、操作过程中放了的人数、男生的人数、女生的人数。
		int **stuplus = new int *[tools[4][3]];
		for (ii = 0; ii < tools[4][3]; ii++)		stuplus[ii] = new int[10];

		for (ii = tools[4][1]; ii < tools[4][3]; ii++)//放入定二学生信息
		{
			for (j = 0; j < 9; j++)
			{
				stuplus[ii][j] = stu1[ii - tools[4][1]][j];
			}
			stuplus[ii][9] = class1[ii - tools[4][1]][i];
		}




		//int stu2num = tools[4][1];//定三人数
		int ss = tools[4][2];//定三班数
		int NUM = tools[4][2] + tools[4][5];//总班级数量
		int stu1num = tools[4][4];//定二人数
		disclass = new int *[6]; //
		for (ii = 0; ii < 6; ii++)		disclass[ii] = new int[NUM];
		classname = new int[tools[4][3]];//行政班班名
		for (ii = 0; ii < ss; ii++)
		{
			disclass[0][ii] = lists[0][ii];//固定班型
			disclass[2][ii] = lists[1][ii];//固定班容量
		}
		for (j = ss; j < NUM; j++)
		{
			disclass[0][j] = pop[i][j - ss];//走班班型
			disclass[2][j] = num[i][j - ss];//走班容量
		}
		for (j = 0; j < classroomno[1][5]; j++)
		{
			if (classroomno[j][4] == 2)    classroomno[j][4] = 0;
			else if (classroomno[j][4] == 3)    classroomno[j][4] = 1;
		}
		for (ii = 0; ii < NUM; ii++)
		{
			int flag = 0;
			for (j = 0; j < classroomno[1][5]; j++)//无论定走 全都分配上教室
			{
				if (classroomno[j][4] == 0 && flag == 0)//普通教室
				{
					disclass[1][ii] = classroomno[j][1];//教室命名 用的教室id
					classroomno[j][4] = 2;
					flag = 1;
				}
			}

			disclass[3][ii] = 0;//
			disclass[4][ii] = 0;//男
			disclass[5][ii] = 0;//女
		}
		for (ii = tools[4][1]; ii < tools[4][3]; ii++)//遍历学生 分定三 男女均分
		{
			int aaa = 1;//记录能否放进去
			int bbb = -1;//记录位置
			int ccc = lu;//记录最小上限
			for (j = 0; j < NUM; j++)//遍历所有班级
			{
				aaa = stuplus[ii][9] - disclass[0][j];//8班型   班型相减
				if (aaa == 0)//如果能放进去
				{
					if (disclass[3][j] < disclass[2][j])//如果还没放满这个班级
					{
						if (stuplus[ii][8] == 1)//如果男
						{
							if (disclass[4][j] < ccc)//如果最小
							{
								bbb = j;//记录位置
								ccc = disclass[4][j];//最小更新
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
			classname[ii] = disclass[1][bbb];//记录这个学生分配到了哪个教室，视为信息表第十列
			if (stuplus[ii][7] == 1)
			{
				disclass[4][bbb] = disclass[4][bbb] + 1;//判断性别 
			}
			else
			{
				disclass[5][bbb] = disclass[5][bbb] + 1;//
			}
			disclass[3][bbb] = disclass[4][bbb] + disclass[5][bbb];
		}


		int ** goone = new int *[9]; //创建走二各班学科统计列表
		for (ii = 0; ii < 9; ii++)		goone[ii] = new int[PRECI];//0 班型 1班级id 2物理3化学 4生物 5政治 6历史 7地理  8信息科技
		for (ii = 0; ii < 9; ii++)
		{
			for (j = 0; j < PRECI; j++)
			{
				goone[ii][j] = 0;
			}
		}
		int ** goone1 = new int *[9]; //创建走二各班学科统计列表
		for (ii = 0; ii < 9; ii++)		goone1[ii] = new int[PRECI];//0 班型 1班级id 2物理3化学 4生物 5政治 6历史 7地理  8信息科技
		for (ii = ss; ii < NUM; ii++)
		{
			goone[0][ii - ss] = disclass[0][ii];//班型 摘出定二
			goone[1][ii - ss] = disclass[1][ii];//班级名
		}
		for (ii = 0; ii < stu1num; ii++)//遍历学生
		{
			int ddd = 1;
			for (j = 0; j < PRECI; j++)//遍历班班级
			{
				ddd = goone[1][j] - classname[ii + tools[4][1]];//如果这学生是这个班的
				if (ddd == 0)
				{
					for (k = 0; k < 7; k++)
					{
						goone[k + 2][j] = goone[k + 2][j] + stuplus[ii + tools[4][1]][k];//统计学生科目 
					}
					break;
				}
			}
		}

		for (ii = 2; ii < 9; ii++)//清零定二班的固定科目
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
				total1[k] = total1[k] + num[i][j] * b[k]; //放进去了的各科目人数？
			}
		}
		for (j = 0; j < 7; j++)
		{
			total[j] = total2[j] - total1[j];//还剩下没放进去的各科人数、
			//cout << total[j] << " " << total2[j] << " " << total1[j] << endl;
		}
		int meansum = 0;                   //已放入班级的总人数
		int d1 = 0;                       //没放进去的人数


		for (j = 0; j < PRECI; j++)//求放进去的总人数
		{
			meansum = meansum + num[i][j];
		}
		d1 = stu1numb - meansum;
		float mean = meansum / (PRECI*1.0);//平均数

		float sum1 = 0.0;
		for (j = 0; j < PRECI; j++)
		{
			sum1 = (num[i][j] - mean)*(num[i][j] - mean)*1.0 + sum1;
		}
		float s1 = sum1 / (PRECI*1.0);   //方差
		int d2 = 0;                         //用于判断是否人数过少
		for (j = 0; j < PRECI; j++)     //如果人数不够最低限度 惩罚
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

			int d5 = 0;//用于判断定二班级走一类型是否少
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
		tools2[i][2] = objv[i]; //tools2[i][2]存入本次适应度值
	}
	int minpos = (min_element(objv, objv + NIND) - objv);          //单次最小值的位置 

	for (i = 0; i < stu1numb; i++)
	{
		tools2[i][0] = class1[i][minpos];// tools2[i][0]存入本次最优学生班级归属
	}
	for (i = 0; i < PRECI; i++)
	{
		tools2[i][1] = num[minpos][i];// tools2[i][1]存入本次最优各班学生数量
	}
	return tools2;
}
int ** updatepopulation_7_3(int ** pop, double * objv, int gen, int PRECI, int ** out)
{
	int **popnext = new int *[NIND];      //popnext为更新后种群 popnext[NIND][tools[4][5]]
	for (i = 0; i < NIND; i++)		popnext[i] = new int[PRECI];

	for (i = 0; i < NIND; i++)
	{
		for (j = 0; j < PRECI; j++)
		{
			popnext[i][j] = pop[i][j];
		}
	}

	int *temp0 = new int[PRECI];
	for (i = 0; i < NIND; i++)                 // 根据个体适应度来排序；（冒泡法）
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

	for (i = NIND * GGAP; i < NIND; i++)       //按照代沟保留优势个体
	{
		for (j = 0; j < PRECI; j++)
		{

			popnext[i][j] = popnext[NIND - i - 1][j];
		}
	}



	int *temp1 = new int[PRECI];
	for (i = 0; i < (NIND / 2); i++)
	{
		double random1 = (rand() % 10) / 10.0;  //产生0-1的随机小数,用来判断是否交叉
		if (random1 >= (1.0 - px))
		{
			int random2 = rand() % PRECI;                     // 随机生成交叉位置，交叉点控制在0到PRECI之间；
			for (j = random2; j < PRECI; j++)
			{
				temp1[j] = popnext[i * 2 + 1][j];
				popnext[i * 2 + 1][j] = popnext[i * 2][j];
				popnext[i * 2][j] = temp1[j];
			}
		}
	}

	for (i = 0; i<int(NIND*PRECI*pm); i++)                             //变异
	{
		int col = rand() % PRECI;                            // 随机产生要变异的基因位号；
		int row = rand() % NIND;                             // 随机产生要变异的染色体号；
		popnext[row][col] = rand() % 21;                  //在0-20之间随机变换一种
	}
	for (i = 0; i < PRECI; i++)                         //把全局最优插入
	{
		popnext[(NIND - 1)][i] = out[0][i];
	}


	return popnext;

}
int ** sectionstu2_7_3(int**stu2, int**tools)
{
	int num = tools[4][2];//定三班个数
	int ** stu2out = new int *[tools[4][1]]; //创建定三分班结果列表
	for (i = 0; i < tools[4][1]; i++)		stu2out[i] = new int[10];

	for (i = 0; i < 2; i++)		lists[i] = new int[num];
	int knum = 0; //初始化list计数器
	for (i = 0; i < 35; i++)//遍历二十种班型
	{
		if (tools[2][i] > 0)//如果开班
		{

			for (j = 0; j < tools[2][i]; j++)//开x个班
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
		int e = -1;                  //用于寄存符合条件的班级序号（用于判断是否放进了班级）
		int f = lu;                  //用于寄存符合条件的班级中人数最少的班级学生数量（优先放入）

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
	int u[35][7];//班级编码比较模板
	for (i = 0; i < 35; i++)
	{
		int b[7];
		swit_7_3(tools[0][i], b);
		for (j = 0; j < 7; j++)
		{
			u[i][j] = b[j];                    //u[i][j]存放第一次分好选课信息的固定班级的类型
		}
	}

	int num2 = tools[4][1];//定三人数
	int **stu2 = new int *[num2];
	for (i = 0; i < num2; i++)		stu2[i] = new int[10];
	int y[35];
	int stu2num = 0;
	int stu2num2 = 0;
	for (i = 0; i < 35; i++)          y[i] = 0;
	for (i = 0; i < tools[4][3]; i++) //tools[4][3]是学生总数
	{
		int f[10];//暂存使用的学生信息
		for (j = 0; j < 10; j++)
		{
			f[j] = stuinform[(randnumber[i] - 1)][j];       //千万注意这里的stu必须是前面的stu，不能再重新生成，否则会和所求的匹配不上！！！！！！！
		}
		for (k = 0; k < 35; k++) //遍历20种可能班
		{
			if (tools[2][k] > 0) //如果有开班
			{
				if (y[k] < tools[3][k]) //还没放满
				{
					int h = 0; //比较计数位

					for (int g = 0; g < 7; g++)
					{
						if (f[g] - u[k][g] == 0)    h = h + 1;//统计相同位个数	
					}
					if (h == 7)          //每个学生与固定班级的科目进行比较，符合的就放进去
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
	int u[35][7];//班级编码比较模板
	for (i = 0; i < 35; i++)
	{
		int b[7];
		swit_7_3(tools[0][i], b);
		for (j = 0; j < 7; j++)
		{
			u[i][j] = b[j];                    //u[i][j]存放第一次分好选课信息的固定班级的类型
		}
	}
	int num1 = tools[4][4];
	int **stu1 = new int *[num1];
	for (i = 0; i < num1; i++)		stu1[i] = new int[10];
	int y[35];
	for (i = 0; i < 35; i++)          y[i] = 0;
	int stunum = 0;
	int q = 0;//是否选中的标志位
	for (i = 0; i < tools[4][3]; i++) //tools[4][3]是学生总数
	{
		q = 0;//是否选中的标志位
		int f[10];//暂存使用的学生信息
		for (j = 0; j < 10; j++)
		{
			f[j] = stuinform[(randnumber[i] - 1)][j];       //千万注意这里的stu必须是前面的stu，不能再重新生成，否则会和所求的匹配不上！！！！！！！
		}
		for (k = 0; k < 35; k++) //遍历20种可能班
		{
			if (tools[2][k] > 0) //如果有开班
			{
				if (y[k] < tools[3][k]) //还没放满
				{
					int h = 0; //比较计数位

					for (int g = 0; g < 7; g++)
					{
						if (f[g] - u[k][g] == 0)    h = h + 1;//统计相同位个数	
					}
					if (h == 7)          //每个学生与固定班级的科目进行比较，符合的就放进去
					{
						q = 1;
						y[k] = y[k] + 1;
						break;
					}
				}

			}
		}
		if (q == 0)//还没被放进去的话
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
	for (i = 0; i < 35; i++)//给r0按照课程ID编码
	{
		r[0][i] = i + 21;
		r[1][i] = 0;
		r[2][i] = 0;
		r[3][i] = 0;
		r[4][i] = 0;
	}
	for (i = 0; i < stunum; i = i + 1) //统计各种选课情况的人数
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
			r[2][i] = rsint; //开rsint个班级
			c = c + 1;//计数 开多少种固定班级
		}
	}
	int numclassnumb = 0;
	if (runsnumber == 0)//算法第一次执行
	{
		for (i = 0; i < 35; i++)
		{
			numclassnumb = numclassnumb + r[2][i];//统计班级总数
		}
		maxrunsnumber = times * (numclassnumb + 2);
	}

	if (runsnumber > 0)  //如果多次分班无果 每三次减少一个固定班级
	{
		int e = runsnumber / times; //计算减少多少个固定班，每两次减少一个
		for (i = 0; i < e; i++)
		{
			int a = 0;                //统计当前有x种开班
			for (j = 0; j < 35; j++)
			{
				if (r[2][j] > 0)
				{
					a = a + 1;
				}
			}
			if (a != 0) //如果还有固定班
			{
				int b = rand() % a + 1; //在目前的几种开班里选一种
				int c = 0;
				for (j = 0; j < 35; j++) //遍历二十个班型
				{
					if (r[2][j] > 0) //如果开班了
					{
						c = c + 1;         //计数
						if (c == b)   //判断是否是第d个班型
						{

							r[2][j] = r[2][j] - 1; //如果是 则减少一个固定班
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
		if ((r[2][i])*lu < (r[1][i])) r[3][i] = (r[2][i])*lu;//如果人数多于开班容量上限r3更新为能选到这个课的学生
		else r[3][i] = r[1][i]; //都能放进去
	}

	int num1 = 0;
	int num2 = 0;
	for (i = 0; i < 35; i++) num1 = num1 + r[3][i];
	for (i = 0; i < 35; i++) num2 = num2 + r[2][i];
	r[4][1] = num1; //固定班的人数
	r[4][2] = num2; //固定班的个数
	r[4][3] = stunum;
	r[4][4] = stunum - num1;
	r[4][5] = classsum - num2;
	cout << "当前拟定固定班数量：" << r[4][2] << endl;
	return r;

}
int getstudentnumber_7_3()
{
	Json::Reader reader;
	Json::Value root;
	Json::Value temp;
	int studentnumber;
	//从文件中读取，保证当前文件有json文件  
	ifstream in(jsonfilename, ios::binary);
	if (!in.is_open()) return 0;
	if (reader.parse(in, root))
	{

		for (i = 0; i < root.size(); i++)//遍历每一块
		{
			if (root[i]["key"] == "Student")//如果是Student
			{
				studentnumber = root[i]["value"].size();
			}
			if (root[i]["key"] == "Class")//如果是Class 以字符串形式存储教室和班级名称 0列教室 1列班级名称
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

		for (i = 0; i < root.size(); i++)//遍历每一块
		{
			if (root[i]["key"] == "Student")//如果是Student
			{
				studentnumber = root[i]["value"].size();
			}
			if (root[i]["key"] == "Class")//如果是Class 以字符串形式存储教室和班级名称 0列教室 1列班级名称
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
int ** readFileJson_7_3(int studentnumber)//从文件中读取JSON  
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
		int ** arr = new int *[studentnumber];
		for (i = 0; i < studentnumber; i++)		 arr[i] = new int[10];
		for (i = 0; i < root.size(); i++)//遍历每一块
		{
			if (root[i]["key"] == "Student")//如果是Student
			{
				studentno = new string *[studentnumber]; //创建学生字符串数组 0列学号 1列姓名
				for (j = 0; j < studentnumber; j++)		studentno[j] = new string[2];
				//读取数组信息  
				for (unsigned int j = 0; j < root[i]["value"].size(); j++)
				{
					//取出学号和姓名 以字符串形式存储
					int temp = root[i]["value"][j]["studentno"].asInt();
					stringstream s1;
					s1 << temp;
					string s11;
					s1 >> s11;
					studentno[j][0] = s11;
					studentno[j][1] = root[i]["value"][j]["name"].asString();
					//取出志愿并翻译 取出性别 学号  以整形存储
					int *p;
					string ach = root[i]["value"][j]["vlounteer"].asString();//取出择课志愿
					p = translate_7_3(ach);//中文转换为二进制b
					for (k = 0; k < 7; k++)
					{
						arr[j][k] = p[k];
					}
					arr[j][7] = root[i]["value"][j]["studentno"].asInt();//存入学号
					arr[j][8] = root[i]["value"][j]["sex"].asInt();//存入性别
					arr[j][9] = 0;//占位 
				}
			}
			if (root[i]["key"] == "Class")//如果是Class 以字符串形式存储教室和班级名称 0列教室 1列班级名称
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
			if (root[i]["key"] == "Teacher")//如果是Teacher  字符串数组 0列id 1列姓名 2列 学科 3 列性别
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
					if (teacherno[j][2] == "物理") teacher[0] = teacher[0] + 1;
					else if (teacherno[j][2] == "化学")teacher[1] = teacher[1] + 1;
					else if (teacherno[j][2] == "生物")teacher[2] = teacher[2] + 1;
					else if (teacherno[j][2] == "政治")teacher[3] = teacher[3] + 1;
					else if (teacherno[j][2] == "历史")teacher[4] = teacher[4] + 1;
					else if (teacherno[j][2] == "地理")teacher[5] = teacher[5] + 1;
					else if (teacherno[j][2] == "信息科技")teacher[6] = teacher[6] + 1;
				}
			}
			if (root[i]["key"] == "Classroom")//如果是Classroom 0 name(教室名称) 1id 2max 3 min 4type A-0 B-1 [1][5]总教室数量
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
			if (root[i]["key"] == "Plot")//如果是Plot
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
int ** readJson_7_3(int studentnumber)//从字符串中读取JSON  
{
	Json::Reader reader;
	Json::Value root;
	Json::Value temp;


	if (reader.parse(str, root))
	{
		int ** arr = new int *[studentnumber]; //创建定三分班结果列表
		for (i = 0; i < studentnumber; i++)		 arr[i] = new int[10];
		for (i = 0; i < root.size(); i++)//遍历每一块
		{
			if (root[i]["key"] == "Student")//如果是Student
			{
				studentno = new string *[studentnumber]; //创建学生字符串数组 0列学号 1列姓名
				for (j = 0; j < studentnumber; j++)		studentno[j] = new string[2];
				//读取数组信息  
				for (unsigned int j = 0; j < root[i]["value"].size(); j++)
				{
					//取出学号和姓名 以字符串形式存储
					int temp = root[i]["value"][j]["studentno"].asInt();
					stringstream s1;
					s1 << temp;
					string s11;
					s1 >> s11;
					studentno[j][0] = s11;
					studentno[j][1] = root[i]["value"][j]["name"].asString();
					//取出志愿并翻译 取出性别 学号  以整形存储
					int *p;
					string ach = root[i]["value"][j]["vlounteer"].asString();//取出择课志愿
					p = translate_7_3(ach);//中文转换为二进制b
					for (k = 0; k < 7; k++)
					{
						arr[j][k] = p[k];
					}
					arr[j][7] = root[i]["value"][j]["studentno"].asInt();//存入学号
					arr[j][8] = root[i]["value"][j]["sex"].asInt();//存入性别
					arr[j][9] = 0;//占位 用于存放班型
				}
			}
			if (root[i]["key"] == "Class")//如果是Class 以字符串形式存储教室和班级名称 0列教室 1列班级名称
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
			if (root[i]["key"] == "Teacher")//如果是Teacher  字符串数组 0列id 1列姓名 2列 学科 3 列性别
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
					if (teacherno[j][2] == "物理") teacher[0] = teacher[0] + 1;
					else if (teacherno[j][2] == "化学")teacher[1] = teacher[1] + 1;
					else if (teacherno[j][2] == "生物")teacher[2] = teacher[2] + 1;
					else if (teacherno[j][2] == "政治")teacher[3] = teacher[3] + 1;
					else if (teacherno[j][2] == "历史")teacher[4] = teacher[4] + 1;
					else if (teacherno[j][2] == "地理")teacher[5] = teacher[5] + 1;
					else if (teacherno[j][2] == "信息科技")teacher[6] = teacher[6] + 1;
				}
			}
			if (root[i]["key"] == "Classroom")//如果是Classroom 0 name(教室名称) 1id 2max 3 min 4type A-0 B-1 [1][5]总教室数量
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
			if (root[i]["key"] == "Plot")//如果是Plot
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
string writeFileJson_7_3(int** stu1out, int** stu2out, int** tools)//将信息保存为JSON格式 
{
	Json::Value jsonoutput;
	Json::Value student;
	student["key"] = Json::Value("Student");
	Json::Value value;
	for (i = 0; i < tools[4][1]; i++)//定三输出
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
	for (i = 0; i < tools[4][4]; i++)//定二输出
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
	for (i = tools[4][2]; i < tools[4][2] + countq; i++)//定二和走班教室
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
			classroomvalue["subject1"] = Json::Value("无");
			classroomvalue["subject1num"] = Json::Value("无");
			classroomvalue["subject2"] = Json::Value(shu[2][i - tools[4][2]]);
			classroomvalue["subject2num"] = Json::Value(shu[1][i - tools[4][2]]);
		}
		classroom["value"].append(Json::Value(classroomvalue));
	}
	for (i = 0; i < tools[4][2]; i++)//定三信息输出
	{

		classroomvalue["classroomno"] = Json::Value(disclass[1][i]);
		classroomvalue["type"] = Json::Value("A");
		classroomvalue["subject1"] = Json::Value(disclass[0][i]);
		classroomvalue["subject1num"] = Json::Value(disclass[3][i]);
		classroomvalue["subject2"] = Json::Value("无");
		classroomvalue["subject2num"] = Json::Value("无");
		classroom["value"].append(Json::Value(classroomvalue));
	}
	jsonoutput.append(Json::Value(classroom));


	Json::StyledWriter sw;
	return sw.write(jsonoutput);
}
int *translate_7_3(string volunteer)   //json数据中文科目转二进制数组表示
{
	int b[7];
	for (int i = 0; i < 7; i++) b[i] = 0;//清空b
	string a("物化生政历史地信");
	for (int i = 0; i < 7; i = i + 2)//每次检查一个，每次向后两个字符 一共三个字
	{
		size_t j = a.find(volunteer[i]);//查找并返回第一次出现的位置，中文字符每个占两个字节
		switch (j)
		{
		case 0: b[0] = 1; break;//如果是物，那b数组第一位赋1，下面类推
		case 2: b[1] = 1; break;
		case 4: b[2] = 1; break;
		case 6: b[3] = 1; break;
		case 8: b[4] = 1; break;//历史两个字的结果一样，不同学校用历、史两种方式表示这门课
		case 10: b[4] = 1; break;
		case 12: b[5] = 1; break;
		case 14: b[6] = 1; break;
		}
	}
	return b;
}
string  translate2_7_3(int * b)//将二进制科目翻译为汉字
{
	string sub1 = "物";
	string sub2 = "化";
	string sub3 = "生";
	string sub4 = "政";
	string sub5 = "史";
	string sub6 = "地";
	string sub7 = "信息";
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
	srand((int)time(0));  // 初始化随机数种子 
	for (i = 0; i < n; i++)
	{
		ele[i].data = rand();  // 随机生成一个数 
		ele[i].index = i + 1;
	}
	qsort(ele, n, sizeof(ele[0]), cmp_7_3);  //排序 
	for (i = 0; i < n; i++)
	{
		a[i] = ele[i].index;
	}
}
int cmp_7_3(const void *a, const void *b)   // 升序排序
{
	return((struct element*)a)->data - ((struct element*)b)->data;
}