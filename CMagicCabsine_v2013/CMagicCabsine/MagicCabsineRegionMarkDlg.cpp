// MagicCabsineRegionMarkDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CMagicCabsine.h"
#include "MagicCabsineRegionMarkDlg.h"
#include "afxdialogex.h"
#include <highgui.h>

// CMagicCabsineRegionMarkDlg 对话框

IMPLEMENT_DYNAMIC(CMagicCabsineRegionMarkDlg, CDialogEx)

CMagicCabsineRegionMarkDlg::CMagicCabsineRegionMarkDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMagicCabsineRegionMarkDlg::IDD, pParent)
{
	splitData = NULL;
	x=0;
	y=0;
	color_R = 0;
	color_G = 0;
	color_B = 0;
	isFront = FALSE;
}

CMagicCabsineRegionMarkDlg::~CMagicCabsineRegionMarkDlg()
{
	cvReleaseImage(&showRegionImg);
}

void CMagicCabsineRegionMarkDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_MARK_FOREBACK, m_selFrontBack);
//	DDX_Control(pDX, IDC_REGIONMARK_MAINCOLOR, m_showMainColor);
	//  DDX_Control(pDX, IDC_REGIONMARK_SHOWREGION, m_showRegion);
	DDX_Control(pDX, IDC_SLIDER_MARKREGION_COLOR_G, m_changeColorG);
	DDX_Control(pDX, IDC_SLIDER_MARKREGION_COLOR_B, m_changeColorB);
	DDX_Control(pDX, IDC_SLIDER_MARKREGION_COLOR_R, m_changeColorR);
	DDX_Control(pDX, IDC_EDIT_REGIONMARK_G, m_showSize_G);
	DDX_Control(pDX, IDC_EDIT_REGIONMARK_B, m_showSize_B);
	DDX_Control(pDX, IDC_EDIT_REGIONMARK_R, m_showSize_R);
}


BEGIN_MESSAGE_MAP(CMagicCabsineRegionMarkDlg, CDialogEx)
	ON_WM_PAINT()
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_MARKREGION_COLOR_R, &CMagicCabsineRegionMarkDlg::OnCustomdrawSliderMarkregionColorR)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_MARKREGION_COLOR_G, &CMagicCabsineRegionMarkDlg::OnCustomdrawSliderMarkregionColorG)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_MARKREGION_COLOR_B, &CMagicCabsineRegionMarkDlg::OnCustomdrawSliderMarkregionColorB)
	ON_BN_CLICKED(IDOK, &CMagicCabsineRegionMarkDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CMagicCabsineRegionMarkDlg 消息处理程序


BOOL CMagicCabsineRegionMarkDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_selFrontBack.InsertString(0, CString("前景"));
	m_selFrontBack.InsertString(1, CString("背景"));

	CString str;
	str.Format("%d", color_R);
	m_showSize_R.SetWindowTextA(str);
	str.Format("%d", color_G);
	m_showSize_G.SetWindowTextA(str);
	str.Format("%d", color_B);
	m_showSize_B.SetWindowTextA(str);
	
	if(isFront == TRUE)
	{
		m_selFrontBack.SetCurSel(0);
	}
	else
	{
		m_selFrontBack.SetCurSel(1);
	}

	m_changeColorR.SetRange(0, 255);
	m_changeColorG.SetRange(0, 255);
	m_changeColorB.SetRange(0, 255);

	m_changeColorR.SetPos(color_R);
	m_changeColorG.SetPos(color_G);
	m_changeColorB.SetPos(color_B);

	m_changeColorR.SetLineSize(16);
	m_changeColorG.SetLineSize(16);
	m_changeColorB.SetLineSize(16);

	m_changeColorR.SetTicFreq(10);
	m_changeColorG.SetTicFreq(10);
	m_changeColorB.SetTicFreq(10);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


INT_PTR CMagicCabsineRegionMarkDlg::DoModal()
{
	// TODO: 在此添加专用代码和/或调用基类
	initialShowData();

	return CDialogEx::DoModal();
}


void CMagicCabsineRegionMarkDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnPaint()
	showSelectedRegion();
	showMainColor();
}


void CMagicCabsineRegionMarkDlg::showSelectedRegion()
{
	CRect rect;
	GetDlgItem(IDC_REGIONMARK_SHOWREGION)->GetClientRect(&rect);

	IplImage* img = cvCreateImage(cvSize(rect.Width(),rect.Height()),showRegionImg->depth,showRegionImg->nChannels);
	cvResize(showRegionImg,img,CV_INTER_LINEAR);

	CDC* pDC = GetDlgItem(IDC_REGIONMARK_SHOWREGION)->GetDC();

	HDC hDC = pDC->GetSafeHdc();

	int rw=rect.right-rect.left;
	int rh=rect.bottom-rect.top;

	int iw=img->width;
	int ih=img->height;

	int tx=(int)(rw-iw)/2;
	int ty=(int)(rh-ih)/2;
	SetRect(rect,tx,ty,tx+iw,ty+ih);
	CvvImage cimg;
	cimg.CopyOf(img);

	cimg.DrawToHDC(hDC,&rect);
	ReleaseDC(pDC);

	cvReleaseImage(&img);
}

//显示主色调
void CMagicCabsineRegionMarkDlg::showMainColor()
{
	CDC *pDC = GetDlgItem(IDC_REGIONMARK_MAINCOLOR)->GetDC();
	CRect rct;
	GetDlgItem(IDC_REGIONMARK_MAINCOLOR)->GetWindowRect(&rct);
	CBrush brs;
	brs.CreateSolidBrush(RGB(color_R,color_G,color_B));
	CRect picrct;
	picrct.top = 0;
	picrct.left = 0;
	picrct.bottom = rct.Height();
	picrct.right = rct.Width();
	pDC->FillRect(&picrct, &brs);

	ReleaseDC(pDC);
}

void CMagicCabsineRegionMarkDlg::initialShowData()
{
	showRegionImg = cvCloneImage(splitData->GetBoundaryImage());
	int width = showRegionImg->width;
	int height = showRegionImg->height;
	const vector< vector<int> > &tempSplitMatrix = splitData->getSplitMat();
	tempRegionID = tempSplitMatrix[y][x];
	const vector< vector<int> > & tempMask = splitData->getMaskMat()[tempRegionID];
	splitData->getForeBackData(frontIDs, backIDs);
	if (frontIDs.find(tempRegionID)!=frontIDs.end())
	{
		isFront = TRUE;
	}
	IplImage* tempMainColor = splitData->GetDisplayImage();
	bool isGetMainColor = false;

	long int tempR = 0;
	long int tempG = 0;
	long int tempB = 0;
	int regionPixelNum = 0;
	CvScalar tempColor;
	for (int i=0; i<height; i++)
	{
		for (int j=0; j<width; j++)
		{
			if (tempMask[i][j] == 0)
			{
				cvSet2D(showRegionImg, i, j, CV_RGB(255,255,255));
			}
			else if (!isGetMainColor)
			{
				tempColor = cvGet2D(tempMainColor, i, j);
				color_R = (int)tempColor.val[2];
				color_G = (int)tempColor.val[1];
				color_B = (int)tempColor.val[0];
				isGetMainColor = true;
			}
		}
	}

	//cvSaveImage("d:\\tempImg.jpg", showRegionImg);
}

void CMagicCabsineRegionMarkDlg::OnCustomdrawSliderMarkregionColorR(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	color_R=m_changeColorR.GetPos();
	UpdateData(FALSE);
	CString str;
	str.Format("%d", color_R);
	m_showSize_R.SetWindowTextA(str);
	showMainColor();

	*pResult = 0;
}


void CMagicCabsineRegionMarkDlg::OnCustomdrawSliderMarkregionColorG(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	color_G=m_changeColorG.GetPos();
	UpdateData(FALSE);
	CString str;
	str.Format("%d", color_G);
	m_showSize_G.SetWindowTextA(str);
	showMainColor();

	*pResult = 0;
}


void CMagicCabsineRegionMarkDlg::OnCustomdrawSliderMarkregionColorB(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	color_B=m_changeColorB.GetPos();
	UpdateData(FALSE);
	CString str;
	str.Format("%d", color_B);
	m_showSize_G.SetWindowTextA(str);
	showMainColor();

	*pResult = 0;
}


void CMagicCabsineRegionMarkDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_selFrontBack.GetCurSel() == 0)
	{
		splitData->setRegionFrontOrBack(tempRegionID, TRUE);
	}
	else
	{
		splitData->setRegionFrontOrBack(tempRegionID, FALSE);
	}
	splitData->rePaintDisplayImg(tempRegionID, color_R, color_G, color_B);


	CDialogEx::OnOK();
}
