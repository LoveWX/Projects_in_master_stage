// CMagicCabsineDisplayView.cpp : 实现文件
//

#include "stdafx.h"
#include "CMagicCabsine.h"
#include "CMagicCabsineDisplayView.h"



// CMagicCabsineDisplayView

IMPLEMENT_DYNCREATE(CMagicCabsineDisplayView, CMagicCabsineShowBaseView)

CMagicCabsineDisplayView::CMagicCabsineDisplayView()
{
	displayImage=NULL;
// 	blankImage=NULL;
}

CMagicCabsineDisplayView::~CMagicCabsineDisplayView()
{
	if(displayImage!=NULL)
	{
		cvReleaseImage(&displayImage);
		displayImage=NULL;
	}
// 	if(blankImage!=NULL)
// 	{
// 		cvReleaseImage(&blankImage);
// 		blankImage=NULL;
// 	}
}

BEGIN_MESSAGE_MAP(CMagicCabsineDisplayView, CMagicCabsineShowBaseView)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CMagicCabsineDisplayView 绘图

void CMagicCabsineDisplayView::OnDraw(CDC* pDC)
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
}


// CMagicCabsineDisplayView 诊断

#ifdef _DEBUG
void CMagicCabsineDisplayView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CMagicCabsineDisplayView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CMagicCabsineDisplayView 消息处理程序

void CMagicCabsineDisplayView::SetDisplayImage(IplImage *tempImage)
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
}

IplImage* CMagicCabsineDisplayView::GetDisplayImage()
{
	return displayImage;
}

void CMagicCabsineDisplayView::ClearDisplayImage()
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

void CMagicCabsineDisplayView::ShowImage(CDC* pDC,const IplImage* img,CRect windowRect,double showSize,CPoint &top_left)
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

double CMagicCabsineDisplayView::showImage2(CDC* pdc,const IplImage* img,CRect windowRect,double showSize,CPoint &top_left)
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

void CMagicCabsineDisplayView::CloseView()
{
	if(displayImage!=NULL)
	{
		cvReleaseImage(&displayImage);
		displayImage=NULL;
	}
}


void CMagicCabsineDisplayView::OnPaint()
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


	ShowImage(pDC, displayImage, windowRect, showSize, rectClient.TopLeft());

}


BOOL CMagicCabsineDisplayView::OnEraseBkgnd(CDC* pDC)  
{ 
	CRect rect; 
	CBrush brush; 
	brush.CreateSolidBrush(RGB(255,255,255)); 
	pDC->GetClipBox(rect); 
	pDC->FillRect(rect, &brush); 
	return true; 
} 
