#if !defined(AFX_REALTIMEDOWN_H__06F28ECE_B1B6_4257_B0F3_BDED440011B4__INCLUDED_)
#define AFX_REALTIMEDOWN_H__06F28ECE_B1B6_4257_B0F3_BDED440011B4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RealTimeDown.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRealTimeDown view

class CRealTimeDown : public CView
{
protected:
	CRealTimeDown();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CRealTimeDown)

// Attributes
public:

// Operations
public:
	CScrollBar m_ScrollBar1;
	int GetYpos(double);
	double CalLastDisMTFV(double);
	double CalLastDisMTFH(double);
	void DrawMTFPoint();
	void DrawPoint();
	void splint(double* ,double* ,double* ,double ,double &,int);//注意倒数第二个变量需为引用
	void spline(double* ,double* ,double ,double ,double* ,int);
	double getRightSlope();
	double getLeftSlope();
	void SpaceInit();
	void CalculateFreq();
	void ExtendMTF();
	void DrawLSFPoint();
	void DrawGrid();
	void DrawBackground();
	double MaxFind(double*,double*,int);
	void UpdateTrace(BOOL,double*,double*,double*,double*,double*,double*,double*,int);

	int nBoxWidth;//存放以下数组长度的整型变量
	double dMaxLSF;//存放LSF的最大值
	int LSFMAX;//存放LSF的纵坐标极大值
	double *PosH;//存放横向LSF对应横坐标
	double *PosV;//存放横向LSF对应纵坐标
	double *Freq;//存放MTF值对应频率坐标
	double *LSFH;//存放横向LSF
	double *LSFV;//存放纵向LSF
	double *MTFH;//存放横向的MTF值
	double *MTFV;//存放纵向的MTF值

	int nExtendedLength;//存放插值后MTF数组的长度（插值前长度为nBoxWidth）
	double dMaxDisFreq;//存放采样显示中MTF
	double dOriginalFreq;//插值前的频率间隔
	double dExtendedFreq;//插值前的频率间隔
	double *dExtendedMTFH;//插值后一个方向MTF数组的首地址
	double *dExtendedMTFV;//插值后一个方向MTF数组的首地址
	double *dOriFreq;//插值前频率坐标数组首地址（长度为nBoxWidth）
	double *dExtFreq;//插值后频率坐标数组首地址（长度为nExtendedLength）
	double *dTempSlopeH;//插值所需一个方向的斜率数组首地址
	double *dTempSlopeV;//插值所需一个方向的斜率数组首地址
	
	char cItemText[80];
	int nDisplayMode;

	

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRealTimeDown)
	public:
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CRealTimeDown();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CRealTimeDown)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REALTIMEDOWN_H__06F28ECE_B1B6_4257_B0F3_BDED440011B4__INCLUDED_)
