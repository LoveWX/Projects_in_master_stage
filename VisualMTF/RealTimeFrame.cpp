// RealTimeFrame.cpp : implementation file
//

#include "stdafx.h"
#include "VisualMTF.h"
#include "RealTimeFrame.h"

#include "RealTimeUp.h"
#include "RealTimeDown.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRealTimeFrame

IMPLEMENT_DYNCREATE(CRealTimeFrame, CFrameWnd)

CRealTimeFrame::CRealTimeFrame()
{
}

CRealTimeFrame::~CRealTimeFrame()
{
}


BEGIN_MESSAGE_MAP(CRealTimeFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CRealTimeFrame)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRealTimeFrame message handlers

BOOL CRealTimeFrame::PreCreateWindow(CREATESTRUCT& cs) 
{
	// TODO: Add your specialized code here and/or call the base class
	cs.style &= ~WS_MINIMIZEBOX;//ʹ�öԻ�����С���Ŀ�����Ч
	cs.style &= ~WS_MAXIMIZEBOX;//ʹ�öԻ�����󻯵Ŀ�����Ч
	return CFrameWnd::PreCreateWindow(cs);
}

BOOL CRealTimeFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
	CRect rc;
    GetClientRect(&rc);//��ȡ�Ի����С
    
	CSize PaneSize1(rc.Width(),100);//�Ϸ���ͼ�ߴ�ȷ��
	CSize PaneSize2(rc.Width(),rc.Height()-100);//�·���ͼ�ߴ�ȷ��
    m_wndSplitter.CreateStatic(this,2,1);//��̬�ָ��Ի���
    m_wndSplitter.CreateView(0,0,RUNTIME_CLASS(CRealTimeUp),PaneSize1,pContext);//��������ͼ
    m_wndSplitter.CreateView(1,0,RUNTIME_CLASS(CRealTimeDown),PaneSize2,pContext);//��������ͼ

	return CFrameWnd::OnCreateClient(lpcs, pContext);
}

void* CRealTimeFrame::GetUpView()
{
	return (void*)m_wndSplitter.GetPane(0,0);//��������ͼ
}



void* CRealTimeFrame::GetDownView()
{
	return (void*)m_wndSplitter.GetPane(1,0);//�������ͼ
}
