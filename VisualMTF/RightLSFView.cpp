// RightLSFView.cpp : implementation file
//

#include "stdafx.h"
#include "VisualMTF.h"
#include "RightLSFView.h"
#include "LeftFormView.h"
#include "BackgroundWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// RightLSFView

IMPLEMENT_DYNCREATE(RightLSFView, CView)

RightLSFView::RightLSFView()
{
	framepos_x1=20;
	framepos_y1=70;
	framepos_x2=405;
	framepos_y2=480;
	picpos_x1=65;
	picpos_y1=120;
	picpos_x2=365;
	picpos_y2=420;
	BColorR=185;
	BColorG=195;
	BColorB=255;
	xmax=0.0;
	ymax=0.0;
}

RightLSFView::~RightLSFView()
{
}


BEGIN_MESSAGE_MAP(RightLSFView, CView)
	//{{AFX_MSG_MAP(RightLSFView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// RightLSFView drawing

void RightLSFView::OnDraw(CDC* pDC)
{
	//CDocument* pDoc = GetDocument();
	// TODO: add draw code here
	//ASSERT_VALID(pDoc);
	DrawBackground();
	DrawFrame();
	DrawGrid();
	CBackgroundWnd* FrameWndPoint=(CBackgroundWnd*)(GetParentFrame());
	LeftFormView* LeftFormViewPoint=(LeftFormView*)(FrameWndPoint->GetLeftView());
	UpdateTrace(TRUE,LeftFormViewPoint->GetHSelected(),LeftFormViewPoint->GetVSelected());
}

void RightLSFView::DrawBackground()
{
	CDC *mypDC=GetDC();
	CRect rc;
	GetClientRect(&rc);
	CBrush mybrush;
	mybrush.CreateSolidBrush(RGB(BColorR,BColorG,BColorB));
	CBrush *oldbrush;
	oldbrush=mypDC->SelectObject(&mybrush);
	mypDC->Rectangle(rc.left-1,rc.top-1,rc.right+1,rc.bottom+1);
	mypDC->SelectObject(oldbrush);
}

void RightLSFView::GetX()
{
	CBackgroundWnd* FrameWndPoint=(CBackgroundWnd*)(GetParentFrame());
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

void RightLSFView::GetYMax()
{
	int i;
	double tempymax=-1.0;
	CBackgroundWnd* FrameWndPoint=(CBackgroundWnd*)(GetParentFrame());
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

void RightLSFView::PreparePrintText(int num,int textwidth,char *printtext)
{
	char myFormat[5]="%0d";
	if(textwidth>9)
	{
		textwidth%=10;
	}
	myFormat[1]=textwidth+'0';
	sprintf(printtext,myFormat,num);
}

void RightLSFView::DrawFrame()
{
	CDC *mypDC=GetDC();
	mypDC->SetBkColor(RGB(BColorR,BColorG,BColorB));
	CBrush mybrush;
	mybrush.CreateSolidBrush(RGB(BColorR,BColorG,BColorB));
	CBrush *oldbrush;
	oldbrush=mypDC->SelectObject(&mybrush);

	int textwidth=3;
	GetYMax();
	char printtext[10];
	mypDC->TextOut(155,30,"LINE SPREAD FUNCTION");
	mypDC->Rectangle(framepos_x1,framepos_y1,framepos_x2,framepos_y2);
	mypDC->TextOut(35,95,"Intensity");
	sprintf(printtext,"%d",(int)ymax);
	mypDC->TextOut(35,112,printtext);
	PreparePrintText((int)(ymax*0.8),textwidth,printtext);
	mypDC->TextOut(35,172,printtext);
	PreparePrintText((int)(ymax*0.6),textwidth,printtext);
	mypDC->TextOut(35,232,printtext);
	PreparePrintText((int)(ymax*0.4),textwidth,printtext);
	mypDC->TextOut(35,292,printtext);
	PreparePrintText((int)(ymax*0.2),textwidth,printtext);
	mypDC->TextOut(35,352,printtext);
	mypDC->TextOut(35,412,"    0");
	mypDC->TextOut(165,450,"Distance(microns)");
	GetX();
	sprintf(printtext,"%.3lf",xmin);
	mypDC->TextOut(55,425,printtext);
	mypDC->TextOut(200,425,"0.000");
	sprintf(printtext,"%.3lf",xmax);
	mypDC->TextOut(345,425,printtext);
	mypDC->Rectangle(picpos_x1,picpos_y1,picpos_x2,picpos_y2);
	mypDC->SelectObject(oldbrush);
}

void RightLSFView::DrawGrid()
{
	CDC *mypDC=GetDC();
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
	mypDC->Rectangle(picpos_x1+1,picpos_y1+1,picpos_x2,picpos_y2);
	
	mypen2.CreatePen(PS_DOT,1,RGB(0,0,0));
	oldpen=mypDC->SelectObject(&mypen2);
	
	//画竖线
	gridwidth=(picpos_x2-picpos_x1)/numofblock;
	for(gridpos=picpos_x1+gridwidth;gridpos<picpos_x2;gridpos+=gridwidth)
	{
		mypDC->MoveTo(gridpos,picpos_y2);
		mypDC->LineTo(gridpos,picpos_y1);
	}
	
	//画横线
	gridwidth=(picpos_y2-picpos_y1)/numofblock;
	for(gridpos=picpos_y1+gridwidth;gridpos<picpos_y2;gridpos+=gridwidth)
	{
		mypDC->MoveTo(picpos_x1,gridpos);
		mypDC->LineTo(picpos_x2,gridpos);
	}
	
	mypDC->SelectObject(oldpen);
	
	for(gridpos=picpos_y1+gridwidth;gridpos<picpos_y2;gridpos+=gridwidth)
	{
		mypDC->MoveTo(picpos_x1-2,gridpos);
		mypDC->LineTo(picpos_x1,gridpos);
	}
	gridwidth=(picpos_x2-picpos_x1)/numofblock;
	for(gridpos=picpos_x1+gridwidth;gridpos<picpos_x2;gridpos+=gridwidth)
	{
		mypDC->MoveTo(gridpos,picpos_y2);
		mypDC->LineTo(gridpos,picpos_y2+2);
	}
	
	mypDC->SelectObject(oldbrush);
}

void RightLSFView::UpdateTrace(BOOL Redraw,BOOL TTrace,BOOL STrace)
{
	if(Redraw | (!TTrace) | (!STrace))
		ErasureTrace();
	if(TTrace)
		DrawTTrace();
	if(STrace)
		DrawSTrace();
}

void RightLSFView::DrawTTrace()
{
	CDC *mypDC=GetDC();
	mypDC->SetBkColor(RGB(BColorR,BColorG,BColorB));
	mypDC->TextOut(550,200,"子午方向");
	CPen mypen;
	CPen *oldpen;
	mypen.CreatePen(PS_SOLID,1,RGB(255,0,0));
	oldpen=mypDC->SelectObject(&mypen);
	mypDC->MoveTo(450,207);
	mypDC->LineTo(535,207);


	CBackgroundWnd* FrameWndPoint=(CBackgroundWnd*)(GetParentFrame());
	int dArrLen=FrameWndPoint->getarraylength();
	double *pdpos=FrameWndPoint->getdPOSt();
	double *pdTTrace=FrameWndPoint->getdLSFt();
	int i,xlen=picpos_x2-picpos_x1,ylen=picpos_y2-picpos_y1;
	int tempx=(int)((pdpos[0]*0.5/xmax+0.5)*xlen+picpos_x1+0.5),tempy=(int)(picpos_y2-pdTTrace[0]*ylen/ymax+0.5);
	mypDC->SetBkColor(RGB(255,255,255));
	mypDC->MoveTo(tempx,tempy);
	for(i=1;i<dArrLen;i++)
	{
		tempx=(int)((pdpos[i]*0.5/xmax+0.5)*xlen+picpos_x1+0.5);
		tempy=(int)(picpos_y2-pdTTrace[i]*ylen/ymax+0.5);
		mypDC->LineTo(tempx,tempy);
		mypDC->MoveTo(tempx,tempy);
	}
	mypDC->SelectObject(oldpen);
}

void RightLSFView::DrawSTrace()
{
	CDC *mypDC=GetDC();
	mypDC->SetBkColor(RGB(BColorR,BColorG,BColorB));
	mypDC->TextOut(550,220,"弧矢方向");
	CPen mypen;
	CPen *oldpen;
	mypen.CreatePen(PS_SOLID,1,RGB(0,0,255));
	oldpen=mypDC->SelectObject(&mypen);
	mypDC->MoveTo(450,227);
	mypDC->LineTo(535,227);

	CBackgroundWnd* FrameWndPoint=(CBackgroundWnd*)(GetParentFrame());
	int dArrLen=FrameWndPoint->getarraylength();
	double *pdpos=FrameWndPoint->getdPOSs();
	double *pdSTrace=FrameWndPoint->getdLSFs();
	int i,xlen=picpos_x2-picpos_x1,ylen=picpos_y2-picpos_y1;
	int tempx=(int)((pdpos[0]*0.5/xmax+0.5)*xlen+picpos_x1+0.5),tempy=(int)(picpos_y2-pdSTrace[0]*ylen/ymax+0.5);
	mypDC->SetBkColor(RGB(255,255,255));
	mypDC->MoveTo(tempx,tempy);
	for(i=1;i<dArrLen;i++)
	{
		tempx=(int)((pdpos[i]*0.5/xmax+0.5)*xlen+picpos_x1+0.5);
		tempy=(int)(picpos_y2-pdSTrace[i]*ylen/ymax+0.5);
		mypDC->LineTo(tempx,tempy);
		mypDC->MoveTo(tempx,tempy);
	}

	/*
	//画框内的点
	CBackgroundWnd* FrameWndPoint=(CBackgroundWnd*)(GetParentFrame());
	int dArrLen=FrameWndPoint->getarraylength();
	double *pdFreq=FrameWndPoint->getdFreq();
	double *pdSTrace=FrameWndPoint->getdLSFs();
	int i,xlen=picpos_x2-picpos_x1,ylen=picpos_y2-picpos_y1;
	int tempx=(int)(pdFreq[0]*xlen*0.1+picpos_x1+0.5),tempy=(int)(picpos_y2-pdSTrace[0]*ylen/250.0+0.5);
	mypDC->SetBkColor(RGB(255,255,255));
	mypDC->MoveTo(tempx,tempy);
	for(i=1;i<dArrLen;i++)
	{
		tempx=(int)(pdFreq[i]*xlen*0.1+picpos_x1+0.5);
		tempy=(int)(picpos_y2-pdSTrace[i]*ylen/250.0+0.5);
		mypDC->LineTo(tempx,tempy);
		mypDC->MoveTo(tempx,tempy);
	}
	*/
	mypDC->SelectObject(oldpen);
}

void RightLSFView::ErasureTrace()
{
	CDC *mypDC=GetDC();
	CPen mypen1,mypen2;
	CPen *oldpen;
	mypen1.CreatePen(PS_SOLID,1,RGB(BColorR,BColorG,BColorB));
	mypDC->SelectObject(&mypen1);
	CBrush mybrush1,mybrush2;
	CBrush *oldbrush;
	mybrush1.CreateSolidBrush(RGB(BColorR,BColorG,BColorB));
	mypDC->SelectObject(&mybrush1);
	mypDC->Rectangle(450,200,599,236);
	
	mypen2.CreatePen(PS_NULL,1,RGB(255,255,255));
	oldpen=mypDC->SelectObject(&mypen2);
	mybrush2.CreateSolidBrush(RGB(255,255,255));
	oldbrush=mypDC->SelectObject(&mybrush2);
	mypDC->Rectangle(picpos_x1+1,picpos_y1+1,picpos_x2,picpos_y2);
	DrawGrid();
	
	mypDC->SelectObject(oldpen);
	mypDC->SelectObject(oldbrush);
}

/////////////////////////////////////////////////////////////////////////////
// RightLSFView diagnostics

#ifdef _DEBUG
void RightLSFView::AssertValid() const
{
	CView::AssertValid();
}

void RightLSFView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// RightLSFView message handlers
