/*
//���ñ����Ի���,��ҪΪProjectConfigDLG�ඨ�弰ʵ��
//���ǹ���Ի�������ģ��,����4�����͵�������Ϣ
//��Ҫ�����������͵�������Ϣ��Ҫ�޸Ĵ����ڱ�ǩҳ�����
//2012-11-29,zhouzhou
*/

#pragma once

#include "stdafx.h"
#include "CMagicCabsineConfig.h"
#include "ProjectConfigChildDLG.h"

// ProjectConfigDLG �Ի���

class ProjectConfigDLG : public CDialogEx
{
	DECLARE_DYNAMIC(ProjectConfigDLG)

public:
	ProjectConfigDLG(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~ProjectConfigDLG();

// �Ի�������
	enum { IDD = IDD_DIALOG_CONF };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
