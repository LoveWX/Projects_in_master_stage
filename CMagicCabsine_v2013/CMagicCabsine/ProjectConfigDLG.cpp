// ProjectConfigDLG.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CMagicCabsine.h"
#include "ProjectConfigDLG.h"
#include "afxdialogex.h"


// ProjectConfigDLG �Ի���

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


// ProjectConfigDLG ��Ϣ�������


void ProjectConfigDLG::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnOK();

	childDLGHuman.SaveConfig();
	childDLGScenery.SaveConfig();
	childDLGAnimal.SaveConfig();
	childDLGCustom.SaveConfig();
}


BOOL ProjectConfigDLG::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_TAB1.InsertItem(0, CString("����"));
	m_TAB1.InsertItem(1, CString("�羰"));
	m_TAB1.InsertItem(2, CString("����"));
	m_TAB1.InsertItem(3, CString("����"));

	childDLGHuman.Create(IDD_DIALOG_CHILD,GetDlgItem(IDC_TAB1)); 
	childDLGScenery.Create(IDD_DIALOG_CHILD,GetDlgItem(IDC_TAB1)); 
	childDLGAnimal.Create(IDD_DIALOG_CHILD,GetDlgItem(IDC_TAB1)); 
	childDLGCustom.Create(IDD_DIALOG_CHILD,GetDlgItem(IDC_TAB1)); 

	// ���Ӵ�����ʾ��m_Tab��Χ�� 
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
	// �쳣: OCX ����ҳӦ���� FALSE
}


void ProjectConfigDLG::OnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;

	int nCurSel = m_TAB1.GetCurSel(); 

	switch(nCurSel) 
	{ 
	case 0: //��ʾ����������Ϣ����
		childDLGHuman.ShowWindow(TRUE);
		childDLGScenery.ShowWindow(FALSE);
		childDLGAnimal.ShowWindow(FALSE);
		childDLGCustom.ShowWindow(FALSE);
		break;
	case 1: //��ʾ�羰������Ϣ����
		childDLGHuman.ShowWindow(FALSE);
		childDLGScenery.ShowWindow(TRUE);
		childDLGAnimal.ShowWindow(FALSE);
		childDLGCustom.ShowWindow(FALSE);
		break;
	case 2: //��ʾ����������Ϣ����
		childDLGHuman.ShowWindow(FALSE);
		childDLGScenery.ShowWindow(FALSE);
		childDLGAnimal.ShowWindow(TRUE);
		childDLGCustom.ShowWindow(FALSE);
		break;
	case 3: //��ʾ����������Ϣ����
		childDLGHuman.ShowWindow(FALSE);
		childDLGScenery.ShowWindow(FALSE);
		childDLGAnimal.ShowWindow(FALSE);
		childDLGCustom.ShowWindow(TRUE);
		break;
	}
}
