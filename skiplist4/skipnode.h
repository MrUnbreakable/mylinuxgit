#include<vector>
using namespace std;
struct skipnode//��ʾһ�����Ľṹ��
{
	int data;//Ԫ�ص�ֵ
	int level;//����
	vector<skipnode* >p;//����ָ�������
	skipnode(int datain = 0, int levelin = 1) {//���캯��
		setnode(datain, levelin);
	}
	void setnode(int datain = 0, int levelin = 1) {//�������ݳ�Ա����������p�ĳ��Ȳ������渳��ֵ
		data = datain;
		level = levelin;
		while (!p.empty())
			p.pop_back();
		for (int i = 0; i < level; i++) {
			p.push_back(NULL);
		}
	}
};
