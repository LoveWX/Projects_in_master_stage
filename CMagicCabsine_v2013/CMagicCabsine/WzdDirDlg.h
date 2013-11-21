// WzdDirDlg.h: interface for the CWzdDirDlg class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WZDDIRDLG_H__5C6586C8_A790_4979_8F6D_C80F21176411__INCLUDED_)
#define AFX_WZDDIRDLG_H__5C6586C8_A790_4979_8F6D_C80F21176411__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CWzdDirDlg  
{
public:
	static CString m_strRootDir;

public:
	CString GetDirectory(CWnd *pParent,LPCSTR lpszRoot,LPCSTR lpszTitle );
	CWzdDirDlg();
	virtual ~CWzdDirDlg();


};

int CALLBACK BrowseCalbackProc(HWND hwnd,UINT uMsg,LPARAM lp,LPARAM pData);

#endif // !defined(AFX_WZDDIRDLG_H__5C6586C8_A790_4979_8F6D_C80F21176411__INCLUDED_)
