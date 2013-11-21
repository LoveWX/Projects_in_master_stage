#if !defined(AFX_FREQSET_H__B495E52F_8C8C_4746_B924_D4F477E9DF2F__INCLUDED_)
#define AFX_FREQSET_H__B495E52F_8C8C_4746_B924_D4F477E9DF2F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FreqSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFreqSet dialog

class CFreqSet : public CDialog
{
// Construction
public:
	CFreqSet(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CFreqSet)
	enum { IDD = IDD_DIALOG2 };
	double	m_dFreq1;
	double	m_dFreq2;
	double	m_dFreq3;
	double	m_dFreq4;
	double	m_dFreq6;
	double	m_dFreq5;
	double	m_dMTFt1;
	double	m_dMTFt2;
	double	m_dMTFt3;
	double	m_dMTFt4;
	double	m_dMTFt5;
	double	m_dMTFt6;
	double	m_dMTFs1;
	double	m_dMTFs2;
	double	m_dMTFs3;
	double	m_dMTFs4;
	double	m_dMTFs5;
	double	m_dMTFs6;
	//}}AFX_DATA

public:
	void setAimPoint(void *pfrm=NULL);
	void get6data(void *pfrm=NULL);
protected:
	void* pBackgroundWnd;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFreqSet)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFreqSet)
	afx_msg void OnBUTTONUpdate();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FREQSET_H__B495E52F_8C8C_4746_B924_D4F477E9DF2F__INCLUDED_)
