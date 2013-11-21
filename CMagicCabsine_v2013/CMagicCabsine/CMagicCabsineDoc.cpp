
// CMagicCabsineDoc.cpp : CMagicCabsineDoc 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "CMagicCabsine.h"
#endif

#include "MainFrm.h"

#include "CMagicCabsineDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//#include "ProjectConfigDLG.h"
#include "CMagicCabsineConfig.h"
#include "StitchLibraryDLG.h"
#include "ThreadLibraryDLG.h"
#include "MagicCabsineConfigDlg.h"

// CMagicCabsineDoc

IMPLEMENT_DYNCREATE(CMagicCabsineDoc, CDocument)

BEGIN_MESSAGE_MAP(CMagicCabsineDoc, CDocument)
	ON_COMMAND(ID_Menu_Confic, &CMagicCabsineDoc::OnMenuConfic)
	ON_COMMAND(ID_FILE_NEW, &CMagicCabsineDoc::OnFileNew)
	ON_COMMAND(ID_MarkForeground, &CMagicCabsineDoc::OnMarkForeground)
	ON_COMMAND(ID_MarkBackground, &CMagicCabsineDoc::OnMarkBackground)
	ON_COMMAND(ID_MarkClear, &CMagicCabsineDoc::OnMarkClear)
	ON_COMMAND(ID_MarkDone, &CMagicCabsineDoc::OnMarkDone)
	ON_COMMAND(ID_SplitDone, &CMagicCabsineDoc::OnSplitDone)
	ON_COMMAND(ID_CANVAS_SELECT, &CMagicCabsineDoc::OnCanvasSelect)
	ON_UPDATE_COMMAND_UI(ID_CANVAS_SELECT, &CMagicCabsineDoc::OnUpdateCanvasSelect)
	ON_COMMAND(ID_SIMULATE_DONE, &CMagicCabsineDoc::OnSimulateDone)
	ON_UPDATE_COMMAND_UI(ID_SIMULATE_DONE, &CMagicCabsineDoc::OnUpdateSimulateDone)
	ON_UPDATE_COMMAND_UI(ID_PROCESS_MARK, &CMagicCabsineDoc::OnUpdateProcessMark)
	ON_UPDATE_COMMAND_UI(ID_PROCESS_SIMULATE, &CMagicCabsineDoc::OnUpdateProcessSimulate)
	ON_UPDATE_COMMAND_UI(ID_PROCESS_MACHINE, &CMagicCabsineDoc::OnUpdateProcessMachine)
	ON_UPDATE_COMMAND_UI(ID_PROCESS_MARKDOWN, &CMagicCabsineDoc::OnUpdateProcessMarkdown)
	ON_UPDATE_COMMAND_UI(ID_PROCESS_SPLITED, &CMagicCabsineDoc::OnUpdateProcessSplited)
	ON_COMMAND(ID_FILE_SAVE, &CMagicCabsineDoc::OnFileSave)
	ON_COMMAND(ID_FILE_CLOSE, &CMagicCabsineDoc::OnFileClose)
	ON_COMMAND(ID_FILE_OPEN, &CMagicCabsineDoc::OnFileOpen)
	ON_COMMAND(ID_MENU_STITCHLIBRARY, &CMagicCabsineDoc::OnMenuStitchlibrary)
	ON_COMMAND(ID_MENU_THREADLIBRARY, &CMagicCabsineDoc::OnMenuThreadlibrary)
	ON_COMMAND(ID_FILE_IMPORT, &CMagicCabsineDoc::OnFileImport)
	ON_UPDATE_COMMAND_UI(ID_Menu_Confic, &CMagicCabsineDoc::OnUpdateMenuConfic)
	ON_UPDATE_COMMAND_UI(ID_MENU_STITCHLIBRARY, &CMagicCabsineDoc::OnUpdateMenuStitchlibrary)
	ON_UPDATE_COMMAND_UI(ID_MENU_THREADLIBRARY, &CMagicCabsineDoc::OnUpdateMenuThreadlibrary)
	ON_COMMAND(ID_REGION_PROP_DOWN, &CMagicCabsineDoc::OnRegionPropDown)
	ON_UPDATE_COMMAND_UI(ID_REGION_PROP_DOWN, &CMagicCabsineDoc::OnUpdateRegionPropDown)
	ON_UPDATE_COMMAND_UI(ID_BLANK_UP2, &CMagicCabsineDoc::OnUpdateBlankUp2)
	ON_UPDATE_COMMAND_UI(ID_BLANK_UP3, &CMagicCabsineDoc::OnUpdateBlankUp2)
	ON_UPDATE_COMMAND_UI(ID_BLANK_UP4, &CMagicCabsineDoc::OnUpdateBlankUp2)
	ON_UPDATE_COMMAND_UI(ID_BLANK_UP5, &CMagicCabsineDoc::OnUpdateBlankUp2)
	ON_UPDATE_COMMAND_UI(ID_BLANK_UP6, &CMagicCabsineDoc::OnUpdateBlankUp2)
	ON_UPDATE_COMMAND_UI(ID_BLANK_UP8, &CMagicCabsineDoc::OnUpdateBlankUp8)
	ON_UPDATE_COMMAND_UI(ID_BLANK_UP9, &CMagicCabsineDoc::OnUpdateBlankUp8)
	ON_UPDATE_COMMAND_UI(ID_BLANK_UP10, &CMagicCabsineDoc::OnUpdateBlankUp8)
	ON_UPDATE_COMMAND_UI(ID_BLANK_UP11, &CMagicCabsineDoc::OnUpdateBlankUp8)
	ON_UPDATE_COMMAND_UI(ID_BLANK_UP13, &CMagicCabsineDoc::OnUpdateBlankUp13)
	ON_UPDATE_COMMAND_UI(ID_BLANK_UP15, &CMagicCabsineDoc::OnUpdateBlankUp15)
	ON_UPDATE_COMMAND_UI(ID_BLANK_UP16, &CMagicCabsineDoc::OnUpdateBlankUp15)
	ON_COMMAND(ID_SHOWLEFT, &CMagicCabsineDoc::OnShowleft)
	ON_COMMAND(ID_SHOWRIGHT, &CMagicCabsineDoc::OnShowright)
	ON_COMMAND(ID_SHOWBOTH, &CMagicCabsineDoc::OnShowboth)
	ON_COMMAND(ID_FILE_SAVE_AS, &CMagicCabsineDoc::OnFileSaveAs)
END_MESSAGE_MAP()

// CMagicCabsineDoc 构造/析构
CMagicCabsineDoc::CMagicCabsineDoc()
{
	// TODO: 在此添加一次性构造代码

	theProject=new CMagicCabsineProject();
}

CMagicCabsineDoc::~CMagicCabsineDoc()
{
	if(theProject!=NULL)
	{
		delete theProject;
		theProject=NULL;
	}
}

BOOL CMagicCabsineDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CMagicCabsineDoc 序列化

void CMagicCabsineDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}

#ifdef SHARED_HANDLERS

// 缩略图的支持
void CMagicCabsineDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 修改此代码以绘制文档数据
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 搜索处理程序的支持
void CMagicCabsineDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:  strSearchContent = _T("point;rectangle;circle;ole object;")；
	SetSearchContent(strSearchContent);
}

void CMagicCabsineDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CMagicCabsineDoc 诊断

#ifdef _DEBUG
void CMagicCabsineDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMagicCabsineDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMagicCabsineDoc 命令


//主菜单上配置按钮触发的函数,打开配置管理对话框
void CMagicCabsineDoc::OnMenuConfic()
{
	// TODO: 在此添加命令处理程序代码

//	ProjectConfigDLG configDLG;
	CMagicCabsineConfigDlg configDLG;
	configDLG.DoModal();
}

//主菜单上新建按钮触发的函数,打开新建工程对话框
void CMagicCabsineDoc::OnFileNew()
{
	// TODO: 在此添加命令处理程序代码
// 	ProjectNewDLG projectNewDLG;
// 	if(projectNewDLG.DoModal()!=IDOK)
// 	{
// 		return;
// 	}

	//打开工程时有工程正处于打开状态,需要先关闭
	if(theProject->currentProcessType!=PROCESS_START)
	{
		string theProjectName=theProject->GetProjectName();
		if(IDOK!=MessageBox(NULL,CString("工程关闭时未保存的数据将丢失\n确定要关闭工程")+CString(theProjectName.c_str())+CString("吗?"),CString("关闭工程提示"),MB_OKCANCEL|MB_ICONWARNING))
		{
			return;
		}

		theProject->CloseProject();
	}

	theProject->stateInitialize();//初始化系统状态
	theProject->RunWorkStep1();//开始运行流程
}

void CMagicCabsineDoc::OnMarkForeground()
{
	// TODO: 在此添加命令处理程序代码

	CString tempMsg=CString("请单击\"确定\"后标记前景");
	MessageBox(NULL,tempMsg,CString("标记前景"),MB_OK|MB_ICONWARNING);

	MainFrame *mainFrame=(MainFrame*)AfxGetMainWnd();
	CMagicCabsineLeftView *m_leftView=(CMagicCabsineLeftView *)mainFrame->m_WndSplitter.GetPane(0,0);
	void *tp=m_leftView->getTabViewPoint(TABTYPE_SPLIT,0);
	CMagicCabsineInteractiveView *interactiveView=(CMagicCabsineInteractiveView *)tp;
	interactiveView->EnableMarking();
	interactiveView->EnableMarkingForeground();
}

void CMagicCabsineDoc::OnMarkBackground()
{
	// TODO: 在此添加命令处理程序代码

	CString tempMsg=CString("请单击\"确定\"后标记背景");
	MessageBox(NULL,tempMsg,CString("标记背景"),MB_OK|MB_ICONWARNING);

	MainFrame *mainFrame=(MainFrame*)AfxGetMainWnd();
	CMagicCabsineLeftView *m_leftView=(CMagicCabsineLeftView *)mainFrame->m_WndSplitter.GetPane(0,0);
	void *tp=m_leftView->getTabViewPoint(TABTYPE_SPLIT,0);
	CMagicCabsineInteractiveView *interactiveView=(CMagicCabsineInteractiveView *)tp;
	interactiveView->EnableMarking();
	interactiveView->EnableMarkingBackground();
}

void CMagicCabsineDoc::OnMarkClear()
{
	// TODO: 在此添加命令处理程序代码

	CString tempMsg=CString("单击\"确定\"清除标记\n单击\"取消\"保留标记");
	if(MessageBox(NULL,tempMsg,CString("清除标记?"),MB_OKCANCEL|MB_ICONWARNING)==IDCANCEL)
	{
		return;
	}

	MainFrame *mainFrame=(MainFrame*)AfxGetMainWnd();
	CMagicCabsineLeftView *m_leftView=(CMagicCabsineLeftView *)mainFrame->m_WndSplitter.GetPane(0,0);

	//清除上一次分割的结果,使活动标签为分割页
	m_leftView->clearImageInTab(TABTYPE_SPLIT_RES,0);
	m_leftView->clearImageInTab(TABTYPE_SPLIT_RES,1);

	void *tp=m_leftView->getTabViewPoint(TABTYPE_SPLIT,0);
	CMagicCabsineInteractiveView *interactiveView=(CMagicCabsineInteractiveView *)tp;
	interactiveView->DisableMarking();
	interactiveView->ClearMarking();
	tp=NULL;
	interactiveView=NULL;
}

void CMagicCabsineDoc::OnMarkDone()
{
	// TODO: 在此添加命令处理程序代码
	MessageBox(NULL,CString("标记已完成\n正在进行分割"),CString("标记完成"),MB_OK|MB_ICONWARNING);

	MainFrame *mainFrame=(MainFrame*)AfxGetMainWnd();
	CMagicCabsineLeftView *m_leftView=(CMagicCabsineLeftView *)mainFrame->m_WndSplitter.GetPane(0,0);
	void *tp=m_leftView->getTabViewPoint(TABTYPE_SPLIT,0);
	CMagicCabsineInteractiveView *interactiveView=(CMagicCabsineInteractiveView *)tp;
	interactiveView->SetSplitDone();
	interactiveView->DisableMarking();

	theProject->RunWorkStep2();
	interactiveView->ClearMarking();
}

void CMagicCabsineDoc::OnSplitDone()
{
	// TODO: 在此添加命令处理程序代码
	MainFrame *mainFrame=(MainFrame*)AfxGetMainWnd();
	CMagicCabsineLeftView *m_leftView=(CMagicCabsineLeftView *)mainFrame->m_WndSplitter.GetPane(0,0);
	void *tp=m_leftView->getTabViewPoint(TABTYPE_SPLIT,0);
	CMagicCabsineInteractiveView *interactiveView=(CMagicCabsineInteractiveView *)tp;
	interactiveView->DisableMarking();
	if(!interactiveView->IsSplited())
	{
		MessageBox(NULL,CString("分割未完成\n请点击按钮\"分\"以完成分割"),CString("分割未完成"),MB_OK|MB_ICONWARNING);
		return;
	}

	MessageBox(NULL,CString("图像分割已完成"),CString("分割完成"),MB_OK|MB_ICONINFORMATION);
	theProject->RunWorkStep3();
}

void CMagicCabsineDoc::OnUpdateMarkForeground(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	switch (theProject->currentProcessType)
	{
	case PROCESS_UNIVERSALCALCED:
		pCmdUI->Enable(TRUE);
		break;
	default:
		pCmdUI->Enable(FALSE);
		break;
	}
}

void CMagicCabsineDoc::OnUpdateMarkBackground(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	switch (theProject->currentProcessType)
	{
	case PROCESS_UNIVERSALCALCED:
		pCmdUI->Enable(TRUE);
		break;
	default:
		pCmdUI->Enable(FALSE);
		break;
	}
}

void CMagicCabsineDoc::OnUpdateMarkClear(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	switch (theProject->currentProcessType)
	{
	case PROCESS_UNIVERSALCALCED:
		pCmdUI->Enable(TRUE);
		break;
	default:
		pCmdUI->Enable(FALSE);
		break;
	}
}

void CMagicCabsineDoc::OnUpdateMarkDone(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	switch (theProject->currentProcessType)
	{
	case PROCESS_UNIVERSALCALCED:
		pCmdUI->Enable(TRUE);
		break;
	default:
		pCmdUI->Enable(FALSE);
		break;
	}
}

void CMagicCabsineDoc::OnUpdateSplitDone(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	switch (theProject->currentProcessType)
	{
	case PROCESS_START:
	case PROCESS_UNIVERSALCALCED:
		pCmdUI->Enable(FALSE);
		break;
	case PROCESS_SPLITED:
		pCmdUI->Enable(TRUE);
		break;
	case PROCESS_LEFTDONE:
	case PROCESS_SIMULATED:
	case PROCESS_SIMULATEDONE:
	case PROCESS_DONE:
		pCmdUI->Enable(FALSE);
		break;
	default:
		pCmdUI->Enable(FALSE);
		break;
	}
}

void CMagicCabsineDoc::OnCanvasSelect()
{
	// TODO: 在此添加命令处理程序代码
	theProject->RunWorkStep4();
}

void CMagicCabsineDoc::OnUpdateCanvasSelect(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	switch (theProject->currentProcessType)
	{
	case PROCESS_LEFTDONE:
		pCmdUI->Enable(TRUE);
		break;
	default:
		pCmdUI->Enable(FALSE);
		break;
	}
}

void CMagicCabsineDoc::OnSimulateDone()
{
	// TODO: 在此添加命令处理程序代码
	theProject->RunWorkStep5();
}

void CMagicCabsineDoc::OnFileSave()
{
	// TODO: 在此添加命令处理程序代码
	string theProjectName=theProject->GetProjectName();
	if(theProjectName.size()>0)//工程名称不会为空
	{
		theProject->SaveProject();
		MessageBox(NULL,CString("工程成功保存:")+CString(theProjectName.c_str()),CString("保存工程提示"),MB_OK|MB_ICONINFORMATION);
	}
}

BOOL CMagicCabsineDoc::CreateFolder(CString strPath)
{
	SECURITY_ATTRIBUTES attrib;
	attrib.bInheritHandle = FALSE;
	attrib.lpSecurityDescriptor = NULL;
	attrib.nLength =sizeof(SECURITY_ATTRIBUTES);
	//上面定义的属性可以省略。 直接return ::CreateDirectory( path, NULL); 即可
	return ::CreateDirectory( strPath, &attrib);
}

void CMagicCabsineDoc::OnFileSaveAs()
{
	// TODO: 在此添加命令处理程序代码
	CString theSrcPath=theProject->GetProjectPath().c_str();
	theSrcPath+=theProject->GetProjectName().c_str();

	CFileDialog dlgFile(FALSE,_T("*.lzx"),NULL,OFN_PATHMUSTEXIST|OFN_HIDEREADONLY,
		_T("LZX FILES(*.lzx)|*.lzx|All Files(*.*)|*.*||"),NULL);
	CString tempCString=theApp.GetDefaultPath().c_str();
	tempCString+="Projects\\";
	dlgFile.m_ofn.lpstrInitialDir=tempCString;
	if(dlgFile.DoModal()!=IDOK)
	{
		return;
	}
	tempCString=dlgFile.GetPathName();

	CString theDesPath=tempCString.Left(tempCString.GetLength()-4);
	time_t myTime=time(NULL);
	char tmpStr[300];
	strftime(tmpStr,sizeof(tmpStr),"_%Y%m%d%H%M%S",localtime(&myTime));
	theDesPath+=tmpStr;
	tempCString=theDesPath;
	theDesPath+="\\";
	CreateFolder(theDesPath);

	CFileFind ff;
	BOOL bFound=ff.FindFile(theSrcPath,0);
	theSrcPath+="\\";
	if(bFound)
	{
		bFound = ff.FindFile(theSrcPath+"*",0);  
		while(bFound)
		{
			bFound = ff.FindNextFile();
			if(ff.IsDots())
			{
				continue;
			}
			if(ff.IsDirectory())
			{
				continue;
			}
			CString strSubSrcPath = ff.GetFilePath();
			CString strSubDespath = strSubSrcPath;
			strSubDespath.Replace(theSrcPath, theDesPath);

			CopyFile(strSubSrcPath,strSubDespath,FALSE);//拷贝文件
		}
	}
	ff.Close();
	
	int i;
	for(i=tempCString.GetLength()-1;i>=0&&tempCString[i]!='\\';i--);
	tempCString=tempCString.Right(tempCString.GetLength()-i-1);
	theProject->SetProjectName(string(tempCString));
	theApp.SetTitleText(tempCString);
	theDesPath=theDesPath.Left(theDesPath.GetLength()-1-tempCString.GetLength());
	theProject->SetProjectPath(string(theDesPath));

	theProject->SaveProject();
	MessageBox(NULL,CString("工程成功保存:")+tempCString,CString("保存工程提示"),MB_OK|MB_ICONINFORMATION);
}

void CMagicCabsineDoc::OnFileClose()
{
	// TODO: 在此添加命令处理程序代码
	string theProjectName=theProject->GetProjectName();
	if(theProjectName.length()<=0)
	{
		return;
	}
	if(IDOK!=MessageBox(NULL,CString("工程关闭时未保存的数据将丢失\n确定要关闭工程")+CString(theProjectName.c_str())+CString("吗?"),CString("关闭工程提示"),MB_OKCANCEL|MB_ICONWARNING))
	{
		return;
	}
	theProject->CloseProject();
	theApp.SetTitleText(CString("MagicCabsine"));
	if(theProjectName.length()>0)
	{
		MessageBox(NULL,CString("工程已关闭:")+CString(theProjectName.c_str()),CString("关闭工程提示"),MB_OK|MB_ICONINFORMATION);
	}
}

void CMagicCabsineDoc::OnFileOpen()
{
	// TODO: 在此添加命令处理程序代码
	string theProjectName=theProject->GetProjectName();

	//打开工程时有工程正处于打开状态,需要先关闭
	if(theProject->currentProcessType!=PROCESS_START)
	{	
		if(IDOK!=MessageBox(NULL,CString("工程关闭时未保存的数据将丢失\n确定要关闭工程")+CString(theProjectName.c_str())+CString("吗?"),CString("关闭工程提示"),MB_OKCANCEL|MB_ICONWARNING))
		{
			return;
		}

		theProject->CloseProject();
	}

	theProject->LoadProject();
	theProjectName=theProject->GetProjectName();
	theApp.SetTitleText(theProjectName.c_str());

	if(theProjectName.size()>0)//工程名称不会为空
	{
		MessageBox(NULL,CString("工程成功打开:")+CString(theProjectName.c_str()),CString("打开工程提示"),MB_OK|MB_ICONINFORMATION);
	}
	else
	{
		theApp.SetTitleText();
	}
}

void CMagicCabsineDoc::OnMenuStitchlibrary()
{
	// TODO: 在此添加命令处理程序代码
	StitchLibraryDLG dlg;
	if (dlg.DoModal()!=IDOK)
	{
		return;
	}
}

void CMagicCabsineDoc::OnMenuThreadlibrary()
{
	// TODO: 在此添加命令处理程序代码
	ThreadLibraryDLG dlg;
	if(dlg.DoModal()!=IDOK)
	{
		return;
	}
}

void CMagicCabsineDoc::OnFileImport()
{
	// TODO: 在此添加命令处理程序代码
	theProject->ImportImage();
}

void CMagicCabsineDoc::OnUpdateMenuConfic(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	switch (theProject->currentProcessType)
	{
	case PROCESS_START:
		pCmdUI->Enable(TRUE);
		break;
	default:
		pCmdUI->Enable(FALSE);
		break;
	}
}

void CMagicCabsineDoc::OnUpdateMenuStitchlibrary(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	switch (theProject->currentProcessType)
	{
	case PROCESS_START:
		pCmdUI->Enable(TRUE);
		break;
	default:
		pCmdUI->Enable(FALSE);
		break;
	}
}

void CMagicCabsineDoc::OnUpdateMenuThreadlibrary(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	switch (theProject->currentProcessType)
	{
	case PROCESS_START:
		pCmdUI->Enable(TRUE);
		break;
	default:
		pCmdUI->Enable(FALSE);
		break;
	}
}

void CMagicCabsineDoc::OnUpdateSimulateDone(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	switch (theProject->currentProcessType)
	{
	case PROCESS_START:
	case PROCESS_UNIVERSALCALCED:
	case PROCESS_SPLIT_MARKDOWN:
	case PROCESS_SPLITED:
	case PROCESS_LEFTDONE:
		pCmdUI->Enable(FALSE);
		break;
	case PROCESS_SIMULATED:
		pCmdUI->Enable(TRUE);
		break;
	case PROCESS_SIMULATEDONE:
	case PROCESS_DONE:
		pCmdUI->Enable(FALSE);
		break;
	default:
		pCmdUI->Enable(FALSE);
		break;
	}
}

void CMagicCabsineDoc::OnUpdateProcessMark(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	switch (theProject->currentProcessType)
	{
	case PROCESS_START:
		pCmdUI->Enable(FALSE);
		break;
	case PROCESS_UNIVERSALCALCED:
	case PROCESS_SPLIT_MARKDOWN:
	case PROCESS_SPLITED:
	case PROCESS_LEFTDONE:
	case PROCESS_SIMULATED:
	case PROCESS_SIMULATEDONE:
	case PROCESS_DONE:
		pCmdUI->Enable(TRUE);
		break;
	default:
		pCmdUI->Enable(FALSE);
		break;
	}
}

void CMagicCabsineDoc::OnUpdateProcessSimulate(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	switch (theProject->currentProcessType)
	{
	case PROCESS_START:
	case PROCESS_UNIVERSALCALCED:
	case PROCESS_SPLIT_MARKDOWN:
	case PROCESS_SPLITED:
		pCmdUI->Enable(FALSE);
		break;
	case PROCESS_LEFTDONE:
	case PROCESS_SIMULATED:
	case PROCESS_SIMULATEDONE:
	case PROCESS_DONE:
		pCmdUI->Enable(TRUE);
		break;
	default:
		pCmdUI->Enable(FALSE);
		break;
	}
}

void CMagicCabsineDoc::OnUpdateProcessMachine(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	switch (theProject->currentProcessType)
	{
	case PROCESS_START:
	case PROCESS_UNIVERSALCALCED:
	case PROCESS_SPLIT_MARKDOWN:
	case PROCESS_SPLITED:
	case PROCESS_LEFTDONE:
	case PROCESS_SIMULATED:
	case PROCESS_SIMULATEDONE:
		pCmdUI->Enable(FALSE);
		break;
	case PROCESS_DONE:
		pCmdUI->Enable(TRUE);
		break;
	default:
		pCmdUI->Enable(FALSE);
		break;
	}
}

void CMagicCabsineDoc::OnUpdateProcessMarkdown(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	switch (theProject->currentProcessType)
	{
	case PROCESS_START:
	case PROCESS_UNIVERSALCALCED:
		pCmdUI->Enable(FALSE);
		break;
	case PROCESS_SPLIT_MARKDOWN:
	case PROCESS_SPLITED:
	case PROCESS_LEFTDONE:
	case PROCESS_SIMULATED:
	case PROCESS_SIMULATEDONE:
	case PROCESS_DONE:
		pCmdUI->Enable(TRUE);
		break;
	default:
		pCmdUI->Enable(FALSE);
		break;
	}
}

void CMagicCabsineDoc::OnUpdateProcessSplited(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	switch (theProject->currentProcessType)
	{
	case PROCESS_START:
	case PROCESS_UNIVERSALCALCED:
	case PROCESS_SPLIT_MARKDOWN:
		pCmdUI->Enable(FALSE);
		break;
	case PROCESS_SPLITED:
	case PROCESS_LEFTDONE:
	case PROCESS_SIMULATED:
	case PROCESS_SIMULATEDONE:
	case PROCESS_DONE:
		pCmdUI->Enable(TRUE);
		break;
	default:
		pCmdUI->Enable(FALSE);
		break;
	}
}

void CMagicCabsineDoc::OnRegionPropDown()
{
	// TODO: 在此添加命令处理程序代码
	MessageBox(NULL,CString("图像分割已完成"),CString("分割完成"),MB_OK|MB_ICONINFORMATION);
	theProject->RunWorkStep3();
}

void CMagicCabsineDoc::OnUpdateRegionPropDown(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	switch (theProject->currentProcessType)
	{
	case PROCESS_SPLITED:
		pCmdUI->Enable(TRUE);
		break;
	default:
		pCmdUI->Enable(FALSE);
		break;
	}
}

void CMagicCabsineDoc::OnUpdateBlankUp2(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	switch (theProject->currentProcessType)
	{
	case PROCESS_START:
	case PROCESS_UNIVERSALCALCED:
		pCmdUI->Enable(FALSE);
		break;
	case PROCESS_SPLIT_MARKDOWN:
	case PROCESS_SPLITED:
	case PROCESS_LEFTDONE:
	case PROCESS_SIMULATED:
	case PROCESS_SIMULATEDONE:
	case PROCESS_DONE:
		pCmdUI->Enable(TRUE);
		break;
	default:
		pCmdUI->Enable(FALSE);
		break;
	}
}

void CMagicCabsineDoc::OnUpdateBlankUp8(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	switch (theProject->currentProcessType)
	{
	case PROCESS_START:
	case PROCESS_UNIVERSALCALCED:
	case PROCESS_SPLIT_MARKDOWN:
		pCmdUI->Enable(FALSE);
		break;
	case PROCESS_SPLITED:
	case PROCESS_LEFTDONE:
	case PROCESS_SIMULATED:
	case PROCESS_SIMULATEDONE:
	case PROCESS_DONE:
		pCmdUI->Enable(TRUE);
		break;
	default:
		pCmdUI->Enable(FALSE);
		break;
	}
}

void CMagicCabsineDoc::OnUpdateBlankUp13(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	switch (theProject->currentProcessType)
	{
	case PROCESS_START:
	case PROCESS_UNIVERSALCALCED:
	case PROCESS_SPLIT_MARKDOWN:
	case PROCESS_SPLITED:
		pCmdUI->Enable(FALSE);
		break;
	case PROCESS_LEFTDONE:
	case PROCESS_SIMULATED:
	case PROCESS_SIMULATEDONE:
	case PROCESS_DONE:
		pCmdUI->Enable(TRUE);
		break;
	default:
		pCmdUI->Enable(FALSE);
		break;
	}
}

void CMagicCabsineDoc::OnUpdateBlankUp15(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	switch (theProject->currentProcessType)
	{
	case PROCESS_START:
	case PROCESS_UNIVERSALCALCED:
	case PROCESS_SPLIT_MARKDOWN:
	case PROCESS_SPLITED:
	case PROCESS_LEFTDONE:
	case PROCESS_SIMULATED:
	case PROCESS_SIMULATEDONE:
		pCmdUI->Enable(FALSE);
		break;
	case PROCESS_DONE:
		pCmdUI->Enable(TRUE);
		break;
	default:
		pCmdUI->Enable(FALSE);
		break;
	}
}

void CMagicCabsineDoc::OnShowleft()
{
	// TODO: 在此添加命令处理程序代码
	MainFrame *mainFrame=(MainFrame*)AfxGetMainWnd();
	mainFrame->OnShowLeftView();
	mainFrame=NULL;
}

void CMagicCabsineDoc::OnShowright()
{
	// TODO: 在此添加命令处理程序代码
	MainFrame *mainFrame=(MainFrame*)AfxGetMainWnd();
	mainFrame->OnShowRightView();
	mainFrame=NULL;
}

void CMagicCabsineDoc::OnShowboth()
{
	// TODO: 在此添加命令处理程序代码
	MainFrame *mainFrame=(MainFrame*)AfxGetMainWnd();
	mainFrame->OnShowBothView();
	mainFrame=NULL;
}
