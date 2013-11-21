// ProjectConfigChildDLG.cpp : 实现文件
//

#include "stdafx.h"
#include "CMagicCabsine.h"
#include "ProjectConfigChildDLG.h"
#include "afxdialogex.h"


// ProjectConfigChildDLG 对话框

IMPLEMENT_DYNAMIC(ProjectConfigChildDLG, CDialogEx)

ProjectConfigChildDLG::ProjectConfigChildDLG(CWnd* pParent /*=NULL*/)
	: CDialogEx(ProjectConfigChildDLG::IDD, pParent)
{
	theConfig=NULL;
	universalSelected.clear();
	portionSelected.clear();
}

ProjectConfigChildDLG::~ProjectConfigChildDLG()
{
	if(theConfig!=NULL)
	{
		delete theConfig;
		theConfig=NULL;
	}
	universalSelected.clear();
	portionSelected.clear();
}

void ProjectConfigChildDLG::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK1_1, m_CHECK1_1);
	DDX_Control(pDX, IDC_CHECK1_2, m_CHECK1_2);
	DDX_Control(pDX, IDC_CHECK1_3, m_CHECK1_3);
	DDX_Control(pDX, IDC_CHECK2_1, m_CHECK2_1);
	DDX_Control(pDX, IDC_EDIT1, m_EDIT1);
	DDX_Control(pDX, IDC_EDIT2, m_EDIT2);
	DDX_Control(pDX, IDC_BUTTON1, m_BUTTON1);
	DDX_Control(pDX, IDC_BUTTON2, m_BUTTON2);
}


BEGIN_MESSAGE_MAP(ProjectConfigChildDLG, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &ProjectConfigChildDLG::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &ProjectConfigChildDLG::OnBnClickedButton2)
END_MESSAGE_MAP()


// ProjectConfigChildDLG 消息处理程序
void ProjectConfigChildDLG::LoadConfig(IMAGE_TYPE tempType)
{
	theConfig=new CMagicCabsineConfig(tempType);
	theConfig->GetPathOfSplitData(splitPath);
	theConfig->GetPathOfSimulateData(simulatePath);
	theConfig->GetSeleted(universalSelected,portionSelected);
	
	if(universalSelected[0])
	{
		m_CHECK1_1.SetCheck(1);
	}
	else
	{
		m_CHECK1_1.SetCheck(0);
	}
	if(universalSelected[1])
	{
		m_CHECK1_2.SetCheck(1);
	}
	else
	{
		m_CHECK1_2.SetCheck(0);
	}
	if(universalSelected[2])
	{
		m_CHECK1_3.SetCheck(1);
	}
	else
	{
		m_CHECK1_3.SetCheck(0);
	}
	if(portionSelected[0])
	{
		m_CHECK2_1.SetCheck(1);
	}
	else
	{
		m_CHECK2_1.SetCheck(0);
	}
	m_EDIT1.SetWindowText(CString(splitPath.c_str()));
	m_EDIT2.SetWindowText(CString(simulatePath.c_str()));
}

void ProjectConfigChildDLG::SaveConfig()
{
	theConfig->SetPathOfSplitData(splitPath);
	theConfig->SetPathOfSimulateData(simulatePath);

	universalSelected.clear();
	if(m_CHECK1_1.GetCheck()==1)
	{
		universalSelected.push_back(true);
	}
	else
	{
		universalSelected.push_back(false);
	}
	if(m_CHECK1_2.GetCheck()==1)
	{
		universalSelected.push_back(true);
	}
	else
	{
		universalSelected.push_back(false);
	}
	if(m_CHECK1_3.GetCheck()==1)
	{
		universalSelected.push_back(true);
	}
	else
	{
		universalSelected.push_back(false);
	}

	portionSelected.clear();
	if(m_CHECK2_1.GetCheck()==1)
	{
		portionSelected.push_back(true);
	}
	else
	{
		portionSelected.push_back(false);
	}

	theConfig->SetSeleted(universalSelected,portionSelected);
	theConfig->SaveConfigToFile();
}


void ProjectConfigChildDLG::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CFileDialog dlgFile(TRUE,_T("*.dll"),NULL,OFN_FILEMUSTEXIST|OFN_PATHMUSTEXIST|OFN_HIDEREADONLY,
		_T("动态链接库(*.dll)|*.dll|All Files(*.*)|*.*||"),NULL);

	if(dlgFile.DoModal()!=IDOK)
		return;

	//得到的是分割方法dll文件的路径
	CString filePath=dlgFile.GetPathName();
	m_EDIT1.SetWindowText(filePath);
	splitPath=filePath;
}


void ProjectConfigChildDLG::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	CFileDialog dlgFile(TRUE,_T("*.dll"),NULL,OFN_FILEMUSTEXIST|OFN_PATHMUSTEXIST|OFN_HIDEREADONLY,
		_T("动态链接库(*.dll)|*.dll|All Files(*.*)|*.*||"),NULL);
	if(dlgFile.DoModal()!=IDOK)
		return;

	//得到的是模拟方法dll文件的路径
	CString filePath=dlgFile.GetPathName();
	m_EDIT2.SetWindowText(filePath);
	simulatePath=filePath;
}


BOOL ProjectConfigChildDLG::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
