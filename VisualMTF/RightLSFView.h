#if !defined(AFX_RIGHTLSFVIEW_H__26E221C2_054D_476C_9DA9_606201F5C6D6__INCLUDED_)
#define AFX_RIGHTLSFVIEW_H__26E221C2_054D_476C_9DA9_606201F5C6D6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RightLSFView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// RightLSFView view

class RightLSFView : public CView
{
protected:
	RightLSFView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(RightLSFView)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(RightLSFView)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

	void DrawFrame();
	void DrawBackground();
	void DrawGrid();
	void DrawTTrace();
	void DrawSTrace();
	void ErasureTrace();
	void GetX();
	void GetYMax();
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
	double xmax;
	double xmin;
	double ymax;
public:
	void UpdateTrace(BOOL Redraw,BOOL TTrace,BOOL STrace);

// Implementation
protected:
	virtual ~RightLSFView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(RightLSFView)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RIGHTLSFVIEW_H__26E221C2_054D_476C_9DA9_606201F5C6D6__INCLUDED_)
