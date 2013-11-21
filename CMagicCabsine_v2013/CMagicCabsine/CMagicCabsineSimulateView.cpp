// CMagicCabsineSimulateView.cpp : ʵ���ļ�
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
	//��������ͼ��ͬ,����ͼ�е�displayImage��ʵ��highlightImage[0],����������ѭ����ͳһ�ͷ�
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


// CMagicCabsineSimulateView ��ͼ

void CMagicCabsineSimulateView::OnDraw(CDC* pDC)
{
 	CDocument* pDoc = GetDocument();
 	// TODO: �ڴ���ӻ��ƴ���
	

}


// CMagicCabsineSimulateView ���

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
	CDC MemDC; //���ȶ���һ����ʾ�豸����  
	CBitmap MemBitmap;//����һ��λͼ����  

	//���������Ļ��ʾ���ݵ��ڴ���ʾ�豸  
	MemDC.CreateCompatibleDC(NULL);  
	//��ʱ�����ܻ�ͼ����Ϊû�еط��� ^_^  
	//���潨��һ������Ļ��ʾ���ݵ�λͼ������λͼ�Ĵ�С������ô��ڵĴ�С  
	MemBitmap.CreateCompatibleBitmap(pdc,windowRect.Width(),windowRect.Height());  

	//��λͼѡ�뵽�ڴ���ʾ�豸��  
	//ֻ��ѡ����λͼ���ڴ���ʾ�豸���еط���ͼ������ָ����λͼ��  
	CBitmap *pOldBit=MemDC.SelectObject(&MemBitmap);  

	//���ñ���ɫ��λͼ����ɾ����������õ��ǰ�ɫ��Ϊ����  
	//��Ҳ�������Լ�Ӧ���õ���ɫ  
	MemDC.FillSolidRect(0,0,windowRect.Width(),windowRect.Height(),RGB(255,255,255));  

	//��ͼ
	showImage2(&MemDC, img, windowRect, showSize, top_left);

	//���ڴ��е�ͼ��������Ļ�Ͻ�����ʾ  
	pdc->BitBlt(0,0,windowRect.Width(),windowRect.Height(),&MemDC,0,0,SRCCOPY);  

	//��ͼ��ɺ������  
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
// 			//�����л�û����������,��ӽ�������
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
	//ֱ�Ӵ����������и��ƹ�����
	levelIndex=0;
	//��������ͼ��ͬ,����ͼ�е�displayImage��ʵ��highlightImage[0],����������ѭ����ͳһ�ͷ�
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

// CMagicCabsineSimulateView ��Ϣ�������


void CMagicCabsineSimulateView::OnLButtonDown(UINT nFlags, CPoint point)
{
	/*
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CMagicCabsineDoc* pDoc=(CMagicCabsineDoc*)GetDocument();
	if(pDoc->theProject->currentProcessType!=PROCESS_SIMULATED)
	{
		CView::OnLButtonDown(nFlags, point);
		return;//������ģ�⽻���Ĳ���
	}

	int height=displayImage->height;
	int width=displayImage->width;
	int xx=point.x;
	int yy=point.y;
	if(xx<0||xx>=width||yy<0||yy>=height)
	{
		//û����ͼƬ��Χ�ڵ��
		if(currentRegionImage>0)//��Ҫ����ʾͼƬ���»���ԭͼ
		{
			displayImage=highlightImage[0];
			currentRegionImage=0;
			this->Invalidate(FALSE);
		}
		CView::OnLButtonDown(nFlags, point);
		return;
	}

	//��������,ע��CPoint��CvPoint����Ĳ�ͬ
	
	CMagicCabsineSimulateData_Test *simulateData=(CMagicCabsineSimulateData_Test *)pDoc->theProject->GetSimulateData();
	int regionNum=simulateData->GetRegionNum(yy,xx);
	THREAD_TYPE tempType=simulateData->GetThreadType(regionNum,levelIndex);
	int regionArea=simulateData->GetRegionArea(regionNum,levelIndex);
	CvScalar regionColor=simulateData->GetMainColor(regionNum,levelIndex);
	int numOfThread=simulateData->GetNumOfThread(regionNum,levelIndex);

	//��ʾ���ұߵ���������
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
		str=CString("��������1");
	}
	else
	{
		str=CString("��������2");
	}
	mainFrame->m_wndProperties.m_wndPropList.GetProperty(0)->GetSubItem(6)->SetValue(str);
	str.Format("%d",numOfThread);
	mainFrame->m_wndProperties.m_wndPropList.GetProperty(0)->GetSubItem(7)->SetValue(str);

	//���յ�ѡ��������ʾͼƬ
	displayImage=highlightImage[regionNum];
	currentRegionImage=regionNum;
	this->Invalidate(FALSE);
	*/
	CMagicCabsineShowBaseView::OnLButtonDown(nFlags, point);
}

void CMagicCabsineSimulateView::OnRButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
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
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CMagicCabsineShowBaseView::OnPaint()

	if(displayImage==NULL)
	{
		return;
	}

	CDC* pDC =this->GetDC();
	
	CSize sizeTotal;
	// TODO: �������ͼ�ĺϼƴ�С
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
