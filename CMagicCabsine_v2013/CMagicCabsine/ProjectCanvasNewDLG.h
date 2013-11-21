#pragma once

#include "stdafx.h"

// ProjectCanvasNewDLG �Ի���

class ProjectCanvasNewDLG : public CDialogEx
{
	DECLARE_DYNAMIC(ProjectCanvasNewDLG)

public:
	ProjectCanvasNewDLG(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~ProjectCanvasNewDLG();

// �Ի�������
	enum { IDD = IDD_DIALOG_CANVAS_NEW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

//����Ϊzhouzhou��ӵĴ���
protected:
	CString canvasLength;
	CString canvasWidth;
	CLOTH_TYPE clothType;
	THREAD_TYPE threadType;
public:
	CEdit m_CanvasLength;
	CEdit m_CanvasWidth;
	CEdit m_Magnification;
	CComboBox m_ClothType;
	CComboBox m_ThreadType;

	int getCanvasLength();
	int getCanvasWidth();
	CLOTH_TYPE getClothType();
	THREAD_TYPE getThreadType();
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	void SetCanvasSize(int theHeight,int theWidth);
};
