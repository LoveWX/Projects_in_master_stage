// RightTextView.cpp : implementation file
//

#include "stdafx.h"
#include "VisualMTF.h"
#include "RightTextView.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// RightTextView

IMPLEMENT_DYNCREATE(RightTextView, CFormView)

RightTextView::RightTextView()
	: CFormView(RightTextView::IDD)
{
	m_brush.CreateSolidBrush(RGB(255,255,255));//将背景初始化为白色
	//{{AFX_DATA_INIT(RightTextView)
	CMainFrame* MainFramePoint=(CMainFrame*)((CFrameWnd*)AfxGetApp()->m_pMainWnd);
	if(MainFramePoint==NULL)		//程序开始时设置为默认值
	{
		m_dPinDiameter = 10.0;
		m_dAmplify = 20.0;
		m_dFocusLength = 50.0;
		m_dFNumber = 8.0;
		m_dWaveLength = 550.0;
		m_dLength = 2000.0;
		m_sLensName = _T("Unknown Name1");
	}
	else
	{
		m_dPinDiameter = MainFramePoint->getdPinDiameter();
		m_dAmplify = MainFramePoint->getdAmplify();
		m_sLensName = MainFramePoint->getsLensName();
		m_dFocusLength = MainFramePoint->getdFocusLength();
		m_dFNumber = MainFramePoint->getdFNumber();
		m_dWaveLength = MainFramePoint->getdWaveLength();
		m_dLength = MainFramePoint->getdLength();
	}
	//}}AFX_DATA_INIT
}

RightTextView::~RightTextView()
{
}

void RightTextView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(RightTextView)
	DDX_Text(pDX, IDC_EDIT2, m_dAmplify);
	DDX_Text(pDX, IDC_EDIT1, m_dPinDiameter);
	DDX_Text(pDX, IDC_EDIT3, m_sLensName);
	DDX_Text(pDX, IDC_EDIT4, m_dFocusLength);
	DDX_Text(pDX, IDC_EDIT5, m_dFNumber);
	DDX_Text(pDX, IDC_EDIT6, m_dWaveLength);
	DDX_Text(pDX, IDC_EDIT7, m_dLength);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(RightTextView, CFormView)
	//{{AFX_MSG_MAP(RightTextView)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// RightTextView diagnostics

#ifdef _DEBUG
void RightTextView::AssertValid() const
{
	CFormView::AssertValid();
}

void RightTextView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// RightTextView message handlers

HBRUSH RightTextView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CFormView::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	
	// TODO: Return a different brush if the default is not desired
	//return hbr;
	
	pDC->SetBkMode(TRANSPARENT);
	return m_brush;		//返回自己定义的画刷
}
