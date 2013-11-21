#ifndef cmagiccabsinechaosstitch
#define cmagiccabsinechaosstitch

#include <string>
using namespace std;

//�������뷨�ṹ��
struct ChaosStitch
{
	double density;			//�ܶ�
	double length;			//����
	double chaosExtent;		//���Ҷ�
	double theta;			//thetaֵ
	double beta;			//betaֵ
	string stitchName;		//�뷨����
	STITCH_TYPE stitchType;	//�뷨����

	ChaosStitch();
	ChaosStitch(double tempDensity,double tempLength,double tempChaosExtent,double tempTheta,double tempBeta,
				STITCH_TYPE theStitchType=STITCH_ChaosVectorFieldCross,string theStitchName=string(""));//���ι��캯��

	ChaosStitch(const ChaosStitch &tempStitch);//�������캯��
	ChaosStitch& operator =(const ChaosStitch& tempStitch);
};

#endif
