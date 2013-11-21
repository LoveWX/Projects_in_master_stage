//该文件重载CSplitterWnd类实现鼠标无法拖动窗口分割条
//2012-11-29,zhouzhou

#pragma once
#include "afxext.h"
class CFixedSplitterWnd : public CSplitterWnd
{
public:
	CFixedSplitterWnd();
	~CFixedSplitterWnd();

	DECLARE_MESSAGE_MAP()
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};
