#pragma once


// CMagicCabsineShowBaseView 视图

class CMagicCabsineShowBaseView : public CScrollView
{
	DECLARE_DYNCREATE(CMagicCabsineShowBaseView)
protected:
	CMagicCabsineShowBaseView();           // 动态创建所使用的受保护的构造函数
	virtual ~CMagicCabsineShowBaseView();

public:
	virtual void OnDraw(CDC* pDC) ;      // 重写以绘制该视图
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
public:

	virtual void OnInitialUpdate();     // 构造后的第一次


	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
protected:
	CPoint		startPoint;
	CPoint		endPoint;
	bool		startMove;
	CPoint		top_left;			//显示位置
	double		showSize;			//显示比例
	int			tempSizeIndex;		//显示比例数组索引
public:
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
};


