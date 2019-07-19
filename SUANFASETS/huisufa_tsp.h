#include<iostream>
using namespace std;
/*���ݷ����TSP���⣬�����������������ѡ�����ķ���
���ڿα���û�и����㷨�����ڴ˸����㷨���
������
1.���и���n
2.����֮��ľ���value[][]
3.�����߹���·��cl
4.���·��bestx[]
5.���б������x[]
���裺
*/
#define MAXLENGTH 10
//���и���
int n;
//����֮��ľ���
int value[MAXLENGTH][MAXLENGTH];
//���б��
int citys[MAXLENGTH];
//����·��
int bestx[MAXLENGTH];
int maybex[MAXLENGTH];
//������·��
int cl = 0;
//����·������
int bestl = 999;
int maybel = 999;

//��������ԭ������
void Modify();
//Tsp����ԭ������
void Tsp(int n);

//�������������Խ���������Ϊ0
void Modify(){
	for (int i = 1; i <= n; i++)
	{
		value[i][i] = -1;
	}
}

//��������
void swap(int &a, int &b){
	int temp;
	temp = a;
	a = b;
	b = temp;
}
//������ݷ���TSP����
void Tsp(int t){
	//���ڼ���
	int j;
	//����Ҷ�ӽڵ�
	if (t>n)
	{
		if (value[citys[n]][1] != -1 && (cl + value[citys[n]][1])<bestl){
			//��¼��������·��
			for (j = 1; j <= n; j++)
			{
				bestx[j] = citys[j];
			}
			bestl = cl + value[citys[n]][1];
		}
	}
	else{//��û�е���Ҷ�ӽڵ�
		//������չ�ڵ�����ҷ�֧���������뵱ǰ�������ڵ��ڽ�����
		for ( j = t; j <= n ; j++)
		{
			//������t-1���������t������֮����·���ҿ��Եõ����̵�·��
			if (value[citys[t - 1]][citys[j]] != -1 && (cl + value[citys[t - 1]][citys[j]]) < bestl){
				//����λ��
				swap(citys[t], citys[j]);
				//Ϊ���ȸ�ֵ
				cl += value[citys[t - 1]][citys[t]];
				//������ȱ���
				Tsp(t + 1);
				//�ָ�ԭ״
				cl -= value[citys[t - 1]][citys[t]];
				swap(citys[t], citys[j]);
			}
		}
	}
}