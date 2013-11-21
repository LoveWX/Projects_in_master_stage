#if !defined(AFX_LEFTFORMVIEW_H__BC086372_55B6_4A51_A68C_C8089E63AB53__INCLUDED_)
#define AFX_LEFTFORMVIEW_H__BC086372_55B6_4A51_A68C_C8089E63AB53__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LeftFormView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// LeftFormView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class LeftFormView : public CFormView
{
protected:
	LeftFormView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(LeftFormView)

// Form Data
public:
	//{{AFX_DATA(LeftFormView)
	enum { IDD = IDD_DIALOG3 };
	CButton	m_ChangeMax;
	CComboBox	m_selmode;
	BOOL	m_vcheck;
	BOOL	m_hcheck;
	int		m_iComboDefaultSel;
	BOOL	m_Interpolationcheck;
	double	m_TypedMax;
	//}}AFX_DATA

// Attributes
public:
	int ComboLastMode;
	BOOL GetHSelected();
	BOOL GetVSelected();
	BOOL GetInterpolationSelected();



// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(LeftFormView)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~LeftFormView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(LeftFormView)
	afx_msg void OnSelchangeCombo();
	afx_msg void OnCheckHChanged();
	afx_msg void OnCheckVChanged();
	afx_msg void OnCheckInterpolation();
	afx_msg void OnButtonChangeMax();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LEFTFORMVIEW_H__BC086372_55B6_4A51_A68C_C8089E63AB53__INCLUDED_)
