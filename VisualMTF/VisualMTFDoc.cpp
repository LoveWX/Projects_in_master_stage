// VisualMTFDoc.cpp : implementation of the CVisualMTFDoc class
//

#include "stdafx.h"
#include "VisualMTF.h"

#include "VisualMTFDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVisualMTFDoc

IMPLEMENT_DYNCREATE(CVisualMTFDoc, CDocument)

BEGIN_MESSAGE_MAP(CVisualMTFDoc, CDocument)
	//{{AFX_MSG_MAP(CVisualMTFDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVisualMTFDoc construction/destruction

CVisualMTFDoc::CVisualMTFDoc()
{
	// TODO: add one-time construction code here

}

CVisualMTFDoc::~CVisualMTFDoc()
{
}

BOOL CVisualMTFDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CVisualMTFDoc serialization

void CVisualMTFDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CVisualMTFDoc diagnostics

#ifdef _DEBUG
void CVisualMTFDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CVisualMTFDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CVisualMTFDoc commands
