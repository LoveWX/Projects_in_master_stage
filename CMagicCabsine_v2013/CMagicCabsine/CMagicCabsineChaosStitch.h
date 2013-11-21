#ifndef cmagiccabsinechaosstitch
#define cmagiccabsinechaosstitch

#include <string>
using namespace std;

//大乱针针法结构体
struct ChaosStitch
{
	double density;			//密度
	double length;			//长度
	double chaosExtent;		//混乱度
	double theta;			//theta值
	double beta;			//beta值
	string stitchName;		//针法名称
	STITCH_TYPE stitchType;	//针法类型

	ChaosStitch();
	ChaosStitch(double tempDensity,double tempLength,double tempChaosExtent,double tempTheta,double tempBeta,
				STITCH_TYPE theStitchType=STITCH_ChaosVectorFieldCross,string theStitchName=string(""));//含参构造函数

	ChaosStitch(const ChaosStitch &tempStitch);//拷贝构造函数
	ChaosStitch& operator =(const ChaosStitch& tempStitch);
};

#endif
