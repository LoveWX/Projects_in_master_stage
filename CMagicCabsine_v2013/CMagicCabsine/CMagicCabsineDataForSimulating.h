#ifndef cmagiccabsinedataforsimulating
#define cmagiccabsinedataforsimulating

#include <string>
#include <vector>
#include <fstream>
#include <set>
using namespace std;
#include "cv.h"

class CMagicCabsineDataForSimulating
{
public:
	CMagicCabsineDataForSimulating();										//���캯��
	CMagicCabsineDataForSimulating(IplImage *theImage);						//���ι��캯��
	~CMagicCabsineDataForSimulating();										//��������
	void SetSrcImage(IplImage *theImage);								//����Դͼ��,ֻ�޸�Դͼ��,�����޸Ķ�Ӧ����������ֵ

	void PrepareDataForSimulating();										//ͨ�����ø���Load������ȡ������������

	void LoadSplitMatrix();													//���ļ������ݿ��ȡ�ָ��������
	void LoadUniversalProperty_CLD();										//���ļ������ݿ��ȡȫ������CLD�Ľ��
	void LoadUniversalProperty_Saliency();									//���ļ������ݿ��ȡȫ�����������ԵĽ��
	void LoadUniversalProperty_VectorField();								//���ļ������ݿ��ȡȫ������ʸ�����Ľ��
	void LoadPortionProperty_AverageColor();								//���ļ������ݿ��ȡ�ֲ���������ƽ��ɫ�Ľ��
	
	void GetSplitMatrix(vector< vector<int> > &theMatrix);					//��÷ָ��������
	void GetUniversalProperty_CLD(vector< vector<int> > &theMatrix);		//���ȫ������CLD�Ľ��
	void GetUniversalProperty_Saliency(vector< vector<int> > &theMatrix);	//���ȫ�����������ԵĽ��
	void GetUniversalProperty_VectorField(vector< vector<double> > &theMatrix);//���ȫ������ʸ�����Ľ��
	void GetPortionProperty_AverageColor(vector<CvScalar> &theColorList);	//��þֲ���������ƽ��ɫ�Ľ��
	void GetRegionArea(vector<int> &theRegionArea);							//����������

	void CalcRegionMasks();													//ͨ���ָ��������splitMatrix�������������
	void GetRegionMasks(vector< vector< vector<int> > > &tempRegionMasks);	//��ø�����������
	void GetRegionMask(int numOfRegion,vector< vector<int> > &tempRegionMask);//���ĳ�����������

	bool IsRegionFront(int regionID);										//�ж���������������������Ƿ���ǰ��
	
protected:
	IplImage *srcImage;										//Դͼ��
	int height;												//Դͼ��߶�
	int width;												//Դͼ����
// 	string thePath;											//����ȡ�������ļ���·��
	int maxRegionNum;										//��������

	vector< vector<int> > splitMatrix;						//�ָ��������
	vector< vector< vector<int> > > regionMasks;			//�����������ļ���
	set<int> frontIDs;										//ǰ������ŵļ���
	set<int> backIDs;										//��������ŵļ���

	vector< vector<int> > universalProperty_CLD;			//ȫ������CLD�Ľ������
	vector< vector<int> > universalProperty_Saliency;		//ȫ�����������ԵĽ������
	vector< vector<double> > universalProperty_VectorField;	//ȫ������ʸ�����Ľ������

	vector<int> regionArea;									//ĳ��������ص����
	vector<int> portionProperty_AverageColorBlue;			//ĳ������ɫ��ƽ��ֵ,�����±��1��ʼ
	vector<int> portionProperty_AverageColorGreen;			//ĳ������ɫ��ƽ��ֵ,�����±��1��ʼ
	vector<int> portionProperty_AverageColorRed;			//ĳ�����ɫ��ƽ��ֵ,�����±��1��ʼ

	void LoadMatrix(string filename,vector< vector<int> > &theMatrix);		//���ļ�filename�ж�������theMatrix��ֵ
	void LoadMatrix(string filename,vector< vector<double> > &theMatrix);	//���ļ�filename�ж�������theMatrix��ֵ

	//����ѡ���б�
// 	vector<bool> universalPropertySelected;
// 	vector<bool> portionPropertySelected;
};

#endif
