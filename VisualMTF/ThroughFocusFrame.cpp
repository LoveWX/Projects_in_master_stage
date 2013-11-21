// ThroughFocusFrame.cpp : implementation file
//

#include "stdafx.h"
#include "VisualMTF.h"
#include "ThroughFocusFrame.h"

#include "ThroughFocusLeft.h"
#include "ThroughFocusRight.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CThroughFocusFrame

IMPLEMENT_DYNCREATE(CThroughFocusFrame, CFrameWnd)

CThroughFocusFrame::CThroughFocusFrame()
{
}

CThroughFocusFrame::~CThroughFocusFrame()
{
}


BEGIN_MESSAGE_MAP(CThroughFocusFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CThroughFocusFrame)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CThroughFocusFrame message handlers

BOOL CThroughFocusFrame::PreCreateWindow(CREATESTRUCT& cs) 
{
	// TODO: Add your specialized code here and/or call the base class
	cs.style &= ~WS_MINIMIZEBOX;//ʹ�öԻ�����С���Ŀ�����Ч
	cs.style &= ~WS_MAXIMIZEBOX;//ʹ�öԻ�����󻯵Ŀ�����Ч
	return CFrameWnd::PreCreateWindow(cs);
}

BOOL CThroughFocusFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
	CRect rc;
    GetClientRect(&rc);//��ȡ�Ի����С
    
	CSize PaneSize1(300,rc.Height());//�����ͼ�ߴ�ȷ����300��561��
	CSize PaneSize2(rc.Width()-300,rc.Height());//�ҷ���ͼ�ߴ�ȷ����588��561��
	int a=rc.Height();
	int b=rc.Width();
    m_wndSplitter.CreateStatic(this,1,2);//��̬�ָ��Ի���
    m_wndSplitter.CreateView(0,0,RUNTIME_CLASS(CThroughFocusLeft),PaneSize1,pContext);//��������ͼ
    m_wndSplitter.CreateView(0,1,RUNTIME_CLASS(CThroughFocusRight),PaneSize2,pContext);//��������ͼ

	return CFrameWnd::OnCreateClient(lpcs, pContext);
}

void* CThroughFocusFrame::GetLeftView()
{
	return (void*)m_wndSplitter.GetPane(0,0);//��������ͼ
}

void* CThroughFocusFrame::GetRightView()
{
	return (void*)m_wndSplitter.GetPane(0,1);//��������ͼ
}
