// CMagicCabsineRightView.cpp : 实现文件
//

#include "stdafx.h"
#include "CMagicCabsine.h"
#include "CMagicCabsineRightView.h"


// CMagicCabsineRightView

IMPLEMENT_DYNCREATE(CMagicCabsineRightView, CTabView)

CMagicCabsineRightView::CMagicCabsineRightView()
{
	splitMatrix.clear();
}

CMagicCabsineRightView::~CMagicCabsineRightView()
{
	splitMatrix.clear();
}

BEGIN_MESSAGE_MAP(CMagicCabsineRightView, CTabView)
END_MESSAGE_MAP()


// CMagicCabsineRightView 诊断

#ifdef _DEBUG
void CMagicCabsineRightView::AssertValid() const
{
	CTabView::AssertValid();
}

#ifndef _WIN32_WCE
void CMagicCabsineRightView::Dump(CDumpContext& dc) const
{
	CTabView::Dump(dc);
}
#endif
#endif //_DEBUG


// CMagicCabsineRightView 消息处理程序

//由标签类型tabType和类型中下标indexInType获得标签页的下标
//各类型按对应关系从0开始顺序排列,indexInType超出范围可能导致失败
//函数成功返回标签页的下标,否则返回-1
int CMagicCabsineRightView::getTabIndex(TABVIEW_TYPE tabType,int indexInType)
{
	/*下面是标签和所使用的View之间的对应关系
	//叠加图像 1 CMagicCabsineDisplayView     TABTYPE_SIMU_ALL
	//分层图像 9 CMagicCabsineSimulateView    TABTYPE_SIMU_LEVEL
	*/
	int ansType=-1;
	switch (tabType)
	{
	case TABTYPE_SIMU_ALL:    //叠加图像类型TABTYPE_SIMU_ALL
		ansType=0;
		break;
	case TABTYPE_SIMU_LEVEL:   //分层图像类型TABTYPE_SIMU_LEVEL
		if(indexInType<0||indexInType>8)
		{
			return -1;
		}
		ansType=1+indexInType;//分层图像类型
		break;
	default:
		ansType=-1;
		break;
	}
	return ansType;
}

void CMagicCabsineRightView::displayImageInTab
	(CString name,IplImage *display,TABVIEW_TYPE tabType,int indexInType/* =0 */)
{
	//通过tabType和indexInType来设置活动的视图
	int tabIndex=getTabIndex(tabType,indexInType);
	if(tabIndex==-1)//标签下标错误
	{
		return;
	}
	SetActiveView(tabIndex);

	if(tabIndex==0)//目前只有0号标签不需要交互
	{
		CMagicCabsineDisplayView *displayView=(CMagicCabsineDisplayView *)GetActiveView();
		displayView->SetDisplayImage(display);
		displayView->Invalidate();
		displayView=NULL;
		return;
	}
	CMagicCabsineSimulateView *simulateView=(CMagicCabsineSimulateView *)GetActiveView();
	simulateView->SetLevelIndex(indexInType);
	simulateView->SetDisplayImage(display);
	if(splitMatrix.size()>0)//在载入工程时可能不需要计算高亮图片
	{
// 		simulateView->CalcHighLightImage(splitMatrix);
	}
	simulateView->Invalidate();
	simulateView=NULL;
}

void* CMagicCabsineRightView::getTabViewPoint(TABVIEW_TYPE tabType,int indexInType/* =0 */)
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

void CMagicCabsineRightView::clearImageInTab(TABVIEW_TYPE tabType,int indexInType/* =0 */)
{
	int tabIndex=getTabIndex(tabType,indexInType);

	if(tabIndex==-1)//标签下标错误
	{
		return;
	}
	//目前只有0号标签需要清理图片
	if(tabIndex!=0)
	{
		return;
	}
	SetActiveView(tabIndex);

	CMagicCabsineDisplayView *displayView=(CMagicCabsineDisplayView *)GetActiveView();
	displayView->ClearDisplayImage();
	displayView->Invalidate();
	displayView=NULL;
}

void CMagicCabsineRightView::myShowTab(TABVIEW_TYPE tabType,int indexInType/* =0 */)
{
	int tabIndex=getTabIndex(tabType,indexInType);
	if(tabIndex==-1)//标签下标错误
	{
		return;
	}
	this->GetTabControl().ShowTab(tabIndex,TRUE);
}

void CMagicCabsineRightView::SetSplitMatrix(vector< vector<int> > &tempMatrix)
{
	splitMatrix=tempMatrix;
}

void CMagicCabsineRightView::GetDisplayImage(vector<TABVIEW_TYPE> &tabviewType,vector<int> &indexInType,vector<IplImage *> &theImage)
{
	tabviewType.clear();
	indexInType.clear();
	theImage.clear();

	//获得当前的标签页下标,便于本函数结束时恢复
	int i;
	int tabIndex=-1;
	int numOfLevel=3;//目前有3层,一共4层
	int numOfTabview=1+numOfLevel;
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
	tabviewType.push_back(TABTYPE_SIMU_ALL);
	indexInType.push_back(0);
	tempPoint=getTabViewPoint(TABTYPE_SIMU_ALL,0);
	CMagicCabsineDisplayView *displayView=(CMagicCabsineDisplayView *)tempPoint;
	theImage.push_back(displayView->GetDisplayImage());

	//添加分层图像的标签类型,标签下标,对应图片
	CMagicCabsineSimulateView *simulateView=NULL;
	for(i=0;i<numOfLevel;i++)
	{
		tabviewType.push_back(TABTYPE_SIMU_LEVEL);
		indexInType.push_back(i);
		tempPoint=getTabViewPoint(TABTYPE_SIMU_LEVEL,i);
		simulateView=(CMagicCabsineSimulateView *)tempPoint;
		theImage.push_back(simulateView->GetDisplayImage());
	}

	//恢复之前选择的标签页
	SetActiveView(tabIndex);
}

void CMagicCabsineRightView::CloseTabView()
{
	int numOfLevel=3;//显示模拟绣制的层数
	int numOfTabview=1+numOfLevel;//该数值模拟绣制的层数有关,加上原图,目前一共是4层
	int i,tabIndex=-1;
	void *tempPoint;
	CMagicCabsineDisplayView *displayView=NULL;
	CMagicCabsineSimulateView *simulateView=NULL;

	//关闭显示模拟绣制结果的标签页
	for(i=0;i<numOfLevel;i++)
	{
		tabIndex=getTabIndex(TABTYPE_SIMU_LEVEL,i);
		SetActiveView(tabIndex);
		tempPoint=(void *)GetActiveView();
		simulateView=(CMagicCabsineSimulateView *)tempPoint;
		simulateView->CloseView();
		this->GetTabControl().ShowTab(tabIndex,FALSE);
	}

	//清除显示模拟结果的标签页上的图片
	clearImageInTab(TABTYPE_SIMU_ALL,0);

	tempPoint=NULL;
	displayView=NULL;
	simulateView=NULL;
}

void CMagicCabsineRightView::SetDisplayImage(const vector<TABVIEW_TYPE> &tabviewType,const vector<int> &indexInTabview,const vector<IplImage *> &theImage)
{
	//添加打开功能时再写代码
}

