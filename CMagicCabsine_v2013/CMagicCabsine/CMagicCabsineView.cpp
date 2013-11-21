
// CMagicCabsineView.cpp : CMagicCabsineView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "CMagicCabsine.h"
#endif

#include "CMagicCabsineDoc.h"
#include "CMagicCabsineView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMagicCabsineView

IMPLEMENT_DYNCREATE(CMagicCabsineView, CView)

BEGIN_MESSAGE_MAP(CMagicCabsineView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMagicCabsineView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CMagicCabsineView ����/����

CMagicCabsineView::CMagicCabsineView()
{
	// TODO: �ڴ˴���ӹ������

}

CMagicCabsineView::~CMagicCabsineView()
{
}

BOOL CMagicCabsineView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CMagicCabsineView ����

void CMagicCabsineView::OnDraw(CDC* /*pDC*/)
{
	CMagicCabsineDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CMagicCabsineView ��ӡ


void CMagicCabsineView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMagicCabsineView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CMagicCabsineView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CMagicCabsineView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}

void CMagicCabsineView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMagicCabsineView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMagicCabsineView ���

#ifdef _DEBUG
void CMagicCabsineView::AssertValid() const
{
	CView::AssertValid();
}

void CMagicCabsineView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMagicCabsineDoc* CMagicCabsineView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMagicCabsineDoc)));
	return (CMagicCabsineDoc*)m_pDocument;
}
#endif //_DEBUG


// CMagicCabsineView ��Ϣ�������
