// VisualMTFView.cpp : implementation of the CVisualMTFView class
//

#include "stdafx.h"
#include "VisualMTF.h"

#include "VisualMTFDoc.h"
#include "VisualMTFView.h"
#include "MainFrm.h"
#include "LeftFormView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVisualMTFView

IMPLEMENT_DYNCREATE(CVisualMTFView, CView)

BEGIN_MESSAGE_MAP(CVisualMTFView, CView)
	//{{AFX_MSG_MAP(CVisualMTFView)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVisualMTFView construction/destruction

CVisualMTFView::CVisualMTFView()
{
	// TODO: add construction code here
	framepos_x1=110;
	framepos_y1=-700;
	framepos_x2=1635;
	framepos_y2=-2400;
	picpos_x1=310;
	picpos_y1=-900;
	picpos_x2=1510;
	picpos_y2=-2100;
	BColorR=185;
	BColorG=195;
	BColorB=255;
	dLinePerPage=43;
}

CVisualMTFView::~CVisualMTFView()
{
}

BOOL CVisualMTFView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CVisualMTFView drawing

void CVisualMTFView::OnDraw(CDC* pDC)
{
	CVisualMTFDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CVisualMTFView printing

BOOL CVisualMTFView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	CMainFrame* MainFramePoint=(CMainFrame*)((CFrameWnd*)AfxGetApp()->m_pMainWnd);
	int type=MainFramePoint->getTypedPage();//获得打印的试图类型
	if(type==3)//若为3，即打印结果数表，需计算页数
	{
		int i=MainFramePoint->getarraylength();
		if(i%dLinePerPage==0)
			i=i/dLinePerPage;
		else
			i=i/dLinePerPage+1;
		pInfo->SetMaxPage(i);
	}
	else//其它，则显示页数仅为1
	{
		pInfo->SetMaxPage(1);
	}
	return DoPreparePrinting(pInfo);
}

void CVisualMTFView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CVisualMTFView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CVisualMTFView diagnostics

#ifdef _DEBUG
void CVisualMTFView::AssertValid() const
{
	CView::AssertValid();
}

void CVisualMTFView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CVisualMTFDoc* CVisualMTFView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CVisualMTFDoc)));
	return (CVisualMTFDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CVisualMTFView message handlers

void CVisualMTFView::OnPrint(CDC* pDC, CPrintInfo* pInfo) 
{
	// TODO: Add your specialized code here and/or call the base class
	CMainFrame* MainFramePoint=(CMainFrame*)((CFrameWnd*)AfxGetApp()->m_pMainWnd);
	int type=MainFramePoint->getTypedPage();//获得显示类型
	if(type==0)
		PrintMTFView(pDC,(void*)MainFramePoint);//状态0，视图为MTF结果
	else if(type==1)
		PrintLSFView(pDC,(void*)MainFramePoint);//状态1，视图为LSF结果
	else if(type==2)
		PrintTextView(pDC,(void*)MainFramePoint);//状态2，视图为配置参数
	else
		PrintListView(pDC,(void*)MainFramePoint,pInfo->m_nCurPage-1);//状态3，视图为结果列表（多一参数，当前页数减一值）
}

void CVisualMTFView::PrintMTFView(CDC *pDC,void *mainfrm)//MTF结果视图打印
{
	CMainFrame* MainFramePoint=(CMainFrame*)mainfrm;
	CFont myTitleFont;
	pDC->SetMapMode(MM_LOMETRIC);
	myTitleFont.CreatePointFont(400,"黑体",pDC);
	CFont* pOldFont=pDC->SelectObject(&myTitleFont);
	pDC->TextOut(0,-100,"   Video MTF Image Analysis");//头
	pDC->SelectObject(pOldFont);

	CString pntstr;
	pntstr.Format("Camera Name:  %s",MainFramePoint->getsLensName());//镜头名
	pDC->TextOut(100,-250,pntstr);
	CTime temptime=*(MainFramePoint->getSavedTime());
	pntstr=temptime.Format("Saved Time:   %H:%M:%S %A, %B %d,%Y");//保存时间
	pDC->TextOut(100,-300,pntstr);
	temptime=CTime::GetCurrentTime();
	pntstr=temptime.Format("Printed Time: %H:%M:%S %A, %B %d,%Y");//打印时间
	pDC->TextOut(100,-350,pntstr);

	DrawBackground(pDC);//背景
	DrawMTFFrame(pDC,MainFramePoint);//MTF坐标
	DrawGrid(pDC);//网格
	DrawMTFTTrace(pDC,MainFramePoint);//MTF数据线
	DrawMTFSTrace(pDC,MainFramePoint);//MTF数据线
}

void CVisualMTFView::PrintLSFView(CDC *pDC,void *mainfrm)//LSF结果视图打印
{
	CMainFrame* MainFramePoint=(CMainFrame*)mainfrm;
	CFont myTitleFont;
	pDC->SetMapMode(MM_LOMETRIC);
	myTitleFont.CreatePointFont(400,"黑体",pDC);
	CFont* pOldFont=pDC->SelectObject(&myTitleFont);
	pDC->TextOut(0,-100,"   Video MTF Image Analysis");//头
	pDC->SelectObject(pOldFont);
	
	CString pntstr;
	pntstr.Format("Camera Name:  %s",MainFramePoint->getsLensName());//镜头名
	pDC->TextOut(100,-250,pntstr);
	CTime temptime=*(MainFramePoint->getSavedTime());
	pntstr=temptime.Format("Saved Time:   %H:%M:%S %A, %B %d,%Y");//保存时间
	pDC->TextOut(100,-300,pntstr);
	temptime=CTime::GetCurrentTime();
	pntstr=temptime.Format("Printed Time: %H:%M:%S %A, %B %d,%Y");//打印时间
	pDC->TextOut(100,-350,pntstr);
	
	DrawBackground(pDC);//背景
	DrawLSFFrame(pDC,MainFramePoint);//LSF坐标
	DrawGrid(pDC);//网格
	DrawLSFTTrace(pDC,MainFramePoint);//LSF数据线
	DrawLSFSTrace(pDC,MainFramePoint);//LSF数据线
}

void CVisualMTFView::PrintTextView(CDC *pDC,void *mainfrm)//配置参数视图打印
{
	int xstart=600,ystart=-600;
	int disy=-300;
	CString pntstr;
	CMainFrame* MainFramePoint=(CMainFrame*)mainfrm;

	pDC->SetMapMode(MM_TWIPS);
	CFont myFont;
	myFont.CreatePointFont(150,"黑体",pDC);
	CFont* pOldFont=pDC->SelectObject(&myFont);

	pDC->TextOut(xstart,ystart,"Video MTF Configuration Data");//头
	pntstr.Format("Pin Diameter:           %.2lf",MainFramePoint->getdPinDiameter());//孔径
	pDC->TextOut(xstart,ystart+disy*2,pntstr);
	pntstr.Format("Amplification Ratio:    %.2lf",MainFramePoint->getdAmplify());//中继放大率
	pDC->TextOut(xstart,ystart+disy*3,pntstr);
	pntstr.Format("Camera Name:            %s",MainFramePoint->getsLensName());//镜头名称
	pDC->TextOut(xstart,ystart+disy*4,pntstr);
	pntstr.Format("Focus:                  %.2lf",MainFramePoint->getdFocusLength());//镜头焦距
	pDC->TextOut(xstart,ystart+disy*5,pntstr);
	pntstr.Format("F Number:               %.2lf",MainFramePoint->getdFNumber());//F数
	pDC->TextOut(xstart,ystart+disy*6,pntstr);
	pntstr.Format("WaveLength:             %.2lf",MainFramePoint->getdWaveLength());//光源波长
	pDC->TextOut(xstart,ystart+disy*7,pntstr);
	pntstr.Format("Collimated Focus:       %.2lf",MainFramePoint->getdLength());//平行光管焦距
	pDC->TextOut(xstart,ystart+disy*8,pntstr);
	pntstr.Format("Array Length:           %.2lf",MainFramePoint->getarraylength());//数据长度
	pDC->TextOut(xstart,ystart+disy*9,pntstr);	
	pDC->SelectObject(pOldFont);
}

void CVisualMTFView::PrintListView(CDC *pDC,void *mainfrm,int nPage)//结果列表，多出参数为当前减1页
{
	PrintPageHeader(pDC,mainfrm);//打印数表表头
	int startline=nPage*dLinePerPage;//需显示的首行
	int endline=startline+dLinePerPage;//需显示的末行
	CString pntstr;
	CMainFrame* MainFramePoint=(CMainFrame*)mainfrm;
	if(endline>MainFramePoint->getarraylength())
		endline=MainFramePoint->getarraylength();
	int posx=100,posy=-450,i=0,disy=-50;
	double *pdFreq=MainFramePoint->getdFreq();
	double *pdMTFt=MainFramePoint->getdMTFt();
	double *pdMTFs=MainFramePoint->getdMTFs();
	double *pdLSFt=MainFramePoint->getdLSFt();
	double *pdLSFs=MainFramePoint->getdLSFs();
	double *pdpost=MainFramePoint->getdPOSt();
	double *pdposs=MainFramePoint->getdPOSs();
	for(i=startline;i<endline;i++)
	{
		pntstr.Format("%-16.2lf%-14.2lf%-13.2lf%-13.2lf%-13.2lf%-13.2lf%-10.2lf",//显示七数组对应行的的信息
			pdFreq[i],pdMTFt[i],pdMTFs[i],pdLSFt[i],pdLSFs[i],pdpost[i],pdposs[i]);
		pDC->TextOut(posx,posy+i*disy,pntstr);
	}
}

void CVisualMTFView::DrawBackground(CDC *mypDC)
{
	CBrush mybrush;
	mybrush.CreateSolidBrush(RGB(BColorR,BColorG,BColorB));//设置颜色为[185,195,255]的浅蓝
	CBrush *oldbrush;
	oldbrush=mypDC->SelectObject(&mybrush);
	mypDC->Rectangle(60,-500,2087,-2500);//局部背景染色
	mypDC->SelectObject(oldbrush);
}

void CVisualMTFView::DrawMTFFrame(CDC *mypDC,void *mainfrm)
{
	mypDC->SetBkColor(RGB(BColorR,BColorG,BColorB));//为字笔设置同上的背景色，防止白底出现
	CBrush mybrush;
	mybrush.CreateSolidBrush(RGB(BColorR,BColorG,BColorB));
	CBrush *oldbrush;
	oldbrush=mypDC->SelectObject(&mybrush);
	
	char printtext[10];
	CMainFrame* MainFramePoint=(CMainFrame*)mainfrm;
	double xmax=MainFramePoint->getMTFxmax();

	CFont myTitleFont,myFont;
	myTitleFont.CreatePointFont(300,"黑体",mypDC);
	CFont* pOldFont=mypDC->SelectObject(&myTitleFont);
	mypDC->TextOut(760,-550,"Video MTF Data");
	myFont.CreatePointFont(200,"黑体",mypDC);
	mypDC->SelectObject(&myFont);
	mypDC->Rectangle(framepos_x1,framepos_y1,framepos_x2,framepos_y2);
	mypDC->TextOut(180,-790,"Modulation(%)");//以下显示纵轴
	mypDC->TextOut(180,-865,"100");
	mypDC->TextOut(180,-1105," 80");
	mypDC->TextOut(180,-1345," 60");
	mypDC->TextOut(180,-1585," 40");
	mypDC->TextOut(180,-1825," 20");
	mypDC->TextOut(180,-2065,"  0");
	mypDC->TextOut(610,-2250,"Frequency(lp/mm)");//以下显示横轴
	sprintf(printtext,"%.2lf",xmax*0.5);
	mypDC->TextOut(835,-2120,printtext);
	sprintf(printtext,"%.2lf",xmax);
	mypDC->TextOut(1395,-2120,printtext);
	
	mypDC->Rectangle(picpos_x1,picpos_y1,picpos_x2,picpos_y2);//边框显示
	mypDC->SelectObject(oldbrush);
	mypDC->SelectObject(pOldFont);
}

void CVisualMTFView::DrawLSFFrame(CDC *mypDC,void *mainfrm)
{
	mypDC->SetBkColor(RGB(BColorR,BColorG,BColorB));
	CBrush mybrush;
	mybrush.CreateSolidBrush(RGB(BColorR,BColorG,BColorB));
	CBrush *oldbrush;
	oldbrush=mypDC->SelectObject(&mybrush);
	
	int textwidth=3;
	GetYMax(mainfrm);
	char printtext[10];
	CMainFrame* MainFramePoint=(CMainFrame*)mainfrm;

	CFont myTitleFont,myFont;
	myTitleFont.CreatePointFont(300,"黑体",mypDC);
	CFont* pOldFont=mypDC->SelectObject(&myTitleFont);
	mypDC->TextOut(535,-550,"LINE SPREAD FUNCTION");
	myFont.CreatePointFont(200,"黑体",mypDC);
	mypDC->SelectObject(&myFont);
	mypDC->Rectangle(framepos_x1,framepos_y1,framepos_x2,framepos_y2);
	mypDC->TextOut(180,-790,"Intensity");

	sprintf(printtext,"%d",(int)ymax);
	mypDC->TextOut(180,-865,printtext);
	PreparePrintText((int)(ymax*0.8),textwidth,printtext);
	mypDC->TextOut(180,-1105,printtext);
	PreparePrintText((int)(ymax*0.6),textwidth,printtext);
	mypDC->TextOut(180,-1345,printtext);
	PreparePrintText((int)(ymax*0.4),textwidth,printtext);
	mypDC->TextOut(180,-1585,printtext);
	PreparePrintText((int)(ymax*0.2),textwidth,printtext);
	mypDC->TextOut(180,-1825,printtext);
	mypDC->TextOut(180,-2065,"  0");
	mypDC->TextOut(610,-2250,"Distance(microns)");
	GetX(mainfrm);
	sprintf(printtext,"%.3lf",xmin);
	mypDC->TextOut(275,-2120,printtext);
	mypDC->TextOut(835,-2120,"0.000");
	sprintf(printtext,"%.3lf",xmin);
	mypDC->TextOut(1395,-2120,printtext);

	mypDC->Rectangle(picpos_x1,picpos_y1,picpos_x2,picpos_y2);
	mypDC->SelectObject(oldbrush);
	mypDC->SelectObject(pOldFont);
}

void CVisualMTFView::DrawGrid(CDC *mypDC)
{
	mypDC->SetBkColor(RGB(BColorR,BColorG,BColorB));
	CPen mypen1,mypen2;
	CPen *oldpen;
	const int numofblock=10;
	int gridpos,gridwidth;
	mypen1.CreatePen(PS_NULL,1,RGB(0,0,0));
	oldpen=mypDC->SelectObject(&mypen1);
		
	CBrush mybrush;
	CBrush *oldbrush;
	mybrush.CreateSolidBrush(RGB(255,255,255));
	oldbrush=mypDC->SelectObject(&mybrush);
	mypDC->Rectangle(picpos_x1+5,picpos_y1-4,picpos_x2-5,picpos_y2+4);

	mypDC->SetBkColor(RGB(255,255,255));
	mypen2.CreatePen(PS_DOT,1,RGB(0,0,0));
	mypDC->SelectObject(&mypen2);

	//画竖线
	gridwidth=(picpos_x2-picpos_x1)/numofblock;
	for(gridpos=picpos_x1+gridwidth;gridpos<picpos_x2;gridpos+=gridwidth)
	{
		mypDC->MoveTo(gridpos,picpos_y2);
		mypDC->LineTo(gridpos,picpos_y1);
	}
	
	//画横线
	gridwidth=(picpos_y1-picpos_y2)/numofblock;
	for(gridpos=picpos_y2+gridwidth;gridpos<picpos_y1;gridpos+=gridwidth)
	{
		mypDC->MoveTo(picpos_x1,gridpos);
		mypDC->LineTo(picpos_x2,gridpos);
	}
	
	mypDC->SelectObject(oldpen);
	
	for(gridpos=picpos_y2+gridwidth;gridpos<picpos_y1;gridpos+=gridwidth)
	{
		mypDC->MoveTo(picpos_x1-10,gridpos);
		mypDC->LineTo(picpos_x1,gridpos);
	}
	gridwidth=(picpos_x2-picpos_x1)/numofblock;
	for(gridpos=picpos_x1+gridwidth;gridpos<picpos_x2;gridpos+=gridwidth)
	{
		mypDC->MoveTo(gridpos,picpos_y2);
		mypDC->LineTo(gridpos,picpos_y2-10);
	}
	
	mypDC->SelectObject(oldbrush);
}

void CVisualMTFView::DrawMTFTTrace(CDC *mypDC,void *mainfrm)
{
	CFont myFont;
	myFont.CreatePointFont(200,"黑体",mypDC);
	CFont* pOldFont=mypDC->SelectObject(&myFont);
	mypDC->SetBkColor(RGB(BColorR,BColorG,BColorB));
	mypDC->TextOut(1810,-1250,"子午方向");//标示
	CPen mypen;
	CPen *oldpen;
	mypen.CreatePen(PS_SOLID,1,RGB(255,0,0));
	oldpen=mypDC->SelectObject(&mypen);
	mypDC->MoveTo(1650,-1285);
	mypDC->LineTo(1795,-1285);
	
	//画框内的点
	CMainFrame* MainFramePoint=(CMainFrame*)mainfrm;
	int dArrLen=MainFramePoint->getExtendedlength();
	double *pdTTrace=MainFramePoint->getExtendedMTFt();
	int i,xlen=picpos_x2-picpos_x1,ylen=picpos_y1-picpos_y2;
	int tempx=picpos_x1,tempy=picpos_y1;
	mypDC->SetBkColor(RGB(255,255,255));
	mypDC->MoveTo(tempx,tempy);
	double dMTFxmax=MainFramePoint->getMTFxmax();
	int fmaxtimes=0;
	while(dMTFxmax>=0.00001)
	{
		fmaxtimes++;
		dMTFxmax-=MainFramePoint->getdF();
	}
	for(i=1;i<dArrLen&&i<=fmaxtimes;i++)
	{
		tempx=(int)((double)i/fmaxtimes*xlen+picpos_x1+0.5);
		tempy=(int)(picpos_y2+pdTTrace[i]*ylen+0.5);
		mypDC->LineTo(tempx,tempy);
		mypDC->MoveTo(tempx,tempy);
	}
	
	mypDC->SelectObject(oldpen);
	mypDC->SelectObject(pOldFont);
}

void CVisualMTFView::DrawMTFSTrace(CDC *mypDC,void *mainfrm)
{
	CFont myFont;
	myFont.CreatePointFont(200,"黑体",mypDC);
	CFont* pOldFont;
	pOldFont=mypDC->SelectObject(&myFont);
	mypDC->SetBkColor(RGB(BColorR,BColorG,BColorB));
	mypDC->TextOut(1810,-1340,"弧矢方向");//标示
	CPen mypen;
	CPen *oldpen;
	mypen.CreatePen(PS_SOLID,1,RGB(0,0,255));
	oldpen=mypDC->SelectObject(&mypen);
	mypDC->MoveTo(1650,-1375);
	mypDC->LineTo(1795,-1375);
	
	//画框内的点
	CMainFrame* MainFramePoint=(CMainFrame*)mainfrm;
	int dArrLen=MainFramePoint->getExtendedlength();
	double *pdSTrace=MainFramePoint->getExtendedMTFs();
	int i,xlen=picpos_x2-picpos_x1,ylen=picpos_y1-picpos_y2;
	int tempx=picpos_x1,tempy=picpos_y1;
	mypDC->SetBkColor(RGB(255,255,255));
	mypDC->MoveTo(tempx,tempy);
	double dMTFxmax=MainFramePoint->getMTFxmax();
	int fmaxtimes=0;
	while(dMTFxmax>=0.00001)
	{
		fmaxtimes++;
		dMTFxmax-=MainFramePoint->getdF();
	}
	for(i=1;i<dArrLen&&i<=fmaxtimes;i++)
	{
		tempx=(int)((double)i/fmaxtimes*xlen+picpos_x1+0.5);
		tempy=(int)(picpos_y2+pdSTrace[i]*ylen+0.5);
		mypDC->LineTo(tempx,tempy);
		mypDC->MoveTo(tempx,tempy);
	}
	
	mypDC->SelectObject(oldpen);
	mypDC->SelectObject(pOldFont);
}

void CVisualMTFView::DrawLSFTTrace(CDC *mypDC,void *mainfrm)
{
	CFont myFont;
	myFont.CreatePointFont(200,"黑体",mypDC);
	CFont* pOldFont=mypDC->SelectObject(&myFont);
	mypDC->SetBkColor(RGB(BColorR,BColorG,BColorB));
	mypDC->TextOut(1810,-1250,"子午方向");//标示
	CPen mypen;
	CPen *oldpen;
	mypen.CreatePen(PS_SOLID,1,RGB(255,0,0));
	oldpen=mypDC->SelectObject(&mypen);
	mypDC->MoveTo(1650,-1285);
	mypDC->LineTo(1795,-1285);
	
	//画框内的点
	CMainFrame* MainFramePoint=(CMainFrame*)mainfrm;
	int dArrLen=MainFramePoint->getarraylength();
	double *pdpos=MainFramePoint->getdPOSt();
	double *pdTTrace=MainFramePoint->getdLSFt();
	int i,xlen=picpos_x2-picpos_x1,ylen=picpos_y1-picpos_y2;
	int tempx=(int)((pdpos[0]*0.5/xmax+0.5)*xlen+picpos_x1+0.5),tempy=(int)(picpos_y2+pdTTrace[0]*ylen/ymax+0.5);
	mypDC->SetBkColor(RGB(255,255,255));
	mypDC->MoveTo(tempx,tempy);
	for(i=1;i<dArrLen;i++)
	{
		tempx=(int)((pdpos[i]*0.5/xmax+0.5)*xlen+picpos_x1+0.5);
		tempy=(int)(picpos_y2+pdTTrace[i]*ylen/ymax+0.5);
		mypDC->LineTo(tempx,tempy);
		mypDC->MoveTo(tempx,tempy);
	}
	
	mypDC->SelectObject(oldpen);
	mypDC->SelectObject(pOldFont);
}

void CVisualMTFView::DrawLSFSTrace(CDC *mypDC,void *mainfrm)
{
	CFont myFont;
	myFont.CreatePointFont(200,"黑体",mypDC);
	CFont* pOldFont;
	pOldFont=mypDC->SelectObject(&myFont);
	mypDC->SetBkColor(RGB(BColorR,BColorG,BColorB));
	mypDC->TextOut(1810,-1340,"弧矢方向");//标示
	CPen mypen;
	CPen *oldpen;
	mypen.CreatePen(PS_SOLID,1,RGB(0,0,255));
	oldpen=mypDC->SelectObject(&mypen);
	mypDC->MoveTo(1650,-1375);
	mypDC->LineTo(1795,-1375);
	
	//画框内的点
	CMainFrame* MainFramePoint=(CMainFrame*)mainfrm;
	int dArrLen=MainFramePoint->getarraylength();
	double *pdpos=MainFramePoint->getdPOSs();
	double *pdSTrace=MainFramePoint->getdLSFs();
	int i,xlen=picpos_x2-picpos_x1,ylen=picpos_y1-picpos_y2;
	int tempx=(int)((pdpos[0]*0.5/xmax+0.5)*xlen+picpos_x1+0.5),tempy=(int)(picpos_y2+pdSTrace[0]*ylen/ymax+0.5);
	mypDC->SetBkColor(RGB(255,255,255));
	mypDC->MoveTo(tempx,tempy);
	for(i=1;i<dArrLen;i++)
	{
		tempx=(int)((pdpos[i]*0.5/xmax+0.5)*xlen+picpos_x1+0.5);
		tempy=(int)(picpos_y2+pdSTrace[i]*ylen/ymax+0.5);
		mypDC->LineTo(tempx,tempy);
		mypDC->MoveTo(tempx,tempy);
	}
	
	mypDC->SelectObject(oldpen);
	mypDC->SelectObject(pOldFont);
}

void CVisualMTFView::PrintPageHeader(CDC *pDC,void *mainfrm)//状态3结果列表中打印表头
{
	CMainFrame* MainFramePoint=(CMainFrame*)mainfrm;
	CFont myTitleFont;
	pDC->SetMapMode(MM_LOMETRIC);
	myTitleFont.CreatePointFont(250,"黑体",pDC);
	CFont* pOldFont=pDC->SelectObject(&myTitleFont);
	pDC->TextOut(400,-100,"   Video MTF List Analysis");//头
	pDC->SelectObject(pOldFont);
	
	CString pntstr;
	pntstr.Format("Camera Name:  %s",MainFramePoint->getsLensName());//镜头名称
	pDC->TextOut(100,-200,pntstr);
	CTime temptime=*(MainFramePoint->getSavedTime());
	pntstr=temptime.Format("Saved Time:   %H:%M:%S %A, %B %d,%Y");//保存时间
	pDC->TextOut(100,-250,pntstr);
	temptime=CTime::GetCurrentTime();
	pntstr=temptime.Format("Printed Time: %H:%M:%S %A, %B %d,%Y");//打印时间
	pDC->TextOut(100,-300,pntstr);
	
	pntstr.Format("%-16s%-14s%-13s%-13s%-13s%-13s%-10s",
		"Freq(lp/mm)","MTF(T)","MTF(S)","LSF(T)","LSF(S)","pos(t)","pos(s)");//正式数表表头
	pDC->TextOut(100,-400,pntstr);
}

void CVisualMTFView::GetX(void *mainfrm)
{
	CMainFrame* FrameWndPoint=(CMainFrame*)mainfrm;
	double tmin=99999999.9,tmax=-1.0;
	int i,len=FrameWndPoint->getarraylength();
	double *dp1=FrameWndPoint->getdPOSs();
	double *dp2=FrameWndPoint->getdPOSt();
	for(i=0;i<len;i++)
	{
		if(dp1[i]<tmin)
		{
			tmin=dp1[i];
		}
		if(dp2[i]<tmin)
		{
			tmin=dp2[i];
		}
		if(dp1[i]>tmax)
		{
			tmax=dp1[i];
		}
		if(dp2[i]>tmax)
		{
			tmax=dp2[i];
		}
	}
	if(tmin+tmax>0)
	{
		xmin=-tmax;
		xmax=tmax;
	}
	else
	{
		xmin=tmin;
		xmax=-tmin;
	}
}

void CVisualMTFView::GetYMax(void *mainfrm)
{
	int i;
	double tempymax=-1.0;
	CMainFrame* FrameWndPoint=(CMainFrame*)mainfrm;
	int len=FrameWndPoint->getarraylength();
	double *dp1=FrameWndPoint->getdLSFs();
	double *dp2=FrameWndPoint->getdLSFt();
	for(i=0;i<len;i++)
	{
		if(dp1[i]>tempymax)
		{
			tempymax=dp1[i];
		}
		if(dp2[i]>tempymax)
		{
			tempymax=dp2[i];
		}
	}
	for(i=100;i<tempymax;i+=100);
	ymax=i;
}

void CVisualMTFView::PreparePrintText(int num,int textwidth,char *printtext)
{
	char myFormat[5]="%0d";
	if(textwidth>9)
	{
		textwidth%=10;
	}
	myFormat[1]=textwidth+'0';
	sprintf(printtext,myFormat,num);
}
