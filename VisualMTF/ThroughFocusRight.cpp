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
	nDisplayMode=0;//初始显示状态，下子图不刷新
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
		if(bPenInit==FALSE)//尚未创建画笔
		{
			PenCreate();//创建画笔	
			bPenInit=TRUE;//更改标示
		}
		DrawBackground();//画下子视图背景、网格、标注
		DrawPoint();//画子视图点与曲线
		DrawGrid();//画下子视图坐标
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
*该函数用以刷新实时采样对话框
*bMode　标识　
*pFreq 双向MTF频率坐标数组首地址
*pHMTF 横向MTF数值数组首地址
*pVMTF 纵向MTF数值数组首地址
nLength 数组长度
*pPos 各采样点Z轴位置
nTimes 采样次数
*********/

void CThroughFocusRight::UpdateTrace(BOOL bMode, double *pFreq, double *pHMTF, double *pVMTF, int nLength, double *pPos, int nTimes)
{
	
	int i,j;
	nBoxWidth=nLength;
	nAcqTimes=nTimes;
	Freq=new double[nBoxWidth];//开辟MTF频率坐标数组空间
	MTFH=new double[nBoxWidth*nAcqTimes];//开辟MTF空间
	MTFV=new double[nBoxWidth*nAcqTimes];
	EveryPos=new double[nAcqTimes];

	for(i=0;i<nBoxWidth;i++)
	{
		*(Freq+i)=*(pFreq+i);//赋频率坐标
		
	}

	for(i=0;i<nAcqTimes;i++)
	{
		*(EveryPos+i)=*(pPos+i);//赋位置坐标
		for(j=0;j<nBoxWidth;j++)
		{
			*(MTFH+i*nBoxWidth+j)=*(pHMTF+i*nBoxWidth+j);//赋MTF值（多簇）
			*(MTFV+i*nBoxWidth+j)=*(pVMTF+i*nBoxWidth+j);
		}
		
	}


	
	ExtendMTF();//立即获得全频率范围插值后
	
	if(bMode==TRUE)
	{
		nDisplayMode=1;//显示数据已经全部生成，改变显示状态
		Invalidate();
	// TODO: Add your specialized creation code here
	}
	else return;	
}



void CThroughFocusRight::ExtendMTF()
{
	CalculateFreq();//计算插值前后的频率间隔，与插值后MTF数组长度
	SpaceInit();//开辟插值后MTF数组空间

	//以下进行实际的插值运算
	int f,i;
	double *tempsor,*tempdes;
	tempsor=new double[nBoxWidth];//开辟作一次fft变换的原始数组空间
	tempdes=new double[nExtendedLength];//开辟作一次fft变换的结果空间

	
	for(f=0;f<nAcqTimes;f++)
	{
		for(i=0;i<nBoxWidth;i++)
			*(tempsor+i)=*(MTFH+f*nBoxWidth+i);//得当前变换需要的MTF行数据
		spline(dOriFreq,tempsor,getLeftSlope(),getRightSlope(),dTempSlopeH,nBoxWidth);//获得原各点斜率
		
		for(i=0;i<nExtendedLength;i++)
		{
			splint(dOriFreq,tempsor,dTempSlopeH,dExtFreq[i],tempdes[i],nBoxWidth);//获得新频率坐标下MTF插值
			//double firstdes=tempdes[0];
			//*(dExtendedMTFH+f*nExtendedLength+i)=tempdes[i]/firstdes;//新值归一化
			*(dExtendedMTFH+f*nExtendedLength+i)=tempdes[i];//不归一化
		}

		

		for(i=0;i<nBoxWidth;i++)
			*(tempsor+i)=*(MTFV+f*nBoxWidth+i);//得当前变换需要的MTF行数据
		spline(dOriFreq,tempsor,getLeftSlope(),getRightSlope(),dTempSlopeV,nBoxWidth);//获得原各点斜率
	
		for(i=0;i<nExtendedLength;i++)
		{
			splint(dOriFreq,tempsor,dTempSlopeV,dExtFreq[i],tempdes[i],nBoxWidth);//获得新频率坐标下MTF插值
			//double firstdes=tempdes[0];
			//*(dExtendedMTFV+f*nExtendedLength+i)=tempdes[i]/firstdes;//新值归一化
			*(dExtendedMTFV+f*nExtendedLength+i)=tempdes[i];//不归一化
		}
		
			
	}

	delete[] tempsor;
	delete[] tempdes;
}

void CThroughFocusRight::CalculateFreq()
{
	const double dPixelWidth=PIXEL_WIDTH;//探测器像元尺寸（mm）
	CMainFrame* MainFramePoint=(CMainFrame*)((CFrameWnd*)AfxGetApp()->m_pMainWnd);
	double dAmplify=MainFramePoint->getdAmplify();
	
	dOriginalFreq=dAmplify/nBoxWidth/dPixelWidth;//计算原始频率间隔
	int temp=(int)(dOriginalFreq/10);//原始频率间隔两点间的插值数（插值原则为插值后两点间频率差为不大于10的最大可能值）
	nExtendedLength=temp*(nBoxWidth-1)+nBoxWidth;//插值后频率点数
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

	dExtendedMTFH=new double[nExtendedLength*nAcqTimes];//MTF插值所有数值需保留
	dExtendedMTFV=new double[nExtendedLength*nAcqTimes];
	dTempSlopeH=new double[nBoxWidth];//中间结果不作全部保留
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

void CThroughFocusRight::DrawBackground()//该函数用以描绘右子视图蓝色背景，白色图区及其上网格、标注
{
	int i;
	CDC *mypDC=GetDC();
	CRect rc;
	GetClientRect(&rc);//获取下子视图大小


	CBrush mybrush1,mybrush2;
	mybrush1.CreateSolidBrush(RGB(200,200,255));//创建蓝色刷
	CBrush *oldbrush;
	oldbrush=mypDC->SelectObject(&mybrush1);//选择新刷，同时保留旧刷
	mypDC->Rectangle(rc.left-1,rc.top-1,rc.right+1,rc.bottom+1);//全视图染底色

	mybrush2.CreateSolidBrush(RGB(255,255,255));//创建白色刷
	mypDC->SelectObject(&mybrush2);//选择白刷
	mypDC->Rectangle(150,100,509,459);//画方框
	

	mypDC->SelectObject(oldbrush);//恢复旧刷


	CPen mypen1(PS_DOT,1,RGB(0,0,0));//创建黑色虚线笔
	CPen *oldpen;
	oldpen=mypDC->SelectObject(&mypen1);
	for(i=0;i<9;i++)
	{
		mypDC->MoveTo(150,136+36*i);
		mypDC->LineTo(509,136+36*i);
		mypDC->MoveTo(186+36*i,100);
		mypDC->LineTo(186+36*i,459);
	}
	mypDC->SetBkColor(RGB(200,200,255));//文字背景设为蓝色底色
	for(i=0;i<nAcqTimes;i++)
	{
		mypDC->SelectObject(&mypen[i]);
		mypDC->MoveTo(80+i*80,570);
		mypDC->LineTo(130+i*80,570);

		mypDC->SelectObject(&mypen[10+i]);
		mypDC->MoveTo(80+i*80,600);
		mypDC->LineTo(130+i*80,600);
	
	}


	mypDC->SelectObject(oldpen);//恢复旧笔

	mypDC->SetBkColor(RGB(200,200,255));//文字背景设为蓝色底色

	CFont font1;
	font1.CreatePointFont(100,"宋体",mypDC);//创建字体
	CFont* oldfont;
	oldfont=mypDC->SelectObject(&font1);//选择新字体并保留旧字体

	mypDC->TextOut(220,50,"MODULATION TRANSFER FUNCTION");//显示右曲线图标题

	mypDC->TextOut(20,562,"子午方向");
	mypDC->TextOut(20,592,"弧矢方向");
	mypDC->TextOut(18,622,"  位置  ");

	for(i=0;i<nAcqTimes;i++)
	{
		CString temp;
		double curpos=*(EveryPos+i);
		temp.Format("%.3f",curpos);
		mypDC->TextOut(85+80*i,622,temp);
	
	}



	mypDC->SelectObject(oldfont);//恢复旧字体*/
}

void CThroughFocusRight::DrawGrid()//该函数用以描绘右子视图坐标
{
	CDC *mypDC=GetDC();
	mypDC->SetBkColor(RGB(200,200,255));
	CString temp;
	
	double MTFMAX=1.0;
	CString MTFUpString[6];//MTF的纵坐标
	for(int i=0;i<6;i++)
	{
		MTFUpString[i].Format("%.1f",MTFMAX*(5-i)/5);//获得MTF的纵坐标（由上到下递减）
		mypDC->TextOut(125,90+72*i,MTFUpString[i]);//标MTF纵坐标
	}

	
	CString MTFDOWNSTRING[3];//MTF的横坐标
	for(i=0;i<3;i++)
	{
		MTFDOWNSTRING[i].Format("%.2f",dActMaxFreq*i/2);//获得MTF的横坐标（由左到右递增）//此处由于最后不补点，极大频率值为接近设定值的一个大值
		mypDC->SetTextColor(RGB(0,0,0));//字体还原为黑色
		mypDC->TextOut(135+180*i,472,MTFDOWNSTRING[i]);//标MTF横坐标

	}
}


void CThroughFocusRight::DrawPoint()
{
	

	DrawMTFPoint();
}

void CThroughFocusRight::DrawMTFPoint()//该函数描MTF点
{
	CDC *mypDC=GetDC();
	
	int *MTFXPos;
	int *MTFYPos;



	int nExtDisLen=int(dMaxDisFreq/dExtendedFreq);//获得当前需要显示的插值点数
	MTFXPos=new int[nExtDisLen];
	MTFYPos=new int[nExtDisLen];
	dActMaxFreq=dExtendedFreq*(nExtDisLen-1);//所有显示点中最后一点的实际频率
	double dGapPixelNum=360.0/(nExtDisLen-1);//显示点中相邻两点的横坐标间隔
	
	
	
	CPen *oldpen;

		int f,i;
	
		for(f=0;f<nAcqTimes;f++)
		{
			if(f==0)
				oldpen=mypDC->SelectObject(&mypen[f]);//选择对应序号颜色的实线笔
			else
				mypDC->SelectObject(&mypen[f]);
			
			for(i=0;i<nExtDisLen;i++)
			{
				MTFXPos[i]=150+int(dGapPixelNum*i);
				MTFYPos[i]=GetYpos(dExtendedMTFH[f*nExtendedLength+i]);
			}	
		
			mypDC->MoveTo(MTFXPos[0],MTFYPos[0]);//画第一点
			for(i=1;i<nExtDisLen;i++)
				mypDC->LineTo(MTFXPos[i],MTFYPos[i]);//描除最后一点外的中间点
	
			
			
			mypDC->SelectObject(&mypen[f+10]);//选择对应序号颜色的虚线笔
		    
			for(i=0;i<nExtDisLen;i++)
			{
				double a=MTFXPos[i]=150+int(dGapPixelNum*i);
				double b=dExtendedMTFV[f*nExtendedLength+i];
				double c=MTFYPos[i]=GetYpos(b);
			}
		
			mypDC->MoveTo(MTFXPos[0],MTFYPos[0]);//画第一点
			for(i=1;i<nExtDisLen;i++)
				mypDC->LineTo(MTFXPos[i],MTFYPos[i]);//描除最后一点外的中间点
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
	mypen[0].CreatePen(PS_SOLID,1,RGB(255,0,0));//红
	mypen[10].CreatePen(PS_DOT,1,RGB(255,0,0));
	mypen[1].CreatePen(PS_SOLID,1,RGB(0,255,0));//绿
	mypen[11].CreatePen(PS_DOT,1,RGB(0,255,0));
	mypen[2].CreatePen(PS_SOLID,1,RGB(0,0,255));//蓝
	mypen[12].CreatePen(PS_DOT,1,RGB(0,0,255));
	mypen[3].CreatePen(PS_SOLID,1,RGB(128,0,64));//绛红
	mypen[13].CreatePen(PS_DOT,1,RGB(128,0,64));
	mypen[4].CreatePen(PS_SOLID,1,RGB(0,255,255));//淡蓝
	mypen[14].CreatePen(PS_DOT,1,RGB(0,255,255));
	mypen[5].CreatePen(PS_SOLID,1,RGB(255,128,255));//粉红
	mypen[15].CreatePen(PS_DOT,1,RGB(255,128,255));
	mypen[6].CreatePen(PS_SOLID,1,RGB(255,128,0));//橘黄
	mypen[16].CreatePen(PS_DOT,1,RGB(255,128,0));
	mypen[7].CreatePen(PS_SOLID,1,RGB(128,128,255));//中蓝
	mypen[17].CreatePen(PS_DOT,1,RGB(128,128,255));
	mypen[8].CreatePen(PS_SOLID,1,RGB(128,0,0));//褐
	mypen[18].CreatePen(PS_DOT,1,RGB(128,0,0));
	mypen[9].CreatePen(PS_SOLID,1,RGB(255,255,0));//黄
	mypen[19].CreatePen(PS_DOT,1,RGB(255,255,0));
	
	

}

int CThroughFocusRight::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	// TODO: Add your specialized creation code here
	CRect rc(200,500,459,515);//该参数用以确定滚动条的位置
	m_ScrollBar1.Create(SBS_HORZ | SBS_TOPALIGN | WS_CHILD | WS_VISIBLE, 
      rc, this, 55556);//参数依次为　风格：横向、子窗口、可见　位置　对象　ID号
	m_ScrollBar1.ShowScrollBar(FALSE);
	
	return 0;
}

void CThroughFocusRight::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	double dCurrent=dMaxDisFreq;//获得当前的最大频率值
	double dMaxFreq=300;//最大显示频率，暂定为定值300
	double dMinFreq=20;//最小显示频率，暂定为定值20

	switch(nSBCode)//分析消息
	{
		case SB_LINELEFT://左触击
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
		case SB_LINERIGHT://右触击
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
