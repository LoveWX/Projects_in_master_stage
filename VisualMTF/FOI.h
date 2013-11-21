#if !defined(AFX_FOI_H__9D8BAC93_6F20_4FAF_B38A_9459E6F61C00__INCLUDED_)
#define AFX_FOI_H__9D8BAC93_6F20_4FAF_B38A_9459E6F61C00__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FOI.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFOI dialog

class CFOI : public CDialog
{
// Construction
public:
	double getRightSlope();
	double getLeftSlope();
	void spline(double* ,double* ,double ,double ,double* ,int);
	void splint(double* ,double* ,double* ,double ,double &,int);
	void CalcMTF(double* ,double* ,double* );
	void Init(int,double*,double*,double*);
	int nBoxWidth;
	double *OriFreq;
	double *OriMTFH;
	double *OriMTFV;

	double *tempslopet;
	double *tempslopes;

	double AimFreq[6];
	double AimMTFH[6];
	double AimMTFV[6];
	CFOI(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CFOI)
	enum { IDD = IDD_DIALOG11 };
	double	m_dFreq1;
	double	m_dFreq2;
	double	m_dFreq3;
	double	m_dFreq4;
	double	m_dFreq5;
	double	m_dFreq6;
	double	m_dMTFH1;
	double	m_dMTFH2;
	double	m_dMTFH3;
	double	m_dMTFH4;
	double	m_dMTFH5;
	double	m_dMTFH6;
	double	m_dMTFV1;
	double	m_dMTFV2;
	double	m_dMTFV3;
	double	m_dMTFV4;
	double	m_dMTFV5;
	double	m_dMTFV6;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFOI)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFOI)
	virtual void OnCancel();
	afx_msg void OnRefresh();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FOI_H__9D8BAC93_6F20_4FAF_B38A_9459E6F61C00__INCLUDED_)
