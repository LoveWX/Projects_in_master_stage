
// CMagicCabsine.h : CMagicCabsine 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"       // 主符号


// CMagicCabsineApp:
// 有关此类的实现，请参阅 CMagicCabsine.cpp
//

class CMagicCabsineApp : public CWinAppEx
{
public:
	CMagicCabsineApp();

	string GetDefaultPath(){return defaultPath;}
	string GetProjectPath(){return projectPath;}
	void SetProjectPath(const string &tempPath){projectPath=tempPath;}

	void SetTitleText(CString titleCStr="MagicCabsine");

// 重写
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// 实现
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()


protected:
	string defaultPath;//默认路径,为程序所在文件夹,在CMagicCabsineDoc的构造函数中初始化

	//工程路径,为工程所在文件夹,在CMagicCabsineProject的RunWorkStep1()函数中调用工程新建对话框后初始化
	string projectPath;

	//创建目录
	BOOL CreateFolder(CString strPath);
	//检测工程所需要的文件和文件夹是否齐全,若齐全返回TRUE,否则返回FALSE
	void CheckFilesAndFolders();
};

extern CMagicCabsineApp theApp;
