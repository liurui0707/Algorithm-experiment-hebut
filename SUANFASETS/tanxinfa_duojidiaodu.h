#include<stdio.h>
//���������ҵ����
#define MAXLENGTH 10
//��������Ŀ���ʱ��
int d[MAXLENGTH];
//����ÿ̨�����Ĵ���ʱ��
int S[MAXLENGTH][MAXLENGTH];
//����һ���ṹ�壬��¼��ҵ����ʱ��
struct work{
	//��ҵʱ��
	int hour;
	//ԭ˳��
	int number;
};
work t[MAXLENGTH];
//����������㷨
void bubble_sort(work a[], int n){
	int i, j;
	work temp;
	for (j = 0; j < n - 1; j++){
		for ( i = 0; i < n-1-j; i++)
		{
			if (a[i].hour<a[i+1].hour)
			{
				temp = a[i];
				a[i] = a[i + 1];
				a[i + 1] = temp;
			}
		}
	}
}
//��������㷨
void MultiMachine(work t[], int n, int d[], int m){
	//��β�±�
	int rear[MAXLENGTH];
	int i, j, k;
	//����ǰm����ҵ
	for ( i = 0; i < m; i++)
	{
		S[i][0] = t[i].number;
		rear[i] = 0;
		d[i] = t[i].hour;
	}
	//һ�ΰ������¼�����ҵ
	for ( i = m; i < n; i++)
	{
		//�������ȿ��еĻ���
		for (j = 0, k = 1; k < m; k++){
			if (d[k]<d[j])
			{
				j = k;
			}
		}
		rear[j]++;
		S[j][rear[j]] = t[i].number;
		d[j] += t[i].hour;
	}
}