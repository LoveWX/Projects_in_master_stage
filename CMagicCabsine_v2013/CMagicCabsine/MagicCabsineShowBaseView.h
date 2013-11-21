#pragma once


// CMagicCabsineShowBaseView ��ͼ

class CMagicCabsineShowBaseView : public CScrollView
{
	DECLARE_DYNCREATE(CMagicCabsineShowBaseView)
protected:
	CMagicCabsineShowBaseView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CMagicCabsineShowBaseView();

public:
	virtual void OnDraw(CDC* pDC) ;      // ��д�Ի��Ƹ���ͼ
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
public:

	virtual void OnInitialUpdate();     // �����ĵ�һ��


	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
protected:
	CPoint		startPoint;
	CPoint		endPoint;
	bool		startMove;
	CPoint		top_left;			//��ʾλ��
	double		showSize;			//��ʾ����
	int			tempSizeIndex;		//��ʾ������������
public:
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
};


