/*
//配置表管理模块,主要为CMagicCabsineConfig类定义及实现
//需要在构造函数中指定图片类型,
//从而在配置文件夹ConfigFile中解析出需要的信息
//2012-11-28,zhouzhou
*/

#ifndef cmagiccabsineconfig
#define cmagiccabsineconfig

#include "stdafx.h"

#include <cstring>
#include <vector>
#include <fstream>
using namespace std;
#include <cv.h>

class CMagicCabsineConfig
{
public:
	CMagicCabsineConfig(IMAGE_TYPE tempImageType);
	~CMagicCabsineConfig();
	int GetNumOfUniversalProperty()const;//返回可选全局特征的数量
	int GetNumOfPortionProperty()const;//返回可选局部特征的数量

	//对于不同的图片类型将pathOfConfig置为其配置文件的默认路径
	void FindoutPathOfConfig();

	void SaveConfigToFile();//将配置表信息保存至文件中
	void LoadConfigFromFile();//从文件中读取配置表信息

	//获取图片类型
	IMAGE_TYPE GetImageType();
	//设置图片类型
	void SetImageType(const IMAGE_TYPE tempImageType);

	//获取配置表选择信息
	void GetSeleted(vector<bool> &tempUniversal,vector<bool> &tempPortion)const;
	//设置配置表选择信息
	void SetSeleted(const vector<bool> &tempUniversal,const vector<bool> &tempPortion);

	//获取所选取的分割方法dll文件的路径
	SPLIT_METHOD_NAME GetSplitDataName(){return splitName;}
	//设置所选取的分割方法dll文件的路径
	void SetSplitDataName(SPLIT_METHOD_NAME tempSplitName){splitName = tempSplitName;}
	// 	//获取所选取的模拟方法dll文件的路径
	// 	void GetPathOfSimulateData(string &tempPathOfSimulate)const;
	// 	//设置所选取的模拟方法dll文件的路径
	// 	void SetPathOfSimulateData(const string &tempPathOfSimulate);

protected:
	IMAGE_TYPE imageType;
	string pathOfConfig;//若工程已经关闭过则该路径可能为空

	int numOfUniversalProperty;//可选全局特征的数量
	int numOfPortionProperty;//可选局部特征的数量

	//所选取的全局特征,true为选择了某特征,false为未选择,长度为可选全局特征的数量
	vector<bool> universalPropertySelected;
	//所选取的局部特征,true为选择了某特征,false为未选择,长度为可选局部特征的数量
	vector<bool> portionPropertySelected;

	//所选择的分割方法，true为选择了这种分割方法，false为不选择
	SPLIT_METHOD_NAME splitName;

	// 	//分割方法的dll文件路径
	// 	string pathOfSplitData;
	// 	//模拟方法的dll文件路径
	// 	string pathOfSimulateData;
};

#endif
