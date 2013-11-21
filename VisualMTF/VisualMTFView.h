// VisualMTFView.h : interface of the CVisualMTFView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_VISUALMTFVIEW_H__3229B48C_EA4A_4182_8110_7162CBF457C0__INCLUDED_)
#define AFX_VISUALMTFVIEW_H__3229B48C_EA4A_4182_8110_7162CBF457C0__INCLUDED_

#define ARRAYLENGTH 6

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CVisualMTFView : public CView
{
protected: // create from serialization only
	CVisualMTFView();
	DECLARE_DYNCREATE(CVisualMTFView)

// Attributes
public:
	CVisualMTFDoc* GetDocument();
	void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	void PrintMTFView(CDC *pDC,void *mainfrm);
	void PrintLSFView(CDC *pDC,void *mainfrm);
	void PrintTextView(CDC *pDC,void *mainfrm);
	void PrintListView(CDC *pDC,void *mainfrm,int nPage);
	void DrawBackground(CDC *mypDC);
	void DrawMTFFrame(CDC *mypDC,void *mainfrm);
	void DrawLSFFrame(CDC *mypDC,void *mainfrm);
	void DrawGrid(CDC *mypDC);
	void DrawMTFTTrace(CDC *mypDC,void *mainfrm);
	void DrawMTFSTrace(CDC *mypDC,void *mainfrm);
	void DrawLSFTTrace(CDC *mypDC,void *mainfrm);
	void DrawLSFSTrace(CDC *mypDC,void *mainfrm);
	void PrintPageHeader(CDC *pDC,void *mainfrm);
	void GetX(void *mainfrm);
	void GetYMax(void *mainfrm);
	void PreparePrintText(int num,int textwidth,char *printtext);

	int framepos_x1;
	int framepos_y1;
	int framepos_x2;
	int framepos_y2;
	int picpos_x1;
	int picpos_y1;
	int picpos_x2;
	int picpos_y2;
	int BColorR;
	int BColorG;
	int BColorB;
	int dLinePerPage;
	double xmax;
	double xmin;
	double ymax;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVisualMTFView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CVisualMTFView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
// Generated message map functions
	//{{AFX_MSG(CVisualMTFView)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in VisualMTFView.cpp
inline CVisualMTFDoc* CVisualMTFView::GetDocument()
   { return (CVisualMTFDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VISUALMTFVIEW_H__3229B48C_EA4A_4182_8110_7162CBF457C0__INCLUDED_)
