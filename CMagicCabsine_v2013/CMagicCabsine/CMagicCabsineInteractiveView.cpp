// CMagicCabsineInteractiveView.cpp : 实现文件
//

#include "stdafx.h"
#include "CMagicCabsineDoc.h"
#include "MainFrm.h"

#include "CMagicCabsine.h"
#include "CMagicCabsineInteractiveView.h"
#include "bresenham.h"
#include "MagicCabsineRegionMarkDlg.h"

// CMagicCabsineInteractiveView

IMPLEMENT_DYNCREATE(CMagicCabsineInteractiveView, CView)

CMagicCabsineInteractiveView::CMagicCabsineInteractiveView()
{
	foregroundPoints.clear();
	backgroundPoints.clear();
	foregroundLines.clear();
	backgroundLines.clear();
	isMarkingForeground=FALSE;
	isMarkingBackground=FALSE;
	displayImage=NULL;
	userMarksImage=NULL;
	redPen.CreatePen(PS_SOLID,2,RGB(255,0,0));
	greenPen.CreatePen(PS_SOLID,2,RGB(0,255,0));
	bluePen.CreatePen(PS_SOLID,2,RGB(0,0,255));
	yellowPen.CreatePen(PS_SOLID,2,RGB(255, 255, 0));
	maxX=0;
	maxY=0;
	lastDrawingPoint=CPoint(0,0);
	isSplited=FALSE;
	splitLine.clear();
	isSplit = FALSE;
	isMerge = FALSE;
	isModify = FALSE;
	isStartDraw = FALSE;
	enableModify = TRUE;
}

CMagicCabsineInteractiveView::~CMagicCabsineInteractiveView()
{
	foregroundPoints.clear();
	backgroundPoints.clear();
	foregroundLines.clear();
	backgroundLines.clear();
	splitLine.clear();
	isMarkingForeground=FALSE;
	isMarkingBackground=FALSE;
	if(displayImage!=NULL)
	{
		cvReleaseImage(&displayImage);
		displayImage=NULL;
	}
	if(userMarksImage!=NULL)
	{
		cvReleaseImage(&userMarksImage);
		userMarksImage=NULL;
	}
	maxX=0;
	maxY=0;
	lastDrawingPoint=CPoint(0,0);
	isSplited = FALSE;
	isSplit = FALSE;
	isMerge = FALSE;
	isModify = FALSE;
	isStartDraw = FALSE;
}

BEGIN_MESSAGE_MAP(CMagicCabsineInteractiveView, CView)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_REGION_MERGE, &CMagicCabsineInteractiveView::OnRegionMerge)
	ON_COMMAND(ID_REGION_SPLIT, &CMagicCabsineInteractiveView::OnRegionSplit)
	ON_COMMAND(ID_REGION_MODIFY, &CMagicCabsineInteractiveView::OnRegionModify)
	ON_UPDATE_COMMAND_UI(ID_REGION_MERGE, &CMagicCabsineInteractiveView::OnUpdateRegionMerge)
	ON_UPDATE_COMMAND_UI(ID_REGION_SPLIT, &CMagicCabsineInteractiveView::OnUpdateRegionSplit)
	ON_UPDATE_COMMAND_UI(ID_REGION_MODIFY, &CMagicCabsineInteractiveView::OnUpdateRegionModify)
	ON_WM_LBUTTONDBLCLK()
	ON_COMMAND(ID_REGION_MODIFY_OK, &CMagicCabsineInteractiveView::OnRegionModifyOk)
	ON_COMMAND(ID_MARK_FOREGROUND, &CMagicCabsineInteractiveView::OnMarkForeground)
	ON_COMMAND(ID_MARK_BACKGROUND, &CMagicCabsineInteractiveView::OnMarkBackground)
	ON_COMMAND(ID_MARK_REGION_LINE, &CMagicCabsineInteractiveView::OnMarkRegionLine)
	ON_COMMAND(ID_MARK_DOWN, &CMagicCabsineInteractiveView::OnMarkDown)
	ON_UPDATE_COMMAND_UI(ID_MARK_FOREGROUND, &CMagicCabsineInteractiveView::OnUpdateMarkForeground)
	ON_UPDATE_COMMAND_UI(ID_MARK_BACKGROUND, &CMagicCabsineInteractiveView::OnUpdateMarkBackground)
	ON_UPDATE_COMMAND_UI(ID_MARK_REGION_LINE, &CMagicCabsineInteractiveView::OnUpdateMarkRegionLine)
	ON_COMMAND(ID_MARK_CLEAR, &CMagicCabsineInteractiveView::OnMarkClear)
	ON_UPDATE_COMMAND_UI(ID_MARK_DOWN, &CMagicCabsineInteractiveView::OnUpdateMarkDown)
	ON_UPDATE_COMMAND_UI(ID_MARK_CLEAR, &CMagicCabsineInteractiveView::OnUpdateMarkClear)
	ON_UPDATE_COMMAND_UI(ID_REGION_MODIFY_OK, &CMagicCabsineInteractiveView::OnUpdateRegionModifyOk)
	ON_COMMAND(ID_REGION_UNDO, &CMagicCabsineInteractiveView::OnRegionUndo)
	ON_COMMAND(ID_REGION_REDO, &CMagicCabsineInteractiveView::OnRegionRedo)
	ON_UPDATE_COMMAND_UI(ID_REGION_UNDO, &CMagicCabsineInteractiveView::OnUpdateRegionUndo)
	ON_UPDATE_COMMAND_UI(ID_REGION_REDO, &CMagicCabsineInteractiveView::OnUpdateRegionRedo)
END_MESSAGE_MAP()


// CMagicCabsineInteractiveView 绘图

void CMagicCabsineInteractiveView::OnDraw(CDC* pDC)
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

	//绘制已经标记的线
	int i;
	for(i=0;i<backgroundLines.size();i++)
	{
		drawPolyLine(pDC,redPen,backgroundLines[i]);
	}
	for(i=0;i<foregroundLines.size();i++)
	{
		drawPolyLine(pDC,bluePen,foregroundLines[i]);
	}
}


// CMagicCabsineInteractiveView 诊断

#ifdef _DEBUG
void CMagicCabsineInteractiveView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CMagicCabsineInteractiveView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG

void CMagicCabsineInteractiveView::DrawUserMarks()
{
	CvScalar greenColor=cvScalar(0,255,0);//所标记前景线条的颜色
	CvScalar blueColor=cvScalar(255,0,0);//所标记背景线条的颜色
	int thinkness=2;//所标记线条的宽度

	if(userMarksImage!=NULL)
	{
		cvReleaseImage(&userMarksImage);
		userMarksImage=NULL;
	}
	userMarksImage=cvCloneImage(displayImage);

	int i,j,xx,yy;
	CvPoint currentPoint,lastPoint;
	//注意这里需要用cvLine来画线,点坐标表示和CvPoint及cvSet2D不一样
	for(i=0;i<foregroundLines.size();i++)
	{
		xx=foregroundLines[i][0].x;
		yy=foregroundLines[i][0].y;
		if(foregroundLines[i].size()<=1)
		{
			cvSet2D(userMarksImage,yy,xx,greenColor);
			continue;
		}
		lastPoint=cvPoint(xx,yy);
		for(j=1;j<foregroundLines[i].size();j++)
		{
			currentPoint=cvPoint(foregroundLines[i][j].x,foregroundLines[i][j].y);
			cvLine(userMarksImage,lastPoint,currentPoint,greenColor,thinkness);
			lastPoint=currentPoint;
		}
	}
	for(i=0;i<backgroundLines.size();i++)
	{
		xx=backgroundLines[i][0].x;
		yy=backgroundLines[i][0].y;
		if(backgroundLines[i].size()<=1)
		{
			cvSet2D(userMarksImage,yy,xx,blueColor);
			continue;
		}
		lastPoint=cvPoint(xx,yy);
		for(j=1;j<backgroundLines[i].size();j++)
		{
			currentPoint=cvPoint(backgroundLines[i][j].x,backgroundLines[i][j].y);
			cvLine(userMarksImage,lastPoint,currentPoint,blueColor,thinkness);
			lastPoint=currentPoint;
		}
	}
}

IplImage* CMagicCabsineInteractiveView::GetDisplayImage()
{
	if(userMarksImage==NULL)
	{
		DrawUserMarks();
	}
	return userMarksImage;
}

void CMagicCabsineInteractiveView::SetDisplayImage(IplImage *tempImage)
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

	isModify = FALSE;
	isMerge = FALSE;
	isSplit = FALSE;
}

void CMagicCabsineInteractiveView::EnableMarking()
{
	isSplited=FALSE;
}

void CMagicCabsineInteractiveView::EnableMarkingForeground()
{
	isMarkingForeground=TRUE;
	isMarkingBackground=FALSE;
}

void CMagicCabsineInteractiveView::EnableMarkingBackground()
{
	isMarkingBackground=TRUE;
	isMarkingForeground=FALSE;
}

void CMagicCabsineInteractiveView::DisableMarking()
{
	isMarkingForeground=FALSE;
	isMarkingBackground=FALSE;
}

void CMagicCabsineInteractiveView::ClearMarking()
{
	foregroundPoints.clear();
	backgroundPoints.clear();
	foregroundLines.clear();
	backgroundLines.clear();
//	isSplited=FALSE;
	this->Invalidate();
}

BOOL CMagicCabsineInteractiveView::IsSplited()
{
	return isSplited;
}

void CMagicCabsineInteractiveView::SetSplitDone()
{
	isSplited=TRUE;
}

void CMagicCabsineInteractiveView::GetCvPoint(vector< vector<CvPoint> > &foreLines,vector< vector<CvPoint> > &backLines)
{
	foreLines.clear();
	backLines.clear();
	int i,j,xx,yy;
	vector<CvPoint> tempVector;
	for(i=0;i<foregroundLines.size();i++)
	{
		tempVector.clear();
		for(j=0;j<foregroundLines[i].size();j++)
		{
			xx=foregroundLines[i][j].x;
			yy=foregroundLines[i][j].y;
			tempVector.push_back(cvPoint(yy,xx));
		}
		foreLines.push_back(tempVector);
	}
	for(i=0;i<backgroundLines.size();i++)
	{
		tempVector.clear();
		for(j=0;j<backgroundLines[i].size();j++)
		{
			xx=backgroundLines[i][j].x;
			yy=backgroundLines[i][j].y;
			tempVector.push_back(cvPoint(yy,xx));
		}
		backLines.push_back(tempVector);
	}
}

void CMagicCabsineInteractiveView::SetCvPoint(const vector< vector<CvPoint> > &foreLines,const vector< vector<CvPoint> > &backLines)
{
	int i,j;
	CPoint tempPoint;
	CClientDC dc(this);
	foregroundLines.clear();
	backgroundLines.clear();
	vector<CPoint> tempVector;
	for(i=0;i<foreLines.size();i++)
	{
		tempVector.clear();
		for(j=0;j<foreLines[i].size();j++)
		{
			tempPoint.y=foreLines[i][j].x;
			tempPoint.x=foreLines[i][j].y;
			tempVector.push_back(tempPoint);
		}
		foregroundLines.push_back(tempVector);
		drawPolyLine(&dc,greenPen,tempVector);
	}
	for(i=0;i<backLines.size();i++)
	{
		tempVector.clear();
		for(j=0;j<backLines[i].size();j++)
		{
			tempPoint.y=backLines[i][j].x;
			tempPoint.x=backLines[i][j].y;
			tempVector.push_back(tempPoint);
		}
		backgroundLines.push_back(tempVector);
		drawPolyLine(&dc,bluePen,tempVector);
	}
}

void CMagicCabsineInteractiveView::ShowImage(CDC* pDC,const IplImage* img,CRect windowRect,double showSize,CPoint &top_left)
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

double CMagicCabsineInteractiveView::showImage2(CDC* pdc,const IplImage* img,CRect windowRect,double showSize,CPoint &top_left)
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

void CMagicCabsineInteractiveView::drawPolyLine(CDC* pDC,CPen &thePen,vector<CPoint> &tempPoly)
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
	//CPen *pOldPen=pDC->SelectObject(&thePen);
	//int length=tempPoly.size();
	//pDC->MoveTo(tempPoly[0]);
	//for (int i=1; i<length; i++)
	//{
	//	pDC->LineTo(tempPoly[i]);
	//}
}

BOOL CMagicCabsineInteractiveView::isInImageScope(const CPoint &thePoint)
{
	if(thePoint.x<0||thePoint.y<0)
	{
		return FALSE;
	}
	if(thePoint.x>maxX||thePoint.y>maxY)
	{
		return FALSE;
	}
	return TRUE;
}

BOOL CMagicCabsineInteractiveView::putInImageScope(CPoint &thePoint)
{
	BOOL isInImage=TRUE;
	if(thePoint.x<0)
	{
		thePoint.x=0;
		isInImage=FALSE;
	}
	if(thePoint.y<0)
	{
		thePoint.y=0;
		isInImage=FALSE;
	}
	if(thePoint.x>maxX)
	{
		thePoint.x=maxX;
		isInImage=FALSE;
	}
	if(thePoint.y>maxY)
	{
		thePoint.y=maxY;
		isInImage=FALSE;
	}
	return isInImage;
}

BOOL CMagicCabsineInteractiveView::putInImageScope(CvPoint &thePoint)
{
	BOOL isInImage=TRUE;
	if(thePoint.x<0)
	{
		thePoint.x=0;
		isInImage=FALSE;
	}
	if(thePoint.y<0)
	{
		thePoint.y=0;
		isInImage=FALSE;
	}
	if(thePoint.x>maxY)
	{
		thePoint.x=maxY;
		isInImage=FALSE;
	}
	if(thePoint.y>maxX)
	{
		thePoint.y=maxX;
		isInImage=FALSE;
	}
	return isInImage;
}

void CMagicCabsineInteractiveView::CloseView()
{
	//直接从析构函数中复制过来的
	foregroundPoints.clear();
	backgroundPoints.clear();
	foregroundLines.clear();
	backgroundLines.clear();
	splitLine.clear();
	isMarkingForeground=FALSE;
	isMarkingBackground=FALSE;
	if(displayImage!=NULL)
	{
		cvReleaseImage(&displayImage);
		displayImage=NULL;
	}
	if(userMarksImage!=NULL)
	{
		cvReleaseImage(&userMarksImage);
		userMarksImage=NULL;
	}
	maxX=0;
	maxY=0;
	lastDrawingPoint=CPoint(0,0);
	isSplited=FALSE;

	enableModify = TRUE;
}

// CMagicCabsineInteractiveView 消息处理程序


void CMagicCabsineInteractiveView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	if(!isInImageScope(point))
	{
		//如果在边界之外
		foregroundPoints.clear();
		backgroundPoints.clear();
		splitLine.clear();
		isStartDraw = FALSE;
		return;
	}
	if (isMarkingForeground)
	{
		//正在标记前景
		foregroundPoints.clear();
		foregroundPoints.push_back(point);
		isStartDraw = TRUE;
	} 
	else if (isMarkingBackground)
	{
		//正在标记背景
		backgroundPoints.clear();
		backgroundPoints.push_back(point);
		isStartDraw = TRUE;
	}
	else if (isMerge||isSplit||isModify)
	{
		//分割，合并，修改边界
		splitLine.clear();
		splitLine.push_back(point);
		isStartDraw = TRUE;
	}
	else
	{
		isStartDraw = FALSE;
	}
	lastDrawingPoint=point;
//	this->Invalidate();
	CView::OnLButtonDown(nFlags, point);
}


void CMagicCabsineInteractiveView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (isStartDraw == FALSE)
	{
		return;
	}

	CMagicCabsineDoc* pDoc = (CMagicCabsineDoc*)GetDocument();
	CPoint tempPoint=point;
	putInImageScope(tempPoint);//将点置于图片范围中

	if(isMarkingForeground)
	{
		//正在标记前景
		if(lastDrawingPoint!=tempPoint)
		{
			foregroundPoints.push_back(tempPoint);
		}
		if (foregroundPoints.empty())
		{
			return;
		}
		foregroundLines.push_back(breseMarkLine(foregroundPoints));
		foregroundPoints.clear();
	}
	else if(isMarkingBackground)
	{
		//正在标记背景
		if(lastDrawingPoint!=tempPoint)
		{
			backgroundPoints.push_back(tempPoint);
		}
		if (backgroundPoints.empty())
		{
			return;
		}
		backgroundLines.push_back(breseMarkLine(backgroundPoints));
		backgroundPoints.clear();
	}
	else if(isMerge || isSplit || isModify)
	{
		if(isMerge)
		{
			vector<CvPoint>& tempMergeLine = getSplitLine(splitLine);
			if (tempMergeLine.size() < 2)
			{
				return;
			}
			//判断是否合并区域的线
			const IplImage* frontBackImg = pDoc->theProject->getSplitData()->GetFrontBackImage();		//获取前背景图像
			CvPoint tempCvPoint = tempMergeLine[0];
			CvScalar tempColor = cvGet2D(frontBackImg, tempCvPoint.x, tempCvPoint.y);
			int tempR = (int)(tempColor.val[2]);
			int tempG = (int)(tempColor.val[1]);
			int tempB = (int)(tempColor.val[0]);
			for (int i=1; i<tempMergeLine.size(); i++)
			{
				tempCvPoint = tempMergeLine[i];
				tempColor = cvGet2D(frontBackImg, tempCvPoint.x, tempCvPoint.y);
				if (tempColor.val[0] != tempB ||
					tempColor.val[1] != tempG ||
					tempColor.val[2] != tempR)
				{
					splitLine.clear();
					this->Invalidate();
					MessageBox(CString("不允许前背景区域的合并"),CString("区域分割提示"),MB_OK|MB_ICONWARNING);
					return;
				}
			}

			pDoc->theProject->getSplitData()->mergeRegion(tempMergeLine);
		}
		else if (isSplit)
		{
			pDoc->theProject->getSplitData()->splitRegion(getSplitLine(splitLine));
		}
		else if (isModify)
		{
			vector<CvPoint>& tempModifyLine = getSplitLine(splitLine);
			if (tempModifyLine.size() > 100)
			{
				MessageBox(CString("只允许简单修改边界"));
				splitLine.clear();
				return;
			}
			pDoc->theProject->getSplitData()->modifyRegion(tempModifyLine);
		}
		else
		{
			return;
		}
		MainFrame *mainFrame=(MainFrame*)AfxGetMainWnd();
		CMagicCabsineLeftView *m_leftView=(CMagicCabsineLeftView *)mainFrame->m_WndSplitter.GetPane(0,0);
		string splitName;
		pDoc->theProject->getSplitData()->GetSplitName(splitName);
// 		m_leftView->displayImageInTab(CString(splitName.c_str()), pDoc->theProject->getSplitData()->GetFrontBackImage(), TABTYPE_SPLIT_RES, 2 );
// 		m_leftView->displayImageInTab(CString(splitName.c_str()), pDoc->theProject->getSplitData()->GetDisplayImage(), TABTYPE_SPLIT_RES, 1);
// 		m_leftView->displayImageInTab(CString(splitName.c_str()), pDoc->theProject->getSplitData()->GetBoundaryImage(), TABTYPE_SPLIT_RES, 0);
// 		m_leftView->displayImageInTab(CString(splitName.c_str()), pDoc->theProject->getSplitData()->GetBoundaryImage(), TABTYPE_SPLIT );

		CString tName=CString(splitName.c_str());
		IplImage *tempImage0=pDoc->theProject->getSplitData()->GetBoundaryImage();
		IplImage *tempImage1=pDoc->theProject->getSplitData()->GetDisplayImage();
		IplImage *tempImage2=pDoc->theProject->getSplitData()->GetFrontBackImage();
		SegmentationData *tData=new SegmentationData(pDoc->theProject->getSplitData()->getSplitMat(),tempImage0,tempImage1,tempImage2);
		pDoc->theProject->undoStack->pushState(tData);
		tData=NULL;//由undoStack释放
		m_leftView->displayImageInTab(tName, tempImage2, TABTYPE_SPLIT_RES, 2 );
		m_leftView->displayImageInTab(tName, tempImage1, TABTYPE_SPLIT_RES, 1);
		m_leftView->displayImageInTab(tName, tempImage0, TABTYPE_SPLIT_RES, 0);
		m_leftView->displayImageInTab(tName, tempImage0, TABTYPE_SPLIT );
		
		splitLine.clear();
		this->Invalidate();
	}

	isStartDraw = FALSE;
	
	CView::OnLButtonUp(nFlags, point);
}

void CMagicCabsineInteractiveView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(!isStartDraw)
	{
		return;
	}

	CPoint tempPoint=point;
	putInImageScope(tempPoint);//将点置于图片范围中

	if(lastDrawingPoint!=tempPoint)
	{
		if(isMarkingForeground )
		{
			//正在标记前景
			foregroundPoints.push_back(tempPoint);

			CDC* dc = GetDC();
			dc->SelectObject(bluePen);
			dc->MoveTo(lastDrawingPoint);
			dc->LineTo(tempPoint);
		}
		else if(isMarkingBackground  )
		{
			//正在标记背景
			backgroundPoints.push_back(tempPoint);
			CDC* dc = GetDC();
			dc->SelectObject(redPen);
			dc->MoveTo(lastDrawingPoint);
			dc->LineTo(tempPoint);
		}
		else if (isSplit || isModify || isMerge)
		{
			if (splitLine.empty())
			{
				isStartDraw;
				return;
			}
			else
			{
				splitLine.push_back(tempPoint);
				CDC* dc = GetDC();
				dc->SelectObject(yellowPen);
				dc->MoveTo(lastDrawingPoint);
				dc->LineTo(tempPoint);
			}
		}	
		else
		{
			return;
		}
		lastDrawingPoint=tempPoint;
	}
	CView::OnMouseMove(nFlags, point);
}
	


// CMagicCabsineInteractiveView 消息处理程序


void CMagicCabsineInteractiveView::OnRegionMerge()
{
	// TODO: 在此添加命令处理程序代码
	isMerge = !isMerge;
	isSplit = FALSE;
	isModify = FALSE;


	if (isMerge)
	{
		MessageBox(CString("画一条线对现有区域进行合并"),CString("区域合并"),MB_OK|MB_ICONINFORMATION);
	}
}


void CMagicCabsineInteractiveView::OnRegionSplit()
{
	// TODO: 在此添加命令处理程序代码
	isSplit = !isSplit;
	isMerge = FALSE;
	isModify = FALSE;

	if (isSplit)
	{
		MessageBox(CString("画一条线对现有区域进行分割"),CString("区域分割"),MB_OK|MB_ICONINFORMATION);
	}
}


void CMagicCabsineInteractiveView::OnRegionModify()
{
	//TODO: 在此添加命令处理程序代码
	isModify = !isModify;
	isSplit = FALSE;
	isMerge = FALSE;

	if (isModify)
	{
		MessageBox(CString("画一条线对现有区域的边界进行修改"),CString("区域边界修改"),MB_OK|MB_ICONINFORMATION);
	}
}


void CMagicCabsineInteractiveView::OnUpdateRegionMerge(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	CMagicCabsineDoc* pDoc = (CMagicCabsineDoc*)GetDocument();
	switch (pDoc->theProject->currentProcessType)
	{
	case PROCESS_SPLIT_MARKDOWN:
//	case PROCESS_SPLITED:
		pCmdUI->Enable(enableModify);
		pCmdUI->SetCheck(isMerge);
		break;
	default:
		pCmdUI->Enable(FALSE);
		pCmdUI->SetCheck(FALSE);
		break;
	}

}


void CMagicCabsineInteractiveView::OnUpdateRegionSplit(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	CMagicCabsineDoc* pDoc = (CMagicCabsineDoc*)GetDocument();
	switch (pDoc->theProject->currentProcessType)
	{
	case PROCESS_SPLIT_MARKDOWN:
//	case PROCESS_SPLITED:
		pCmdUI->Enable(enableModify);
		pCmdUI->SetCheck(isSplit);
		break;
	default:
		pCmdUI->Enable(FALSE);
		pCmdUI->SetCheck(FALSE);
		break;
	}
}


void CMagicCabsineInteractiveView::OnUpdateRegionModify(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	CMagicCabsineDoc* pDoc = (CMagicCabsineDoc*)GetDocument();
	switch (pDoc->theProject->currentProcessType)
	{
	case PROCESS_SPLIT_MARKDOWN:
//	case PROCESS_SPLITED:
		pCmdUI->Enable(enableModify);
		pCmdUI->SetCheck(isModify);
		break;
	default:
		pCmdUI->Enable(FALSE);
		pCmdUI->SetCheck(FALSE);
		break;
	}
}


BOOL CMagicCabsineInteractiveView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	return TRUE;
}

//vector<CvPoint> CMagicCabsineInteractiveView::getSplitLine(vector<CPoint>& line)
//{
//	vector<CvPoint> tempLine;
//	vector<CvPoint> resultLine;
//	int pointNum = splitLine.size();
//	CvPoint tempPoint;
//	CvPoint oldPoint;
//	oldPoint.x = splitLine[0].y;
//	oldPoint.y = splitLine[0].x;
//	for (int i=1; i<pointNum; i++)
//	{
//		tempPoint.y = splitLine[i].x;
//		tempPoint.x = splitLine[i].y;
//		bresenham(&tempLine, oldPoint.x, oldPoint.y, tempPoint.x, tempPoint.y);
//
//		for (int j=0; j<tempLine.size()-1; j++)
//		{
//	//		putInImageScope(tempLine[j]);
//			resultLine.push_back(tempLine[j]);
//		}
//		tempLine.clear();
//		oldPoint = tempPoint;
//	}
//	tempPoint.x = splitLine[line.size()-1].y;
//	tempPoint.y = splitLine[line.size()-1].x;
//	resultLine.push_back(tempPoint);
//	return resultLine;
//
//}

vector<CvPoint> CMagicCabsineInteractiveView::getSplitLine(vector<CPoint>& line)
{
	vector<CvPoint> tempLine;
	for (int i=0; i<line.size(); i++)
	{
		tempLine.push_back(cvPoint(line[i].y, line[i].x));
	}

	BresenhamDrawLine(tempLine);

	return tempLine;

	//vector<CvPoint> resultLine;
	//int pointNum = splitLine.size();
	//CvPoint tempPoint;
	//CvPoint oldPoint;
	//oldPoint.x = splitLine[0].y;
	//oldPoint.y = splitLine[0].x;
	//for (int i=1; i<pointNum; i++)
	//{
	//	tempPoint.y = splitLine[i].x;
	//	tempPoint.x = splitLine[i].y;
	//	bresenham(&tempLine, oldPoint.x, oldPoint.y, tempPoint.x, tempPoint.y);

	//	//		BresenhamDrawLine(line)
	//	for (int j=0; j<tempLine.size()-1; j++)
	//	{
	//		//		putInImageScope(tempLine[j]);
	//		resultLine.push_back(tempLine[j]);
	//	}
	//	tempLine.clear();
	//	oldPoint = tempPoint;
	//}
	//tempPoint.x = splitLine[line.size()-1].y;
	//tempPoint.y = splitLine[line.size()-1].x;
	//resultLine.push_back(tempPoint);
	//return resultLine;

}


vector<CPoint> CMagicCabsineInteractiveView::breseMarkLine(vector<CPoint>& line)
{
	vector<CPoint> tempLine;
	vector<CPoint> resultLine;
	int pointNum = line.size();
	CPoint tempPoint;
	CPoint oldPoint;
	oldPoint = line[0];
	for (int i=1; i<pointNum; i++)
	{
		tempPoint = line[i];
		bresenham(&tempLine, oldPoint.x, oldPoint.y, tempPoint.x, tempPoint.y);
		for (int j=0; j<tempLine.size()-1; j++)
		{
			putInImageScope(tempLine[j]);
			resultLine.push_back(tempLine[j]);
		}
		tempLine.clear();
		oldPoint = tempPoint;
	}
	return resultLine;

}

void CMagicCabsineInteractiveView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CMagicCabsineDoc* pDoc = (CMagicCabsineDoc*)GetDocument();
	if(pDoc->theProject->currentProcessType != PROCESS_SPLITED)
	{
		return;
	}

	if (isInImageScope(point))
	{
		isSplit = FALSE;
		isMerge = FALSE;
		isModify = FALSE;
		isStartDraw = FALSE;

		CMagicCabsineRegionMarkDlg dlg;
		dlg.setPoint(point.x, point.y);
		dlg.setSplitData(pDoc->theProject->getSplitData());
		dlg.DoModal();
		MainFrame *mainFrame=(MainFrame*)AfxGetMainWnd();
		CMagicCabsineLeftView *m_leftView=(CMagicCabsineLeftView *)mainFrame->m_WndSplitter.GetPane(0,0);
		string splitName;
		pDoc->theProject->getSplitData()->GetSplitName(splitName);
		m_leftView->displayImageInTab(CString(splitName.c_str()), pDoc->theProject->getSplitData()->GetFrontBackImage(), TABTYPE_SPLIT_RES, 2 );
		m_leftView->displayImageInTab(CString(splitName.c_str()), pDoc->theProject->getSplitData()->GetDisplayImage(), TABTYPE_SPLIT_RES, 1 );
		m_leftView->displayImageInTab(CString(splitName.c_str()), pDoc->theProject->getSplitData()->GetBoundaryImage(), TABTYPE_SPLIT );
		this->SetActiveWindow();
	}
	CView::OnLButtonDblClk(nFlags, point);
}


void CMagicCabsineInteractiveView::OnRegionModifyOk()
{
	// TODO: 在此添加命令处理程序代码
	MessageBox(CString("请双击某区域来修改该区域的属性"),CString("区域属性修改"),MB_OK|MB_ICONINFORMATION);
	enableModify = FALSE;
	CMagicCabsineDoc* pDoc = (CMagicCabsineDoc*)GetDocument();
	pDoc->theProject->currentProcessType = PROCESS_SPLITED;
	pDoc->theProject->getSplitData()->regularAllData();

	isModify = FALSE;
	isMerge = FALSE;
	isSplit = FALSE;
}


void CMagicCabsineInteractiveView::OnMarkForeground()
{
	// TODO: 在此添加命令处理程序代码
	CString tempMsg=CString("请单击\"确定\"后标记前景");
	MessageBox(tempMsg,CString("标记前景"),MB_OK|MB_ICONINFORMATION);
	EnableMarking();
	EnableMarkingForeground();
}


void CMagicCabsineInteractiveView::OnMarkBackground()
{
	// TODO: 在此添加命令处理程序代码

	CString tempMsg=CString("请单击\"确定\"后标记背景");
	MessageBox(tempMsg,CString("标记背景"),MB_OK|MB_ICONINFORMATION);

	
	EnableMarking();
	EnableMarkingBackground();
}


void CMagicCabsineInteractiveView::OnMarkRegionLine()
{
	// TODO: 在此添加命令处理程序代码
}


void CMagicCabsineInteractiveView::OnMarkDown()
{
	// TODO: 在此添加命令处理程序代码
	MessageBox(CString("标记已完成\n正在进行分割"),CString("标记完成"),MB_OK|MB_ICONINFORMATION);
	
	SetSplitDone();
	DisableMarking();

	CMagicCabsineDoc* pDoc = (CMagicCabsineDoc*)GetDocument();
	pDoc->theProject->RunWorkStep2();
	ClearMarking();

	isMarkingForeground = FALSE;
	isMarkingBackground = FALSE;
}


void CMagicCabsineInteractiveView::OnUpdateMarkForeground(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	CMagicCabsineDoc* pDoc = (CMagicCabsineDoc*)GetDocument();
	switch (pDoc->theProject->currentProcessType)
	{
	case PROCESS_UNIVERSALCALCED:
		pCmdUI->Enable(TRUE);
		break;
	default:
		pCmdUI->Enable(FALSE);
		break;
	}
	pCmdUI->SetCheck(isMarkingForeground);
}


void CMagicCabsineInteractiveView::OnUpdateMarkBackground(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	CMagicCabsineDoc* pDoc = (CMagicCabsineDoc*)GetDocument();
	switch (pDoc->theProject->currentProcessType)
	{
	case PROCESS_UNIVERSALCALCED:
		pCmdUI->Enable(TRUE);
		break;
	default:
		pCmdUI->Enable(FALSE);
		break;
	}
	pCmdUI->SetCheck(isMarkingBackground);
}


void CMagicCabsineInteractiveView::OnUpdateMarkRegionLine(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	CMagicCabsineDoc* pDoc = (CMagicCabsineDoc*)GetDocument();
	switch (pDoc->theProject->currentProcessType)
	{
	case PROCESS_UNIVERSALCALCED:
		pCmdUI->Enable(FALSE);//目前暂时不能进行勾选区域轮廓,所以置为FALSE
		break;
	default:
		pCmdUI->Enable(FALSE);
		break;
	}
}



void CMagicCabsineInteractiveView::OnMarkClear()
{
	// TODO: 在此添加命令处理程序代码
	isMarkingForeground = FALSE;
	isMarkingBackground = FALSE;
	CString tempMsg=CString("确定要删除标记吗?\n单击\"确定\"清除标记\n单击\"取消\"保留标记");
	if(MessageBox(tempMsg,CString("清除标记?"),MB_OKCANCEL|MB_ICONWARNING)==IDCANCEL)
	{
		return;
	}
	ClearMarking();
// 	Invalidate();
}


void CMagicCabsineInteractiveView::OnUpdateMarkDown(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	CMagicCabsineDoc* pDoc = (CMagicCabsineDoc*)GetDocument();
	switch (pDoc->theProject->currentProcessType)
	{
	case PROCESS_UNIVERSALCALCED:
		pCmdUI->Enable(TRUE);
		break;
	default:
		pCmdUI->Enable(FALSE);
		break;
	}
}


void CMagicCabsineInteractiveView::OnUpdateMarkClear(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	CMagicCabsineDoc* pDoc = (CMagicCabsineDoc*)GetDocument();
	switch (pDoc->theProject->currentProcessType)
	{
	case PROCESS_UNIVERSALCALCED:
		pCmdUI->Enable(TRUE);
		break;
	default:
		pCmdUI->Enable(FALSE);
		break;
	}
}


void CMagicCabsineInteractiveView::OnUpdateRegionModifyOk(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码

	CMagicCabsineDoc* pDoc = (CMagicCabsineDoc*)GetDocument();
	switch (pDoc->theProject->currentProcessType)
	{
	case PROCESS_SPLIT_MARKDOWN:
		pCmdUI->Enable(enableModify);
		break;
	default:
		pCmdUI->Enable(FALSE);
		break;
	}

	pCmdUI->SetCheck(FALSE);

}

void CMagicCabsineInteractiveView::OnRegionUndo()
{
	CMagicCabsineDoc* pDoc = (CMagicCabsineDoc*)GetDocument();
	if(!(pDoc->theProject->undoStack->Undo()))
	{
		return;
	}
	MainFrame *mainFrame=(MainFrame*)AfxGetMainWnd();
	CMagicCabsineLeftView *m_leftView=(CMagicCabsineLeftView *)mainFrame->m_WndSplitter.GetPane(0,0);
	string splitName;
	pDoc->theProject->getSplitData()->GetSplitName(splitName);
	CString tName=CString(splitName.c_str());
	SegmentationData *cur=pDoc->theProject->undoStack->getCurrentPoint();
	pDoc->theProject->getSplitData()->setSplitMat(cur->splitMatrix);
	m_leftView->displayImageInTab(tName, cur->frontBackImage, TABTYPE_SPLIT_RES, 2 );
	m_leftView->displayImageInTab(tName, cur->maincolorImage, TABTYPE_SPLIT_RES, 1);
	m_leftView->displayImageInTab(tName, cur->boundaryImage, TABTYPE_SPLIT_RES, 0);
	m_leftView->displayImageInTab(tName, cur->boundaryImage, TABTYPE_SPLIT );
	cur=NULL;
	this->Invalidate();
}

void CMagicCabsineInteractiveView::OnRegionRedo()
{
	CMagicCabsineDoc* pDoc = (CMagicCabsineDoc*)GetDocument();
	if(!(pDoc->theProject->undoStack->Redo()))
	{
		return;
	}
	MainFrame *mainFrame=(MainFrame*)AfxGetMainWnd();
	CMagicCabsineLeftView *m_leftView=(CMagicCabsineLeftView *)mainFrame->m_WndSplitter.GetPane(0,0);
	string splitName;
	pDoc->theProject->getSplitData()->GetSplitName(splitName);
	CString tName=CString(splitName.c_str());
	SegmentationData *cur=pDoc->theProject->undoStack->getCurrentPoint();
	pDoc->theProject->getSplitData()->setSplitMat(cur->splitMatrix);
	m_leftView->displayImageInTab(tName, cur->frontBackImage, TABTYPE_SPLIT_RES, 2 );
	m_leftView->displayImageInTab(tName, cur->maincolorImage, TABTYPE_SPLIT_RES, 1);
	m_leftView->displayImageInTab(tName, cur->boundaryImage, TABTYPE_SPLIT_RES, 0);
	m_leftView->displayImageInTab(tName, cur->boundaryImage, TABTYPE_SPLIT );
	cur=NULL;
	this->Invalidate();
}

void CMagicCabsineInteractiveView::OnUpdateRegionUndo(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	CMagicCabsineDoc* pDoc = (CMagicCabsineDoc*)GetDocument();
	switch (pDoc->theProject->currentProcessType)
	{
	case PROCESS_SPLIT_MARKDOWN:
//	case PROCESS_SPLITED:
		if(pDoc->theProject->undoStack->isLeftEmpty())
		{
			pCmdUI->Enable(FALSE);
		}
		else
		{
			pCmdUI->Enable(TRUE);
		}
		break;
	default:
		pCmdUI->Enable(FALSE);
		break;
	}
}

void CMagicCabsineInteractiveView::OnUpdateRegionRedo(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	CMagicCabsineDoc* pDoc = (CMagicCabsineDoc*)GetDocument();
	switch (pDoc->theProject->currentProcessType)
	{
	case PROCESS_SPLIT_MARKDOWN:
//	case PROCESS_SPLITED:
		if(pDoc->theProject->undoStack->isRightEmpty())
		{
			pCmdUI->Enable(FALSE);
		}
		else
		{
			pCmdUI->Enable(TRUE);
		}
		break;
	default:
		pCmdUI->Enable(FALSE);
		break;
	}
}
