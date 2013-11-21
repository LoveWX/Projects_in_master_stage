// ProjectImageNewDLG.cpp : 实现文件
//

#include "stdafx.h"
#include "CMagicCabsine.h"
#include "ProjectImageNewDLG.h"
#include "afxdialogex.h"


// ProjectImageNewDLG 对话框

IMPLEMENT_DYNAMIC(ProjectImageNewDLG, CDialogEx)

ProjectImageNewDLG::ProjectImageNewDLG(CWnd* pParent /*=NULL*/)
	: CDialogEx(ProjectImageNewDLG::IDD, pParent)
{

	m_ImageType_Group = 0;
}

ProjectImageNewDLG::~ProjectImageNewDLG()
{
}

void ProjectImageNewDLG::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON3, m_PathSelect);
	DDX_Control(pDX, IDC_EDIT1, m_SrcImagePath);
	DDX_Control(pDX, IDC_ImageShowBox, m_ImageShowBox);
	DDX_Radio(pDX, IDC_RADIO1, m_ImageType_Group);
	DDV_MinMaxInt(pDX, m_ImageType_Group, 0, 3);
}


BEGIN_MESSAGE_MAP(ProjectImageNewDLG, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON3, &ProjectImageNewDLG::OnClickedButton3)
	ON_BN_CLICKED(IDOK, &ProjectImageNewDLG::OnBnClickedOk)
END_MESSAGE_MAP()


// ProjectImageNewDLG 消息处理程序


void ProjectImageNewDLG::OnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	CFileDialog dlgFile(TRUE,_T("*.jpg"),NULL,OFN_FILEMUSTEXIST|OFN_PATHMUSTEXIST|OFN_HIDEREADONLY,
		_T("IMAGE FILES(*.bmp;*.jpg)|*.bmp;*.jpg|All Files(*.*)|*.*||"),NULL);
	CString tempPath=theApp.GetDefaultPath().c_str();
	tempPath+="ImageLibrary\\";
	dlgFile.m_ofn.lpstrInitialDir=tempPath;

	if(dlgFile.DoModal()!=IDOK)
		return;

	CRect rect;
	GetDlgItem(IDC_ImageShowBox)->GetWindowRect(&rect);

	CString filePath = dlgFile.GetPathName();
	IplImage *img1=cvLoadImage(filePath,1);
	if(img1!=NULL)
	{
		TheImage=cvCreateImage(cvSize(rect.Width(),rect.Height()),img1->depth,img1->nChannels);
		cvResize(img1,TheImage,CV_INTER_LINEAR);
		ShowImage(TheImage,IDC_ImageShowBox);
		cvReleaseImage(&TheImage);
	}

	m_SrcImagePath.SetWindowTextA(filePath);
	cvReleaseImage(&img1);
	img1=NULL;
}


void ProjectImageNewDLG::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	
	UpdateData(TRUE);
	m_SrcImagePath.GetWindowTextA(imagePath);//获取图像路径

	if(imagePath==CString(""))
	{
		MessageBox(CString("请选择图像路径"), CString("Warning"), MB_OK|MB_ICONWARNING);
		return;
	}

	if(m_ImageType_Group==0)
	{
		imageType=IMAGE_HUMAN;
	}
	else if (m_ImageType_Group==1)
	{
		imageType=IMAGE_SCENERY;
	}
	else if (m_ImageType_Group==2)
	{
		imageType=IMAGE_ANIMAL;
	}
	else
	{
		imageType=IMAGE_CUSTOM;
	}

	CDialogEx::OnOK();
}

void ProjectImageNewDLG::ResizeImage(IplImage* img)
{
	int w = img->width;
	int h = img->height;

	int max = (w>h)?w:h;

	float scale = (float)((float)max/256.0f);

	int nw = (int)(w/scale);
	int nh = (int)(h/scale);

	int tlx = (nw>nh)?0:(int)(256-nw)/2;
	int tly = (nw>nh)?(int)(256-nh)/2:0;

	cvSetImageROI(TheImage,cvRect(tlx,tly,nw,nh));

	cvResize(img,TheImage);

	cvResetImageROI(TheImage);
}

void ProjectImageNewDLG::ShowImage(IplImage* img,UINT ID)
{
	CDC* pDC = GetDlgItem(ID)->GetDC();

	HDC hDC = pDC->GetSafeHdc();

	CRect rect;
	GetDlgItem(ID)->GetClientRect(&rect);

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
}

CString ProjectImageNewDLG::getImagePath()
{
	return imagePath;
}

IMAGE_TYPE ProjectImageNewDLG::getImageType()
{
	return imageType;
}
