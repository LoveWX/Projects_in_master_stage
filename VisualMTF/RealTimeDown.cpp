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
	nDisplayMode=0;//初始显示状态，下子图不刷新
	


	
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
		DrawBackground();//画下子视图背景、网格、标注
		DrawGrid();//画下子视图坐标
		DrawPoint();//画子视图点与曲线
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
*该函数用以刷新实时采样对话框
*bMode　标识　
*pHPos 横向LSF位置坐标数组首地址
*pVPos 纵向LSF位置坐标数组首地址
*pHLSF 横向LSF数值数组首地址
*pVLSF 纵向LSF数值数组首地址
*pFreq 双向MTF频率坐标数组首地址
*pHMTF 横向MTF数值数组首地址
*PVMTF 纵向MTF数值数组首地址
nLength 数组长度
*********/

void CRealTimeDown::UpdateTrace(BOOL bMode, double *pHPos, double *pVPos, double *pHLSF, double *pVLSF, double *pFreq, double *pHMTF, double *pVMTF, int nLength)
{
	nBoxWidth=nLength;
	PosH=new double[nBoxWidth];//开辟LSF位置坐标数组空间
	PosV=new double[nBoxWidth];
	LSFH=new double[nBoxWidth];//开辟LSF空间
	LSFV=new double[nBoxWidth];
	Freq=new double[nBoxWidth];//开辟MTF频率坐标数组空间
	MTFH=new double[nBoxWidth];//开辟MTF空间
	MTFV=new double[nBoxWidth];

	for(int i=0;i<nBoxWidth;i++)
	{
		*(PosH+i)=*(pHPos+i);//赋位置坐标
		*(PosV+i)=*(pVPos+i);
		*(LSFH+i)=*(pHLSF+i);//赋LSF值
		*(LSFV+i)=*(pVLSF+i);
		*(Freq+i)=*(pFreq+i);//赋频率坐标
		*(MTFH+i)=*(pHMTF+i);//赋MTF值
		*(MTFV+i)=*(pVMTF+i);

	}

	dMaxLSF=MaxFind(LSFH,LSFV,nBoxWidth);//得到两LSF数列中的极大值
	
	ExtendMTF();//立即获得全频率范围插值后
	
	if(bMode==TRUE)
	{
		nDisplayMode=1;//显示数据已经全部生成，改变显示状态
		Invalidate();
	// TODO: Add your specialized creation code here
	}
	else return;
}

double CRealTimeDown::MaxFind(double *pArray1, double *pArray2, int nLength)//该函数用以判定得到两列LSF数组中的最大值
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

void CRealTimeDown::DrawBackground()//该函数用以描绘下子视图蓝色背景，白色图区及其上网格、标注
{
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
	mypDC->Rectangle(100,100,459,459);//画左方框
	mypDC->Rectangle(560,100,919,459);//画右方框

	mypDC->SelectObject(oldbrush);//恢复旧刷


	CPen mypen1(PS_DOT,1,RGB(0,0,0));//创建黑色虚线笔
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


	mypDC->SelectObject(oldpen);//恢复旧笔

	mypDC->SetBkColor(RGB(200,200,255));//文字背景设为蓝色底色

	CFont font1;
	font1.CreatePointFont(100,"宋体",mypDC);//创建字体
	CFont* oldfont;
	oldfont=mypDC->SelectObject(&font1);//选择新字体并保留旧字体
	mypDC->TextOut(200,50,"LINE SPREAD FUNCTION");//显示左曲线图标题
	mypDC->TextOut(630,50,"MODULATION TRANSFER FUNCTION");//显示右曲线图标题

	mypDC->SetTextColor(RGB(255,0,0));
	mypDC->TextOut(195,515,"子午方向");
	
	mypDC->SetTextColor(RGB(0,0,255));
	mypDC->TextOut(345,515,"弧矢方向");


	mypDC->SelectObject(oldfont);//恢复旧字体
}

void CRealTimeDown::DrawGrid()//该函数用以描绘下子视图坐标
{
	CDC *mypDC=GetDC();
	mypDC->SetBkColor(RGB(200,200,255));
	CString temp;
	LSFMAX=(int)(dMaxLSF/100+1)*100;//以不小于LSF最大数值的整百数作为纵轴的上限
	double MTFMAX=1.0;
	CString LSFUpString[6];//LSF的纵坐标
	CString MTFUpString[6];//MTF的纵坐标
	for(int i=0;i<6;i++)
	{
		LSFUpString[i].Format("%3d",LSFMAX*(5-i)/5);//获得LSF的纵坐标（由上到下递减）
		mypDC->TextOut(72,90+72*i,LSFUpString[i]);//标LSF纵坐标
		MTFUpString[i].Format("%.1f",MTFMAX*(5-i)/5);//获得MTF的纵坐标（由上到下递减）
		mypDC->TextOut(535,90+72*i,MTFUpString[i]);//标MTF纵坐标
	}

	CString LSFDOWNSTRING[2][3];//LSF的横坐标（两行）
	CString MTFDOWNSTRING[3];//MTF的横坐标
	for(i=0;i<3;i++)
	{
		LSFDOWNSTRING[0][i].Format("%.2f",PosH[(nBoxWidth-1)*i/2]);//获得LSF的横坐标（由左到右递增）
		mypDC->SetTextColor(RGB(255,0,0));//字体更改为红色
		mypDC->TextOut(85+180*i,465,LSFDOWNSTRING[0][i]);//标LSF横坐标
		LSFDOWNSTRING[1][i].Format("%.2f",PosV[(nBoxWidth-1)*i/2]);//获得LSF的横坐标（由左到右递增）
		mypDC->SetTextColor(RGB(0,0,255));//字体更改为蓝色
		mypDC->TextOut(85+180*i,480,LSFDOWNSTRING[1][i]);//标LSF横坐标
		MTFDOWNSTRING[i].Format("%.2f",dMaxDisFreq*i/2);//获得MTF的横坐标（由左到右递增）
		mypDC->SetTextColor(RGB(0,0,0));//字体还原为黑色
		mypDC->TextOut(545+180*i,472,MTFDOWNSTRING[i]);//标MTF横坐标

	}
}

void CRealTimeDown::DrawLSFPoint()//该函数描LSF点
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
	CPen mypen1(PS_SOLID,1,RGB(255,0,0));//创建红色笔
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
	CPen mypen2(PS_SOLID,1,RGB(0,0,255));//创建蓝色笔
	mypDC->SelectObject(&mypen2);
	mypDC->MoveTo(LSFXPos[0],LSFYPos[0]);
	for(i=1;i<nBoxWidth;i++)
		mypDC->LineTo(LSFXPos[i],LSFYPos[i]);

	mypDC->SelectObject(oldpen);
	delete  LSFXPos;
	delete  LSFYPos;
}

void CRealTimeDown::DrawMTFPoint()//该函数描MTF点
{
	CDC *mypDC=GetDC();
	
	int *MTFXPos;
	int *MTFYPos;

	int nExtDisLen=int(dMaxDisFreq/dExtendedFreq)+1;//获得当前需要显示的插值点数
	MTFXPos=new int[nExtDisLen+1];
	MTFYPos=new int[nExtDisLen+1];
	double dActMaxFreq=dExtendedFreq*(nExtDisLen-1);//所有显示点中最后一点的实际频率
	double dGapPixelNum=360.0*dActMaxFreq/dMaxDisFreq/(nExtDisLen-1);//显示点中相邻两点的横坐标间隔
	
	int i;
	for(i=0;i<nExtDisLen;i++)
	{
		MTFXPos[i]=560+int(dGapPixelNum*i);
		MTFYPos[i]=GetYpos(dExtendedMTFH[i]);
	}
	double dLastMTFH=CalLastDisMTFH(dMaxDisFreq);
	MTFXPos[nExtDisLen]=916;
	MTFYPos[nExtDisLen]=GetYpos(dLastMTFH);	

	CPen mypen1(PS_SOLID,1,RGB(255,0,0));//创建红色笔
	CPen *oldpen;
	oldpen=mypDC->SelectObject(&mypen1);
	mypDC->MoveTo(MTFXPos[0],MTFYPos[0]);//画第一点
	for(i=1;i<nExtDisLen;i++)
		mypDC->LineTo(MTFXPos[i],MTFYPos[i]);//描除最后一点外的中间点
	mypDC->LineTo(MTFXPos[nExtDisLen],MTFYPos[nExtDisLen]);//补最后一点

	for(i=0;i<nExtDisLen;i++)
	{
		MTFXPos[i]=560+int(dGapPixelNum*i);
		MTFYPos[i]=GetYpos(dExtendedMTFV[i]);
	}
	double dLastMTFV=CalLastDisMTFV(dMaxDisFreq);
	MTFXPos[nExtDisLen]=916;
	MTFYPos[nExtDisLen]=GetYpos(dLastMTFV);
	

	CPen mypen2(PS_SOLID,1,RGB(0,0,255));//创建蓝色笔
	mypDC->SelectObject(&mypen2);
	mypDC->MoveTo(MTFXPos[0],MTFYPos[0]);//画第一点
	for(i=1;i<nExtDisLen;i++)
		mypDC->LineTo(MTFXPos[i],MTFYPos[i]);//描除最后一点外的中间点
	mypDC->LineTo(MTFXPos[nExtDisLen],MTFYPos[nExtDisLen]);//补最后一点


	mypDC->SelectObject(oldpen);
	delete  MTFXPos;
	delete  MTFYPos;
}


void CRealTimeDown::ExtendMTF()
{
	CalculateFreq();//计算插值前后的频率间隔，与插值后MTF数组长度
	SpaceInit();//开辟插值后MTF数组空间

	//以下进行实际的插值运算
	int i;

	spline(dOriFreq,MTFH,getLeftSlope(),getRightSlope(),dTempSlopeH,nBoxWidth);//获得原各点斜率
	for(i=0;i<nExtendedLength;i++)
	{
		splint(dOriFreq,MTFH,dTempSlopeH,dExtFreq[i],dExtendedMTFH[i],nBoxWidth);//获得新频率坐标下MTF插值
		//double temp=dExtendedMTFH[0];
		//dExtendedMTFH[i]/=temp;//新值归一化
		//此处不归一化
	}

	spline(dOriFreq,MTFV,getLeftSlope(),getRightSlope(),dTempSlopeV,nBoxWidth);//获得原各点斜率
	for(i=0;i<nExtendedLength;i++)
	{
		splint(dOriFreq,MTFV,dTempSlopeV,dExtFreq[i],dExtendedMTFV[i],nBoxWidth);//获得新频率坐标下MTF插值
		//double temp=dExtendedMTFV[0];
		//dExtendedMTFV[i]/=temp;//新值归一化
		//此处不归一化
	}

}

void CRealTimeDown::CalculateFreq()
{
	const double dPixelWidth=PIXEL_WIDTH;//探测器像元尺寸（mm）
	CMainFrame* MainFramePoint=(CMainFrame*)((CFrameWnd*)AfxGetApp()->m_pMainWnd);
	double dAmplify=MainFramePoint->getdAmplify();
	
	dOriginalFreq=dAmplify/nBoxWidth/dPixelWidth;//计算原始频率间隔
	int temp=(int)(dOriginalFreq/5);//原始频率间隔两点间的插值数（插值原则为插值后两点间频率差为不大于5的最大可能值）
	nExtendedLength=temp*(nBoxWidth-1)+nBoxWidth;//插值后频率点数
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


double CRealTimeDown::CalLastDisMTFH(double dLastFreq)//该函数用以拟合计算采样MTF显示中用户设置最高频率下的MTF值
{
	double dLastMTFH;
	splint(dOriFreq,MTFH,dTempSlopeH,dLastFreq,dLastMTFH,nBoxWidth);
	
	return dLastMTFH;
}

double CRealTimeDown::CalLastDisMTFV(double dLastFreq)//该函数用以拟合计算采样MTF显示中用户设置最高频率下的MTF值
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
	CRect rc(600,490,876,505);//该参数用以确定滚动条的位置
	m_ScrollBar1.Create(SBS_HORZ | SBS_TOPALIGN | WS_CHILD | WS_VISIBLE, 
      rc, this, 55555);//参数依次为　风格：横向、子窗口、可见　位置　对象　ID号
	m_ScrollBar1.ShowScrollBar(FALSE);
	// TODO: Add your specialized creation code here
	
	return 0;
}



void CRealTimeDown::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
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
