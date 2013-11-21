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
	cs.style &= ~WS_MINIMIZEBOX;//使得对话框最小化的开关无效
	cs.style &= ~WS_MAXIMIZEBOX;//使得对话框最大化的开关无效
	return CFrameWnd::PreCreateWindow(cs);
}

BOOL CThroughFocusFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
	CRect rc;
    GetClientRect(&rc);//获取对话框大小
    
	CSize PaneSize1(300,rc.Height());//左分视图尺寸确定（300，561）
	CSize PaneSize2(rc.Width()-300,rc.Height());//右分视图尺寸确定（588，561）
	int a=rc.Height();
	int b=rc.Width();
    m_wndSplitter.CreateStatic(this,1,2);//静态分隔对话框
    m_wndSplitter.CreateView(0,0,RUNTIME_CLASS(CThroughFocusLeft),PaneSize1,pContext);//创建左视图
    m_wndSplitter.CreateView(0,1,RUNTIME_CLASS(CThroughFocusRight),PaneSize2,pContext);//创建右视图

	return CFrameWnd::OnCreateClient(lpcs, pContext);
}

void* CThroughFocusFrame::GetLeftView()
{
	return (void*)m_wndSplitter.GetPane(0,0);//返回左视图
}

void* CThroughFocusFrame::GetRightView()
{
	return (void*)m_wndSplitter.GetPane(0,1);//返回右视图
}
