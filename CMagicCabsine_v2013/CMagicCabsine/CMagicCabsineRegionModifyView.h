#pragma once
#include <vector>
#include <cv.h>
using namespace std;

// CMagicCabsineRegionModifyView ��ͼ

class CMagicCabsineRegionModifyView : public CView
{
	DECLARE_DYNCREATE(CMagicCabsineRegionModifyView)

protected:
	CMagicCabsineRegionModifyView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CMagicCabsineRegionModifyView();

public:
	virtual void OnDraw(CDC* pDC);      // ��д�Ի��Ƹ���ͼ
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()


protected:
	IplImage *displayImage;//���ڽ�����ԭʼͼ��
	//�������й�����ָ�ͺϲ��Ľ�������
	BOOL isMerge;
	BOOL isSplit;
	BOOL isModify;
	BOOL isMarkFront;
	BOOL isMarkBack;
	BOOL isStartDraw;	//�Ƿ�ʼ����
	vector<CPoint> splitLine;
	int maxX;//ͼƬ��MFC�е�һά�����ֵ
	int maxY;//ͼƬ��MFC�еڶ�ά�����ֵ

	CPen yellowPen;//��ɫ����RGB(255, 255, 0),�����޸���
	CPen greenPen;//��ɫ����RGB(0, 255, 255),���ڱ��������
	CPen redPen;//��ɫ����RGB(255, 0, 0),����ǰ�������

public:
// 	afx_msg void OnRegionMerge();
// 	afx_msg void OnRegionSplit();
// 	afx_msg void OnRegionModify();
// 	afx_msg void OnUpdateRegionMerge(CCmdUI *pCmdUI);
// 	afx_msg void OnUpdateRegionSplit(CCmdUI *pCmdUI);
// 	afx_msg void OnUpdateRegionModify(CCmdUI *pCmdUI);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	// ��ʾͼ��ķ���
	void ShowImage(CDC* pDC,const IplImage* img,CRect windowRect,double showSize,CPoint &top_left);
	double showImage2(CDC* pdc,const IplImage* img,CRect windowRect,double showSize,CPoint &top_left);

	void SetDisplayImage(IplImage *tempImage);
	
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	void showModifyLine(CDC* pDC,CPen &thePen,vector<CPoint> &tempPoly);

	vector<CvPoint> getSplitLine(vector<CPoint>& temp);
	afx_msg void OnRegionMarkFront();
	afx_msg void OnRegionMarkBack();
	afx_msg void OnUpdateRegionMarkFront(CCmdUI *pCmdUI);
	afx_msg void OnUpdateRegionMarkBack(CCmdUI *pCmdUI);

	void CloseView();//�رյ�ǰ��ͼʱ�������ݵ�����
	IplImage* GetDisplayImage();
	void ClearDisplayImage();//�����ʾ��ͼƬ

};


