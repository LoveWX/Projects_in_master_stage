#pragma once

#include <cstring>
#include <vector>
using namespace std;
#include <cv.h>
#include <highgui.h>
#include "MagicCabsineShowBaseView.h"

// CMagicCabsineSimulateView 视图

class CMagicCabsineSimulateView : public CMagicCabsineShowBaseView
{
	DECLARE_DYNCREATE(CMagicCabsineSimulateView)

protected:
	CMagicCabsineSimulateView();           // 动态创建所使用的受保护的构造函数
	virtual ~CMagicCabsineSimulateView();

public:
	virtual void OnDraw(CDC* pDC);      // 重写以绘制该视图
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()

//以下为zhouzhou添加的代码
public:
	//调用showImage2显示图片,在OnDraw中被调用
	void showImage(CDC* pdc, const IplImage* img, CRect windowRect, double showSize, CPoint &top_left);
	void SetDisplayImage(IplImage *tempImage);//设置图片和分割矩阵
protected:
	IplImage *displayImage;
	int levelIndex;//标识这是分层显示的第几层
	double showImage2(CDC* pdc, const IplImage* img, CRect windowRect, double showSize, CPoint &top_left);

	vector<IplImage *> highlightImage;//用于交互的高亮图片
	int currentRegionImage;//标识现在显示的是几号区域高亮的图片

public:
	IplImage* GetDisplayImage();//获取显示的图片
	void SetLevelIndex(int level);//设置这是分层显示的第几层
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

	void CalcHighLightImage(const vector< vector<int> > &splitMatrix);//计算用于交互的高亮图片
	void lightSinglePoint(CvScalar &theColor);//高亮某个像素点

	void CloseView();//关闭当前视图时进行数据的清理
	afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);

	int tabID;
	afx_msg void OnPaint();

//	bool isClicked;
};


