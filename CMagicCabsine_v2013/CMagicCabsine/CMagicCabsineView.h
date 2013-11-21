
// CMagicCabsineView.h : CMagicCabsineView 类的接口
//

#pragma once

#include "CMagicCabsineDoc.h"

class CMagicCabsineView : public CView
{
protected: // 仅从序列化创建
	CMagicCabsineView();
	DECLARE_DYNCREATE(CMagicCabsineView)

// 特性
public:
	CMagicCabsineDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CMagicCabsineView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // CMagicCabsineView.cpp 中的调试版本
inline CMagicCabsineDoc* CMagicCabsineView::GetDocument() const
   { return reinterpret_cast<CMagicCabsineDoc*>(m_pDocument); }
#endif

