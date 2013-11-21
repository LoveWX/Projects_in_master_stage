// RealTimeUp.cpp : implementation file
//

#include "stdafx.h"
#include "VisualMTF.h"
#include "RealTimeUp.h"

#include<string>
#include<fstream>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



#include "MainFrm.h"
#include "dmccom.h"
#include "okapi32.h"
#include <math.h>
#include "RealTimeFrame.h"
#include "RealTimeDown.h"
#include "FOI.h"
#include "BackgroundWnd.h"

#define FRAMENUM 18
#define WIDTH 640
#define HEIGHT 480
#define STEP_DISTANCE 0.25

/////////////////////////////////////////////////////////////////////////////
// CRealTimeUp

IMPLEMENT_DYNCREATE(CRealTimeUp, CFormView)

CRealTimeUp::CRealTimeUp()
	: CFormView(CRealTimeUp::IDD)
{
	//{{AFX_DATA_INIT(CRealTimeUp)
	m_dStepDis = 0.0;
	m_bChecked = FALSE;
	//}}AFX_DATA_INIT
	CMainFrame* MainFramePoint=(CMainFrame*)((CFrameWnd*)AfxGetApp()->m_pMainWnd);
	bCameraInit=MainFramePoint->getbCamInit();//��������ʼ״̬
	hBoard=MainFramePoint->getCameraHandle();//���������
	lpLinear=MainFramePoint->getCameraBuffer();//�������洢�ռ�ָ��
	dAmplify=MainFramePoint->getdAmplify();//�����΢ϵͳ�Ŵ���
	dPixel=MainFramePoint->getdPixel();//��������Ԫ�ߴ�
	nBoxHeight=MainFramePoint->getnStarHeight();//���ʮ�ֲ��
	nBoxWidth=MainFramePoint->getnStarWidth();//���ʮ�ֲ��
	m_dStepDis=5;
	
}

CRealTimeUp::~CRealTimeUp()
{
}

void CRealTimeUp::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRealTimeUp)
	DDX_Text(pDX, IDC_EDIT1, m_dStepDis);
	DDX_Check(pDX, IDC_CHECK1, m_bChecked);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRealTimeUp, CFormView)
	//{{AFX_MSG_MAP(CRealTimeUp)
	ON_BN_CLICKED(IDC_BUTTON1, OnAcquire)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_BUTTON3, OnFOISet)
	ON_BN_CLICKED(IDC_BUTTON2, OnDisplay)
	ON_BN_CLICKED(IDC_BUTTON4, OnSave)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRealTimeUp diagnostics

#ifdef _DEBUG
void CRealTimeUp::AssertValid() const
{
	CFormView::AssertValid();
}

void CRealTimeUp::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CRealTimeUp message handlers

void CRealTimeUp::OnAcquire() 
{
	// TODO: Add your control notification handler code here
	int i,j;

/*	if(bCameraInit==FALSE)//�����ʼ���ж�
	{
		sprintf(cItemText,"�������δ��ɡ�������ֹ��");
		MessageBox(cItemText);
		return;
	}
	
	MemoryCheck();
	long lImageSize=WIDTH*HEIGHT;


	SetMemoryZero();
	//������������
	lNum=okGetBufferSize(hBoard, (void **)&lpLinear, &dwSize);//��õ�ǰ״̬���������������
	long lFrameNum=FRAMENUM;
	if( lFrameNum > lNum ) //��ֹ��Ҫ�ɼ���ͼ��֡�����ڵ�ǰBUFFER�����ŵ�ͼ��֡��
	{
		lFrameNum = lNum;
		sprintf(cItemText,"���棺�����ǰ������������18������ǰ��Ϊ%d��",lFrameNum);
		MessageBox(cItemText);
	}
	okCaptureTo(hBoard,BUFFER,0,lFrameNum); //�ɼ�ָ������֡ͼ������(�׵�ַΪlpLinear) 
	okGetCaptureStatus(hBoard,1); //��ȡ�ɼ����� 
	
	//���»��������ͼ�����ݵ�ƽ��ֵ
	
	for(i=0;i<lFrameNum;i++)//ѭ����������
		for(j=0;j<lImageSize;j++)
				pData[i]+=*(lpLinear+i*lImageSize+j);//��֡�ۼ�

	for(j=0;j<lImageSize;j++)
		pData[j]/=lFrameNum;//ȡ��ֵ
	
	int xpos,ypos;
	CenterFind(pData,xpos,ypos,HEIGHT,WIDTH);//���ƽ����ͼ������ĵ�

	
	AreaSelect(pData,pDataH,pDataV,nBoxWidth,nBoxHeight,xpos,ypos,WIDTH);//�����������ͼ������
	
	
	
	for(j=0;j<nBoxWidth;j++)//��LSF��ֵ
	{
		*(LSFH+j)=0;
		*(LSFV+j)=0;
	}
	for(j=0;j<nBoxWidth;j++)//������������LSF
		for(i=0;i<nBoxHeight;i++)
		{
			*(LSFH+j)=*(LSFH+j)+*(pDataH+i*nBoxWidth+j);//����LSFֵ
			*(LSFV+j)=*(LSFV+j)+*(pDataV+i*nBoxWidth+j);//����LSFֵ
		}
	
	
	
	for(j=0;j<nBoxWidth;j++)//��MTF��ֵ
	{
		*(MTFH+j)=0;
		*(MTFV+j)=0;
	}
	



	fft(LSFH,FtDataRe,FtDataIm,nBoxWidth);
	for(j=0;j<nBoxWidth;j++)
	{
		*(MTFH+j)=sqrt( (*(FtDataRe+j)) * (*(FtDataRe+j)) + (*(FtDataIm+j)) * (*(FtDataIm+j)) );//��һ��ǰֵ
		*(MTFH+j)/=*(MTFH+0);//��һ����ֵ
	}
	fft(LSFV,FtDataRe,FtDataIm,nBoxWidth);
	for(j=0;j<nBoxWidth;j++)
	{
		*(MTFV+j)=sqrt( (*(FtDataRe+j)) * (*(FtDataRe+j)) + (*(FtDataIm+j)) * (*(FtDataIm+j)) );//��һ��ǰֵ
		*(MTFV+j)/=*(MTFV+0);//��һ����ֵ
	}
	
	
	for(j=0;j<nBoxWidth;j++)
	{
		*(PosH+j)=(xpos+j-nBoxWidth/2+1)*dPixel/dAmplify;//��LSFλ������
		*(PosV+j)=(ypos+j-nBoxWidth/2+1)*dPixel/dAmplify;
		*(Freq+j)=j*dAmplify/nBoxWidth/dPixel;//��MTFƵ������
	}
*/
	//��Ҫ���Ƶ���PosH~LSFH��PosV~LSFV��Freq~MTFH~MTFV

	PosH=new double[nBoxWidth];//����LSFλ����������ռ�
	PosV=new double[nBoxWidth];
	LSFH=new double[nBoxWidth];//����LSF�ռ�
	LSFV=new double[nBoxWidth];
	Freq=new double[nBoxWidth];//����MTFƵ����������ռ�
	MTFH=new double[nBoxWidth];//����MTF�ռ�
	MTFV=new double[nBoxWidth];

	for(i=0;i<nBoxWidth;i++)
	{
		*(PosH+i)=1.0+i*0.2;
		*(PosV+i)=3.0-i*0.1;
		*(LSFH+i)=250.0+i*20;
		*(LSFV+i)=320.0+i*10;
		//*(Freq+i)=40.0*i;
		*(Freq+i)=i*dAmplify/nBoxWidth/dPixel;//��MTFƵ������
		*(MTFH+i)=1.0-i*0.025;
		*(MTFV+i)=1.0-i*0.02;
	}

	

	CRealTimeFrame* FrameWndPoint=(CRealTimeFrame*)(GetParentFrame());//�񸸿�
	CRealTimeDown* DownViewPoint=(CRealTimeDown*)(FrameWndPoint->GetDownView());//��������ͼ
	
	DownViewPoint->UpdateTrace(TRUE,PosH,PosV,LSFH,LSFV,Freq,MTFH,MTFV,nBoxWidth);//��ͼˢ�²����ݲ������������ݼ���������
	
}

/*****************************
* *image ͼ������ָ��
* &x     ��ֵ�������
* &y     ��ֵ��������
* height ͼ��߶�
* width  ͼ����
*****************************/
void CRealTimeUp::CenterFind(double *image, int &x, int &y, int height, int width)//�ú��������ж�ƽ��ͼ�����ݼ�ֵ��λ��
{
	int i, j;
	x = 0;
	y = 0;

	double a = 0.0;
	for(i=0;i<height;i++)
	{
		for(j=0;j<width;j++)
		{
			if( *(image+i*width+j) > a)
			{
				a = *(image+i*width+j); 
				x = j;
				y = i;
			}
		}
	}

}

/*****************************
* *image ͼ������ָ��
* *outimageH ����ĺ���ͼ���׵�ַ
* *outimageV ���������ͼ���׵�ַ 
* areawidth ���ͼ����
* areaheight  ���ͼ��߶�
* centerx ��ֵ���ĵ������
* centery ��ֵ���ĵ�������
* imagewidth ԭͼ����
*****************************/
void CRealTimeUp::AreaSelect(double *image, double *outimageH, double *outimageV, int areawidth, int areaheight, int centerx, int centery, int imagewidth)//�ú����ڻ�ȡͼ��ֵ��λ�ú�
{
	int i,j;
	for(i=0;i<areaheight;i++)
	{
		for (j=0;j<areawidth;j++)
		{
			outimageH[i*areawidth+j]=image[(centery+i-areaheight/2+1)*imagewidth+(centerx+j-areawidth/2+1)];//��ú�������ݾ���			
		}

	}
	for(i=0;i<areaheight;i++)
	{
		for (j=0;j<areawidth-1;j++)
		{
			outimageV[i*areawidth+j]=image[(centery+j-areawidth/2+1)*imagewidth+(centerx+i-areaheight/2+1)];//�����������ݾ���
		}

	}
}

/*****************************
* *TD ����ʱ��ʵ�������׵�ַ
* *FDre ���Ƶ��ʵ�������׵�ַ
* *FDim ���Ƶ���鲿�����׵�ַ
* r �任���鳤��
*****************************/
void CRealTimeUp::fft(double *TD, double *FDre, double *FDim, int r)
{
	long count;		//����Ҷ�任����
	int i,j,k;		//ѭ������
	int bfsize,p;
	double angle,tempre,tempim;	//�Ƕ�
	double *Wre,*Wim,*Xre1,*Xim1,*Xre2,*Xim2,*X;
	
	count=1<<r;		//���㸵��Ҷ�任��������2^r��rΪ��������
	
	//������������洢��
	Wre=new double[count/2];
	Wim=new double[count/2];
	Xre1=new double[count];
	Xim1=new double[count];
	Xre2=new double[count];
	Xim2=new double[count];
	
	//�����Ȩϵ��
	for(i=0;i<count/2;i++)
	{
		angle=-i*PI*2/count;
		Wre[i]=cos(angle);//��Ȩϵ��ʵ��
		Wim[i]=sin(angle);//��Ȩϵ���鲿
	}
	
	//��ʱ���д��X1
	for (i=0;i<count;i++)
	{
		Xre1[i]=TD[i];//ʱ��ʵ��
		Xim1[i]=0;//ʱ���鲿��ȫΪ�㣩
	}
	
	//���õ����㷨���п��ٸ���Ҷ�任
	for (k=0;k<r;k++)//����r�ε���
	{
		for (j=0;j<1<<k;j++)//ÿ�ε����ֳ�(1<<k)�����ּ���
		{
			bfsize=1<<(r-k);//ÿ�ε����������ֵĳ���
			for (i=0;i<bfsize/2;i++)
			{
				p=j*bfsize;//��λ��������
				Xre2[i+p]=Xre1[i+p]+Xre1[i+p+bfsize/2];
				Xim2[i+p]=Xim1[i+p]+Xim1[i+p+bfsize/2];
				//X2[i+p+bfsize/2]=(X1[i+p]-X1[i+p+bfsize/2])*W[i*(1<<k)];
				tempre=Xre1[i+p]-Xre1[i+p+bfsize/2];
				tempim=Xim1[i+p]-Xim1[i+p+bfsize/2];
				Xre2[i+p+bfsize/2]=tempre*Wre[i*(1<<k)]-tempim*Wim[i*(1<<k)];
				Xim2[i+p+bfsize/2]=tempre*Wim[i*(1<<k)]+tempim*Wre[i*(1<<k)];
			}
		}
		X=Xre1;			//����X1��X2
		Xre1=Xre2;		//Ŀ���ǽ�X2�е�Ԫ���Ƶ�X1�������ý���ָ��ķ���ʵ��
		Xre2=X;
		X=Xim1;
		Xim1=Xim2;
		Xim2=X;
	}
	
	//��������
	for (j=0;j<count;j++)
	{
		p=0;
		for (i=0;i<r;i++)//�������빲rλ����ѭ��ʹpΪj�ĵ�����
		{
			if(j&(1<<i))
			{
				p+=1<<(r-i-1);
			}
		}
		FDre[j]=Xre1[p];//Ƶ��
		FDim[j]=Xim1[p];
	}
	
	delete[] Wre;
	delete[] Wim;
	delete[] Xre1;
	delete[] Xre2;
	delete[] Xim1;
	delete[] Xim2;
}



void CRealTimeUp::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	UpdateData(TRUE);
	double dMoveDis=m_dStepDis;//���ƽ��̨�����ƶ��Ĳ���(��λum)
	
	switch(nSBCode)//������Ϣ
	{
		case SB_LINELEFT://�󴥻�
			if(rc=MoveDistance(2,(-1)*dMoveDis))//Zƽ��̨����λ�ƾ�����
			{
				sprintf(cItemText,"Could not make the stage move.RC=%ld\n",rc);
				MessageBox(cItemText);	
			}
			break;
		case SB_LINERIGHT://�Ҵ���
			if(rc=MoveDistance(2,dMoveDis))//Zƽ��̨����λ�ƾ�����
			{
				sprintf(cItemText,"Could not make the stage move.RC=%ld\n",rc);
				MessageBox(cItemText);
			}
			break;

	}

	CFormView::OnHScroll(nSBCode, nPos, pScrollBar);
}

long CRealTimeUp::MoveDistance(int nStageNum, double dMoveDistance)
{
	CString cMes,cMes1,cMes2;
	int nMoveStep=GetMoveStep(dMoveDistance);//������ת���ɲ���
	cMes1="SP 500,500,500,500\r\n";//�����ٶ�
	switch(nStageNum)//���ݵ����ű�д���λ�ƴ���
	{
		case(0):
			cMes2.Format("PR %d,0,0,0\r\nEN",nMoveStep);
			break;
		case(1):
			cMes2.Format("PR 0,%d,0,0\r\nEN",nMoveStep);
			break;
		case(2):
			cMes2.Format("PR 0,0,%d,0\r\nEN",nMoveStep);
			break;
		case(3):
			cMes2.Format("PR 0,0,%d,0\r\nEN",nMoveStep);
			break;
	}
	cMes=cMes1+cMes2;//���ָ��ϲ�
	
	for(int i=0;i<cMes.GetLength();i++)
		szBuffer[i]=cMes.GetAt(i);//�ַ���ת����ַ�����

	CMainFrame* MainFramePoint=(CMainFrame*)((CFrameWnd*)AfxGetApp()->m_pMainWnd);
	hDmc=MainFramePoint->getStageHandle();//��ȡ������������

    rc=DMCDownloadFromBuffer(hDmc,szBuffer,NULL);//ָ���
	if(rc)
	{
		sprintf(cItemText,"Could not download a program to the controller.RC=%ld\n",rc);
		MessageBox(cItemText);
		return rc;
	}
	
	rc=DMCCommand(hDmc,"XQ/r",szBuffer,NULL);//ָ��ִ��
	
	if(rc)
	{
		sprintf(cItemText,"Could not execute a program in the controller.RC=%ld\n",rc);
		MessageBox(cItemText);
		return rc;
	}

	
		return 0;
}

int CRealTimeUp::GetMoveStep(double dMoveDis)
{
	int nMoveStep=int(dMoveDis/STEP_DISTANCE);
	return nMoveStep;
}






void CRealTimeUp::MemoryCheck()
{
	if(pData!=NULL)
	{
		delete[] pData;
	}
	if(pDataH!=NULL)
	{
		delete[] pDataH;
	}
	if(pDataV!=NULL)
	{
		delete[] pDataV;
	}
	if(LSFH!=NULL)
	{
		delete[] LSFH;
	}
	if(LSFV!=NULL)
	{
		delete[] LSFV;
	}
	if(MTFH!=NULL)
	{
		delete[] MTFH;
	}
	if(MTFV!=NULL)
	{
		delete[] MTFV;
	}
	if(FtDataRe!=NULL)
	{
		delete[] FtDataRe;
	}
	if(FtDataIm!=NULL)
	{
		delete[] FtDataIm;
	}
	if(PosH!=NULL)
	{
		delete[] PosH;
	}
	if(PosV!=NULL)
	{
		delete[] PosV;
	}
	if(Freq!=NULL)
	{
		delete[] Freq;
	}
	long lImageSize=WIDTH*HEIGHT;
	pData=new double[lImageSize]; //����ͼ������ƽ��ֵ�ռ�

	long lAreaSize=nBoxHeight*nBoxWidth;//���ѡ������ͼ���С
	pDataH=new double[lAreaSize];//����ѡ������ͼ��
	pDataV=new double[lAreaSize];

	LSFH=new double[nBoxWidth];//����LSF�ռ�
	LSFV=new double[nBoxWidth];

	
	FtDataRe=new double[nBoxWidth];
	FtDataIm=new double[nBoxWidth];
	
	MTFH=new double[nBoxWidth];//����MTF�ռ�
	MTFV=new double[nBoxWidth];

	PosH=new double[nBoxWidth];//����LSFλ����������ռ�
	PosV=new double[nBoxWidth];
	Freq=new double[nBoxWidth];//����MTFƵ����������ռ�

}


void CRealTimeUp::SetMemoryZero()
{
	memset(LSFH,0,nBoxWidth);
	memset(LSFV,0,nBoxWidth);
	memset(MTFH,0,nBoxWidth);
	memset(MTFV,0,nBoxWidth);
	memset(PosH,0,nBoxWidth);
	memset(PosV,0,nBoxWidth);
	memset(Freq,0,nBoxWidth);

	memset(pData,0,WIDTH*HEIGHT);
	memset(pDataH,0,nBoxWidth*nBoxHeight);
	memset(pDataV,0,nBoxWidth*nBoxHeight);
	memset(FtDataRe,0,nBoxWidth);
	memset(FtDataIm,0,nBoxWidth);
}

void CRealTimeUp::OnFOISet() 
{
	// TODO: Add your control notification handler code here
	CFOI dlg;
	
	dlg.Init(nBoxWidth,Freq,MTFH,MTFV);

	dlg.DoModal();

}


void CRealTimeUp::OnDisplay() 
{
	// TODO: Add your control notification handler code here
		//������ģ̬�Ի���
		CBackgroundWnd* pBackgroundWnd;
		pBackgroundWnd=new CBackgroundWnd();
		CMainFrame* MainFramePoint=(CMainFrame*)((CFrameWnd*)AfxGetApp()->m_pMainWnd);
		CString sLensName=MainFramePoint->getsLensName();
		
		if(pBackgroundWnd!=NULL)
		{
			//pBackgroundWnd->getDataFromMainFrm(this);
			pBackgroundWnd->getDataFromRealTimeFrm(this);//�˺�������ɵ�ǰ������ʾ������������͵�����
			CRect rect;
			GetWindowRect(rect);//λ�ü���С�趨
			rect.top+=75;
			rect.left+=75;
			rect.right=rect.left+660;
			rect.bottom=rect.top+520;
			BOOL ret=pBackgroundWnd->Create(NULL,sLensName,WS_OVERLAPPEDWINDOW,rect,this);
			if(!ret)
				AfxMessageBox("Error Creating Dialog!");
			pBackgroundWnd->ShowWindow(SW_SHOW);//��ʾ�Ի���
		}
		else
		{
			AfxMessageBox("Error Creating Dialog Object!");
		}
	
}

void CRealTimeUp::OnSave() 
{
	// TODO: Add your control notification handler code here
	int i;
	CFileDialog filedlg(FALSE, NULL, NULL, OFN_HIDEREADONLY 
		|OFN_OVERWRITEPROMPT, "VMF�ļ� (*.vmf)|*.vmf|�����ļ� (*.*)|*.*||", NULL);//�����ļ�����Ի���
	char *filepath;
	if(filedlg.DoModal()==IDOK)
	{
		string sfpath=filedlg.GetPathName();//����ļ�����·��
		i=sfpath.length();
		filepath=new char[i+5];
		strcpy(filepath,sfpath.c_str());//�����ļ�·��
		if(strcmp(filepath+i-4,".vmf")!=0)//�ļ���׺���б�
		{
			filepath[i++]='.';//��׺�����
			filepath[i++]='v';
			filepath[i++]='m';
			filepath[i++]='f';
			filepath[i]='\0';
		}
		FILE *filepoint=fopen(filepath,"w");//���ļ�
		delete[] filepath;//�����ļ���ָ��
		filepath=NULL;
		if(filepoint==NULL)
		{
			MessageBox("Could not save file!","Error");//���ļ�ʧ��
			return;
		}
		CTime temptime;
		temptime=CTime::GetCurrentTime();//��ȡ��ǰʱ��
		CString temptimestring=temptime.Format("%Y-%m-%d-%H-%M-%S");//��ʱ�����ת�����ַ�������ʽΪ��-��-��-ʱ-��-��
		fprintf(filepoint,"Saved time:%s\n",temptimestring);//д�뱣��ʱ��
		//���µ����ò������������
		int arraylength=nBoxWidth;

		CMainFrame* MainFramePoint;
		MainFramePoint=(CMainFrame*)((CFrameWnd*)AfxGetApp()->m_pMainWnd);//�������ָ��
		double dPinDiameter=MainFramePoint->getdPinDiameter();//��ÿ׾�
		fprintf(filepoint,"Pin Diameter:%.2lf\n",dPinDiameter);//д��׾�
		double dAmplify=MainFramePoint->getdAmplify();//����м̷Ŵ���
		fprintf(filepoint,"Amplification Ratio:%.2lf\n",dAmplify);//д���м�ϵͳ�Ŵ���
		CString sLensName=MainFramePoint->getsLensName();//��þ�ͷ����
		fprintf(filepoint,"Camera Name:%s\n",sLensName);//д�뾵ͷ����
		double dFocusLength=MainFramePoint->getdFocusLength();//���ƽ�й�ܽ���
		fprintf(filepoint,"Focus:%.2lf\n",dFocusLength);//д��ƽ�й�ܽ���
		double dFNumber=MainFramePoint->getdFNumber();//��þ�ͷF��
		fprintf(filepoint,"F Number:%.2lf\n",dFNumber);//д�뾵ͷF��
		double dWaveLength=MainFramePoint->getdWaveLength();//��ù�Դ����
		fprintf(filepoint,"WaveLength:%.2lf\n",dWaveLength);//д���Դ����
		double dLength=MainFramePoint->getdLength();//���ƽ�й�ܽ���
		fprintf(filepoint,"Collimated Focus:%.2lf\n",dLength);//д��ƽ�й�ܽ���
		//�ò���ֱ�Ӵӱ�����
		fprintf(filepoint,"Array Length:%d\n",arraylength);//д����������ߴ磬��ʹ��arraylength
		
		//�˴��Ĳ��������������ж�Ӧ���������Ʋ�ͬ������ʽ��������ͬ
		fprintf(filepoint,"position(T):");//д��T����λ������
		for(i=0;i<arraylength;i++)
		{
			fprintf(filepoint,"%.2lf ",PosH[i]);
		}
	

		fprintf(filepoint,"\nLSF(T):");//д��T����LSF����
		for(i=0;i<arraylength;i++)
		{
			fprintf(filepoint,"%.4lf ",LSFH[i]);
		}

		
		fprintf(filepoint,"\nposition(S):");//д��S����λ������
		for(i=0;i<arraylength;i++)
		{
			fprintf(filepoint,"%.2lf ",PosV[i]);
		}
		


		fprintf(filepoint,"\nLSF(S):");//д��S����LSF����
		for(i=0;i<arraylength;i++)
		{
			fprintf(filepoint,"%.4lf ",LSFV[i]);
		}
		

		fprintf(filepoint,"\nFrequence(lp/mm):");//д��Ƶ������
		for(i=0;i<arraylength;i++)
		{
			fprintf(filepoint,"%.2lf ",Freq[i]);
		}
		
		fprintf(filepoint,"\nMTF(T):");//д��T����MTF����
		for(i=0;i<arraylength;i++)
		{
			fprintf(filepoint,"%.4lf ",MTFH[i]);
		}
		
		
		fprintf(filepoint,"\nMTF(S):");//д��S����MTF����
		for(i=0;i<arraylength;i++)
		{
			fprintf(filepoint,"%.4lf ",MTFV[i]);
		}
		
		
		fclose(filepoint);//�ر��ļ�
	}
}



int CRealTimeUp::getarraylength()
{
	return nBoxWidth;
}

double* CRealTimeUp::getdFreq()
{
	return Freq;
}


double* CRealTimeUp::getdMTFt()
{
	return MTFH;
}

double* CRealTimeUp::getdMTFs()
{
	return MTFV;
}

double* CRealTimeUp::getdLSFt()
{
	return LSFH;
}

double* CRealTimeUp::getdLSFs()
{
	return LSFV;
}

double* CRealTimeUp::getdPOSt()
{
	return PosH;
}


double* CRealTimeUp::getdPOSs()
{
	return PosV;
}
