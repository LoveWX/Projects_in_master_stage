#pragma once

#include "CMagicCabsineThreadLibrary.h"

// ThreadLibraryDLG �Ի���

class ThreadLibraryDLG : public CDialogEx
{
	DECLARE_DYNAMIC(ThreadLibraryDLG)

public:
	ThreadLibraryDLG(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~ThreadLibraryDLG();

// �Ի�������
	enum { IDD = IDD_DIALOG_THREAD_LIBRERY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
	int selectedThreadSet;//ѡ�е����߼���

	void CreateListHead();
	void UpdateListThreadSet();
	void UpdateListThread(int libSelected);
public:
	afx_msg void OnBnClickedButtonDelthreadset();
	afx_msg void OnNMClickListThreadSet(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickListThread(NMHDR *pNMHDR, LRESULT *pResult);
};
