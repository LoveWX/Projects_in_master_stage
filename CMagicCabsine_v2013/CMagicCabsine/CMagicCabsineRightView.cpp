// CMagicCabsineRightView.cpp : ʵ���ļ�
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


// CMagicCabsineRightView ���

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


// CMagicCabsineRightView ��Ϣ�������

//�ɱ�ǩ����tabType���������±�indexInType��ñ�ǩҳ���±�
//�����Ͱ���Ӧ��ϵ��0��ʼ˳������,indexInType������Χ���ܵ���ʧ��
//�����ɹ����ر�ǩҳ���±�,���򷵻�-1
int CMagicCabsineRightView::getTabIndex(TABVIEW_TYPE tabType,int indexInType)
{
	/*�����Ǳ�ǩ����ʹ�õ�View֮��Ķ�Ӧ��ϵ
	//����ͼ�� 1 CMagicCabsineDisplayView     TABTYPE_SIMU_ALL
	//�ֲ�ͼ�� 9 CMagicCabsineSimulateView    TABTYPE_SIMU_LEVEL
	*/
	int ansType=-1;
	switch (tabType)
	{
	case TABTYPE_SIMU_ALL:    //����ͼ������TABTYPE_SIMU_ALL
		ansType=0;
		break;
	case TABTYPE_SIMU_LEVEL:   //�ֲ�ͼ������TABTYPE_SIMU_LEVEL
		if(indexInType<0||indexInType>8)
		{
			return -1;
		}
		ansType=1+indexInType;//�ֲ�ͼ������
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
	//ͨ��tabType��indexInType�����û����ͼ
	int tabIndex=getTabIndex(tabType,indexInType);
	if(tabIndex==-1)//��ǩ�±����
	{
		return;
	}
	SetActiveView(tabIndex);

	if(tabIndex==0)//Ŀǰֻ��0�ű�ǩ����Ҫ����
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
	if(splitMatrix.size()>0)//�����빤��ʱ���ܲ���Ҫ�������ͼƬ
	{
// 		simulateView->CalcHighLightImage(splitMatrix);
	}
	simulateView->Invalidate();
	simulateView=NULL;
}

void* CMagicCabsineRightView::getTabViewPoint(TABVIEW_TYPE tabType,int indexInType/* =0 */)
{
	int tabIndex=getTabIndex(tabType,indexInType);
	if(tabIndex==-1)//��ǩ�±����
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

	if(tabIndex==-1)//��ǩ�±����
	{
		return;
	}
	//Ŀǰֻ��0�ű�ǩ��Ҫ����ͼƬ
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
	if(tabIndex==-1)//��ǩ�±����
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

	//��õ�ǰ�ı�ǩҳ�±�,���ڱ���������ʱ�ָ�
	int i;
	int tabIndex=-1;
	int numOfLevel=3;//Ŀǰ��3��,һ��4��
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

	//���ԭͼ�ı�ǩ����,��ǩ�±�,��ӦͼƬ
	tabviewType.push_back(TABTYPE_SIMU_ALL);
	indexInType.push_back(0);
	tempPoint=getTabViewPoint(TABTYPE_SIMU_ALL,0);
	CMagicCabsineDisplayView *displayView=(CMagicCabsineDisplayView *)tempPoint;
	theImage.push_back(displayView->GetDisplayImage());

	//��ӷֲ�ͼ��ı�ǩ����,��ǩ�±�,��ӦͼƬ
	CMagicCabsineSimulateView *simulateView=NULL;
	for(i=0;i<numOfLevel;i++)
	{
		tabviewType.push_back(TABTYPE_SIMU_LEVEL);
		indexInType.push_back(i);
		tempPoint=getTabViewPoint(TABTYPE_SIMU_LEVEL,i);
		simulateView=(CMagicCabsineSimulateView *)tempPoint;
		theImage.push_back(simulateView->GetDisplayImage());
	}

	//�ָ�֮ǰѡ��ı�ǩҳ
	SetActiveView(tabIndex);
}

void CMagicCabsineRightView::CloseTabView()
{
	int numOfLevel=3;//��ʾģ�����ƵĲ���
	int numOfTabview=1+numOfLevel;//����ֵģ�����ƵĲ����й�,����ԭͼ,Ŀǰһ����4��
	int i,tabIndex=-1;
	void *tempPoint;
	CMagicCabsineDisplayView *displayView=NULL;
	CMagicCabsineSimulateView *simulateView=NULL;

	//�ر���ʾģ�����ƽ���ı�ǩҳ
	for(i=0;i<numOfLevel;i++)
	{
		tabIndex=getTabIndex(TABTYPE_SIMU_LEVEL,i);
		SetActiveView(tabIndex);
		tempPoint=(void *)GetActiveView();
		simulateView=(CMagicCabsineSimulateView *)tempPoint;
		simulateView->CloseView();
		this->GetTabControl().ShowTab(tabIndex,FALSE);
	}

	//�����ʾģ�����ı�ǩҳ�ϵ�ͼƬ
	clearImageInTab(TABTYPE_SIMU_ALL,0);

	tempPoint=NULL;
	displayView=NULL;
	simulateView=NULL;
}

void CMagicCabsineRightView::SetDisplayImage(const vector<TABVIEW_TYPE> &tabviewType,const vector<int> &indexInTabview,const vector<IplImage *> &theImage)
{
	//��Ӵ򿪹���ʱ��д����
}

