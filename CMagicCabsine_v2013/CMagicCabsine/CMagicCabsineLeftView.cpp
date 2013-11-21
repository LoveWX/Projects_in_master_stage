// CMagicCabsineLeftView.cpp : ʵ���ļ�
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


// CMagicCabsineLeftView ���

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


// CMagicCabsineLeftView ��Ϣ�������


//�ɱ�ǩ����tabType���������±�indexInType��ñ�ǩҳ���±�
//�����Ͱ���Ӧ��ϵ��0��ʼ˳������,indexInType������Χ���ܵ���ʧ��
//�����ɹ����ر�ǩҳ���±�,���򷵻�-1
int CMagicCabsineLeftView::getTabIndex(TABVIEW_TYPE tabType,int indexInType)
{
	/*�����Ǳ�ǩ����ʹ�õ�View֮��Ķ�Ӧ��ϵ
	//ԭͼ     1 CMagicCabsineDisplayView     TABTYPE_SRCIMAGE
	//ȫ������ 3 CMagicCabsineDisplayView     TABTYPE_UNIVERSAL
	//�ָ�� 1 CMagicCabsineInteractiveView TABTYPE_SPLIT
	//�ָ��� 2 CMagicCabsineDisplayView     TABTYPE_SPLIT_RES
	//�ֲ����� 1 CMagicCabsineDisplayView     TABTYPE_PORTION
	//ǰ����   1 CMagicCabsineDisplayView	  TABTYPE_SPLIT_RES
	*/
	int ansType=-1;
	switch (tabType)
	{
	case TABTYPE_SRCIMAGE:    //ԭͼ����TABTYPE_SRCIMAGE
		ansType=0;
		break;
	case TABTYPE_UNIVERSAL:   //ȫ����������TABTYPE_UNIVERSAL
		if(indexInType<0||indexInType>2)
		{
			return -1;
		}
		ansType=1+indexInType;//�ָ������
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
	//ͨ��tabType��indexInType�����û����ͼ
	int tabIndex=getTabIndex(tabType,indexInType);
	if(tabIndex==-1)//��ǩ�±����
	{
		return;
	}
	SetActiveView(tabIndex);

	if(tabIndex==4)//Ŀǰֻ��4�ű�ǩ��Ҫ����,5�ű�ǩ��Ҫ����ʱ����Ҫ����
	{
		CMagicCabsineInteractiveView *interactiveView=(CMagicCabsineInteractiveView *)GetActiveView();
	//	CMagicCabsineRegionModifyView *interactiveView=(CMagicCabsineRegionModifyView *)GetActiveView();
		interactiveView->SetDisplayImage(display);
		interactiveView->Invalidate();
		interactiveView=NULL;
		return;
	}
	//��Ҫɾ����������������ǩҳʱ����ɾ�����еĴ���
	else if(tabIndex==5)//Ŀǰֻ��4�ű�ǩ��Ҫ����,5�ű�ǩ��Ҫ����ʱ����Ҫ����
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
	if(tabIndex==-1)//��ǩ�±����
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

	//Ŀǰֻ��4�ű�ǩ��Ҫ����,����Ҫ������
	//5�ű�ǩ��Ҫ����ʱ����Ҫ����,������ʱӦ������ԭͼƬ
	if(tabIndex==4)
	{
		return;
	}

	if(tabIndex==-1)//��ǩ�±����
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
	if(tabIndex==-1)//��ǩ�±����
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

	//��õ�ǰ�ı�ǩҳ�±�,���ڱ���������ʱ�ָ�
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

	//���ԭͼ�ı�ǩ����,��ǩ�±�,��ӦͼƬ
	tabviewType.push_back(TABTYPE_SRCIMAGE);
	indexInType.push_back(0);
	tempPoint=getTabViewPoint(TABTYPE_SRCIMAGE,0);
	CMagicCabsineDisplayView *displayView=(CMagicCabsineDisplayView *)tempPoint;
	theImage.push_back(displayView->GetDisplayImage());

	//����universalSelectedָ����ֵ���ȫ������������,�±�,��ӦͼƬ
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

	//��ӷָ��������,�±�,��Ӧ��ͼƬ
	tabviewType.push_back(TABTYPE_SPLIT);
	indexInType.push_back(0);
	tempPoint=getTabViewPoint(TABTYPE_SPLIT,0);
	CMagicCabsineInteractiveView *interactiveView=(CMagicCabsineInteractiveView *)tempPoint;
	theImage.push_back(interactiveView->GetDisplayImage());

	//��ӷָ�����ʾ������,�±�,��Ӧ��ͼƬ
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

	//����portionSelectedָ����ֵ��Ӿֲ�����������,�±�,��ӦͼƬ
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

	//�ָ�֮ǰѡ��ı�ǩҳ
	SetActiveView(tabIndex);
}

void CMagicCabsineLeftView::SetDisplayImage(const vector<TABVIEW_TYPE> &tabviewType,const vector<int> &indexInType,const vector<IplImage *> &theImage)
{
	//���򿪲�����ʱ��д����
}

void CMagicCabsineLeftView::CloseTabView(int numOfUniversal,int numOfPortion)
{
	int numOfTabview=1+numOfUniversal+3+numOfPortion;//����ֵ��ȫ�������;ֲ������������й�
	int i,tabIndex;
	void *tempPoint;
	CMagicCabsineDisplayView *displayView=NULL;
	CMagicCabsineInteractiveView *interactiveView=NULL;

	//�ر���ʾȫ�������ı�ǩҳ
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
	m_leftView->AddView(RUNTIME_CLASS(CMagicCabsineInteractiveView),CString("�ָ�"));
	m_leftView->AddView(RUNTIME_CLASS(CMagicCabsineRegionModifyView),CString("�ָ���1"));
	m_leftView->AddView(RUNTIME_CLASS(CMagicCabsineDisplayView),CString("�ָ���2"));
	m_leftView->AddView(RUNTIME_CLASS(CMagicCabsineDisplayView),CString("ǰ����"));
	*/
	//Note:дmodifyView��closeView����
	//�رշָ����Ӧ�ı�ǩҳ
	tabIndex=getTabIndex(TABTYPE_SPLIT,0);
	SetActiveView(tabIndex);
	tempPoint=(void *)GetActiveView();
	interactiveView=(CMagicCabsineInteractiveView *)tempPoint;
	interactiveView->CloseView();
	this->GetTabControl().ShowTab(tabIndex,FALSE);

	//�رշָ�����Ӧ�ı�ǩҳ
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
	//�ر�ǰ������ǩҳ
	tabIndex=getTabIndex(TABTYPE_SPLIT_RES,2);
	SetActiveView(tabIndex);
	tempPoint=(void *)GetActiveView();
	displayView=(CMagicCabsineDisplayView *)tempPoint;
	displayView->CloseView();
	this->GetTabControl().ShowTab(tabIndex,FALSE);

	//�ر���ʾ�ֲ������ı�ǩҳ
	for(i=0;i<numOfPortion;i++)
	{
		tabIndex=getTabIndex(TABTYPE_PORTION,i);
		SetActiveView(tabIndex);
		tempPoint=(void *)GetActiveView();
		displayView=(CMagicCabsineDisplayView *)tempPoint;
		displayView->CloseView();
		this->GetTabControl().ShowTab(tabIndex,FALSE);
	}

	//�����ʾԭͼ�ı�ǩҳ�ϵ�ͼƬ
	clearImageInTab(TABTYPE_SRCIMAGE,0);

	tempPoint=NULL;
	displayView=NULL;
	interactiveView=NULL;
}
