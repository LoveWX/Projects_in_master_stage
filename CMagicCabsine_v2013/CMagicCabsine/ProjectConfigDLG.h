/*
//配置表管理对话框,主要为ProjectConfigDLG类定义及实现
//这是管理对话框的外框模块,保留4种类型的配置信息
//需要保留更多类型的配置信息需要修改代码在标签页中添加
//2012-11-29,zhouzhou
*/

#pragma once

#include "stdafx.h"
#include "CMagicCabsineConfig.h"
#include "ProjectConfigChildDLG.h"

// ProjectConfigDLG 对话框

class ProjectConfigDLG : public CDialogEx
{
	DECLARE_DYNAMIC(ProjectConfigDLG)

public:
	ProjectConfigDLG(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~ProjectConfigDLG();

// 对话框数据
	enum { IDD = IDD_DIALOG_CONF };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

	ProjectConfigChildDLG childDLGHuman;
	ProjectConfigChildDLG childDLGScenery;
	ProjectConfigChildDLG childDLGAnimal;
	ProjectConfigChildDLG childDLGCustom;
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	CTabCtrl m_TAB1;
	afx_msg void OnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
};
