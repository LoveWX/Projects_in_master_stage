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
	HANDLE hBoard;//����ɼ������
	LPBYTE	lpLinear; //ָ��BUFFER�׵�ַ��ָ��
	long  lNum;//���ڴ�ŵ�ǰBUFFER�������ͼ��֡��
	DWORD	dwSize;//���ڴ�ŵ�ǰBUFFER��bit��
	double dPixel;//�����Ԫ�ߴ�
	double dAmplify;//��΢ϵͳ�Ŵ���

	double *pData;//���ڴ��ͼ�����������ƽ��ֵ����СΪWIDTH*HEIGHT��
	double *pDataH;//��ź������ݾ��󣨴�СΪnBoxWidth*nBoxHeight��
	double *pDataV;//����������ݾ��󣨴�СΪnBoxWidth*nBoxHeight��
	double *LSFH;//��ź���LSF������ΪnBoxWidth��
	double *LSFV;//�������LSF������ΪnBoxWidth��
	double *FtDataRe;//���MTF�����ʵ��������ΪnBoxWidth��
	double *FtDataIm;//���MTF������鲿������ΪnBoxWidth��
	double *MTFH;//��ź����MTFֵ������ΪnBoxWidth��
	double *MTFV;//��������MTFֵ������ΪnBoxWidth��
	double *PosH;//��ź���LSF��Ӧ�����꣨����ΪnBoxWidth��
	double *PosV;//��ź���LSF��Ӧ�����꣨����ΪnBoxWidth��
	double *Freq;//���MTFֵ��ӦƵ�����꣨����ΪnBoxWidth��

	

	HANDLEDMC hDmc;
	long rc;
	char szBuffer[256];
	
	int nBoxHeight;//���ڴ�����ݲ������ĸ߶�
	int nBoxWidth;//���ڴ�����ݲ������Ŀ��

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
