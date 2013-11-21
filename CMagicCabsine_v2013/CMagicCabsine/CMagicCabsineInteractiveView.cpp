// CMagicCabsineInteractiveView.cpp : ʵ���ļ�
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


// CMagicCabsineInteractiveView ��ͼ

void CMagicCabsineInteractiveView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: �ڴ���ӻ��ƴ���

	//�ȹ̶����ű���Ϊ1.0
	double showSize=1.0;

	CRect windowRect;
	GetClientRect(&windowRect);

	//��ͼ
	if(displayImage==NULL)
	{
		return;
	}
	ShowImage(pDC,displayImage,windowRect,showSize,CPoint(0,0));

	//�����Ѿ���ǵ���
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


// CMagicCabsineInteractiveView ���

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
	CvScalar greenColor=cvScalar(0,255,0);//�����ǰ����������ɫ
	CvScalar blueColor=cvScalar(255,0,0);//����Ǳ�����������ɫ
	int thinkness=2;//����������Ŀ��

	if(userMarksImage!=NULL)
	{
		cvReleaseImage(&userMarksImage);
		userMarksImage=NULL;
	}
	userMarksImage=cvCloneImage(displayImage);

	int i,j,xx,yy;
	CvPoint currentPoint,lastPoint;
	//ע��������Ҫ��cvLine������,�������ʾ��CvPoint��cvSet2D��һ��
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
	maxX=tempImage->width-1;//����ˮƽ�����ͼƬ�������ֵ
	maxY=tempImage->height-1;//���ô�ֱ�����ͼƬ�������ֵ

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
	CDC MemDC; //���ȶ���һ����ʾ�豸����
	CBitmap MemBitmap;//����һ��λͼ����

	//���������Ļ��ʾ���ݵ��ڴ���ʾ�豸
	MemDC.CreateCompatibleDC(NULL);
	//��ʱ�����ܻ�ͼ����Ϊû�еط��� ^_^
	//���潨��һ������Ļ��ʾ���ݵ�λͼ������λͼ�Ĵ�С������ô��ڵĴ�С
	MemBitmap.CreateCompatibleBitmap(pDC,windowRect.Width(),windowRect.Height());

	//��λͼѡ�뵽�ڴ���ʾ�豸��  
	//ֻ��ѡ����λͼ���ڴ���ʾ�豸���еط���ͼ������ָ����λͼ��
	CBitmap *pOldBit=MemDC.SelectObject(&MemBitmap);

	//���ñ���ɫ��λͼ����ɾ����������õ��ǰ�ɫ��Ϊ����
	//��Ҳ�������Լ�Ӧ���õ���ɫ
	MemDC.FillSolidRect(0,0,windowRect.Width(),windowRect.Height(),RGB(255,255,255));

	//��ͼ
	showImage2(&MemDC,displayImage,windowRect,showSize,top_left);

	//���ڴ��е�ͼ��������Ļ�Ͻ�����ʾ
	pDC->BitBlt(0,0,windowRect.Width(),windowRect.Height(),&MemDC,0,0,SRCCOPY);

	//��ͼ��ɺ������
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
	//ֱ�Ӵ����������и��ƹ�����
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

// CMagicCabsineInteractiveView ��Ϣ�������


void CMagicCabsineInteractiveView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	if(!isInImageScope(point))
	{
		//����ڱ߽�֮��
		foregroundPoints.clear();
		backgroundPoints.clear();
		splitLine.clear();
		isStartDraw = FALSE;
		return;
	}
	if (isMarkingForeground)
	{
		//���ڱ��ǰ��
		foregroundPoints.clear();
		foregroundPoints.push_back(point);
		isStartDraw = TRUE;
	} 
	else if (isMarkingBackground)
	{
		//���ڱ�Ǳ���
		backgroundPoints.clear();
		backgroundPoints.push_back(point);
		isStartDraw = TRUE;
	}
	else if (isMerge||isSplit||isModify)
	{
		//�ָ�ϲ����޸ı߽�
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
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (isStartDraw == FALSE)
	{
		return;
	}

	CMagicCabsineDoc* pDoc = (CMagicCabsineDoc*)GetDocument();
	CPoint tempPoint=point;
	putInImageScope(tempPoint);//��������ͼƬ��Χ��

	if(isMarkingForeground)
	{
		//���ڱ��ǰ��
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
		//���ڱ�Ǳ���
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
			//�ж��Ƿ�ϲ��������
			const IplImage* frontBackImg = pDoc->theProject->getSplitData()->GetFrontBackImage();		//��ȡǰ����ͼ��
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
					MessageBox(CString("������ǰ��������ĺϲ�"),CString("����ָ���ʾ"),MB_OK|MB_ICONWARNING);
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
				MessageBox(CString("ֻ������޸ı߽�"));
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
		tData=NULL;//��undoStack�ͷ�
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
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if(!isStartDraw)
	{
		return;
	}

	CPoint tempPoint=point;
	putInImageScope(tempPoint);//��������ͼƬ��Χ��

	if(lastDrawingPoint!=tempPoint)
	{
		if(isMarkingForeground )
		{
			//���ڱ��ǰ��
			foregroundPoints.push_back(tempPoint);

			CDC* dc = GetDC();
			dc->SelectObject(bluePen);
			dc->MoveTo(lastDrawingPoint);
			dc->LineTo(tempPoint);
		}
		else if(isMarkingBackground  )
		{
			//���ڱ�Ǳ���
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
	


// CMagicCabsineInteractiveView ��Ϣ�������


void CMagicCabsineInteractiveView::OnRegionMerge()
{
	// TODO: �ڴ���������������
	isMerge = !isMerge;
	isSplit = FALSE;
	isModify = FALSE;


	if (isMerge)
	{
		MessageBox(CString("��һ���߶�����������кϲ�"),CString("����ϲ�"),MB_OK|MB_ICONINFORMATION);
	}
}


void CMagicCabsineInteractiveView::OnRegionSplit()
{
	// TODO: �ڴ���������������
	isSplit = !isSplit;
	isMerge = FALSE;
	isModify = FALSE;

	if (isSplit)
	{
		MessageBox(CString("��һ���߶�����������зָ�"),CString("����ָ�"),MB_OK|MB_ICONINFORMATION);
	}
}


void CMagicCabsineInteractiveView::OnRegionModify()
{
	//TODO: �ڴ���������������
	isModify = !isModify;
	isSplit = FALSE;
	isMerge = FALSE;

	if (isModify)
	{
		MessageBox(CString("��һ���߶���������ı߽�����޸�"),CString("����߽��޸�"),MB_OK|MB_ICONINFORMATION);
	}
}


void CMagicCabsineInteractiveView::OnUpdateRegionMerge(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
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
	// TODO: �ڴ������������û����洦��������
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
	// TODO: �ڴ������������û����洦��������
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
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

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
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
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
	// TODO: �ڴ���������������
	MessageBox(CString("��˫��ĳ�������޸ĸ����������"),CString("���������޸�"),MB_OK|MB_ICONINFORMATION);
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
	// TODO: �ڴ���������������
	CString tempMsg=CString("�뵥��\"ȷ��\"����ǰ��");
	MessageBox(tempMsg,CString("���ǰ��"),MB_OK|MB_ICONINFORMATION);
	EnableMarking();
	EnableMarkingForeground();
}


void CMagicCabsineInteractiveView::OnMarkBackground()
{
	// TODO: �ڴ���������������

	CString tempMsg=CString("�뵥��\"ȷ��\"���Ǳ���");
	MessageBox(tempMsg,CString("��Ǳ���"),MB_OK|MB_ICONINFORMATION);

	
	EnableMarking();
	EnableMarkingBackground();
}


void CMagicCabsineInteractiveView::OnMarkRegionLine()
{
	// TODO: �ڴ���������������
}


void CMagicCabsineInteractiveView::OnMarkDown()
{
	// TODO: �ڴ���������������
	MessageBox(CString("��������\n���ڽ��зָ�"),CString("������"),MB_OK|MB_ICONINFORMATION);
	
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
	// TODO: �ڴ������������û����洦��������
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
	// TODO: �ڴ������������û����洦��������
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
	// TODO: �ڴ������������û����洦��������
	CMagicCabsineDoc* pDoc = (CMagicCabsineDoc*)GetDocument();
	switch (pDoc->theProject->currentProcessType)
	{
	case PROCESS_UNIVERSALCALCED:
		pCmdUI->Enable(FALSE);//Ŀǰ��ʱ���ܽ��й�ѡ��������,������ΪFALSE
		break;
	default:
		pCmdUI->Enable(FALSE);
		break;
	}
}



void CMagicCabsineInteractiveView::OnMarkClear()
{
	// TODO: �ڴ���������������
	isMarkingForeground = FALSE;
	isMarkingBackground = FALSE;
	CString tempMsg=CString("ȷ��Ҫɾ�������?\n����\"ȷ��\"������\n����\"ȡ��\"�������");
	if(MessageBox(tempMsg,CString("������?"),MB_OKCANCEL|MB_ICONWARNING)==IDCANCEL)
	{
		return;
	}
	ClearMarking();
// 	Invalidate();
}


void CMagicCabsineInteractiveView::OnUpdateMarkDown(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
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
	// TODO: �ڴ������������û����洦��������
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
	// TODO: �ڴ������������û����洦��������

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
	// TODO: �ڴ������������û����洦��������
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
	// TODO: �ڴ������������û����洦��������
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
