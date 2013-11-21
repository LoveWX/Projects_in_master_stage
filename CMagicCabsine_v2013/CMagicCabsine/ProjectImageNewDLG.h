#pragma once

#include "stdafx.h"
#include <cv.h>
#include <highgui.h>

// ProjectImageNewDLG �Ի���

class ProjectImageNewDLG : public CDialogEx
{
	DECLARE_DYNAMIC(ProjectImageNewDLG)

public:
	ProjectImageNewDLG(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~ProjectImageNewDLG();

// �Ի�������
	enum { IDD = IDD_DIALOG_PROJECT_IMAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

//����Ϊzhouzhou��ӵĴ���
public:
	CButton m_PathSelect;
	CEdit m_SrcImagePath;
	CStatic m_ImageShowBox;
	int m_ImageType_Group;

	IplImage* TheImage;
	void ResizeImage(IplImage* img);
	void ShowImage(IplImage* img,UINT ID);

	afx_msg void OnBnClickedOk();
	afx_msg void OnClickedButton3();

	CString imagePath;
	IMAGE_TYPE imageType;
	CString getImagePath();
	IMAGE_TYPE getImageType();
};
