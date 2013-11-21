#ifndef cmagiccabsinesplitdata
#define cmagiccabsinesplitdata

#include <vector>
#include <cstring>
#include <set>
using namespace std;
#include <cv.h>
#include "ImageRegionOperator.h"

//�û�������Ϣ:���������.h�ļ��ж��彻����Ϣ�Ľṹ��,
//Ȼ���������а����ýṹ����Ϊ��Ա����


class CMagicCabsineSplitData
{
public:
	CMagicCabsineSplitData(const IplImage *tempSrcImage);//���캯��
	virtual ~CMagicCabsineSplitData();//��������,�ͷŻ����е�����,Ŀǰ����Ҫ�ͷ�displayImage��boundaryImage��markImage,��������Ϊ��

	void GetSplitName(string &tempName)const;//��ȡ�ָ��������
	void SetSplitName(const string &tempName);//���÷ָ��������
	void GetSplitTips(string &tempTips)const;//��ȡ�ָ������ʾ
	void SetSplitTips(const string &tempTips);//���÷ָ������ʾ

	//Ӧ���ж����,�������ﶨ���麯������̫��
	//�����û������Ϣ������drawMarks()��ʼ��markImage,��isMarkedΪtrue,��isCalcedΪfalse
	virtual void SetUserMark(vector< vector<CvPoint> > &foreLines,vector< vector<CvPoint> > &backLines);
	//��ȡ�û������Ϣ
	virtual void GetUserMark(vector< vector<CvPoint> > &foreLines,vector< vector<CvPoint> > &backLines);

	virtual void DrawMarks()=0;//���û���ǻ�����Դͼ����,���������markImage��
	IplImage* GetMarkImage()const;//���isMarked==true?����������Ҫ����computeSplitData()���зָ�,����markImage

	IplImage* GetDisplayImage()const;//���isCalc==true?����������Ҫ����computeSplitData()���зָ�,����displayImage
	IplImage* GetBoundaryImage()const;//���isCalc==true?����������Ҫ����computeSplitData()���зָ�,����boundaryImage

	virtual void LoadSplitData();//�麯��,�����ݿ���ļ���������Ҫ������
	virtual void SaveSplitData();//�麯��,���������ݱ��������ݿ���ļ���

	virtual void LoadSplitDataFile(string filepath)=0;//���麯��,���������ݱ������ļ���
	virtual void SaveSplitDataFile(string filepath)=0;//���麯��,���ļ���������Ҫ������

	//�ɷָ�������splitMatrix��������regionMasks
	void ComputeRegionMask();
	//��÷ָ����������������
	void GetSplitResult(vector< vector<int> > &tempMatrix,vector< vector< vector<int> > > &tempMask);

	//���麯��,����ʵ�ָú��������ĳһȫ�������ļ���,������ɺ���isCalced=true
	virtual void ComputeSplitData();

	//ɾ���ָ�����,���ж�̬����Ŀռ䶼Ӧ�ڴ˺������ͷŲ���ָ����Ϊ��,�������������пɵ��������жԸú�����ʵ����������
	virtual void DeleteSplitData()=0;

/************************************************************************/
/* �ָ��޸ĵĺ���                                                       */
/************************************************************************/
	//�ָ�ϲ��޸ĵĲ�������
	void splitRegion(vector<CvPoint> splitLine);
	void mergeRegion(vector<CvPoint> mergeLine);
	void modifyRegion(vector<CvPoint> modifyLine);

	SPLIT_METHOD_TYPE getSplitMethodType(){return methodType;}


	//���ݱ����Ϣ����¼ǰ���ͱ����������:
	//isFrontΪtrue���ʾ�����������ǰ��
	//isFrontΪfalse��ʾ����������Ǳ���
	void markFrontAndBack(vector<CvPoint>& markLine, bool isFront);
	IplImage* GetFrontBackImage()const{return frontBackImg;};

	void regularMarkID();			//������ָ���ߺϲ�֮�󣬱�ǵ�IDֵҲ��֮�ı�

// 	//��ȡ����Ϊ��x��y�������������
// 	const vector<vector<int>>& getTempRegionMask(int x, int y);
	//��ȡ�ָ���������
	vector<vector<int>>& getSplitMat(){return splitMatrix;}
	//���÷ָ����,������������ʱʹ��
	void setSplitMat(vector<vector<int>> &theMat){splitMatrix=theMat;}
	//��ȡ������������
	const vector<vector<vector<int>>>& getMaskMat(){return regionMasks;}
	//��ȡ���ǰ��������
	void getForeBackData(set<int>& tempFrontIDs, set<int>& tempBackIDs);

	//����һ������Ϊǰ�����߱���:���isFrontΪTRUE����Ϊǰ��������Ϊ����
	void setRegionFrontOrBack(int regionID, BOOL isFront);

	//�ػ�һ���������ɫ��
	void rePaintDisplayImg(int regionID, int color_R, int color_G, int color_B);


	//���¹������󣬹���ǰ����ID��ע����ÿ���޸�����֮�󣬵��ꡰ�ɡ������ť֮����ù���
	void regularAllData();

protected:
	void DrawContoursAroundSegments(vector<vector<int>>							   &segmentedImage,
		const int&								width,
		const int&								height,
		const int&								color);


	void computeBoundaryImage();			//�����б߽��ͼ��
	void computeFrontBackImage();			//����ǰ������ͼ��
	void computeMarkedRegionID();			//���ݷָ�ǰ�ı����Ϣ������������ǰ�����Ǳ���


/*	vector<CvPoint> getSplitLine(vector<CvPoint>& line);*/

protected:
	const IplImage *srcImage;//�ָ����õ���Դͼ��
	IplImage *displayImage;//������ʾ�ָ�����ͼ��
	IplImage *boundaryImage;//�зָ���(�߽�)��ǵ�ͼ��

	int width;
	int height;

	string splitName;//�ָ������,�������ݿ����ģ����ӷָ����
	string splitTips;//�ָ������ʾ��Ϣ

	IplImage *markImage;//�����û���ǵ�Դͼ��
	bool isMarked;//��ʶ�û�����Ƿ��Ѿ����,��markImage�Ƿ����

	bool isCalced;//��ʶ�ָ��Ƿ��Ѿ��������,��displayImage��boundaryImage�Ƿ����

	//��Դͼ��ߴ�һ�µĶ�ά�����ʾ�ָ���,���в�ͬ����ֵ��ʾ��ͬ������
	vector< vector<int> > splitMatrix;
	//�������������,ÿ��������Դͼ��ߴ�һ��,��splitMatrix�б�ǵ�����Ž��д洢
	vector< vector< vector<int> > > regionMasks;

	SPLIT_METHOD_TYPE methodType;		//����ָ�����ͣ��ж�����Ҫ�Ľ����������Ƿ���Ҫ�����Ϣ�������Ϣ���������ͣ�ǰ�������ı�ǻ�������ı�ǣ�

	set<int> frontIDs;		//ǰ����ID��
	set<int> backIDs;		//������ID��
	IplImage* frontBackImg;	//ǰ��������ʾͼ��

	ImageRegionOperator* regionOpe;		//��������Ĺ�����

	vector< vector<CvPoint> > foreLines;	//���ǰ��������
	vector< vector<CvPoint> > backLines;	//��Ǳ���������

	//???
	int getMaxNum();
};

#endif
