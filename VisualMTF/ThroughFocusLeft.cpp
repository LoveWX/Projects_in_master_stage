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
	
	bCameraInit=MainFramePoint->getbCamInit();//获得相机初始状态
	hBoard=MainFramePoint->getCameraHandle();//获得相机句柄

	bStageInit=MainFramePoint->getbCamInit();//获得位移台初始状态
	hDmc=MainFramePoint->getStageHandle();//获得位移台控制器句柄
	
	lpLinear=MainFramePoint->getCameraBuffer();//获得相机存储空间指针
	dAmplify=MainFramePoint->getdAmplify();//获得显微系统放大率
	dPixel=MainFramePoint->getdPixel();//获得相机像元尺寸
	nBoxHeight=MainFramePoint->getnStarHeight();//获得十字叉高
	nBoxWidth=MainFramePoint->getnStarWidth();//获得十字叉宽

	m_dFromPos=-10.0;//起点的相对距离默认值为-10微米
	m_dToPos=10.0;//终点的相对距离默认值为+10微米
	m_nStepNum=2;//采样点数默认值为5（0至9依次对应1至10）
	m_bChecked=FALSE;//默认状态不显示衍射极限曲线
	
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
	
	/*if(bCameraInit==FALSE)//相机初始化判定
	{
		sprintf(cItemText,"相机初试未完成。任务终止！");
		MessageBox(cItemText);
		return;
	}

	if(bStageInit==FALSE)
	{
		sprintf(cItemText,"相机初试未完成。任务终止！");
		MessageBox(cItemText);
		return;
	}
	
	UpdateData(TRUE);//刷新控件
	double dFromPos=m_dFromPos;//获得采样电移台起始位置
	double dToPos=m_dToPos;//获得采样电移台终止位置
	nAcqTimes=2*m_nStepNum+1;//获得采样数
	
	if((dFromPos+dToPos)!=0)
	{
		sprintf(cItemText,"The two positions are suggested to be symmetrical. Please re-input.");
		MessageBox(cItemText);
		return;
	}	
	

	
	double dFirstStepDis=dFromPos;//获得平移台从当前位置至起始点所需移动的距离（单位um）
	double dEveryStepDis=(m_dToPos-m_dFromPos)/(nAcqTimes-1);//获得平移台中间所需移动的距离（单位um）
	double dLastStepDis=0-m_dToPos;//获得平移台从最后采样点回复到原点所需移动的距离（单位um）
	
	if(rc=MoveDistance(2,dFirstStepDis))//Z平移台移动相应距离至于客户设定之起始点
	{
		sprintf(cItemText,"Could not make the stage move.RC=%ld\n",rc);
		MessageBox(cItemText);
		return;
	}
	
	lNum=okGetBufferSize(hBoard, (void **)&lpLinear, &dwSize);//获得当前状态允许拍摄的最大幅数
	long lFrameNum=FRAMENUM;
	if( lFrameNum > lNum ) //防止需要采集的图像帧数大于当前BUFFER容许存放的图像帧数
	{
		lFrameNum = lNum;
		sprintf(cItemText,"警告：相机当前缓存容量低于18幅，当前仅为%d幅",lFrameNum);
		MessageBox(cItemText);
	}
	
	MemoryCheck();
	
	OutMemorySetZero();//最后结果清零
	long lImageSize=WIDTH*HEIGHT;
	//以下连续采样
	int xpos,ypos;//平均图像极值点坐标
	for(f=0;f<nAcqTimes;f++)
	{
		*(EveryPos+f)=dFromPos+dEveryStepDis*f;//获得本次采样Z轴位置相对坐标
		InMemorySetZero();//中间结果清零

		okCaptureTo(hBoard,BUFFER,0,lFrameNum); //采集指定数量帧图像数据(首地址为lpLinear) 
		okGetCaptureStatus(hBoard,1); //获取采集结束
		
		for(i=0;i<lFrameNum;i++)//循环采样次数
			for(j=0;j<lImageSize;j++)
				pData[j]+=*(lpLinear+i*lImageSize+j);//逐帧累加
		for(j=0;j<lImageSize;j++)
		pData[j]/=lFrameNum;//取均值

		
		CenterFind(pData,xpos,ypos,HEIGHT,WIDTH);//获得平均后图像的中心点

		AreaSelect(pData,pDataH,pDataV,nBoxWidth,nBoxHeight,xpos,ypos,WIDTH);//获得两个方向图像区域

		
		for(j=0;j<nBoxWidth;j++)//获得两个方向的LSF
		for(i=0;i<nBoxHeight;i++)
		{
			*(LSFH+f*nBoxWidth+j)=*(LSFH+f*nBoxWidth+j)+*(pDataH+i*nBoxWidth+j);//横向LSF值
			*(LSFV+f*nBoxWidth+j)=*(LSFV+f*nBoxWidth+j)+*(pDataV+i*nBoxWidth+j);//纵向LSF值
		}
		

		fft(LSFH,FtDataRe,FtDataIm,nBoxWidth);//对另一个方向数据进行fft	
		for(j=0;j<nBoxWidth;j++)
		{
			*(MTFH+f*nBoxWidth+j)=sqrt( (*(FtDataRe+j)) * (*(FtDataRe+j)) + (*(FtDataIm+j)) * (*(FtDataIm+j)) );//归一化前值
			*(MTFH+f*nBoxWidth+j)/=*(MTFH+f*nBoxWidth);//归一化后值
		}

		fft(LSFV,FtDataRe,FtDataIm,nBoxWidth);
		for(j=0;j<nBoxWidth;j++)
		{
			*(MTFV+f*nBoxWidth+j)=sqrt( (*(FtDataRe+j)) * (*(FtDataRe+j)) + (*(FtDataIm+j)) * (*(FtDataIm+j)) );//归一化前值
			*(MTFV+f*nBoxWidth+j)=*(MTFV+f*nBoxWidth);//归一化后值
		}

		if(f!=nAcqTimes-1)//采样nAcqTimes次，移动nAcqTimes-1次，因此最后归位仅返回-m_dToPos即可，而非-(m_dToPos+dEveryStepDis)
		{
			if(rc=MoveDistance(2,dEveryStepDis))//Z平移台移动相应距离至于客户设定之起始点
			{
				sprintf(cItemText,"Could not make the stage move.RC=%ld\n",rc);
				MessageBox(cItemText);
				return;
			}
		}

	}
	
	 
		
	for(j=0;j<nBoxWidth;j++)
	{
		*(PosH+j)=(xpos+j-nBoxWidth/2+1)*dPixel/dAmplify;//获LSF位置坐标
		*(PosV+j)=(ypos+j-nBoxWidth/2+1)*dPixel/dAmplify;
		*(Freq+j)=j*dAmplify/nBoxWidth/dPixel;//获MTF频率坐标
	}

	if(rc=MoveDistance(2,dLastStepDis))//Z平移台移动相应距离至于客户设定之起始点
	{
		sprintf(cItemText,"Could not make the stage move.RC=%ld\n",rc);
		MessageBox(cItemText);
		return;
	}
	
	//需要绘制的是PosH~LSFH，PosV~LSFV，Freq~MTFH~MTFV*/
	UpdateData(TRUE);
	nAcqTimes=2*m_nStepNum+1;//获得采样数

	EveryPos=new double[nAcqTimes];//开辟每个采样Z轴位置记录数组空间
	MTFH=new double[nBoxWidth*nAcqTimes];//开辟MTF空间，该空间保留所有取样结果
	MTFV=new double[nBoxWidth*nAcqTimes];
	Freq=new double[nBoxWidth];//开辟MTF频率坐标数组空间
	

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
	
		
	

	CThroughFocusFrame* FrameWndPoint=(CThroughFocusFrame*)(GetParentFrame());//获父框
	CThroughFocusRight* RightViewPoint=(CThroughFocusRight*)(FrameWndPoint->GetRightView());//获右子视图
	
	RightViewPoint->UpdateTrace(TRUE,Freq,MTFH,MTFV,nBoxWidth,EveryPos,nAcqTimes);//视图刷新并传递参量，参数内容见函数声明*/
}

/*****************************
* *image 图像数据指针
* &x     极值点横坐标
* &y     极值点纵坐标
* height 图像高度
* width  图像宽度
*****************************/
void CThroughFocusLeft::CenterFind(double *image, int &x, int &y, int height, int width)//该函数用于判断平均图像数据极值点位置
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
* *TD 输入时域实部数组首地址
* *FDre 输出频率实部数组首地址
* *FDim 输出频率虚部数组首地址
* r 变换数组长度
*****************************/
void CThroughFocusLeft::fft(double *TD, double *FDre, double *FDim, int r)
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
void CThroughFocusLeft::AreaSelect(double *image, double *outimageH, double *outimageV, int areawidth, int areaheight, int centerx, int centery, int imagewidth)//该函数在获取图像极值点位置后
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

int CThroughFocusLeft::GetMoveStep(double dMoveDis)
{
	int nMoveStep=int(dMoveDis/STEP_DISTANCE);
	return nMoveStep;
}

long CThroughFocusLeft::MoveDistance(int nStageNum, double dMoveDistance)
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
	EveryPos=new double[nAcqTimes];//开辟每个采样Z轴位置记录数组空间

	long lImageSize=WIDTH*HEIGHT;
	pData=new double[lImageSize];//开辟图像数据平均值空间

	long lAreaSize=nBoxHeight*nBoxWidth;//获得选择区域图像大小
	pDataH=new double[lAreaSize];//开辟选择区域图像
	pDataV=new double[lAreaSize];

	
	FtDataRe=new double[nBoxWidth];//开辟fft结果实部与虚部空间
	FtDataIm=new double[nBoxWidth];

	LSFH=new double[nBoxWidth*nAcqTimes];//开辟LSF空间，该空间保留所有取样结果
	LSFV=new double[nBoxWidth*nAcqTimes];

	MTFH=new double[nBoxWidth*nAcqTimes];//开辟MTF空间，该空间保留所有取样结果
	MTFV=new double[nBoxWidth*nAcqTimes];

	PosH=new double[nBoxWidth];//开辟LSF位置坐标数组空间
	PosV=new double[nBoxWidth];

	Freq=new double[nBoxWidth];//开辟MTF频率坐标数组空间
	
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
	int index=(nAcqTimes-1)/2*nBoxWidth;//获取所有采样中的中间组采样数据的偏移量
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
