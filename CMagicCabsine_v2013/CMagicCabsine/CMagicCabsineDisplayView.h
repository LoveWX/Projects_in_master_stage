#pragma once

#include "stdAfx.h"
//#include "CMagicCabsineDoc.h"
#include <cv.h>
#include <highgui.h>
#include "MagicCabsineShowBaseView.h"
using namespace std;


// CMagicCabsineDisplayView 视图

class CMagicCabsineDisplayView : public CMagicCabsineShowBaseView
{
	DECLARE_DYNCREATE(CMagicCabsineDisplayView)

protected:
	CMagicCabsineDisplayView();           // 动态创建所使用的受保护的构造函数
	virtual ~CMagicCabsineDisplayView();

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
	void ShowImage(CDC* pDC,const IplImage* img,CRect windowRect,double showSize,CPoint &top_left);
	void SetDisplayImage(IplImage *tempImage);//设置显示的图片
	IplImage* GetDisplayImage();//获取显示的图片
	void ClearDisplayImage();//清除显示的图片
	void CloseView();//关闭当前视图时进行数据的清理
protected:
	IplImage *displayImage;//显示的图片
// 	IplImage *blankImage;//与原图尺寸相同的空白图片用于在视图中擦除背景
	double showImage2(CDC* pDC,const IplImage* img,CRect windowRect,double showSize,CPoint &top_left);

	afx_msg void OnPaint();

	afx_msg BOOL OnEraseBkgnd(CDC* pDC)  ;
};
