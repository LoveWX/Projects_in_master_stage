
// MainFrm.h : MainFrame ��Ľӿ�
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
	
protected: // �������л�����
	MainFrame();
	DECLARE_DYNCREATE(MainFrame)

// ����
public:

// ����
public:

// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL LoadFrame(UINT nIDResource, DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, CWnd* pParentWnd = NULL, CCreateContext* pContext = NULL);

// ʵ��
public:
	virtual ~MainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // �ؼ���Ƕ���Ա
	CMFCMenuBar       m_wndMenuBar;
	CMFCToolBar       m_wndToolBar;
	CMFCStatusBar     m_wndStatusBar;
	CMFCToolBarImages m_UserImages;
	CMFCToolBar       m_wndToolBar_splitRegion;

	//�޸ĺ�Ĺ�����
	CMFCToolBar       m_wndToolBar_upside;
	CMFCToolBar       m_wndToolBar_downside;
public:
	CPropertiesWnd    m_wndProperties;

	//�Լ�������ڷָ��ǵĹ�����
// 	CMFCToolBar       m_wndToolBar_splitMark;

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnViewCustomize();
	afx_msg LRESULT OnToolbarCreateNew(WPARAM wp, LPARAM lp);
	afx_msg void OnApplicationLook(UINT id);
	afx_msg void OnUpdateApplicationLook(CCmdUI* pCmdUI);
	DECLARE_MESSAGE_MAP()

	BOOL CreateDockingWindows();
	void SetDockingWindowIcons(BOOL bHiColorIcons);

//����Ϊzhouzhou��ӵ����Ա�ͺ���
public:
	CFixedSplitterWnd m_WndSplitter;//���ڷָ���
	SHOW_VIEW_TYPE showViewType;
protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
public:
	afx_msg void OnNcPaint();
	afx_msg void OnShowLeftView();
	afx_msg void OnShowRightView();
	afx_msg void OnShowBothView();
};
