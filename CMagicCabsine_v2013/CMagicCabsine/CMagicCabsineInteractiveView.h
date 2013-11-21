#pragma once

#include <cstring>
#include <vector>
using namespace std;
#include <cv.h>
#include <highgui.h>

// CMagicCabsineInteractiveView ��ͼ

class CMagicCabsineInteractiveView : public CView
{
	DECLARE_DYNCREATE(CMagicCabsineInteractiveView)

protected:
	CMagicCabsineInteractiveView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CMagicCabsineInteractiveView();

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
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);

//����Ϊzhouzhou��ӵĴ���
protected:
	IplImage *displayImage;//���ڽ�����ԭʼͼ��
	vector<CPoint> foregroundPoints;//���Ϊǰ���ĵ�,��ʱ����,������Ӧ������
	vector<CPoint> backgroundPoints;//���Ϊ�����ĵ�,��ʱ����,������Ӧ������
	vector< vector<CPoint> > foregroundLines;//���Ϊǰ�����ߵļ���
	vector< vector<CPoint> > backgroundLines;//���Ϊ�������ߵļ���
	int maxX;//ͼƬ��MFC�е�һά�����ֵ
	int maxY;//ͼƬ��MFC�еڶ�ά�����ֵ
	CPoint lastDrawingPoint;//���Ƶ����һ����
	BOOL isSplited;//TRUE��ʾ�Ѿ��зָ���,FALSE��ʾû�зָ������ѱ����

	BOOL enableModify;

	//ʹ��thePen�ж������ɫ��������tempPoly
	void drawPolyLine(CDC* pDC,CPen &thePen,vector<CPoint> &tempPoly);

	//��齻���б�ǵĵ��Ƿ���ͼƬ��Χ��
	BOOL isInImageScope(const CPoint &thePoint);
	//���㲻��ͼƬ��Χ��������ΪͼƬ��Χ�ھ�õ�����ĵ�
	BOOL putInImageScope(CPoint &thePoint);
	BOOL putInImageScope(CvPoint &thePoint);

	CPen redPen;//��ɫ����RGB(255,0,0)
	CPen greenPen;//��ɫ����RGB(0,255,0),����ǰ�������
	CPen bluePen;//��ɫ����RGB(0,0,255),���ڱ��������
	CPen yellowPen;//��ɫ����RGB(255, 255, 0),�����޸���

	//���û��ı�ǻ�������ʾͼ����
	void DrawUserMarks();
	IplImage* userMarksImage;
public:
	IplImage* GetDisplayImage();//��ȡ��ʾ��ͼƬ
	void SetDisplayImage(IplImage *tempImage);//����ͼƬ
	void EnableMarking();//���Խ��б��
	void EnableMarkingForeground();//ʹ���Ա��ǰ��
	void EnableMarkingBackground();//ʹ���Ա�Ǳ���
	void DisableMarking();//��ֹ���б��
	void ClearMarking();//����û����,ͬʱ��isSplitedΪFALSE
	BOOL IsSplited();//�Ƿ��Ѿ��зָ���
	void SetSplitDone();//����isSplitedΪTRUE,���ڱ�ʾ���Խ����ָ�׶�

	//��ñ�ǵ�ǰ����ͱ�����,���ݷָ���Ĳ�ͬ�ú�����Ҫ��д
	void GetCvPoint(vector< vector<CvPoint> > &foreLines,vector< vector<CvPoint> > &backLines);

	//�����û���ǵ�ǰ�������ͱ�������,����������ʾͼ����
	void SetCvPoint(const vector< vector<CvPoint> > &foreLines,const vector< vector<CvPoint> > &backLines);

	//����showImage2��ʾͼƬ,��OnDraw�б�����
	void ShowImage(CDC* pDC,const IplImage* img,CRect windowRect,double showSize,CPoint &top_left);

	void CloseView();//�رյ�ǰ��ͼʱ�������ݵ�����

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
	BOOL isMarkingForeground;//ǰ���ܷ���
	BOOL isMarkingBackground;//�����ܷ���
	BOOL isMerge;			//�ܷ�ϲ�����	
	BOOL isSplit;			//�ܷ�ָ�����
	BOOL isModify;			//�ܷ��޸ı߽�
	BOOL isStartDraw;	//�Ƿ�ʼ����
	vector<CPoint> splitLine;

	vector<CvPoint> getSplitLine(vector<CPoint>& line);		//��CPointתΪCvPoint
	vector<CPoint> breseMarkLine(vector<CPoint>& line);		//��ֵ�������
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

