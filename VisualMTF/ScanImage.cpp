// ScanImage.cpp : implementation file
//

#include "stdafx.h"
#include "VisualMTF.h"
#include "ScanImage.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define CROSS_POINT_NUM 5
#define CROSS_CAPTURE_NUM 1
#define CAMERA_WIDTH 640
#define CAMERA_HEIGHT 480
#define COMBO_NUM 5
/////////////////////////////////////////////////////////////////////////////
// CScanImage dialog


CScanImage::CScanImage(CWnd* pParent /*=NULL*/)
	: CDialog(CScanImage::IDD, pParent)
{
	//{{AFX_DATA_INIT(CScanImage)
	m_nBoxHeight = 0;
	m_nBoxWidth = 0;
	m_nXPos = 0;
	m_nYPos = 0;
	m_sCombo1 = _T("");
	m_sCombo2 = _T("");
	//}}AFX_DATA_INIT
	bCameraActive=FALSE;
}


void CScanImage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CScanImage)
	DDX_Control(pDX, IDC_IMGAE, m_image);
	DDX_Text(pDX, IDC_EDIT1, m_nXPos);
	DDX_Text(pDX, IDC_EDIT2, m_nYPos);
	DDX_CBString(pDX, IDC_COMBO1, m_sCombo1);
	DDX_CBString(pDX, IDC_COMBO2, m_sCombo2);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CScanImage, CDialog)
	//{{AFX_MSG_MAP(CScanImage)
	ON_CBN_SELCHANGE(IDC_COMBO1, OnSelchangeCombo1)
	ON_CBN_SELCHANGE(IDC_COMBO2, OnSelchangeCombo2)
	ON_WM_PAINT()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScanImage message handlers

int CScanImage::power(int nInput)
{
	int temp=1;
	for(int i=0;i<nInput;i++)
		temp*=2;
	return temp;
}

void CScanImage::FindCenter(unsigned char *cInput,int& nXPos,int& nYPos,int nWidth,int nHeight)
{
	int i, j;
	nXPos=nYPos=0;
	int maxvalue=0;
	for(i=0;i<nHeight-1;i++)
	{
		for(j=0;j<=nWidth-1;j++)
		{
			if(*(cInput+i*nWidth+j)>maxvalue)
			{
				maxvalue=*(cInput+i*nWidth+j); 
				nXPos=j;
				nYPos=i;
			}
		}
	}
}

void CScanImage::DrawCross(int nWidth, int nHeight, int nXPos, int nYPos)
{
	CWnd* pWnd=GetDlgItem(IDC_IMAGE);
	CDC* pDC=pWnd->GetDC();
	
	int nHalfWidth=int(nWidth*0.5);
	int nHalfHeight=int(nHeight*0.5);
	CPoint CrossPoint1[CROSS_POINT_NUM];
	CPoint CrossPoint2[CROSS_POINT_NUM];
	CrossPoint1[4].x=CrossPoint1[0].x=CrossPoint1[3].x=nXPos-nHalfWidth;
	CrossPoint1[1].x=CrossPoint1[2].x=nXPos+nHalfWidth-1;
	CrossPoint1[4].y=CrossPoint1[0].y=CrossPoint1[1].y=nYPos-nHalfHeight;
	CrossPoint1[2].y=CrossPoint1[3].y=nYPos+nHalfHeight-1;
	
	CrossPoint2[4].x=CrossPoint2[0].x=CrossPoint2[3].x=nXPos-nHalfHeight;
	CrossPoint2[1].x=CrossPoint2[2].x=nXPos+nHalfHeight-1;
	CrossPoint2[4].y=CrossPoint2[0].y=CrossPoint2[1].y=nYPos-nHalfWidth;
	CrossPoint2[2].y=CrossPoint2[3].y=nYPos+nHalfWidth-1;

	
	CPen pen(PS_SOLID,1,RGB(240,120,0));
	CPen *pOldPen=pDC->SelectObject(&pen);
	pDC->Polyline(CrossPoint1,CROSS_POINT_NUM);
	pDC->Polyline(CrossPoint2,CROSS_POINT_NUM);
	pDC->SelectObject(pOldPen);
}

BOOL CScanImage::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	bWindowMoved=FALSE;
	pComboBox1=(CComboBox*)GetDlgItem(IDC_COMBO1);//初始化组合框类指针成员
	pComboBox2=(CComboBox*)GetDlgItem(IDC_COMBO2);//初始化组合框类指针成员

	CMainFrame* MainFramePoint=(CMainFrame*)((CFrameWnd*)AfxGetApp()->m_pMainWnd);
	hBoard=MainFramePoint->getHANDLEOK();//获得相机句柄
	lpLinear=MainFramePoint->getLPBYTEOK();//获得相机数据空间指针
	okSetToWndRect(hBoard,m_image);//设置相机输出对象
	if(!okCaptureTo(hBoard,SCREEN,0,0))//启动相机（连续拍摄模式）
		sprintf(cItemText,"Could not capture the camera image!");
	else
		bCameraActive=TRUE;//设置相机为工作状态
	

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CScanImage::OnSelchangeCombo1() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);//刷新控件
	int n_sCombo;
	n_sCombo=atoi(m_sCombo1);//获取当前控件字符串值并转化成整形数据
	
	CMainFrame* MainFramePoint=(CMainFrame*)((CFrameWnd*)AfxGetApp()->m_pMainWnd);
	*(MainFramePoint->getpStarHeight())=n_sCombo;

	m_nBoxHeight=n_sCombo;//赋该类值
			
	
	Invalidate();//刷新对话框
}

void CScanImage::OnSelchangeCombo2() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);//刷新控件
	int n_sCombo;
	n_sCombo=atoi(m_sCombo2);//获取当前控件字符串值并转化成整形数据
	
	CMainFrame* MainFramePoint=(CMainFrame*)((CFrameWnd*)AfxGetApp()->m_pMainWnd);
	*(MainFramePoint->getpStarWidth())=n_sCombo;

	m_nBoxWidth=n_sCombo;//赋该类值
			
	
	Invalidate();//刷新对话框
}

void CScanImage::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	int nWidth=m_nBoxWidth;
	int nHeight=m_nBoxHeight;
	int nXPos=m_nXPos;
	int nYPos=m_nYPos;
	DrawCross(nWidth,nHeight,nXPos,nYPos);//画十字叉

	// Do not call CDialog::OnPaint() for painting messages
}

void CScanImage::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	CMainFrame* MainFramePoint=(CMainFrame*)((CFrameWnd*)AfxGetApp()->m_pMainWnd);
	hBoard=MainFramePoint->getHANDLEOK();//获得相机句柄
	okStopCapture(hBoard);//停止连续采样
}

void CScanImage::OnButton1() 
{
	// TODO: Add your control notification handler code here
	okCaptureTo(hBoard,BUFFER,0,CROSS_CAPTURE_NUM);//采集一幅图像
	okGetCaptureStatus(hBoard,1);//等待采集完毕
	long lBitNumber=CAMERA_WIDTH*CAMERA_HEIGHT;//单幅图像数据所需空间大小
	cData=new unsigned char[lBitNumber]; //开辟自用图像数据区
	memcpy(cData, lpLinear, lBitNumber); //将BUFFER中数据拷贝到开辟的自由图像数据区
	int nCenterX,nCenterY;
	int nWidth=CAMERA_WIDTH;
	int nHeight=CAMERA_HEIGHT;
	
	FindCenter(cData,nCenterX,nCenterY,nWidth,nHeight);//在当前的图像数据中，寻找亮度极大值点（作为十字叉中心）
	delete cData;

	m_nXPos=nCenterX;
	m_nYPos=nCenterY;
	
	Invalidate();
}

void CScanImage::OnButton2() 
{
	// TODO: Add your control notification handler code here
	okCaptureTo(hBoard,BUFFER,0,CROSS_CAPTURE_NUM);//采集一幅图像
	okGetCaptureStatus(hBoard,1);//等待采集结束
	int nWidth=CAMERA_WIDTH;
	int nHeight=CAMERA_HEIGHT;
	long lBitNumber=nWidth*nHeight;//单幅图像所需数据空间大小
	BITMAPFILEHEADER fhead;
	LPBITMAPINFOHEADER lpDIBInfo;
	BYTE *lpBmp;

	eDIB=GlobalAlloc(GMEM_MOVEABLE, sizeof(BITMAPINFOHEADER)+256*sizeof(RGBQUAD)+sizeof(unsigned char)*lBitNumber);//开辟位图空间
	lpBmp=(BYTE*)GlobalLock(eDIB);
	//以下写文件头	
	lpDIBInfo=(LPBITMAPINFOHEADER)lpBmp;
	lpDIBInfo->biSize = sizeof(BITMAPINFOHEADER);
	lpDIBInfo->biWidth = nWidth;
	lpDIBInfo->biHeight = nHeight;
	lpDIBInfo->biPlanes = 1;
	lpDIBInfo->biBitCount = 8;
	lpDIBInfo->biCompression = 0;
	lpDIBInfo->biSizeImage = (lpDIBInfo->biWidth)*(lpDIBInfo->biHeight);
	lpDIBInfo->biXPelsPerMeter = 0;
	lpDIBInfo->biYPelsPerMeter = 0;
	lpDIBInfo->biClrUsed = 0;
	lpDIBInfo->biClrImportant = 0;
	//以下写色盘
	RGBQUAD *bmiColors;
	bmiColors = (RGBQUAD*)(lpBmp+sizeof(BITMAPINFOHEADER));
	for(int i=0;i<256;i++,bmiColors++)
	{
		bmiColors->rgbBlue=i;
		bmiColors->rgbGreen=i;
		bmiColors->rgbRed=i;
		bmiColors->rgbReserved=0;
	}
	//以下写图像数据
	BYTE *lpBmpValue;
	for(i=0;i<nHeight;i++)
	{
		for(int j=0;j<nWidth;j++)
		{
			lpBmpValue=lpBmp+sizeof(BITMAPINFOHEADER)+256*sizeof(RGBQUAD)+
				+ (nHeight-i-1)*nWidth+j;
			*lpBmpValue=*(lpLinear+i*nWidth+j);
			
		}
	}
	
	//写文件头
	//lpDIBInfo=(LPBITMAPINFOHEADER)lpBmp;
	fhead.bfType=256*'M'+'B';
	fhead.bfSize=sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)
				+256*sizeof(RGBQUAD)+lBitNumber*sizeof(unsigned char);
	fhead.bfReserved1=0;
	fhead.bfReserved2=0;
	fhead.bfOffBits=sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+256*sizeof(RGBQUAD);
	
	//保存数据
	CFileDialog browsefile(FALSE, "bmp", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, 
		"Windows Bitmap Files(*.BMP)|*.bmp||", NULL);
	CString FileName;
	FILE *fp;
	if (browsefile.DoModal()==IDOK) 
	{
		FileName=browsefile.GetPathName();
		fp=fopen((LPCTSTR)FileName, "wb");
		fwrite(&fhead,1,sizeof(BITMAPFILEHEADER),fp);
		fwrite(lpBmp,1,sizeof(BITMAPINFOHEADER)+256*sizeof(RGBQUAD)
			+lBitNumber*sizeof(unsigned char),fp);
		fclose(fp);
	}

}



void CScanImage::OnButton3() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);//获得十字叉新位置与新尺寸
	Invalidate();//刷新视图
}

LRESULT CScanImage::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(message==WM_MOVING)
		if(bCameraActive)
		{
			okStopCapture(hBoard);//暂停采样
			bWindowMoved=TRUE;
		}

	return CDialog::DefWindowProc(message, wParam, lParam);
}

void CScanImage::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if(bCameraActive&&bWindowMoved==TRUE)
		{
			okSetToWndRect(hBoard,m_image);//设置Picture控件为目标体
			okCaptureTo(hBoard,SCREEN,0,0);//恢复连续采样
			bWindowMoved=FALSE;
		}
	CDialog::OnLButtonDown(nFlags, point);
}

void CScanImage::OnMove(int x, int y) 
{
	CDialog::OnMove(x, y);
	if(bCameraActive&&bWindowMoved)
	{
		okSetToWndRect(hBoard,m_image);//设置Picture控件为目标体
		okCaptureTo(hBoard,SCREEN,0,0);//恢复连续采样
	}
	// TODO: Add your message handler code here
	
}
