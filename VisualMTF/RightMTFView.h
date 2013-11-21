#if !defined(AFX_RIGHTMTFVIEW_H__0CA74F41_1C61_4DCF_BEAA_07705BC6D28D__INCLUDED_)
#define AFX_RIGHTMTFVIEW_H__0CA74F41_1C61_4DCF_BEAA_07705BC6D28D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RightMTFView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// RightMTFView view

class RightMTFView : public CView
{
protected:
	RightMTFView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(RightMTFView)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(RightMTFView)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

	void DrawFrame();
	void DrawBackground();
	void DrawGrid();
	void DrawTTrace();
	void DrawSTrace();
	void ErasureTrace();
	void GetXmax();
	int GetPrintTimes();
	double Calc_f();
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
public:
	void UpdateTrace(BOOL Redraw,BOOL TTrace,BOOL STrace);
	void ChangeXMax(double mymax);
	double getMTFmax();

// Implementation
protected:
	virtual ~RightMTFView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(RightMTFView)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RIGHTMTFVIEW_H__0CA74F41_1C61_4DCF_BEAA_07705BC6D28D__INCLUDED_)
