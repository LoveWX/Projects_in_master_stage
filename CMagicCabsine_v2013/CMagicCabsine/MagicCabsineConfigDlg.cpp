// MagicCabsineConfigDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CMagicCabsine.h"
#include "MagicCabsineConfigDlg.h"
#include "afxdialogex.h"
#include "CMagicCabsineConfig.h"


// CMagicCabsineConfigDlg �Ի���

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


// CMagicCabsineConfigDlg ��Ϣ�������


BOOL CMagicCabsineConfigDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	//ѡ��ͼƬ���͵Ĵ���
	m_selectImageType;
	CString strImageType;
	m_selectImageType.ResetContent();
	strImageType = CString("����");
	m_selectImageType.AddString(strImageType);
	strImageType = CString("�羰");
	m_selectImageType.AddString(strImageType);
	strImageType = CString("����");
	m_selectImageType.AddString(strImageType);
	strImageType = CString("�Զ���");
	m_selectImageType.AddString(strImageType);
	m_selectImageType.SetWindowTextA(CString("ѡ��ͼƬ����"));

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	LONG lStyle_1;
	lStyle_1=GetWindowLong(m_universalProp.m_hWnd, GWL_STYLE); //��ȡ��ǰ����style
	lStyle_1 &= ~LVS_TYPEMASK; //�����ʾ��ʽλ
	lStyle_1 |= LVS_REPORT; //����style
	SetWindowLong(m_universalProp.m_hWnd, GWL_STYLE, lStyle_1); //����style

	DWORD dwStyle_1 = m_universalProp.GetExtendedStyle(); //��ȡ��ǰ��չ��ʽ
	dwStyle_1 |= LVS_EX_FULLROWSELECT; //ѡ��ĳ��ʹ���и�����report���ʱ��
	dwStyle_1 |= LVS_EX_GRIDLINES; //�����ߣ�report���ʱ��
	dwStyle_1 |= LVS_EX_CHECKBOXES; //itemǰ����checkbox�ؼ�

	m_universalProp.SetExtendedStyle(dwStyle_1);
	m_universalProp.InsertColumn(0, CString("ȫ������"));
	m_universalProp.SetColumnWidth(0,120);
	m_universalProp.InsertItem(0, CString("ʸ����"));
	m_universalProp.InsertItem(1, CString("CLD"));
	m_universalProp.InsertItem(2, CString("������"));


	m_splitMethod.SetExtendedStyle(dwStyle_1);
	m_splitMethod.InsertColumn(0, CString("�ָ��"));
	m_splitMethod.SetColumnWidth(0,120);
	m_splitMethod.InsertItem(0, CString("MeanShift"));
	m_splitMethod.InsertItem(1, CString("GraphBase"));


	m_portionProp.SetExtendedStyle(dwStyle_1);
	m_portionProp.InsertColumn(0, CString("�ֲ�����"));
	m_portionProp.SetColumnWidth(0,120);
	m_portionProp.InsertItem(0, CString("ƽ��ɫ"));


	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}




void CMagicCabsineConfigDlg::OnSelchangeComboSelectImagetype()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString strTemp;
	m_selectImageType.GetWindowText(strTemp);
	//MessageBox(strTemp);
	IMAGE_TYPE tempType;
	if (strTemp==CString("����"))
	{
		tempType = IMAGE_HUMAN;
	}
	else if (strTemp==CString("�羰"))
	{
		tempType = IMAGE_SCENERY;
	}
	else if (strTemp==CString("����"))
	{
		tempType = IMAGE_ANIMAL;
	}
	else if (strTemp==CString("�Զ���"))
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	DWORD dwPos = GetMessagePos();  
	CPoint point( LOWORD(dwPos), HIWORD(dwPos) );  
	m_splitMethod.ScreenToClient(&point);  
	//����ṹ��  
	LVHITTESTINFO lvinfo;  
	lvinfo.pt = point;  
	//��ȡ�к���Ϣ  
	int nItem = m_splitMethod.HitTest(&lvinfo);  
	if(nItem != -1)  
		currentClickedItem = lvinfo.iItem;   //��ǰ�к�  

	//�ж��Ƿ�����CheckBox��  
	if(lvinfo.flags == LVHT_ONITEMSTATEICON)  
	{
		m_bHit = TRUE;  
	}

	*pResult = 0;
}

void CMagicCabsineConfigDlg::OnItemchangedListSplitMethod(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//�ж�m_bHit�����Ƿ�����CheckBox  
	if(m_bHit)  
	{  
		m_bHit = FALSE;     //��λ  

		if(m_splitMethod.GetCheck(currentClickedItem))  
		{       //CheckBox��ѡ��  
			//do your own processing   
			for (int i=0; i<m_splitMethod.GetItemCount(); i++)
			{
				m_splitMethod.SetCheck(i, FALSE);
			}
			m_splitMethod.SetCheck(currentClickedItem, TRUE);
		}  
		else  
		{      //CheckBoxȡ��ѡ��  
			//do your own processing  
			m_splitMethod.SetCheck(currentClickedItem, TRUE); 
		}  
	}  

	*pResult = 0;  

}


void CMagicCabsineConfigDlg::OnDblclkListSplitMethod(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	DWORD dwPos = GetMessagePos();  
	CPoint point( LOWORD(dwPos), HIWORD(dwPos) );  
	m_splitMethod.ScreenToClient(&point);  
	//����ṹ��  
	LVHITTESTINFO lvinfo;  
	lvinfo.pt = point;  
	//��ȡ�к���Ϣ  
	int nItem = m_splitMethod.HitTest(&lvinfo);  
	if(nItem != -1)  
		currentClickedItem = lvinfo.iItem;   //��ǰ�к�  

	//�ж��Ƿ�����CheckBox��  
	if(lvinfo.flags == LVHT_ONITEMSTATEICON)  
	{
		m_bHit = TRUE;  
	}

	*pResult = 0;
}
