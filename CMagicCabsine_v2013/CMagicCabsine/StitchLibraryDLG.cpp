// SitchLibraryDLG.cpp : 实现文件
//

#include "stdafx.h"
#include "CMagicCabsine.h"
#include "StitchLibraryDLG.h"
#include "afxdialogex.h"


// SitchLibraryDLG 对话框

IMPLEMENT_DYNAMIC(StitchLibraryDLG, CDialogEx)

	StitchLibraryDLG::StitchLibraryDLG(CWnd* pParent /*=NULL*/)
	: CDialogEx(StitchLibraryDLG::IDD, pParent)
{
	m_showImage = NULL;
}

StitchLibraryDLG::~StitchLibraryDLG()
{
}

void StitchLibraryDLG::CreateList()
{
	m_listStitch.DeleteAllItems();
	CRect rectClient;
	m_listStitch.GetClientRect(&rectClient);
	int wid = rectClient.Width();

	m_listStitch.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	m_listStitch.InsertColumn(0,"名称",LVCFMT_LEFT,wid/2);
	m_listStitch.InsertColumn(1,"备注",LVCFMT_LEFT,wid/2);

	/*int iItem = m_listStitch.InsertItem(m_listStitch.GetItemCount(), "", 0);
	m_listStitch.SetItemText(iItem,0,"竖交叉");
	m_listStitch.SetItemText(iItem,1,"||||||||");

	iItem = m_listStitch.InsertItem(m_listStitch.GetItemCount(), "", 0);
	m_listStitch.SetItemText(iItem,0,"横交叉");
	m_listStitch.SetItemText(iItem,1,"———");

	iItem = m_listStitch.InsertItem(m_listStitch.GetItemCount(), "", 0);
	m_listStitch.SetItemText(iItem,0,"方向场交叉");
	m_listStitch.SetItemText(iItem,1,"#+-");

	iItem = m_listStitch.InsertItem(m_listStitch.GetItemCount(), "", 0);
	m_listStitch.SetItemText(iItem,0,"小乱针");
	m_listStitch.SetItemText(iItem,1,"&*%￥");*/
}
void StitchLibraryDLG::UpdateList()
{
	m_listStitch.DeleteAllItems();
	/*CRect rectClient;
	m_listStitch.GetClientRect(&rectClient);
	int wid = rectClient.Width();

	m_listStitch.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	m_listStitch.InsertColumn(0,"名称",LVCFMT_LEFT,wid/2);
	m_listStitch.InsertColumn(1,"备注",LVCFMT_LEFT,wid/2);*/

	int iItem = m_listStitch.InsertItem(m_listStitch.GetItemCount(), "", 0);
	m_listStitch.SetItemText(iItem,0,"竖交叉");
	m_listStitch.SetItemText(iItem,1,"默认针法");

	iItem = m_listStitch.InsertItem(m_listStitch.GetItemCount(), "", 0);
	m_listStitch.SetItemText(iItem,0,"横交叉");
	m_listStitch.SetItemText(iItem,1,"默认针法");

	iItem = m_listStitch.InsertItem(m_listStitch.GetItemCount(), "", 0);
	m_listStitch.SetItemText(iItem,0,"方向场交叉");
	m_listStitch.SetItemText(iItem,1,"默认针法");

	iItem = m_listStitch.InsertItem(m_listStitch.GetItemCount(), "", 0);
	m_listStitch.SetItemText(iItem,0,"小乱针");
	m_listStitch.SetItemText(iItem,1,"默认针法");

	vector<ChaosStitch> tempChaosStitch;
	vector<OrderlessStitch> tempOrderlessStitch;
	m_stitchlib.GetOtherChaosStitch(tempChaosStitch);
	m_stitchlib.GetOtherOrderlessStitch(tempOrderlessStitch);

	for (int i=0;i<tempChaosStitch.size();i++)
	{
		iItem = m_listStitch.InsertItem(m_listStitch.GetItemCount(), "", 0);
		CString str;
		str.Format("%s",tempChaosStitch[i].stitchName.c_str());
		m_listStitch.SetItemText(iItem,0,str);
		m_listStitch.SetItemText(iItem,1,"自定义针法");
	}
	for (int i=0;i<tempOrderlessStitch.size();i++)
	{
		iItem = m_listStitch.InsertItem(m_listStitch.GetItemCount(), "", 0);
		CString str;
		str.Format("%s",tempOrderlessStitch[i].stitchName.c_str());
		m_listStitch.SetItemText(iItem,0,str);
		m_listStitch.SetItemText(iItem,1,"自定义针法");
	}
}
void StitchLibraryDLG::InitSliderAndEdit()
{
	m_sliderDensity.SetRange(0,SLD_UP_DSY);
	m_sliderLength.SetRange(0,SLD_UP_LEN);
	m_sliderChaos.SetRange(0,SLD_UP_CHA);
	m_sliderTheta.SetRange(0,SLD_UP_THETA);
	m_sliderBeta.SetRange(0,SLD_UP_BETA);
}
int StitchLibraryDLG::GetParaFromList(int nItem,TempParaVal& tpv)
{
	if(nItem>=0 && nItem<m_listStitch.GetItemCount())            //判断dan击位置是否在有数据的列表项上面
	{
		ChaosStitch cs;
		OrderlessStitch os;
		int ret;
		switch (nItem)
		{
		case 0:
			m_stitchlib.GetChaosVerticalCross(cs);
			tpv.name = "竖交叉";
			tpv.density = cs.density;
			tpv.length = cs.length;
			tpv.chaos = cs.chaosExtent;
			tpv.theta = cs.theta;
			tpv.beta = cs.beta;
			m_type = STITCH_ChaosVerticalCross;
			break;
		case 1:
			m_stitchlib.GetChaosHorizontalCross(cs);
			tpv.name = "横交叉";
			tpv.density = cs.density;
			tpv.length = cs.length;
			tpv.chaos = cs.chaosExtent;
			tpv.theta = cs.theta;
			tpv.beta = cs.beta;
			m_type = STITCH_ChaosHorizontalCross;
			break;
		case 2:
			m_stitchlib.GetChaosVectorFieldCross(cs);
			tpv.name = "矢量场交叉";
			tpv.density = cs.density;
			tpv.length = cs.length;
			tpv.chaos = cs.chaosExtent;
			tpv.theta = cs.theta;
			tpv.beta = cs.beta;
			m_type = STITCH_ChaosVectorFieldCross;
			break;
		case 3:
			m_stitchlib.GetOrderlessCross(os);
			tpv.name = "小乱针";
			tpv.density = os.density;
			tpv.length = os.length;
			tpv.chaos = os.chaosExtent;
			tpv.theta = os.theta;
			tpv.beta = os.beta;
			m_type = STITCH_OrderlessCross;
			break;
		default:
			ret = m_stitchlib.GetOtherStitch(nItem,cs,os);
			if (ret==1)
			{
				tpv.name = (CString)(cs.stitchName.c_str());
				tpv.density = cs.density;
				tpv.length = cs.length;
				tpv.chaos = cs.chaosExtent;
				tpv.theta = cs.theta;
				tpv.beta = cs.beta;
			}
			if (ret==2)
			{
				tpv.name = (CString)(os.stitchName.c_str());
				tpv.density = os.density;
				tpv.length = os.length;
				tpv.chaos = os.chaosExtent;
				tpv.theta = os.theta;
				tpv.beta = os.beta;
			}
			m_type = STITCH_Other;
			break;
		}
	}
	return 0;
}
void StitchLibraryDLG::UpdateSlider(TempParaVal tpv)
{
	ParaBound PB;
	int pos = 0;
	pos =(int) (SLD_UP_DSY*(tpv.density-PB.DensityMin)/(PB.DensityMax-PB.DensityMin));
	m_sliderDensity.SetPos(pos);
	pos =(int) (SLD_UP_LEN*(tpv.length-PB.LengthMin)/(PB.LengthMax-PB.LengthMin));
	m_sliderLength.SetPos(pos);
	pos =(int) (SLD_UP_CHA*(tpv.chaos-PB.ChaosMin)/(PB.ChaosMax-PB.ChaosMin));
	m_sliderChaos.SetPos(pos);
	pos =(int) (SLD_UP_THETA*(tpv.theta*180/PI-PB.ThetaMin)/(PB.ThetaMax-PB.ThetaMin));
	m_sliderTheta.SetPos(pos);
	pos =(int) (SLD_UP_BETA*(tpv.beta*180/PI-PB.BetaMin)/(PB.BetaMax-PB.BetaMin));
	m_sliderBeta.SetPos(pos);
}
void StitchLibraryDLG::UpdateEdit(TempParaVal tpv)
{
	m_editName.SetWindowText(tpv.name);
	CString str;
	str.Format("%.2f",tpv.density);
	m_editDensity.SetWindowText(str);
	str.Format("%.2f",tpv.length);
	m_editLength.SetWindowText(str);
	str.Format("%.2f",tpv.chaos);
	m_editChaos.SetWindowText(str);
	str.Format("%.2f",tpv.theta*180/PI);
	m_editTheta.SetWindowText(str);
	str.Format("%.2f",tpv.beta*180/PI);
	m_editBeta.SetWindowText(str);
}
void StitchLibraryDLG::GetParaFromSlider(TempParaVal& tpv)
{
	ParaBound PB;
	int pos=0;
	pos = m_sliderDensity.GetPos();
	tpv.density = pos*(PB.DensityMax-PB.DensityMin)/SLD_UP_DSY + PB.DensityMin;
	pos = m_sliderLength.GetPos();
	tpv.length = pos*(PB.LengthMax-PB.LengthMin)/SLD_UP_LEN + PB.LengthMin;
	pos = m_sliderChaos.GetPos();
	tpv.chaos = pos*(PB.ChaosMax-PB.ChaosMin)/SLD_UP_CHA + PB.ChaosMin;
	pos = m_sliderTheta.GetPos();
	tpv.theta = (pos*(PB.ThetaMax-PB.ThetaMin)/SLD_UP_THETA + PB.ThetaMin)*PI/180;
	pos = m_sliderBeta.GetPos();
	tpv.beta = (pos*(PB.BetaMax-PB.BetaMin)/SLD_UP_BETA + PB.BetaMin)*PI/180;
}
void StitchLibraryDLG::UpdateImage(TempParaVal tpv)
{
	if (m_type==STITCH_ChaosVectorFieldCross)
	{
		m_gsi.isvector = true;
	}
	else m_gsi.isvector = false;

	IplImage* img = m_gsi.GetImg1(tpv.density,tpv.length,tpv.chaos,tpv.theta*180/PI,tpv.beta*180/PI);
	CRect rect;
	GetDlgItem(IDC_STATIC_STITCHSHOW)->GetWindowRect(&rect);

	if(img!=NULL)
	{
		m_showImage = cvCreateImage(cvSize(rect.Width(),rect.Height()),img->depth,img->nChannels);
		cvResize(img,m_showImage,CV_INTER_LINEAR);
		ShowImage(m_showImage);
		cvReleaseImage(&m_showImage);
	}
}
void StitchLibraryDLG::ShowImage(IplImage* img)
{
	CDC* pDC = GetDlgItem(IDC_STATIC_STITCHSHOW)->GetDC();

	HDC hDC = pDC->GetSafeHdc();

	CRect rect;
	GetDlgItem(IDC_STATIC_STITCHSHOW)->GetClientRect(&rect);

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
void StitchLibraryDLG::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_STITCH, m_listStitch);
	DDX_Control(pDX, IDC_SLIDER_STITCHDENSITY, m_sliderDensity);
	DDX_Control(pDX, IDC_SLIDER_STITCHLENGTH, m_sliderLength);
	DDX_Control(pDX, IDC_SLIDER_STITCHCHAOS, m_sliderChaos);
	DDX_Control(pDX, IDC_SLIDER_STITCHTHETA, m_sliderTheta);
	DDX_Control(pDX, IDC_SLIDER_STITCHBETA, m_sliderBeta);
	DDX_Control(pDX, IDC_EDIT_STITCHDENSITY, m_editDensity);
	DDX_Control(pDX, IDC_EDIT_STITCHLENGTH, m_editLength);
	DDX_Control(pDX, IDC_EDIT_STITCHCHAOS, m_editChaos);
	DDX_Control(pDX, IDC_EDIT_STITCHTHETA, m_editTheta);
	DDX_Control(pDX, IDC_EDIT_STITCHBETA, m_editBeta);
	DDX_Control(pDX, IDC_EDIT_STITCHNAME, m_editName);
	DDX_Control(pDX, IDC_BUTTON_ADDSTITCH, m_btnAddStitch);
	DDX_Control(pDX, IDC_BUTTON_DELETESTITCH, m_btnDeleteStitch);
	DDX_Control(pDX, IDC_BUTTON_MODIFYSTITCH, m_btnModifyStitch);
}


BEGIN_MESSAGE_MAP(StitchLibraryDLG, CDialogEx)
	ON_NOTIFY(NM_CLICK, IDC_LIST_STITCH, &StitchLibraryDLG::OnNMClickListStitch)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_STITCHDENSITY, &StitchLibraryDLG::OnNMReleasedcaptureSliderStitchdensity)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_STITCHLENGTH, &StitchLibraryDLG::OnNMReleasedcaptureSliderStitchlength)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_STITCHCHAOS, &StitchLibraryDLG::OnNMReleasedcaptureSliderStitchchaos)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_STITCHTHETA, &StitchLibraryDLG::OnNMReleasedcaptureSliderStitchtheta)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_STITCHBETA, &StitchLibraryDLG::OnNMReleasedcaptureSliderStitchbeta)
	ON_BN_CLICKED(IDC_BUTTON_ADDSTITCH, &StitchLibraryDLG::OnBnClickedButtonAddstitch)
	ON_BN_CLICKED(IDC_BUTTON_DELETESTITCH, &StitchLibraryDLG::OnBnClickedButtonDeletestitch)
	ON_BN_CLICKED(IDC_BUTTON_MODIFYSTITCH, &StitchLibraryDLG::OnBnClickedButtonModifystitch)
END_MESSAGE_MAP()


// SitchLibraryDLG 消息处理程序


BOOL StitchLibraryDLG::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CreateList();
	UpdateList();
	InitSliderAndEdit();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void StitchLibraryDLG::OnNMClickListStitch(NMHDR *pNMHDR, LRESULT *pResult)
{
	//LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	NM_LISTVIEW *pNMListView=(NM_LISTVIEW *)pNMHDR;
	int nItem=pNMListView->iItem;
	if(nItem>=0 && nItem<m_listStitch.GetItemCount())            //判断双击位置是否在有数据的列表项上面
	{
		if (nItem<4)
		{
			m_btnAddStitch.EnableWindow(FALSE);
			m_btnDeleteStitch.EnableWindow(FALSE);
			m_btnModifyStitch.EnableWindow(FALSE);
		}
		else{
			m_btnAddStitch.EnableWindow(FALSE);
			m_btnDeleteStitch.EnableWindow(TRUE);
			m_btnModifyStitch.EnableWindow(TRUE);
		}

		TempParaVal tpv;
		GetParaFromList(nItem,tpv);
		UpdateSlider(tpv);
		UpdateEdit(tpv);
		UpdateImage(tpv);
	}
	else{
		m_btnAddStitch.EnableWindow(TRUE);
	}

	*pResult = 0;
}


void StitchLibraryDLG::OnNMReleasedcaptureSliderStitchdensity(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	TempParaVal tpv;
	GetParaFromSlider(tpv);
	UpdateEdit(tpv);
	UpdateImage(tpv);

	*pResult = 0;
}


void StitchLibraryDLG::OnNMReleasedcaptureSliderStitchlength(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	TempParaVal tpv;
	GetParaFromSlider(tpv);
	UpdateEdit(tpv);
	UpdateImage(tpv);
	*pResult = 0;
}


void StitchLibraryDLG::OnNMReleasedcaptureSliderStitchchaos(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	TempParaVal tpv;
	GetParaFromSlider(tpv);
	UpdateEdit(tpv);
	UpdateImage(tpv);
	*pResult = 0;
}

void StitchLibraryDLG::OnNMReleasedcaptureSliderStitchtheta(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	TempParaVal tpv;
	GetParaFromSlider(tpv);
	UpdateEdit(tpv);
	UpdateImage(tpv);
	*pResult = 0;
}


void StitchLibraryDLG::OnNMReleasedcaptureSliderStitchbeta(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	TempParaVal tpv;
	GetParaFromSlider(tpv);
	UpdateEdit(tpv);
	UpdateImage(tpv);
	*pResult = 0;
}


void StitchLibraryDLG::OnBnClickedButtonAddstitch()
{
	// TODO: 在此添加控件通知处理程序代码
	TempParaVal tpv;
	GetParaFromSlider(tpv);
	m_editName.GetWindowTextA(tpv.name);

	int iItem = m_listStitch.InsertItem(m_listStitch.GetItemCount(), "", 0);
	m_listStitch.SetItemText(iItem,0,tpv.name);
	m_listStitch.SetItemText(iItem,1,"自定义针法");

	ChaosStitch cs;
	cs.stitchName = tpv.name.GetBuffer(0);
	cs.density = tpv.density;
	cs.length = tpv.length;
	cs.chaosExtent = tpv.chaos;
	cs.theta = tpv.theta;
	cs.beta = tpv.beta;
	m_stitchlib.AddNewChaosStitch(cs);

	m_stitchlib.SaveStitchFile();
}


void StitchLibraryDLG::OnBnClickedButtonDeletestitch()
{
	// TODO: 在此添加控件通知处理程序代码
	int nItem = m_listStitch.GetSelectionMark();
	m_stitchlib.RemoveStitch(nItem);

	m_stitchlib.SaveStitchFile();

	UpdateList();
}


void StitchLibraryDLG::OnBnClickedButtonModifystitch()
{
	// TODO: 在此添加控件通知处理程序代码
	int nItem = m_listStitch.GetSelectionMark();

	TempParaVal tpv;
	GetParaFromSlider(tpv);
	m_editName.GetWindowTextA(tpv.name);

	ChaosStitch cs;
	cs.stitchName = tpv.name.GetBuffer(0);
	cs.density = tpv.density;
	cs.length = tpv.length;
	cs.chaosExtent = tpv.chaos;
	cs.theta = tpv.theta;
	cs.beta = tpv.beta;

	m_stitchlib.ModifyChaosStitch(nItem,cs);

	m_stitchlib.SaveStitchFile();
}
