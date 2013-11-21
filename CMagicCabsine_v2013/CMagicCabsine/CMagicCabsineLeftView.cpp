// CMagicCabsineLeftView.cpp : 实现文件
//

#include "stdafx.h"
#include "CMagicCabsine.h"
#include "CMagicCabsineLeftView.h"
#include "CMagicCabsineRegionModifyView.h"


// CMagicCabsineLeftView

IMPLEMENT_DYNCREATE(CMagicCabsineLeftView, CTabView)

CMagicCabsineLeftView::CMagicCabsineLeftView()
{

}

CMagicCabsineLeftView::~CMagicCabsineLeftView()
{
}

BEGIN_MESSAGE_MAP(CMagicCabsineLeftView, CTabView)
END_MESSAGE_MAP()


// CMagicCabsineLeftView 诊断

#ifdef _DEBUG
void CMagicCabsineLeftView::AssertValid() const
{
	CTabView::AssertValid();
}

#ifndef _WIN32_WCE
void CMagicCabsineLeftView::Dump(CDumpContext& dc) const
{
	CTabView::Dump(dc);
}
#endif
#endif //_DEBUG


// CMagicCabsineLeftView 消息处理程序


//由标签类型tabType和类型中下标indexInType获得标签页的下标
//各类型按对应关系从0开始顺序排列,indexInType超出范围可能导致失败
//函数成功返回标签页的下标,否则返回-1
int CMagicCabsineLeftView::getTabIndex(TABVIEW_TYPE tabType,int indexInType)
{
	/*下面是标签和所使用的View之间的对应关系
	//原图     1 CMagicCabsineDisplayView     TABTYPE_SRCIMAGE
	//全局特征 3 CMagicCabsineDisplayView     TABTYPE_UNIVERSAL
	//分割交互 1 CMagicCabsineInteractiveView TABTYPE_SPLIT
	//分割结果 2 CMagicCabsineDisplayView     TABTYPE_SPLIT_RES
	//局部特征 1 CMagicCabsineDisplayView     TABTYPE_PORTION
	//前背景   1 CMagicCabsineDisplayView	  TABTYPE_SPLIT_RES
	*/
	int ansType=-1;
	switch (tabType)
	{
	case TABTYPE_SRCIMAGE:    //原图类型TABTYPE_SRCIMAGE
		ansType=0;
		break;
	case TABTYPE_UNIVERSAL:   //全局特征类型TABTYPE_UNIVERSAL
		if(indexInType<0||indexInType>2)
		{
			return -1;
		}
		ansType=1+indexInType;//分割交互类型
		break;
	case TABTYPE_SPLIT:
		ansType=4;
		break;
	case TABTYPE_SPLIT_RES:
		if(indexInType<0||indexInType>2)
		{
			return -1;
		}
		ansType=5+indexInType;
		break;
	case TABTYPE_PORTION:
		ansType=8;
		break;
	default:
		ansType=-1;
		break;
	}
	return ansType;
}

void CMagicCabsineLeftView::displayImageInTab
	(CString name,IplImage *display,TABVIEW_TYPE tabType,int indexInType/* =0 */)
{
	//通过tabType和indexInType来设置活动的视图
	int tabIndex=getTabIndex(tabType,indexInType);
	if(tabIndex==-1)//标签下标错误
	{
		return;
	}
	SetActiveView(tabIndex);

	if(tabIndex==4)//目前只有4号标签需要交互,5号标签需要交互时还需要更改
	{
		CMagicCabsineInteractiveView *interactiveView=(CMagicCabsineInteractiveView *)GetActiveView();
	//	CMagicCabsineRegionModifyView *interactiveView=(CMagicCabsineRegionModifyView *)GetActiveView();
		interactiveView->SetDisplayImage(display);
		interactiveView->Invalidate();
		interactiveView=NULL;
		return;
	}
	//需要删除“区域轮廓”标签页时可以删除下列的代码
	else if(tabIndex==5)//目前只有4号标签需要交互,5号标签需要交互时还需要更改
	{
	//	CMagicCabsineInteractiveView *interactiveView=(CMagicCabsineInteractiveView *)GetActiveView();
		CMagicCabsineRegionModifyView *interactiveView=(CMagicCabsineRegionModifyView *)GetActiveView();
		interactiveView->SetDisplayImage(display);
		interactiveView->Invalidate();
		interactiveView=NULL;
		return;
	}
	

	CMagicCabsineDisplayView *displayView=(CMagicCabsineDisplayView *)GetActiveView();
	displayView->SetDisplayImage(display);

	displayView->Invalidate();
	displayView=NULL;
}

void* CMagicCabsineLeftView::getTabViewPoint(TABVIEW_TYPE tabType,int indexInType/* =0 */)
{
	int tabIndex=getTabIndex(tabType,indexInType);
	if(tabIndex==-1)//标签下标错误
	{
		return NULL;
	}
	SetActiveView(tabIndex);
	void *tp=(void *)GetActiveView();
	return tp;
}

void CMagicCabsineLeftView::clearImageInTab(TABVIEW_TYPE tabType,int indexInType/* =0 */)
{
	int tabIndex=getTabIndex(tabType,indexInType);

	//目前只有4号标签需要交互,不需要清理背景
	//5号标签需要交互时还需要更改,清理背景时应该留下原图片
	if(tabIndex==4)
	{
		return;
	}

	if(tabIndex==-1)//标签下标错误
	{
		return;
	}
	SetActiveView(tabIndex);

	CMagicCabsineDisplayView *displayView=(CMagicCabsineDisplayView *)GetActiveView();
	displayView->ClearDisplayImage();
	displayView->Invalidate();
	displayView=NULL;
}

void CMagicCabsineLeftView::myShowTab(TABVIEW_TYPE tabType,int indexInType/* =0 */)
{
	int tabIndex=getTabIndex(tabType,indexInType);
	if(tabIndex==-1)//标签下标错误
	{
		return;
	}
	this->GetTabControl().ShowTab(tabIndex,TRUE);
}

void CMagicCabsineLeftView::GetDisplayImage
	(const vector<bool> &universalSelected,const vector<bool> &portionSelected, 
	vector<TABVIEW_TYPE> &tabviewType,vector<int> &indexInType,vector<IplImage *> &theImage)
{
	tabviewType.clear();
	indexInType.clear();
	theImage.clear();

	//获得当前的标签页下标,便于本函数结束时恢复
	int i;
	int tabIndex=-1;
	int numOfTabview=1+universalSelected.size()+1+3+portionSelected.size();
	void *tempPoint,*currentPoint=(void *)GetActiveView();
	for(i=0;i<numOfTabview;i++)
	{
		SetActiveView(i);
		tempPoint=(void *)GetActiveView();
		if(tempPoint==currentPoint)
		{
			tabIndex=i;
			break;
		}
	}
	tempPoint=NULL;
	currentPoint=NULL;

	//添加原图的标签类型,标签下标,对应图片
	tabviewType.push_back(TABTYPE_SRCIMAGE);
	indexInType.push_back(0);
	tempPoint=getTabViewPoint(TABTYPE_SRCIMAGE,0);
	CMagicCabsineDisplayView *displayView=(CMagicCabsineDisplayView *)tempPoint;
	theImage.push_back(displayView->GetDisplayImage());

	//根据universalSelected指定的值添加全局特征的类型,下标,对应图片
	for(i=0;i<universalSelected.size();i++)
	{
		if(!universalSelected[i])
		{
			continue;
		}
		tabviewType.push_back(TABTYPE_UNIVERSAL);
		indexInType.push_back(i);
		tempPoint=getTabViewPoint(TABTYPE_UNIVERSAL,i);
		displayView=(CMagicCabsineDisplayView *)tempPoint;
		theImage.push_back(displayView->GetDisplayImage());
	}

	//添加分割交互的类型,下标,对应的图片
	tabviewType.push_back(TABTYPE_SPLIT);
	indexInType.push_back(0);
	tempPoint=getTabViewPoint(TABTYPE_SPLIT,0);
	CMagicCabsineInteractiveView *interactiveView=(CMagicCabsineInteractiveView *)tempPoint;
	theImage.push_back(interactiveView->GetDisplayImage());

	//添加分割结果显示的类型,下标,对应的图片
	tabviewType.push_back(TABTYPE_SPLIT_RES);
	indexInType.push_back(0);
	tempPoint=getTabViewPoint(TABTYPE_SPLIT_RES,0);
	CMagicCabsineRegionModifyView *modifyView=(CMagicCabsineRegionModifyView *)tempPoint;
	theImage.push_back(modifyView->GetDisplayImage());
	modifyView=NULL;

	tabviewType.push_back(TABTYPE_SPLIT_RES);
	indexInType.push_back(1);
	tempPoint=getTabViewPoint(TABTYPE_SPLIT_RES,1);
	displayView=(CMagicCabsineDisplayView *)tempPoint;
	theImage.push_back(displayView->GetDisplayImage());

	tabviewType.push_back(TABTYPE_SPLIT_RES);
	indexInType.push_back(2);
	tempPoint=getTabViewPoint(TABTYPE_SPLIT_RES,2);
	displayView=(CMagicCabsineDisplayView *)tempPoint;
	theImage.push_back(displayView->GetDisplayImage());

	//根据portionSelected指定的值添加局部特征的类型,下标,对应图片
	for(i=0;i<portionSelected.size();i++)
	{
		if(!portionSelected[i])
		{
			continue;
		}
		tabviewType.push_back(TABTYPE_PORTION);
		indexInType.push_back(i);
		tempPoint=getTabViewPoint(TABTYPE_PORTION,i);
		displayView=(CMagicCabsineDisplayView *)tempPoint;
		theImage.push_back(displayView->GetDisplayImage());
	}

	//恢复之前选择的标签页
	SetActiveView(tabIndex);
}

void CMagicCabsineLeftView::SetDisplayImage(const vector<TABVIEW_TYPE> &tabviewType,const vector<int> &indexInType,const vector<IplImage *> &theImage)
{
	//做打开操作的时候写代码
}

void CMagicCabsineLeftView::CloseTabView(int numOfUniversal,int numOfPortion)
{
	int numOfTabview=1+numOfUniversal+3+numOfPortion;//该数值与全局特征和局部特征的数量有关
	int i,tabIndex;
	void *tempPoint;
	CMagicCabsineDisplayView *displayView=NULL;
	CMagicCabsineInteractiveView *interactiveView=NULL;

	//关闭显示全局特征的标签页
	for(i=0;i<numOfUniversal;i++)
	{
		tabIndex=getTabIndex(TABTYPE_UNIVERSAL,i);
		SetActiveView(tabIndex);
		tempPoint=(void *)GetActiveView();
		displayView=(CMagicCabsineDisplayView *)tempPoint;
		displayView->CloseView();
		this->GetTabControl().ShowTab(tabIndex,FALSE);
	}

	/*
	m_leftView->AddView(RUNTIME_CLASS(CMagicCabsineInteractiveView),CString("分割"));
	m_leftView->AddView(RUNTIME_CLASS(CMagicCabsineRegionModifyView),CString("分割结果1"));
	m_leftView->AddView(RUNTIME_CLASS(CMagicCabsineDisplayView),CString("分割结果2"));
	m_leftView->AddView(RUNTIME_CLASS(CMagicCabsineDisplayView),CString("前背景"));
	*/
	//Note:写modifyView的closeView函数
	//关闭分割方法对应的标签页
	tabIndex=getTabIndex(TABTYPE_SPLIT,0);
	SetActiveView(tabIndex);
	tempPoint=(void *)GetActiveView();
	interactiveView=(CMagicCabsineInteractiveView *)tempPoint;
	interactiveView->CloseView();
	this->GetTabControl().ShowTab(tabIndex,FALSE);

	//关闭分割结果对应的标签页
	tabIndex=getTabIndex(TABTYPE_SPLIT_RES,0);
	SetActiveView(tabIndex);
	tempPoint=(void *)GetActiveView();
	CMagicCabsineRegionModifyView* modifyView=(CMagicCabsineRegionModifyView *)tempPoint;
	modifyView->CloseView();
	this->GetTabControl().ShowTab(tabIndex,FALSE);

	tabIndex=getTabIndex(TABTYPE_SPLIT_RES,1);
	SetActiveView(tabIndex);
	tempPoint=(void *)GetActiveView();
	displayView=(CMagicCabsineDisplayView *)tempPoint;
	displayView->CloseView();
	this->GetTabControl().ShowTab(tabIndex,FALSE);
	//关闭前背景标签页
	tabIndex=getTabIndex(TABTYPE_SPLIT_RES,2);
	SetActiveView(tabIndex);
	tempPoint=(void *)GetActiveView();
	displayView=(CMagicCabsineDisplayView *)tempPoint;
	displayView->CloseView();
	this->GetTabControl().ShowTab(tabIndex,FALSE);

	//关闭显示局部特征的标签页
	for(i=0;i<numOfPortion;i++)
	{
		tabIndex=getTabIndex(TABTYPE_PORTION,i);
		SetActiveView(tabIndex);
		tempPoint=(void *)GetActiveView();
		displayView=(CMagicCabsineDisplayView *)tempPoint;
		displayView->CloseView();
		this->GetTabControl().ShowTab(tabIndex,FALSE);
	}

	//清除显示原图的标签页上的图片
	clearImageInTab(TABTYPE_SRCIMAGE,0);

	tempPoint=NULL;
	displayView=NULL;
	interactiveView=NULL;
}
