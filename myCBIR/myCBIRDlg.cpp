// myCBIRDlg.cpp : implementation file
//

#include "stdafx.h"
#include "myCBIR.h"
#include "myCBIRDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyCBIRDlg dialog

CMyCBIRDlg::CMyCBIRDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMyCBIRDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMyCBIRDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CMyCBIRDlg::~CMyCBIRDlg()
{
	if(srcImage!=NULL)
	{
		cvReleaseImage(&srcImage);
		srcImage=NULL;
	}
	int i;
	for(i=0;i<numOfPoolPictures;i++)
	{
		if(histOfPoolPictures[i]!=NULL)
		{
			cvReleaseHist(&histOfPoolPictures[i]);
			histOfPoolPictures[i]=NULL;
		}
	}
	if(histOfSrcPicture!=NULL)
	{
		cvReleaseHist(&histOfSrcPicture);
		histOfSrcPicture=NULL;
	}
}

void CMyCBIRDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMyCBIRDlg)
	DDX_Control(pDX, IDC_STATIC_sizeOfPool, m_sizeOfPool);
	DDX_Control(pDX, IDC_STATIC_calcedPic, m_calcedPic);
	DDX_Control(pDX, IDC_STATIC_RES03, m_res03);
	DDX_Control(pDX, IDC_STATIC_RES20, m_res20);
	DDX_Control(pDX, IDC_STATIC_RES19, m_res19);
	DDX_Control(pDX, IDC_STATIC_RES18, m_res18);
	DDX_Control(pDX, IDC_STATIC_RES17, m_res17);
	DDX_Control(pDX, IDC_STATIC_RES16, m_res16);
	DDX_Control(pDX, IDC_STATIC_RES15, m_res15);
	DDX_Control(pDX, IDC_STATIC_RES14, m_res14);
	DDX_Control(pDX, IDC_STATIC_RES13, m_res13);
	DDX_Control(pDX, IDC_STATIC_RES12, m_res12);
	DDX_Control(pDX, IDC_STATIC_RES11, m_res11);
	DDX_Control(pDX, IDC_STATIC_RES10, m_res10);
	DDX_Control(pDX, IDC_STATIC_RES09, m_res09);
	DDX_Control(pDX, IDC_STATIC_RES08, m_res08);
	DDX_Control(pDX, IDC_STATIC_RES07, m_res07);
	DDX_Control(pDX, IDC_STATIC_RES06, m_res06);
	DDX_Control(pDX, IDC_STATIC_RES05, m_res05);
	DDX_Control(pDX, IDC_STATIC_RES04, m_res04);
	DDX_Control(pDX, IDC_STATIC_RES02, m_res02);
	DDX_Control(pDX, IDC_STATIC_RES01, m_res01);
	DDX_Control(pDX, IDC_EDIT1, m_srcImagePath);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMyCBIRDlg, CDialog)
	//{{AFX_MSG_MAP(CMyCBIRDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyCBIRDlg message handlers

BOOL CMyCBIRDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	isCalcPoolPictures=false;
	char strBuffer[20];
	sprintf(strBuffer,"/ %d",numOfPoolPictures);
	m_sizeOfPool.SetWindowText(strBuffer);
	srcImage=NULL;
	histOfSrcPicture=NULL;
	int i;
	for(i=0;i<numOfPoolPictures;i++)
	{
		histOfPoolPictures[i]=NULL;
	}

	strcpy(defaultPath,_pgmptr);
	for(i=strlen(defaultPath)-1;i>=0&&defaultPath[i]!='\\';i--);
	for(i--;i>=0&&defaultPath[i]!='\\';i--);
	defaultPath[i+1]='\0';
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMyCBIRDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMyCBIRDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMyCBIRDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

bool cmp(const DistanceOfPicture &a,const DistanceOfPicture &b)
{
	return a.similarity>b.similarity;
}

void CMyCBIRDlg::OnButton1() 
{
	// TODO: Add your control notification handler code here
	CFileDialog dlgFile(TRUE,_T("*.bmp"),NULL,OFN_FILEMUSTEXIST|OFN_PATHMUSTEXIST|OFN_HIDEREADONLY,
		_T("IMAGE FILES(*.bmp;*.jpg)|*.bmp;*.jpg|All Files(*.*)|*.*||"),NULL);
	if(dlgFile.DoModal()!=IDOK)
		return;

	CString filePath = dlgFile.GetPathName();
	if(filePath==CString(""))
	{
		MessageBox("请选择图片路径","图片选择");
		return;
	}

	srcImage=cvLoadImage(filePath,1);
	if(srcImage==NULL)
	{
		MessageBox(CString("图片")+filePath+CString("无法打开."),"图片选择");
		return;
	}
	ShowImageInBox(srcImage,IDC_srcImageShowBox);
	
	m_srcImagePath.SetWindowTextA(filePath);

	//计算备选图片直方图
	if(!isCalcPoolPictures)
	{
		CalcHistOfPoolPictures();
		isCalcPoolPictures=true;
	}
}

void CMyCBIRDlg::ShowImageInBox(IplImage* img,UINT ID)
{
	if(img==NULL)
		return;

	CRect rect;
	GetDlgItem(ID)->GetWindowRect(&rect);

	IplImage *tempImage=cvCreateImage(cvSize(rect.Width(),rect.Height()),img->depth,img->nChannels);
	cvResize(img,tempImage,CV_INTER_LINEAR);
	ShowImage(tempImage,ID);
	cvReleaseImage(&tempImage);
	tempImage=NULL;
}

void CMyCBIRDlg::ShowImage(IplImage* img,UINT ID)
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

void CMyCBIRDlg::myCalcHist(CvHistogram * &theHist,IplImage *srcImage)
{
	IplImage *hsvImage=cvCreateImage(cvGetSize(srcImage),8,3);
	cvCvtColor(srcImage,hsvImage,CV_BGR2HSV);
	
	IplImage *h_plane=cvCreateImage(cvGetSize(srcImage),8,1);
	IplImage *s_plane=cvCreateImage(cvGetSize(srcImage),8,1);
	IplImage *v_plane=cvCreateImage(cvGetSize(srcImage),8,1);
	IplImage *planes[]={h_plane,s_plane,v_plane};
	cvCvtPixToPlane(hsvImage,h_plane,s_plane,v_plane,0);
	
	{
		int hist_size[]={h_bins,s_bins,v_bins};
		float h_ranges[]={0,max_h};
		float s_ranges[]={0,max_s};
		float v_ranges[]={0,max_v};
		float *ranges[]={h_ranges,s_ranges,v_ranges};
		theHist=cvCreateHist(3,hist_size,CV_HIST_ARRAY,ranges,1);
	}
	
	cvCalcHist(planes,theHist,0,0);
	cvNormalizeHist(theHist,1.0);
	
	cvReleaseImage(&hsvImage);
	cvReleaseImage(&h_plane);
	cvReleaseImage(&s_plane);
	cvReleaseImage(&v_plane);
}

void CMyCBIRDlg::CalcHistOfPoolPictures()
{
	IplImage *img=NULL;

	char pathOfPictures[325];
	strcpy(pathOfPictures,defaultPath);
	int i=strlen(defaultPath);
	pathOfPictures[i]='p';
	pathOfPictures[i+1]='o';
	pathOfPictures[i+2]='o';
	pathOfPictures[i+3]='l';
	pathOfPictures[i+4]='\\';
	pathOfPictures[i+5]='\0';
	char *pchar=pathOfPictures+i+5;
	char strBuffer[20];
	for(i=0;i<numOfPoolPictures;i++)
	{
		sprintf(pchar,"%d.jpg",i+1);
		img=cvLoadImage(pathOfPictures,1);
		if(img==NULL)
		{
			continue;
		}
		myCalcHist(histOfPoolPictures[i],img);
		cvReleaseImage(&img);

		sprintf(strBuffer,"%d",i+1);
		m_calcedPic.SetWindowText(strBuffer);
	}
}

void CMyCBIRDlg::OnOK() 
{
	// TODO: Add extra validation here

	if(srcImage==NULL)
	{
		CString filePath;
		m_srcImagePath.GetWindowText(filePath);
		if(filePath==CString(""))
		{
			MessageBox("请选择图片路径","图片选择",MB_ICONWARNING);
			return;
		}
		
		srcImage=cvLoadImage(filePath,1);
		if(srcImage==NULL)
		{
			MessageBox(CString("图片")+filePath+CString("无法打开."),"图片选择",MB_ICONWARNING);
			return;
		}
	}

	if(!isCalcPoolPictures)
	{
		CalcHistOfPoolPictures();
		isCalcPoolPictures=true;
	}

	const int numOfShowImage=20;

	if(histOfSrcPicture!=NULL)
	{
		cvReleaseHist(&histOfSrcPicture);
		histOfSrcPicture=NULL;
	}
	myCalcHist(histOfSrcPicture,srcImage);

	int i;
	for(i=0;i<numOfPoolPictures;i++)
	{
		resultOfEachPicture[i].index=i+1;
		resultOfEachPicture[i].similarity=cvCompareHist(histOfSrcPicture,histOfPoolPictures[i],CV_COMP_INTERSECT);
	}
	sort(&resultOfEachPicture[0],&resultOfEachPicture[numOfPoolPictures],cmp);

	IplImage *retImage[numOfShowImage];
	CString retText[numOfShowImage];
	char pathOfPictures[325];
	strcpy(pathOfPictures,defaultPath);
	i=strlen(defaultPath);
	pathOfPictures[i]='p';
	pathOfPictures[i+1]='o';
	pathOfPictures[i+2]='o';
	pathOfPictures[i+3]='l';
	pathOfPictures[i+4]='\\';
	pathOfPictures[i+5]='\0';
	char *pchar=pathOfPictures+i+5;
	char strbuffer[50];

	for(i=0;i<numOfShowImage;i++)
	{
		sprintf(pchar,"%d.jpg",resultOfEachPicture[i].index);
		retImage[i]=cvLoadImage(pathOfPictures,1);
		sprintf(strbuffer,"(%d) %s %.5lf",i+1,pchar,resultOfEachPicture[i].similarity);
		retText[i]=strbuffer;
	}

	ShowImageInBox(srcImage,IDC_srcImageShowBox);
	ShowImageInBox(retImage[0],IDC_ShowBox01);
	ShowImageInBox(retImage[1],IDC_ShowBox02);
	ShowImageInBox(retImage[2],IDC_ShowBox03);
	ShowImageInBox(retImage[3],IDC_ShowBox04);
	ShowImageInBox(retImage[4],IDC_ShowBox05);
	ShowImageInBox(retImage[5],IDC_ShowBox06);
	ShowImageInBox(retImage[6],IDC_ShowBox07);
	ShowImageInBox(retImage[7],IDC_ShowBox08);
	ShowImageInBox(retImage[8],IDC_ShowBox09);
	ShowImageInBox(retImage[9],IDC_ShowBox10);
	ShowImageInBox(retImage[10],IDC_ShowBox11);
	ShowImageInBox(retImage[11],IDC_ShowBox12);
	ShowImageInBox(retImage[12],IDC_ShowBox13);
	ShowImageInBox(retImage[13],IDC_ShowBox14);
	ShowImageInBox(retImage[14],IDC_ShowBox15);
	ShowImageInBox(retImage[15],IDC_ShowBox16);
	ShowImageInBox(retImage[16],IDC_ShowBox17);
	ShowImageInBox(retImage[17],IDC_ShowBox18);
	ShowImageInBox(retImage[18],IDC_ShowBox19);
	ShowImageInBox(retImage[19],IDC_ShowBox20);

	m_res01.SetWindowText(retText[0]);
	m_res02.SetWindowText(retText[1]);
	m_res03.SetWindowText(retText[2]);
	m_res04.SetWindowText(retText[3]);
	m_res05.SetWindowText(retText[4]);
	m_res06.SetWindowText(retText[5]);
	m_res07.SetWindowText(retText[6]);
	m_res08.SetWindowText(retText[7]);
	m_res09.SetWindowText(retText[8]);
	m_res10.SetWindowText(retText[9]);
	m_res11.SetWindowText(retText[10]);
	m_res12.SetWindowText(retText[11]);
	m_res13.SetWindowText(retText[12]);
	m_res14.SetWindowText(retText[13]);
	m_res15.SetWindowText(retText[14]);
	m_res16.SetWindowText(retText[15]);
	m_res17.SetWindowText(retText[16]);
	m_res18.SetWindowText(retText[17]);
	m_res19.SetWindowText(retText[18]);
	m_res20.SetWindowText(retText[19]);

	for(i=0;i<numOfShowImage;i++)
	{
		cvReleaseImage(&retImage[i]);
		retImage[i]=NULL;
	}

// 	CDialog::OnOK();
}
