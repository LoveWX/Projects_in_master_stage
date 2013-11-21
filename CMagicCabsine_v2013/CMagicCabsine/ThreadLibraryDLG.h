#pragma once

#include "CMagicCabsineThreadLibrary.h"

// ThreadLibraryDLG 对话框

class ThreadLibraryDLG : public CDialogEx
{
	DECLARE_DYNAMIC(ThreadLibraryDLG)

public:
	ThreadLibraryDLG(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~ThreadLibraryDLG();

// 对话框数据
	enum { IDD = IDD_DIALOG_THREAD_LIBRERY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonAddthreadset();
	CListCtrl m_ThreadSet;
	CListCtrl m_Thread;
	CEdit m_ThreadName;
	CEdit m_ThreadNum;
	CEdit m_ThreadLib;

public:
	virtual BOOL OnInitDialog();

protected:
	string pathOfConfig;
	CMagicCabsineThreadLibrary *threadLib;
	vector< vector<Thread> > threadLibrary;
	vector<string> threadFactoryName;
	int selectedThreadSet;//选中的绣线集合

	void CreateListHead();
	void UpdateListThreadSet();
	void UpdateListThread(int libSelected);
public:
	afx_msg void OnBnClickedButtonDelthreadset();
	afx_msg void OnNMClickListThreadSet(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickListThread(NMHDR *pNMHDR, LRESULT *pResult);
};
