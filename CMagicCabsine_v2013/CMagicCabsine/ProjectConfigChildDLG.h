/*
//���ñ����Ի���,��ҪΪProjectConfigChildDLG�ඨ�弰ʵ��
//���ǹ���Ի�����ڿ�ģ��,ÿ�������һ�����ñ��ļ�
//���ñ��ļ��еĸ�������������Ҫ��ҳ���Ӧѡ���������ͬ
//2012-11-29,zhouzhou
*/

#pragma once

#include "stdafx.h"
#include "CMagicCabsineConfig.h"
#include "afxwin.h"

// ProjectConfigChildDLG �Ի���

class ProjectConfigChildDLG : public CDialogEx
{
	DECLARE_DYNAMIC(ProjectConfigChildDLG)

public:
	ProjectConfigChildDLG(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~ProjectConfigChildDLG();

// �Ի�������
	enum { IDD = IDD_DIALOG_CHILD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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

//����Ϊzhouzhou��ӵĳ�Ա�����ͺ���
protected:
	CMagicCabsineConfig *theConfig;//�������ָ��
	string splitPath;//�ָ��dll�ļ���·��
	string simulatePath;//ģ�ⷽ����dll�ļ���·��
	vector<bool> universalSelected;//ȫ�ֱ�����ѡ��
	vector<bool> portionSelected;//�ֲ�������ѡ��

public:
	//ͨ��tempType���벻ͬ�������ļ���ʼ���Ի����е���Ϣ
	void LoadConfig(IMAGE_TYPE tempType);
	//���Ի����е���Ϣ������Ӧ���ļ���
	void SaveConfig();

	virtual BOOL OnInitDialog();
};
