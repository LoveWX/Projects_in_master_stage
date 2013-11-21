/*
//新建工程对话框所关联的类,主要为ProjectNewDLG类定义及实现
//这是新建工程时所调用的对话框,它将工程信息存储到CMagicCabsineProject类中
//2012-11-29,zhouzhou
*/


#pragma once

#include "resource.h"
#include "WzdDirDlg.h"

// ProjectNewDLG 对话框

class ProjectNewDLG : public CDialogEx
{
	DECLARE_DYNAMIC(ProjectNewDLG)

public:
	ProjectNewDLG(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~ProjectNewDLG();

// 对话框数据
	enum { IDD = IDD_DIALOG_PROJECT_NEW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

//以下为zhouzhou添加的代码
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
