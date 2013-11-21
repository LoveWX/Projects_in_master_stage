#pragma once


// CMagicCabsineRightView 视图

#include "stdafx.h"
#include <cv.h>

#include "CMagicCabsineDisplayView.h"
#include "CMagicCabsineSimulateView.h"

class CMagicCabsineRightView : public CTabView
{
	DECLARE_DYNCREATE(CMagicCabsineRightView)

protected:
	CMagicCabsineRightView();           // 动态创建所使用的受保护的构造函数
	virtual ~CMagicCabsineRightView();

public:
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
	//由标签类型tabType和类型中下标indexInType获得标签页的下标,参见类中的说明
	int getTabIndex(TABVIEW_TYPE tabType,int indexInType=0);

	//将图片显示在指定的标签中
	void displayImageInTab(CString name,IplImage *display,TABVIEW_TYPE tabType,int indexInType=0);

	//按标签类型tabType和类型中下标indexInType获得标签页视图指针
	void* getTabViewPoint(TABVIEW_TYPE tabType,int indexInType=0);

	//清除指定标签页中的图片
	void clearImageInTab(TABVIEW_TYPE tabType,int indexInType=0);

	//显示指定的标签页
	void myShowTab(TABVIEW_TYPE tabType,int indexInType=0);

	//设置分割矩阵
	void SetSplitMatrix(vector< vector<int> > &tempMatrix);

	//获得当前正在显示的标签页中的图片及对应的编号
	void GetDisplayImage(vector<TABVIEW_TYPE> &tabviewType,vector<int> &indexInType,vector<IplImage *> &theImage);

	//根据编号设置需要显示的标签页中的图片
	void SetDisplayImage(const vector<TABVIEW_TYPE> &tabviewType,const vector<int> &indexInTabview,const vector<IplImage *> &theImage);

	//关闭工程时关闭除原图外的所有标签页
	void CloseTabView();

protected:
	//由于高亮显示的需要,需要在这里放一个分割矩阵
	vector< vector<int> > splitMatrix;
};

