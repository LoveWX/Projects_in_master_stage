#ifndef cmagiccabsinesimulatedatatest
#define cmagiccabsinesimulatedatatest

#include <vector>
#include <cstring>
#include <fstream>
using namespace std;
#include <cv.h>
#include <highgui.h>

#include "CMagicCabsineSimuLine.h"
#include "CMagicCabsineSimulateData.h"
#include "CMagicCabsineSimuLineSet.h"

class CMagicCabsineSimulateData_Test:public CMagicCabsineSimulateData
{
public:
	CMagicCabsineSimulateData_Test(const IplImage *tempSrcImage);//���캯��
	~CMagicCabsineSimulateData_Test();
	void PrepareSimulateData();//�����ɱ��ж�������Ҫ������,׼������ģ��,��isPrepared=true
	void ComputeSimulateData();//����ģ��,��isCalced=true
	void SaveSimulateData();//����ģ������
	void LoadSimulateData();//��ȡģ������
	void SaveSimulateDataFile(string filepath);//����ģ������
	void LoadSimulateDataFile(string filepath);//��ȡģ������
	void DeleteSimulateData();//ɾ��ģ������
	int GetRegionNum(int xx,int yy);//���������������,������Ϊ��opencv�������ʽ
	THREAD_TYPE GetThreadType(int regionNum,int levelNum)const;//�����������
	void SetThreadType(int regionNum,int levelNum,THREAD_TYPE newType);//������������
	int GetRegionArea(int regionNum,int levelNum)const;//����������
	CvScalar GetMainColor(int regionNum,int levelNum)const;//���������ɫ��
	int GetNumOfThread(int regionNum,int levelNum)const;
	void DrawLevelImage(int levelIndex);//�ػ�levelIndex�����ʾͼ��,ͬʱ����displayLevelImage����Ӧ��ͼƬ
	void DrawDisplayImage();//�ػ�����ʾͼƬ

	//�ı�ĳ���������ɫ��,����ģ��Ľ���
	void ChangeMainColor(int regionNum,int levelNum,CvScalar theColor);
	//��toChangeColor��ΪtoChangeColor��affectColor��ƽ��ɫ
	void ChangeSingleColor(CvScalar &toChangeColor,const CvScalar &affectColor);

	//����ÿ��������뷨����
	//void CalcRegionStitchProperty();
	//������theRegionMask��ָ���������ģ������
	void FillContour(IplImage* contour,double percentage,double alpha1,double alpha2,double ratio);
	void processLine(vector<CvPoint>* line,IplImage * contour, int left, int top, int right, int bottom, int k);
	void AddStitch1(CvPoint p1, CvPoint p2);
	void AddStitch2(CvPoint p1, CvPoint p2);
	void DrawSimuLinesInChaosRegion(const vector< vector<int> > &theRegionMask,vector<SimuLine> &simuLineSet,ChaosStitch CS);
	void DrawSimuLinesInOrderlessRegion(const vector< vector<int> > &theRegionMask,vector<SimuLine> &simuLineSet,OrderlessStitch OS);

	//����ĳ����ĳ��ε��������Ͻṹ��ָ�����ڽ���ģ���޸�
	SimuLineSet* GetPointOfSimuLineSet(int regionNum,int levelNum);

	void DrawRegionMask(int regID,IplImage* mask);

protected:
	int maxRegionNum;//��������,����ŷ�ΧΪ[1,maxRegionNum]
	int maxLevelNum;//����κ�,��κŷ�ΧΪ[0,maxLevelNum-1]
	vector< vector<SimuLineSet> > simuLines;//ģ�ⷽ�����ɵ�ģ������,��һά�������,�ڶ�ά�ǲ��

	IplImage *blankImage;//�հ�ͼƬ,�������Ļ���

	void CreatBlankImage();//��blankImageΪ��ԭͼ��С��ͬ�Ŀհ�ͼƬ
private:
	vector<vector<CvPoint>> stitches1;
	vector<vector<CvPoint>> stitches2;
	vector<vector<CvPoint>> StitchSet1;										
	vector<vector<CvPoint>> StitchSet2;
};

#endif
