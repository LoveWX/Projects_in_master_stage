
// CMagicCabsine.h : CMagicCabsine Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CMagicCabsineApp:
// �йش����ʵ�֣������ CMagicCabsine.cpp
//

class CMagicCabsineApp : public CWinAppEx
{
public:
	CMagicCabsineApp();

	string GetDefaultPath(){return defaultPath;}
	string GetProjectPath(){return projectPath;}
	void SetProjectPath(const string &tempPath){projectPath=tempPath;}

	void SetTitleText(CString titleCStr="MagicCabsine");

// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()


protected:
	string defaultPath;//Ĭ��·��,Ϊ���������ļ���,��CMagicCabsineDoc�Ĺ��캯���г�ʼ��

	//����·��,Ϊ���������ļ���,��CMagicCabsineProject��RunWorkStep1()�����е��ù����½��Ի�����ʼ��
	string projectPath;

	//����Ŀ¼
	BOOL CreateFolder(CString strPath);
	//��⹤������Ҫ���ļ����ļ����Ƿ���ȫ,����ȫ����TRUE,���򷵻�FALSE
	void CheckFilesAndFolders();
};

extern CMagicCabsineApp theApp;
