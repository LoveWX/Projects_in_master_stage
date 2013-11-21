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

//���������ȡֵ��Χ
struct ChaosStitchRange
{
	double densityDefault;		//�ܶ�Ĭ��ֵ
	double lengthDefault;		//����Ĭ��ֵ
	double chaosExtentMin;		//���Ҷ��½�
	double chaosExtentMax;		//���Ҷ��Ͻ�
	double chaosExtentDefault;	//���Ҷ�Ĭ��ֵ
	double thetaMin;			//thetaֵ�½�
	double thetaMax;			//thetaֵ�Ͻ�
	double thetaDefault;		//thetaֵĬ��ֵ
	double betaMin;				//betaֵ�½�
	double betaMax;				//betaֵ�Ͻ�
	double betaDefault;			//betaֵĬ��ֵ
};

//С�������ȡֵ��Χ
struct OrderlessStitchRange
{
	double densityDefault;		//�ܶ�Ĭ��ֵ
	double lengthDefault;		//����Ĭ��ֵ
	double chaosExtentMin;		//���Ҷ��½�
	double chaosExtentMax;		//���Ҷ��Ͻ�
	double chaosExtentDefault;	//���Ҷ�Ĭ��ֵ
	double thetaMin;			//thetaֵ�½�
	double thetaMax;			//thetaֵ�Ͻ�
	double thetaDefault;		//thetaֵĬ��ֵ
	double betaMin;				//betaֵ�½�
	double betaMax;				//betaֵ�Ͻ�
	double betaDefault;			//betaֵĬ��ֵ
};

class CMagicCabsineStitchLibrary
{
public:
	CMagicCabsineStitchLibrary();//����Initialization()��ʼ��������
	~CMagicCabsineStitchLibrary();
	void GetChaosVerticalCross(ChaosStitch &tempChaoStitch);			//��ô������������һ�����
	void GetChaosHorizontalCross(ChaosStitch &tempChaoStitch);			//��ô�����ύ���һ�����
	void GetChaosVectorFieldCross(ChaosStitch &tempChaoStitch);			//��ô�����ʸ���������һ�����
	void GetOrderlessCross(OrderlessStitch &tempOrderlessStitch);		//���С�����һ�����

	void AddNewChaosStitch(ChaosStitch tempChaosStitch);
	void RemoveStitch(int nItem);
	void ModifyChaosStitch(int nItem,ChaosStitch tempChaosStitch);

	int GetOtherStitch(int nItem,ChaosStitch& tempChaosStitch,OrderlessStitch& tempOrderlessStitch);

	void GetOtherChaosStitch(int idx,ChaosStitch& tempChaosStitch);
	void GetOtherOrderlessStitch(int idx,OrderlessStitch& tempOrderlessStitch);

	void SaveStitchFile();//�����뷨����������������ļ�
	void LoadStitchFile();//�������ļ���ȡ�뷨���������

	void GetOtherChaosStitch(vector<ChaosStitch> &tempChaosStitch);					//��ȡ�����Զ���Ĵ������뷨������
	void SetOtherChaosStitch(const vector<ChaosStitch> &tempChaosStitch);			//���������Զ���Ĵ������뷨������
	void GetOtherOrderlessStitch(vector<OrderlessStitch> &tempOrderlessStitch);		//��ȡ�����Զ����С�����뷨������
	void SetOtherOrderlessStitch(const vector<OrderlessStitch> &tempOrderlessStitch);//���������Զ����С�����뷨������

	bool CheckParameters(ChaosStitch tempStitch,STITCH_TYPE tempType);				//�������Ƿ���ȡֵ��Χ��
	bool CheckParameters(OrderlessStitch tempStitch,STITCH_TYPE tempType);			//�������Ƿ���ȡֵ��Χ��
protected:
	void Initialization();//��ʼ�����뷨����,�����������ļ��ж�ȡ�û�������뷨����
	ChaosStitchRange chaosVerticalCross;
	ChaosStitchRange chaosHorizontalCross;
	ChaosStitchRange chaosVectorFieldCross;
	OrderlessStitchRange orderlessCross;
	vector<string> otherChaosStitchName;//�����������뷨������
	vector<string> otherOrderlessStitchName;//����С�����뷨������
	vector<ChaosStitch> otherChaosStitch;//�����������뷨������
	vector<OrderlessStitch> otherOrderlessStitch;//����С�����뷨������
	Random myRandom;//�����������
	string pathOfConfig;//���ñ�洢·��
};

#endif
