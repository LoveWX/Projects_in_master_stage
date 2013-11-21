#ifndef cmagiccabsineorderlessstitch
#define cmagiccabsineorderlessstitch

#include <string>
using namespace std;

//С�����뷨�ṹ��
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
	OrderlessStitch& operator =(const OrderlessStitch &tempStitch);
};

#endif
