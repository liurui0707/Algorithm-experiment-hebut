#include<iostream>
#define MAXLENGTH 10
//��·����
int TSPLength;
//�����Ȩͼ�Ĵ��۾���
int value[5][5];

//����һ���ṹ��
struct bian
{
	int x;
	int y;
};
//������м���
int V[MAXLENGTH];
//�����ü���
bian P[MAXLENGTH];
//����ʵ�ʸ���
int citys;
//������������
void Modify(int a[5][5]){
	int i;
	for (i = 0; i < citys; i++)
	{
		value[i][i] = 999;
	}
}
//˳����Һ���
int FindBySeq(int *ListSeq, int ListLength, int KeyData)
{
	int tmp = 0;
	int length = ListLength;
	for (int i = 0; i < ListLength; i++)
	{
		if (ListSeq[i] == KeyData)
			return i;
	}
	return -1;
}
