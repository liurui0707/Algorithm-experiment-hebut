#include<stdio.h>
#include<math.h>
#include<time.h>
#include<stdlib.h>
#include<conio.h>
#include<graphics.h>

#define MIN(a,b) ((a.dis)>(b.dis)?(b):(a))
#define fabs(a) ((a)<(0)?(-(a)):(a))

//���ڼ�¼һά��������
typedef struct{
	int a, b;
	double dis;
}record;

//��ά�ĵ�
struct point
{
	int x, y;
};

//���ά�ľ��뺯��
double Distance(point a, point b){
	return sqrt((double)((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y)));
}

//һά�ıȽ�������
int cmp(const void *x, const void *y){
	return (*(int *)x-*(int *)y);
}
//����
int Partition(point P[], int first, int end){
	//��ʼ������������
	int i = first, j = end;
	while (i<j)
	{
		//�Ҳ�ɨ��
		while (i<j&&P[i].y <= P[j].y)
		{
			j--;
		}
		//����С�ļ�¼����ǰ��
		if (i<j)
		{
			point temp = P[i];
			P[i] = P[j];
			P[j] = temp;
			i++;
		}
		while (i<j&&P[i].y <= P[j].y)
		{
			i++;
		}
		if (i<j)
		{
			point temp = P[i];
			P[i] = P[j];
			P[j] = temp;
			j--;
		}
	}
	return i;
}

//���п�������
void QuickSort(point P[], int first, int end){
	int pivot;
	if (first<end)
	{
		pivot = Partition(P, first, end);
		QuickSort(P, first, pivot - 1);
		QuickSort(P, pivot + 1, end);
	}
}

//���ά������
double Closest(point S[], int low, int high, point & a, point & b){
	double d1, d2, d3, d;
	int mid, i, j, index;

	//��ŵ㼯��P1��P2
	point P[30];

	//ֻ��������
	if (high-low==1)
	{
		//printf("<%d,%d><%d,%d>\n", S[low].x, S[low].y, S[high].x, S[high].y);
		a = S[low];
		b = S[high];
		return Distance(S[low], S[high]);
	}

	//ֻ��������
	if (high-low==2)
	{
		d1 = Distance(S[low], S[low + 1]);
		d2 = Distance(S[low + 1], S[high]);
		d3 = Distance(S[low], S[high]);

		if ((d1 < d2) && (d1 < d3)){
			a = S[low];
			b = S[low + 1];
			//printf("<%d,%d><%d,%d>\n", S[low].x, S[low].y, S[low + 1].x, S[low + 1].y);
			return d1;
		}
			
		else if ((d2<d1)&&(d2 < d3)){
			a = S[low+1];
			b = S[high];
			//printf("<%d,%d><%d,%d>\n", S[low+1].x, S[low+1].y, S[high].x, S[high].y);
			return d2;
		}
			
		else{
			//printf("<%d,%d><%d,%d>\n", S[low].x, S[low].y, S[high].x, S[high].y);
			a = S[low];
			b = S[high];
			return d3;
		}
			
	}

	//���ڵ㿪ʼ��������
	mid = (low + high) / 2;
	//�ݹ����������1
	d1 = Closest(S, low, mid,a,b);
	//�ݹ����������2
	point ar, br;
	d2 = Closest(S, mid + 1, high,ar,br);
	if (d1<d2)
	{
		d = d1;
	}
	else
	{
		a = ar;
		b = br;
		d = d2;
	}

	index = 0;
	//��������P1
	for (i = mid; (i >= low) && ((S[mid].x - S[i].x) < d); i--){
		P[index++] = S[i];
	}
	//��������P2
	for (i = mid + 1; (i <= high) && ((S[i].x - S[mid].x) < d); i++){
		P[index++] = S[i];
	}

	//�����������е����ݰ�Y�������������
	QuickSort(P, 0, index - 1);

	for (i = 0; i < index; i++){
		for (j = i + 1; j < index; j++){
			if ((P[j].y-P[i].y)>=d)
			{
				break;
			}
			else
			{
				d3 = Distance(P[i], P[j]);
				//printf("<%d,%d><%d,%d>\n", S[i].x, S[i].y, S[j].x, S[j].y);
				if (d3<d)
				{
					a = P[i];
					b = P[j];
					d = d3;
				}
			}
		}
	}
	return d;
}

//�ṹ���ð������
void BubbleSort(point *P, int len){
	point temp;
	for (int i = 0; i < len - 1; i++)
	{
		for (int j = 0; j < len - i - 1; j++)
		{
			if ((P+j)->x>(P+j+1)->x)
			{
				temp = *(P + j);
				*(P + j) = *(P + j+1);
				*(P + j+1) = temp;
			}
		}
	}
}

//һά������������
record min_close_yiwei(int *num, int n){
	record re;
	record left, right;
	int mid;
	//ֻ��һ�������Ϊ�����
	if (n==1)
	{
		re.a = re.b = num[0];
		re.dis = 0xFFFFFF;
		return re;
	}
	else if (n==2)
	{
		re.a = num[0];
		re.b = num[1];
		re.dis = num[0] - num[1];
		re.dis = fabs(re.dis);
		return re;
	}
	else
	{
		mid = n / 2;
		left = min_close_yiwei(num, mid);
		right = min_close_yiwei(num + mid, n - mid);

		re.a = num[mid];
		re.b = num[mid + 1];
		re.dis = num[mid] - num[mid + 1];
		re.dis = fabs(re.dis);
		re = MIN(re, left);
		re = MIN(re, right);
		return re;
	}
}
//��������������30����
/*int main()
{
	//��ά�����
	//�����Ա����
	int x[30], y[30];
	int i,j,count=0;
	point P[30];

	//�������x,y����
	srand(time(NULL));
	for ( i = 0; i < 30; i++)
	{
		x[i] = 1 + (rand() % 100);
		y[i] = 1 + (rand() % 100);
	}

	//Ϊ�ṹ�����鸳ֵ
	for ( i = 0; i < 30; i++)
	{
		P[i].x = x[i];
		P[i].y = y[i];
	}

	BubbleSort(P, 30);

	for (i = 0; i < 30; i++)
	{
		printf("<%d,%d>\t", P[i].x, P[i].y);
		count++;
		if (count % 5 == 0)
		{
			printf("\n");
		}
	}

	point a, b;
	double length = Closest(P, 0, 29,a,b);
	printf("������<%d,%d>��<%d,%d>�ľ���Ϊ:%f", a.x,a.y,b.x,b.y,length);

	printf("�Ƿ����ͼ�λ���ʾ?Y OR N\n");
	char c;
	scanf("%c", &c);
	if (c=='Y')
	{
		initgraph(400, 400);
		line(0, 200, 400, 200);
		line(200, 0, 200, 400);
		//circle(200, 200, 2);
		for (i = 0; i < 30; i++)
		{
			circle(P[i].x*2 + 200, P[i].y*2, 2);
		}	
		//�ڴ˴����л���
		line(a.x*2+200, a.y*2, b.x*2+200, b.y*2);
		getch();
		closegraph();
	}
	//һά�����
	double yiwei[30];
	//һά�����
	for (int i = 0; i < 30; i++)
	{
		yiwei[i] = 1 + (rand() % 100);
		printf("%lf", yiwei[i]);
		if ((i+1)%5==0)
		{
			printf("\n");
		}
	}
	//�Ӵ�С��������
	qsort(yiwei, 30, sizeof(yiwei[0]), cmp);
	record d;
	d = min_close_yiwei(yiwei, 30);
	printf("������Ϊ:%g,%g\n,�������Ϊ:%g\n\n", d.a, d.b, d.dis);
	getchar();
	getchar();
	getchar();
	return 0;
}*/