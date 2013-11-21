#if !defined(AFX_STAGESET_H__C89BBDB2_7EA5_4164_A06D_23675CD495B9__INCLUDED_)
#define AFX_STAGESET_H__C89BBDB2_7EA5_4164_A06D_23675CD495B9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StageSet.h : header file
//
#include "dmccom.h"
#include "MainFrm.h"
/////////////////////////////////////////////////////////////////////////////
// CStageSet dialog

class CStageSet : public CDialog
{
// Construction
public:
	long UnlockStage(int);
	long LockStage(int);
	int GetMoveStep(double);
	long MoveDistance(int , double);
	void ChangeRelPos(int,double);
	void ChangeAbsPos(int , double);
	int GetScrollPos(double);
	void OnHScroll(UINT,UINT,CScrollBar*);
	int nListBoxPos;
	CListBox *pLB;
	CScrollBar *pSB;
	CStageSet(CWnd* pParent = NULL);   // standard constructor
	double dXAbs;
	double dYAbs;
	double dZAbs;
	double dTAbs;

	HANDLEDMC hDmc;
	long rc;
	char szBuffer[256];
	int iMotionInProgress;
	char cItemText[80];
	BOOL bStageLocked[4];

	

// Dialog Data
	//{{AFX_DATA(CStageSet)
	enum { IDD = IDD_DIALOG7 };
	BOOL	m_bLocked;
	double	m_dXPos;
	double	m_dYPos;
	double	m_dZPos;
	double	m_dTPos;
	double	m_dRelDis;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStageSet)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CStageSet)
	virtual BOOL OnInitDialog();
	afx_msg void OnMove();
	afx_msg void OnSetZero();
	afx_msg void OnCheck1();
	afx_msg void OnCenter();
	afx_msg void OnSelchangeList1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STAGESET_H__C89BBDB2_7EA5_4164_A06D_23675CD495B9__INCLUDED_)
