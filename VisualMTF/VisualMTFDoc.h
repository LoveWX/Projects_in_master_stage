// VisualMTFDoc.h : interface of the CVisualMTFDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_VISUALMTFDOC_H__63910BFC_9B3F_4348_BAB1_A5679D4E7913__INCLUDED_)
#define AFX_VISUALMTFDOC_H__63910BFC_9B3F_4348_BAB1_A5679D4E7913__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CVisualMTFDoc : public CDocument
{
protected: // create from serialization only
	CVisualMTFDoc();
	DECLARE_DYNCREATE(CVisualMTFDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVisualMTFDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CVisualMTFDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CVisualMTFDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VISUALMTFDOC_H__63910BFC_9B3F_4348_BAB1_A5679D4E7913__INCLUDED_)
