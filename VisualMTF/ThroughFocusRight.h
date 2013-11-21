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
	int nBoxWidth;//����������鳤�ȵ����ͱ���
	int nAcqTimes;//��Ųɼ����������ͱ���
	
		
	double *Freq;//���MTFֵ��ӦƵ������
	double *EveryPos;//��Ÿ��ɼ��������
	double *MTFH;//��ź����MTFֵ
	double *MTFV;//��������MTFֵ

	int nExtendedLength;//��Ų�ֵ��MTF����ĳ��ȣ���ֵǰ����ΪnBoxWidth��
	double dMaxDisFreq;//��Ų�����ʾ��MTF
	double dActMaxFreq;//��ʾ��ʵ�����Ƶ��
	double dOriginalFreq;//��ֵǰ��Ƶ�ʼ��
	double dExtendedFreq;//��ֵǰ��Ƶ�ʼ��
	double *dExtendedMTFH;//��ֵ��һ������MTF������׵�ַ
	double *dExtendedMTFV;//��ֵ��һ������MTF������׵�ַ
	double *dOriFreq;//��ֵǰƵ�����������׵�ַ������ΪnBoxWidth��
	double *dExtFreq;//��ֵ��Ƶ�����������׵�ַ������ΪnExtendedLength��
	double *dTempSlopeH;//��ֵ����һ�������б�������׵�ַ
	double *dTempSlopeV;//��ֵ����һ�������б�������׵�ַ
	
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
