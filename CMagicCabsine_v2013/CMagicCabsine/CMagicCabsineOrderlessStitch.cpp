#include "stdafx.h"

#include "CMagicCabsineOrderlessStitch.h"

/*
struct OrderlessStitch
{
	double density;			//�ܶ�
	double length;			//����
	double chaosExtent;		//���Ҷ�
	double theta;			//thetaֵ
	double beta;			//betaֵ
	string stitchName;		//�뷨����
	STITCH_TYPE stitchType;	//�뷨����
	
	OrderlessStitch();
	OrderlessStitch(double tempDensity,double tempLength,double tempChaosExtent,double tempTheta,double tempBeta,
		STITCH_TYPE theStitchType=STITCH_OrderlessCross,string theStitchName=string(""));//���ι��캯��
	
	OrderlessStitch(const OrderlessStitch &tempStitch);//�������캯��
	OrderlessStitch& operator= (const OrderlessStitch &tempStitch);
};
*/

OrderlessStitch::OrderlessStitch()
{
	density=0.5;
	length=10.0;
	chaosExtent=0.9;
	theta=pi/4;
	beta=theta;
	stitchType=STITCH_OrderlessCross;
	stitchName=string("");
}

OrderlessStitch::OrderlessStitch(double tempDensity,double tempLength,double tempChaosExtent,double tempTheta,double tempBeta,
								 STITCH_TYPE theStitchType/* =STITCH_OrderlessCross */,string theStitchName/* =string("") */)
{
	density=tempDensity;
	length=tempLength;
	chaosExtent=tempChaosExtent;
	theta=tempTheta;
	beta=tempBeta;
	stitchType=theStitchType;
	stitchName=theStitchName;
}

OrderlessStitch::OrderlessStitch(const OrderlessStitch &tempStitch)
{
	density=tempStitch.density;
	length=tempStitch.length;
	chaosExtent=tempStitch.chaosExtent;
	theta=tempStitch.theta;
	beta=tempStitch.beta;
	stitchType=tempStitch.stitchType;
	stitchName=tempStitch.stitchName;
}

OrderlessStitch& OrderlessStitch::operator =(const OrderlessStitch &tempStitch)
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
