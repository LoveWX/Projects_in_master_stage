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

	//设置用户标记信息并调用drawMarks()初始化markImage,置isMarked为true,置isCalced为false
	void SetUserMark(vector< vector<CvPoint> > &foreLines,vector< vector<CvPoint> > &backLines);
	void GetUserMark(vector< vector<CvPoint> > &foreLines,vector< vector<CvPoint> > &backLines);//获取用户标记信息

	void DrawMarks();//将用户标记绘制在源图像上,结果保存在markImage中

	void LoadSplitData();//将各种数据保存在数据库或文件中
	void SaveSplitData();//从数据库或文件读入所需要的数据

	void LoadSplitDataFile(string filepath);//将各种数据保存在数据库或文件中
	void SaveSplitDataFile(string filepath);//从数据库或文件读入所需要的数据

	void ComputeSplitData();//完成分割的计算,计算完成后置isCalced=true
	void DeleteSplitData();//删除分割数据
protected:
	vector<CvPoint> foregroundPoints;//处理后的输入数据,用户标记的前景
	vector<CvPoint> backgroundPoints;//处理后的输入数据,用户标记的背景

	vector< vector<CvPoint> > foregroundLines;//输入数据,用户标记的前景线条
	vector< vector<CvPoint> > backgroundLines;//输入数据,用户标记的背景线条

	int height;
	int width;
};

#endif
