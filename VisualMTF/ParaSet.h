#if !defined(AFX_PARASET_H__5F595725_0817_47C2_8E04_9403EC00C54F__INCLUDED_)
#define AFX_PARASET_H__5F595725_0817_47C2_8E04_9403EC00C54F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ParaSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CParaSet dialog

class CParaSet : public CDialog
{
// Construction
public:
	CParaSet(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CParaSet)
	enum { IDD = IDD_DIALOG1 };
	double	m_dPinDiameter;
	double	m_dAmplify;
	double	m_dFocusLength;
	double	m_dFNumber;
	double	m_dWaveLength;
	double	m_dLength;
	CString	m_sLensName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CParaSet)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CParaSet)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PARASET_H__5F595725_0817_47C2_8E04_9403EC00C54F__INCLUDED_)
