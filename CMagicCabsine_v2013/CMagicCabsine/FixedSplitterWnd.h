//���ļ�����CSplitterWnd��ʵ������޷��϶����ڷָ���
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
