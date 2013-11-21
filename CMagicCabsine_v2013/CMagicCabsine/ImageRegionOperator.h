#ifndef imageregionoperator
#define imageregionoperator

#include <fstream>
#include <vector>
#include <queue>
using namespace std;
#include "cv.h"
#include "highgui.h"

class ImageRegionOperator
{
public:
	ImageRegionOperator();//构造函数,需要调用SetImageAndMatrix()进行初始化
	ImageRegionOperator(const IplImage *theImage,const vector< vector<int> > &theMatrix);//含参构造函数
	~ImageRegionOperator();//析构函数
	void SetImageAndMatrix(const IplImage *theImage,const vector< vector<int> > &theMatrix);//将图片和对应的区域矩阵传入类中

	IplImage* GetDisplayImage();							//获取显示用的结果图片
	void GetAreaMatrix(vector< vector<int> > &theMatrix);	//获得当前区域矩阵
	void SetAreaMatrix(vector< vector<int> > &theMatrix);	//设置区域矩阵,用于撤销和重做操作
	//获得最大区域号,如果先调用RearrangeRegionNum()重新排列区域号,则该区域号等于区域数
	int GetNumOfRegions();
	//获得当前最大区域号,仅供类内部调用
	int GetMaxRegionNum();					

	//获得区域掩码,选中的区域置1,其它区域置0
	void CalcMasks(int regionNum,vector< vector<int> > &theMasks);					//选择由区域号regionNum指定的区域
	void CalcMasks(const CvPoint &thePoint,vector< vector<int> > &theMasks);		//选择thePoint所在的区域
	void CalcMasks(const vector<CvPoint> &thePoints,vector< vector<int> > &theMasks);//选择thePoints扫过的所有区域

	void CalcAverageColor();//按照areaMatrix计算平均色

	//调用BresenhamConnectPoints()在pointSequence相邻点间插入点以将pointSequence连成8邻接的线
	void BresenhamDrawLine(vector<CvPoint> &pointSequence);
	
	
	void RegionMerge(const vector<CvPoint> &pointSequence);			//区域合并,合并pointSequence扫过的所有区域
	void RegionSplit(const vector<CvPoint> &pointSequence);			//区域分割,pointSequence作为新的边界进行区域分割
	void RegionCircle(const vector<CvPoint> &pointSequence);		//圈选区域,pointSequence圈中的区域成为新区域
	void RegionModifyBoundary(const vector<CvPoint> &pointSequence);//边界修改

	void RearrangeRegionNum();//重新排列区域号,使其为[1,maxRegionNum]

protected:
	IplImage *srcImage;//与区域矩阵对应的原始图像
	IplImage *displayImage;//显示用结果图片,每次区域操作后会进行更新
	int height;//图像高度,区域矩阵第一维长度
	int width;//图像宽度,区域矩阵第二维长度
	vector< vector<int> > areaMatrix;//区域矩阵
	int maxRegionNum;//当前最大区域号

	//使用Bresenham方法在连接(xa,ya)和(xb,yb),产生的点按序插入points中
	void BresenhamConnectPoints(vector<CvPoint> &points,int xa,int ya,int xb,int yb);
	
	bool IsInScale(CvPoint thePoint);		//判断thePoint是否在区域矩阵内
	void PutPointInScale(CvPoint &thePoint);//将thePoint放回区域矩阵内

	//专用的调用函数,在某些代码细节上会有差异
	//区域填充,仅供RegionSplit()调用
	void FillingRegion(vector< vector<int> > &theMasks,CvPoint seedPoint,int newRegionNum);
	//获得圈中的区域,仅供RegionCircle()调用
	void GetCircleRegionMasks(vector< vector<int> > &theMasks,CvPoint seedPoint);
	//获得pointsequence扫过的所有区域的总像素点个数,仅供RegionModifyBoundary()调用
	int CountingRegionPoints(const vector<CvPoint> &pointsequence);
	//获得填充并计算像素点个数,仅供RegionModifyBoundary()调用
	int FillingRegionCountingPoints(vector< vector<int> > &theMasks,CvPoint seedPoint,int newNum);

	//以下为测试用函数,可以删除
public:
	void printImage();
	void testRegion(vector< vector<int> > &theMatrix);
	void testMasks(vector< vector<int> > &masks);
	void printMatrix(vector< vector<int> > &theMatrix);
};

#endif
