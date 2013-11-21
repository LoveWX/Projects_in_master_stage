
// MainFrm.cpp : MainFrame ���ʵ��
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
	ID_SEPARATOR,           // ״̬��ָʾ��
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// MainFrame ����/����

MainFrame::MainFrame()
{
	// TODO: �ڴ���ӳ�Ա��ʼ������
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
	// ���ڳ־�ֵ�����Ӿ�����������ʽ
	OnApplicationLook(theApp.m_nAppLook);

	if (!m_wndMenuBar.Create(this))
	{
		TRACE0("δ�ܴ����˵���\n");
		return -1;      // δ�ܴ���
	}

	m_wndMenuBar.SetPaneStyle(m_wndMenuBar.GetPaneStyle() | CBRS_SIZE_DYNAMIC | CBRS_TOOLTIPS | CBRS_FLYBY);

	// ��ֹ�˵����ڼ���ʱ��ý���
	CMFCPopupMenu::SetForceMenuFocus(FALSE);

	//if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
	//	!m_wndToolBar.LoadToolBar(theApp.m_bHiColorIcons ? IDR_MAINFRAME_256 : IDR_MAINFRAME))
	//{
	//	TRACE0("δ�ܴ���������\n");
	//	return -1;      // δ�ܴ���
	//}

	//if (!m_wndToolBar_splitRegion.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
	//	!m_wndToolBar_splitRegion.LoadToolBar(theApp.m_bHiColorIcons ? IDR_SPLIT_MODIFY : IDR_SPLIT_MODIFY))
	//{
	//	TRACE0("δ�ܴ���������\n");
	//	return -1;      // δ�ܴ���
	//}

// 	//�����ָ��ǲ˵���,����ÿ��m_wndToolBar���ֵĵط�����дһ��m_wndToolBar_splitMark
// 	if (!m_wndToolBar_splitMark.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
// 		!m_wndToolBar_splitMark.LoadToolBar(IDR_TOOLBAR1))
// 	{
// 		TRACE0("δ�ܴ���������\n");
// 		return -1;      // δ�ܴ���
// 	}


	if (!m_wndToolBar_upside.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar_upside.LoadToolBar(theApp.m_bHiColorIcons ? IDR_TOOLBAR_UPSIDE : IDR_TOOLBAR_UPSIDE))
	{
		TRACE0("δ�ܴ���������\n");
		return -1;      // δ�ܴ���
	}

	if (!m_wndToolBar_downside.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar_downside.LoadToolBar(theApp.m_bHiColorIcons ? IDR_TOOLBAR_DOWNSIDE : IDR_TOOLBAR_DOWNSIDE))
	{
		TRACE0("δ�ܴ���������\n");
		return -1;      // δ�ܴ���
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

	// �����û�����Ĺ���������:
	InitUserToolbars(NULL, uiFirstUserToolBarId, uiLastUserToolBarId);

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("δ�ܴ���״̬��\n");
		return -1;      // δ�ܴ���
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// TODO: �������ϣ���������Ͳ˵�����ͣ������ɾ��������
	/*m_wndMenuBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndToolBar_splitRegion.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);*/
	DockPane(&m_wndMenuBar);
	//DockPane(&m_wndToolBar);
	//	DockPane(&m_wndToolBar_splitRegion);
	DockPane(&m_wndToolBar_upside);
	DockPane(&m_wndToolBar_downside);

	

	// ���� Visual Studio 2005 ��ʽͣ��������Ϊ
	CDockingManager::SetDockingMode(DT_SMART);
	// ���� Visual Studio 2005 ��ʽͣ�������Զ�������Ϊ
	EnableAutoHidePanes(CBRS_ALIGN_ANY);

	//// ����ͣ������
	//if (!CreateDockingWindows())
	//{
	//	TRACE0("δ�ܴ���ͣ������\n");
	//	return -1;
	//}

	//m_wndProperties.EnableDocking(CBRS_ALIGN_ANY);
	//DockPane(&m_wndProperties);


	// ���ù�������ͣ�����ڲ˵��滻
//	EnablePaneMenu(TRUE, ID_VIEW_CUSTOMIZE, strCustomize, ID_VIEW_TOOLBAR);

	// ���ÿ���(��ס Alt �϶�)�������Զ���
	CMFCToolBar::EnableQuickCustomization();

	//if (CMFCToolBar::GetUserImages() == NULL)
	//{
	//	// �����û�����Ĺ�����ͼ��
	//	if (m_UserImages.Load(_T(".\\UserImages.bmp")))
	//	{
	//		CMFCToolBar::SetUserImages(&m_UserImages);
	//	}
	//}

	// ���ò˵����Ի�(���ʹ�õ�����)
	// TODO: �������Լ��Ļ������ȷ��ÿ�������˵�������һ���������
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
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return TRUE;
}

BOOL MainFrame::CreateDockingWindows()
{
	BOOL bNameValid;
	// �������Դ���
	CString strPropertiesWnd;
	bNameValid = strPropertiesWnd.LoadString(IDS_PROPERTIES_WND);
	ASSERT(bNameValid);
	if (!m_wndProperties.Create(strPropertiesWnd, this, CRect(0, 0, 200, 200), TRUE, ID_VIEW_PROPERTIESWND, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_RIGHT | CBRS_FLOAT_MULTI))
	{
		TRACE0("δ�ܴ��������ԡ�����\n");
		return FALSE; // δ�ܴ���
	}

	SetDockingWindowIcons(theApp.m_bHiColorIcons);
	return TRUE;
}

void MainFrame::SetDockingWindowIcons(BOOL bHiColorIcons)
{
	HICON hPropertiesBarIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_PROPERTIES_WND_HC : IDI_PROPERTIES_WND), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
	m_wndProperties.SetIcon(hPropertiesBarIcon, FALSE);

}

// MainFrame ���

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


// MainFrame ��Ϣ�������

void MainFrame::OnViewCustomize()
{
	CMFCToolBarsCustomizeDialog* pDlgCust = new CMFCToolBarsCustomizeDialog(this, TRUE /* ɨ��˵�*/);
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
	// ���ཫִ�������Ĺ���

	if (!CFrameWndEx::LoadFrame(nIDResource, dwDefaultStyle, pParentWnd, pContext))
	{
		return FALSE;
	}


	// Ϊ�����û������������Զ��尴ť
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
	// TODO: �ڴ����ר�ô����/����û���

	CRect rect;
	GetClientRect(&rect);
	m_WndSplitter.CreateStatic(this,1,2);       //�������ܹ���1��2�� 

	//������ߵ���ͼ
	m_WndSplitter.CreateView(
		0, 0,
		RUNTIME_CLASS(CMagicCabsineLeftView),
		CSize(rect.Width()/2, rect.Height()),
		pContext
		);
	//�����ұߵ���ͼ
	m_WndSplitter.CreateView(
		0, 1,
		RUNTIME_CLASS(CMagicCabsineRightView),
		CSize(rect.Width()/2,rect.Height()),
		pContext
		);

	/*�����Ǳ�ǩ����ʹ�õ�View֮��Ķ�Ӧ��ϵ
	//ԭͼ     1 CMagicCabsineDisplayView
	//ȫ������ 3 CMagicCabsineDisplayView
	//�ָ�� 2 CMagicCabsineInteractiveView
	//�ָ��� 1 CMagicCabsineDisplayView
	//�ֲ����� 1 CMagicCabsineDisplayView
	*/

	//�������϶�Ӧ��ϵ�����ߵı�ǩҳ
	CMagicCabsineLeftView* m_leftView=(CMagicCabsineLeftView *)m_WndSplitter.GetPane(0,0);
	m_leftView->GetTabControl().EnableTabSwap(FALSE);//��ֹ��ǩҳ�϶�
	m_leftView->AddView(RUNTIME_CLASS(CMagicCabsineDisplayView),CString("ԭͼ"));
	m_leftView->AddView(RUNTIME_CLASS(CMagicCabsineDisplayView),CString("CLD"));
	m_leftView->AddView(RUNTIME_CLASS(CMagicCabsineDisplayView),CString("ʸ����"));
	m_leftView->AddView(RUNTIME_CLASS(CMagicCabsineDisplayView),CString("������"));
	m_leftView->AddView(RUNTIME_CLASS(CMagicCabsineInteractiveView),CString("�ָ�"));
	m_leftView->AddView(RUNTIME_CLASS(CMagicCabsineRegionModifyView),CString("��������"));
	m_leftView->AddView(RUNTIME_CLASS(CMagicCabsineDisplayView),CString("��ɫ��"));
	m_leftView->AddView(RUNTIME_CLASS(CMagicCabsineDisplayView),CString("ǰ����"));
	m_leftView->AddView(RUNTIME_CLASS(CMagicCabsineDisplayView),CString("ƽ��ɫ"));

	//��ʼʱֻ��ʾԭͼһ����ǩҳ,����������ǩҳ
	m_leftView->GetTabControl().ShowTab(1,FALSE);
	m_leftView->GetTabControl().ShowTab(2,FALSE);
	m_leftView->GetTabControl().ShowTab(3,FALSE);
	m_leftView->GetTabControl().ShowTab(4,FALSE);
	m_leftView->GetTabControl().ShowTab(5,FALSE);
	m_leftView->GetTabControl().ShowTab(6,FALSE);
	m_leftView->GetTabControl().ShowTab(7,FALSE);
	m_leftView->GetTabControl().ShowTab(8,FALSE);

	//����ұߵı�ǩҳ,Ŀǰֻ��һ��
	CMagicCabsineRightView* m_rightView=(CMagicCabsineRightView *)m_WndSplitter.GetPane(0,1);
	m_rightView->GetTabControl().EnableTabSwap(FALSE);//��ֹ��ǩҳ�϶�
	m_rightView->AddView(RUNTIME_CLASS(CMagicCabsineDisplayView),CString("ģ����"));
	//m_rightView->AddView(RUNTIME_CLASS(CMagicCabsineSimulateView),CString("�̵ײ�"));
	//m_rightView->AddView(RUNTIME_CLASS(CMagicCabsineSimulateView),CString("�����"));
	//m_rightView->AddView(RUNTIME_CLASS(CMagicCabsineSimulateView),CString("�����"));
	//m_rightView->AddView(RUNTIME_CLASS(CMagicCabsineSimulateView),CString("��4��"));
	//m_rightView->AddView(RUNTIME_CLASS(CMagicCabsineSimulateView),CString("��5��"));

	m_rightView->AddView(RUNTIME_CLASS(CMagicCabsineSimulateView),CString("�̵ײ�"));
	int tabNum = m_rightView->GetTabControl().GetTabsNum();
	m_rightView->SetActiveView(tabNum - 1);
	CMagicCabsineSimulateView* view = (CMagicCabsineSimulateView*)m_rightView->GetActiveView();
	view->tabID = tabNum - 1;

	m_rightView->AddView(RUNTIME_CLASS(CMagicCabsineSimulateView),CString("�����"));
	tabNum = m_rightView->GetTabControl().GetTabsNum();
	m_rightView->SetActiveView(tabNum - 1);
	view = (CMagicCabsineSimulateView*)m_rightView->GetActiveView();
	view->tabID = tabNum - 1;

	m_rightView->AddView(RUNTIME_CLASS(CMagicCabsineSimulateView),CString("�����"));
	tabNum = m_rightView->GetTabControl().GetTabsNum();
	m_rightView->SetActiveView(tabNum - 1);
	view = (CMagicCabsineSimulateView*)m_rightView->GetActiveView();
	view->tabID = tabNum - 1;

	m_rightView->AddView(RUNTIME_CLASS(CMagicCabsineSimulateView),CString("��4��"));
	tabNum = m_rightView->GetTabControl().GetTabsNum();
	m_rightView->SetActiveView(tabNum - 1);
	view = (CMagicCabsineSimulateView*)m_rightView->GetActiveView();
	view->tabID = tabNum - 1;

	m_rightView->AddView(RUNTIME_CLASS(CMagicCabsineSimulateView),CString("��5��"));
	tabNum = m_rightView->GetTabControl().GetTabsNum();
	m_rightView->SetActiveView(tabNum - 1);
	view = (CMagicCabsineSimulateView*)m_rightView->GetActiveView();
	view->tabID = tabNum - 1;

	//��ʼʱֻ��ʾģ����ӽ��һ����ǩҳ,����������ǩҳ
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
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CFrameWndEx::OnNcPaint()
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
	// TODO: �ڴ���������������
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
	// TODO: �ڴ���������������
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
	// TODO: �ڴ���������������
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
