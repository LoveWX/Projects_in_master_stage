#if !defined(AFX_THROUGHFOCUSLEFT_H__9024D334_331E_4198_964A_B5E88160DA57__INCLUDED_)
#define AFX_THROUGHFOCUSLEFT_H__9024D334_331E_4198_964A_B5E88160DA57__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ThroughFocusLeft.h : header file
//
#include "dmccom.h"
/////////////////////////////////////////////////////////////////////////////
// CThroughFocusLeft form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CThroughFocusLeft : public CFormView
{
protected:
	CThroughFocusLeft();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CThroughFocusLeft)

// Form Data
public:
	//{{AFX_DATA(CThroughFocusLeft)
	enum { IDD = IDD_DIALOG10 };
	double	m_dFromPos;
	double	m_dToPos;
	BOOL	m_bChecked;
	int		m_nStepNum;
	//}}AFX_DATA

// Attributes
public:

// Operations
public:
	void InMemorySetZero();
	void OutMemorySetZero();
	void MemoryCheck();
	long MoveDistance(int ,double);
	int GetMoveStep(double);
	char cItemText[80];
	
	BOOL bCameraInit;//相机初始状态参量
	HANDLE hBoard;//相机采集卡句柄
	LPBYTE	lpLinear; //指向BUFFER首地址的指针
	long  lNum;//用于存放当前BUFFER容许保存的图像帧数
	DWORD	dwSize;//用于存放当前BUFFER的bit数

	BOOL bStageInit;//电机初始状态参量
	HANDLEDMC hDmc;//位移台控制器句柄
	long rc;//控制器反馈结果
	char szBuffer[256];
	
	double dPixel;//相机像元尺寸
	double dAmplify;//显微系统放大率
	int nBoxHeight;//用于存放数据捕获区的高度
	int nBoxWidth;//用于存放数据捕获区的宽度

	double *pData;//用于存放图像采样后数组平均值（大小为WIDTH*HEIGHT）
	double *pDataH;//存放横向数据矩阵（大小为nBoxWidth*nBoxHeight）
	double *pDataV;//存放纵向数据矩阵（大小为nBoxWidth*nBoxHeight）
	double *LSFH;//存放横向LSF（长度为nBoxWidth*nAcqTimes）
	double *LSFV;//存放纵向LSF（长度为nBoxWidth*nAcqTimes）
	double *FtDataRe;//存放MTF结果的实部（长度为nBoxWidth）
	double *FtDataIm;//存放MTF结果的虚部（长度为nBoxWidth）
	double *MTFH;//存放横向的MTF值（长度为nBoxWidth*nAcqTimes）
	double *MTFV;//存放纵向的MTF值（长度为nBoxWidth*nAcqTimes）
	double *PosH;//存放横向LSF对应横坐标（长度为nBoxWidth）
	double *PosV;//存放横向LSF对应纵坐标（长度为nBoxWidth）
	double *Freq;//存放MTF值对应频率坐标（长度为nBoxWidth）

	int nAcqTimes;//推扫次数
	double *EveryPos;//每次推扫的Z轴位置

	int nDisplayMode;

	void AreaSelect(double *, double *, double *, int , int , int, int , int );
	void fft(double*, double* ,double* ,int);
	void CenterFind(double* , int& , int& , int ,int);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CThroughFocusLeft)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CThroughFocusLeft();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CThroughFocusLeft)
	afx_msg void OnAcquire();
	afx_msg void OnFOISet();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_THROUGHFOCUSLEFT_H__9024D334_331E_4198_964A_B5E88160DA57__INCLUDED_)
