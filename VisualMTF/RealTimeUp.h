#if !defined(AFX_REALTIMEUP_H__D24D6857_247D_4050_A128_EF45C50CC28D__INCLUDED_)
#define AFX_REALTIMEUP_H__D24D6857_247D_4050_A128_EF45C50CC28D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RealTimeUp.h : header file
//
#include "dmccom.h"
#include "MainFrm.h"
/////////////////////////////////////////////////////////////////////////////
// CRealTimeUp form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CRealTimeUp : public CFormView
{
protected:
	CRealTimeUp();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CRealTimeUp)

// Form Data
public:
	//{{AFX_DATA(CRealTimeUp)
	enum { IDD = IDD_DIALOG9 };
	double	m_dStepDis;
	BOOL	m_bChecked;
	//}}AFX_DATA

// Attributes
public:

// Operations
public:
	double* getdPOSs();
	double* getdPOSt();
	double* getdLSFs();
	double* getdLSFt();
	double* getdMTFs();
	double* getdMTFt();
	double* getdFreq();
	int getarraylength();
	void SetMemoryZero();
	void MemoryCheck();
	
	
	int GetMoveStep(double);
	long MoveDistance(int,double);
	void fft(double *, double *, double *, int );
	void AreaSelect(double *, double *, double *, int , int , int, int , int );
	void CenterFind(double *, int &, int &, int, int);
	char cItemText[80];
	BOOL bCameraInit;
	HANDLE hBoard;//相机采集卡句柄
	LPBYTE	lpLinear; //指向BUFFER首地址的指针
	long  lNum;//用于存放当前BUFFER容许保存的图像帧数
	DWORD	dwSize;//用于存放当前BUFFER的bit数
	double dPixel;//相机像元尺寸
	double dAmplify;//显微系统放大率

	double *pData;//用于存放图像采样后数组平均值（大小为WIDTH*HEIGHT）
	double *pDataH;//存放横向数据矩阵（大小为nBoxWidth*nBoxHeight）
	double *pDataV;//存放纵向数据矩阵（大小为nBoxWidth*nBoxHeight）
	double *LSFH;//存放横向LSF（长度为nBoxWidth）
	double *LSFV;//存放纵向LSF（长度为nBoxWidth）
	double *FtDataRe;//存放MTF结果的实部（长度为nBoxWidth）
	double *FtDataIm;//存放MTF结果的虚部（长度为nBoxWidth）
	double *MTFH;//存放横向的MTF值（长度为nBoxWidth）
	double *MTFV;//存放纵向的MTF值（长度为nBoxWidth）
	double *PosH;//存放横向LSF对应横坐标（长度为nBoxWidth）
	double *PosV;//存放横向LSF对应纵坐标（长度为nBoxWidth）
	double *Freq;//存放MTF值对应频率坐标（长度为nBoxWidth）

	

	HANDLEDMC hDmc;
	long rc;
	char szBuffer[256];
	
	int nBoxHeight;//用于存放数据捕获区的高度
	int nBoxWidth;//用于存放数据捕获区的宽度

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRealTimeUp)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CRealTimeUp();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CRealTimeUp)
	afx_msg void OnAcquire();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnFOISet();
	afx_msg void OnDisplay();
	afx_msg void OnSave();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REALTIMEUP_H__D24D6857_247D_4050_A128_EF45C50CC28D__INCLUDED_)
