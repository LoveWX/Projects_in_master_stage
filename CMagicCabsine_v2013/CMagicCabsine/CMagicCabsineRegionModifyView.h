#pragma once
#include <vector>
#include <cv.h>
using namespace std;

// CMagicCabsineRegionModifyView 视图

class CMagicCabsineRegionModifyView : public CView
{
	DECLARE_DYNCREATE(CMagicCabsineRegionModifyView)

protected:
	CMagicCabsineRegionModifyView();           // 动态创建所使用的受保护的构造函数
	virtual ~CMagicCabsineRegionModifyView();

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


protected:
	IplImage *displayImage;//用于交互的原始图像
	//以下是有关区域分割和合并的交互代码
	BOOL isMerge;
	BOOL isSplit;
	BOOL isModify;
	BOOL isMarkFront;
	BOOL isMarkBack;
	BOOL isStartDraw;	//是否开始画线
	vector<CPoint> splitLine;
	int maxX;//图片在MFC中第一维的最大值
	int maxY;//图片在MFC中第二维的最大值

	CPen yellowPen;//黄色画笔RGB(255, 255, 0),用于修改线
	CPen greenPen;//青色画笔RGB(0, 255, 255),用于背景标记线
	CPen redPen;//红色画笔RGB(255, 0, 0),用于前景标记线

public:
// 	afx_msg void OnRegionMerge();
// 	afx_msg void OnRegionSplit();
// 	afx_msg void OnRegionModify();
// 	afx_msg void OnUpdateRegionMerge(CCmdUI *pCmdUI);
// 	afx_msg void OnUpdateRegionSplit(CCmdUI *pCmdUI);
// 	afx_msg void OnUpdateRegionModify(CCmdUI *pCmdUI);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	// 显示图像的方法
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

	void CloseView();//关闭当前视图时进行数据的清理
	IplImage* GetDisplayImage();
	void ClearDisplayImage();//清除显示的图片

};


