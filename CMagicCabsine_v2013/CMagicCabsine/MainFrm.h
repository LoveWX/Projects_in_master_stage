
// MainFrm.h : MainFrame 类的接口
//

#pragma once
#include "stdafx.h"
#include "PropertiesWnd.h"

#include "CMagicCabsineView.h"
#include "CMagicCabsineLeftView.h"
#include "CMagicCabsineRightView.h"
#include "CMagicCabsineDisplayView.h"
#include "CMagicCabsineInteractiveView.h"
#include "CMagicCabsineRegionModifyView.h"
#include "FixedSplitterWnd.h"

class MainFrame : public CFrameWndEx
{
	
protected: // 仅从序列化创建
	MainFrame();
	DECLARE_DYNCREATE(MainFrame)

// 特性
public:

// 操作
public:

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL LoadFrame(UINT nIDResource, DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, CWnd* pParentWnd = NULL, CCreateContext* pContext = NULL);

// 实现
public:
	virtual ~MainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // 控件条嵌入成员
	CMFCMenuBar       m_wndMenuBar;
	CMFCToolBar       m_wndToolBar;
	CMFCStatusBar     m_wndStatusBar;
	CMFCToolBarImages m_UserImages;
	CMFCToolBar       m_wndToolBar_splitRegion;

	//修改后的工具条
	CMFCToolBar       m_wndToolBar_upside;
	CMFCToolBar       m_wndToolBar_downside;
public:
	CPropertiesWnd    m_wndProperties;

	//自己添加用于分割标记的工具条
// 	CMFCToolBar       m_wndToolBar_splitMark;

// 生成的消息映射函数
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnViewCustomize();
	afx_msg LRESULT OnToolbarCreateNew(WPARAM wp, LPARAM lp);
	afx_msg void OnApplicationLook(UINT id);
	afx_msg void OnUpdateApplicationLook(CCmdUI* pCmdUI);
	DECLARE_MESSAGE_MAP()

	BOOL CreateDockingWindows();
	void SetDockingWindowIcons(BOOL bHiColorIcons);

//以下为zhouzhou添加的类成员和函数
public:
	CFixedSplitterWnd m_WndSplitter;//窗口分割类
	SHOW_VIEW_TYPE showViewType;
protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
public:
	afx_msg void OnNcPaint();
	afx_msg void OnShowLeftView();
	afx_msg void OnShowRightView();
	afx_msg void OnShowBothView();
};
