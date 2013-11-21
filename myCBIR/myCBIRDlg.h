// myCBIRDlg.h : header file
//

#if !defined(AFX_MYCBIRDLG_H__64623080_C219_4F7D_B781_EA01E45937C9__INCLUDED_)
#define AFX_MYCBIRDLG_H__64623080_C219_4F7D_B781_EA01E45937C9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMyCBIRDlg dialog

#include <algorithm>
using namespace std;
#include "cv.h"
#include "highgui.h"

const int h_bins=30;
const int s_bins=32;
const int v_bins=32;

const float max_h=180;
const float max_s=255;
const float max_v=255;

const int numOfTestPictures=500;
const int numOfPoolPictures=9000;

struct DistanceOfPicture 
{
	int index;
	double similarity;
};

class CMyCBIRDlg : public CDialog
{
// Construction
public:
	CMyCBIRDlg(CWnd* pParent = NULL);	// standard constructor
	~CMyCBIRDlg();

// Dialog Data
	//{{AFX_DATA(CMyCBIRDlg)
	enum { IDD = IDD_MYCBIR_DIALOG };
	CStatic	m_sizeOfPool;
	CStatic	m_calcedPic;
	CStatic	m_res03;
	CStatic	m_res20;
	CStatic	m_res19;
	CStatic	m_res18;
	CStatic	m_res17;
	CStatic	m_res16;
	CStatic	m_res15;
	CStatic	m_res14;
	CStatic	m_res13;
	CStatic	m_res12;
	CStatic	m_res11;
	CStatic	m_res10;
	CStatic	m_res09;
	CStatic	m_res08;
	CStatic	m_res07;
	CStatic	m_res06;
	CStatic	m_res05;
	CStatic	m_res04;
	CStatic	m_res02;
	CStatic	m_res01;
	CEdit	m_srcImagePath;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyCBIRDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMyCBIRDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButton1();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	void ShowImage(IplImage* img,UINT ID);
	void ShowImageInBox(IplImage* img,UINT ID);
	void myCalcHist(CvHistogram * &theHist,IplImage *srcImage);
	void CalcHistOfPoolPictures();

	char defaultPath[300];//起始时默认的路径
	bool isCalcPoolPictures;
	IplImage *srcImage;//要检索的图片
	CvHistogram *histOfSrcPicture;
	CvHistogram *histOfPoolPictures[numOfPoolPictures];
	DistanceOfPicture resultOfEachPicture[numOfPoolPictures];

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYCBIRDLG_H__64623080_C219_4F7D_B781_EA01E45937C9__INCLUDED_)
