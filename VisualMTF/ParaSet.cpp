// ParaSet.cpp : implementation file
//

#include "stdafx.h"
#include "VisualMTF.h"
#include "ParaSet.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CParaSet dialog


CParaSet::CParaSet(CWnd* pParent /*=NULL*/)
	: CDialog(CParaSet::IDD, pParent)
{
	//{{AFX_DATA_INIT(CParaSet)
	CMainFrame* MainFramePoint=(CMainFrame*)((CFrameWnd*)AfxGetApp()->m_pMainWnd);
	m_dPinDiameter = MainFramePoint->getdPinDiameter();
	m_dAmplify = MainFramePoint->getdAmplify();
	m_dFocusLength = MainFramePoint->getdFocusLength();
	m_dFNumber = MainFramePoint->getdFNumber();
	m_dWaveLength = MainFramePoint->getdLength();
	m_dLength = MainFramePoint->getdLength();
	m_sLensName = MainFramePoint->getsLensName();
	//}}AFX_DATA_INIT
}


void CParaSet::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CParaSet)
	DDX_Text(pDX, IDC_EDIT1, m_dPinDiameter);
	DDX_Text(pDX, IDC_EDIT2, m_dAmplify);
	DDX_Text(pDX, IDC_EDIT3, m_dFocusLength);
	DDX_Text(pDX, IDC_EDIT4, m_dFNumber);
	DDX_Text(pDX, IDC_EDIT5, m_dWaveLength);
	DDX_Text(pDX, IDC_EDIT6, m_dLength);
	DDX_Text(pDX, IDC_EDIT7, m_sLensName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CParaSet, CDialog)
	//{{AFX_MSG_MAP(CParaSet)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CParaSet message handlers
