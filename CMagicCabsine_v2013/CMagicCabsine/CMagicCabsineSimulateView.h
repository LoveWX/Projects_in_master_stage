#pragma once

#include <cstring>
#include <vector>
using namespace std;
#include <cv.h>
#include <highgui.h>
#include "MagicCabsineShowBaseView.h"

// CMagicCabsineSimulateView ��ͼ

class CMagicCabsineSimulateView : public CMagicCabsineShowBaseView
{
	DECLARE_DYNCREATE(CMagicCabsineSimulateView)

protected:
	CMagicCabsineSimulateView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CMagicCabsineSimulateView();

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

//����Ϊzhouzhou��ӵĴ���
public:
	//����showImage2��ʾͼƬ,��OnDraw�б�����
	void showImage(CDC* pdc, const IplImage* img, CRect windowRect, double showSize, CPoint &top_left);
	void SetDisplayImage(IplImage *tempImage);//����ͼƬ�ͷָ����
protected:
	IplImage *displayImage;
	int levelIndex;//��ʶ���Ƿֲ���ʾ�ĵڼ���
	double showImage2(CDC* pdc, const IplImage* img, CRect windowRect, double showSize, CPoint &top_left);

	vector<IplImage *> highlightImage;//���ڽ����ĸ���ͼƬ
	int currentRegionImage;//��ʶ������ʾ���Ǽ������������ͼƬ

public:
	IplImage* GetDisplayImage();//��ȡ��ʾ��ͼƬ
	void SetLevelIndex(int level);//�������Ƿֲ���ʾ�ĵڼ���
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

	void CalcHighLightImage(const vector< vector<int> > &splitMatrix);//�������ڽ����ĸ���ͼƬ
	void lightSinglePoint(CvScalar &theColor);//����ĳ�����ص�

	void CloseView();//�رյ�ǰ��ͼʱ�������ݵ�����
	afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);

	int tabID;
	afx_msg void OnPaint();

//	bool isClicked;
};


