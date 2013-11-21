// MagicCabsineConfigDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CMagicCabsine.h"
#include "MagicCabsineConfigDlg.h"
#include "afxdialogex.h"
#include "CMagicCabsineConfig.h"


// CMagicCabsineConfigDlg 对话框

IMPLEMENT_DYNAMIC(CMagicCabsineConfigDlg, CDialogEx)

CMagicCabsineConfigDlg::CMagicCabsineConfigDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMagicCabsineConfigDlg::IDD, pParent)
{
	m_bHit = FALSE;
	currentClickedItem = -1;
}

CMagicCabsineConfigDlg::~CMagicCabsineConfigDlg()
{
}

void CMagicCabsineConfigDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_SELECT_IMAGETYPE, m_selectImageType);
	DDX_Control(pDX, IDC_LIST_PORTION_PROP, m_portionProp);
	DDX_Control(pDX, IDC_LIST_SPLIT_METHOD, m_splitMethod);
	DDX_Control(pDX, IDC_LIST_UNIVERSAL_PROP, m_universalProp);
}


BEGIN_MESSAGE_MAP(CMagicCabsineConfigDlg, CDialogEx)
	ON_NOTIFY(NM_CLICK, IDC_LIST_SPLIT_METHOD, &CMagicCabsineConfigDlg::OnClickListSplitMethod)
	ON_CBN_SELCHANGE(IDC_COMBO_SELECT_IMAGETYPE, &CMagicCabsineConfigDlg::OnSelchangeComboSelectImagetype)
	ON_BN_CLICKED(IDOK, &CMagicCabsineConfigDlg::OnBnClickedOk)
//	ON_NOTIFY(HDN_ITEMCLICK, 0, &CMagicCabsineConfigDlg::OnItemclickListSplitMethod)
ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_SPLIT_METHOD, &CMagicCabsineConfigDlg::OnItemchangedListSplitMethod)
ON_NOTIFY(NM_DBLCLK, IDC_LIST_SPLIT_METHOD, &CMagicCabsineConfigDlg::OnDblclkListSplitMethod)
END_MESSAGE_MAP()


// CMagicCabsineConfigDlg 消息处理程序


BOOL CMagicCabsineConfigDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//选择图片类型的代码
	m_selectImageType;
	CString strImageType;
	m_selectImageType.ResetContent();
	strImageType = CString("人物");
	m_selectImageType.AddString(strImageType);
	strImageType = CString("风景");
	m_selectImageType.AddString(strImageType);
	strImageType = CString("动物");
	m_selectImageType.AddString(strImageType);
	strImageType = CString("自定义");
	m_selectImageType.AddString(strImageType);
	m_selectImageType.SetWindowTextA(CString("选择图片类型"));

	// TODO:  在此添加额外的初始化
	LONG lStyle_1;
	lStyle_1=GetWindowLong(m_universalProp.m_hWnd, GWL_STYLE); //获取当前窗口style
	lStyle_1 &= ~LVS_TYPEMASK; //清除显示方式位
	lStyle_1 |= LVS_REPORT; //设置style
	SetWindowLong(m_universalProp.m_hWnd, GWL_STYLE, lStyle_1); //设置style

	DWORD dwStyle_1 = m_universalProp.GetExtendedStyle(); //获取当前扩展样式
	dwStyle_1 |= LVS_EX_FULLROWSELECT; //选中某行使整行高亮（report风格时）
	dwStyle_1 |= LVS_EX_GRIDLINES; //网格线（report风格时）
	dwStyle_1 |= LVS_EX_CHECKBOXES; //item前生成checkbox控件

	m_universalProp.SetExtendedStyle(dwStyle_1);
	m_universalProp.InsertColumn(0, CString("全局特征"));
	m_universalProp.SetColumnWidth(0,120);
	m_universalProp.InsertItem(0, CString("矢量场"));
	m_universalProp.InsertItem(1, CString("CLD"));
	m_universalProp.InsertItem(2, CString("显著性"));


	m_splitMethod.SetExtendedStyle(dwStyle_1);
	m_splitMethod.InsertColumn(0, CString("分割方法"));
	m_splitMethod.SetColumnWidth(0,120);
	m_splitMethod.InsertItem(0, CString("MeanShift"));
	m_splitMethod.InsertItem(1, CString("GraphBase"));


	m_portionProp.SetExtendedStyle(dwStyle_1);
	m_portionProp.InsertColumn(0, CString("局部特征"));
	m_portionProp.SetColumnWidth(0,120);
	m_portionProp.InsertItem(0, CString("平均色"));


	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}




void CMagicCabsineConfigDlg::OnSelchangeComboSelectImagetype()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strTemp;
	m_selectImageType.GetWindowText(strTemp);
	//MessageBox(strTemp);
	IMAGE_TYPE tempType;
	if (strTemp==CString("人物"))
	{
		tempType = IMAGE_HUMAN;
	}
	else if (strTemp==CString("风景"))
	{
		tempType = IMAGE_SCENERY;
	}
	else if (strTemp==CString("动物"))
	{
		tempType = IMAGE_ANIMAL;
	}
	else if (strTemp==CString("自定义"))
	{
		tempType = IMAGE_CUSTOM;
	}

	theConfig=new CMagicCabsineConfig(tempType);

	theConfig->GetSeleted(universalSelected,portionSelected);
	for (int i=0; i<universalSelected.size(); i++)
	{
		m_universalProp.SetCheck(i, universalSelected[i]);
	}

	for (int i=0; i<m_splitMethod.GetItemCount(); i++)
	{
		m_splitMethod.SetCheck(i, FALSE);
	}

	tempSplitMethodName = theConfig->GetSplitDataName();
	switch (tempSplitMethodName)
	{
	case SPLIT_MEANSHIFT:
		m_splitMethod.SetCheck(0, TRUE);
		m_splitMethod.SetCheck(1, FALSE);
		break;
	case SPLIT_GRAPHBASE:
		m_splitMethod.SetCheck(0, FALSE);
		m_splitMethod.SetCheck(1, TRUE);
		break;
	}

	for (int i=0; i<portionSelected.size(); i++)
	{
		m_portionProp.SetCheck(i, portionSelected[i]);
	}
}


void CMagicCabsineConfigDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str;
	m_selectImageType.GetWindowText(str);
	if(str.IsEmpty())
	{
		OnOK();
		return;
	}

	universalSelected.clear();
	for (int i=0; i<m_universalProp.GetItemCount(); i++)
	{
		universalSelected.push_back(m_universalProp.GetCheck(i));
	}

	portionSelected.clear();
	for (int i=0; i<m_portionProp.GetItemCount(); i++)
	{
		portionSelected.push_back(m_portionProp.GetCheck(i));
	}

	for (int i=0; i<m_splitMethod.GetItemCount(); i++)
	{
		if (m_splitMethod.GetCheck(i))
		{
			if (i==0)
			{
				tempSplitMethodName = SPLIT_MEANSHIFT;
			}
			else if (i==1)
			{
				tempSplitMethodName = SPLIT_GRAPHBASE;
			}
		}
	}

	theConfig->SetSeleted(universalSelected,portionSelected);
	theConfig->SetSplitDataName(tempSplitMethodName);
	theConfig->SaveConfigToFile();

	CDialogEx::OnOK();
}


void CMagicCabsineConfigDlg::OnClickListSplitMethod(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码

	DWORD dwPos = GetMessagePos();  
	CPoint point( LOWORD(dwPos), HIWORD(dwPos) );  
	m_splitMethod.ScreenToClient(&point);  
	//定义结构体  
	LVHITTESTINFO lvinfo;  
	lvinfo.pt = point;  
	//获取行号信息  
	int nItem = m_splitMethod.HitTest(&lvinfo);  
	if(nItem != -1)  
		currentClickedItem = lvinfo.iItem;   //当前行号  

	//判断是否点击在CheckBox上  
	if(lvinfo.flags == LVHT_ONITEMSTATEICON)  
	{
		m_bHit = TRUE;  
	}

	*pResult = 0;
}

void CMagicCabsineConfigDlg::OnItemchangedListSplitMethod(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	//判断m_bHit，即是否点击了CheckBox  
	if(m_bHit)  
	{  
		m_bHit = FALSE;     //复位  

		if(m_splitMethod.GetCheck(currentClickedItem))  
		{       //CheckBox被选中  
			//do your own processing   
			for (int i=0; i<m_splitMethod.GetItemCount(); i++)
			{
				m_splitMethod.SetCheck(i, FALSE);
			}
			m_splitMethod.SetCheck(currentClickedItem, TRUE);
		}  
		else  
		{      //CheckBox取消选择  
			//do your own processing  
			m_splitMethod.SetCheck(currentClickedItem, TRUE); 
		}  
	}  

	*pResult = 0;  

}


void CMagicCabsineConfigDlg::OnDblclkListSplitMethod(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码

	DWORD dwPos = GetMessagePos();  
	CPoint point( LOWORD(dwPos), HIWORD(dwPos) );  
	m_splitMethod.ScreenToClient(&point);  
	//定义结构体  
	LVHITTESTINFO lvinfo;  
	lvinfo.pt = point;  
	//获取行号信息  
	int nItem = m_splitMethod.HitTest(&lvinfo);  
	if(nItem != -1)  
		currentClickedItem = lvinfo.iItem;   //当前行号  

	//判断是否点击在CheckBox上  
	if(lvinfo.flags == LVHT_ONITEMSTATEICON)  
	{
		m_bHit = TRUE;  
	}

	*pResult = 0;
}
