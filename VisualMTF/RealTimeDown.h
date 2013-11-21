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
	void splint(double* ,double* ,double* ,double ,double &,int);//ע�⵹���ڶ���������Ϊ����
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

	int nBoxWidth;//����������鳤�ȵ����ͱ���
	double dMaxLSF;//���LSF�����ֵ
	int LSFMAX;//���LSF�������꼫��ֵ
	double *PosH;//��ź���LSF��Ӧ������
	double *PosV;//��ź���LSF��Ӧ������
	double *Freq;//���MTFֵ��ӦƵ������
	double *LSFH;//��ź���LSF
	double *LSFV;//�������LSF
	double *MTFH;//��ź����MTFֵ
	double *MTFV;//��������MTFֵ

	int nExtendedLength;//��Ų�ֵ��MTF����ĳ��ȣ���ֵǰ����ΪnBoxWidth��
	double dMaxDisFreq;//��Ų�����ʾ��MTF
	double dOriginalFreq;//��ֵǰ��Ƶ�ʼ��
	double dExtendedFreq;//��ֵǰ��Ƶ�ʼ��
	double *dExtendedMTFH;//��ֵ��һ������MTF������׵�ַ
	double *dExtendedMTFV;//��ֵ��һ������MTF������׵�ַ
	double *dOriFreq;//��ֵǰƵ�����������׵�ַ������ΪnBoxWidth��
	double *dExtFreq;//��ֵ��Ƶ�����������׵�ַ������ΪnExtendedLength��
	double *dTempSlopeH;//��ֵ����һ�������б�������׵�ַ
	double *dTempSlopeV;//��ֵ����һ�������б�������׵�ַ
	
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
