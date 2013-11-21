// ThroughFocusLeft.cpp : implementation file
//

#include "stdafx.h"
#include "VisualMTF.h"
#include "ThroughFocusLeft.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "MainFrm.h"
#include "dmccom.h"
#include "okapi32.h"
#include <math.h>
#include "ThroughFocusFrame.h"
#include "ThroughFocusRight.h"
#include "FOI.h"

#define STEP_DISTANCE 0.25
#define FRAMENUM 18
#define WIDTH 640
#define HEIGHT 480
/////////////////////////////////////////////////////////////////////////////
// CThroughFocusLeft

IMPLEMENT_DYNCREATE(CThroughFocusLeft, CFormView)

CThroughFocusLeft::CThroughFocusLeft()
	: CFormView(CThroughFocusLeft::IDD)
{
	//{{AFX_DATA_INIT(CThroughFocusLeft)
	m_dFromPos = 0.0;
	m_dToPos = 0.0;
	m_bChecked = FALSE;
	m_nStepNum = -1;
	//}}AFX_DATA_INIT
	CMainFrame* MainFramePoint=(CMainFrame*)((CFrameWnd*)AfxGetApp()->m_pMainWnd);
	
	bCameraInit=MainFramePoint->getbCamInit();//��������ʼ״̬
	hBoard=MainFramePoint->getCameraHandle();//���������

	bStageInit=MainFramePoint->getbCamInit();//���λ��̨��ʼ״̬
	hDmc=MainFramePoint->getStageHandle();//���λ��̨���������
	
	lpLinear=MainFramePoint->getCameraBuffer();//�������洢�ռ�ָ��
	dAmplify=MainFramePoint->getdAmplify();//�����΢ϵͳ�Ŵ���
	dPixel=MainFramePoint->getdPixel();//��������Ԫ�ߴ�
	nBoxHeight=MainFramePoint->getnStarHeight();//���ʮ�ֲ��
	nBoxWidth=MainFramePoint->getnStarWidth();//���ʮ�ֲ��

	m_dFromPos=-10.0;//������Ծ���Ĭ��ֵΪ-10΢��
	m_dToPos=10.0;//�յ����Ծ���Ĭ��ֵΪ+10΢��
	m_nStepNum=2;//��������Ĭ��ֵΪ5��0��9���ζ�Ӧ1��10��
	m_bChecked=FALSE;//Ĭ��״̬����ʾ���伫������
	
}

CThroughFocusLeft::~CThroughFocusLeft()
{
}

void CThroughFocusLeft::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CThroughFocusLeft)
	DDX_Text(pDX, IDC_EDIT1, m_dFromPos);
	DDX_Text(pDX, IDC_EDIT2, m_dToPos);
	DDX_Check(pDX, IDC_CHECK1, m_bChecked);
	DDX_CBIndex(pDX, IDC_COMBO1, m_nStepNum);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CThroughFocusLeft, CFormView)
	//{{AFX_MSG_MAP(CThroughFocusLeft)
	ON_BN_CLICKED(IDC_BUTTON1, OnAcquire)
	ON_BN_CLICKED(IDC_BUTTON3, OnFOISet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CThroughFocusLeft diagnostics

#ifdef _DEBUG
void CThroughFocusLeft::AssertValid() const
{
	CFormView::AssertValid();
}

void CThroughFocusLeft::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CThroughFocusLeft message handlers

void CThroughFocusLeft::OnAcquire() 
{
	// TODO: Add your control notification handler code here
	
	int f,i,j;
	
	/*if(bCameraInit==FALSE)//�����ʼ���ж�
	{
		sprintf(cItemText,"�������δ��ɡ�������ֹ��");
		MessageBox(cItemText);
		return;
	}

	if(bStageInit==FALSE)
	{
		sprintf(cItemText,"�������δ��ɡ�������ֹ��");
		MessageBox(cItemText);
		return;
	}
	
	UpdateData(TRUE);//ˢ�¿ؼ�
	double dFromPos=m_dFromPos;//��ò�������̨��ʼλ��
	double dToPos=m_dToPos;//��ò�������̨��ֹλ��
	nAcqTimes=2*m_nStepNum+1;//��ò�����
	
	if((dFromPos+dToPos)!=0)
	{
		sprintf(cItemText,"The two positions are suggested to be symmetrical. Please re-input.");
		MessageBox(cItemText);
		return;
	}	
	

	
	double dFirstStepDis=dFromPos;//���ƽ��̨�ӵ�ǰλ������ʼ�������ƶ��ľ��루��λum��
	double dEveryStepDis=(m_dToPos-m_dFromPos)/(nAcqTimes-1);//���ƽ��̨�м������ƶ��ľ��루��λum��
	double dLastStepDis=0-m_dToPos;//���ƽ��̨����������ظ���ԭ�������ƶ��ľ��루��λum��
	
	if(rc=MoveDistance(2,dFirstStepDis))//Zƽ��̨�ƶ���Ӧ�������ڿͻ��趨֮��ʼ��
	{
		sprintf(cItemText,"Could not make the stage move.RC=%ld\n",rc);
		MessageBox(cItemText);
		return;
	}
	
	lNum=okGetBufferSize(hBoard, (void **)&lpLinear, &dwSize);//��õ�ǰ״̬���������������
	long lFrameNum=FRAMENUM;
	if( lFrameNum > lNum ) //��ֹ��Ҫ�ɼ���ͼ��֡�����ڵ�ǰBUFFER�����ŵ�ͼ��֡��
	{
		lFrameNum = lNum;
		sprintf(cItemText,"���棺�����ǰ������������18������ǰ��Ϊ%d��",lFrameNum);
		MessageBox(cItemText);
	}
	
	MemoryCheck();
	
	OutMemorySetZero();//���������
	long lImageSize=WIDTH*HEIGHT;
	//������������
	int xpos,ypos;//ƽ��ͼ��ֵ������
	for(f=0;f<nAcqTimes;f++)
	{
		*(EveryPos+f)=dFromPos+dEveryStepDis*f;//��ñ��β���Z��λ���������
		InMemorySetZero();//�м�������

		okCaptureTo(hBoard,BUFFER,0,lFrameNum); //�ɼ�ָ������֡ͼ������(�׵�ַΪlpLinear) 
		okGetCaptureStatus(hBoard,1); //��ȡ�ɼ�����
		
		for(i=0;i<lFrameNum;i++)//ѭ����������
			for(j=0;j<lImageSize;j++)
				pData[j]+=*(lpLinear+i*lImageSize+j);//��֡�ۼ�
		for(j=0;j<lImageSize;j++)
		pData[j]/=lFrameNum;//ȡ��ֵ

		
		CenterFind(pData,xpos,ypos,HEIGHT,WIDTH);//���ƽ����ͼ������ĵ�

		AreaSelect(pData,pDataH,pDataV,nBoxWidth,nBoxHeight,xpos,ypos,WIDTH);//�����������ͼ������

		
		for(j=0;j<nBoxWidth;j++)//������������LSF
		for(i=0;i<nBoxHeight;i++)
		{
			*(LSFH+f*nBoxWidth+j)=*(LSFH+f*nBoxWidth+j)+*(pDataH+i*nBoxWidth+j);//����LSFֵ
			*(LSFV+f*nBoxWidth+j)=*(LSFV+f*nBoxWidth+j)+*(pDataV+i*nBoxWidth+j);//����LSFֵ
		}
		

		fft(LSFH,FtDataRe,FtDataIm,nBoxWidth);//����һ���������ݽ���fft	
		for(j=0;j<nBoxWidth;j++)
		{
			*(MTFH+f*nBoxWidth+j)=sqrt( (*(FtDataRe+j)) * (*(FtDataRe+j)) + (*(FtDataIm+j)) * (*(FtDataIm+j)) );//��һ��ǰֵ
			*(MTFH+f*nBoxWidth+j)/=*(MTFH+f*nBoxWidth);//��һ����ֵ
		}

		fft(LSFV,FtDataRe,FtDataIm,nBoxWidth);
		for(j=0;j<nBoxWidth;j++)
		{
			*(MTFV+f*nBoxWidth+j)=sqrt( (*(FtDataRe+j)) * (*(FtDataRe+j)) + (*(FtDataIm+j)) * (*(FtDataIm+j)) );//��һ��ǰֵ
			*(MTFV+f*nBoxWidth+j)=*(MTFV+f*nBoxWidth);//��һ����ֵ
		}

		if(f!=nAcqTimes-1)//����nAcqTimes�Σ��ƶ�nAcqTimes-1�Σ��������λ������-m_dToPos���ɣ�����-(m_dToPos+dEveryStepDis)
		{
			if(rc=MoveDistance(2,dEveryStepDis))//Zƽ��̨�ƶ���Ӧ�������ڿͻ��趨֮��ʼ��
			{
				sprintf(cItemText,"Could not make the stage move.RC=%ld\n",rc);
				MessageBox(cItemText);
				return;
			}
		}

	}
	
	 
		
	for(j=0;j<nBoxWidth;j++)
	{
		*(PosH+j)=(xpos+j-nBoxWidth/2+1)*dPixel/dAmplify;//��LSFλ������
		*(PosV+j)=(ypos+j-nBoxWidth/2+1)*dPixel/dAmplify;
		*(Freq+j)=j*dAmplify/nBoxWidth/dPixel;//��MTFƵ������
	}

	if(rc=MoveDistance(2,dLastStepDis))//Zƽ��̨�ƶ���Ӧ�������ڿͻ��趨֮��ʼ��
	{
		sprintf(cItemText,"Could not make the stage move.RC=%ld\n",rc);
		MessageBox(cItemText);
		return;
	}
	
	//��Ҫ���Ƶ���PosH~LSFH��PosV~LSFV��Freq~MTFH~MTFV*/
	UpdateData(TRUE);
	nAcqTimes=2*m_nStepNum+1;//��ò�����

	EveryPos=new double[nAcqTimes];//����ÿ������Z��λ�ü�¼����ռ�
	MTFH=new double[nBoxWidth*nAcqTimes];//����MTF�ռ䣬�ÿռ䱣������ȡ�����
	MTFV=new double[nBoxWidth*nAcqTimes];
	Freq=new double[nBoxWidth];//����MTFƵ����������ռ�
	

	for(i=0;i<nBoxWidth;i++)
	{
		*(Freq+i)=20.0*i;
	}
	for(f=0;f<nAcqTimes;f++)
	{
		*(EveryPos+f)=(m_dToPos-m_dFromPos)/(nAcqTimes-1)*f+m_dFromPos;
		for(j=0;j<nBoxWidth;j++)
		{
			*(MTFH+f*nBoxWidth+j)=1.0-j*0.015-f*0.1;
			*(MTFV+f*nBoxWidth+j)=1.0-j*0.01-f*0.1;
		}
	}
	
		
	

	CThroughFocusFrame* FrameWndPoint=(CThroughFocusFrame*)(GetParentFrame());//�񸸿�
	CThroughFocusRight* RightViewPoint=(CThroughFocusRight*)(FrameWndPoint->GetRightView());//��������ͼ
	
	RightViewPoint->UpdateTrace(TRUE,Freq,MTFH,MTFV,nBoxWidth,EveryPos,nAcqTimes);//��ͼˢ�²����ݲ������������ݼ���������*/
}

/*****************************
* *image ͼ������ָ��
* &x     ��ֵ�������
* &y     ��ֵ��������
* height ͼ��߶�
* width  ͼ����
*****************************/
void CThroughFocusLeft::CenterFind(double *image, int &x, int &y, int height, int width)//�ú��������ж�ƽ��ͼ�����ݼ�ֵ��λ��
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
* *TD ����ʱ��ʵ�������׵�ַ
* *FDre ���Ƶ��ʵ�������׵�ַ
* *FDim ���Ƶ���鲿�����׵�ַ
* r �任���鳤��
*****************************/
void CThroughFocusLeft::fft(double *TD, double *FDre, double *FDim, int r)
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
void CThroughFocusLeft::AreaSelect(double *image, double *outimageH, double *outimageV, int areawidth, int areaheight, int centerx, int centery, int imagewidth)//�ú����ڻ�ȡͼ��ֵ��λ�ú�
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

int CThroughFocusLeft::GetMoveStep(double dMoveDis)
{
	int nMoveStep=int(dMoveDis/STEP_DISTANCE);
	return nMoveStep;
}

long CThroughFocusLeft::MoveDistance(int nStageNum, double dMoveDistance)
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

void CThroughFocusLeft::MemoryCheck()
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
	if(EveryPos!=NULL)
	{
		delete[] EveryPos;
	}
	EveryPos=new double[nAcqTimes];//����ÿ������Z��λ�ü�¼����ռ�

	long lImageSize=WIDTH*HEIGHT;
	pData=new double[lImageSize];//����ͼ������ƽ��ֵ�ռ�

	long lAreaSize=nBoxHeight*nBoxWidth;//���ѡ������ͼ���С
	pDataH=new double[lAreaSize];//����ѡ������ͼ��
	pDataV=new double[lAreaSize];

	
	FtDataRe=new double[nBoxWidth];//����fft���ʵ�����鲿�ռ�
	FtDataIm=new double[nBoxWidth];

	LSFH=new double[nBoxWidth*nAcqTimes];//����LSF�ռ䣬�ÿռ䱣������ȡ�����
	LSFV=new double[nBoxWidth*nAcqTimes];

	MTFH=new double[nBoxWidth*nAcqTimes];//����MTF�ռ䣬�ÿռ䱣������ȡ�����
	MTFV=new double[nBoxWidth*nAcqTimes];

	PosH=new double[nBoxWidth];//����LSFλ����������ռ�
	PosV=new double[nBoxWidth];

	Freq=new double[nBoxWidth];//����MTFƵ����������ռ�
	
}

void CThroughFocusLeft::OutMemorySetZero()
{
	memset(LSFH,0,nBoxWidth*nAcqTimes);
	memset(LSFV,0,nBoxWidth*nAcqTimes);
	memset(MTFH,0,nBoxWidth*nAcqTimes);
	memset(MTFV,0,nBoxWidth*nAcqTimes);
	memset(PosH,0,nBoxWidth);
	memset(PosV,0,nBoxWidth);
	memset(Freq,0,nBoxWidth);
	memset(EveryPos,0,nAcqTimes);
}

void CThroughFocusLeft::InMemorySetZero()
{
	memset(pData,0,WIDTH*HEIGHT);
	memset(pDataH,0,nBoxWidth*nBoxHeight);
	memset(pDataV,0,nBoxWidth*nBoxHeight);
	memset(FtDataRe,0,nBoxWidth);
	memset(FtDataIm,0,nBoxWidth);

}

void CThroughFocusLeft::OnFOISet() 
{
	// TODO: Add your control notification handler code here
	CFOI dlg;
	double *tempmtfh,*tempmtfv;
	tempmtfh=new double[nBoxWidth];
	tempmtfv=new double[nBoxWidth];
	int i;
	int index=(nAcqTimes-1)/2*nBoxWidth;//��ȡ���в����е��м���������ݵ�ƫ����
	for(i=0;i<nBoxWidth;i++)
	{
		*(tempmtfh+i)=*(MTFH+index+i);
		*(tempmtfv+i)=*(MTFV+index+i);
	}
	
	dlg.Init(nBoxWidth,Freq,tempmtfh,tempmtfv);

	dlg.DoModal();

	delete tempmtfh;
	delete tempmtfv;
}
