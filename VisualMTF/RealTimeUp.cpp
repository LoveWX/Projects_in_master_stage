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
	bCameraInit=MainFramePoint->getbCamInit();//获得相机初始状态
	hBoard=MainFramePoint->getCameraHandle();//获得相机句柄
	lpLinear=MainFramePoint->getCameraBuffer();//获得相机存储空间指针
	dAmplify=MainFramePoint->getdAmplify();//获得显微系统放大率
	dPixel=MainFramePoint->getdPixel();//获得相机像元尺寸
	nBoxHeight=MainFramePoint->getnStarHeight();//获得十字叉高
	nBoxWidth=MainFramePoint->getnStarWidth();//获得十字叉宽
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

/*	if(bCameraInit==FALSE)//相机初始化判定
	{
		sprintf(cItemText,"相机初试未完成。任务终止！");
		MessageBox(cItemText);
		return;
	}
	
	MemoryCheck();
	long lImageSize=WIDTH*HEIGHT;


	SetMemoryZero();
	//以下连续采样
	lNum=okGetBufferSize(hBoard, (void **)&lpLinear, &dwSize);//获得当前状态允许拍摄的最大幅数
	long lFrameNum=FRAMENUM;
	if( lFrameNum > lNum ) //防止需要采集的图像帧数大于当前BUFFER容许存放的图像帧数
	{
		lFrameNum = lNum;
		sprintf(cItemText,"警告：相机当前缓存容量低于18幅，当前仅为%d幅",lFrameNum);
		MessageBox(cItemText);
	}
	okCaptureTo(hBoard,BUFFER,0,lFrameNum); //采集指定数量帧图像数据(首地址为lpLinear) 
	okGetCaptureStatus(hBoard,1); //获取采集结束 
	
	//以下获采样连续图样数据的平均值
	
	for(i=0;i<lFrameNum;i++)//循环采样次数
		for(j=0;j<lImageSize;j++)
				pData[i]+=*(lpLinear+i*lImageSize+j);//逐帧累加

	for(j=0;j<lImageSize;j++)
		pData[j]/=lFrameNum;//取均值
	
	int xpos,ypos;
	CenterFind(pData,xpos,ypos,HEIGHT,WIDTH);//获得平均后图像的中心点

	
	AreaSelect(pData,pDataH,pDataV,nBoxWidth,nBoxHeight,xpos,ypos,WIDTH);//获得两个方向图像区域
	
	
	
	for(j=0;j<nBoxWidth;j++)//赋LSF初值
	{
		*(LSFH+j)=0;
		*(LSFV+j)=0;
	}
	for(j=0;j<nBoxWidth;j++)//获得两个方向的LSF
		for(i=0;i<nBoxHeight;i++)
		{
			*(LSFH+j)=*(LSFH+j)+*(pDataH+i*nBoxWidth+j);//横向LSF值
			*(LSFV+j)=*(LSFV+j)+*(pDataV+i*nBoxWidth+j);//纵向LSF值
		}
	
	
	
	for(j=0;j<nBoxWidth;j++)//赋MTF初值
	{
		*(MTFH+j)=0;
		*(MTFV+j)=0;
	}
	



	fft(LSFH,FtDataRe,FtDataIm,nBoxWidth);
	for(j=0;j<nBoxWidth;j++)
	{
		*(MTFH+j)=sqrt( (*(FtDataRe+j)) * (*(FtDataRe+j)) + (*(FtDataIm+j)) * (*(FtDataIm+j)) );//归一化前值
		*(MTFH+j)/=*(MTFH+0);//归一化后值
	}
	fft(LSFV,FtDataRe,FtDataIm,nBoxWidth);
	for(j=0;j<nBoxWidth;j++)
	{
		*(MTFV+j)=sqrt( (*(FtDataRe+j)) * (*(FtDataRe+j)) + (*(FtDataIm+j)) * (*(FtDataIm+j)) );//归一化前值
		*(MTFV+j)/=*(MTFV+0);//归一化后值
	}
	
	
	for(j=0;j<nBoxWidth;j++)
	{
		*(PosH+j)=(xpos+j-nBoxWidth/2+1)*dPixel/dAmplify;//获LSF位置坐标
		*(PosV+j)=(ypos+j-nBoxWidth/2+1)*dPixel/dAmplify;
		*(Freq+j)=j*dAmplify/nBoxWidth/dPixel;//获MTF频率坐标
	}
*/
	//需要绘制的是PosH~LSFH，PosV~LSFV，Freq~MTFH~MTFV

	PosH=new double[nBoxWidth];//开辟LSF位置坐标数组空间
	PosV=new double[nBoxWidth];
	LSFH=new double[nBoxWidth];//开辟LSF空间
	LSFV=new double[nBoxWidth];
	Freq=new double[nBoxWidth];//开辟MTF频率坐标数组空间
	MTFH=new double[nBoxWidth];//开辟MTF空间
	MTFV=new double[nBoxWidth];

	for(i=0;i<nBoxWidth;i++)
	{
		*(PosH+i)=1.0+i*0.2;
		*(PosV+i)=3.0-i*0.1;
		*(LSFH+i)=250.0+i*20;
		*(LSFV+i)=320.0+i*10;
		//*(Freq+i)=40.0*i;
		*(Freq+i)=i*dAmplify/nBoxWidth/dPixel;//获MTF频率坐标
		*(MTFH+i)=1.0-i*0.025;
		*(MTFV+i)=1.0-i*0.02;
	}

	

	CRealTimeFrame* FrameWndPoint=(CRealTimeFrame*)(GetParentFrame());//获父框
	CRealTimeDown* DownViewPoint=(CRealTimeDown*)(FrameWndPoint->GetDownView());//获下子视图
	
	DownViewPoint->UpdateTrace(TRUE,PosH,PosV,LSFH,LSFV,Freq,MTFH,MTFV,nBoxWidth);//视图刷新并传递参量，参数内容见函数声明
	
}

/*****************************
* *image 图像数据指针
* &x     极值点横坐标
* &y     极值点纵坐标
* height 图像高度
* width  图像宽度
*****************************/
void CRealTimeUp::CenterFind(double *image, int &x, int &y, int height, int width)//该函数用于判断平均图像数据极值点位置
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
* *image 图像数据指针
* *outimageH 输出的横向图像首地址
* *outimageV 输出的纵向图像首地址 
* areawidth 输出图像宽度
* areaheight  输出图像高度
* centerx 极值中心点横坐标
* centery 极值中心点纵坐标
* imagewidth 原图像宽度
*****************************/
void CRealTimeUp::AreaSelect(double *image, double *outimageH, double *outimageV, int areawidth, int areaheight, int centerx, int centery, int imagewidth)//该函数在获取图像极值点位置后
{
	int i,j;
	for(i=0;i<areaheight;i++)
	{
		for (j=0;j<areawidth;j++)
		{
			outimageH[i*areawidth+j]=image[(centery+i-areaheight/2+1)*imagewidth+(centerx+j-areawidth/2+1)];//获得横向的数据矩阵			
		}

	}
	for(i=0;i<areaheight;i++)
	{
		for (j=0;j<areawidth-1;j++)
		{
			outimageV[i*areawidth+j]=image[(centery+j-areawidth/2+1)*imagewidth+(centerx+i-areaheight/2+1)];//获得纵向的数据矩阵
		}

	}
}

/*****************************
* *TD 输入时域实部数组首地址
* *FDre 输出频率实部数组首地址
* *FDim 输出频率虚部数组首地址
* r 变换数组长度
*****************************/
void CRealTimeUp::fft(double *TD, double *FDre, double *FDim, int r)
{
	long count;		//傅里叶变换点数
	int i,j,k;		//循环变量
	int bfsize,p;
	double angle,tempre,tempim;	//角度
	double *Wre,*Wim,*Xre1,*Xim1,*Xre2,*Xim2,*X;
	
	count=1<<r;		//计算傅里叶变换点数，即2^r，r为迭代次数
	
	//分配运算所需存储器
	Wre=new double[count/2];
	Wim=new double[count/2];
	Xre1=new double[count];
	Xim1=new double[count];
	Xre2=new double[count];
	Xim2=new double[count];
	
	//计算加权系数
	for(i=0;i<count/2;i++)
	{
		angle=-i*PI*2/count;
		Wre[i]=cos(angle);//加权系数实部
		Wim[i]=sin(angle);//加权系数虚部
	}
	
	//将时域点写入X1
	for (i=0;i<count;i++)
	{
		Xre1[i]=TD[i];//时域实部
		Xim1[i]=0;//时域虚部（全为零）
	}
	
	//采用蝶形算法进行快速傅里叶变换
	for (k=0;k<r;k++)//进行r次迭代
	{
		for (j=0;j<1<<k;j++)//每次迭代分成(1<<k)个部分计算
		{
			bfsize=1<<(r-k);//每次迭代各个部分的长度
			for (i=0;i<bfsize/2;i++)
			{
				p=j*bfsize;//定位各个部分
				Xre2[i+p]=Xre1[i+p]+Xre1[i+p+bfsize/2];
				Xim2[i+p]=Xim1[i+p]+Xim1[i+p+bfsize/2];
				//X2[i+p+bfsize/2]=(X1[i+p]-X1[i+p+bfsize/2])*W[i*(1<<k)];
				tempre=Xre1[i+p]-Xre1[i+p+bfsize/2];
				tempim=Xim1[i+p]-Xim1[i+p+bfsize/2];
				Xre2[i+p+bfsize/2]=tempre*Wre[i*(1<<k)]-tempim*Wim[i*(1<<k)];
				Xim2[i+p+bfsize/2]=tempre*Wim[i*(1<<k)]+tempim*Wre[i*(1<<k)];
			}
		}
		X=Xre1;			//交换X1，X2
		Xre1=Xre2;		//目的是将X2中的元素移到X1，这里用交换指针的方法实现
		Xre2=X;
		X=Xim1;
		Xim1=Xim2;
		Xim2=X;
	}
	
	//重新排序
	for (j=0;j<count;j++)
	{
		p=0;
		for (i=0;i<r;i++)//二进制码共r位，此循环使p为j的倒序数
		{
			if(j&(1<<i))
			{
				p+=1<<(r-i-1);
			}
		}
		FDre[j]=Xre1[p];//频域
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
	double dMoveDis=m_dStepDis;//获得平移台所需移动的步长(单位um)
	
	switch(nSBCode)//分析消息
	{
		case SB_LINELEFT://左触击
			if(rc=MoveDistance(2,(-1)*dMoveDis))//Z平移台向左位移绝对量
			{
				sprintf(cItemText,"Could not make the stage move.RC=%ld\n",rc);
				MessageBox(cItemText);	
			}
			break;
		case SB_LINERIGHT://右触击
			if(rc=MoveDistance(2,dMoveDis))//Z平移台向右位移绝对量
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
	int nMoveStep=GetMoveStep(dMoveDistance);//将距离转化成步数
	cMes1="SP 500,500,500,500\r\n";//设置速度
	switch(nStageNum)//依据电机序号编写电机位移代码
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
	cMes=cMes1+cMes2;//电机指令合并
	
	for(int i=0;i<cMes.GetLength();i++)
		szBuffer[i]=cMes.GetAt(i);//字符串转变成字符数组

	CMainFrame* MainFramePoint=(CMainFrame*)((CFrameWnd*)AfxGetApp()->m_pMainWnd);
	hDmc=MainFramePoint->getStageHandle();//获取电机控制器句柄

    rc=DMCDownloadFromBuffer(hDmc,szBuffer,NULL);//指令发送
	if(rc)
	{
		sprintf(cItemText,"Could not download a program to the controller.RC=%ld\n",rc);
		MessageBox(cItemText);
		return rc;
	}
	
	rc=DMCCommand(hDmc,"XQ/r",szBuffer,NULL);//指令执行
	
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
	pData=new double[lImageSize]; //开辟图像数据平均值空间

	long lAreaSize=nBoxHeight*nBoxWidth;//获得选择区域图像大小
	pDataH=new double[lAreaSize];//开辟选择区域图像
	pDataV=new double[lAreaSize];

	LSFH=new double[nBoxWidth];//开辟LSF空间
	LSFV=new double[nBoxWidth];

	
	FtDataRe=new double[nBoxWidth];
	FtDataIm=new double[nBoxWidth];
	
	MTFH=new double[nBoxWidth];//开辟MTF空间
	MTFV=new double[nBoxWidth];

	PosH=new double[nBoxWidth];//开辟LSF位置坐标数组空间
	PosV=new double[nBoxWidth];
	Freq=new double[nBoxWidth];//开辟MTF频率坐标数组空间

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
		//弹出非模态对话框
		CBackgroundWnd* pBackgroundWnd;
		pBackgroundWnd=new CBackgroundWnd();
		CMainFrame* MainFramePoint=(CMainFrame*)((CFrameWnd*)AfxGetApp()->m_pMainWnd);
		CString sLensName=MainFramePoint->getsLensName();
		
		if(pBackgroundWnd!=NULL)
		{
			//pBackgroundWnd->getDataFromMainFrm(this);
			pBackgroundWnd->getDataFromRealTimeFrm(this);//此函数解决由当前类向显示类完成数据输送的问题
			CRect rect;
			GetWindowRect(rect);//位置及大小设定
			rect.top+=75;
			rect.left+=75;
			rect.right=rect.left+660;
			rect.bottom=rect.top+520;
			BOOL ret=pBackgroundWnd->Create(NULL,sLensName,WS_OVERLAPPEDWINDOW,rect,this);
			if(!ret)
				AfxMessageBox("Error Creating Dialog!");
			pBackgroundWnd->ShowWindow(SW_SHOW);//显示对话框
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
		|OFN_OVERWRITEPROMPT, "VMF文件 (*.vmf)|*.vmf|所有文件 (*.*)|*.*||", NULL);//生成文件保存对话框
	char *filepath;
	if(filedlg.DoModal()==IDOK)
	{
		string sfpath=filedlg.GetPathName();//获得文件保存路径
		i=sfpath.length();
		filepath=new char[i+5];
		strcpy(filepath,sfpath.c_str());//拷贝文件路径
		if(strcmp(filepath+i-4,".vmf")!=0)//文件后缀名判别
		{
			filepath[i++]='.';//后缀名添加
			filepath[i++]='v';
			filepath[i++]='m';
			filepath[i++]='f';
			filepath[i]='\0';
		}
		FILE *filepoint=fopen(filepath,"w");//打开文件
		delete[] filepath;//销毁文件名指针
		filepath=NULL;
		if(filepoint==NULL)
		{
			MessageBox("Could not save file!","Error");//打开文件失败
			return;
		}
		CTime temptime;
		temptime=CTime::GetCurrentTime();//获取当前时间
		CString temptimestring=temptime.Format("%Y-%m-%d-%H-%M-%S");//将时间变量转化成字符串，格式为年-月-日-时-分-秒
		fprintf(filepoint,"Saved time:%s\n",temptimestring);//写入保存时间
		//以下的配置参数需从主框获得
		int arraylength=nBoxWidth;

		CMainFrame* MainFramePoint;
		MainFramePoint=(CMainFrame*)((CFrameWnd*)AfxGetApp()->m_pMainWnd);//获得主框指针
		double dPinDiameter=MainFramePoint->getdPinDiameter();//获得孔径
		fprintf(filepoint,"Pin Diameter:%.2lf\n",dPinDiameter);//写入孔径
		double dAmplify=MainFramePoint->getdAmplify();//获得中继放大率
		fprintf(filepoint,"Amplification Ratio:%.2lf\n",dAmplify);//写入中继系统放大率
		CString sLensName=MainFramePoint->getsLensName();//获得镜头名称
		fprintf(filepoint,"Camera Name:%s\n",sLensName);//写入镜头名称
		double dFocusLength=MainFramePoint->getdFocusLength();//获得平行光管焦距
		fprintf(filepoint,"Focus:%.2lf\n",dFocusLength);//写入平行光管焦距
		double dFNumber=MainFramePoint->getdFNumber();//获得镜头F数
		fprintf(filepoint,"F Number:%.2lf\n",dFNumber);//写入镜头F数
		double dWaveLength=MainFramePoint->getdWaveLength();//获得光源波长
		fprintf(filepoint,"WaveLength:%.2lf\n",dWaveLength);//写入光源波长
		double dLength=MainFramePoint->getdLength();//获得平行光管焦距
		fprintf(filepoint,"Collimated Focus:%.2lf\n",dLength);//写入平行光管焦距
		//该参数直接从本类获得
		fprintf(filepoint,"Array Length:%d\n",arraylength);//写入数据数组尺寸，仍使用arraylength
		
		//此处的参数名称与主框中对应参数的名称不同，但形式和作用相同
		fprintf(filepoint,"position(T):");//写入T方向位置数组
		for(i=0;i<arraylength;i++)
		{
			fprintf(filepoint,"%.2lf ",PosH[i]);
		}
	

		fprintf(filepoint,"\nLSF(T):");//写入T方向LSF数组
		for(i=0;i<arraylength;i++)
		{
			fprintf(filepoint,"%.4lf ",LSFH[i]);
		}

		
		fprintf(filepoint,"\nposition(S):");//写入S方向位置数组
		for(i=0;i<arraylength;i++)
		{
			fprintf(filepoint,"%.2lf ",PosV[i]);
		}
		


		fprintf(filepoint,"\nLSF(S):");//写入S方向LSF数组
		for(i=0;i<arraylength;i++)
		{
			fprintf(filepoint,"%.4lf ",LSFV[i]);
		}
		

		fprintf(filepoint,"\nFrequence(lp/mm):");//写入频率数组
		for(i=0;i<arraylength;i++)
		{
			fprintf(filepoint,"%.2lf ",Freq[i]);
		}
		
		fprintf(filepoint,"\nMTF(T):");//写入T方向MTF数组
		for(i=0;i<arraylength;i++)
		{
			fprintf(filepoint,"%.4lf ",MTFH[i]);
		}
		
		
		fprintf(filepoint,"\nMTF(S):");//写入S方向MTF数组
		for(i=0;i<arraylength;i++)
		{
			fprintf(filepoint,"%.4lf ",MTFV[i]);
		}
		
		
		fclose(filepoint);//关闭文件
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
