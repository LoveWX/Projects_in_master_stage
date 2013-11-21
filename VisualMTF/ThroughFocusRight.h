#if !defined(AFX_THROUGHFOCUSRIGHT_H__7D4C7BBA_D8A6_4BF4_9E3E_9378329E3912__INCLUDED_)
#define AFX_THROUGHFOCUSRIGHT_H__7D4C7BBA_D8A6_4BF4_9E3E_9378329E3912__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ThroughFocusRight.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CThroughFocusRight view

class CThroughFocusRight : public CView
{
protected:
	CThroughFocusRight();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CThroughFocusRight)

// Attributes
public:

// Operations
public:
	BOOL bPenInit;
	void PenCreate();
	int GetYpos(double);
	void DrawMTFPoint();
	void DrawPoint();
	void DrawGrid();
	void DrawBackground();
	void splint(double* ,double* ,double* ,double ,double &,int);
	void spline(double* ,double* ,double ,double ,double* ,int);
	double getRightSlope();
	double getLeftSlope();
	void SpaceInit();
	void CalculateFreq();
	void ExtendMTF();
	int nBoxWidth;//存放以下数组长度的整型变量
	int nAcqTimes;//存放采集次数的整型变量
	
		
	double *Freq;//存放MTF值对应频率坐标
	double *EveryPos;//存放各采集点坐标的
	double *MTFH;//存放横向的MTF值
	double *MTFV;//存放纵向的MTF值

	int nExtendedLength;//存放插值后MTF数组的长度（插值前长度为nBoxWidth）
	double dMaxDisFreq;//存放采样显示中MTF
	double dActMaxFreq;//显示的实际最大频率
	double dOriginalFreq;//插值前的频率间隔
	double dExtendedFreq;//插值前的频率间隔
	double *dExtendedMTFH;//插值后一个方向MTF数组的首地址
	double *dExtendedMTFV;//插值后一个方向MTF数组的首地址
	double *dOriFreq;//插值前频率坐标数组首地址（长度为nBoxWidth）
	double *dExtFreq;//插值后频率坐标数组首地址（长度为nExtendedLength）
	double *dTempSlopeH;//插值所需一个方向的斜率数组首地址
	double *dTempSlopeV;//插值所需一个方向的斜率数组首地址
	
	CScrollBar m_ScrollBar1;
	char cItemText[80];
	int nDisplayMode;
	CPen mypen[20];
	void UpdateTrace(BOOL,double*,double*,double*,int,double*,int);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CThroughFocusRight)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CThroughFocusRight();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CThroughFocusRight)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_THROUGHFOCUSRIGHT_H__7D4C7BBA_D8A6_4BF4_9E3E_9378329E3912__INCLUDED_)
