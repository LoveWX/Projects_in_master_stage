/*
//配置表管理对话框,主要为ProjectConfigChildDLG类定义及实现
//这是管理对话框的内框模块,每个类管理一个配置表文件
//配置表文件中的各特征的数量需要与页面对应选项的数量相同
//2012-11-29,zhouzhou
*/

#pragma once

#include "stdafx.h"
#include "CMagicCabsineConfig.h"
#include "afxwin.h"

// ProjectConfigChildDLG 对话框

class ProjectConfigChildDLG : public CDialogEx
{
	DECLARE_DYNAMIC(ProjectConfigChildDLG)

public:
	ProjectConfigChildDLG(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~ProjectConfigChildDLG();

// 对话框数据
	enum { IDD = IDD_DIALOG_CHILD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	CButton m_CHECK1_1;
	CButton m_CHECK1_2;
	CButton m_CHECK1_3;
	CButton m_CHECK2_1;
	CEdit m_EDIT1;
	CEdit m_EDIT2;
	CButton m_BUTTON1;
	CButton m_BUTTON2;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();

//以下为zhouzhou添加的成员变量和函数
protected:
	CMagicCabsineConfig *theConfig;//配置类的指针
	string splitPath;//分割方法dll文件的路径
	string simulatePath;//模拟方法的dll文件的路径
	vector<bool> universalSelected;//全局变量的选择
	vector<bool> portionSelected;//局部变量的选择

public:
	//通过tempType读入不同的配置文件初始化对话框中的信息
	void LoadConfig(IMAGE_TYPE tempType);
	//将对话框中的信息存入相应的文件中
	void SaveConfig();

	virtual BOOL OnInitDialog();
};
