// WzdDirDlg.cpp: implementation of the CWzdDirDlg class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "WzdDirDlg.h"
#include <shlobj.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CString CWzdDirDlg::m_strRootDir ;
CWzdDirDlg::CWzdDirDlg()
{

}

CWzdDirDlg::~CWzdDirDlg()
{

}

CString CWzdDirDlg::GetDirectory(CWnd *pParent, LPCSTR lpszRoot, LPCSTR lpszTitle )
{
	CString str;
	BROWSEINFO bi;
	bi.hwndOwner = pParent->m_hWnd;
	bi.pidlRoot = 0;
	bi.pszDisplayName  = 0;
	bi.lpszTitle = lpszTitle;
	bi.lpfn = BrowseCalbackProc;

	bi.lParam = 0;
	bi.ulFlags = BIF_RETURNONLYFSDIRS;// | BIF_STATUSTEXT;

	m_strRootDir = lpszRoot;

	str = "";

	LPITEMIDLIST lpItemId = ::SHBrowseForFolder(&bi);
	if(lpItemId)
	{
		LPTSTR szBuf = str.GetBuffer(MAX_PATH);
		::SHGetPathFromIDList(lpItemId,szBuf);
		::GlobalFree(lpItemId);
		str.ReleaseBuffer();

	}


	return str;

}

int CALLBACK BrowseCalbackProc(HWND hwnd,UINT uMsg,LPARAM lp,LPARAM pData)
{
	TCHAR buf[MAX_PATH];
	switch(uMsg)
	{
	case BFFM_INITIALIZED:
		strcpy_s(buf,CWzdDirDlg::m_strRootDir);
		::SendMessage(hwnd,BFFM_SETSELECTION,TRUE,(LPARAM)buf);
		break;
	case BFFM_SELCHANGED:
		if(::SHGetPathFromIDList((LPITEMIDLIST)lp,buf))
		{
			::SendMessage(hwnd,BFFM_SETSTATUSTEXT,0,(LPARAM)buf);
		}
		break;
	}

	return 0;
}
