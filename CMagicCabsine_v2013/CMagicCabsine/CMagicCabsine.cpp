
// CMagicCabsine.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "CMagicCabsine.h"
#include "MainFrm.h"

#include "CMagicCabsineDoc.h"
#include "CMagicCabsineView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMagicCabsineApp

BEGIN_MESSAGE_MAP(CMagicCabsineApp, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CMagicCabsineApp::OnAppAbout)
	// �����ļ��ı�׼�ĵ�����
	ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
	// ��׼��ӡ��������
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinAppEx::OnFilePrintSetup)
END_MESSAGE_MAP()


// CMagicCabsineApp ����

CMagicCabsineApp::CMagicCabsineApp()
{
	m_bHiColorIcons = TRUE;

	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// ���Ӧ�ó��������ù�����������ʱ֧��(/clr)�����ģ���:
	//     1) �����д˸������ã�������������������֧�ֲ�������������
	//     2) ��������Ŀ�У������밴������˳���� System.Windows.Forms ������á�
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: ������Ӧ�ó��� ID �ַ����滻ΪΨһ�� ID �ַ�����������ַ�����ʽ
	//Ϊ CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("CMagicCabsine.AppID.NoVersion"));

	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}

// Ψһ��һ�� CMagicCabsineApp ����

CMagicCabsineApp theApp;


// CMagicCabsineApp ��ʼ��

BOOL CMagicCabsineApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();


	// ��ʼ�� OLE ��
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction(FALSE);

	// ʹ�� RichEdit �ؼ���Ҫ  AfxInitRichEdit2()	
	// AfxInitRichEdit2();

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));
	LoadStdProfileSettings(4);  // ���ر�׼ INI �ļ�ѡ��(���� MRU)


	InitContextMenuManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	// ע��Ӧ�ó�����ĵ�ģ�塣�ĵ�ģ��
	// �������ĵ�����ܴ��ں���ͼ֮�������
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CMagicCabsineDoc),
		RUNTIME_CLASS(MainFrame),       // �� SDI ��ܴ���
		RUNTIME_CLASS(CMagicCabsineView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);


	// ������׼ shell ���DDE�����ļ�������������
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// ���á�DDE ִ�С�
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);


	// ��������������ָ����������
	// �� /RegServer��/Register��/Unregserver �� /Unregister ����Ӧ�ó����򷵻� FALSE��
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// Ψһ��һ�������ѳ�ʼ���������ʾ����������и���
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	// �������к�׺ʱ�ŵ��� DragAcceptFiles
	//  �� SDI Ӧ�ó����У���Ӧ�� ProcessShellCommand ֮����
	// ������/��
	m_pMainWnd->DragAcceptFiles();

	//m_pMainWnd->SetWindowText(CString("MagicCabsine"));
	SetTitleText(CString("MagicCabsine"));

	//���������ļ��е����·��
// 	string tempPath=string(_pgmptr);//_pgmptr��.exe���ڵľ���·��
// 	int myPos=tempPath.length()-1;
// 	for(;myPos>=0&&tempPath[myPos]!='\\';myPos--);//����forѭ����Ϊ�˽��뵱ǰ��Ĭ��·����
// 	for(myPos--;myPos>=0&&tempPath[myPos]!='\\';myPos--);
// 	defaultPath=tempPath.substr(0,myPos)+"\\CMagicCabsine\\";

	//��������ļ������·������԰汾����ͬ
	string tempPath=string(_pgmptr);//_pgmptr��.exe���ڵľ���·��
	int myPos=tempPath.length()-1;
	for(;myPos>=0&&tempPath[myPos]!='\\';myPos--);
	defaultPath=tempPath.substr(0,myPos+1);

	CheckFilesAndFolders();

	return TRUE;
}

int CMagicCabsineApp::ExitInstance()
{
	//TODO: �����������ӵĸ�����Դ
	AfxOleTerm(FALSE);

	return CWinAppEx::ExitInstance();
}

// CMagicCabsineApp ��Ϣ�������


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
public:
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// �������жԻ����Ӧ�ó�������
void CMagicCabsineApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CMagicCabsineApp �Զ������/���淽��

void CMagicCabsineApp::PreLoadState()
{
	BOOL bNameValid;
	CString strName;
	bNameValid = strName.LoadString(IDS_EDIT_MENU);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EDIT);
}

void CMagicCabsineApp::LoadCustomState()
{
}

void CMagicCabsineApp::SaveCustomState()
{
}

BOOL CMagicCabsineApp::CreateFolder(CString strPath)
{
	SECURITY_ATTRIBUTES attrib;
	attrib.bInheritHandle = FALSE;
	attrib.lpSecurityDescriptor = NULL;
	attrib.nLength =sizeof(SECURITY_ATTRIBUTES);
	//���涨������Կ���ʡ�ԡ� ֱ��return ::CreateDirectory( path, NULL); ����
	return ::CreateDirectory( strPath, &attrib);
}

void CMagicCabsineApp::CheckFilesAndFolders()
{
	CString theDefaultPath=defaultPath.c_str();

	CString thePath;

	//������ʱ�ļ���temp
	thePath=theDefaultPath+"temp\\";
	CreateFolder(thePath);

	//�������߿��ļ���ThreadLibrary
	thePath=theDefaultPath+"ThreadLibrary\\";
	CreateFolder(thePath);

	//�������ñ��ļ���ConfigFile
	thePath=theDefaultPath+"ConfigFile\\";
	CreateFolder(thePath);

	//���������ļ���Projects
	thePath=theDefaultPath+"Projects\\";
	CreateFolder(thePath);

	//����ͼƬ���ļ���ImageLibrary�����е����ļ���
	thePath=theDefaultPath+"ImageLibrary\\";
	CreateFolder(thePath);
	CreateFolder(thePath+"human\\");
	CreateFolder(thePath+"scenery\\");
	CreateFolder(thePath+"animal\\");
	CreateFolder(thePath+"custom\\");
	CreateFolder(thePath+"unclassified\\");

	//����ͼƬ���ļ���PropertyLibrary�����е����ļ���
	thePath=theDefaultPath+"PropertyLibrary\\";
	CreateFolder(thePath);
	CreateFolder(thePath+"human\\");
	CreateFolder(thePath+"scenery\\");
	CreateFolder(thePath+"animal\\");
	CreateFolder(thePath+"custom\\");
	CreateFolder(thePath+"unclassified\\");
}

// CMagicCabsineApp ��Ϣ�������

void CMagicCabsineApp::SetTitleText(CString titleCStr/* ="MagicCabsine" */)
{
	m_pMainWnd->SetWindowText(titleCStr);
}
