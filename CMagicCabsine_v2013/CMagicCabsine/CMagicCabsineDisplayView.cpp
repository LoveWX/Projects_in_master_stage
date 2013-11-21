// CMagicCabsineDisplayView.cpp : ʵ���ļ�
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


// CMagicCabsineDisplayView ��ͼ

void CMagicCabsineDisplayView::OnDraw(CDC* pDC)
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
}


// CMagicCabsineDisplayView ���

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


// CMagicCabsineDisplayView ��Ϣ�������

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
	if(displayImage==NULL)//û��ͼƬ����ʾ,����Ҫ����
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
