// RegionModifyDLG.cpp : 实现文件
//

#include "stdafx.h"
#include "CMagicCabsine.h"
#include "RegionModifyDLG.h"
#include "afxdialogex.h"


// RegionModifyDLG 对话框

IMPLEMENT_DYNAMIC(RegionModifyDLG, CDialogEx)

RegionModifyDLG::RegionModifyDLG(CWnd* pParent /*=NULL*/)
	: CDialogEx(RegionModifyDLG::IDD, pParent)
{
	RM_SLD_UP_DSY = 20;
	RM_SLD_UP_LEN = 20;
	RM_SLD_UP_CHA = 10;

	m_SlsPtr = NULL;

	m_showImageMask = NULL;
	m_showImageStitch = NULL;
}

RegionModifyDLG::~RegionModifyDLG()
{
}
void RegionModifyDLG::InitCombox()
{
	m_comboType.Clear();
	m_comboType.AddString("竖交叉");
	m_comboType.AddString("横交叉");
	m_comboType.AddString("矢量场交叉");
	m_comboType.AddString("小乱针");

	vector<ChaosStitch> tempChaosStitch;
	vector<OrderlessStitch> tempOrderlessStitch;
	m_stitchlib.GetOtherChaosStitch(tempChaosStitch);
	m_stitchlib.GetOtherOrderlessStitch(tempOrderlessStitch);

	for (int i=0;i<tempChaosStitch.size();i++)
	{
		CString str;
		str.Format("%s",tempChaosStitch[i].stitchName.c_str());
		m_comboType.AddString(str);
	}
	for (int i=0;i<tempOrderlessStitch.size();i++)
	{
		CString str;
		str.Format("%s",tempOrderlessStitch[i].stitchName.c_str());
		m_comboType.AddString(str);
	}
	int sel = 0;
	m_type = m_SlsPtr->stitchType;
	switch (m_type)
	{
	case STITCH_ChaosVerticalCross:
		sel = 0;
		break;
	case STITCH_ChaosHorizontalCross:
		sel = 1;
		break;
	case STITCH_ChaosVectorFieldCross:
		sel = 2;
		break;
	case STITCH_OrderlessCross:
		sel  = 3;
		break;
	case STITCH_Other:
		sel = 0;
		break;
	}
	m_comboType.SetCurSel(sel);
}
void RegionModifyDLG::InitSlider()
{
	m_sliderDensity.SetRange(0,RM_SLD_UP_DSY);
	m_sliderLength.SetRange(0,RM_SLD_UP_LEN);
	m_sliderChaos.SetRange(0,RM_SLD_UP_CHA);
}
void RegionModifyDLG::InitTPV()
{
	if (m_SlsPtr != NULL)
	{
		if (m_SlsPtr->stitchType==STITCH_ChaosHorizontalCross 
			|| m_SlsPtr->stitchType==STITCH_ChaosVectorFieldCross
			|| m_SlsPtr->stitchType==STITCH_ChaosVerticalCross)
		{
			ChaosStitch* cs = (ChaosStitch*)(m_SlsPtr->stitchPoint);
			m_tpv.density = cs->density;
			m_tpv.length = cs->length;
			m_tpv.chaos = cs->chaosExtent;
			m_tpv.theta = cs->theta;
			m_tpv.beta = cs->beta;
		}
		else if (m_SlsPtr->stitchType==STITCH_OrderlessCross)
		{
			OrderlessStitch* os = (OrderlessStitch*)(m_SlsPtr->stitchPoint);
			m_tpv.density = os->density;
			m_tpv.length = os->length;
			m_tpv.chaos = os->chaosExtent;
			m_tpv.theta = os->theta;
			m_tpv.beta = os->beta;
		}
	}
}
void RegionModifyDLG::UpdateSlider(TempParaVal tpv)
{
	ParaBound PB;
	int pos = 0;
	pos =(int) (RM_SLD_UP_DSY*(tpv.density-PB.DensityMin)/(PB.DensityMax-PB.DensityMin));
	m_sliderDensity.SetPos(pos);
	pos =(int) (RM_SLD_UP_LEN*(tpv.length-PB.LengthMin)/(PB.LengthMax-PB.LengthMin));
	m_sliderLength.SetPos(pos);
	pos =(int) (RM_SLD_UP_CHA*(tpv.chaos-PB.ChaosMin)/(PB.ChaosMax-PB.ChaosMin));
	m_sliderChaos.SetPos(pos);
}
void RegionModifyDLG::UpdateEdit(TempParaVal tpv)
{
	CString str;
	str.Format("%.2f",tpv.density);
	m_editDensity.SetWindowText(str);
	str.Format("%.2f",tpv.length);
	m_editLength.SetWindowText(str);
	str.Format("%.2f",tpv.chaos);
	m_editChaos.SetWindowText(str);
}
void RegionModifyDLG::GetParaFromSlider(TempParaVal& tpv)
{
	ParaBound PB;
	int pos=0;
	pos = m_sliderDensity.GetPos();
	tpv.density = pos*(PB.DensityMax-PB.DensityMin)/RM_SLD_UP_DSY + PB.DensityMin;
	pos = m_sliderLength.GetPos();
	tpv.length = pos*(PB.LengthMax-PB.LengthMin)/RM_SLD_UP_LEN + PB.LengthMin;
	pos = m_sliderChaos.GetPos();
	tpv.chaos = pos*(PB.ChaosMax-PB.ChaosMin)/RM_SLD_UP_CHA + PB.ChaosMin;
}
void RegionModifyDLG::ShowMaskImage()
{
	CvScalar tempColor=m_SlsPtr->mainColor;
	int R = (int)tempColor.val[2];
	int G = (int)tempColor.val[1];
	int B = (int)tempColor.val[0];
	CDC *pDC = GetDlgItem(IDC_STATIC_MAINCOLOR)->GetDC();
	CRect rct;
	GetDlgItem(IDC_STATIC_MAINCOLOR)->GetWindowRect(&rct);
	CBrush brs;
	brs.CreateSolidBrush(RGB(R,G,B));
	CRect picrct;
	picrct.top = 0;
	picrct.left = 0;
	picrct.bottom = rct.Height();
	picrct.right = rct.Width();
	pDC->FillRect(&picrct, &brs);

	ReleaseDC(pDC);

	if(m_showImageMask != NULL)
	{
		CRect rect;
		GetDlgItem(IDC_STATIC_REGIONSHOW)->GetClientRect(&rect);

		IplImage* img = cvCreateImage(cvSize(rect.Width(),rect.Height()),m_showImageMask->depth,m_showImageMask->nChannels);
		cvResize(m_showImageMask,img,CV_INTER_LINEAR);
		
		CDC* pDC = GetDlgItem(IDC_STATIC_REGIONSHOW)->GetDC();

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
}
void RegionModifyDLG::ShowStitchImage(TempParaVal tpv)
{
	if (m_type==STITCH_ChaosVectorFieldCross)
	{
		m_gsi.isvector = true;
	}
	else m_gsi.isvector = false;
	IplImage* img = m_gsi.GetImg1(tpv.density,tpv.length,tpv.chaos,tpv.theta*180/PI,tpv.beta*180/PI);

	if(img!=NULL)
	{
		CRect rect;
		GetDlgItem(IDC_STATIC_REGIONSTITCHSHOW)->GetClientRect(&rect);

		m_showImageStitch = cvCreateImage(cvSize(rect.Width(),rect.Height()),img->depth,img->nChannels);
		cvResize(img,m_showImageStitch,CV_INTER_LINEAR);

		CDC* pDC = GetDlgItem(IDC_STATIC_REGIONSTITCHSHOW)->GetDC();

		HDC hDC = pDC->GetSafeHdc();

		int rw=rect.right-rect.left;
		int rh=rect.bottom-rect.top;

		int iw=m_showImageStitch->width;
		int ih=m_showImageStitch->height;

		int tx=(int)(rw-iw)/2;
		int ty=(int)(rh-ih)/2;
		SetRect(rect,tx,ty,tx+iw,ty+ih);
		CvvImage cimg;
		cimg.CopyOf(m_showImageStitch);

		cimg.DrawToHDC(hDC,&rect);
		ReleaseDC(pDC);

		cvReleaseImage(&m_showImageStitch);
	}
}

void RegionModifyDLG::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_LEVELNUM, m_editLevelID);
	DDX_Control(pDX, IDC_EDIT_REGIONNUM, m_editRegionID);
	DDX_Control(pDX, IDC_EDIT_REGIONAREA, m_editRegionColor);
	DDX_Control(pDX, IDC_COMBO_STITCHTYPE, m_comboType);
	DDX_Control(pDX, IDC_EDIT_REGIONDENSITY, m_editDensity);
	DDX_Control(pDX, IDC_EDIT_REGIONLENGTH, m_editLength);
	DDX_Control(pDX, IDC_EDIT_REGIONCHAOS, m_editChaos);
	DDX_Control(pDX, IDC_SLIDER_REGIONDENSITY, m_sliderDensity);
	DDX_Control(pDX, IDC_SLIDER_REGIONLENGTH, m_sliderLength);
	DDX_Control(pDX, IDC_SLIDER_REGIONCHAOS, m_sliderChaos);
}


BEGIN_MESSAGE_MAP(RegionModifyDLG, CDialogEx)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_REGIONDENSITY, &RegionModifyDLG::OnNMReleasedcaptureSliderRegiondensity)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_REGIONLENGTH, &RegionModifyDLG::OnNMReleasedcaptureSliderRegionlength)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_REGIONCHAOS, &RegionModifyDLG::OnNMReleasedcaptureSliderRegionchaos)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDOK, &RegionModifyDLG::OnBnClickedOk)
	ON_CBN_SELCHANGE(IDC_COMBO_STITCHTYPE, &RegionModifyDLG::OnCbnSelchangeComboStitchtype)
END_MESSAGE_MAP()


// RegionModifyDLG 消息处理程序


BOOL RegionModifyDLG::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// TODO:  在此添加额外的初始化
	CString str;
	str.Format("%d",m_regID);
	m_editRegionID.SetWindowText(str);
	str.Format("%d",m_levelID);
	m_editLevelID.SetWindowText(str);
	str.Format("%.2lf",m_SlsPtr->regionArea*100.0/(m_showImageMask->width*m_showImageMask->height));
	m_editRegionColor.SetWindowText(str);

	InitCombox();
	InitSlider();
	InitTPV();

	this->Invalidate(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void RegionModifyDLG::OnNMReleasedcaptureSliderRegiondensity(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	int sel = m_comboType.GetCurSel();
	GetParaFromSlider(m_tpv);
	UpdateEdit(m_tpv);
	ShowMaskImage();
	ShowStitchImage(m_tpv);

	*pResult = 0;
}


void RegionModifyDLG::OnNMReleasedcaptureSliderRegionlength(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	GetParaFromSlider(m_tpv);
	UpdateEdit(m_tpv);
	ShowMaskImage();
	ShowStitchImage(m_tpv);

	*pResult = 0;
}


void RegionModifyDLG::OnNMReleasedcaptureSliderRegionchaos(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	GetParaFromSlider(m_tpv);
	UpdateEdit(m_tpv);
	ShowMaskImage();
	ShowStitchImage(m_tpv);

	*pResult = 0;
}


void RegionModifyDLG::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnPaint()

	ShowMaskImage();
	UpdateSlider(m_tpv);
	UpdateEdit(m_tpv);
	ShowStitchImage(m_tpv);
}


void RegionModifyDLG::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	if(m_SlsPtr->stitchType==STITCH_ChaosVerticalCross
	|| m_SlsPtr->stitchType==STITCH_ChaosHorizontalCross
	|| m_SlsPtr->stitchType==STITCH_ChaosVectorFieldCross)
	{
		ChaosStitch *tempPoint=(ChaosStitch *)m_SlsPtr->stitchPoint;
		delete tempPoint;
		tempPoint=NULL;
		m_SlsPtr->stitchPoint=NULL;
	}
	else if(m_SlsPtr->stitchType==STITCH_OrderlessCross)
	{
		OrderlessStitch *tempPoint=(OrderlessStitch *)m_SlsPtr->stitchPoint;
		delete tempPoint;
		tempPoint=NULL;
		m_SlsPtr->stitchPoint=NULL;
	}
	else
	{
		m_SlsPtr->stitchPoint=NULL;
	}

	m_SlsPtr->stitchType = m_type;
	m_SlsPtr->lineSet.clear();
	
	if(m_SlsPtr->stitchType==STITCH_ChaosVerticalCross
	 || m_SlsPtr->stitchType==STITCH_ChaosHorizontalCross
	 ||	m_SlsPtr->stitchType==STITCH_ChaosVectorFieldCross)
	{
		ChaosStitch *tempPoint=new ChaosStitch;
		tempPoint->density=m_tpv.density;
		tempPoint->length=m_tpv.length;
		tempPoint->chaosExtent=m_tpv.chaos;
		tempPoint->theta=m_tpv.theta;
		tempPoint->beta=m_tpv.beta;
		tempPoint->stitchName=string(m_tpv.name);
		tempPoint->stitchType = m_SlsPtr->stitchType;

		m_SlsPtr->stitchPoint=(void *)tempPoint;
		tempPoint=NULL;
	}
	else if(m_SlsPtr->stitchType==STITCH_OrderlessCross)
	{
		OrderlessStitch *tempPoint=new OrderlessStitch;
		tempPoint->density=m_tpv.density;
		tempPoint->length=m_tpv.length;
		tempPoint->chaosExtent=m_tpv.chaos;
		tempPoint->theta=m_tpv.theta;
		tempPoint->beta=m_tpv.beta;
		tempPoint->stitchName=string(m_tpv.name);
		tempPoint->stitchType = m_SlsPtr->stitchType;

		m_SlsPtr->stitchPoint=(void *)tempPoint;
		tempPoint=NULL;
	}
	else
	{
		m_SlsPtr->stitchPoint=NULL;
	}


	CDialogEx::OnOK();
}
void RegionModifyDLG::OnCbnSelchangeComboStitchtype()
{
	// TODO: 在此添加控件通知处理程序代码
	int sel = m_comboType.GetCurSel();
	ChaosStitch cs;
	OrderlessStitch os;
	int ret;
	switch (sel)
	{
	case 0:
		m_stitchlib.GetChaosVerticalCross(cs);
		m_tpv.name = "竖交叉";
		m_tpv.density = cs.density;
		m_tpv.length = cs.length;
		m_tpv.chaos = cs.chaosExtent;
		m_tpv.theta = cs.theta;
		m_tpv.beta = cs.beta;
		m_type = STITCH_ChaosVerticalCross;
		break;
	case 1:
		m_stitchlib.GetChaosHorizontalCross(cs);
		m_tpv.name = "横交叉";
		m_tpv.density = cs.density;
		m_tpv.length = cs.length;
		m_tpv.chaos = cs.chaosExtent;
		m_tpv.theta = cs.theta;
		m_tpv.beta = cs.beta;
		m_type = STITCH_ChaosHorizontalCross;
		break;
	case 2:
		m_stitchlib.GetChaosVectorFieldCross(cs);
		m_tpv.name = "矢量场交叉";
		m_tpv.density = cs.density;
		m_tpv.length = cs.length;
		m_tpv.chaos = cs.chaosExtent;
		m_tpv.theta = cs.theta;
		m_tpv.beta = cs.beta;
		m_type = STITCH_ChaosVectorFieldCross;
		break;
	case 3:
		m_stitchlib.GetOrderlessCross(os);
		m_tpv.name = "小乱针";
		m_tpv.density = os.density;
		m_tpv.length = os.length;
		m_tpv.chaos = os.chaosExtent;
		m_tpv.theta = os.theta;
		m_tpv.beta = os.beta;
		m_type = STITCH_OrderlessCross;
		break;
	default:
		ret = m_stitchlib.GetOtherStitch(sel,cs,os);
		if (ret==1)
		{
			m_tpv.name = (CString)(cs.stitchName.c_str());
			m_tpv.density = cs.density;
			m_tpv.length = cs.length;
			m_tpv.chaos = cs.chaosExtent;
			m_tpv.theta = cs.theta;
			m_tpv.beta = cs.beta;
		}
		if (ret==2)
		{
			m_tpv.name = (CString)(os.stitchName.c_str());
			m_tpv.density = os.density;
			m_tpv.length = os.length;
			m_tpv.chaos = os.chaosExtent;
			m_tpv.theta = os.theta;
			m_tpv.beta = os.beta;
		}
		m_type = STITCH_Other;
		break;
	}

	UpdateSlider(m_tpv);
	UpdateEdit(m_tpv);
	ShowStitchImage(m_tpv);
}
