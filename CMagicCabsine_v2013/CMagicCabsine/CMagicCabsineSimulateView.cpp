// CMagicCabsineSimulateView.cpp : 实现文件
//

#include "stdafx.h"
#include "CMagicCabsine.h"
#include "CMagicCabsineSimulateView.h"
#include "MainFrm.h"
#include "CMagicCabsineDoc.h"
#include "RegionModifyDLG.h"


// CMagicCabsineSimulateView

IMPLEMENT_DYNCREATE(CMagicCabsineSimulateView, CMagicCabsineShowBaseView)

CMagicCabsineSimulateView::CMagicCabsineSimulateView()
{
	levelIndex=0;
	displayImage=NULL;
	highlightImage.clear();
	currentRegionImage=0;
	tabID=-1;
//	isClicked = false;
}

CMagicCabsineSimulateView::~CMagicCabsineSimulateView()
{
	levelIndex=0;
// 	if(displayImage!=NULL)
// 	{
// 		cvReleaseImage(&displayImage);
// 		displayImage=NULL;
// 	}
	//与其它视图不同,此视图中的displayImage其实是highlightImage[0],所以在下列循环中统一释放
	if(displayImage!=NULL)
	{
		cvReleaseImage(&displayImage);
		displayImage=NULL;
	}
	int i;
	for(i=0;i<highlightImage.size();i++)
	{
		displayImage=highlightImage[i];
		highlightImage[i]=NULL;
		if(displayImage!=NULL)
		{
			cvReleaseImage(&displayImage);
			displayImage=NULL;
		}
	}
	highlightImage.clear();
	currentRegionImage=0;
	tabID=-1;
}

BEGIN_MESSAGE_MAP(CMagicCabsineSimulateView, CMagicCabsineShowBaseView)
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDBLCLK()
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CMagicCabsineSimulateView 绘图

void CMagicCabsineSimulateView::OnDraw(CDC* pDC)
{
 	CDocument* pDoc = GetDocument();
 	// TODO: 在此添加绘制代码
	

}


// CMagicCabsineSimulateView 诊断

#ifdef _DEBUG
void CMagicCabsineSimulateView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CMagicCabsineSimulateView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG

void CMagicCabsineSimulateView::SetDisplayImage(IplImage *tempImage)
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
	currentRegionImage=0;
}

void CMagicCabsineSimulateView::showImage(CDC* pdc, const IplImage* img, CRect windowRect, double showSize, CPoint &top_left)
{
	CDC MemDC; //首先定义一个显示设备对象  
	CBitmap MemBitmap;//定义一个位图对象  

	//随后建立与屏幕显示兼容的内存显示设备  
	MemDC.CreateCompatibleDC(NULL);  
	//这时还不能绘图，因为没有地方画 ^_^  
	//下面建立一个与屏幕显示兼容的位图，至于位图的大小嘛，可以用窗口的大小  
	MemBitmap.CreateCompatibleBitmap(pdc,windowRect.Width(),windowRect.Height());  

	//将位图选入到内存显示设备中  
	//只有选入了位图的内存显示设备才有地方绘图，画到指定的位图上  
	CBitmap *pOldBit=MemDC.SelectObject(&MemBitmap);  

	//先用背景色将位图清除干净，这里我用的是白色作为背景  
	//你也可以用自己应该用的颜色  
	MemDC.FillSolidRect(0,0,windowRect.Width(),windowRect.Height(),RGB(255,255,255));  

	//绘图
	showImage2(&MemDC, img, windowRect, showSize, top_left);

	//将内存中的图拷贝到屏幕上进行显示  
	pdc->BitBlt(0,0,windowRect.Width(),windowRect.Height(),&MemDC,0,0,SRCCOPY);  

	//绘图完成后的清理  
	MemBitmap.DeleteObject();  
	MemDC.DeleteDC();  
}

double CMagicCabsineSimulateView::showImage2(CDC* pdc, const IplImage* img, CRect windowRect, double showSize, CPoint &top_left)
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
	int window_height = windowRect.Height();
	int window_width = windowRect.Width();

	double imgHeight = imgData.Height() * showSize;
	double imgWidth = imgData.Width() * showSize;

	if (imgHeight > window_height)
	{
		if (top_left.y < window_height - imgHeight)
		{
			top_left.y = window_height - imgHeight;
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
		else if (top_left.y > window_height - imgHeight)
		{
			top_left.y = window_height - imgHeight;
		}
	}

	if (imgWidth > window_width)
	{
		if (top_left.x < window_width - imgWidth)
		{
			top_left.x = window_width - imgWidth;
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
		else if (top_left.x > window_width - imgWidth)
		{
			top_left.x = window_width - imgWidth;
		}
	}


	CRect showRect;
	showRect.left = top_left.x;
	showRect.top = top_left.y;
	showRect.right = top_left.x + imgWidth;
	showRect.bottom = top_left.y + imgHeight;
	HDC hDC = pdc->GetSafeHdc(); 
	imgData.DrawToHDC(hDC, &showRect);
	return showSize;
}

IplImage* CMagicCabsineSimulateView::GetDisplayImage()
{
	return displayImage;
}

void CMagicCabsineSimulateView::SetLevelIndex(int level)
{
	levelIndex=level;
}

void CMagicCabsineSimulateView::CalcHighLightImage(const vector< vector<int> > &splitMatrix)
{
// 	int i,j,k;
// 	highlightImage.clear();
// 	int height=displayImage->height;
// 	int width=displayImage->width;
// 	int currentRegion;
// 	IplImage *tempImage=displayImage;
// 	CvScalar tempColor;
// 	highlightImage.push_back(tempImage);
// 	for(i=0;i<height;i++)
// 	{
// 		for(j=0;j<width;j++)
// 		{
// 			currentRegion=splitMatrix[i][j];
// 			//向量中还没有这个区域号,添加进向量中
// 			if(currentRegion+1>highlightImage.size())
// 			{
// 				for(k=highlightImage.size();k<=currentRegion;k++)
// 				{
// 					highlightImage.push_back(cvCloneImage(tempImage));
// 				}
// 			}
// 			tempColor=cvGet2D(tempImage,i,j);
// 			lightSinglePoint(tempColor);
// 			cvSet2D(highlightImage[currentRegion],i,j,tempColor);
// 		}
// 	}
// 	tempImage=NULL;
}

void CMagicCabsineSimulateView::lightSinglePoint(CvScalar &theColor)
{
	int t0=(int)(theColor.val[0]);
	int t1=(int)(theColor.val[1]);
	int t2=(int)(theColor.val[2]);
	if(t0>127)
	{
		theColor.val[0]=255;
	}
	else
	{
		theColor.val[0]=t0+t0;
	}
	if(t1>127)
	{
		theColor.val[1]=255;
	}
	else
	{
		theColor.val[1]=t1+t1;
	}
	if(t2>127)
	{
		theColor.val[2]=255;
	}
	else
	{
		theColor.val[2]=t2+t2;
	}
}

void CMagicCabsineSimulateView::CloseView()
{
	//直接从析构函数中复制过来的
	levelIndex=0;
	//与其它视图不同,此视图中的displayImage其实是highlightImage[0],所以在下列循环中统一释放
	if(displayImage!=NULL)
	{
		cvReleaseImage(&displayImage);
		displayImage=NULL;
	}
	int i;
	for(i=0;i<highlightImage.size();i++)
	{
		displayImage=highlightImage[i];
		highlightImage[i]=NULL;
		if(displayImage!=NULL)
		{
			cvReleaseImage(&displayImage);
			displayImage=NULL;
		}
	}
	highlightImage.clear();
	currentRegionImage=0;
}

// CMagicCabsineSimulateView 消息处理程序


void CMagicCabsineSimulateView::OnLButtonDown(UINT nFlags, CPoint point)
{
	/*
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CMagicCabsineDoc* pDoc=(CMagicCabsineDoc*)GetDocument();
	if(pDoc->theProject->currentProcessType!=PROCESS_SIMULATED)
	{
		CView::OnLButtonDown(nFlags, point);
		return;//不属于模拟交互的步骤
	}

	int height=displayImage->height;
	int width=displayImage->width;
	int xx=point.x;
	int yy=point.y;
	if(xx<0||xx>=width||yy<0||yy>=height)
	{
		//没有在图片范围内点击
		if(currentRegionImage>0)//需要将显示图片重新换成原图
		{
			displayImage=highlightImage[0];
			currentRegionImage=0;
			this->Invalidate(FALSE);
		}
		CView::OnLButtonDown(nFlags, point);
		return;
	}

	//获得区域号,注意CPoint和CvPoint坐标的不同
	
	CMagicCabsineSimulateData_Test *simulateData=(CMagicCabsineSimulateData_Test *)pDoc->theProject->GetSimulateData();
	int regionNum=simulateData->GetRegionNum(yy,xx);
	THREAD_TYPE tempType=simulateData->GetThreadType(regionNum,levelIndex);
	int regionArea=simulateData->GetRegionArea(regionNum,levelIndex);
	CvScalar regionColor=simulateData->GetMainColor(regionNum,levelIndex);
	int numOfThread=simulateData->GetNumOfThread(regionNum,levelIndex);

	//显示在右边的属性栏中
	CString str;
	MainFrame *mainFrame=(MainFrame*)AfxGetMainWnd();

	str.Format("%d",regionNum);
	mainFrame->m_wndProperties.m_wndPropList.GetProperty(0)->GetSubItem(0)->SetValue(str);
	str.Format("%d",levelIndex+1);
	mainFrame->m_wndProperties.m_wndPropList.GetProperty(0)->GetSubItem(1)->SetValue(str);
	str.Format("%d",regionArea);
	mainFrame->m_wndProperties.m_wndPropList.GetProperty(0)->GetSubItem(2)->SetValue(str);
	str.Format("%d",(int)(regionColor.val[2]));
	mainFrame->m_wndProperties.m_wndPropList.GetProperty(0)->GetSubItem(3)->SetValue(str);
	str.Format("%d",(int)(regionColor.val[1]));
	mainFrame->m_wndProperties.m_wndPropList.GetProperty(0)->GetSubItem(4)->SetValue(str);
	str.Format("%d",(int)(regionColor.val[0]));
	mainFrame->m_wndProperties.m_wndPropList.GetProperty(0)->GetSubItem(5)->SetValue(str);
	if(tempType==THREAD_TYPE1)
	{
		str=CString("绣线类型1");
	}
	else
	{
		str=CString("绣线类型2");
	}
	mainFrame->m_wndProperties.m_wndPropList.GetProperty(0)->GetSubItem(6)->SetValue(str);
	str.Format("%d",numOfThread);
	mainFrame->m_wndProperties.m_wndPropList.GetProperty(0)->GetSubItem(7)->SetValue(str);

	//按照点选的区域显示图片
	displayImage=highlightImage[regionNum];
	currentRegionImage=regionNum;
	this->Invalidate(FALSE);
	*/
	CMagicCabsineShowBaseView::OnLButtonDown(nFlags, point);
}

void CMagicCabsineSimulateView::OnRButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//if (isClicked==false)
	//{
	//	CView::OnRButtonDblClk(nFlags, point);
	//	return;
	//}

	CMagicCabsineDoc* pDoc=(CMagicCabsineDoc*)GetDocument();
	if(pDoc->theProject->currentProcessType!=PROCESS_SIMULATED)
	{
		return;
	}

	int XRoll = GetScrollPos(SB_HORZ);
	int YRoll = GetScrollPos(SB_VERT);

	int x,y;
	x = (point.x+XRoll)/(2*showSize);
	y = (point.y+YRoll)/(2*showSize);
	CMagicCabsineSimulateData_Test* sd = (CMagicCabsineSimulateData_Test*)(pDoc->theProject->GetSimulateData());
	
	int regID = sd->GetRegionNum(y,x);
	if(regID<=0)
	{
		return;
	}
	int levelID = tabID - 1;

	vector< vector<int> > mat;
	sd->GetMakeTable()->GetRegionMask(regID,mat);

	SimuLineSet* tempSimuLineSet=sd->GetPointOfSimuLineSet(regID,levelID);

	RegionModifyDLG dlg;
	dlg.m_regID = regID;
	dlg.m_levelID = levelID;
	dlg.m_SlsPtr = tempSimuLineSet;
	dlg.m_showImageMask = cvCreateImage(cvGetSize(sd->GetSrcImage()),IPL_DEPTH_8U,3);
	sd->DrawRegionMask(regID,dlg.m_showImageMask);
	if (dlg.DoModal()!=IDOK)
	{
		return;
	}
	if (dlg.m_SlsPtr->stitchType==STITCH_ChaosVerticalCross
	 || dlg.m_SlsPtr->stitchType==STITCH_ChaosHorizontalCross
	 || dlg.m_SlsPtr->stitchType==STITCH_ChaosVectorFieldCross)
	{
		sd->DrawSimuLinesInChaosRegion(mat,dlg.m_SlsPtr->lineSet,*((ChaosStitch*)(dlg.m_SlsPtr->stitchPoint)));
	}
	else if (dlg.m_SlsPtr->stitchType==STITCH_OrderlessCross)
	{
		sd->DrawSimuLinesInOrderlessRegion(mat,dlg.m_SlsPtr->lineSet,*((OrderlessStitch*)(dlg.m_SlsPtr->stitchPoint)));
	}

	sd->DrawDisplayImage();
	sd->DrawLevelImage(levelID);
	
	MainFrame* tempFrame = (MainFrame*)AfxGetMainWnd();
	CMagicCabsineRightView *tempRightView = (CMagicCabsineRightView*)tempFrame->m_WndSplitter.GetPane(0,1);
	CMagicCabsineDisplayView *tempDisplayView = (CMagicCabsineDisplayView *)tempRightView->getTabViewPoint(TABTYPE_SIMU_ALL,0);
	tempDisplayView->SetDisplayImage(sd->GetDisplayImage());

	SetDisplayImage(sd->GetSingleLevelImage(levelID));

	tempDisplayView->Invalidate(FALSE);
	this->Invalidate(FALSE);

	tempRightView->SetActiveView(tabID);

	CView::OnRButtonDblClk(nFlags, point);
}


void CMagicCabsineSimulateView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CMagicCabsineShowBaseView::OnPaint()

	if(displayImage==NULL)
	{
		return;
	}

	CDC* pDC =this->GetDC();
	
	CSize sizeTotal;
	// TODO: 计算此视图的合计大小
	int width = displayImage->width;
	int height = displayImage->height;
	sizeTotal.cx = width*showSize;
	sizeTotal.cy = height*showSize;
	SetScrollSizes(MM_TEXT, sizeTotal);

	CRect rectClient;
	CRect windowRect;
	GetClientRect(&rectClient);
	windowRect = rectClient;

	int XRoll = -GetScrollPos(SB_HORZ);
	int YRoll = -GetScrollPos(SB_VERT);
	rectClient.SetRect(XRoll,YRoll,sizeTotal.cx-1+XRoll,sizeTotal.cy-1+YRoll);


	showImage(pDC, displayImage, windowRect, showSize, rectClient.TopLeft());

}
