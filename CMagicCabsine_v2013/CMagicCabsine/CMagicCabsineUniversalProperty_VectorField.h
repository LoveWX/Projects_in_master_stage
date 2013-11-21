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
	void ComputeProperty();//计算全局特征,测试类中仅完成数据的准备
	void SaveProperty();//保存数据
	void LoadProperty();//读取数据
	void SavePropertyFile(string filepath);//保存数据
	void LoadPropertyFile(string filepath);//读取数据
	void DeleteProperty();//删除不需要的数据

	void GetProperty(vector< vector<double> > &tempMatrix);//获得特征的计算结果

protected:
	int height;//需要保存的矩阵的高度
	int width;//需要保存的矩阵的宽度
	vector< vector<double> > ansMatrix;//需要保存的矩阵

	IplImage* cldImage;		//之前计算好的需要用到的cld计算结果

private:
	double ClosenessWeight(CvMat* imMat,int r1,int c1,int r2,int c2);
	double FeatureWeight(CvMat* gdMat,int r1,int c1,int r2,int c2);

	bool isCLDnewed;
	CMagicCabsineUniversalProperty_CLD *pointOfCLD;
};

#endif
