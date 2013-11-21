// ProjectConfigDLG.cpp : 实现文件
//

#include "stdafx.h"
#include "CMagicCabsine.h"
#include "ProjectConfigDLG.h"
#include "afxdialogex.h"


// ProjectConfigDLG 对话框

IMPLEMENT_DYNAMIC(ProjectConfigDLG, CDialogEx)

ProjectConfigDLG::ProjectConfigDLG(CWnd* pParent /*=NULL*/)
	: CDialogEx(ProjectConfigDLG::IDD, pParent)
{
}

ProjectConfigDLG::~ProjectConfigDLG()
{
}

void ProjectConfigDLG::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_TAB1);
}


BEGIN_MESSAGE_MAP(ProjectConfigDLG, CDialogEx)
	ON_BN_CLICKED(IDOK, &ProjectConfigDLG::OnBnClickedOk)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &ProjectConfigDLG::OnSelchangeTab1)
END_MESSAGE_MAP()


// ProjectConfigDLG 消息处理程序


void ProjectConfigDLG::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();

	childDLGHuman.SaveConfig();
	childDLGScenery.SaveConfig();
	childDLGAnimal.SaveConfig();
	childDLGCustom.SaveConfig();
}


BOOL ProjectConfigDLG::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_TAB1.InsertItem(0, CString("人物"));
	m_TAB1.InsertItem(1, CString("风景"));
	m_TAB1.InsertItem(2, CString("动物"));
	m_TAB1.InsertItem(3, CString("静物"));

	childDLGHuman.Create(IDD_DIALOG_CHILD,GetDlgItem(IDC_TAB1)); 
	childDLGScenery.Create(IDD_DIALOG_CHILD,GetDlgItem(IDC_TAB1)); 
	childDLGAnimal.Create(IDD_DIALOG_CHILD,GetDlgItem(IDC_TAB1)); 
	childDLGCustom.Create(IDD_DIALOG_CHILD,GetDlgItem(IDC_TAB1)); 

	// 将子窗口显示在m_Tab范围内 
	CRect rs; 
	m_TAB1.GetClientRect(rs); 
	rs.top+=22; 
	rs.bottom-=4; 
	rs.left+=2; 
	rs.right-=4; 
	childDLGHuman.MoveWindow(rs); 
	childDLGScenery.MoveWindow(rs); 
	childDLGAnimal.MoveWindow(rs); 
	childDLGCustom.MoveWindow(rs); 

	childDLGHuman.LoadConfig(IMAGE_HUMAN);
	childDLGScenery.LoadConfig(IMAGE_SCENERY);
	childDLGAnimal.LoadConfig(IMAGE_ANIMAL);
	childDLGCustom.LoadConfig(IMAGE_CUSTOM);

	childDLGHuman.ShowWindow(TRUE);
	childDLGScenery.ShowWindow(FALSE);
	childDLGAnimal.ShowWindow(FALSE);
	childDLGCustom.ShowWindow(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void ProjectConfigDLG::OnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

	int nCurSel = m_TAB1.GetCurSel(); 

	switch(nCurSel) 
	{ 
	case 0: //显示人物配置信息窗口
		childDLGHuman.ShowWindow(TRUE);
		childDLGScenery.ShowWindow(FALSE);
		childDLGAnimal.ShowWindow(FALSE);
		childDLGCustom.ShowWindow(FALSE);
		break;
	case 1: //显示风景配置信息窗口
		childDLGHuman.ShowWindow(FALSE);
		childDLGScenery.ShowWindow(TRUE);
		childDLGAnimal.ShowWindow(FALSE);
		childDLGCustom.ShowWindow(FALSE);
		break;
	case 2: //显示动物配置信息窗口
		childDLGHuman.ShowWindow(FALSE);
		childDLGScenery.ShowWindow(FALSE);
		childDLGAnimal.ShowWindow(TRUE);
		childDLGCustom.ShowWindow(FALSE);
		break;
	case 3: //显示静物配置信息窗口
		childDLGHuman.ShowWindow(FALSE);
		childDLGScenery.ShowWindow(FALSE);
		childDLGAnimal.ShowWindow(FALSE);
		childDLGCustom.ShowWindow(TRUE);
		break;
	}
}
