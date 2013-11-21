// ThreadLibraryDLG.cpp : 实现文件
//

#include "stdafx.h"
#include "CMagicCabsine.h"
#include "ThreadLibraryDLG.h"
#include "afxdialogex.h"


// ThreadLibraryDLG 对话框

IMPLEMENT_DYNAMIC(ThreadLibraryDLG, CDialogEx)

ThreadLibraryDLG::ThreadLibraryDLG(CWnd* pParent /*=NULL*/)
	: CDialogEx(ThreadLibraryDLG::IDD, pParent)
{
}

ThreadLibraryDLG::~ThreadLibraryDLG()
{
	selectedThreadSet=-1;
	threadLib->SetThreadSetName(threadFactoryName);
	threadFactoryName.clear();
	threadLib->SetThreadSet(threadLibrary);
	threadLibrary.clear();
	threadLib->SaveConfigToFile();
	if(threadLib!=NULL)
	{
		delete threadLib;
		threadLib=NULL;
	}
}

BOOL ThreadLibraryDLG::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	pathOfConfig=theApp.GetDefaultPath()+string("ConfigFile\\threadLibrary.config");

	selectedThreadSet=-1;

	threadLib=new CMagicCabsineThreadLibrary;
	threadLib->GetThreadSet(threadLibrary);
	threadLib->GetThreadSetName(threadFactoryName);

	CreateListHead();
	UpdateListThreadSet();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void ThreadLibraryDLG::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_THREAD_SET, m_ThreadSet);
	DDX_Control(pDX, IDC_LIST_THREAD, m_Thread);
	DDX_Control(pDX, IDC_EDIT_THREADNAME, m_ThreadName);
	DDX_Control(pDX, IDC_EDIT_THREADNUM, m_ThreadNum);
	DDX_Control(pDX, IDC_EDIT_THREADLIB, m_ThreadLib);
}

void ThreadLibraryDLG::CreateListHead()
{
	m_ThreadSet.DeleteAllItems();
	CRect rectClient;
	m_ThreadSet.GetClientRect(&rectClient);
	m_ThreadSet.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	m_ThreadSet.InsertColumn(0,"绣线库名称",LVCFMT_LEFT,rectClient.Width());

	m_Thread.DeleteAllItems();
	m_Thread.GetClientRect(&rectClient);
	int width=rectClient.Width()/2;
	m_Thread.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	m_Thread.InsertColumn(0,"绣线名称",LVCFMT_LEFT,width);
	m_Thread.InsertColumn(1,"绣线颜色(R,G,B)",LVCFMT_LEFT,width);
}

void ThreadLibraryDLG::UpdateListThreadSet()
{
	int i,iItem;
	m_ThreadSet.DeleteAllItems();

	for(i=0;i<threadLibrary.size();i++)
	{
		iItem=m_ThreadSet.InsertItem(m_ThreadSet.GetItemCount(),"",0);
		m_ThreadSet.SetItemText(iItem,0,threadFactoryName[i].c_str());
	}
}

void ThreadLibraryDLG::UpdateListThread(int libSelected)
{
	int i,iItem;
	m_Thread.DeleteAllItems();

	for(i=0;i<threadLibrary[libSelected].size();i++)
	{
		iItem=m_ThreadSet.InsertItem(m_ThreadSet.GetItemCount(),"",0);
		m_ThreadSet.SetItemText(iItem,0,threadLibrary[libSelected][i].threadName.c_str());
	}
}

BEGIN_MESSAGE_MAP(ThreadLibraryDLG, CDialogEx)
//	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_THREAD_SET, &ThreadLibraryDLG::OnItemchangedListThreadSet)
	ON_BN_CLICKED(IDC_BUTTON_ADDTHREADSET, &ThreadLibraryDLG::OnBnClickedButtonAddthreadset)
	ON_BN_CLICKED(IDC_BUTTON_DELTHREADSET, &ThreadLibraryDLG::OnBnClickedButtonDelthreadset)
	ON_NOTIFY(NM_CLICK, IDC_LIST_THREAD_SET, &ThreadLibraryDLG::OnNMClickListThreadSet)
	ON_NOTIFY(NM_CLICK, IDC_LIST_THREAD, &ThreadLibraryDLG::OnNMClickListThread)
END_MESSAGE_MAP()


// ThreadLibraryDLG 消息处理程序


//void ThreadLibraryDLG::OnItemchangedListThreadSet(NMHDR *pNMHDR, LRESULT *pResult)
//{
//	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
//	// TODO: 在此添加控件通知处理程序代码
//	*pResult = 0;
//}

void ThreadLibraryDLG::OnBnClickedButtonAddthreadset()
{
	// TODO: 在此添加控件通知处理程序代码
	CFileDialog dlgFile(TRUE,_T("*.csv"),NULL,OFN_FILEMUSTEXIST|OFN_PATHMUSTEXIST|OFN_HIDEREADONLY,
		_T("CSV FILES(*.csv)|*.csv|All Files(*.*)|*.*||"),NULL);
	CString tempCString=theApp.GetDefaultPath().c_str();
	tempCString+="ThreadLibrary\\";
	dlgFile.m_ofn.lpstrInitialDir=tempCString;
	
	if(dlgFile.DoModal()!=IDOK)
	{
		return;
	}

	tempCString=dlgFile.GetPathName();//获取打开的文件路径

	Thread tempThread;
	vector<Thread> tempThreadVector;
	ifstream fin(tempCString);
	int i;
	const int sizeOfStr=300;
	char str[sizeOfStr];
	string factoryName;
	fin.getline(str,sizeOfStr,',');
	factoryName=str;
	fin.getline(str,sizeOfStr);
	while(fin.getline(str,sizeOfStr,','))
	{
		fin.getline(str,sizeOfStr,',');
		tempThread.threadName=str;
		fin>>tempThread.colorR>>str[0]>>tempThread.colorG>>str[0]>>tempThread.colorB;
		fin.getline(str,sizeOfStr);
		tempThreadVector.push_back(tempThread);
	}
	threadLibrary.push_back(tempThreadVector);
	threadFactoryName.push_back(factoryName);
	fin.close();

	//插入列表表项
	i=m_ThreadSet.InsertItem(m_ThreadSet.GetItemCount(),"",0);
	m_ThreadSet.SetItemText(i,0,factoryName.c_str());
}

void ThreadLibraryDLG::OnBnClickedButtonDelthreadset()
{
	// TODO: 在此添加控件通知处理程序代码
	int iItem = m_ThreadSet.GetSelectionMark();
	if(iItem<0||iItem>=threadLibrary.size())
	{
		return;
	}
	threadLibrary.erase(threadLibrary.begin()+iItem);
	threadFactoryName.erase(threadFactoryName.begin()+iItem);

	UpdateListThreadSet();
	m_Thread.DeleteAllItems();
}

void ThreadLibraryDLG::OnNMClickListThreadSet(NMHDR *pNMHDR, LRESULT *pResult)
{
	//LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	NM_LISTVIEW *pNMListView=(NM_LISTVIEW *)pNMHDR;
	int nItem=pNMListView->iItem;
	
	int i,iItem;
	const int SizeOfStr=300;
	char str[SizeOfStr];
	if(nItem>=0&&nItem<threadLibrary.size()&&nItem!=selectedThreadSet)
	{
		sprintf_s(str,"%d",threadLibrary[nItem].size());
		m_ThreadNum.SetWindowText(CString(str));
		m_ThreadLib.SetWindowText(threadFactoryName[nItem].c_str());

		m_Thread.DeleteAllItems();
		for(i=0;i<threadLibrary[nItem].size();i++)
		{
			Thread &tempThread=threadLibrary[nItem][i];
			iItem=m_Thread.InsertItem(m_Thread.GetItemCount(),"",0);
			m_Thread.SetItemText(iItem,0,tempThread.threadName.c_str());
			sprintf_s(str,"%d,%d,%d",tempThread.colorR,tempThread.colorG,tempThread.colorB);
			m_Thread.SetItemText(iItem,1,str);
		}
		selectedThreadSet=nItem;
	}

	*pResult = 0;
}

void ThreadLibraryDLG::OnNMClickListThread(NMHDR *pNMHDR, LRESULT *pResult)
{
// 	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	NM_LISTVIEW *pNMListView=(NM_LISTVIEW *)pNMHDR;
	int nItem=pNMListView->iItem;

	if(nItem>=0&&nItem<threadLibrary[selectedThreadSet].size())
	{
		Thread &tempThread=threadLibrary[selectedThreadSet][nItem];
		m_ThreadName.SetWindowText(CString(tempThread.threadName.c_str()));

		int R=tempThread.colorR;
		int G=tempThread.colorG;
		int B=tempThread.colorB;
		CDC *pDC = GetDlgItem(IDC_THREADCOLOR)->GetDC();
		CRect rct;
		GetDlgItem(IDC_THREADCOLOR)->GetWindowRect(&rct);
		CBrush brs;
		brs.CreateSolidBrush(RGB(R,G,B));
		CRect picrct;
		picrct.top = 0;
		picrct.left = 0;
		picrct.bottom = rct.Height();
		picrct.right = rct.Width();
		pDC->FillRect(&picrct, &brs);

		ReleaseDC(pDC);
		pDC=NULL;
	}

	*pResult = 0;
}
