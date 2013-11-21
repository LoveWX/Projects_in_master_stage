#if !defined(AFX_SCANIMAGE_H__2663AE42_A913_4232_8A7B_26E24DC0DC26__INCLUDED_)
#define AFX_SCANIMAGE_H__2663AE42_A913_4232_8A7B_26E24DC0DC26__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ScanImage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CScanImage dialog

class CScanImage : public CDialog
{
// Construction
public:
	void DrawCross(int,int,int,int);
	void FindCenter(unsigned char *,int& ,int& ,int ,int );
	int power(int);
	
	CScanImage(CWnd* pParent = NULL);   // standard constructor
	HANDLE hBoard;
	LPBYTE	lpLinear; //指向BUFFER首地址的指针
	DWORD	dwSize; //用于存放当前BUFFER的bit数
	unsigned char *cData; //指向用户自开辟数据区的指针
	char cItemText[80];
	HGLOBAL eDIB;//用于保存文件的空间句柄
	CComboBox *pComboBox1;
	CComboBox *pComboBox2;
	BOOL bCameraActive;
	BOOL bWindowMoved;
	int		m_nBoxHeight;//对应CMainFrame::的nStar
	int		m_nBoxWidth;
	
	

// Dialog Data
	//{{AFX_DATA(CScanImage)
	enum { IDD = IDD_DIALOG8 };
	CStatic	m_image;
	int		m_nXPos;
	int		m_nYPos;
	CString	m_sCombo1;
	CString	m_sCombo2;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScanImage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CScanImage)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeCombo1();
	afx_msg void OnSelchangeCombo2();
	afx_msg void OnPaint();
	afx_msg void OnDestroy();
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	afx_msg void OnButton3();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMove(int x, int y);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCANIMAGE_H__2663AE42_A913_4232_8A7B_26E24DC0DC26__INCLUDED_)
