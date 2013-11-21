
// MainFrm.cpp : MainFrame 类的实现
//

#include "stdafx.h"
#include "CMagicCabsine.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// MainFrame

IMPLEMENT_DYNCREATE(MainFrame, CFrameWndEx)

const int  iMaxUserToolbars = 10;
const UINT uiFirstUserToolBarId = AFX_IDW_CONTROLBAR_FIRST + 40;
const UINT uiLastUserToolBarId = uiFirstUserToolBarId + iMaxUserToolbars - 1;

BEGIN_MESSAGE_MAP(MainFrame, CFrameWndEx)
	ON_WM_CREATE()
	ON_COMMAND(ID_VIEW_CUSTOMIZE, &MainFrame::OnViewCustomize)
	ON_REGISTERED_MESSAGE(AFX_WM_CREATETOOLBAR, &MainFrame::OnToolbarCreateNew)
	ON_COMMAND_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &MainFrame::OnApplicationLook)
	ON_UPDATE_COMMAND_UI_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &MainFrame::OnUpdateApplicationLook)
	ON_WM_NCPAINT()
	ON_COMMAND(ID_ShowLeftView, &MainFrame::OnShowLeftView)
	ON_COMMAND(ID_ShowRightView, &MainFrame::OnShowRightView)
	ON_COMMAND(ID_ShowBothView, &MainFrame::OnShowBothView)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 状态行指示器
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// MainFrame 构造/析构

MainFrame::MainFrame()
{
	// TODO: 在此添加成员初始化代码
	theApp.m_nAppLook = theApp.GetInt(_T("ApplicationLook"), ID_VIEW_APPLOOK_VS_2008);
	showViewType=BOTH_SHOW;
}

MainFrame::~MainFrame()
{
}

int MainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	//BOOL bNameValid;
	// 基于持久值设置视觉管理器和样式
	OnApplicationLook(theApp.m_nAppLook);

	if (!m_wndMenuBar.Create(this))
	{
		TRACE0("未能创建菜单栏\n");
		return -1;      // 未能创建
	}

	m_wndMenuBar.SetPaneStyle(m_wndMenuBar.GetPaneStyle() | CBRS_SIZE_DYNAMIC | CBRS_TOOLTIPS | CBRS_FLYBY);

	// 防止菜单栏在激活时获得焦点
	CMFCPopupMenu::SetForceMenuFocus(FALSE);

	//if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
	//	!m_wndToolBar.LoadToolBar(theApp.m_bHiColorIcons ? IDR_MAINFRAME_256 : IDR_MAINFRAME))
	//{
	//	TRACE0("未能创建工具栏\n");
	//	return -1;      // 未能创建
	//}

	//if (!m_wndToolBar_splitRegion.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
	//	!m_wndToolBar_splitRegion.LoadToolBar(theApp.m_bHiColorIcons ? IDR_SPLIT_MODIFY : IDR_SPLIT_MODIFY))
	//{
	//	TRACE0("未能创建工具栏\n");
	//	return -1;      // 未能创建
	//}

// 	//建立分割标记菜单栏,以下每个m_wndToolBar出现的地方都仿写一个m_wndToolBar_splitMark
// 	if (!m_wndToolBar_splitMark.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
// 		!m_wndToolBar_splitMark.LoadToolBar(IDR_TOOLBAR1))
// 	{
// 		TRACE0("未能创建工具栏\n");
// 		return -1;      // 未能创建
// 	}


	if (!m_wndToolBar_upside.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar_upside.LoadToolBar(theApp.m_bHiColorIcons ? IDR_TOOLBAR_UPSIDE : IDR_TOOLBAR_UPSIDE))
	{
		TRACE0("未能创建工具栏\n");
		return -1;      // 未能创建
	}

	if (!m_wndToolBar_downside.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar_downside.LoadToolBar(theApp.m_bHiColorIcons ? IDR_TOOLBAR_DOWNSIDE : IDR_TOOLBAR_DOWNSIDE))
	{
		TRACE0("未能创建工具栏\n");
		return -1;      // 未能创建
	}

	/*CString strToolBarName;
	bNameValid = strToolBarName.LoadString(IDS_TOOLBAR_STANDARD);
	ASSERT(bNameValid);
	m_wndToolBar.SetWindowText(strToolBarName);

	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);
	m_wndToolBar.EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);*/

// 	CString strToolBarName_splitMark;
// 	bNameValid = strToolBarName_splitMark.LoadString(IDS_TOOLBAR1);
// 	ASSERT(bNameValid);
// 	m_wndToolBar_splitMark.SetWindowText(strToolBarName_splitMark);

	// 允许用户定义的工具栏操作:
	InitUserToolbars(NULL, uiFirstUserToolBarId, uiLastUserToolBarId);

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("未能创建状态栏\n");
		return -1;      // 未能创建
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// TODO: 如果您不希望工具栏和菜单栏可停靠，请删除这五行
	/*m_wndMenuBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndToolBar_splitRegion.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);*/
	DockPane(&m_wndMenuBar);
	//DockPane(&m_wndToolBar);
	//	DockPane(&m_wndToolBar_splitRegion);
	DockPane(&m_wndToolBar_upside);
	DockPane(&m_wndToolBar_downside);

	

	// 启用 Visual Studio 2005 样式停靠窗口行为
	CDockingManager::SetDockingMode(DT_SMART);
	// 启用 Visual Studio 2005 样式停靠窗口自动隐藏行为
	EnableAutoHidePanes(CBRS_ALIGN_ANY);

	//// 创建停靠窗口
	//if (!CreateDockingWindows())
	//{
	//	TRACE0("未能创建停靠窗口\n");
	//	return -1;
	//}

	//m_wndProperties.EnableDocking(CBRS_ALIGN_ANY);
	//DockPane(&m_wndProperties);


	// 启用工具栏和停靠窗口菜单替换
//	EnablePaneMenu(TRUE, ID_VIEW_CUSTOMIZE, strCustomize, ID_VIEW_TOOLBAR);

	// 启用快速(按住 Alt 拖动)工具栏自定义
	CMFCToolBar::EnableQuickCustomization();

	//if (CMFCToolBar::GetUserImages() == NULL)
	//{
	//	// 加载用户定义的工具栏图像
	//	if (m_UserImages.Load(_T(".\\UserImages.bmp")))
	//	{
	//		CMFCToolBar::SetUserImages(&m_UserImages);
	//	}
	//}

	// 启用菜单个性化(最近使用的命令)
	// TODO: 定义您自己的基本命令，确保每个下拉菜单至少有一个基本命令。
	CList<UINT, UINT> lstBasicCommands;

	lstBasicCommands.AddTail(ID_FILE_NEW);
	lstBasicCommands.AddTail(ID_FILE_OPEN);
	lstBasicCommands.AddTail(ID_FILE_SAVE);
	lstBasicCommands.AddTail(ID_FILE_PRINT);
	lstBasicCommands.AddTail(ID_APP_EXIT);
	lstBasicCommands.AddTail(ID_EDIT_CUT);
	lstBasicCommands.AddTail(ID_EDIT_PASTE);
	lstBasicCommands.AddTail(ID_EDIT_UNDO);
	lstBasicCommands.AddTail(ID_APP_ABOUT);
	lstBasicCommands.AddTail(ID_VIEW_STATUS_BAR);
	lstBasicCommands.AddTail(ID_VIEW_TOOLBAR);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2003);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_VS_2005);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2007_BLUE);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2007_SILVER);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2007_BLACK);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2007_AQUA);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_WINDOWS_7);

	CMFCToolBar::SetBasicCommands(lstBasicCommands);

	return 0;
}

BOOL MainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWndEx::PreCreateWindow(cs) )
		return FALSE;
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return TRUE;
}

BOOL MainFrame::CreateDockingWindows()
{
	BOOL bNameValid;
	// 创建属性窗口
	CString strPropertiesWnd;
	bNameValid = strPropertiesWnd.LoadString(IDS_PROPERTIES_WND);
	ASSERT(bNameValid);
	if (!m_wndProperties.Create(strPropertiesWnd, this, CRect(0, 0, 200, 200), TRUE, ID_VIEW_PROPERTIESWND, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_RIGHT | CBRS_FLOAT_MULTI))
	{
		TRACE0("未能创建“属性”窗口\n");
		return FALSE; // 未能创建
	}

	SetDockingWindowIcons(theApp.m_bHiColorIcons);
	return TRUE;
}

void MainFrame::SetDockingWindowIcons(BOOL bHiColorIcons)
{
	HICON hPropertiesBarIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_PROPERTIES_WND_HC : IDI_PROPERTIES_WND), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
	m_wndProperties.SetIcon(hPropertiesBarIcon, FALSE);

}

// MainFrame 诊断

#ifdef _DEBUG
void MainFrame::AssertValid() const
{
	CFrameWndEx::AssertValid();
}

void MainFrame::Dump(CDumpContext& dc) const
{
	CFrameWndEx::Dump(dc);
}
#endif //_DEBUG


// MainFrame 消息处理程序

void MainFrame::OnViewCustomize()
{
	CMFCToolBarsCustomizeDialog* pDlgCust = new CMFCToolBarsCustomizeDialog(this, TRUE /* 扫描菜单*/);
	pDlgCust->EnableUserDefinedToolbars();
	pDlgCust->Create();
}

LRESULT MainFrame::OnToolbarCreateNew(WPARAM wp,LPARAM lp)
{
	LRESULT lres = CFrameWndEx::OnToolbarCreateNew(wp,lp);
	if (lres == 0)
	{
		return 0;
	}

	CMFCToolBar* pUserToolbar = (CMFCToolBar*)lres;
	ASSERT_VALID(pUserToolbar);

	BOOL bNameValid;
	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);

	pUserToolbar->EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
	return lres;
}

void MainFrame::OnApplicationLook(UINT id)
{
	CWaitCursor wait;

	theApp.m_nAppLook = id;

	switch (theApp.m_nAppLook)
	{
	case ID_VIEW_APPLOOK_WIN_2000:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManager));
		break;

	case ID_VIEW_APPLOOK_OFF_XP:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOfficeXP));
		break;

	case ID_VIEW_APPLOOK_WIN_XP:
		CMFCVisualManagerWindows::m_b3DTabsXPTheme = TRUE;
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));
		break;

	case ID_VIEW_APPLOOK_OFF_2003:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2003));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	case ID_VIEW_APPLOOK_VS_2005:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2005));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	case ID_VIEW_APPLOOK_VS_2008:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2008));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	case ID_VIEW_APPLOOK_WINDOWS_7:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows7));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	default:
		switch (theApp.m_nAppLook)
		{
		case ID_VIEW_APPLOOK_OFF_2007_BLUE:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_LunaBlue);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_BLACK:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_ObsidianBlack);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_SILVER:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Silver);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_AQUA:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Aqua);
			break;
		}

		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2007));
		CDockingManager::SetDockingMode(DT_SMART);
	}

	RedrawWindow(NULL, NULL, RDW_ALLCHILDREN | RDW_INVALIDATE | RDW_UPDATENOW | RDW_FRAME | RDW_ERASE);

	theApp.WriteInt(_T("ApplicationLook"), theApp.m_nAppLook);
}

void MainFrame::OnUpdateApplicationLook(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio(theApp.m_nAppLook == pCmdUI->m_nID);
}

BOOL MainFrame::LoadFrame(UINT nIDResource, DWORD dwDefaultStyle, CWnd* pParentWnd, CCreateContext* pContext) 
{
	// 基类将执行真正的工作

	if (!CFrameWndEx::LoadFrame(nIDResource, dwDefaultStyle, pParentWnd, pContext))
	{
		return FALSE;
	}


	// 为所有用户工具栏启用自定义按钮
	BOOL bNameValid;
	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);

	for (int i = 0; i < iMaxUserToolbars; i ++)
	{
		CMFCToolBar* pUserToolbar = GetUserToolBarByIndex(i);
		if (pUserToolbar != NULL)
		{
			pUserToolbar->EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
		}
	}

	return TRUE;
}



BOOL MainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// TODO: 在此添加专用代码和/或调用基类

	CRect rect;
	GetClientRect(&rect);
	m_WndSplitter.CreateStatic(this,1,2);       //建立外层架构，1行2列 

	//创建左边的视图
	m_WndSplitter.CreateView(
		0, 0,
		RUNTIME_CLASS(CMagicCabsineLeftView),
		CSize(rect.Width()/2, rect.Height()),
		pContext
		);
	//创建右边的视图
	m_WndSplitter.CreateView(
		0, 1,
		RUNTIME_CLASS(CMagicCabsineRightView),
		CSize(rect.Width()/2,rect.Height()),
		pContext
		);

	/*下面是标签和所使用的View之间的对应关系
	//原图     1 CMagicCabsineDisplayView
	//全局特征 3 CMagicCabsineDisplayView
	//分割交互 2 CMagicCabsineInteractiveView
	//分割结果 1 CMagicCabsineDisplayView
	//局部特征 1 CMagicCabsineDisplayView
	*/

	//按照以上对应关系添加左边的标签页
	CMagicCabsineLeftView* m_leftView=(CMagicCabsineLeftView *)m_WndSplitter.GetPane(0,0);
	m_leftView->GetTabControl().EnableTabSwap(FALSE);//禁止标签页拖动
	m_leftView->AddView(RUNTIME_CLASS(CMagicCabsineDisplayView),CString("原图"));
	m_leftView->AddView(RUNTIME_CLASS(CMagicCabsineDisplayView),CString("CLD"));
	m_leftView->AddView(RUNTIME_CLASS(CMagicCabsineDisplayView),CString("矢量场"));
	m_leftView->AddView(RUNTIME_CLASS(CMagicCabsineDisplayView),CString("显著性"));
	m_leftView->AddView(RUNTIME_CLASS(CMagicCabsineInteractiveView),CString("分割"));
	m_leftView->AddView(RUNTIME_CLASS(CMagicCabsineRegionModifyView),CString("区域轮廓"));
	m_leftView->AddView(RUNTIME_CLASS(CMagicCabsineDisplayView),CString("主色调"));
	m_leftView->AddView(RUNTIME_CLASS(CMagicCabsineDisplayView),CString("前背景"));
	m_leftView->AddView(RUNTIME_CLASS(CMagicCabsineDisplayView),CString("平均色"));

	//开始时只显示原图一个标签页,隐藏其它标签页
	m_leftView->GetTabControl().ShowTab(1,FALSE);
	m_leftView->GetTabControl().ShowTab(2,FALSE);
	m_leftView->GetTabControl().ShowTab(3,FALSE);
	m_leftView->GetTabControl().ShowTab(4,FALSE);
	m_leftView->GetTabControl().ShowTab(5,FALSE);
	m_leftView->GetTabControl().ShowTab(6,FALSE);
	m_leftView->GetTabControl().ShowTab(7,FALSE);
	m_leftView->GetTabControl().ShowTab(8,FALSE);

	//添加右边的标签页,目前只有一个
	CMagicCabsineRightView* m_rightView=(CMagicCabsineRightView *)m_WndSplitter.GetPane(0,1);
	m_rightView->GetTabControl().EnableTabSwap(FALSE);//禁止标签页拖动
	m_rightView->AddView(RUNTIME_CLASS(CMagicCabsineDisplayView),CString("模拟结果"));
	//m_rightView->AddView(RUNTIME_CLASS(CMagicCabsineSimulateView),CString("铺底层"));
	//m_rightView->AddView(RUNTIME_CLASS(CMagicCabsineSimulateView),CString("粗绣层"));
	//m_rightView->AddView(RUNTIME_CLASS(CMagicCabsineSimulateView),CString("精绣层"));
	//m_rightView->AddView(RUNTIME_CLASS(CMagicCabsineSimulateView),CString("第4层"));
	//m_rightView->AddView(RUNTIME_CLASS(CMagicCabsineSimulateView),CString("第5层"));

	m_rightView->AddView(RUNTIME_CLASS(CMagicCabsineSimulateView),CString("铺底层"));
	int tabNum = m_rightView->GetTabControl().GetTabsNum();
	m_rightView->SetActiveView(tabNum - 1);
	CMagicCabsineSimulateView* view = (CMagicCabsineSimulateView*)m_rightView->GetActiveView();
	view->tabID = tabNum - 1;

	m_rightView->AddView(RUNTIME_CLASS(CMagicCabsineSimulateView),CString("粗绣层"));
	tabNum = m_rightView->GetTabControl().GetTabsNum();
	m_rightView->SetActiveView(tabNum - 1);
	view = (CMagicCabsineSimulateView*)m_rightView->GetActiveView();
	view->tabID = tabNum - 1;

	m_rightView->AddView(RUNTIME_CLASS(CMagicCabsineSimulateView),CString("精绣层"));
	tabNum = m_rightView->GetTabControl().GetTabsNum();
	m_rightView->SetActiveView(tabNum - 1);
	view = (CMagicCabsineSimulateView*)m_rightView->GetActiveView();
	view->tabID = tabNum - 1;

	m_rightView->AddView(RUNTIME_CLASS(CMagicCabsineSimulateView),CString("第4层"));
	tabNum = m_rightView->GetTabControl().GetTabsNum();
	m_rightView->SetActiveView(tabNum - 1);
	view = (CMagicCabsineSimulateView*)m_rightView->GetActiveView();
	view->tabID = tabNum - 1;

	m_rightView->AddView(RUNTIME_CLASS(CMagicCabsineSimulateView),CString("第5层"));
	tabNum = m_rightView->GetTabControl().GetTabsNum();
	m_rightView->SetActiveView(tabNum - 1);
	view = (CMagicCabsineSimulateView*)m_rightView->GetActiveView();
	view->tabID = tabNum - 1;

	//开始时只显示模拟叠加结果一个标签页,隐藏其它标签页
	m_rightView->GetTabControl().ShowTab(1,FALSE);
	m_rightView->GetTabControl().ShowTab(2,FALSE);
	m_rightView->GetTabControl().ShowTab(3,FALSE);
	m_rightView->GetTabControl().ShowTab(4,FALSE);
	m_rightView->GetTabControl().ShowTab(5,FALSE);
	
	return TRUE;
//	return CFrameWndEx::OnCreateClient(lpcs, pContext);
}


void MainFrame::OnNcPaint()
{
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CFrameWndEx::OnNcPaint()
	CRect rect;
	GetWindowRect(&rect);
	if(m_WndSplitter)  // m_bSplitterCreated set in OnCreateClient
	{
		switch (showViewType)
		{
		case LEFT_SHOW:
			m_WndSplitter.SetColumnInfo(0, rect.Width(), 10);
			break;
		case RIGHT_SHOW:
			m_WndSplitter.SetColumnInfo(0, 0, 0);
			break;
		case BOTH_SHOW:
			m_WndSplitter.SetColumnInfo(0, rect.Width()/2, 10);
			m_WndSplitter.SetColumnInfo(1, rect.Width()/2, 10);
			break;
		default:
			m_WndSplitter.SetColumnInfo(0, rect.Width()/2, 10);
			m_WndSplitter.SetColumnInfo(1, rect.Width()/2, 10);
			break;
		}
		m_WndSplitter.RecalcLayout();
	}

	CFrameWndEx::OnNcPaint();
}


void MainFrame::OnShowLeftView()
{
	// TODO: 在此添加命令处理程序代码
	if(showViewType==LEFT_SHOW)
	{
		return;
	}
	CRect rect;
	GetWindowRect(&rect);
	if(m_WndSplitter)  // m_bSplitterCreated set in OnCreateClient
	{
		m_WndSplitter.SetColumnInfo(0, rect.Width(), 10);
		m_WndSplitter.RecalcLayout();
	}
	showViewType=LEFT_SHOW;
}


void MainFrame::OnShowRightView()
{
	// TODO: 在此添加命令处理程序代码
	if(showViewType==RIGHT_SHOW)
	{
		return;
	}
	CRect rect;
	GetWindowRect(&rect);
	if(m_WndSplitter)  // m_bSplitterCreated set in OnCreateClient
	{
		m_WndSplitter.SetColumnInfo(0, 0, 0);
		m_WndSplitter.RecalcLayout();
	}
	showViewType=RIGHT_SHOW;
}


void MainFrame::OnShowBothView()
{
	// TODO: 在此添加命令处理程序代码
	if(showViewType==BOTH_SHOW)
	{
		return;
	}
	CRect rect;
	GetWindowRect(&rect);
	if(m_WndSplitter)  // m_bSplitterCreated set in OnCreateClient
	{
		m_WndSplitter.SetColumnInfo(0, rect.Width()/2, 10);
		m_WndSplitter.SetColumnInfo(1, rect.Width()/2, 10);
		m_WndSplitter.RecalcLayout();
	}
	showViewType=BOTH_SHOW;
}
