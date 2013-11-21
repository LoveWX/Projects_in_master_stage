#pragma once
#include "cmagiccabsinesplitdata.h"
#include "Meanshift(C)/msImageProcessor.h"
#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

typedef unsigned int        UINT;

class CMagicCabsineSplitData_Meanshift :
	public CMagicCabsineSplitData
{
public:
	CMagicCabsineSplitData_Meanshift(const IplImage *tempSrcImage);
	~CMagicCabsineSplitData_Meanshift(void);

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

	//===========================================================================
	//	DoMeanShiftSegmentation
	//===========================================================================
	void DoMeanShiftSegmentation(
		const vector<UINT>&						inputImg,
		const int&								width,
		const int&								height,
		vector<UINT>&							segimg,
		const int&								sigmaS,
		const float&							sigmaR,
		const int&								minRegion,
		vector<int>&							labels,
		int&									numlabels);
	//画轮廓边界
	void DrawContoursAroundSegments(
		vector<UINT>&							segmentedImage,
		const int&								width,
		const int&								height,
		const UINT&								color);
};
