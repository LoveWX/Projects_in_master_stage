// ProjectCanvasNewDLG.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CMagicCabsine.h"
#include "ProjectCanvasNewDLG.h"
#include "afxdialogex.h"


// ProjectCanvasNewDLG �Ի���

IMPLEMENT_DYNAMIC(ProjectCanvasNewDLG, CDialogEx)

ProjectCanvasNewDLG::ProjectCanvasNewDLG(CWnd* pParent /*=NULL*/)
	: CDialogEx(ProjectCanvasNewDLG::IDD, pParent)
{
}

ProjectCanvasNewDLG::~ProjectCanvasNewDLG()
{
}

void ProjectCanvasNewDLG::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_CANVAS_LEN, m_CanvasLength);
	DDX_Control(pDX, IDC_EDIT_CANVAS_WID, m_CanvasWidth);
	DDX_Control(pDX, IDC_COMBO_CLOTHTYPE, m_ClothType);
	DDX_Control(pDX, IDC_COMBO_THREADTYPE, m_ThreadType);
	DDX_Control(pDX, IDC_EDIT_MAGNIFICATION, m_Magnification);
}


BEGIN_MESSAGE_MAP(ProjectCanvasNewDLG, CDialogEx)
	ON_BN_CLICKED(IDOK, &ProjectCanvasNewDLG::OnBnClickedOk)
END_MESSAGE_MAP()


int ProjectCanvasNewDLG::getCanvasLength()
{
	int ans;
	sscanf_s(canvasLength,"%d",&ans);
	return ans;
}

int ProjectCanvasNewDLG::getCanvasWidth()
{
	int ans;
	sscanf_s(canvasWidth,"%d",&ans);
	return ans;
}

CLOTH_TYPE ProjectCanvasNewDLG::getClothType()
{
	return clothType;
}

THREAD_TYPE ProjectCanvasNewDLG::getThreadType()
{
	return threadType;
}

// ProjectCanvasNewDLG ��Ϣ�������


void ProjectCanvasNewDLG::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	m_CanvasLength.GetWindowText(canvasLength);
	if(canvasLength==CString(""))
	{
		MessageBox(CString("�����뻭������"), CString("Warning"), MB_OK|MB_ICONWARNING);
		return;
	}
	m_CanvasWidth.GetWindowText(canvasWidth);
	if(canvasWidth==CString(""))
	{
		MessageBox(CString("�����뻭�����"), CString("Warning"), MB_OK|MB_ICONWARNING);
		return;
	}

	switch (m_ClothType.GetCurSel())
	{
	case 0:
		clothType=CLOTH_TYPE1;
		break;
	case 1:
		clothType=CLOTH_TYPE2;
		break;
	default:
		break;
	}
	switch (m_ThreadType.GetCurSel())
	{
	case 0:
		threadType=THREAD_TYPE1;
		break;
	case 1:
		threadType=THREAD_TYPE2;
		break;
	default:
		break;
	}

	CDialogEx::OnOK();
}

BOOL ProjectCanvasNewDLG::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	m_CanvasLength.SetWindowText("1");
	m_CanvasWidth.SetWindowText("1");
	m_ClothType.AddString("��������1");
	m_ClothType.AddString("��������2");
	m_ClothType.SetCurSel(0);
	m_ThreadType.AddString("��������1");
	m_ThreadType.AddString("��������2");
	m_ThreadType.SetCurSel(0);

	m_Magnification.SetWindowText("2");

	if(canvasLength.GetLength()<=0)
	{
		canvasLength=CString("1");
	}
	if(canvasWidth.GetLength()<=0)
	{
		canvasWidth=CString("1");
	}
	m_CanvasLength.SetWindowText(canvasLength);
	m_CanvasWidth.SetWindowText(canvasWidth);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void ProjectCanvasNewDLG::SetCanvasSize(int theHeight,int theWidth)
{
	char tempStr[10];
	if(theHeight<=0)
	{
		theHeight=1;
	}
	sprintf_s(tempStr,"%d",theHeight);
	canvasLength=tempStr;
	if(theWidth<=0)
	{
		theWidth=1;
	}
	sprintf_s(tempStr,"%d",theWidth);
	canvasWidth=tempStr;
}
