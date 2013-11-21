#ifndef cmagiccabsineuniversalpropertysaliency
#define cmagiccabsineuniversalpropertysaliency

#include <vector>
#include <cstring>
#include <fstream>
using namespace std;
#include <cv.h>
#include <highgui.h>

#include "CMagicCabsineUniversalProperty.h"

class CMagicCabsineUniversalProperty_Saliency:public CMagicCabsineUniversalProperty
{
public:
	CMagicCabsineUniversalProperty_Saliency(const IplImage *tempSrcImage);
	~CMagicCabsineUniversalProperty_Saliency();
	void ComputeProperty();//计算全局特征,测试类中仅完成数据的准备
	void SaveProperty();//保存数据
	void LoadProperty();//读取数据
	void SavePropertyFile(string filepath);//保存数据
	void LoadPropertyFile(string filepath);//读取数据
	void DeleteProperty();//删除不需要的数据

	void GetProperty(vector< vector<float> > &tempMatrix);//获得特征的计算结果

protected:
	int height;//需要保存的矩阵的高度
	int width;//需要保存的矩阵的宽度
	vector< vector<float> > ansMatrix;//需要保存的矩阵
};

#endif
