// RealTimeDown.cpp : implementation file
//

#include "stdafx.h"
#include "VisualMTF.h"
#include "RealTimeDown.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define PIXEL_WIDTH 0.0098
/////////////////////////////////////////////////////////////////////////////
// CRealTimeDown

IMPLEMENT_DYNCREATE(CRealTimeDown, CView)

CRealTimeDown::CRealTimeDown()
{
	dExtendedMTFH=NULL;
	dExtendedMTFV=NULL;
	dTempSlopeH=NULL;
	dTempSlopeV=NULL;

	dMaxDisFreq=100.0;
	nDisplayMode=0;//��ʼ��ʾ״̬������ͼ��ˢ��
	


	
}

CRealTimeDown::~CRealTimeDown()
{
}


BEGIN_MESSAGE_MAP(CRealTimeDown, CView)
	//{{AFX_MSG_MAP(CRealTimeDown)
	ON_WM_CREATE()
	ON_WM_HSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRealTimeDown drawing

void CRealTimeDown::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	if(nDisplayMode==0)
		return;
	else
	{
		DrawBackground();//��������ͼ���������񡢱�ע
		DrawGrid();//��������ͼ����
		DrawPoint();//������ͼ��������
		m_ScrollBar1.ShowScrollBar(TRUE);	
	}
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CRealTimeDown diagnostics

#ifdef _DEBUG
void CRealTimeDown::AssertValid() const
{
	CView::AssertValid();
}

void CRealTimeDown::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CRealTimeDown message handlers

/*********
*�ú�������ˢ��ʵʱ�����Ի���
*bMode����ʶ��
*pHPos ����LSFλ�����������׵�ַ
*pVPos ����LSFλ�����������׵�ַ
*pHLSF ����LSF��ֵ�����׵�ַ
*pVLSF ����LSF��ֵ�����׵�ַ
*pFreq ˫��MTFƵ�����������׵�ַ
*pHMTF ����MTF��ֵ�����׵�ַ
*PVMTF ����MTF��ֵ�����׵�ַ
nLength ���鳤��
*********/

void CRealTimeDown::UpdateTrace(BOOL bMode, double *pHPos, double *pVPos, double *pHLSF, double *pVLSF, double *pFreq, double *pHMTF, double *pVMTF, int nLength)
{
	nBoxWidth=nLength;
	PosH=new double[nBoxWidth];//����LSFλ����������ռ�
	PosV=new double[nBoxWidth];
	LSFH=new double[nBoxWidth];//����LSF�ռ�
	LSFV=new double[nBoxWidth];
	Freq=new double[nBoxWidth];//����MTFƵ����������ռ�
	MTFH=new double[nBoxWidth];//����MTF�ռ�
	MTFV=new double[nBoxWidth];

	for(int i=0;i<nBoxWidth;i++)
	{
		*(PosH+i)=*(pHPos+i);//��λ������
		*(PosV+i)=*(pVPos+i);
		*(LSFH+i)=*(pHLSF+i);//��LSFֵ
		*(LSFV+i)=*(pVLSF+i);
		*(Freq+i)=*(pFreq+i);//��Ƶ������
		*(MTFH+i)=*(pHMTF+i);//��MTFֵ
		*(MTFV+i)=*(pVMTF+i);

	}

	dMaxLSF=MaxFind(LSFH,LSFV,nBoxWidth);//�õ���LSF�����еļ���ֵ
	
	ExtendMTF();//�������ȫƵ�ʷ�Χ��ֵ��
	
	if(bMode==TRUE)
	{
		nDisplayMode=1;//��ʾ�����Ѿ�ȫ�����ɣ��ı���ʾ״̬
		Invalidate();
	// TODO: Add your specialized creation code here
	}
	else return;
}

double CRealTimeDown::MaxFind(double *pArray1, double *pArray2, int nLength)//�ú��������ж��õ�����LSF�����е����ֵ
{
	double dMax=0.0;
	for(int i=0;i<nLength;i++)
	{
		if(*(pArray1+i)>dMax)
			dMax=*(pArray1+i);
		if(*(pArray1+i)>dMax)
			dMax=*(pArray1+i);
	}
	return dMax;
}

void CRealTimeDown::DrawBackground()//�ú����������������ͼ��ɫ��������ɫͼ�����������񡢱�ע
{
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
	mypDC->Rectangle(100,100,459,459);//���󷽿�
	mypDC->Rectangle(560,100,919,459);//���ҷ���

	mypDC->SelectObject(oldbrush);//�ָ���ˢ


	CPen mypen1(PS_DOT,1,RGB(0,0,0));//������ɫ���߱�
	CPen *oldpen;
	oldpen=mypDC->SelectObject(&mypen1);
	for(int i=0;i<9;i++)
	{
		mypDC->MoveTo(100,136+36*i);
		mypDC->LineTo(459,136+36*i);
		mypDC->MoveTo(560,136+36*i);
		mypDC->LineTo(919,136+36*i);
		mypDC->MoveTo(136+36*i,100);
		mypDC->LineTo(136+36*i,459);
		mypDC->MoveTo(596+36*i,100);
		mypDC->LineTo(596+36*i,459);
	}

	CPen mypen2(PS_SOLID,1,RGB(255,0,0));
	mypDC->SelectObject(&mypen2);
	mypDC->MoveTo(120,520);
	mypDC->LineTo(180,520);

	CPen mypen3(PS_SOLID,1,RGB(0,0,255));
	mypDC->SelectObject(&mypen3);
	mypDC->MoveTo(270,520);
	mypDC->LineTo(330,520);


	mypDC->SelectObject(oldpen);//�ָ��ɱ�

	mypDC->SetBkColor(RGB(200,200,255));//���ֱ�����Ϊ��ɫ��ɫ

	CFont font1;
	font1.CreatePointFont(100,"����",mypDC);//��������
	CFont* oldfont;
	oldfont=mypDC->SelectObject(&font1);//ѡ�������岢����������
	mypDC->TextOut(200,50,"LINE SPREAD FUNCTION");//��ʾ������ͼ����
	mypDC->TextOut(630,50,"MODULATION TRANSFER FUNCTION");//��ʾ������ͼ����

	mypDC->SetTextColor(RGB(255,0,0));
	mypDC->TextOut(195,515,"���緽��");
	
	mypDC->SetTextColor(RGB(0,0,255));
	mypDC->TextOut(345,515,"��ʸ����");


	mypDC->SelectObject(oldfont);//�ָ�������
}

void CRealTimeDown::DrawGrid()//�ú����������������ͼ����
{
	CDC *mypDC=GetDC();
	mypDC->SetBkColor(RGB(200,200,255));
	CString temp;
	LSFMAX=(int)(dMaxLSF/100+1)*100;//�Բ�С��LSF�����ֵ����������Ϊ���������
	double MTFMAX=1.0;
	CString LSFUpString[6];//LSF��������
	CString MTFUpString[6];//MTF��������
	for(int i=0;i<6;i++)
	{
		LSFUpString[i].Format("%3d",LSFMAX*(5-i)/5);//���LSF�������꣨���ϵ��µݼ���
		mypDC->TextOut(72,90+72*i,LSFUpString[i]);//��LSF������
		MTFUpString[i].Format("%.1f",MTFMAX*(5-i)/5);//���MTF�������꣨���ϵ��µݼ���
		mypDC->TextOut(535,90+72*i,MTFUpString[i]);//��MTF������
	}

	CString LSFDOWNSTRING[2][3];//LSF�ĺ����꣨���У�
	CString MTFDOWNSTRING[3];//MTF�ĺ�����
	for(i=0;i<3;i++)
	{
		LSFDOWNSTRING[0][i].Format("%.2f",PosH[(nBoxWidth-1)*i/2]);//���LSF�ĺ����꣨�����ҵ�����
		mypDC->SetTextColor(RGB(255,0,0));//�������Ϊ��ɫ
		mypDC->TextOut(85+180*i,465,LSFDOWNSTRING[0][i]);//��LSF������
		LSFDOWNSTRING[1][i].Format("%.2f",PosV[(nBoxWidth-1)*i/2]);//���LSF�ĺ����꣨�����ҵ�����
		mypDC->SetTextColor(RGB(0,0,255));//�������Ϊ��ɫ
		mypDC->TextOut(85+180*i,480,LSFDOWNSTRING[1][i]);//��LSF������
		MTFDOWNSTRING[i].Format("%.2f",dMaxDisFreq*i/2);//���MTF�ĺ����꣨�����ҵ�����
		mypDC->SetTextColor(RGB(0,0,0));//���廹ԭΪ��ɫ
		mypDC->TextOut(545+180*i,472,MTFDOWNSTRING[i]);//��MTF������

	}
}

void CRealTimeDown::DrawLSFPoint()//�ú�����LSF��
{
	CDC *mypDC=GetDC();
	
	int *LSFXPos;
	int *LSFYPos;
	LSFXPos=new int[nBoxWidth];
	LSFYPos=new int[nBoxWidth];
	
	for(int i=0;i<nBoxWidth;i++)
	{
		LSFXPos[i]=100+359*i/(nBoxWidth-1);
		LSFYPos[i]=int(459-1.0*LSFH[i]/LSFMAX*359);
	}
	CPen mypen1(PS_SOLID,1,RGB(255,0,0));//������ɫ��
	CPen *oldpen;
	oldpen=mypDC->SelectObject(&mypen1);
	mypDC->MoveTo(LSFXPos[0],LSFYPos[0]);
	for(i=1;i<nBoxWidth;i++)
		mypDC->LineTo(LSFXPos[i],LSFYPos[i]);

	for(i=0;i<nBoxWidth;i++)
	{
		LSFXPos[i]=100+359*i/(nBoxWidth-1);
		LSFYPos[i]=int(459-1.0*LSFV[i]/LSFMAX*359);
	}
	CPen mypen2(PS_SOLID,1,RGB(0,0,255));//������ɫ��
	mypDC->SelectObject(&mypen2);
	mypDC->MoveTo(LSFXPos[0],LSFYPos[0]);
	for(i=1;i<nBoxWidth;i++)
		mypDC->LineTo(LSFXPos[i],LSFYPos[i]);

	mypDC->SelectObject(oldpen);
	delete  LSFXPos;
	delete  LSFYPos;
}

void CRealTimeDown::DrawMTFPoint()//�ú�����MTF��
{
	CDC *mypDC=GetDC();
	
	int *MTFXPos;
	int *MTFYPos;

	int nExtDisLen=int(dMaxDisFreq/dExtendedFreq)+1;//��õ�ǰ��Ҫ��ʾ�Ĳ�ֵ����
	MTFXPos=new int[nExtDisLen+1];
	MTFYPos=new int[nExtDisLen+1];
	double dActMaxFreq=dExtendedFreq*(nExtDisLen-1);//������ʾ�������һ���ʵ��Ƶ��
	double dGapPixelNum=360.0*dActMaxFreq/dMaxDisFreq/(nExtDisLen-1);//��ʾ������������ĺ�������
	
	int i;
	for(i=0;i<nExtDisLen;i++)
	{
		MTFXPos[i]=560+int(dGapPixelNum*i);
		MTFYPos[i]=GetYpos(dExtendedMTFH[i]);
	}
	double dLastMTFH=CalLastDisMTFH(dMaxDisFreq);
	MTFXPos[nExtDisLen]=916;
	MTFYPos[nExtDisLen]=GetYpos(dLastMTFH);	

	CPen mypen1(PS_SOLID,1,RGB(255,0,0));//������ɫ��
	CPen *oldpen;
	oldpen=mypDC->SelectObject(&mypen1);
	mypDC->MoveTo(MTFXPos[0],MTFYPos[0]);//����һ��
	for(i=1;i<nExtDisLen;i++)
		mypDC->LineTo(MTFXPos[i],MTFYPos[i]);//������һ������м��
	mypDC->LineTo(MTFXPos[nExtDisLen],MTFYPos[nExtDisLen]);//�����һ��

	for(i=0;i<nExtDisLen;i++)
	{
		MTFXPos[i]=560+int(dGapPixelNum*i);
		MTFYPos[i]=GetYpos(dExtendedMTFV[i]);
	}
	double dLastMTFV=CalLastDisMTFV(dMaxDisFreq);
	MTFXPos[nExtDisLen]=916;
	MTFYPos[nExtDisLen]=GetYpos(dLastMTFV);
	

	CPen mypen2(PS_SOLID,1,RGB(0,0,255));//������ɫ��
	mypDC->SelectObject(&mypen2);
	mypDC->MoveTo(MTFXPos[0],MTFYPos[0]);//����һ��
	for(i=1;i<nExtDisLen;i++)
		mypDC->LineTo(MTFXPos[i],MTFYPos[i]);//������һ������м��
	mypDC->LineTo(MTFXPos[nExtDisLen],MTFYPos[nExtDisLen]);//�����һ��


	mypDC->SelectObject(oldpen);
	delete  MTFXPos;
	delete  MTFYPos;
}


void CRealTimeDown::ExtendMTF()
{
	CalculateFreq();//�����ֵǰ���Ƶ�ʼ�������ֵ��MTF���鳤��
	SpaceInit();//���ٲ�ֵ��MTF����ռ�

	//���½���ʵ�ʵĲ�ֵ����
	int i;

	spline(dOriFreq,MTFH,getLeftSlope(),getRightSlope(),dTempSlopeH,nBoxWidth);//���ԭ����б��
	for(i=0;i<nExtendedLength;i++)
	{
		splint(dOriFreq,MTFH,dTempSlopeH,dExtFreq[i],dExtendedMTFH[i],nBoxWidth);//�����Ƶ��������MTF��ֵ
		//double temp=dExtendedMTFH[0];
		//dExtendedMTFH[i]/=temp;//��ֵ��һ��
		//�˴�����һ��
	}

	spline(dOriFreq,MTFV,getLeftSlope(),getRightSlope(),dTempSlopeV,nBoxWidth);//���ԭ����б��
	for(i=0;i<nExtendedLength;i++)
	{
		splint(dOriFreq,MTFV,dTempSlopeV,dExtFreq[i],dExtendedMTFV[i],nBoxWidth);//�����Ƶ��������MTF��ֵ
		//double temp=dExtendedMTFV[0];
		//dExtendedMTFV[i]/=temp;//��ֵ��һ��
		//�˴�����һ��
	}

}

void CRealTimeDown::CalculateFreq()
{
	const double dPixelWidth=PIXEL_WIDTH;//̽������Ԫ�ߴ磨mm��
	CMainFrame* MainFramePoint=(CMainFrame*)((CFrameWnd*)AfxGetApp()->m_pMainWnd);
	double dAmplify=MainFramePoint->getdAmplify();
	
	dOriginalFreq=dAmplify/nBoxWidth/dPixelWidth;//����ԭʼƵ�ʼ��
	int temp=(int)(dOriginalFreq/5);//ԭʼƵ�ʼ�������Ĳ�ֵ������ֵԭ��Ϊ��ֵ�������Ƶ�ʲ�Ϊ������5��������ֵ��
	nExtendedLength=temp*(nBoxWidth-1)+nBoxWidth;//��ֵ��Ƶ�ʵ���
	dExtendedFreq=dOriginalFreq*(nBoxWidth-1)/(nExtendedLength-1);
}

void CRealTimeDown::SpaceInit()
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
	dExtendedMTFH=new double[nExtendedLength];
	dExtendedMTFV=new double[nExtendedLength];
	dTempSlopeH=new double[nBoxWidth];
	dTempSlopeV=new double[nBoxWidth];
	dOriFreq=new double[nBoxWidth];	
	dExtFreq=new double[nExtendedLength];	
	int i;
	dOriFreq[0]=0.0;
	dExtFreq[0]=0.0;
	for(i=1;i<nBoxWidth;i++)
	{
		dOriFreq[i]=dOriFreq[i-1]+dOriginalFreq;
	}
	for(i=1;i<nExtendedLength;i++)
	{
		dExtFreq[i]=dExtFreq[i-1]+dExtendedFreq;
	}
}

double CRealTimeDown::getLeftSlope()
{
	return 1.0e31;
}





double CRealTimeDown::getRightSlope()
{
	return 1.0e31;
}

void CRealTimeDown::spline(double *x, double *y, double yp1, double ypn, double * y2, int lena)
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

void CRealTimeDown::splint(double* xa,double* ya,double* y2a,double x,double &y,int lena)
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

void CRealTimeDown::DrawPoint()
{
	DrawLSFPoint();
	DrawMTFPoint();
}	


double CRealTimeDown::CalLastDisMTFH(double dLastFreq)//�ú���������ϼ������MTF��ʾ���û��������Ƶ���µ�MTFֵ
{
	double dLastMTFH;
	splint(dOriFreq,MTFH,dTempSlopeH,dLastFreq,dLastMTFH,nBoxWidth);
	
	return dLastMTFH;
}

double CRealTimeDown::CalLastDisMTFV(double dLastFreq)//�ú���������ϼ������MTF��ʾ���û��������Ƶ���µ�MTFֵ
{
	double dLastMTFV;
	splint(dOriFreq,MTFV,dTempSlopeV,dLastFreq,dLastMTFV,nBoxWidth);
	
	return dLastMTFV;
}

int CRealTimeDown::GetYpos(double dMTF)
{
	return int(459-dMTF*359);

}



int CRealTimeDown::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	CRect rc(600,490,876,505);//�ò�������ȷ����������λ��
	m_ScrollBar1.Create(SBS_HORZ | SBS_TOPALIGN | WS_CHILD | WS_VISIBLE, 
      rc, this, 55555);//��������Ϊ����񣺺����Ӵ��ڡ��ɼ���λ�á�����ID��
	m_ScrollBar1.ShowScrollBar(FALSE);
	// TODO: Add your specialized creation code here
	
	return 0;
}



void CRealTimeDown::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
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
