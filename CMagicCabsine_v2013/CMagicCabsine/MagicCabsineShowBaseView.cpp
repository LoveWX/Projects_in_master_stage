
#include "stdafx.h"
#include "MagicCabsineShowBaseView.h"
#include "CMagicCabsineDoc.h"

IMPLEMENT_DYNCREATE(CMagicCabsineShowBaseView, CScrollView)


CMagicCabsineShowBaseView::CMagicCabsineShowBaseView()          // 动态创建所使用的受保护的构造函数
{
	startPoint = CPoint(0,0);
	endPoint = CPoint(0,0);
	startMove = false;
	top_left = CPoint(0,0);
	tempSizeIndex = 5;
	showSize = 1.0;
}

CMagicCabsineShowBaseView::~CMagicCabsineShowBaseView()          
{
}

BEGIN_MESSAGE_MAP(CMagicCabsineShowBaseView, CScrollView)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_ERASEBKGND()
	ON_WM_MOUSEWHEEL()
END_MESSAGE_MAP()

#ifdef _DEBUG
void CMagicCabsineShowBaseView::AssertValid() const
{
	CScrollView::AssertValid();
}

#ifndef _WIN32_WCE
void CMagicCabsineShowBaseView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}
#endif
#endif //_DEBUG


void CMagicCabsineShowBaseView::OnDraw(CDC* pDC)
{
}

BOOL CMagicCabsineShowBaseView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	return TRUE;
}

void CMagicCabsineShowBaseView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	/*CMagicCabsineDoc* pDoc = (CMagicCabsineDoc*)GetDocument();
	switch (pDoc->m_currentMouse)
	{
	case MOUSE_MOVE:
		endPoint = point;
		startMove = true;
		break;
	}
	this->Invalidate();*/
	CScrollView::OnLButtonDown(nFlags, point);
}


void CMagicCabsineShowBaseView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//CMagicCabsineDoc* pDoc = (CMagicCabsineDoc*)GetDocument();
	//switch (pDoc->m_currentMouse)
	//{
	//case MOUSE_MOVE:
	//	if (startMove)
	//	{
	//		startPoint = endPoint;
	//		endPoint = point;
	//		int move_x = endPoint.x - startPoint.x;
	//		int move_y = endPoint.y - startPoint.y;
	//		top_left.x += move_x;
	//		top_left.y += move_y;
	//	}
	//	startMove = false;
	//	break;
	//case MOUSE_ZOOM_IN:
	//	tempSizeIndex--;
	//	if(tempSizeIndex < 0)
	//	{
	//		tempSizeIndex = 0;
	//	}
	//	showSize = picsize_show[tempSizeIndex];
	//	break;
	//case MOUSE_ZOOM_OUT:
	//	tempSizeIndex++;
	//	if(tempSizeIndex > 11)
	//	{
	//		tempSizeIndex = 11;
	//	}
	//	showSize = picsize_show[tempSizeIndex];
	//	break;
	//}
	//this->Invalidate();



	CScrollView::OnLButtonUp(nFlags, point);
}


void CMagicCabsineShowBaseView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	//CMagicCabsineDoc* pDoc = (CMagicCabsineDoc*)GetDocument();
	//switch (pDoc->m_currentMouse)
	//{
	//case MOUSE_MOVE:
	//	if (startMove)
	//	{
	//		startPoint = endPoint;
	//		endPoint = point;
	//		int move_x = endPoint.x - startPoint.x;
	//		int move_y = endPoint.y - startPoint.y;
	//		top_left.x += move_x;
	//		top_left.y += move_y;
	//		this->Invalidate();
	//	}
	//	break;
	//}
	CScrollView::OnMouseMove(nFlags, point);
}

void CMagicCabsineShowBaseView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: 计算此视图的合计大小
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);
}




BOOL CMagicCabsineShowBaseView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	if (zDelta==-120)
	{
		showSize -= 0.1;
		if (showSize<0.1)
		{
			showSize = 0.1;
		}
	}
	if (zDelta==120)
	{
		showSize += 0.2;
		if (showSize>1)
		{
			showSize = 1.0;
		}
	}
	this->Invalidate(FALSE);

	return CScrollView::OnMouseWheel(nFlags, zDelta, pt);
}
