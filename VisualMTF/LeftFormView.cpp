// LeftFormView.cpp : implementation file
//

#include "stdafx.h"
#include "VisualMTF.h"
#include "LeftFormView.h"
#include "RightMTFView.h"
#include "RightLSFView.h"
#include "BackgroundWnd.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// LeftFormView

IMPLEMENT_DYNCREATE(LeftFormView, CFormView)

LeftFormView::LeftFormView()
	: CFormView(LeftFormView::IDD)
{
	double tmp;
	//{{AFX_DATA_INIT(LeftFormView)
	m_vcheck = TRUE;
	m_hcheck = TRUE;
	m_iComboDefaultSel = 2;
	m_Interpolationcheck = TRUE;
//	m_TypedMax = 0.0;

	CMainFrame* MainFramePoint=(CMainFrame*)((CFrameWnd*)AfxGetApp()->m_pMainWnd);
	
	tmp=MainFramePoint->GetTypedmax();
	m_TypedMax=tmp;

	//}}AFX_DATA_INIT
	ComboLastMode=-1;
}



LeftFormView::~LeftFormView()
{
}

void LeftFormView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(LeftFormView)
	DDX_Control(pDX, IDC_BUTTON1, m_ChangeMax);
	DDX_Control(pDX, IDC_COMBO1, m_selmode);
	DDX_Check(pDX, IDC_CHECK2, m_vcheck);
	DDX_Check(pDX, IDC_CHECK1, m_hcheck);
	DDX_CBIndex(pDX, IDC_COMBO1, m_iComboDefaultSel);
	DDX_Check(pDX, IDC_CHECK3, m_Interpolationcheck);
	DDX_Text(pDX, IDC_EDIT1, m_TypedMax);
	//}}AFX_DATA_MAP
}

BOOL LeftFormView::GetHSelected()
{
	return m_hcheck;
}

BOOL LeftFormView::GetVSelected()
{
	return m_vcheck;
}

BOOL LeftFormView::GetInterpolationSelected()
{
	return m_Interpolationcheck;
}

BEGIN_MESSAGE_MAP(LeftFormView, CFormView)
	//{{AFX_MSG_MAP(LeftFormView)
	ON_CBN_SELCHANGE(IDC_COMBO1, OnSelchangeCombo)
	ON_BN_CLICKED(IDC_CHECK1, OnCheckHChanged)
	ON_BN_CLICKED(IDC_CHECK2, OnCheckVChanged)
	ON_BN_CLICKED(IDC_CHECK3, OnCheckInterpolation)
	ON_BN_CLICKED(IDC_BUTTON1, OnButtonChangeMax)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// LeftFormView diagnostics

#ifdef _DEBUG
void LeftFormView::AssertValid() const
{
	CFormView::AssertValid();
}

void LeftFormView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// LeftFormView message handlers

void LeftFormView::OnSelchangeCombo()
{
	int CurrentMode=m_selmode.GetCurSel();
	if(CurrentMode==ComboLastMode)
		return;
	CBackgroundWnd* FrameWndPoint=(CBackgroundWnd*)(GetParentFrame());
	FrameWndPoint->ChangeView(CurrentMode);
	ComboLastMode=CurrentMode;
}

void LeftFormView::OnCheckHChanged() 
{
	// TODO: Add your control notification handler code here
	if(m_hcheck)
		m_hcheck=FALSE;
	else
		m_hcheck=TRUE;
	int CurrentMode=m_selmode.GetCurSel();
	CBackgroundWnd* FrameWndPoint=(CBackgroundWnd*)(GetParentFrame());
	if(CurrentMode==0)
	{
		RightMTFView* RightMTFViewPoint=(RightMTFView*)(FrameWndPoint->GetRightView());
		RightMTFViewPoint->UpdateTrace(FALSE,m_hcheck,m_vcheck);
	}
	else if(CurrentMode==1)
	{
		RightLSFView* RightLSFViewPoint=(RightLSFView*)(FrameWndPoint->GetRightView());
		RightLSFViewPoint->UpdateTrace(FALSE,m_hcheck,m_vcheck);
	}
}

void LeftFormView::OnCheckVChanged() 
{
	// TODO: Add your control notification handler code here
	if(m_vcheck)
		m_vcheck=FALSE;
	else
		m_vcheck=TRUE;
	int CurrentMode=m_selmode.GetCurSel();
	CBackgroundWnd* FrameWndPoint=(CBackgroundWnd*)(GetParentFrame());
	if(CurrentMode==0)
	{
		RightMTFView* RightMTFViewPoint=(RightMTFView*)(FrameWndPoint->GetRightView());
		RightMTFViewPoint->UpdateTrace(FALSE,m_hcheck,m_vcheck);
	}
	else if(CurrentMode==1)
	{
		RightLSFView* RightLSFViewPoint=(RightLSFView*)(FrameWndPoint->GetRightView());
		RightLSFViewPoint->UpdateTrace(FALSE,m_hcheck,m_vcheck);
	}
}

void LeftFormView::OnCheckInterpolation() 
{
	// TODO: Add your control notification handler code here
	if(m_Interpolationcheck==FALSE)
		m_Interpolationcheck=TRUE;
	else
		m_Interpolationcheck=FALSE;
	int CurrentMode=m_selmode.GetCurSel();
	CBackgroundWnd* FrameWndPoint=(CBackgroundWnd*)(GetParentFrame());
	if(CurrentMode==0)
	{
		RightMTFView* RightMTFViewPoint=(RightMTFView*)(FrameWndPoint->GetRightView());
		RightMTFViewPoint->UpdateTrace(TRUE,m_hcheck,m_vcheck);
	}
	else if(CurrentMode==1)
	{
		RightLSFView* RightLSFViewPoint=(RightLSFView*)(FrameWndPoint->GetRightView());
		RightLSFViewPoint->UpdateTrace(FALSE,m_hcheck,m_vcheck);
	}
}

void LeftFormView::OnButtonChangeMax() 
{
	// TODO: Add your control notification handler code here
	if(m_selmode.GetCurSel()!=0)
	{
		return;
	}
	CBackgroundWnd* FrameWndPoint=(CBackgroundWnd*)(GetParentFrame());
	UpdateData(true);
	double temp=FrameWndPoint->getOriginalF();
	int len=FrameWndPoint->getarraylength();
	//if(m_TypedMax<temp)
	if(m_TypedMax<10)
	{
		MessageBox("The max value can not be too small!");
		return;
	}
	temp=temp*(len-1);
	temp=(temp+temp)/3;
	if(m_TypedMax>=temp)
	{
		MessageBox("The max value can not be too large!");
		return;
	}
	RightMTFView* RightMTFViewPoint=(RightMTFView*)(FrameWndPoint->GetRightView());
	RightMTFViewPoint->ChangeXMax(m_TypedMax);
	RightMTFViewPoint->UpdateTrace(TRUE,m_hcheck,m_vcheck);
}
