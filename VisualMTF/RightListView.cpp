// RightListView.cpp : implementation file
//

#include "stdafx.h"
#include "VisualMTF.h"
#include "RightListView.h"
#include "BackgroundWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// RightListView

IMPLEMENT_DYNCREATE(RightListView, CListView)

RightListView::RightListView()
{
}

RightListView::~RightListView()
{
}


BEGIN_MESSAGE_MAP(RightListView, CListView)
	//{{AFX_MSG_MAP(RightListView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// RightListView drawing

void RightListView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// RightListView diagnostics

#ifdef _DEBUG
void RightListView::AssertValid() const
{
	CListView::AssertValid();
}

void RightListView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// RightListView message handlers

BOOL RightListView::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.style=cs.style|LVS_REPORT;
	return CListView::PreCreateWindow(cs);
}

void RightListView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();
	const int numofColumn=7;
	int i;
	CString m_ColumnLabelStr[numofColumn]={"Frequence(lp/mm)","MTF(T)","MTF(S)","LSF(T)","LSF(S)","POS(t)","POS(s)"};
	CListCtrl& listctrl=GetListCtrl();
	listctrl.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_UNDERLINEHOT);
	int ColumnWidth[numofColumn]={140,100,100,100,100,100,100};
	for(i=0;i<numofColumn;i++)
	{
		listctrl.InsertColumn(i,m_ColumnLabelStr[i],LVCFMT_LEFT,ColumnWidth[i]);
	}
	
	CBackgroundWnd* FrameWndPoint=(CBackgroundWnd*)(GetParentFrame());
	int arraylen=FrameWndPoint->getarraylength();
	double* dpfreq=FrameWndPoint->getdFreq();
	double* dpmtft=FrameWndPoint->getdMTFt();
	double* dpmtfs=FrameWndPoint->getdMTFs();
	double* dplsft=FrameWndPoint->getdLSFt();
	double* dplsfs=FrameWndPoint->getdLSFs();
	double* dppost=FrameWndPoint->getdPOSt();
	double* dpposs=FrameWndPoint->getdPOSs();
	char insertbuffer[100];
	for(i=0;i<arraylen;i++)
	{
		sprintf(insertbuffer,"%.4lf",dpfreq[i]);
		listctrl.InsertItem(i,insertbuffer);
		sprintf(insertbuffer,"%.4lf",dpmtft[i]);
		listctrl.SetItemText(i,1,insertbuffer);
		sprintf(insertbuffer,"%.4lf",dpmtfs[i]);
		listctrl.SetItemText(i,2,insertbuffer);
		sprintf(insertbuffer,"%.4lf",dplsft[i]);
		listctrl.SetItemText(i,3,insertbuffer);
		sprintf(insertbuffer,"%.4lf",dplsfs[i]);
		listctrl.SetItemText(i,4,insertbuffer);
		sprintf(insertbuffer,"%.4lf",dppost[i]);
		listctrl.SetItemText(i,5,insertbuffer);
		sprintf(insertbuffer,"%.4lf",dpposs[i]);
		listctrl.SetItemText(i,6,insertbuffer);
	}
}