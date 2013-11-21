#ifndef cmagiccabsinestitchlibrary
#define cmagiccabsinestitchlibrary

#include <string>
#include <vector>
#include <fstream>
using namespace std;

#include "random.h"

#include "CMagicCabsineChaosStitch.h"
#include "CMagicCabsineOrderlessStitch.h"

class ParaBound
{
public:
	double DensityMin;
	double DensityMax;
	double LengthMin;
	double LengthMax;
	double ChaosMin;
	double ChaosMax;
	double ThetaMin;
	double ThetaMax;
	double BetaMin;
	double BetaMax;
public:
	ParaBound()
	{
		DensityMin = 0.0;
		DensityMax = 1.0;
		LengthMin = 5.0;
		LengthMax = 30.0;
		ChaosMin = 0.0;
		ChaosMax = 1.0;
		ThetaMin = 0;
		ThetaMax = 180;
		BetaMin = 0;
		BetaMax = 90;
	}
};
struct TempParaVal
{
	CString name;
	double density;
	double length;
	double chaos;
	double theta;
	double beta;
};

//大乱针参数取值范围
struct ChaosStitchRange
{
	double densityDefault;		//密度默认值
	double lengthDefault;		//长度默认值
	double chaosExtentMin;		//混乱度下界
	double chaosExtentMax;		//混乱度上界
	double chaosExtentDefault;	//混乱度默认值
	double thetaMin;			//theta值下界
	double thetaMax;			//theta值上界
	double thetaDefault;		//theta值默认值
	double betaMin;				//beta值下界
	double betaMax;				//beta值上界
	double betaDefault;			//beta值默认值
};

//小乱针参数取值范围
struct OrderlessStitchRange
{
	double densityDefault;		//密度默认值
	double lengthDefault;		//长度默认值
	double chaosExtentMin;		//混乱度下界
	double chaosExtentMax;		//混乱度上界
	double chaosExtentDefault;	//混乱度默认值
	double thetaMin;			//theta值下界
	double thetaMax;			//theta值上界
	double thetaDefault;		//theta值默认值
	double betaMin;				//beta值下界
	double betaMax;				//beta值上界
	double betaDefault;			//beta值默认值
};

class CMagicCabsineStitchLibrary
{
public:
	CMagicCabsineStitchLibrary();//调用Initialization()初始化各参数
	~CMagicCabsineStitchLibrary();
	void GetChaosVerticalCross(ChaosStitch &tempChaoStitch);			//获得大乱针竖交叉的一组参数
	void GetChaosHorizontalCross(ChaosStitch &tempChaoStitch);			//获得大乱针横交叉的一组参数
	void GetChaosVectorFieldCross(ChaosStitch &tempChaoStitch);			//获得大乱针矢量场交叉的一组参数
	void GetOrderlessCross(OrderlessStitch &tempOrderlessStitch);		//获得小乱针的一组参数

	void AddNewChaosStitch(ChaosStitch tempChaosStitch);
	void RemoveStitch(int nItem);
	void ModifyChaosStitch(int nItem,ChaosStitch tempChaosStitch);

	int GetOtherStitch(int nItem,ChaosStitch& tempChaosStitch,OrderlessStitch& tempOrderlessStitch);

	void GetOtherChaosStitch(int idx,ChaosStitch& tempChaosStitch);
	void GetOtherOrderlessStitch(int idx,OrderlessStitch& tempOrderlessStitch);

	void SaveStitchFile();//保存针法库参数集合至配置文件
	void LoadStitchFile();//从配置文件读取针法库参数集合

	void GetOtherChaosStitch(vector<ChaosStitch> &tempChaosStitch);					//获取其它自定义的大乱针针法参数集
	void SetOtherChaosStitch(const vector<ChaosStitch> &tempChaosStitch);			//设置其它自定义的大乱针针法参数集
	void GetOtherOrderlessStitch(vector<OrderlessStitch> &tempOrderlessStitch);		//获取其它自定义的小乱针针法参数集
	void SetOtherOrderlessStitch(const vector<OrderlessStitch> &tempOrderlessStitch);//设置其它自定义的小乱针针法参数集

	bool CheckParameters(ChaosStitch tempStitch,STITCH_TYPE tempType);				//检测参数是否在取值范围内
	bool CheckParameters(OrderlessStitch tempStitch,STITCH_TYPE tempType);			//检测参数是否在取值范围内
protected:
	void Initialization();//初始化各针法参数,包括从配置文件中读取用户定义的针法参数
	ChaosStitchRange chaosVerticalCross;
	ChaosStitchRange chaosHorizontalCross;
	ChaosStitchRange chaosVectorFieldCross;
	OrderlessStitchRange orderlessCross;
	vector<string> otherChaosStitchName;//其它大乱针针法的名称
	vector<string> otherOrderlessStitchName;//其它小乱针针法的名称
	vector<ChaosStitch> otherChaosStitch;//其它大乱针针法参数集
	vector<OrderlessStitch> otherOrderlessStitch;//其它小乱针针法参数集
	Random myRandom;//随机数生成器
	string pathOfConfig;//配置表存储路径
};

#endif
