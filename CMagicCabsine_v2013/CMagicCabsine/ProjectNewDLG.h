/*
//�½����̶Ի�������������,��ҪΪProjectNewDLG�ඨ�弰ʵ��
//�����½�����ʱ�����õĶԻ���,����������Ϣ�洢��CMagicCabsineProject����
//2012-11-29,zhouzhou
*/


#pragma once

#include "resource.h"
#include "WzdDirDlg.h"

// ProjectNewDLG �Ի���

class ProjectNewDLG : public CDialogEx
{
	DECLARE_DYNAMIC(ProjectNewDLG)

public:
	ProjectNewDLG(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~ProjectNewDLG();

// �Ի�������
	enum { IDD = IDD_DIALOG_PROJECT_NEW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

//����Ϊzhouzhou��ӵĴ���
protected:
	CString projectName;
	CString projectPath;
	CString projectDescription;
public:
	CEdit m_ProjectName;
	CEdit m_ProjectPath;
	CEdit m_ProjectDescription;
	afx_msg void OnBnClickedOk();
	CString getProjectName();
	CString getProjectPath();
	CString getProjectDescription();
	afx_msg void OnBnClickedButton1();
	virtual BOOL OnInitDialog();
};
