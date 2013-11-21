// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__4AF51FFF_6F6C_4D2A_91B3_242B191E71DF__INCLUDED_)
#define AFX_MAINFRM_H__4AF51FFF_6F6C_4D2A_91B3_242B191E71DF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#define PI 3.14159265359
#include <math.h>

#include "dmccom.h"
#include "okapi32.h"

class CMainFrame : public CFrameWnd
{
	
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL
	
// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

public:
	HANDLEDMC getStageHandle();
	BOOL getbStageInit();
	double getdPixel();
	LPBYTE getCameraBuffer();
	HANDLE getCameraHandle();
	BOOL getbCamInit();
	int getnStarWidth();
	int getnStarHeight();
	int* getpStarWidth();
	int* getpStarHeight();
	LPBYTE getLPBYTEOK();
	HANDLE getHANDLEOK();
	HANDLEDMC getHANDLEDMC();
	double ResSteptoDis(char *);
	void mydelete();
	void getDataFromWnd(void *pfrm=NULL);

	double getdPinDiameter();
	double getdAmplify();
	double getdFocusLength();
	double getdFNumber();
	double getdWaveLength();
	double getdLength();
	CString getsLensName();	
	int getarraylength();
	double* getdFreq();
	double* getdLSFt();
	double* getdLSFs();
	double* getdMTFt();
	double* getdMTFs();
	double* getdPOSt();
	double* getdPOSs();
	double GetTypedmax();
	CTime* getSavedTime();

	void setdPinDiameter(double dt);
	void setdAmplify(double dt);
	void setdFocusLength(double dt);
	void setdFNumber(double dt);
	void setdWaveLength(double dt);
	void setdLength(double dt);
	void setsLensName(CString ds);	
	void setarraylength(int di);
	void setdFreq(double* pdt);
	void setdLSFt(double* pdt);
	void setdLSFs(double* pdt);
	void setdMTFt(double* pdt);
	void setdMTFs(double* pdt);
	void setdPOSt(double* pdt);
	void setdPOSs(double* pdt);
	void setSavedTime(CTime *LastSavedTime=NULL);
	
	void setTypedPage(int nPage);
	int getTypedPage();
	void myfft(double *TD,double *FDre,double *FDim,int r);
	void SolveMTF();
	int getExtendedlength();
	double* getExtendedMTFt();
	double* getExtendedMTFs();
	void setExtendedMTFt(double* pdt);
	void setExtendedMTFs(double* pdt);
	double getMTFxmax();
	double getdF();
	double Calc_f();

	BOOL bStageInit;//����Ƿ���Ի�
	BOOL bCameraInit;//����Ƿ���Ի�
	
	HANDLEDMC hDmc;
	long rc;
	int iMotionInProgress;
	char szBuffer[256];
   	char cItemText[80];
	double dXAbsPos;
	double dYAbsPos;
	double dZAbsPos;
	double dTAbsPos;

	HANDLE hBoard; 
	RECT rcBuffer, rcVideo; 
	LPBYTE	lpLinear; //ָ��BUFFER�׵�ַ��ָ��
	DWORD	dwSize; //���ڴ�ŵ�ǰBUFFER��bit��
	long lNum;//���ڴ�ŵ�ǰBUFFER�����ŵ�ͼ��֡��

	int nStarHeight;//ʮ�ֲ�߶�
	int nStarWidth;//ʮ�ֲ���
	int *pStarHeight;
	int *pStarWidth;


protected:
	double dPinDiameter;//С��ֱ��
	double dAmplify;//��΢ϵͳ�Ŵ���
	double dFocusLength;//���⾵ͷ����
	double dFNumber;//���⾵ͷF��
	double dWaveLength;//����
	double dLength;//ƽ�й�ܽ���
	double dPixel;//̽������Ԫ�ߴ�
	CString sLensName;//��ͷ����
	
	int arraylength;
	double* dFreq;
	double* dLSFt;
	double* dLSFs;
	double* dMTFt;
	double* dMTFs;
	double* dPOSt;
	double* dPOSs;
	double* ExtendedMTFt;
	double* ExtendedMTFs;
	int extendedMTFlength;
	double dF;
	double dMTFxmax;

	CTime *SavedTime;

	int typedpage;
	
// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnParaSetDialog();
	afx_msg void OnFreqSetDialog();
	afx_msg void OnFileOpenMenu();
	afx_msg void OnFileSaveMenu();
	afx_msg void OnStageSetDialog();
	afx_msg void OnStarImage();
	afx_msg void OnRealTime();
	afx_msg void OnThroughFocus();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__4AF51FFF_6F6C_4D2A_91B3_242B191E71DF__INCLUDED_)
