#if !defined(AFX_RIGHTLISTVIEW_H__5A7D50DB_A2BA_47E3_81DE_134F34B1E053__INCLUDED_)
#define AFX_RIGHTLISTVIEW_H__5A7D50DB_A2BA_47E3_81DE_134F34B1E053__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RightListView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// RightListView view

#include <afxcview.h>

class RightListView : public CListView
{
protected:
	RightListView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(RightListView)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(RightListView)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

	BOOL PreCreateWindow(CREATESTRUCT& cs);
	void OnInitialUpdate();	

// Implementation
protected:
	virtual ~RightListView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(RightListView)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RIGHTLISTVIEW_H__5A7D50DB_A2BA_47E3_81DE_134F34B1E053__INCLUDED_)
