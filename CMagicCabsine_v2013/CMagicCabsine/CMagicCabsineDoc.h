
// CMagicCabsineDoc.h : CMagicCabsineDoc ��Ľӿ�
//


#pragma once

#include "CMagicCabsineProject.h"

class CMagicCabsineDoc : public CDocument
{
protected: // �������л�����
	CMagicCabsineDoc();
	DECLARE_DYNCREATE(CMagicCabsineDoc)

// ����
public:

// ����
public:

// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// ʵ��
public:
	virtual ~CMagicCabsineDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// ����Ϊ����������������������ݵ� Helper ����
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS

//����Ϊzhouzhou��ӵĴ���
protected:
	BOOL CreateFolder(CString strPath);
public:
	afx_msg void OnMenuConfic();
	afx_msg void OnFileNew();
public:
	CMagicCabsineProject *theProject;
	afx_msg void OnMarkForeground();
	afx_msg void OnMarkBackground();
	afx_msg void OnMarkClear();
	afx_msg void OnMarkDone();
	afx_msg void OnSplitDone();
	afx_msg void OnUpdateMarkForeground(CCmdUI *pCmdUI);
	afx_msg void OnUpdateMarkBackground(CCmdUI *pCmdUI);
	afx_msg void OnUpdateMarkClear(CCmdUI *pCmdUI);
	afx_msg void OnUpdateMarkDone(CCmdUI *pCmdUI);
	afx_msg void OnUpdateSplitDone(CCmdUI *pCmdUI);
	afx_msg void OnCanvasSelect();
	afx_msg void OnUpdateCanvasSelect(CCmdUI *pCmdUI);
	afx_msg void OnSimulateDone();
	afx_msg void OnUpdateSimulateDone(CCmdUI *pCmdUI);
	afx_msg void OnUpdateProcessMark(CCmdUI *pCmdUI);
	afx_msg void OnUpdateProcessSimulate(CCmdUI *pCmdUI);
	afx_msg void OnUpdateProcessMachine(CCmdUI *pCmdUI);
	afx_msg void OnFileSave();
	afx_msg void OnFileClose();
	afx_msg void OnFileOpen();
	afx_msg void OnMenuStitchlibrary();
	afx_msg void OnMenuThreadlibrary();
	afx_msg void OnFileImport();
	afx_msg void OnUpdateMenuConfic(CCmdUI *pCmdUI);
	afx_msg void OnUpdateMenuStitchlibrary(CCmdUI *pCmdUI);
	afx_msg void OnUpdateMenuThreadlibrary(CCmdUI *pCmdUI);
	afx_msg void OnUpdateProcessMarkdown(CCmdUI *pCmdUI);
	afx_msg void OnUpdateProcessSplited(CCmdUI *pCmdUI);
	afx_msg void OnRegionPropDown();
	afx_msg void OnUpdateRegionPropDown(CCmdUI *pCmdUI);
	afx_msg void OnUpdateBlankUp2(CCmdUI *pCmdUI);
	afx_msg void OnUpdateBlankUp8(CCmdUI *pCmdUI);
	afx_msg void OnUpdateBlankUp13(CCmdUI *pCmdUI);
	afx_msg void OnUpdateBlankUp15(CCmdUI *pCmdUI);
	afx_msg void OnShowleft();
	afx_msg void OnShowright();
	afx_msg void OnShowboth();
	afx_msg void OnFileSaveAs();
};
