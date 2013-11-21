#ifndef imageregionoperator
#define imageregionoperator

#include <fstream>
#include <vector>
#include <queue>
using namespace std;
#include "cv.h"
#include "highgui.h"

class ImageRegionOperator
{
public:
	ImageRegionOperator();//���캯��,��Ҫ����SetImageAndMatrix()���г�ʼ��
	ImageRegionOperator(const IplImage *theImage,const vector< vector<int> > &theMatrix);//���ι��캯��
	~ImageRegionOperator();//��������
	void SetImageAndMatrix(const IplImage *theImage,const vector< vector<int> > &theMatrix);//��ͼƬ�Ͷ�Ӧ���������������

	IplImage* GetDisplayImage();							//��ȡ��ʾ�õĽ��ͼƬ
	void GetAreaMatrix(vector< vector<int> > &theMatrix);	//��õ�ǰ�������
	void SetAreaMatrix(vector< vector<int> > &theMatrix);	//�����������,���ڳ�������������
	//�����������,����ȵ���RearrangeRegionNum()�������������,�������ŵ���������
	int GetNumOfRegions();
	//��õ�ǰ��������,�������ڲ�����
	int GetMaxRegionNum();					

	//�����������,ѡ�е�������1,����������0
	void CalcMasks(int regionNum,vector< vector<int> > &theMasks);					//ѡ���������regionNumָ��������
	void CalcMasks(const CvPoint &thePoint,vector< vector<int> > &theMasks);		//ѡ��thePoint���ڵ�����
	void CalcMasks(const vector<CvPoint> &thePoints,vector< vector<int> > &theMasks);//ѡ��thePointsɨ������������

	void CalcAverageColor();//����areaMatrix����ƽ��ɫ

	//����BresenhamConnectPoints()��pointSequence���ڵ�������Խ�pointSequence����8�ڽӵ���
	void BresenhamDrawLine(vector<CvPoint> &pointSequence);
	
	
	void RegionMerge(const vector<CvPoint> &pointSequence);			//����ϲ�,�ϲ�pointSequenceɨ������������
	void RegionSplit(const vector<CvPoint> &pointSequence);			//����ָ�,pointSequence��Ϊ�µı߽��������ָ�
	void RegionCircle(const vector<CvPoint> &pointSequence);		//Ȧѡ����,pointSequenceȦ�е������Ϊ������
	void RegionModifyBoundary(const vector<CvPoint> &pointSequence);//�߽��޸�

	void RearrangeRegionNum();//�������������,ʹ��Ϊ[1,maxRegionNum]

protected:
	IplImage *srcImage;//����������Ӧ��ԭʼͼ��
	IplImage *displayImage;//��ʾ�ý��ͼƬ,ÿ��������������и���
	int height;//ͼ��߶�,��������һά����
	int width;//ͼ����,�������ڶ�ά����
	vector< vector<int> > areaMatrix;//�������
	int maxRegionNum;//��ǰ��������

	//ʹ��Bresenham����������(xa,ya)��(xb,yb),�����ĵ㰴�����points��
	void BresenhamConnectPoints(vector<CvPoint> &points,int xa,int ya,int xb,int yb);
	
	bool IsInScale(CvPoint thePoint);		//�ж�thePoint�Ƿ������������
	void PutPointInScale(CvPoint &thePoint);//��thePoint�Ż����������

	//ר�õĵ��ú���,��ĳЩ����ϸ���ϻ��в���
	//�������,����RegionSplit()����
	void FillingRegion(vector< vector<int> > &theMasks,CvPoint seedPoint,int newRegionNum);
	//���Ȧ�е�����,����RegionCircle()����
	void GetCircleRegionMasks(vector< vector<int> > &theMasks,CvPoint seedPoint);
	//���pointsequenceɨ������������������ص����,����RegionModifyBoundary()����
	int CountingRegionPoints(const vector<CvPoint> &pointsequence);
	//�����䲢�������ص����,����RegionModifyBoundary()����
	int FillingRegionCountingPoints(vector< vector<int> > &theMasks,CvPoint seedPoint,int newNum);

	//����Ϊ�����ú���,����ɾ��
public:
	void printImage();
	void testRegion(vector< vector<int> > &theMatrix);
	void testMasks(vector< vector<int> > &masks);
	void printMatrix(vector< vector<int> > &theMatrix);
};

#endif
