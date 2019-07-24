#include<iostream>
#include<vector>
#include<cmath>
#include<time.h>
#include<algorithm>
#include<numeric>
#include"skiplist.h"
using namespace std;
#define E exp(1)
int main() 
{
    vector<double>inserttime, searchtime, removetime;
    vector<int>levellist;
    float p = 1.0 / E;//概率因子
    int ntime = 100;//试验次数
    int i = 0;
    for (int kk = 1; kk <= ntime; kk++) 
    {
        Skiplist list;
	srand((int)time(NULL));
	vector<int>number;
	for (i = 1; i <= 100; i++) 
        {
	    number.push_back(i);
	}
	random_shuffle(number.begin(), number.end());//生成乱序的1到n的数
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
	random_shuffle(number.begin(), number.end());//生成乱序的1到n的数
	start = clock();
	for (i = 0; i < number.size(); i++) 
        {
	    list.search(number.at(i));
	}
	end = clock();
	cost = end - start;
	//cout<<"查找一共运行了"<<cost<<"毫秒"<<endl;
	searchtime.push_back(cost);
	random_shuffle(number.begin(), number.end());//生成乱序的1到n的数
	start = clock();
	for (i = 0; i < number.size(); i++) 
        {
	    list.remove(number.at(i));
	}
	    end = clock();
	    cost = end - start;
	    //cout<<"删除一共运行了"<<cost<<"毫秒"<<endl;
	    removetime.push_back(cost);
	}
	double inserttimemean, searchtimemean, removetimemean, levelmean;
	double zero = 0;
	double size = ntime;
	inserttimemean = accumulate(inserttime.begin(), inserttime.end(), zero) / size;
	levelmean = accumulate(levellist.begin(), levellist.end(), zero) / size;
	searchtimemean = accumulate(searchtime.begin(), searchtime.end(), zero) / size;
	removetimemean = accumulate(removetime.begin(), removetime.end(), zero) / size;
	cout << "probility" << p << endl;
	cout << "test" << ntime << " times" << endl;
	cout << "mean insert time " << inserttimemean << " ms" << endl;
	cout << "mean skip level " << levelmean << " times" << endl;
	cout << "mean search time " << searchtimemean << " ms" << endl;
	cout << "mean remove time " << removetimemean << " ms" << endl;
	return 0;
}
