#ifndef cmagiccabsineuniversalpropertyvectorfield
#define cmagiccabsineuniversalpropertyvectorfield

#include <vector>
#include <cstring>
#include <fstream>
using namespace std;
#include <cv.h>
#include <highgui.h>

#include "CMagicCabsineUniversalProperty.h"

class CMagicCabsineUniversalProperty_VectorField:public CMagicCabsineUniversalProperty
{
public:
	CMagicCabsineUniversalProperty_VectorField(const IplImage *tempSrcImage);
	CMagicCabsineUniversalProperty_VectorField(const IplImage *tempSrcImage,
		CMagicCabsineUniversalProperty_CLD *tempCLDPoint);
	~CMagicCabsineUniversalProperty_VectorField();
	void ComputeProperty();//����ȫ������,�������н�������ݵ�׼��
	void SaveProperty();//��������
	void LoadProperty();//��ȡ����
	void SavePropertyFile(string filepath);//��������
	void LoadPropertyFile(string filepath);//��ȡ����
	void DeleteProperty();//ɾ������Ҫ������

	void GetProperty(vector< vector<double> > &tempMatrix);//��������ļ�����

protected:
	int height;//��Ҫ����ľ���ĸ߶�
	int width;//��Ҫ����ľ���Ŀ��
	vector< vector<double> > ansMatrix;//��Ҫ����ľ���

	IplImage* cldImage;		//֮ǰ����õ���Ҫ�õ���cld������

private:
	double ClosenessWeight(CvMat* imMat,int r1,int c1,int r2,int c2);
	double FeatureWeight(CvMat* gdMat,int r1,int c1,int r2,int c2);

	bool isCLDnewed;
	CMagicCabsineUniversalProperty_CLD *pointOfCLD;
};

#endif
