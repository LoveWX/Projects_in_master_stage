#ifndef cmagiccabsineorderlessstitch
#define cmagiccabsineorderlessstitch

#include <string>
using namespace std;

//小乱针针法结构体
struct OrderlessStitch
{
	double density;			//密度
	double length;			//长度
	double chaosExtent;		//混乱度
	double theta;			//theta值
	double beta;			//beta值
	string stitchName;		//针法名称
	STITCH_TYPE stitchType;	//针法类型

	OrderlessStitch();
	OrderlessStitch(double tempDensity,double tempLength,double tempChaosExtent,double tempTheta,double tempBeta,
					STITCH_TYPE theStitchType=STITCH_OrderlessCross,string theStitchName=string(""));//含参构造函数

	OrderlessStitch(const OrderlessStitch &tempStitch);//拷贝构造函数
	OrderlessStitch& operator =(const OrderlessStitch &tempStitch);
};

#endif
