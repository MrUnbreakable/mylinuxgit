#include<vector>
using namespace std;
struct skipnode//表示一个结点的结构体
{
	int data;//元素的值
	int level;//层数
	vector<skipnode* >p;//存结点指针的数组
	skipnode(int datain = 0, int levelin = 1) {//构造函数
		setnode(datain, levelin);
	}
	void setnode(int datain = 0, int levelin = 1) {//设置数据成员，设置数组p的长度并在里面赋空值
		data = datain;
		level = levelin;
		while (!p.empty())
			p.pop_back();
		for (int i = 0; i < level; i++) {
			p.push_back(NULL);
		}
	}
};
