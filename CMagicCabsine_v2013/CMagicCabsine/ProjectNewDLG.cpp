// ProjectNewDLG.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CMagicCabsine.h"
#include "ProjectNewDLG.h"
#include "afxdialogex.h"

#include <ctime>
using namespace std;

// ProjectNewDLG �Ի���

IMPLEMENT_DYNAMIC(ProjectNewDLG, CDialogEx)

ProjectNewDLG::ProjectNewDLG(CWnd* pParent /*=NULL*/)
	: CDialogEx(ProjectNewDLG::IDD, pParent)
{

}

ProjectNewDLG::~ProjectNewDLG()
{
}

BOOL ProjectNewDLG::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	projectPath=CString(theApp.GetDefaultPath().c_str())+"Projects\\";
	m_ProjectPath.SetWindowText(projectPath);	

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void ProjectNewDLG::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROJECT_DESCRIPTION, m_ProjectDescription);
	DDX_Control(pDX, IDC_PROJECT_NAME, m_ProjectName);
	DDX_Control(pDX, IDC_PROJECT_PATH, m_ProjectPath);
}


BEGIN_MESSAGE_MAP(ProjectNewDLG, CDialogEx)
	ON_BN_CLICKED(IDOK, &ProjectNewDLG::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &ProjectNewDLG::OnBnClickedButton1)
END_MESSAGE_MAP()


// ProjectNewDLG ��Ϣ�������


void ProjectNewDLG::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	m_ProjectName.GetWindowTextA(projectName);
	m_ProjectPath.GetWindowTextA(projectPath);
	m_ProjectDescription.GetWindowTextA(projectDescription);

	int i,j,len=projectDescription.GetLength();
	char *description=new char[len+1];
	char *str=new char[len+1];
	for(i=0,j=0;i<len;i++)
	{
		str[j]=projectDescription[i];
		if(projectDescription[i]==13&&projectDescription[i+1]==10)
		{
			continue;
		}
		j++;
	}
	str[j]='\0';
	projectDescription=str;
	delete[] description;
	delete[] str;
	description=NULL;
	str=NULL;

	CString emptyString=CString("");
	if(projectName==emptyString)
	{
		MessageBox(CString("�����빤������."),CString("��������"),MB_OK|MB_ICONWARNING);
		return;
	}

	time_t myTime=time(NULL);
	char tmpStr[16];
	strftime(tmpStr,sizeof(tmpStr),"_%Y%m%d%H%M%S",localtime(&myTime));
	projectName+=tmpStr;

	if(projectPath==emptyString)
	{
		MessageBox(CString("�����빤��·��."),CString("����·��"),MB_OK|MB_ICONWARNING);
		return;
	}
// 	if(projectDescription==emptyString)
// 	{
// 		MessageBox(CString("�����빤������."),CString("Warning"),MB_OK|MB_ICONWARNING);
// 		return;
// 	}

	CDialogEx::OnOK();
}

CString ProjectNewDLG::getProjectName()
{
	return projectName;
}

CString ProjectNewDLG::getProjectPath()
{
	return projectPath;
}

CString ProjectNewDLG::getProjectDescription()
{
	return projectDescription;
}

void ProjectNewDLG::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CWzdDirDlg dlg;
	
	CString dir=dlg.GetDirectory(this,projectPath,"��ѡ�񹤳�Ŀ¼");
	return;
	int length=dir.GetLength();
	if(length<=0)
	{
		return;
	}
	if(dir.Right(1)!=CString("\\"))
	{
		dir+=CString("\\");
	}
	m_ProjectPath.SetWindowText(dir);
// 	while(dir.GetLength() == 0)
// 	{
// 		MessageBox(CString("��ѡ�񹤳�·��"));
// 		dir = dlg.GetDirectory(this, "","��ѡ�񹤳�Ŀ¼");
// 	}

}
