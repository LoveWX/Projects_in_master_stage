#include "stdafx.h"

#include "CMagicCabsineChaosStitch.h"

/*
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
	
	ChaosStitch(const ChaosStitch &tempChaoStitch);//拷贝构造函数
	ChaosStitch& operator= (const ChaosStitch& tempStitch);
};
*/

ChaosStitch::ChaosStitch()
{
	density=0.5;
	length=10.0;
	chaosExtent=0.15;
	theta=pi*0.25;
	beta=pi/7.2;
	stitchType=STITCH_ChaosVectorFieldCross;
	stitchName=string("");
}

ChaosStitch::ChaosStitch(double tempDensity,double tempLength,double tempChaosExtent,double tempTheta,double tempBeta,
						 STITCH_TYPE theStitchType/* =STITCH_ChaosVectorFieldCross */,string theStitchName/* =string("") */)
{
	density=tempDensity;
	length=tempLength;
	chaosExtent=tempChaosExtent;
	theta=tempTheta;
	beta=tempBeta;
	stitchType=theStitchType;
	stitchName=theStitchName;
}

ChaosStitch::ChaosStitch(const ChaosStitch &tempStitch)
{
	density=tempStitch.density;
	length=tempStitch.length;
	chaosExtent=tempStitch.chaosExtent;
	theta=tempStitch.theta;
	beta=tempStitch.beta;
	stitchType=tempStitch.stitchType;
	stitchName=tempStitch.stitchName;
}

ChaosStitch& ChaosStitch::operator =(const ChaosStitch& tempStitch)
{
	density=tempStitch.density;
	length=tempStitch.length;
	chaosExtent=tempStitch.chaosExtent;
	theta=tempStitch.theta;
	beta=tempStitch.beta;
	stitchType=tempStitch.stitchType;
	stitchName=tempStitch.stitchName;
	return *this;
}
