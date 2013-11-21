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
	cs.style &= ~WS_MINIMIZEBOX;//使得对话框最小化的开关无效
	cs.style &= ~WS_MAXIMIZEBOX;//使得对话框最大化的开关无效
	return CFrameWnd::PreCreateWindow(cs);
}

BOOL CRealTimeFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
	CRect rc;
    GetClientRect(&rc);//获取对话框大小
    
	CSize PaneSize1(rc.Width(),100);//上分视图尺寸确定
	CSize PaneSize2(rc.Width(),rc.Height()-100);//下分视图尺寸确定
    m_wndSplitter.CreateStatic(this,2,1);//静态分隔对话框
    m_wndSplitter.CreateView(0,0,RUNTIME_CLASS(CRealTimeUp),PaneSize1,pContext);//创建上视图
    m_wndSplitter.CreateView(1,0,RUNTIME_CLASS(CRealTimeDown),PaneSize2,pContext);//创建下视图

	return CFrameWnd::OnCreateClient(lpcs, pContext);
}

void* CRealTimeFrame::GetUpView()
{
	return (void*)m_wndSplitter.GetPane(0,0);//返回上视图
}



void* CRealTimeFrame::GetDownView()
{
	return (void*)m_wndSplitter.GetPane(1,0);//获得下视图
}
