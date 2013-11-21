#ifndef cmagiccabsineportionpropertyaveragecolor
#define cmagiccabsineportionpropertyaveragecolor

#include <cstring>
#include <vector>
#include <fstream>
using namespace std;
#include <cv.h>

#include "CMagicCabsinePortionProperty.h"

class CMagicCabsinePortionProperty_AverageColor:public CMagicCabsinePortionProperty
{
public:
	//子类构造函数
	CMagicCabsinePortionProperty_AverageColor(	const IplImage *tempSrcImage,
												vector< vector<int> > &tempSplitMatrix,
												vector< vector< vector<int> > > &tempRegionMasks);
	~CMagicCabsinePortionProperty_AverageColor();//析构函数,会调用DeleteProperty()
	void ComputeProperty();				//实现基类中纯虚函数,完成局部特征的计算,置isCalced为true
	void SaveProperty();				//实现基类中纯虚函数,将各种数据保存在数据库中
	void LoadProperty();				//实现基类中纯虚函数,从数据库读入所需要的数据
	void SavePropertyFile(string filepath);	//实现基类中纯虚函数,将各种数据保存在文件中
	void LoadPropertyFile(string filepath);	//实现基类中纯虚函数,从文件读入所需要的数据
	void DeleteProperty();				//实现基类中纯虚函数,删除该类中的数据

protected:
	int height;							//图像的高度,由子类中的srcImage高度决定
	int width;							//图像的宽度,由子类中的srcImage宽度决定
	int numOfRegion;					//分割矩阵中不同区域的数量
	vector<int> numOfRegionPoints;		//不同区域的点数,下标从1开始
	vector<int> averageBlue;			//某区域蓝色的平均值,下标从1开始
	vector<int> averageGreen;			//某区域绿色的平均值,下标从1开始
	vector<int> averageRed;				//某区域红色的平均值,下标从1开始
};

#endif
