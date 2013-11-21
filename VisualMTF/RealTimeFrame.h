#if !defined(AFX_REALTIMEFRAME_H__4F0080E6_B210_451D_90CF_EBFC4701D69E__INCLUDED_)
#define AFX_REALTIMEFRAME_H__4F0080E6_B210_451D_90CF_EBFC4701D69E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RealTimeFrame.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRealTimeFrame frame

class CRealTimeFrame : public CFrameWnd
{
	DECLARE_DYNCREATE(CRealTimeFrame)
protected:
	

// Attributes
public:

// Operations
public:
	void* GetDownView();
	void* GetUpView();
	CSplitterWnd m_wndSplitter;
	CRealTimeFrame();           // protected constructor used by dynamic creation
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRealTimeFrame)
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CRealTimeFrame();

	// Generated message map functions
	//{{AFX_MSG(CRealTimeFrame)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REALTIMEFRAME_H__4F0080E6_B210_451D_90CF_EBFC4701D69E__INCLUDED_)
