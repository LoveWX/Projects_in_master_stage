// FOI.cpp : implementation file
//

#include "stdafx.h"
#include "VisualMTF.h"
#include "FOI.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFOI dialog


CFOI::CFOI(CWnd* pParent /*=NULL*/)
	: CDialog(CFOI::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFOI)
	m_dFreq1 = 0.0;
	m_dFreq2 = 0.0;
	m_dFreq3 = 0.0;
	m_dFreq4 = 0.0;
	m_dFreq5 = 0.0;
	m_dFreq6 = 0.0;
	m_dMTFH1 = 0.0;
	m_dMTFH2 = 0.0;
	m_dMTFH3 = 0.0;
	m_dMTFH4 = 0.0;
	m_dMTFH5 = 0.0;
	m_dMTFH6 = 0.0;
	m_dMTFV1 = 0.0;
	m_dMTFV2 = 0.0;
	m_dMTFV3 = 0.0;
	m_dMTFV4 = 0.0;
	m_dMTFV5 = 0.0;
	m_dMTFV6 = 0.0;
	//}}AFX_DATA_INIT
}


void CFOI::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFOI)
	DDX_Text(pDX, IDC_FreqEDIT1, m_dFreq1);
	DDX_Text(pDX, IDC_FreqEDIT2, m_dFreq2);
	DDX_Text(pDX, IDC_FreqEDIT3, m_dFreq3);
	DDX_Text(pDX, IDC_FreqEDIT4, m_dFreq4);
	DDX_Text(pDX, IDC_FreqEDIT5, m_dFreq5);
	DDX_Text(pDX, IDC_FreqEDIT6, m_dFreq6);
	DDX_Text(pDX, IDC_MTFsEDIT1, m_dMTFH1);
	DDX_Text(pDX, IDC_MTFsEDIT2, m_dMTFH2);
	DDX_Text(pDX, IDC_MTFsEDIT3, m_dMTFH3);
	DDX_Text(pDX, IDC_MTFsEDIT4, m_dMTFH4);
	DDX_Text(pDX, IDC_MTFsEDIT5, m_dMTFH5);
	DDX_Text(pDX, IDC_MTFsEDIT6, m_dMTFH6);
	DDX_Text(pDX, IDC_MTFtEDIT1, m_dMTFV1);
	DDX_Text(pDX, IDC_MTFtEDIT2, m_dMTFV2);
	DDX_Text(pDX, IDC_MTFtEDIT3, m_dMTFV3);
	DDX_Text(pDX, IDC_MTFtEDIT4, m_dMTFV4);
	DDX_Text(pDX, IDC_MTFtEDIT5, m_dMTFV5);
	DDX_Text(pDX, IDC_MTFtEDIT6, m_dMTFV6);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFOI, CDialog)
	//{{AFX_MSG_MAP(CFOI)
	ON_BN_CLICKED(IDC_REFRESH, OnRefresh)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFOI message handlers

void CFOI::Init(int nLength, double *pFreq, double *pMTFH, double *pMTFV)//该函数完成FOI对话框的数据初始化
{
	nBoxWidth=nLength;
	OriFreq=new double[nBoxWidth];
	OriMTFH=new double[nBoxWidth];
	OriMTFV=new double[nBoxWidth];
	tempslopet=new double[nBoxWidth];
	tempslopes=new double[nBoxWidth];
	for(int i=0;i<nBoxWidth;i++)
	{
		*(OriFreq+i)=*(pFreq+i);
		*(OriMTFH+i)=*(pMTFH+i);
		*(OriMTFV+i)=*(pMTFV+i);

	}
	m_dFreq1=OriFreq[1];
	m_dFreq2=OriFreq[2];
	m_dFreq3=OriFreq[3];
	m_dFreq4=OriFreq[4];
	m_dFreq5=OriFreq[5];
	m_dFreq6=OriFreq[6];
	m_dMTFH1=OriMTFH[1];
	m_dMTFH2=OriMTFH[2];
	m_dMTFH3=OriMTFH[3];
	m_dMTFH4=OriMTFH[4];
	m_dMTFH5=OriMTFH[5];
	m_dMTFH6=OriMTFH[6];
	m_dMTFV1=OriMTFV[1];
	m_dMTFV2=OriMTFV[2];
	m_dMTFV3=OriMTFV[3];
	m_dMTFV4=OriMTFV[4];
	m_dMTFV5=OriMTFV[5];
	m_dMTFV6=OriMTFV[6];
	


}



void CFOI::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void CFOI::OnRefresh() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);//刷控件获数据
	double tempf[6],anst[6],anss[6];
	tempf[0]=m_dFreq1;
	tempf[1]=m_dFreq2;
	tempf[2]=m_dFreq3;
	tempf[3]=m_dFreq4;
	tempf[4]=m_dFreq5;
	tempf[5]=m_dFreq6;
	
	spline(OriFreq,OriMTFH,getLeftSlope(),getRightSlope(),tempslopet,nBoxWidth);
	spline(OriFreq,OriMTFV,getLeftSlope(),getRightSlope(),tempslopes,nBoxWidth);

	CalcMTF(tempf,anst,anss);//计算六处频率的函数，输入第一参量为长度为六频率数组首地址，第二、三参量为长度为六MTF值首地址

	m_dMTFH1=anst[0];//将计算结果赋显示变量 
	m_dMTFH2=anst[1];
	m_dMTFH3=anst[2];
	m_dMTFH4=anst[3];
	m_dMTFH5=anst[4];
	m_dMTFH6=anst[5];
	m_dMTFV1=anss[0];
	m_dMTFV2=anss[1];
	m_dMTFV3=anss[2];
	m_dMTFV4=anss[3];
	m_dMTFV5=anss[4];
	m_dMTFV6=anss[5];

	UpdateData(FALSE);//刷新对话框
}

void CFOI::CalcMTF(double *x, double *y1, double *y2)
{
	int i;
	for(i=0;i<6;i++)
	{
		
			splint(OriFreq,OriMTFH,tempslopet,x[i],y1[i],nBoxWidth);
			splint(OriFreq,OriMTFV,tempslopes,x[i],y2[i],nBoxWidth);
		
	}
}

void CFOI::splint(double* xa,double* ya,double* y2a,double x,double &y,int lena)
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

void CFOI::spline(double *x, double *y, double yp1, double ypn, double * y2, int lena)
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

double CFOI::getLeftSlope()
{
	return 1.0e31;
}

double CFOI::getRightSlope()
{
	return 1.0e31;
}
