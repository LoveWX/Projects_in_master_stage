#ifndef cmagiccabsinesimulatedata
#define cmagiccabsinesimulatedata

#include <cstring>
#include <vector>
using namespace std;
#include <cv.h>

#include "CMagicCabsineDataForSimulating.h"
#include "CMagicCabsineStitchLibrary.h"

class CMagicCabsineSimulateData
{
public:
	CMagicCabsineSimulateData(const IplImage *tempSrcImage);//构造函数
	//析构函数,释放基类中的数据,目前至少要释放stitchThreads和displayImage和displayEveryLevel,并将其置为空
	virtual ~CMagicCabsineSimulateData();

	void GetSimulateName(string &tempName)const;//获取模拟方法的名称
	void SetSimulateName(const string &tempName);//设置模拟方法的名称
	
	//纯虚函数,子类实现该函数以完成模拟方法数据的准备
	virtual void PrepareSimulateData()=0;//计算完成后置isPrepare=true

	//纯虚函数,子类实现该函数以完成某一模拟方法的计算
	virtual void ComputeSimulateData()=0;//计算完成后置isCalced=true
	
	//返回显示模拟方法计算结果的图像
	IplImage* GetDisplayImage();//检测isCalc==true?若不是则需要调用computeProperty()计算特征,返回displayImage
	void GetLevelImage(vector<IplImage *> &tempLevelImage);//检测isCalc==true?若不是则需要调用computeProperty()计算特征,返回displayEveryLevel
	IplImage* GetSingleLevelImage(int levelIndex);//先检测isCalc的值,返回levelIndex层的显示图像,若无这一层的图像则返回NULL

	//在工程读取时设置计算结果的图像
	void SetDisplayImage(IplImage *tempImage);//设置模拟结果的图像
	void SetLevelImage(vector<IplImage *> &tempLevelImage);//设置单层模拟结果的图像
	
	virtual void LoadSimulateData();//虚函数,从数据库读入所需要的数据
	virtual void SaveSimulateData();//虚函数,将各种数据保存在数据库中

	virtual void LoadSimulateDataFile(string filepath);//虚函数,从文件读入所需要的数据
	virtual void SaveSimulateDataFile(string filepath);//虚函数,将各种数据保存在文件中
	
	//删除特征,所有动态申请的空间都应在此函数中释放并将指针置为空,子类析构函数中可调用其类中对该函数的实现用于析构
	virtual void DeleteSimulateData()=0;

	void GetSplitMatrix(vector< vector<int> > &tempMatrix);//获得分割矩阵

	IplImage* GetSrcImage(){return srcImage;}
	CMagicCabsineDataForSimulating* GetMakeTable(){return theMakeTable;}
	
protected:
	IplImage *srcImage;//模拟方法所使用的源图像
	IplImage *displayImage;//模拟计算结果用于显示的图像
	vector<IplImage *> displayLevelImage;//模拟结果每一层用于显示的图像,下标从0开始

	string simulateName;//模拟方法的名称,方便数据库操作模块添加模拟方法表
	bool isPrepared;//标识模拟所需要的数据是否已经准备好(是否已经从生成表中取出)
	bool isCalced;//标识模拟是否已经计算完成,即stitchThreads和displayImage和displayEveryLevel是否可用

	//该数据放在子类中定义
	//vector< vector<CMagicCabsineSimuLine> > simuLine;//模拟方法生成的模拟数据,第一维是区域号,第二维是层次

	vector< vector<int> > splitMatrix;//从数据库中读出的分割矩阵

	CMagicCabsineDataForSimulating *theMakeTable;//生成表指针
	CMagicCabsineStitchLibrary *theStitchLibrary;//针法库指针
};

#endif
