#pragma once

#include <cstring>
#include <vector>
using namespace std;
#include <cv.h>
#include <highgui.h>

// CMagicCabsineInteractiveView 视图

class CMagicCabsineInteractiveView : public CView
{
	DECLARE_DYNCREATE(CMagicCabsineInteractiveView)

protected:
	CMagicCabsineInteractiveView();           // 动态创建所使用的受保护的构造函数
	virtual ~CMagicCabsineInteractiveView();

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
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);

//以下为zhouzhou添加的代码
protected:
	IplImage *displayImage;//用于交互的原始图像
	vector<CPoint> foregroundPoints;//标记为前景的点,临时变量,用于响应函数中
	vector<CPoint> backgroundPoints;//标记为背景的点,临时变量,用于响应函数中
	vector< vector<CPoint> > foregroundLines;//标记为前景的线的集合
	vector< vector<CPoint> > backgroundLines;//标记为背景的线的集合
	int maxX;//图片在MFC中第一维的最大值
	int maxY;//图片在MFC中第二维的最大值
	CPoint lastDrawingPoint;//绘制的最后一个点
	BOOL isSplited;//TRUE表示已经有分割结果,FALSE表示没有分割结果或已被清除

	BOOL enableModify;

	//使用thePen中定义的颜色绘制折线tempPoly
	void drawPolyLine(CDC* pDC,CPen &thePen,vector<CPoint> &tempPoly);

	//检查交互中标记的点是否在图片范围内
	BOOL isInImageScope(const CPoint &thePoint);
	//若点不在图片范围内则将其置为图片范围内距该点最近的点
	BOOL putInImageScope(CPoint &thePoint);
	BOOL putInImageScope(CvPoint &thePoint);

	CPen redPen;//红色画笔RGB(255,0,0)
	CPen greenPen;//绿色画笔RGB(0,255,0),用于前景标记线
	CPen bluePen;//蓝色画笔RGB(0,0,255),用于背景标记线
	CPen yellowPen;//黄色画笔RGB(255, 255, 0),用于修改线

	//将用户的标记绘制在显示图像上
	void DrawUserMarks();
	IplImage* userMarksImage;
public:
	IplImage* GetDisplayImage();//获取显示的图片
	void SetDisplayImage(IplImage *tempImage);//设置图片
	void EnableMarking();//可以进行标记
	void EnableMarkingForeground();//使可以标记前景
	void EnableMarkingBackground();//使可以标记背景
	void DisableMarking();//禁止进行标记
	void ClearMarking();//清除用户标记,同时置isSplited为FALSE
	BOOL IsSplited();//是否已经有分割结果
	void SetSplitDone();//设置isSplited为TRUE,用于表示可以结束分割阶段

	//获得标记的前景点和背景点,根据分割方法的不同该函数需要重写
	void GetCvPoint(vector< vector<CvPoint> > &foreLines,vector< vector<CvPoint> > &backLines);

	//设置用户标记的前景线条和背景线条,并绘制在显示图像上
	void SetCvPoint(const vector< vector<CvPoint> > &foreLines,const vector< vector<CvPoint> > &backLines);

	//调用showImage2显示图片,在OnDraw中被调用
	void ShowImage(CDC* pDC,const IplImage* img,CRect windowRect,double showSize,CPoint &top_left);

	void CloseView();//关闭当前视图时进行数据的清理

protected:
	double showImage2(CDC* pDC,const IplImage* img,CRect windowRect,double showSize,CPoint &top_left);

public:
	afx_msg void OnRegionMerge();
	afx_msg void OnRegionSplit();
	afx_msg void OnRegionModify();
	afx_msg void OnUpdateRegionMerge(CCmdUI *pCmdUI);
	afx_msg void OnUpdateRegionSplit(CCmdUI *pCmdUI);
	afx_msg void OnUpdateRegionModify(CCmdUI *pCmdUI);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//afx_msg void OnMarkDone();
protected:
	BOOL isMarkingForeground;//前景能否标记
	BOOL isMarkingBackground;//背景能否标记
	BOOL isMerge;			//能否合并区域	
	BOOL isSplit;			//能否分割区域
	BOOL isModify;			//能否修改边界
	BOOL isStartDraw;	//是否开始画线
	vector<CPoint> splitLine;

	vector<CvPoint> getSplitLine(vector<CPoint>& line);		//将CPoint转为CvPoint
	vector<CPoint> breseMarkLine(vector<CPoint>& line);		//插值标记线条
public:
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnRegionModifyOk();
	afx_msg void OnMarkForeground();
	afx_msg void OnMarkBackground();
	afx_msg void OnMarkRegionLine();
	afx_msg void OnMarkDown();
	afx_msg void OnUpdateMarkForeground(CCmdUI *pCmdUI);
	afx_msg void OnUpdateMarkBackground(CCmdUI *pCmdUI);
	afx_msg void OnUpdateMarkRegionLine(CCmdUI *pCmdUI);
	afx_msg void OnMarkClear();
	afx_msg void OnUpdateMarkDown(CCmdUI *pCmdUI);
	afx_msg void OnUpdateMarkClear(CCmdUI *pCmdUI);
	afx_msg void OnUpdateRegionModifyOk(CCmdUI *pCmdUI);

public:
	afx_msg void OnRegionUndo();
	afx_msg void OnRegionRedo();
	afx_msg void OnUpdateRegionUndo(CCmdUI *pCmdUI);
	afx_msg void OnUpdateRegionRedo(CCmdUI *pCmdUI);
};

