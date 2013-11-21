#ifndef cmagiccabsinesplitdata
#define cmagiccabsinesplitdata

#include <vector>
#include <cstring>
#include <set>
using namespace std;
#include <cv.h>
#include "ImageRegionOperator.h"

//用户交互信息:先在子类的.h文件中定义交互信息的结构体,
//然后在子类中包含该结构体作为成员变量


class CMagicCabsineSplitData
{
public:
	CMagicCabsineSplitData(const IplImage *tempSrcImage);//构造函数
	virtual ~CMagicCabsineSplitData();//析构函数,释放基类中的数据,目前至少要释放displayImage和boundaryImage和markImage,并将其置为空

	void GetSplitName(string &tempName)const;//获取分割方法的名称
	void SetSplitName(const string &tempName);//设置分割方法的名称
	void GetSplitTips(string &tempTips)const;//获取分割方法的提示
	void SetSplitTips(const string &tempTips);//设置分割方法的提示

	//应该有定义的,但是这里定义虚函数好像不太好
	//设置用户标记信息并调用drawMarks()初始化markImage,置isMarked为true,置isCalced为false
	virtual void SetUserMark(vector< vector<CvPoint> > &foreLines,vector< vector<CvPoint> > &backLines);
	//获取用户标记信息
	virtual void GetUserMark(vector< vector<CvPoint> > &foreLines,vector< vector<CvPoint> > &backLines);

	virtual void DrawMarks()=0;//将用户标记绘制在源图像上,结果保存在markImage中
	IplImage* GetMarkImage()const;//检测isMarked==true?若不是则需要调用computeSplitData()进行分割,返回markImage

	IplImage* GetDisplayImage()const;//检测isCalc==true?若不是则需要调用computeSplitData()进行分割,返回displayImage
	IplImage* GetBoundaryImage()const;//检测isCalc==true?若不是则需要调用computeSplitData()进行分割,返回boundaryImage

	virtual void LoadSplitData();//虚函数,从数据库或文件读入所需要的数据
	virtual void SaveSplitData();//虚函数,将各种数据保存在数据库或文件中

	virtual void LoadSplitDataFile(string filepath)=0;//纯虚函数,将各种数据保存在文件中
	virtual void SaveSplitDataFile(string filepath)=0;//纯虚函数,从文件读入所需要的数据

	//由分割结果矩阵splitMatrix生成掩码regionMasks
	void ComputeRegionMask();
	//获得分割结果及各区域的掩码
	void GetSplitResult(vector< vector<int> > &tempMatrix,vector< vector< vector<int> > > &tempMask);

	//纯虚函数,子类实现该函数以完成某一全局特征的计算,计算完成后置isCalced=true
	virtual void ComputeSplitData();

	//删除分割数据,所有动态申请的空间都应在此函数中释放并将指针置为空,子类析构函数中可调用其类中对该函数的实现用于析构
	virtual void DeleteSplitData()=0;

/************************************************************************/
/* 分割修改的函数                                                       */
/************************************************************************/
	//分割合并修改的操作函数
	void splitRegion(vector<CvPoint> splitLine);
	void mergeRegion(vector<CvPoint> mergeLine);
	void modifyRegion(vector<CvPoint> modifyLine);

	SPLIT_METHOD_TYPE getSplitMethodType(){return methodType;}


	//根据标记信息，记录前景和背景的区域号:
	//isFront为true则表示标记线条的是前景
	//isFront为false表示标记线条的是背景
	void markFrontAndBack(vector<CvPoint>& markLine, bool isFront);
	IplImage* GetFrontBackImage()const{return frontBackImg;};

	void regularMarkID();			//当区域分割或者合并之后，标记的ID值也随之改变

// 	//获取坐标为（x，y）的区域的掩码
// 	const vector<vector<int>>& getTempRegionMask(int x, int y);
	//获取分割矩阵的引用
	vector<vector<int>>& getSplitMat(){return splitMatrix;}
	//设置分割矩阵,当撤销和重做时使用
	void setSplitMat(vector<vector<int>> &theMat){splitMatrix=theMat;}
	//获取掩码矩阵的引用
	const vector<vector<vector<int>>>& getMaskMat(){return regionMasks;}
	//获取标记前背景数据
	void getForeBackData(set<int>& tempFrontIDs, set<int>& tempBackIDs);

	//设置一个区域为前景或者背景:如果isFront为TRUE，则为前景，否则为背景
	void setRegionFrontOrBack(int regionID, BOOL isFront);

	//重绘一个区域的主色调
	void rePaintDisplayImg(int regionID, int color_R, int color_G, int color_B);


	//重新规整矩阵，规整前背景ID，注意在每次修改区域之后，点完“成”这个按钮之后调用规整
	void regularAllData();

protected:
	void DrawContoursAroundSegments(vector<vector<int>>							   &segmentedImage,
		const int&								width,
		const int&								height,
		const int&								color);


	void computeBoundaryImage();			//计算有边界的图像
	void computeFrontBackImage();			//计算前背景的图像
	void computeMarkedRegionID();			//根据分割前的标记信息计算标记区域是前景还是背景


/*	vector<CvPoint> getSplitLine(vector<CvPoint>& line);*/

protected:
	const IplImage *srcImage;//分割所用到的源图像
	IplImage *displayImage;//用于显示分割结果的图像
	IplImage *boundaryImage;//有分割结果(边界)标记的图像

	int width;
	int height;

	string splitName;//分割方法名称,方便数据库操作模块添加分割方法表
	string splitTips;//分割方法的提示信息

	IplImage *markImage;//包含用户标记的源图像
	bool isMarked;//标识用户标记是否已经完成,即markImage是否可用

	bool isCalced;//标识分割是否已经计算完成,即displayImage及boundaryImage是否可用

	//与源图像尺寸一致的二维数组表示分割结果,其中不同的数值表示不同的区域
	vector< vector<int> > splitMatrix;
	//各个区域的掩码,每个掩码与源图像尺寸一致,以splitMatrix中标记的区域号进行存储
	vector< vector< vector<int> > > regionMasks;

	SPLIT_METHOD_TYPE methodType;		//定义分割方法类型，判断所需要的交互条件：是否需要标记信息，标记信息是哪种类型？前景背景的标记还是区域的标记？

	set<int> frontIDs;		//前景的ID号
	set<int> backIDs;		//背景的ID号
	IplImage* frontBackImg;	//前背景的显示图像

	ImageRegionOperator* regionOpe;		//区域操作的工具类

	vector< vector<CvPoint> > foreLines;	//标记前景的线条
	vector< vector<CvPoint> > backLines;	//标记背景的线条

	//???
	int getMaxNum();
};

#endif
