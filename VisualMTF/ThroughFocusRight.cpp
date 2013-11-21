// ThroughFocusRight.cpp : implementation file
//

#include "stdafx.h"
#include "VisualMTF.h"
#include "ThroughFocusRight.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define PIXEL_WIDTH 0.0098
/////////////////////////////////////////////////////////////////////////////
// CThroughFocusRight

IMPLEMENT_DYNCREATE(CThroughFocusRight, CView)

CThroughFocusRight::CThroughFocusRight()
{
	dExtendedMTFH=NULL;
	dExtendedMTFV=NULL;
	dTempSlopeH=NULL;
	dTempSlopeV=NULL;

	bPenInit=FALSE;
	dMaxDisFreq=100.0;
	nDisplayMode=0;//��ʼ��ʾ״̬������ͼ��ˢ��
}

CThroughFocusRight::~CThroughFocusRight()
{
}


BEGIN_MESSAGE_MAP(CThroughFocusRight, CView)
	//{{AFX_MSG_MAP(CThroughFocusRight)
	ON_WM_CREATE()
	ON_WM_HSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CThroughFocusRight drawing

void CThroughFocusRight::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
	if(nDisplayMode==0)
		return;
	else
	{
		if(bPenInit==FALSE)//��δ��������
		{
			PenCreate();//��������	
			bPenInit=TRUE;//���ı�ʾ
		}
		DrawBackground();//��������ͼ���������񡢱�ע
		DrawPoint();//������ͼ��������
		DrawGrid();//��������ͼ����
		m_ScrollBar1.ShowScrollBar(TRUE);	
	}
}

/////////////////////////////////////////////////////////////////////////////
// CThroughFocusRight diagnostics

#ifdef _DEBUG
void CThroughFocusRight::AssertValid() const
{
	CView::AssertValid();
}

void CThroughFocusRight::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CThroughFocusRight message handlers

/*********
*�ú�������ˢ��ʵʱ�����Ի���
*bMode����ʶ��
*pFreq ˫��MTFƵ�����������׵�ַ
*pHMTF ����MTF��ֵ�����׵�ַ
*pVMTF ����MTF��ֵ�����׵�ַ
nLength ���鳤��
*pPos ��������Z��λ��
nTimes ��������
*********/

void CThroughFocusRight::UpdateTrace(BOOL bMode, double *pFreq, double *pHMTF, double *pVMTF, int nLength, double *pPos, int nTimes)
{
	
	int i,j;
	nBoxWidth=nLength;
	nAcqTimes=nTimes;
	Freq=new double[nBoxWidth];//����MTFƵ����������ռ�
	MTFH=new double[nBoxWidth*nAcqTimes];//����MTF�ռ�
	MTFV=new double[nBoxWidth*nAcqTimes];
	EveryPos=new double[nAcqTimes];

	for(i=0;i<nBoxWidth;i++)
	{
		*(Freq+i)=*(pFreq+i);//��Ƶ������
		
	}

	for(i=0;i<nAcqTimes;i++)
	{
		*(EveryPos+i)=*(pPos+i);//��λ������
		for(j=0;j<nBoxWidth;j++)
		{
			*(MTFH+i*nBoxWidth+j)=*(pHMTF+i*nBoxWidth+j);//��MTFֵ����أ�
			*(MTFV+i*nBoxWidth+j)=*(pVMTF+i*nBoxWidth+j);
		}
		
	}


	
	ExtendMTF();//�������ȫƵ�ʷ�Χ��ֵ��
	
	if(bMode==TRUE)
	{
		nDisplayMode=1;//��ʾ�����Ѿ�ȫ�����ɣ��ı���ʾ״̬
		Invalidate();
	// TODO: Add your specialized creation code here
	}
	else return;	
}



void CThroughFocusRight::ExtendMTF()
{
	CalculateFreq();//�����ֵǰ���Ƶ�ʼ�������ֵ��MTF���鳤��
	SpaceInit();//���ٲ�ֵ��MTF����ռ�

	//���½���ʵ�ʵĲ�ֵ����
	int f,i;
	double *tempsor,*tempdes;
	tempsor=new double[nBoxWidth];//������һ��fft�任��ԭʼ����ռ�
	tempdes=new double[nExtendedLength];//������һ��fft�任�Ľ���ռ�

	
	for(f=0;f<nAcqTimes;f++)
	{
		for(i=0;i<nBoxWidth;i++)
			*(tempsor+i)=*(MTFH+f*nBoxWidth+i);//�õ�ǰ�任��Ҫ��MTF������
		spline(dOriFreq,tempsor,getLeftSlope(),getRightSlope(),dTempSlopeH,nBoxWidth);//���ԭ����б��
		
		for(i=0;i<nExtendedLength;i++)
		{
			splint(dOriFreq,tempsor,dTempSlopeH,dExtFreq[i],tempdes[i],nBoxWidth);//�����Ƶ��������MTF��ֵ
			//double firstdes=tempdes[0];
			//*(dExtendedMTFH+f*nExtendedLength+i)=tempdes[i]/firstdes;//��ֵ��һ��
			*(dExtendedMTFH+f*nExtendedLength+i)=tempdes[i];//����һ��
		}

		

		for(i=0;i<nBoxWidth;i++)
			*(tempsor+i)=*(MTFV+f*nBoxWidth+i);//�õ�ǰ�任��Ҫ��MTF������
		spline(dOriFreq,tempsor,getLeftSlope(),getRightSlope(),dTempSlopeV,nBoxWidth);//���ԭ����б��
	
		for(i=0;i<nExtendedLength;i++)
		{
			splint(dOriFreq,tempsor,dTempSlopeV,dExtFreq[i],tempdes[i],nBoxWidth);//�����Ƶ��������MTF��ֵ
			//double firstdes=tempdes[0];
			//*(dExtendedMTFV+f*nExtendedLength+i)=tempdes[i]/firstdes;//��ֵ��һ��
			*(dExtendedMTFV+f*nExtendedLength+i)=tempdes[i];//����һ��
		}
		
			
	}

	delete[] tempsor;
	delete[] tempdes;
}

void CThroughFocusRight::CalculateFreq()
{
	const double dPixelWidth=PIXEL_WIDTH;//̽������Ԫ�ߴ磨mm��
	CMainFrame* MainFramePoint=(CMainFrame*)((CFrameWnd*)AfxGetApp()->m_pMainWnd);
	double dAmplify=MainFramePoint->getdAmplify();
	
	dOriginalFreq=dAmplify/nBoxWidth/dPixelWidth;//����ԭʼƵ�ʼ��
	int temp=(int)(dOriginalFreq/10);//ԭʼƵ�ʼ�������Ĳ�ֵ������ֵԭ��Ϊ��ֵ�������Ƶ�ʲ�Ϊ������10��������ֵ��
	nExtendedLength=temp*(nBoxWidth-1)+nBoxWidth;//��ֵ��Ƶ�ʵ���
	dExtendedFreq=dOriginalFreq*(nBoxWidth-1)/(nExtendedLength-1);
}

void CThroughFocusRight::SpaceInit()
{
	if(dExtendedMTFH!=NULL)
	{
		delete[] dExtendedMTFH;
	}
	if(dExtendedMTFV!=NULL)
	{
		delete[] dExtendedMTFV;
	}
	if(dTempSlopeH!=NULL)
	{
		delete[] dTempSlopeH;
	}
	if(dTempSlopeV!=NULL)
	{
		delete[] dTempSlopeV;
	}

	dExtendedMTFH=new double[nExtendedLength*nAcqTimes];//MTF��ֵ������ֵ�豣��
	dExtendedMTFV=new double[nExtendedLength*nAcqTimes];
	dTempSlopeH=new double[nBoxWidth];//�м�������ȫ������
	dTempSlopeV=new double[nBoxWidth];
	dOriFreq=new double[nBoxWidth];	
	dExtFreq=new double[nExtendedLength];	
	int i;
	*dOriFreq=0.0;
	*dExtFreq=0.0;
	for(i=1;i<nBoxWidth;i++)
	{
		*(dOriFreq+i)=dOriFreq[i-1]+dOriginalFreq;
	}
	for(i=1;i<nExtendedLength;i++)
	{
		double a=*(dExtFreq+i)=*(dExtFreq+i-1)+dExtendedFreq;
	}
}

double CThroughFocusRight::getLeftSlope()
{
	return 1.0e31;
}

double CThroughFocusRight::getRightSlope()
{
	return 1.0e31;
}

void CThroughFocusRight::spline(double *x, double *y, double yp1, double ypn, double * y2, int lena)
{
	int i,k;
	double p,qn,sig,un;
	
	int n=lena;
	double * u=new double[n-1];
	if(yp1>0.99e30)
		y2[0]=u[0]=0.0;
	else
	{
		y2[0]=-0.5;
		u[0]=(3.0/(x[1]-x[0]))*((y[1]-y[0])/(x[1]-x[0])-yp1);
		
	}
	for(i=1;i<n-1;i++)
	{
		sig=(x[i]-x[i-1])/(x[i+1]-x[i-1]);
		p=sig*y2[i-1]+2.0;
		y2[i]=(sig-1.0)/p;
		u[i]=(y[i+1]-y[i])/(x[i+1]-x[i])-(y[i]-y[i-1])/(x[i]-x[i-1]);
		u[i]=(6.0*u[i]/(x[i+1]-x[i-1])-sig*u[i-1]/p);
	}
	if(ypn>0.99e30)
	{
		qn=un=0.0;
	}
	else
	{
		qn=0.5;
		un=(3.0/(x[n-1]-x[n-2]))*(ypn-(y[n-1]-y[n-2])/(x[n-1]-x[n-2]));
	}
	y2[n-1]=(un-qn*u[n-2])/(qn*y2[n-2]+1.0);
	for (k=n-2;k>=0;k--)
		y2[k]=y2[k]*y2[k+1]+u[k];
	delete[] u;
}

void CThroughFocusRight::splint(double* xa,double* ya,double* y2a,double x,double &y,int lena)
{
	int k;
	double h,b,a;
	
	int n=lena;
	int klo=0;
	int khi=n-1;
	while (khi-klo>1)
	{
		k=(khi+klo)>>1;
		if(xa[k]>x)
			khi=k;
		else
			klo=k;
	}
	h=xa[khi]-xa[klo];
	if(h==0.0)
	{
		MessageBox("Bad xa input!");
		return;
	}
	a=(xa[khi]-x)/h;
	b=(x-xa[klo])/h;
	y=a*ya[klo]+b*ya[khi]+((a*a*a-a)*y2a[klo]
		+(b*b*b-b)*y2a[khi])*(h*h)/6.0;
}

void CThroughFocusRight::DrawBackground()//�ú����������������ͼ��ɫ��������ɫͼ�����������񡢱�ע
{
	int i;
	CDC *mypDC=GetDC();
	CRect rc;
	GetClientRect(&rc);//��ȡ������ͼ��С


	CBrush mybrush1,mybrush2;
	mybrush1.CreateSolidBrush(RGB(200,200,255));//������ɫˢ
	CBrush *oldbrush;
	oldbrush=mypDC->SelectObject(&mybrush1);//ѡ����ˢ��ͬʱ������ˢ
	mypDC->Rectangle(rc.left-1,rc.top-1,rc.right+1,rc.bottom+1);//ȫ��ͼȾ��ɫ

	mybrush2.CreateSolidBrush(RGB(255,255,255));//������ɫˢ
	mypDC->SelectObject(&mybrush2);//ѡ���ˢ
	mypDC->Rectangle(150,100,509,459);//������
	

	mypDC->SelectObject(oldbrush);//�ָ���ˢ


	CPen mypen1(PS_DOT,1,RGB(0,0,0));//������ɫ���߱�
	CPen *oldpen;
	oldpen=mypDC->SelectObject(&mypen1);
	for(i=0;i<9;i++)
	{
		mypDC->MoveTo(150,136+36*i);
		mypDC->LineTo(509,136+36*i);
		mypDC->MoveTo(186+36*i,100);
		mypDC->LineTo(186+36*i,459);
	}
	mypDC->SetBkColor(RGB(200,200,255));//���ֱ�����Ϊ��ɫ��ɫ
	for(i=0;i<nAcqTimes;i++)
	{
		mypDC->SelectObject(&mypen[i]);
		mypDC->MoveTo(80+i*80,570);
		mypDC->LineTo(130+i*80,570);

		mypDC->SelectObject(&mypen[10+i]);
		mypDC->MoveTo(80+i*80,600);
		mypDC->LineTo(130+i*80,600);
	
	}


	mypDC->SelectObject(oldpen);//�ָ��ɱ�

	mypDC->SetBkColor(RGB(200,200,255));//���ֱ�����Ϊ��ɫ��ɫ

	CFont font1;
	font1.CreatePointFont(100,"����",mypDC);//��������
	CFont* oldfont;
	oldfont=mypDC->SelectObject(&font1);//ѡ�������岢����������

	mypDC->TextOut(220,50,"MODULATION TRANSFER FUNCTION");//��ʾ������ͼ����

	mypDC->TextOut(20,562,"���緽��");
	mypDC->TextOut(20,592,"��ʸ����");
	mypDC->TextOut(18,622,"  λ��  ");

	for(i=0;i<nAcqTimes;i++)
	{
		CString temp;
		double curpos=*(EveryPos+i);
		temp.Format("%.3f",curpos);
		mypDC->TextOut(85+80*i,622,temp);
	
	}



	mypDC->SelectObject(oldfont);//�ָ�������*/
}

void CThroughFocusRight::DrawGrid()//�ú����������������ͼ����
{
	CDC *mypDC=GetDC();
	mypDC->SetBkColor(RGB(200,200,255));
	CString temp;
	
	double MTFMAX=1.0;
	CString MTFUpString[6];//MTF��������
	for(int i=0;i<6;i++)
	{
		MTFUpString[i].Format("%.1f",MTFMAX*(5-i)/5);//���MTF�������꣨���ϵ��µݼ���
		mypDC->TextOut(125,90+72*i,MTFUpString[i]);//��MTF������
	}

	
	CString MTFDOWNSTRING[3];//MTF�ĺ�����
	for(i=0;i<3;i++)
	{
		MTFDOWNSTRING[i].Format("%.2f",dActMaxFreq*i/2);//���MTF�ĺ����꣨�����ҵ�����//�˴�������󲻲��㣬����Ƶ��ֵΪ�ӽ��趨ֵ��һ����ֵ
		mypDC->SetTextColor(RGB(0,0,0));//���廹ԭΪ��ɫ
		mypDC->TextOut(135+180*i,472,MTFDOWNSTRING[i]);//��MTF������

	}
}


void CThroughFocusRight::DrawPoint()
{
	

	DrawMTFPoint();
}

void CThroughFocusRight::DrawMTFPoint()//�ú�����MTF��
{
	CDC *mypDC=GetDC();
	
	int *MTFXPos;
	int *MTFYPos;



	int nExtDisLen=int(dMaxDisFreq/dExtendedFreq);//��õ�ǰ��Ҫ��ʾ�Ĳ�ֵ����
	MTFXPos=new int[nExtDisLen];
	MTFYPos=new int[nExtDisLen];
	dActMaxFreq=dExtendedFreq*(nExtDisLen-1);//������ʾ�������һ���ʵ��Ƶ��
	double dGapPixelNum=360.0/(nExtDisLen-1);//��ʾ������������ĺ�������
	
	
	
	CPen *oldpen;

		int f,i;
	
		for(f=0;f<nAcqTimes;f++)
		{
			if(f==0)
				oldpen=mypDC->SelectObject(&mypen[f]);//ѡ���Ӧ�����ɫ��ʵ�߱�
			else
				mypDC->SelectObject(&mypen[f]);
			
			for(i=0;i<nExtDisLen;i++)
			{
				MTFXPos[i]=150+int(dGapPixelNum*i);
				MTFYPos[i]=GetYpos(dExtendedMTFH[f*nExtendedLength+i]);
			}	
		
			mypDC->MoveTo(MTFXPos[0],MTFYPos[0]);//����һ��
			for(i=1;i<nExtDisLen;i++)
				mypDC->LineTo(MTFXPos[i],MTFYPos[i]);//������һ������м��
	
			
			
			mypDC->SelectObject(&mypen[f+10]);//ѡ���Ӧ�����ɫ�����߱�
		    
			for(i=0;i<nExtDisLen;i++)
			{
				double a=MTFXPos[i]=150+int(dGapPixelNum*i);
				double b=dExtendedMTFV[f*nExtendedLength+i];
				double c=MTFYPos[i]=GetYpos(b);
			}
		
			mypDC->MoveTo(MTFXPos[0],MTFYPos[0]);//����һ��
			for(i=1;i<nExtDisLen;i++)
				mypDC->LineTo(MTFXPos[i],MTFYPos[i]);//������һ������м��
		}

		mypDC->SelectObject(oldpen);

		delete  MTFXPos;
		delete  MTFYPos;

}

int CThroughFocusRight::GetYpos(double dMTF)
{
	return int(459.0-359.0*dMTF);
}



void CThroughFocusRight::PenCreate()
{
	mypen[0].CreatePen(PS_SOLID,1,RGB(255,0,0));//��
	mypen[10].CreatePen(PS_DOT,1,RGB(255,0,0));
	mypen[1].CreatePen(PS_SOLID,1,RGB(0,255,0));//��
	mypen[11].CreatePen(PS_DOT,1,RGB(0,255,0));
	mypen[2].CreatePen(PS_SOLID,1,RGB(0,0,255));//��
	mypen[12].CreatePen(PS_DOT,1,RGB(0,0,255));
	mypen[3].CreatePen(PS_SOLID,1,RGB(128,0,64));//筺�
	mypen[13].CreatePen(PS_DOT,1,RGB(128,0,64));
	mypen[4].CreatePen(PS_SOLID,1,RGB(0,255,255));//����
	mypen[14].CreatePen(PS_DOT,1,RGB(0,255,255));
	mypen[5].CreatePen(PS_SOLID,1,RGB(255,128,255));//�ۺ�
	mypen[15].CreatePen(PS_DOT,1,RGB(255,128,255));
	mypen[6].CreatePen(PS_SOLID,1,RGB(255,128,0));//�ٻ�
	mypen[16].CreatePen(PS_DOT,1,RGB(255,128,0));
	mypen[7].CreatePen(PS_SOLID,1,RGB(128,128,255));//����
	mypen[17].CreatePen(PS_DOT,1,RGB(128,128,255));
	mypen[8].CreatePen(PS_SOLID,1,RGB(128,0,0));//��
	mypen[18].CreatePen(PS_DOT,1,RGB(128,0,0));
	mypen[9].CreatePen(PS_SOLID,1,RGB(255,255,0));//��
	mypen[19].CreatePen(PS_DOT,1,RGB(255,255,0));
	
	

}

int CThroughFocusRight::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	// TODO: Add your specialized creation code here
	CRect rc(200,500,459,515);//�ò�������ȷ����������λ��
	m_ScrollBar1.Create(SBS_HORZ | SBS_TOPALIGN | WS_CHILD | WS_VISIBLE, 
      rc, this, 55556);//��������Ϊ����񣺺����Ӵ��ڡ��ɼ���λ�á�����ID��
	m_ScrollBar1.ShowScrollBar(FALSE);
	
	return 0;
}

void CThroughFocusRight::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	double dCurrent=dMaxDisFreq;//��õ�ǰ�����Ƶ��ֵ
	double dMaxFreq=300;//�����ʾƵ�ʣ��ݶ�Ϊ��ֵ300
	double dMinFreq=20;//��С��ʾƵ�ʣ��ݶ�Ϊ��ֵ20

	switch(nSBCode)//������Ϣ
	{
		case SB_LINELEFT://�󴥻�
			if(dCurrent<=dMinFreq)
			{
				
				Invalidate();
			}
			else
			{
				dCurrent-=20.0;
				dMaxDisFreq=dCurrent;
				
				Invalidate();

			}
			break;
		case SB_LINERIGHT://�Ҵ���
			if(dCurrent>=dMaxFreq)
			{
				
				Invalidate();
			}
			else
			{
				
				dCurrent+=20.0;
				dMaxDisFreq=dCurrent;
				
				Invalidate();

			}
			break;

	}

	CView::OnHScroll(nSBCode, nPos, pScrollBar);
}
