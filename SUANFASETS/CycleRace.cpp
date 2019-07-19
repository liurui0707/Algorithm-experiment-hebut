// CycleRace.cpp : implementation file
//

#include "stdafx.h"
#include "SUANFASETS.h"
#include "CycleRace.h"
#include <locale.h>
#include "closest.h"
#include "time.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

inline unsigned GetCyCount(){
	__asm _emit 0x0f __asm _emit 0x31
}
/////////////////////////////////////////////////////////////////////////////
// CCycleRace dialog


CCycleRace::CCycleRace(CWnd* pParent /*=NULL*/)
	: CDialog(CCycleRace::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCycleRace)
	//}}AFX_DATA_INIT
}


void CCycleRace::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCycleRace)
	DDX_Control(pDX, IDC_EDIT_Result, m_cycleresult);
	DDX_Control(pDX, IDC_EDIT_FileContent, m_fliecontent);
	DDX_Control(pDX, IDC_EDIT1, m_filepathname);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCycleRace, CDialog)
	//{{AFX_MSG_MAP(CCycleRace)
	ON_BN_CLICKED(IDC_BUTTON_OpenFile, OnBUTTONOpenFile)
	ON_BN_CLICKED(IDC_BUTTON_Calculate, OnBUTTONCalculate)
	ON_BN_CLICKED(IDC_BUTTON_Calculate1, OnBUTTONCalculate1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCycleRace message handlers

void CCycleRace::OnBUTTONOpenFile() 
{
	// TODO: Add your control notification handler code here
	CFileDialog opendlg(true, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, (LPCTSTR)_TEXT("TXT Files (*.txt)|*.txt|All Files (*.*)|*.*||"), NULL);

	CString m_send;
	//��ʾ�Ի��������û�����ѡ��
	if (opendlg.DoModal()==IDOK)
	{
		//����ļ�·��
		filepathname = opendlg.GetPathName();
		CString strData;
		m_filepathname.SetWindowText(filepathname);

		CStdioFile f;
		CString str;

		if (f.Open(filepathname, CFile::modeRead)){
			CString s;
			setlocale(LC_CTYPE, "chs");
			while (f.ReadString(s))
			{
				str += s;
				str+="\r\n";
			}
			f.Close();
			m_fliecontent.SetWindowText(str);
			return;
		}
	}
}

void CCycleRace::OnBUTTONCalculate() 
{	
	// TODO: Add your control notification handler code here
	unsigned long start, finish;
	FILE *fp;
	char *ch = filepathname.GetBuffer(filepathname.GetLength() + 1);
	//char arr[20][20]={0};
	int x[30], y[30];
	int i,j,count=0;
	point P[30];

	if((fp=fopen(ch,"r"))==NULL){
		MessageBox("�ļ���ʧ��!");
	}
	else{
		//MessageBox("�ļ��򿪳ɹ�!");
		for(i=0;i<30;i++)
		{
			for(j=0;j<2;j++)
			{
				if(j==0)
					fscanf(fp,"%d",&x[i]);
				else
					fscanf(fp,"%d",&y[i]);
			}
		}
		//Ϊ�ṹ�����鸳ֵ
		for ( i = 0; i < 30; i++)
		{
			P[i].x = x[i];
			P[i].y = y[i];
		}
		//long start=GetTickCount();
		start = (unsigned long)GetCyCount();
		BubbleSort(P, 30);
		
		point a, b;
		double length = Closest(P, 0, 29,a,b);
		finish = (unsigned long)GetCyCount();
		char string[10];
		CString strData;
		
		strData+="������Ϊ:<";
		sprintf(string, " %d," , a.x);
		strData+= string;
		sprintf(string, " %d>��" , a.y);
		strData+= string;
		sprintf(string, " <%d," , b.x);
		strData+=string;
		sprintf(string, " %d>,��̾���Ϊ:" , b.y);
		strData+= string;
		sprintf(string, " %f\r\n" , length);
		strData+=string;
		strData+="����ʱ��Ϊ:";

		sprintf(string, " %d����" ,finish-start);
		strData+=string;
		m_cycleresult.SetWindowText(strData);

		//����ͼ��
		initgraph(800, 800);
		setbkcolor(WHITE);
		// �ñ���ɫ�����Ļ
		cleardevice();
		char s[20];
		for (i = 0; i < 30; i++)
		{
			//circle(P[i].x*2 + 200, P[i].y*2, 2);
			setcolor(BLACK);
			sprintf(s,"(%d,%d)",P[i].x,P[i].y);
			circle(P[i].x*8, 800-P[i].y*8, 4);
			outtextxy(P[i].x*8+5, 795-P[i].y*8,s);
		}	
		//�ڴ˴����л���
		setlinecolor(RED);
		setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 5);
		line(a.x*8, 800-a.y*8, b.x*8, 800-b.y*8);
		getch();
		//closegraph();
		//printf("������<%d,%d>��<%d,%d>�ľ���Ϊ:%f", a.x,a.y,b.x,b.y,length);
	}
	fclose(fp); 
}

void CCycleRace::OnBUTTONCalculate1() 
{
	// TODO: Add your control notification handler code here
	unsigned long start, finish;
	FILE *fp;
	char *ch = filepathname.GetBuffer(filepathname.GetLength() + 1);
	//char arr[20][20]={0};
	int yiwei[30];
	int i;
	record d;

	if((fp=fopen(ch,"r"))==NULL){
		MessageBox("�ļ���ʧ��!");
	}
	else{
		//MessageBox("�ļ��򿪳ɹ�!");
		for(i=0;i<30;i++)
		{
			fscanf(fp,"%d",&yiwei[i]);
		}
		//long start=GetTickCount();
		start = (unsigned long)GetCyCount();
		qsort(yiwei, 30, sizeof(int), cmp);
		d=min_close_yiwei(yiwei,30);
		
		finish=(unsigned long)GetCyCount();
		char string[10];
		CString strData;
		
		strData+="������Ϊ:<";
		sprintf(string, " %d," , d.a);
		strData+= string;
		sprintf(string, " %d>," , d.b);
		strData+= string;
		sprintf(string, "��̾���Ϊ: %d" , d.dis);
		strData+= string;
		strData+="����ʱ��Ϊ:";

		sprintf(string, " %d����" ,finish-start);
		strData+=string;
		m_cycleresult.SetWindowText(strData);

		//����ͼ��
		/*initgraph(800, 800);
		setbkcolor(WHITE);
		// �ñ���ɫ�����Ļ
		cleardevice();
		char s[20];
		for (i = 0; i < 30; i++)
		{
			//circle(P[i].x*2 + 200, P[i].y*2, 2);
			setcolor(BLACK);
			sprintf(s,"(%1.1f)",yiwei[i]);
			circle(yiwei[i]*8, 400, 4);
			outtextxy(yiwei[i]*8+5, 400-5,s);
		}	
		//�ڴ˴����л���
		setlinecolor(RED);
		setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 5);
		line(d.a*8, 400, d.b*8,400);
		getch();*/
		//closegraph();
		//printf("������<%d,%d>��<%d,%d>�ľ���Ϊ:%f", a.x,a.y,b.x,b.y,length);
	}
	fclose(fp); 
}
