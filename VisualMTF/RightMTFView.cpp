// RightMTFView.cpp : implementation file
//

#include "stdafx.h"
#include "VisualMTF.h"
#include "RightMTFView.h"
#include "LeftFormView.h"
#include "BackgroundWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// RightMTFView

IMPLEMENT_DYNCREATE(RightMTFView, CView)

RightMTFView::RightMTFView()
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
}

RightMTFView::~RightMTFView()
{
}


BEGIN_MESSAGE_MAP(RightMTFView, CView)
	//{{AFX_MSG_MAP(RightMTFView)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// RightMTFView drawing

void RightMTFView::OnDraw(CDC* pDC)
{
	//CDocument* pDoc = GetDocument();
	// TODO: add draw code here
	//ASSERT_VALID(pDoc);
	CBackgroundWnd* FrameWndPoint=(CBackgroundWnd*)(GetParentFrame());
	LeftFormView* LeftFormViewPoint=(LeftFormView*)(FrameWndPoint->GetLeftView());
	DrawBackground();
	DrawFrame();
	DrawGrid();
	UpdateTrace(TRUE,LeftFormViewPoint->GetHSelected(),LeftFormViewPoint->GetVSelected());
}

void RightMTFView::DrawBackground()
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

double RightMTFView::getMTFmax()
{
	return xmax;
}

void RightMTFView::GetXmax()
{
	const double thexmax=400.0;//�˴�ΪMTF������ʾƵ����������ޣ�����CMainFrame::GetTypedmax()�µĸ�ֵһ��ı�
	CBackgroundWnd* FrameWndPoint=(CBackgroundWnd*)(GetParentFrame());
	LeftFormView* LeftFormViewPoint=(LeftFormView*)(FrameWndPoint->GetLeftView());
	double f=FrameWndPoint->getOriginalF();
	xmax=f;
	while(xmax<=thexmax)
	{
		xmax+=f;
	}
	xmax-=f;
}

int RightMTFView::GetPrintTimes()
{
	CBackgroundWnd* FrameWndPoint=(CBackgroundWnd*)(GetParentFrame());
	LeftFormView* LeftFormViewPoint=(LeftFormView*)(FrameWndPoint->GetLeftView());
	double f;
	if(LeftFormViewPoint->GetInterpolationSelected())
	{
		f=FrameWndPoint->getCurrentF();
	}
	else
	{
		f=FrameWndPoint->getOriginalF();
	}
	return (int)(xmax/f+0.001);
}

void RightMTFView::DrawFrame()
{
	CDC *mypDC=GetDC();
	mypDC->SetBkColor(RGB(BColorR,BColorG,BColorB));
	CBrush mybrush;
	mybrush.CreateSolidBrush(RGB(BColorR,BColorG,BColorB));
	CBrush *oldbrush;
	oldbrush=mypDC->SelectObject(&mybrush);

	char printtext[10];
	GetXmax();	
	mypDC->TextOut(165,30,"Video MTF Data");
	mypDC->Rectangle(framepos_x1,framepos_y1,framepos_x2,framepos_y2);
	mypDC->TextOut(35,95,"Modulation");
	mypDC->TextOut(35,112,"1.00");
	mypDC->TextOut(35,172,"0.80");
	mypDC->TextOut(35,232,"0.60");
	mypDC->TextOut(35,292,"0.40");
	mypDC->TextOut(35,352,"0.20");
	mypDC->TextOut(35,412,"    0");
	mypDC->TextOut(165,450,"Frequency(lp/mm)");
	sprintf(printtext,"%.2lf",xmax*0.5);
	mypDC->TextOut(200,425,printtext);
	sprintf(printtext,"%.2lf",xmax);
	mypDC->TextOut(345,425,printtext);
	mypDC->Rectangle(picpos_x1,picpos_y1,picpos_x2,picpos_y2);
	mypDC->SelectObject(oldbrush);
}

void RightMTFView::DrawGrid()
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

	//������
	gridwidth=(picpos_x2-picpos_x1)/numofblock;
	for(gridpos=picpos_x1+gridwidth;gridpos<picpos_x2;gridpos+=gridwidth)
	{
		mypDC->MoveTo(gridpos,picpos_y2);
		mypDC->LineTo(gridpos,picpos_y1);
	}

	//������
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

void RightMTFView::UpdateTrace(BOOL Redraw,BOOL TTrace,BOOL STrace)
{
	if(Redraw | (!TTrace) | (!STrace))
		ErasureTrace();
	if(TTrace)
		DrawTTrace();
	if(STrace)
		DrawSTrace();
}

void RightMTFView::DrawTTrace()
{
	CDC *mypDC=GetDC();
	mypDC->SetBkColor(RGB(BColorR,BColorG,BColorB));
	mypDC->TextOut(550,200,"���緽��");//��ע
	CPen mypen;
	CPen *oldpen;
	mypen.CreatePen(PS_SOLID,1,RGB(255,0,0));
	oldpen=mypDC->SelectObject(&mypen);
	mypDC->MoveTo(450,207);
	mypDC->LineTo(535,207);//������
	
	//�����ڵĵ�
	CBackgroundWnd* FrameWndPoint=(CBackgroundWnd*)(GetParentFrame());
	LeftFormView* LeftFormViewPoint=(LeftFormView*)(FrameWndPoint->GetLeftView());
	int dArrLen,fmaxtimes=GetPrintTimes();
	double *pdTTrace;
	if(LeftFormViewPoint->GetInterpolationSelected())//��Ҫ��ֵ
	{
		dArrLen=FrameWndPoint->getExtendedlength();//���ֵ�������鳤��
		pdTTrace=FrameWndPoint->getExtendedMTFt();//���ֵ����
	}
	else//����Ҫ��ֵ
	{
		dArrLen=FrameWndPoint->getarraylength();//��ԭʼ�������鳤��
		pdTTrace=FrameWndPoint->getdMTFt();//��ԭʼ����
	}
	int i,xlen=picpos_x2-picpos_x1,ylen=picpos_y2-picpos_y1;
	int tempx=picpos_x1,tempy=picpos_y1;
	mypDC->SetBkColor(RGB(255,255,255));
	mypDC->MoveTo(tempx,tempy);
	for(i=1;i<dArrLen&&i<=fmaxtimes;i++)
	{
		tempx=(int)((double)i/fmaxtimes*xlen+picpos_x1+0.5);
		tempy=(int)(picpos_y2-pdTTrace[i]*ylen+0.5);
		mypDC->LineTo(tempx,tempy);
		mypDC->MoveTo(tempx,tempy);
	}
	
	mypDC->SelectObject(oldpen);
}

void RightMTFView::DrawSTrace()
{
	CDC *mypDC=GetDC();
	mypDC->SetBkColor(RGB(BColorR,BColorG,BColorB));
	mypDC->TextOut(550,220,"��ʸ����");//��ע
	CPen mypen;
	CPen *oldpen;
	mypen.CreatePen(PS_SOLID,1,RGB(0,0,255));
	oldpen=mypDC->SelectObject(&mypen);
	mypDC->MoveTo(450,227);
	mypDC->LineTo(535,227);//������

	//�����ڵĵ�
	CBackgroundWnd* FrameWndPoint=(CBackgroundWnd*)(GetParentFrame());
	LeftFormView* LeftFormViewPoint=(LeftFormView*)(FrameWndPoint->GetLeftView());
	int dArrLen,fmaxtimes=GetPrintTimes();
	double *pdSTrace;
	if(LeftFormViewPoint->GetInterpolationSelected())//��Ҫ��ֵ
	{
		dArrLen=FrameWndPoint->getExtendedlength();//���ֵ�������鳤��
		pdSTrace=FrameWndPoint->getExtendedMTFs();//���ֵ����
	}
	else//����Ҫ��ֵ
	{
		dArrLen=FrameWndPoint->getarraylength();//��ԭʼ�������鳤��
		pdSTrace=FrameWndPoint->getdMTFs();//��ԭʼ����
	}
	int i,xlen=picpos_x2-picpos_x1,ylen=picpos_y2-picpos_y1;
	int tempx=picpos_x1,tempy=picpos_y1;
	mypDC->SetBkColor(RGB(255,255,255));
	mypDC->MoveTo(tempx,tempy);
	for(i=1;i<dArrLen&&i<=fmaxtimes;i++)
	{
		tempx=(int)((double)i/fmaxtimes*xlen+picpos_x1+0.5);
		tempy=(int)(picpos_y2-pdSTrace[i]*ylen+0.5);
		mypDC->LineTo(tempx,tempy);
		mypDC->MoveTo(tempx,tempy);
	}

	mypDC->SelectObject(oldpen);
}

void RightMTFView::ErasureTrace()
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

void RightMTFView::ChangeXMax(double mymax)////??????????????????
{
	CDC *mypDC=GetDC();
	/*CRect rc;
	//GetClientRect(&rc);
	CBrush mybrush;
	mybrush.CreateSolidBrush(RGB(BColorR,BColorG,BColorB));
	CBrush *oldbrush;
	oldbrush=mypDC->SelectObject(&mybrush);
	mypDC->Rectangle(300,400,365,420);//????
	*/
	mypDC->SetBkColor(RGB(BColorR,BColorG,BColorB));
	//mypDC->TextOut(550,220,"S-Trace");

	char printtext[10];
	xmax=(double)mymax;
	sprintf(printtext,"%.2lf",xmax*0.5);
	mypDC->TextOut(200,425,printtext);
	sprintf(printtext,"%.2lf",xmax);
	mypDC->TextOut(345,425,printtext);
	//mypDC->SelectObject(oldbrush);

}

/////////////////////////////////////////////////////////////////////////////
// RightMTFView diagnostics

#ifdef _DEBUG
void RightMTFView::AssertValid() const
{
	CView::AssertValid();
}

void RightMTFView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// RightMTFView message handlers
