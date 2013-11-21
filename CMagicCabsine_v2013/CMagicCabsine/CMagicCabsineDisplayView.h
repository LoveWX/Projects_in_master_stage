#pragma once

#include "stdAfx.h"
//#include "CMagicCabsineDoc.h"
#include <cv.h>
#include <highgui.h>
#include "MagicCabsineShowBaseView.h"
using namespace std;


// CMagicCabsineDisplayView ��ͼ

class CMagicCabsineDisplayView : public CMagicCabsineShowBaseView
{
	DECLARE_DYNCREATE(CMagicCabsineDisplayView)

protected:
	CMagicCabsineDisplayView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CMagicCabsineDisplayView();

public:
	virtual void OnDraw(CDC* pDC);      // ��д�Ի��Ƹ���ͼ
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
	//����showImage2��ʾͼƬ,��OnDraw�б�����
	void ShowImage(CDC* pDC,const IplImage* img,CRect windowRect,double showSize,CPoint &top_left);
	void SetDisplayImage(IplImage *tempImage);//������ʾ��ͼƬ
	IplImage* GetDisplayImage();//��ȡ��ʾ��ͼƬ
	void ClearDisplayImage();//�����ʾ��ͼƬ
	void CloseView();//�رյ�ǰ��ͼʱ�������ݵ�����
protected:
	IplImage *displayImage;//��ʾ��ͼƬ
// 	IplImage *blankImage;//��ԭͼ�ߴ���ͬ�Ŀհ�ͼƬ��������ͼ�в�������
	double showImage2(CDC* pDC,const IplImage* img,CRect windowRect,double showSize,CPoint &top_left);

	afx_msg void OnPaint();

	afx_msg BOOL OnEraseBkgnd(CDC* pDC)  ;
};
