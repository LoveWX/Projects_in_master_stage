#if !defined(AFX_RIGHTTEXTVIEW_H__A2DA2F30_6519_45A5_B2BE_6E40DE3CC852__INCLUDED_)
#define AFX_RIGHTTEXTVIEW_H__A2DA2F30_6519_45A5_B2BE_6E40DE3CC852__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RightTextView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// RightTextView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class RightTextView : public CFormView
{
protected:
	RightTextView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(RightTextView)

// Form Data
public:
	//{{AFX_DATA(RightTextView)
	enum { IDD = IDD_DIALOG4 };
	double	m_dAmplify;
	double	m_dPinDiameter;
	CString	m_sLensName;
	double	m_dFocusLength;
	double	m_dFNumber;
	double	m_dWaveLength;
	double	m_dLength;
	//}}AFX_DATA

private:
	CBrush m_brush;
	
// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(RightTextView)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~RightTextView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(RightTextView)
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RIGHTTEXTVIEW_H__A2DA2F30_6519_45A5_B2BE_6E40DE3CC852__INCLUDED_)
