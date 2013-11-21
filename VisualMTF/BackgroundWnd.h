#if !defined(AFX_BACKGROUNDWND_H__4C9D7773_289F_477B_871F_6DAF6D530C2D__INCLUDED_)
#define AFX_BACKGROUNDWND_H__4C9D7773_289F_477B_871F_6DAF6D530C2D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BackgroundWnd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBackgroundWnd frame

class CBackgroundWnd : public CFrameWnd
{
	DECLARE_DYNCREATE(CBackgroundWnd)
public:
	CBackgroundWnd();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBackgroundWnd)
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CBackgroundWnd();

public:
	void getDataFromRealTimeFrm(void *tempfrm=NULL);
	CSplitterWnd m_wndSplitter;
	CMenu m_myMenu;

	double dPinDiameter;
	double dAmplify;
	double dFocusLength;
	double dFNumber;
	double dWaveLength;
	double dLength;
	CString sLensName;
	
	int arraylength;
	double* dFreq;
	double* dLSFt;
	double* dLSFs;
	double* dMTFt;
	double* dMTFs;
	double* dPOSt;
	double* dPOSs;

	double dCurrentF;
	double dOriginalF;
	double* ExtendedMTFt;
	double* ExtendedMTFs;
	int extendedMTFlength;
	double* tempslopet;
	double* tempslopes;

	CTime *SavedTime;
	
	BOOL PreCreateWindow(CREATESTRUCT& cs);
	BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext *pContext);
	void ChangeView(int CurrentGet);
	void* GetLeftView();
	void* GetRightView();
	void mydelete();
	void getDataFromMainFrm(void *mainfrm=NULL);
	void sendDataToMainFrm(void *mainfrm=NULL);
	
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
	double* getExtendedMTFt();
	double* getExtendedMTFs();
	int getExtendedlength();
	CTime* getSavedTime();

	void extendMTF();
	void Calc_f();
	void Calc_Frequence();
	double getCurrentF();
	double getOriginalF();
	void spline(double* x,double* y,double yp1,double ypn,double* y2,int lena);
	void splint(double* xa,double* ya,double* y2a,double x,double &y,int lena);
	double getLeftSlope();
	double getRightSlope();
	double getMTFmax();
	
	void CalcMTF(double* x,double* y1,double* y2);
	void send6data(double* a,double* b,double* c);

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
	void setExtendedMTFt(double* pdt);
	void setExtendedMTFs(double* pdt);
	void setExtendedlength(int di);
	void setSavedTime(CTime *LastSavedTime=NULL);
	
protected:
	

	// Generated message map functions
	//{{AFX_MSG(CBackgroundWnd)
	afx_msg void OnMenuitemSave();
	afx_msg void OnMenuitemPrint();
	afx_msg void OnMenuitemPrintpreview();
	afx_msg void OnMenuConfParaset();
	afx_msg void OnMenuFreqParaset();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BACKGROUNDWND_H__4C9D7773_289F_477B_871F_6DAF6D530C2D__INCLUDED_)
