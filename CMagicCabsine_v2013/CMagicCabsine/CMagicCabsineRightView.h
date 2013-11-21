#pragma once


// CMagicCabsineRightView ��ͼ

#include "stdafx.h"
#include <cv.h>

#include "CMagicCabsineDisplayView.h"
#include "CMagicCabsineSimulateView.h"

class CMagicCabsineRightView : public CTabView
{
	DECLARE_DYNCREATE(CMagicCabsineRightView)

protected:
	CMagicCabsineRightView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
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

//����Ϊzhouzhou��ӵĴ���
public:
	//�ɱ�ǩ����tabType���������±�indexInType��ñ�ǩҳ���±�,�μ����е�˵��
	int getTabIndex(TABVIEW_TYPE tabType,int indexInType=0);

	//��ͼƬ��ʾ��ָ���ı�ǩ��
	void displayImageInTab(CString name,IplImage *display,TABVIEW_TYPE tabType,int indexInType=0);

	//����ǩ����tabType���������±�indexInType��ñ�ǩҳ��ͼָ��
	void* getTabViewPoint(TABVIEW_TYPE tabType,int indexInType=0);

	//���ָ����ǩҳ�е�ͼƬ
	void clearImageInTab(TABVIEW_TYPE tabType,int indexInType=0);

	//��ʾָ���ı�ǩҳ
	void myShowTab(TABVIEW_TYPE tabType,int indexInType=0);

	//���÷ָ����
	void SetSplitMatrix(vector< vector<int> > &tempMatrix);

	//��õ�ǰ������ʾ�ı�ǩҳ�е�ͼƬ����Ӧ�ı��
	void GetDisplayImage(vector<TABVIEW_TYPE> &tabviewType,vector<int> &indexInType,vector<IplImage *> &theImage);

	//���ݱ��������Ҫ��ʾ�ı�ǩҳ�е�ͼƬ
	void SetDisplayImage(const vector<TABVIEW_TYPE> &tabviewType,const vector<int> &indexInTabview,const vector<IplImage *> &theImage);

	//�رչ���ʱ�رճ�ԭͼ������б�ǩҳ
	void CloseTabView();

protected:
	//���ڸ�����ʾ����Ҫ,��Ҫ�������һ���ָ����
	vector< vector<int> > splitMatrix;
};

