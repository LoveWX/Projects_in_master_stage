
// CMagicCabsine.cpp : 定义应用程序的类行为。
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
	// 基于文件的标准文档命令
	ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
	// 标准打印设置命令
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinAppEx::OnFilePrintSetup)
END_MESSAGE_MAP()


// CMagicCabsineApp 构造

CMagicCabsineApp::CMagicCabsineApp()
{
	m_bHiColorIcons = TRUE;

	// 支持重新启动管理器
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// 如果应用程序是利用公共语言运行时支持(/clr)构建的，则:
	//     1) 必须有此附加设置，“重新启动管理器”支持才能正常工作。
	//     2) 在您的项目中，您必须按照生成顺序向 System.Windows.Forms 添加引用。
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: 将以下应用程序 ID 字符串替换为唯一的 ID 字符串；建议的字符串格式
	//为 CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("CMagicCabsine.AppID.NoVersion"));

	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}

// 唯一的一个 CMagicCabsineApp 对象

CMagicCabsineApp theApp;


// CMagicCabsineApp 初始化

BOOL CMagicCabsineApp::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();


	// 初始化 OLE 库
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction(FALSE);

	// 使用 RichEdit 控件需要  AfxInitRichEdit2()	
	// AfxInitRichEdit2();

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));
	LoadStdProfileSettings(4);  // 加载标准 INI 文件选项(包括 MRU)


	InitContextMenuManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	// 注册应用程序的文档模板。文档模板
	// 将用作文档、框架窗口和视图之间的连接
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CMagicCabsineDoc),
		RUNTIME_CLASS(MainFrame),       // 主 SDI 框架窗口
		RUNTIME_CLASS(CMagicCabsineView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);


	// 分析标准 shell 命令、DDE、打开文件操作的命令行
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// 启用“DDE 执行”
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);


	// 调度在命令行中指定的命令。如果
	// 用 /RegServer、/Register、/Unregserver 或 /Unregister 启动应用程序，则返回 FALSE。
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// 唯一的一个窗口已初始化，因此显示它并对其进行更新
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	// 仅当具有后缀时才调用 DragAcceptFiles
	//  在 SDI 应用程序中，这应在 ProcessShellCommand 之后发生
	// 启用拖/放
	m_pMainWnd->DragAcceptFiles();

	//m_pMainWnd->SetWindowText(CString("MagicCabsine"));
	SetTitleText(CString("MagicCabsine"));

	//设置配置文件夹的相对路径
// 	string tempPath=string(_pgmptr);//_pgmptr是.exe所在的绝对路径
// 	int myPos=tempPath.length()-1;
// 	for(;myPos>=0&&tempPath[myPos]!='\\';myPos--);//两次for循环是为了进入当前的默认路径下
// 	for(myPos--;myPos>=0&&tempPath[myPos]!='\\';myPos--);
// 	defaultPath=tempPath.substr(0,myPos)+"\\CMagicCabsine\\";

	//发布版的文件夹相对路径与调试版本不相同
	string tempPath=string(_pgmptr);//_pgmptr是.exe所在的绝对路径
	int myPos=tempPath.length()-1;
	for(;myPos>=0&&tempPath[myPos]!='\\';myPos--);
	defaultPath=tempPath.substr(0,myPos+1);

	CheckFilesAndFolders();

	return TRUE;
}

int CMagicCabsineApp::ExitInstance()
{
	//TODO: 处理可能已添加的附加资源
	AfxOleTerm(FALSE);

	return CWinAppEx::ExitInstance();
}

// CMagicCabsineApp 消息处理程序


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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

// 用于运行对话框的应用程序命令
void CMagicCabsineApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CMagicCabsineApp 自定义加载/保存方法

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
	//上面定义的属性可以省略。 直接return ::CreateDirectory( path, NULL); 即可
	return ::CreateDirectory( strPath, &attrib);
}

void CMagicCabsineApp::CheckFilesAndFolders()
{
	CString theDefaultPath=defaultPath.c_str();

	CString thePath;

	//创建临时文件夹temp
	thePath=theDefaultPath+"temp\\";
	CreateFolder(thePath);

	//创建绣线库文件夹ThreadLibrary
	thePath=theDefaultPath+"ThreadLibrary\\";
	CreateFolder(thePath);

	//创建配置表文件夹ConfigFile
	thePath=theDefaultPath+"ConfigFile\\";
	CreateFolder(thePath);

	//创建工程文件夹Projects
	thePath=theDefaultPath+"Projects\\";
	CreateFolder(thePath);

	//创建图片库文件夹ImageLibrary和其中的子文件夹
	thePath=theDefaultPath+"ImageLibrary\\";
	CreateFolder(thePath);
	CreateFolder(thePath+"human\\");
	CreateFolder(thePath+"scenery\\");
	CreateFolder(thePath+"animal\\");
	CreateFolder(thePath+"custom\\");
	CreateFolder(thePath+"unclassified\\");

	//创建图片库文件夹PropertyLibrary和其中的子文件夹
	thePath=theDefaultPath+"PropertyLibrary\\";
	CreateFolder(thePath);
	CreateFolder(thePath+"human\\");
	CreateFolder(thePath+"scenery\\");
	CreateFolder(thePath+"animal\\");
	CreateFolder(thePath+"custom\\");
	CreateFolder(thePath+"unclassified\\");
}

// CMagicCabsineApp 消息处理程序

void CMagicCabsineApp::SetTitleText(CString titleCStr/* ="MagicCabsine" */)
{
	m_pMainWnd->SetWindowText(titleCStr);
}
