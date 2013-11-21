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
	CMagicCabsineDataForSimulating();										//构造函数
	CMagicCabsineDataForSimulating(IplImage *theImage);						//含参构造函数
	~CMagicCabsineDataForSimulating();										//析构函数
	void SetSrcImage(IplImage *theImage);								//设置源图像,只修改源图像,而不修改对应的其它特征值

	void PrepareDataForSimulating();										//通过调用各个Load函数读取所有特征数据

	void LoadSplitMatrix();													//从文件或数据库读取分割区域矩阵
	void LoadUniversalProperty_CLD();										//从文件或数据库读取全局特征CLD的结果
	void LoadUniversalProperty_Saliency();									//从文件或数据库读取全局特征显著性的结果
	void LoadUniversalProperty_VectorField();								//从文件或数据库读取全局特征矢量场的结果
	void LoadPortionProperty_AverageColor();								//从文件或数据库读取局部特征区域平均色的结果
	
	void GetSplitMatrix(vector< vector<int> > &theMatrix);					//获得分割区域矩阵
	void GetUniversalProperty_CLD(vector< vector<int> > &theMatrix);		//获得全局特征CLD的结果
	void GetUniversalProperty_Saliency(vector< vector<int> > &theMatrix);	//获得全局特征显著性的结果
	void GetUniversalProperty_VectorField(vector< vector<double> > &theMatrix);//获得全局特征矢量场的结果
	void GetPortionProperty_AverageColor(vector<CvScalar> &theColorList);	//获得局部特征区域平均色的结果
	void GetRegionArea(vector<int> &theRegionArea);							//获得区域面积

	void CalcRegionMasks();													//通过分割区域矩阵splitMatrix计算各区域掩码
	void GetRegionMasks(vector< vector< vector<int> > > &tempRegionMasks);	//获得各个区域掩码
	void GetRegionMask(int numOfRegion,vector< vector<int> > &tempRegionMask);//获得某个区域的掩码

	bool IsRegionFront(int regionID);										//判断这个区域号所代表的区域是否是前景
	
protected:
	IplImage *srcImage;										//源图像
	int height;												//源图像高度
	int width;												//源图像宽度
// 	string thePath;											//所读取的特征文件的路径
	int maxRegionNum;										//最大区域号

	vector< vector<int> > splitMatrix;						//分割区域矩阵
	vector< vector< vector<int> > > regionMasks;			//区域掩码矩阵的集合
	set<int> frontIDs;										//前景区域号的集合
	set<int> backIDs;										//背景区域号的集合

	vector< vector<int> > universalProperty_CLD;			//全局特征CLD的结果矩阵
	vector< vector<int> > universalProperty_Saliency;		//全局特征显著性的结果矩阵
	vector< vector<double> > universalProperty_VectorField;	//全局特征矢量场的结果矩阵

	vector<int> regionArea;									//某区域的像素点个数
	vector<int> portionProperty_AverageColorBlue;			//某区域蓝色的平均值,区域下标从1开始
	vector<int> portionProperty_AverageColorGreen;			//某区域绿色的平均值,区域下标从1开始
	vector<int> portionProperty_AverageColorRed;			//某区域红色的平均值,区域下标从1开始

	void LoadMatrix(string filename,vector< vector<int> > &theMatrix);		//从文件filename中读出矩阵theMatrix的值
	void LoadMatrix(string filename,vector< vector<double> > &theMatrix);	//从文件filename中读出矩阵theMatrix的值

	//特征选择列表
// 	vector<bool> universalPropertySelected;
// 	vector<bool> portionPropertySelected;
};

#endif
