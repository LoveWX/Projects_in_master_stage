#if !defined(AFX_THROUGHFOCUSFRAME_H__935E7D15_BCFE_4635_8954_E08C27767036__INCLUDED_)
#define AFX_THROUGHFOCUSFRAME_H__935E7D15_BCFE_4635_8954_E08C27767036__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ThroughFocusFrame.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CThroughFocusFrame frame

class CThroughFocusFrame : public CFrameWnd
{
	DECLARE_DYNCREATE(CThroughFocusFrame)
protected:
	

// Attributes
public:

// Operations
public:
	void* GetRightView();
	void* GetLeftView();
	CSplitterWnd m_wndSplitter;
	CThroughFocusFrame();           // protected constructor used by dynamic creation
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CThroughFocusFrame)
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CThroughFocusFrame();

	// Generated message map functions
	//{{AFX_MSG(CThroughFocusFrame)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_THROUGHFOCUSFRAME_H__935E7D15_BCFE_4635_8954_E08C27767036__INCLUDED_)
