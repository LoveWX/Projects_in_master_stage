#ifndef cmagiccabsinesimulatedatatest
#define cmagiccabsinesimulatedatatest

#include <vector>
#include <cstring>
#include <fstream>
using namespace std;
#include <cv.h>
#include <highgui.h>

#include "CMagicCabsineSimuLine.h"
#include "CMagicCabsineSimulateData.h"
#include "CMagicCabsineSimuLineSet.h"

class CMagicCabsineSimulateData_Test:public CMagicCabsineSimulateData
{
public:
	CMagicCabsineSimulateData_Test(const IplImage *tempSrcImage);//构造函数
	~CMagicCabsineSimulateData_Test();
	void PrepareSimulateData();//从生成表中读出所需要的数据,准备进行模拟,置isPrepared=true
	void ComputeSimulateData();//进行模拟,置isCalced=true
	void SaveSimulateData();//保存模拟数据
	void LoadSimulateData();//读取模拟数据
	void SaveSimulateDataFile(string filepath);//保存模拟数据
	void LoadSimulateDataFile(string filepath);//读取模拟数据
	void DeleteSimulateData();//删除模拟数据
	int GetRegionNum(int xx,int yy);//根据坐标获得区域号,这里认为是opencv的坐标格式
	THREAD_TYPE GetThreadType(int regionNum,int levelNum)const;//获得绣线类型
	void SetThreadType(int regionNum,int levelNum,THREAD_TYPE newType);//设置绣线类型
	int GetRegionArea(int regionNum,int levelNum)const;//获得区域面积
	CvScalar GetMainColor(int regionNum,int levelNum)const;//获得区域主色调
	int GetNumOfThread(int regionNum,int levelNum)const;
	void DrawLevelImage(int levelIndex);//重绘levelIndex层的显示图像,同时更新displayLevelImage中相应的图片
	void DrawDisplayImage();//重绘结果显示图片

	//改变某个区域的主色调,用于模拟的交互
	void ChangeMainColor(int regionNum,int levelNum,CvScalar theColor);
	//将toChangeColor改为toChangeColor和affectColor的平均色
	void ChangeSingleColor(CvScalar &toChangeColor,const CvScalar &affectColor);

	//计算每个区域的针法参数
	//void CalcRegionStitchProperty();
	//计算由theRegionMask中指定的区域的模拟线条
	void FillContour(IplImage* contour,double percentage,double alpha1,double alpha2,double ratio);
	void processLine(vector<CvPoint>* line,IplImage * contour, int left, int top, int right, int bottom, int k);
	void AddStitch1(CvPoint p1, CvPoint p2);
	void AddStitch2(CvPoint p1, CvPoint p2);
	void DrawSimuLinesInChaosRegion(const vector< vector<int> > &theRegionMask,vector<SimuLine> &simuLineSet,ChaosStitch CS);
	void DrawSimuLinesInOrderlessRegion(const vector< vector<int> > &theRegionMask,vector<SimuLine> &simuLineSet,OrderlessStitch OS);

	//返回某区域某层次的线条集合结构体指针用于交互模块修改
	SimuLineSet* GetPointOfSimuLineSet(int regionNum,int levelNum);

	void DrawRegionMask(int regID,IplImage* mask);

protected:
	int maxRegionNum;//最大区域号,区域号范围为[1,maxRegionNum]
	int maxLevelNum;//最大层次号,层次号范围为[0,maxLevelNum-1]
	vector< vector<SimuLineSet> > simuLines;//模拟方法生成的模拟数据,第一维是区域号,第二维是层次

	IplImage *blankImage;//空白图片,方便结果的绘制

	void CreatBlankImage();//置blankImage为与原图大小相同的空白图片
private:
	vector<vector<CvPoint>> stitches1;
	vector<vector<CvPoint>> stitches2;
	vector<vector<CvPoint>> StitchSet1;										
	vector<vector<CvPoint>> StitchSet2;
};

#endif
