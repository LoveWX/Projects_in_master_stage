#ifndef cmagiccabsinesplitdatatest
#define cmagiccabsinesplitdatatest

#include <vector>
#include <cstring>
#include <fstream>
using namespace std;
#include <cv.h>
#include <highgui.h>

#include "CMagicCabsineSplitData.h"

class CMagicCabsineSplitData_Test:public CMagicCabsineSplitData
{
public:
	CMagicCabsineSplitData_Test(const IplImage *tempSrcImage);
	~CMagicCabsineSplitData_Test();

	//�����û������Ϣ������drawMarks()��ʼ��markImage,��isMarkedΪtrue,��isCalcedΪfalse
	void SetUserMark(vector< vector<CvPoint> > &foreLines,vector< vector<CvPoint> > &backLines);
	void GetUserMark(vector< vector<CvPoint> > &foreLines,vector< vector<CvPoint> > &backLines);//��ȡ�û������Ϣ

	void DrawMarks();//���û���ǻ�����Դͼ����,���������markImage��

	void LoadSplitData();//���������ݱ��������ݿ���ļ���
	void SaveSplitData();//�����ݿ���ļ���������Ҫ������

	void LoadSplitDataFile(string filepath);//���������ݱ��������ݿ���ļ���
	void SaveSplitDataFile(string filepath);//�����ݿ���ļ���������Ҫ������

	void ComputeSplitData();//��ɷָ�ļ���,������ɺ���isCalced=true
	void DeleteSplitData();//ɾ���ָ�����
protected:
	vector<CvPoint> foregroundPoints;//��������������,�û���ǵ�ǰ��
	vector<CvPoint> backgroundPoints;//��������������,�û���ǵı���

	vector< vector<CvPoint> > foregroundLines;//��������,�û���ǵ�ǰ������
	vector< vector<CvPoint> > backgroundLines;//��������,�û���ǵı�������

	int height;
	int width;
};

#endif
