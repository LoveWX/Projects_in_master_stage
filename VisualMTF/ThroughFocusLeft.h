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
	
	BOOL bCameraInit;//�����ʼ״̬����
	HANDLE hBoard;//����ɼ������
	LPBYTE	lpLinear; //ָ��BUFFER�׵�ַ��ָ��
	long  lNum;//���ڴ�ŵ�ǰBUFFER�������ͼ��֡��
	DWORD	dwSize;//���ڴ�ŵ�ǰBUFFER��bit��

	BOOL bStageInit;//�����ʼ״̬����
	HANDLEDMC hDmc;//λ��̨���������
	long rc;//�������������
	char szBuffer[256];
	
	double dPixel;//�����Ԫ�ߴ�
	double dAmplify;//��΢ϵͳ�Ŵ���
	int nBoxHeight;//���ڴ�����ݲ������ĸ߶�
	int nBoxWidth;//���ڴ�����ݲ������Ŀ��

	double *pData;//���ڴ��ͼ�����������ƽ��ֵ����СΪWIDTH*HEIGHT��
	double *pDataH;//��ź������ݾ��󣨴�СΪnBoxWidth*nBoxHeight��
	double *pDataV;//����������ݾ��󣨴�СΪnBoxWidth*nBoxHeight��
	double *LSFH;//��ź���LSF������ΪnBoxWidth*nAcqTimes��
	double *LSFV;//�������LSF������ΪnBoxWidth*nAcqTimes��
	double *FtDataRe;//���MTF�����ʵ��������ΪnBoxWidth��
	double *FtDataIm;//���MTF������鲿������ΪnBoxWidth��
	double *MTFH;//��ź����MTFֵ������ΪnBoxWidth*nAcqTimes��
	double *MTFV;//��������MTFֵ������ΪnBoxWidth*nAcqTimes��
	double *PosH;//��ź���LSF��Ӧ�����꣨����ΪnBoxWidth��
	double *PosV;//��ź���LSF��Ӧ�����꣨����ΪnBoxWidth��
	double *Freq;//���MTFֵ��ӦƵ�����꣨����ΪnBoxWidth��

	int nAcqTimes;//��ɨ����
	double *EveryPos;//ÿ����ɨ��Z��λ��

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
