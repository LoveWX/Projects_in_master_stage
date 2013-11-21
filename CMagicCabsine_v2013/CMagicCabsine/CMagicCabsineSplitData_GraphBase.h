#pragma once
#include "cmagiccabsinesplitdata.h"
#include "stdhead.h"


class CMagicCabsineSplitData_GraphBase :
	public CMagicCabsineSplitData
{
public:
	CMagicCabsineSplitData_GraphBase(const IplImage *tempSrcImage);
	~CMagicCabsineSplitData_GraphBase(void);

public:
	void DrawMarks();//将用户标记绘制在源图像上,结果保存在markImage中

	
	void LoadSplitData();//纯虚函数,从数据库或文件读入所需要的数据
	void SaveSplitData();//纯虚函数,将各种数据保存在数据库或文件中

	void LoadSplitDataFile(string filepath);//纯虚函数,将各种数据保存在文件中
	void SaveSplitDataFile(string filepath);//纯虚函数,从文件读入所需要的数据

	//纯虚函数,子类实现该函数以完成某一全局特征的计算,计算完成后置isCalced=true
	void ComputeSplitData();

	//删除分割数据,所有动态申请的空间都应在此函数中释放并将指针置为空,子类析构函数中可调用其类中对该函数的实现用于析构
	void DeleteSplitData();

private:
	Mat GetRC(const Mat &img3f, double sigmaDist, double segK, int segMinSize, double segSigma);

	int Quantize(const Mat& img3f, Mat &idx1i, Mat &_color3f, Mat &_colorNum, double ratio = 0.95);

	void DrawContoursAroundSegments(vector<vector<int>> &segmentedImage,
		const int&								width,
		const int&								height,
		const int&								color);
//	void paintRegionResult();

private:
	int regNum;
};

