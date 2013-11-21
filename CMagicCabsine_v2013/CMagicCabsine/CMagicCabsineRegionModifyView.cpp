// MagicCabsineRegionModifyView.cpp : 实现文件
//

#include "stdafx.h"
#include "CMagicCabsine.h"
#include "CMagicCabsineRegionModifyView.h"
#include "CMagicCabsineDoc.h"
#include "bresenham.h"
#include "MainFrm.h"

// CMagicCabsineRegionModifyView

IMPLEMENT_DYNCREATE(CMagicCabsineRegionModifyView, CView)

CMagicCabsineRegionModifyView::CMagicCabsineRegionModifyView()
{
	displayImage = NULL;
	isSplit = FALSE;
	isMerge = FALSE;
	isModify = FALSE;
	isStartDraw = FALSE;
	isMarkFront = FALSE;
	isMarkBack = FALSE;

	maxX=0;
	maxY=0;

	yellowPen.CreatePen(PS_SOLID,2,RGB(255, 255, 0));
	greenPen.CreatePen(PS_SOLID,2,RGB(0, 255, 255));
	redPen.CreatePen(PS_SOLID,2,RGB(255, 0, 0));
}

CMagicCabsineRegionModifyView::~CMagicCabsineRegionModifyView()
{
	if(displayImage!=NULL)
	{
		cvReleaseImage(&displayImage);
		displayImage=NULL;
	}
}

BEGIN_MESSAGE_MAP(CMagicCabsineRegionModifyView, CView)
// 	ON_COMMAND(ID_REGION_MERGE, &CMagicCabsineRegionModifyView::OnRegionMerge)
// 	ON_COMMAND(ID_REGION_SPLIT, &CMagicCabsineRegionModifyView::OnRegionSplit)
// 	ON_COMMAND(ID_REGION_MODIFY, &CMagicCabsineRegionModifyView::OnRegionModify)
// 	ON_UPDATE_COMMAND_UI(ID_REGION_MERGE, &CMagicCabsineRegionModifyView::OnUpdateRegionMerge)
// 	ON_UPDATE_COMMAND_UI(ID_REGION_SPLIT, &CMagicCabsineRegionModifyView::OnUpdateRegionSplit)
// 	ON_UPDATE_COMMAND_UI(ID_REGION_MODIFY, &CMagicCabsineRegionModifyView::OnUpdateRegionModify)
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_REGION_MARK_FRONT, &CMagicCabsineRegionModifyView::OnRegionMarkFront)
	ON_COMMAND(ID_REGION_MARK_BACK, &CMagicCabsineRegionModifyView::OnRegionMarkBack)
	ON_UPDATE_COMMAND_UI(ID_REGION_MARK_FRONT, &CMagicCabsineRegionModifyView::OnUpdateRegionMarkFront)
	ON_UPDATE_COMMAND_UI(ID_REGION_MARK_BACK, &CMagicCabsineRegionModifyView::OnUpdateRegionMarkBack)
END_MESSAGE_MAP()


// CMagicCabsineRegionModifyView 绘图

void CMagicCabsineRegionModifyView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: 在此添加绘制代码
	//先固定缩放倍数为1.0
	double showSize=1.0;

	CRect windowRect;
	GetClientRect(&windowRect);
	//绘图
	if(displayImage==NULL)
	{
		return;
	}
	ShowImage(pDC,displayImage,windowRect,showSize,CPoint(0,0));
	/*if (splitLine.size()>1)
	{
		if (isSplit || isModify || isMerge)
		{
			showModifyLine(pDC, yellowPen, splitLine);
		}
		else if (isMarkFront)
		{
			showModifyLine(pDC, redPen, splitLine);
		} 
		else if (isMarkBack)
		{
			showModifyLine(pDC, greenPen, splitLine);
		}
	}*/
}


// CMagicCabsineRegionModifyView 诊断

#ifdef _DEBUG
void CMagicCabsineRegionModifyView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CMagicCabsineRegionModifyView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CMagicCabsineRegionModifyView 消息处理程序


// void CMagicCabsineRegionModifyView::OnRegionMerge()
// {
// 	// TODO: 在此添加命令处理程序代码
// 	isMerge = !isMerge;
// 	isSplit = FALSE;
// 	isModify = FALSE;
// 
// 	isMarkBack = FALSE;
// 	isMarkFront = FALSE;
// 
// 	if (isMerge)
// 	{
// 		MessageBox(CString("合并区域"),CString("分割修正"),MB_OK|MB_ICONWARNING);
// 	}
// }
// 
// 
// void CMagicCabsineRegionModifyView::OnRegionSplit()
// {
// 	// TODO: 在此添加命令处理程序代码
// 	isSplit = !isSplit;
// 	isMerge = FALSE;
// 	isModify = FALSE;
// 	isMarkBack = FALSE;
// 	isMarkFront = FALSE;
// 
// 	if (isSplit)
// 	{
// 		MessageBox(CString("新划分区域"),CString("分割修正"),MB_OK|MB_ICONWARNING);
// 	}
// }
// 
// 
// void CMagicCabsineRegionModifyView::OnRegionModify()
// {
// 	//TODO: 在此添加命令处理程序代码
// 	isModify = !isModify;
// 	isSplit = FALSE;
// 	isMerge = FALSE;
// 	isMarkBack = FALSE;
// 	isMarkFront = FALSE;
// 
// 	if (isModify)
// 	{
// 		MessageBox(CString("修改区域边界"),CString("分割修正"),MB_OK|MB_ICONWARNING);
// 	}
// }
// 
// 
// void CMagicCabsineRegionModifyView::OnUpdateRegionMerge(CCmdUI *pCmdUI)
// {
// 	// TODO: 在此添加命令更新用户界面处理程序代码
// 	CMagicCabsineDoc* pDoc = (CMagicCabsineDoc*)GetDocument();
// 	switch (pDoc->theProject->currentProcessType)
// 	{
// 	case PROCESS_UNIVERSALCALCED:
// 	case PROCESS_SPLITED:
// 		pCmdUI->Enable(TRUE);
// 		break;
// 	default:
// 		pCmdUI->Enable(FALSE);
// 		break;
// 	}
// 
// 	pCmdUI->SetCheck(isMerge);
// }
// 
// 
// void CMagicCabsineRegionModifyView::OnUpdateRegionSplit(CCmdUI *pCmdUI)
// {
// 	// TODO: 在此添加命令更新用户界面处理程序代码
// 	CMagicCabsineDoc* pDoc = (CMagicCabsineDoc*)GetDocument();
// 	switch (pDoc->theProject->currentProcessType)
// 	{
// 	case PROCESS_UNIVERSALCALCED:
// 	case PROCESS_SPLITED:
// 		pCmdUI->Enable(TRUE);
// 		break;
// 	default:
// 		pCmdUI->Enable(FALSE);
// 		break;
// 	}
// 	pCmdUI->SetCheck(isSplit);
// }
// 
// 
// void CMagicCabsineRegionModifyView::OnUpdateRegionModify(CCmdUI *pCmdUI)
// {
// 	// TODO: 在此添加命令更新用户界面处理程序代码
// 	CMagicCabsineDoc* pDoc = (CMagicCabsineDoc*)GetDocument();
// 	switch (pDoc->theProject->currentProcessType)
// 	{
// 	case PROCESS_UNIVERSALCALCED:
// 	case PROCESS_SPLITED:
// 		pCmdUI->Enable(TRUE);
// 		break;
// 	default:
// 		pCmdUI->Enable(FALSE);
// 		break;
// 	}
// 	pCmdUI->SetCheck(isModify);
// }


BOOL CMagicCabsineRegionModifyView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	return TRUE;
}


// 显示图像的方法
void CMagicCabsineRegionModifyView::ShowImage(CDC* pDC,const IplImage* img,CRect windowRect,double showSize,CPoint &top_left)
{
	CDC MemDC; //首先定义一个显示设备对象
	CBitmap MemBitmap;//定义一个位图对象

	//随后建立与屏幕显示兼容的内存显示设备
	MemDC.CreateCompatibleDC(NULL);
	//这时还不能绘图，因为没有地方画 ^_^
	//下面建立一个与屏幕显示兼容的位图，至于位图的大小嘛，可以用窗口的大小
	MemBitmap.CreateCompatibleBitmap(pDC,windowRect.Width(),windowRect.Height());

	//将位图选入到内存显示设备中  
	//只有选入了位图的内存显示设备才有地方绘图，画到指定的位图上
	CBitmap *pOldBit=MemDC.SelectObject(&MemBitmap);

	//先用背景色将位图清除干净，这里我用的是白色作为背景
	//你也可以用自己应该用的颜色
	MemDC.FillSolidRect(0,0,windowRect.Width(),windowRect.Height(),RGB(255,255,255));

	//绘图
	showImage2(&MemDC,displayImage,windowRect,showSize,top_left);

	//将内存中的图拷贝到屏幕上进行显示
	pDC->BitBlt(0,0,windowRect.Width(),windowRect.Height(),&MemDC,0,0,SRCCOPY);

	//绘图完成后的清理
	MemBitmap.DeleteObject();
	MemDC.DeleteDC();
	pOldBit=NULL;
}

double CMagicCabsineRegionModifyView::showImage2(CDC* pdc,const IplImage* img,CRect windowRect,double showSize,CPoint &top_left)
{
	if (img == NULL)
	{
		return -1;
	}
	CvSize tempSize;
	tempSize.height = img->height;
	tempSize.width = img->width;
	IplImage* tempImg = cvCreateImage(tempSize, img->depth, img->nChannels);
	cvCopyImage(img, tempImg);
	CvvImage imgData;
	imgData.CopyOf(tempImg);
	cvReleaseImage(&tempImg);
	tempImg=NULL;
	int window_height = windowRect.Height();
	int window_width = windowRect.Width();

	double imgHeight = imgData.Height() * showSize;
	double imgWidth = imgData.Width() * showSize;

	if (imgHeight > window_height)
	{
		if (top_left.y < (double)window_height - imgHeight)
		{
			top_left.y = (LONG)((double)window_height - imgHeight);
		}
		else if (top_left.y > 0)
		{
			top_left.y = 0;
		}
	}
	else
	{
		if (top_left.y < 0)
		{
			top_left.y = 0;
		}
		else if (top_left.y > (double)window_height - imgHeight)
		{
			top_left.y = (LONG)((double)window_height - imgHeight);
		}
	}

	if (imgWidth > window_width)
	{
		if (top_left.x < (double)window_width - imgWidth)
		{
			top_left.x = (LONG)((double)window_width - imgWidth);
		}
		else if (top_left.x > 0)
		{
			top_left.x = 0;
		}
	}
	else
	{
		if (top_left.x < 0)
		{
			top_left.x = 0;
		}
		else if (top_left.x > (double)window_width - imgWidth)
		{
			top_left.x = (LONG)((double)window_width - imgWidth);
		}
	}

	CRect showRect;
	showRect.left = top_left.x;
	showRect.top = top_left.y;
	showRect.right = (LONG)(top_left.x + imgWidth);
	showRect.bottom = (LONG)(top_left.y + imgHeight);
	HDC hDC = pdc->GetSafeHdc(); 
	imgData.DrawToHDC(hDC, &showRect);
	return showSize;
}

void CMagicCabsineRegionModifyView::SetDisplayImage(IplImage *tempImage)
{
	if(tempImage==NULL)
	{
		return;
	}
	if(displayImage!=NULL)
	{
		cvReleaseImage(&displayImage);
		displayImage=NULL;
	}
	displayImage=cvCloneImage(tempImage);
	maxX=tempImage->width-1;//设置水平方向的图片坐标最大值
	maxY=tempImage->height-1;//设置垂直方向的图片坐标最大值
}

void CMagicCabsineRegionModifyView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	splitLine.clear();
	if (point.x < maxX && point.y < maxY)
	{
		splitLine.push_back(point);
		isStartDraw = TRUE;
	}
	else
	{
		//MessageBox(CString("Out of the image_left button down"));
		splitLine.clear();
	}
	this->Invalidate();
	CView::OnLButtonDown(nFlags, point);
}


void CMagicCabsineRegionModifyView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (isStartDraw == FALSE)
	{
		return;
	}

	if (point.x < maxX && point.y < maxY)
	{
		splitLine.push_back(point);
	}
	else
	{
		//MessageBox(CString("Out of the image_left button up"));
		splitLine.clear();
		return;
	}

	CMagicCabsineDoc* pDoc = (CMagicCabsineDoc*)GetDocument();
	
	if(isMerge)
	{
		pDoc->theProject->getSplitData()->mergeRegion(getSplitLine(splitLine));
	}
	else if (isSplit)
	{
		pDoc->theProject->getSplitData()->splitRegion(getSplitLine(splitLine));
	}
	else if (isModify)
	{
		pDoc->theProject->getSplitData()->modifyRegion(getSplitLine(splitLine));
	}
	else if (isMarkFront)
	{
		pDoc->theProject->getSplitData()->markFrontAndBack(getSplitLine(splitLine), true);
	}
	else if (isMarkBack)
	{
		pDoc->theProject->getSplitData()->markFrontAndBack(getSplitLine(splitLine), false);
	}
	else
	{
		return;
	}

	MainFrame *mainFrame=(MainFrame*)AfxGetMainWnd();
	CMagicCabsineLeftView *m_leftView=(CMagicCabsineLeftView *)mainFrame->m_WndSplitter.GetPane(0,0);
	string splitName;
	pDoc->theProject->getSplitData()->GetSplitName(splitName);
	m_leftView->displayImageInTab(CString(splitName.c_str()), pDoc->theProject->getSplitData()->GetFrontBackImage(), TABTYPE_SPLIT_RES, 2 );
	m_leftView->displayImageInTab(CString(splitName.c_str()), pDoc->theProject->getSplitData()->GetDisplayImage(), TABTYPE_SPLIT_RES, 1);
	m_leftView->displayImageInTab(CString(splitName.c_str()), pDoc->theProject->getSplitData()->GetBoundaryImage(), TABTYPE_SPLIT_RES, 0);


	isStartDraw = FALSE;
	splitLine.clear();
	this->Invalidate();
	CView::OnLButtonUp(nFlags, point);
}


void CMagicCabsineRegionModifyView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (point.x < maxX && point.y < maxY )
	{
		if (!splitLine.empty() && isStartDraw)
		{
			CDC* dc = GetDC();
			if (isSplit || isModify || isMerge)
			{
				dc->SelectObject(yellowPen);
			}
			else if (isMarkFront)
			{
				dc->SelectObject(redPen);
			} 
			else if (isMarkBack)
			{
				dc->SelectObject(greenPen);
			}
			else
			{
				return;
			}
			dc->MoveTo(splitLine[splitLine.size()-1]);
			dc->LineTo(point);
			splitLine.push_back(point);
		}
	}
	else
	{
		if (isStartDraw)
		{
			CString str;
			str.Format("Out of the image_mouse move\n(%d, %d)", point.x, point.y);
			//MessageBox(str);
			splitLine.clear();
			isStartDraw = FALSE;
		}
	}

	CView::OnMouseMove(nFlags, point);
}


void CMagicCabsineRegionModifyView::showModifyLine(CDC* pDC,CPen &thePen,vector<CPoint> &tempPoly)
{
	if(pDC==NULL||tempPoly.size()==0)
	{
		return;
	}
	int i,length=tempPoly.size();
	POINT *drawPoint=new POINT[length];
	for(i=0;i<length;i++)
	{
		drawPoint[i]=tempPoly[i];
	}
	CPen *pOldPen=pDC->SelectObject(&thePen);
	pDC->Polyline(drawPoint,length);
	pDC->SelectObject(pOldPen);
	delete drawPoint;
	drawPoint=NULL;
}


vector<CvPoint> CMagicCabsineRegionModifyView::getSplitLine(vector<CPoint>& line)
{

	vector<CvPoint> tempLine;
	vector<CvPoint> resultLine;
	int pointNum = splitLine.size();
	CvPoint tempPoint;
	CvPoint oldPoint;
	oldPoint.x = splitLine[0].y;
	oldPoint.y = splitLine[0].x;
	for (int i=1; i<pointNum; i++)
	{
		tempPoint.y = splitLine[i].x;
		tempPoint.x = splitLine[i].y;
		bresenham(&tempLine, oldPoint.x, oldPoint.y, tempPoint.x, tempPoint.y);
		for (int j=0; j<tempLine.size()-1; j++)
		{
			resultLine.push_back(tempLine[j]);
		}
		tempLine.clear();
		oldPoint = tempPoint;
	}
	tempPoint.x = splitLine[line.size()-1].y;
	tempPoint.y = splitLine[line.size()-1].x;
	resultLine.push_back(tempPoint);
	return resultLine;
}

void CMagicCabsineRegionModifyView::OnRegionMarkFront()
{
	// TODO: 在此添加命令处理程序代码
	isModify = FALSE;
	isSplit = FALSE;
	isMerge = FALSE;
	isMarkBack = FALSE;
	isMarkFront = !isMarkFront;

	if (isMarkFront)
	{
		MessageBox(CString("标记前景"),CString("语义标注"),MB_OK|MB_ICONWARNING);
	}

}


void CMagicCabsineRegionModifyView::OnRegionMarkBack()
{
	// TODO: 在此添加命令处理程序代码
	isModify = FALSE;
	isSplit = FALSE;
	isMerge = FALSE;
	isMarkBack = !isMarkBack;
	isMarkFront = FALSE;

	if (isMarkBack)
	{
		MessageBox(CString("标记背景"),CString("语义标注"),MB_OK|MB_ICONWARNING);
	}
}


void CMagicCabsineRegionModifyView::OnUpdateRegionMarkFront(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	CMagicCabsineDoc* pDoc = (CMagicCabsineDoc*)GetDocument();

	if (pDoc->theProject->getImageType() == IMAGE_SCENERY)
	{
		return;
	}

	switch (pDoc->theProject->currentProcessType)
	{
	case PROCESS_UNIVERSALCALCED:
	case PROCESS_SPLITED:
		pCmdUI->Enable(TRUE);
		break;
	default:
		pCmdUI->Enable(FALSE);
		break;
	}

	pCmdUI->SetCheck(isMarkFront);
}


void CMagicCabsineRegionModifyView::OnUpdateRegionMarkBack(CCmdUI *pCmdUI)
{

	// TODO: 在此添加命令更新用户界面处理程序代码
	CMagicCabsineDoc* pDoc = (CMagicCabsineDoc*)GetDocument();

	if (pDoc->theProject->getImageType() == IMAGE_SCENERY)
	{
		return;
	}

	switch (pDoc->theProject->currentProcessType)
	{
	case PROCESS_UNIVERSALCALCED:
	case PROCESS_SPLITED:
		pCmdUI->Enable(TRUE);
		break;
	default:
		pCmdUI->Enable(FALSE);
		break;
	}

	pCmdUI->SetCheck(isMarkBack);
}

void CMagicCabsineRegionModifyView::CloseView()
{
	if(displayImage!=NULL)
	{
		cvReleaseImage(&displayImage);
		displayImage=NULL;
	}
}

IplImage* CMagicCabsineRegionModifyView::GetDisplayImage()
{
	return displayImage;
}

void CMagicCabsineRegionModifyView::ClearDisplayImage()
{
	if(displayImage==NULL)//没有图片在显示,不需要清理
	{
		return;
	}
	int i,j;
	int height=displayImage->height;
	int width=displayImage->width;
	CvScalar whiteColor=cvScalar(255,255,255);
	for(i=0;i<height;i++)
	{
		for(j=0;j<width;j++)
		{
			cvSet2D(displayImage,i,j,whiteColor);
		}
	}
}
