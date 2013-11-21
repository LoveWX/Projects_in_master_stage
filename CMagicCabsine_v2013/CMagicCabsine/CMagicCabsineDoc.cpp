
// CMagicCabsineDoc.cpp : CMagicCabsineDoc ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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

// CMagicCabsineDoc ����/����
CMagicCabsineDoc::CMagicCabsineDoc()
{
	// TODO: �ڴ����һ���Թ������

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

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CMagicCabsineDoc ���л�

void CMagicCabsineDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
	}
}

#ifdef SHARED_HANDLERS

// ����ͼ��֧��
void CMagicCabsineDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// �޸Ĵ˴����Ի����ĵ�����
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

// ������������֧��
void CMagicCabsineDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// ���ĵ����������������ݡ�
	// ���ݲ���Ӧ�ɡ�;���ָ�

	// ����:  strSearchContent = _T("point;rectangle;circle;ole object;")��
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

// CMagicCabsineDoc ���

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


// CMagicCabsineDoc ����


//���˵������ð�ť�����ĺ���,�����ù���Ի���
void CMagicCabsineDoc::OnMenuConfic()
{
	// TODO: �ڴ���������������

//	ProjectConfigDLG configDLG;
	CMagicCabsineConfigDlg configDLG;
	configDLG.DoModal();
}

//���˵����½���ť�����ĺ���,���½����̶Ի���
void CMagicCabsineDoc::OnFileNew()
{
	// TODO: �ڴ���������������
// 	ProjectNewDLG projectNewDLG;
// 	if(projectNewDLG.DoModal()!=IDOK)
// 	{
// 		return;
// 	}

	//�򿪹���ʱ�й��������ڴ�״̬,��Ҫ�ȹر�
	if(theProject->currentProcessType!=PROCESS_START)
	{
		string theProjectName=theProject->GetProjectName();
		if(IDOK!=MessageBox(NULL,CString("���̹ر�ʱδ��������ݽ���ʧ\nȷ��Ҫ�رչ���")+CString(theProjectName.c_str())+CString("��?"),CString("�رչ�����ʾ"),MB_OKCANCEL|MB_ICONWARNING))
		{
			return;
		}

		theProject->CloseProject();
	}

	theProject->stateInitialize();//��ʼ��ϵͳ״̬
	theProject->RunWorkStep1();//��ʼ��������
}

void CMagicCabsineDoc::OnMarkForeground()
{
	// TODO: �ڴ���������������

	CString tempMsg=CString("�뵥��\"ȷ��\"����ǰ��");
	MessageBox(NULL,tempMsg,CString("���ǰ��"),MB_OK|MB_ICONWARNING);

	MainFrame *mainFrame=(MainFrame*)AfxGetMainWnd();
	CMagicCabsineLeftView *m_leftView=(CMagicCabsineLeftView *)mainFrame->m_WndSplitter.GetPane(0,0);
	void *tp=m_leftView->getTabViewPoint(TABTYPE_SPLIT,0);
	CMagicCabsineInteractiveView *interactiveView=(CMagicCabsineInteractiveView *)tp;
	interactiveView->EnableMarking();
	interactiveView->EnableMarkingForeground();
}

void CMagicCabsineDoc::OnMarkBackground()
{
	// TODO: �ڴ���������������

	CString tempMsg=CString("�뵥��\"ȷ��\"���Ǳ���");
	MessageBox(NULL,tempMsg,CString("��Ǳ���"),MB_OK|MB_ICONWARNING);

	MainFrame *mainFrame=(MainFrame*)AfxGetMainWnd();
	CMagicCabsineLeftView *m_leftView=(CMagicCabsineLeftView *)mainFrame->m_WndSplitter.GetPane(0,0);
	void *tp=m_leftView->getTabViewPoint(TABTYPE_SPLIT,0);
	CMagicCabsineInteractiveView *interactiveView=(CMagicCabsineInteractiveView *)tp;
	interactiveView->EnableMarking();
	interactiveView->EnableMarkingBackground();
}

void CMagicCabsineDoc::OnMarkClear()
{
	// TODO: �ڴ���������������

	CString tempMsg=CString("����\"ȷ��\"������\n����\"ȡ��\"�������");
	if(MessageBox(NULL,tempMsg,CString("������?"),MB_OKCANCEL|MB_ICONWARNING)==IDCANCEL)
	{
		return;
	}

	MainFrame *mainFrame=(MainFrame*)AfxGetMainWnd();
	CMagicCabsineLeftView *m_leftView=(CMagicCabsineLeftView *)mainFrame->m_WndSplitter.GetPane(0,0);

	//�����һ�ηָ�Ľ��,ʹ���ǩΪ�ָ�ҳ
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
	// TODO: �ڴ���������������
	MessageBox(NULL,CString("��������\n���ڽ��зָ�"),CString("������"),MB_OK|MB_ICONWARNING);

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
	// TODO: �ڴ���������������
	MainFrame *mainFrame=(MainFrame*)AfxGetMainWnd();
	CMagicCabsineLeftView *m_leftView=(CMagicCabsineLeftView *)mainFrame->m_WndSplitter.GetPane(0,0);
	void *tp=m_leftView->getTabViewPoint(TABTYPE_SPLIT,0);
	CMagicCabsineInteractiveView *interactiveView=(CMagicCabsineInteractiveView *)tp;
	interactiveView->DisableMarking();
	if(!interactiveView->IsSplited())
	{
		MessageBox(NULL,CString("�ָ�δ���\n������ť\"��\"����ɷָ�"),CString("�ָ�δ���"),MB_OK|MB_ICONWARNING);
		return;
	}

	MessageBox(NULL,CString("ͼ��ָ������"),CString("�ָ����"),MB_OK|MB_ICONINFORMATION);
	theProject->RunWorkStep3();
}

void CMagicCabsineDoc::OnUpdateMarkForeground(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
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
	// TODO: �ڴ������������û����洦��������
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
	// TODO: �ڴ������������û����洦��������
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
	// TODO: �ڴ������������û����洦��������
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
	// TODO: �ڴ������������û����洦��������
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
	// TODO: �ڴ���������������
	theProject->RunWorkStep4();
}

void CMagicCabsineDoc::OnUpdateCanvasSelect(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
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
	// TODO: �ڴ���������������
	theProject->RunWorkStep5();
}

void CMagicCabsineDoc::OnFileSave()
{
	// TODO: �ڴ���������������
	string theProjectName=theProject->GetProjectName();
	if(theProjectName.size()>0)//�������Ʋ���Ϊ��
	{
		theProject->SaveProject();
		MessageBox(NULL,CString("���̳ɹ�����:")+CString(theProjectName.c_str()),CString("���湤����ʾ"),MB_OK|MB_ICONINFORMATION);
	}
}

BOOL CMagicCabsineDoc::CreateFolder(CString strPath)
{
	SECURITY_ATTRIBUTES attrib;
	attrib.bInheritHandle = FALSE;
	attrib.lpSecurityDescriptor = NULL;
	attrib.nLength =sizeof(SECURITY_ATTRIBUTES);
	//���涨������Կ���ʡ�ԡ� ֱ��return ::CreateDirectory( path, NULL); ����
	return ::CreateDirectory( strPath, &attrib);
}

void CMagicCabsineDoc::OnFileSaveAs()
{
	// TODO: �ڴ���������������
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

			CopyFile(strSubSrcPath,strSubDespath,FALSE);//�����ļ�
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
	MessageBox(NULL,CString("���̳ɹ�����:")+tempCString,CString("���湤����ʾ"),MB_OK|MB_ICONINFORMATION);
}

void CMagicCabsineDoc::OnFileClose()
{
	// TODO: �ڴ���������������
	string theProjectName=theProject->GetProjectName();
	if(theProjectName.length()<=0)
	{
		return;
	}
	if(IDOK!=MessageBox(NULL,CString("���̹ر�ʱδ��������ݽ���ʧ\nȷ��Ҫ�رչ���")+CString(theProjectName.c_str())+CString("��?"),CString("�رչ�����ʾ"),MB_OKCANCEL|MB_ICONWARNING))
	{
		return;
	}
	theProject->CloseProject();
	theApp.SetTitleText(CString("MagicCabsine"));
	if(theProjectName.length()>0)
	{
		MessageBox(NULL,CString("�����ѹر�:")+CString(theProjectName.c_str()),CString("�رչ�����ʾ"),MB_OK|MB_ICONINFORMATION);
	}
}

void CMagicCabsineDoc::OnFileOpen()
{
	// TODO: �ڴ���������������
	string theProjectName=theProject->GetProjectName();

	//�򿪹���ʱ�й��������ڴ�״̬,��Ҫ�ȹر�
	if(theProject->currentProcessType!=PROCESS_START)
	{	
		if(IDOK!=MessageBox(NULL,CString("���̹ر�ʱδ��������ݽ���ʧ\nȷ��Ҫ�رչ���")+CString(theProjectName.c_str())+CString("��?"),CString("�رչ�����ʾ"),MB_OKCANCEL|MB_ICONWARNING))
		{
			return;
		}

		theProject->CloseProject();
	}

	theProject->LoadProject();
	theProjectName=theProject->GetProjectName();
	theApp.SetTitleText(theProjectName.c_str());

	if(theProjectName.size()>0)//�������Ʋ���Ϊ��
	{
		MessageBox(NULL,CString("���̳ɹ���:")+CString(theProjectName.c_str()),CString("�򿪹�����ʾ"),MB_OK|MB_ICONINFORMATION);
	}
	else
	{
		theApp.SetTitleText();
	}
}

void CMagicCabsineDoc::OnMenuStitchlibrary()
{
	// TODO: �ڴ���������������
	StitchLibraryDLG dlg;
	if (dlg.DoModal()!=IDOK)
	{
		return;
	}
}

void CMagicCabsineDoc::OnMenuThreadlibrary()
{
	// TODO: �ڴ���������������
	ThreadLibraryDLG dlg;
	if(dlg.DoModal()!=IDOK)
	{
		return;
	}
}

void CMagicCabsineDoc::OnFileImport()
{
	// TODO: �ڴ���������������
	theProject->ImportImage();
}

void CMagicCabsineDoc::OnUpdateMenuConfic(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
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
	// TODO: �ڴ������������û����洦��������
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
	// TODO: �ڴ������������û����洦��������
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
	// TODO: �ڴ������������û����洦��������
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
	// TODO: �ڴ������������û����洦��������
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
	// TODO: �ڴ������������û����洦��������
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
	// TODO: �ڴ������������û����洦��������
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
	// TODO: �ڴ������������û����洦��������
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
	// TODO: �ڴ������������û����洦��������
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
	// TODO: �ڴ���������������
	MessageBox(NULL,CString("ͼ��ָ������"),CString("�ָ����"),MB_OK|MB_ICONINFORMATION);
	theProject->RunWorkStep3();
}

void CMagicCabsineDoc::OnUpdateRegionPropDown(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
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
	// TODO: �ڴ������������û����洦��������
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
	// TODO: �ڴ������������û����洦��������
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
	// TODO: �ڴ������������û����洦��������
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
	// TODO: �ڴ������������û����洦��������
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
	// TODO: �ڴ���������������
	MainFrame *mainFrame=(MainFrame*)AfxGetMainWnd();
	mainFrame->OnShowLeftView();
	mainFrame=NULL;
}

void CMagicCabsineDoc::OnShowright()
{
	// TODO: �ڴ���������������
	MainFrame *mainFrame=(MainFrame*)AfxGetMainWnd();
	mainFrame->OnShowRightView();
	mainFrame=NULL;
}

void CMagicCabsineDoc::OnShowboth()
{
	// TODO: �ڴ���������������
	MainFrame *mainFrame=(MainFrame*)AfxGetMainWnd();
	mainFrame->OnShowBothView();
	mainFrame=NULL;
}
