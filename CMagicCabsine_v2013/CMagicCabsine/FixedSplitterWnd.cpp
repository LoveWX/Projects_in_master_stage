#include "StdAfx.h"
#include "FixedSplitterWnd.h"


CFixedSplitterWnd::CFixedSplitterWnd()
{
}


CFixedSplitterWnd::~CFixedSplitterWnd()
{
}
BEGIN_MESSAGE_MAP(CFixedSplitterWnd, CSplitterWnd)
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


void CFixedSplitterWnd::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	//CSplitterWnd::OnMouseMove(nFlags, point);
	//CWnd::OnMouseMove(nFlags, point);
}
