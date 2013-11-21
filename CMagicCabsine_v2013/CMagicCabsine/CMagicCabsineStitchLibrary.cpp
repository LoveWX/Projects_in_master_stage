#include "stdafx.h"

#include "CMagicCabsineStitchLibrary.h"

/*
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
*/

CMagicCabsineStitchLibrary::CMagicCabsineStitchLibrary()
{
	pathOfConfig=theApp.GetDefaultPath()+string("ConfigFile\\stitchLibrary.config");
	Initialization();
}

CMagicCabsineStitchLibrary::~CMagicCabsineStitchLibrary()
{
	otherChaosStitchName.clear();
	otherOrderlessStitchName.clear();
	otherChaosStitch.clear();
	otherOrderlessStitch.clear();
	pathOfConfig="";
}

void CMagicCabsineStitchLibrary::GetChaosVerticalCross(ChaosStitch &tempChaoStitch)
{
	/*
	tempChaoStitch.density=myRandom.random_real();
	tempChaoStitch.length=myRandom.random_double(5.0,30.0);
	tempChaoStitch.chaosExtent=myRandom.random_double(chaosVerticalCross.chaosExtentMin,chaosVerticalCross.chaosExtentMax);
	tempChaoStitch.theta=myRandom.random_double(chaosVerticalCross.thetaMin,chaosVerticalCross.thetaMax);
	tempChaoStitch.beta=myRandom.random_double(chaosVerticalCross.betaMin,chaosVerticalCross.betaMax);
	*/
	tempChaoStitch.density=0.5;
	tempChaoStitch.length=10.0;
	tempChaoStitch.chaosExtent=0.05;
	tempChaoStitch.theta=myRandom.random_double(chaosVerticalCross.thetaMin,chaosVerticalCross.thetaMax);
	tempChaoStitch.beta=myRandom.random_double(chaosVerticalCross.betaMin,chaosVerticalCross.betaMax);
}

void CMagicCabsineStitchLibrary::GetChaosHorizontalCross(ChaosStitch &tempChaoStitch)
{
	/*
	tempChaoStitch.density=myRandom.random_real();
	tempChaoStitch.length=myRandom.random_double(1e-9,50.0);
	tempChaoStitch.chaosExtent=myRandom.random_double(chaosVectorFieldCross.chaosExtentMin,chaosVectorFieldCross.chaosExtentMax);
	tempChaoStitch.theta=myRandom.random_double(chaosVectorFieldCross.thetaMin,chaosVectorFieldCross.thetaMax);
	tempChaoStitch.beta=myRandom.random_double(chaosVectorFieldCross.betaMin,chaosVectorFieldCross.betaMax);
	*/
	tempChaoStitch.density=0.5;
	tempChaoStitch.length=10.0;
	tempChaoStitch.chaosExtent=0.05;
	tempChaoStitch.theta=myRandom.random_double(chaosHorizontalCross.thetaMin,chaosHorizontalCross.thetaMax);
	tempChaoStitch.beta=myRandom.random_double(chaosHorizontalCross.betaMin,chaosHorizontalCross.betaMax);
}

void CMagicCabsineStitchLibrary::GetOrderlessCross(OrderlessStitch &tempOrderlessStitch)
{
	/*
	tempOrderlessStitch.density=myRandom.random_real();
	tempOrderlessStitch.length=myRandom.random_double(1e-9,50.0);
	tempOrderlessStitch.chaosExtent=myRandom.random_double(orderlessCross.chaosExtentMin,orderlessCross.chaosExtentMax);
	tempOrderlessStitch.theta=myRandom.random_double(orderlessCross.thetaMin,orderlessCross.thetaMax);
	tempOrderlessStitch.beta=myRandom.random_double(orderlessCross.betaMin,orderlessCross.betaMax);
	*/
	tempOrderlessStitch.density=0.6;
	tempOrderlessStitch.length=10.0;
	tempOrderlessStitch.chaosExtent=myRandom.random_double(orderlessCross.chaosExtentMin,orderlessCross.chaosExtentMax);
	tempOrderlessStitch.theta=myRandom.random_double(orderlessCross.thetaMin,orderlessCross.thetaMax);
	tempOrderlessStitch.beta=myRandom.random_double(orderlessCross.betaMin,orderlessCross.betaMax);
}

void CMagicCabsineStitchLibrary::GetChaosVectorFieldCross(ChaosStitch &tempChaoStitch)
{
	/*
	tempChaoStitch.density=myRandom.random_real();
	tempChaoStitch.length=myRandom.random_double(1e-9,50.0);
	tempChaoStitch.chaosExtent=myRandom.random_double(chaosHorizontalCross.chaosExtentMin,chaosHorizontalCross.chaosExtentMax);
	tempChaoStitch.theta=myRandom.random_double(chaosHorizontalCross.thetaMin,chaosHorizontalCross.thetaMax);
	tempChaoStitch.beta=myRandom.random_double(chaosHorizontalCross.betaMin,chaosHorizontalCross.betaMax);
	*/
	tempChaoStitch.density=0.5;
	tempChaoStitch.length=10.0;
	tempChaoStitch.chaosExtent=myRandom.random_double(chaosVectorFieldCross.chaosExtentMin,chaosVectorFieldCross.chaosExtentMax);
	tempChaoStitch.theta=myRandom.random_double(chaosVectorFieldCross.thetaMin,chaosVectorFieldCross.thetaMax);
	tempChaoStitch.beta=myRandom.random_double(chaosVectorFieldCross.betaMin,chaosVectorFieldCross.betaMax);
}

void CMagicCabsineStitchLibrary::AddNewChaosStitch(ChaosStitch tempChaosStitch)
{
	//otherChaosStitchName.push_back(name);
	otherChaosStitch.push_back(tempChaosStitch);
}
void CMagicCabsineStitchLibrary::RemoveStitch(int nItem)
{
	if (nItem>=4)
	{
		int idx = nItem-4;
		if (idx<otherChaosStitch.size())
		{
			vector<ChaosStitch> tmpChaosStitch;
			vector<string> tmpChaosName;
			int i;
			for (i=0;i<idx;i++)
			{
				tmpChaosStitch.push_back(otherChaosStitch[i]);
				//tmpChaosName.push_back(otherChaosStitchName[i]);
			}
			for (i=idx+1;i<otherChaosStitch.size();i++)
			{
				tmpChaosStitch.push_back(otherChaosStitch[i]);
				//tmpChaosName.push_back(otherChaosStitchName[i]);
			}
			otherChaosStitch.clear();
			otherChaosStitch = tmpChaosStitch;
			//otherChaosStitchName.clear();
			//otherChaosStitchName = tmpChaosName;
		}
	}
}
void CMagicCabsineStitchLibrary::ModifyChaosStitch(int nItem,ChaosStitch tempChaosStitch)
{
	if (nItem>=4)
	{
		int idx = nItem-4;
		if (idx<otherChaosStitch.size())
		{
			if (tempChaosStitch.stitchName.length() != 0)
			{
				otherChaosStitch[idx].stitchName = tempChaosStitch.stitchName;
			}
			otherChaosStitch[idx].density = tempChaosStitch.density;
			otherChaosStitch[idx].length = tempChaosStitch.length;
			otherChaosStitch[idx].chaosExtent = tempChaosStitch.chaosExtent;
			otherChaosStitch[idx].theta = tempChaosStitch.theta;
			otherChaosStitch[idx].beta = tempChaosStitch.beta;
		}
	}
}
int CMagicCabsineStitchLibrary::GetOtherStitch(int nItem,ChaosStitch& tempChaosStitch,OrderlessStitch& tempOrderlessStitch)
{
	if (nItem<4)
	{
		return -1;
	}
	int idx = nItem - 4;
	if (idx<otherChaosStitch.size())
	{
		tempChaosStitch = otherChaosStitch[idx];
		return 1;
	}
	int idx1 = idx-otherChaosStitch.size();
	if (idx1<otherOrderlessStitch.size())
	{
		tempOrderlessStitch = otherOrderlessStitch[idx1];
		return 2;
	}
	return -1;
}

void CMagicCabsineStitchLibrary:: GetOtherChaosStitch(int idx,ChaosStitch& tempChaosStitch)
{
	tempChaosStitch = otherChaosStitch[idx];
}

void CMagicCabsineStitchLibrary::GetOtherOrderlessStitch(int idx,OrderlessStitch& tempOrderlessStitch)
{
	tempOrderlessStitch = otherOrderlessStitch[idx];
}

void CMagicCabsineStitchLibrary::SaveStitchFile()
{
	ofstream fout(pathOfConfig.c_str());
	fout.precision(5);
	
	fout<<"STITCH_ChaosVerticalCross:"<<endl;
	fout<<chaosVerticalCross.densityDefault<<' '
		<<chaosVerticalCross.lengthDefault<<' '
		<<chaosVerticalCross.chaosExtentMin<<' '
		<<chaosVerticalCross.chaosExtentMax<<' '
		<<chaosVerticalCross.chaosExtentDefault<<' '
		<<chaosVerticalCross.thetaMin<<' '
		<<chaosVerticalCross.thetaMax<<' '
		<<chaosVerticalCross.thetaDefault<<' '
		<<chaosVerticalCross.betaMin<<' '
		<<chaosVerticalCross.betaMax<<' '
		<<chaosVerticalCross.betaDefault<<endl;

	fout<<"STITCH_ChaosHorizontalCross:"<<endl;
	fout<<chaosHorizontalCross.densityDefault<<' '
		<<chaosHorizontalCross.lengthDefault<<' '
		<<chaosHorizontalCross.chaosExtentMin<<' '
		<<chaosHorizontalCross.chaosExtentMax<<' '
		<<chaosHorizontalCross.chaosExtentDefault<<' '
		<<chaosHorizontalCross.thetaMin<<' '
		<<chaosHorizontalCross.thetaMax<<' '
		<<chaosHorizontalCross.thetaDefault<<' '
		<<chaosHorizontalCross.betaMin<<' '
		<<chaosHorizontalCross.betaMax<<' '
		<<chaosHorizontalCross.betaDefault<<endl;

	fout<<"STITCH_ChaosVectorFieldCross:"<<endl;
	fout<<chaosVectorFieldCross.densityDefault<<' '
		<<chaosVectorFieldCross.lengthDefault<<' '
		<<chaosVectorFieldCross.chaosExtentMin<<' '
		<<chaosVectorFieldCross.chaosExtentMax<<' '
		<<chaosVectorFieldCross.chaosExtentDefault<<' '
		<<chaosVectorFieldCross.thetaMin<<' '
		<<chaosVectorFieldCross.thetaMax<<' '
		<<chaosVectorFieldCross.thetaDefault<<' '
		<<chaosVectorFieldCross.betaMin<<' '
		<<chaosVectorFieldCross.betaMax<<' '
		<<chaosVectorFieldCross.betaDefault<<endl;

	fout<<"STITCH_OrderlessCross:"<<endl;
	fout<<orderlessCross.densityDefault<<' '
		<<orderlessCross.lengthDefault<<' '
		<<orderlessCross.chaosExtentMin<<' '
		<<orderlessCross.chaosExtentMax<<' '
		<<orderlessCross.chaosExtentDefault<<' '
		<<orderlessCross.thetaMin<<' '
		<<orderlessCross.thetaMax<<' '
		<<orderlessCross.thetaDefault<<' '
		<<orderlessCross.betaMin<<' '
		<<orderlessCross.betaMax<<' '
		<<orderlessCross.betaDefault<<endl;

	fout<<"STITCH_Other:"<<endl;
	int i;
	string tempStr;
	fout<<otherChaosStitch.size()<<endl;
	for(i=0;i<otherChaosStitch.size();i++)
	{
		fout<<otherChaosStitch[i].stitchName<<endl;
		fout<<otherChaosStitch[i].density<<' '
			<<otherChaosStitch[i].length<<' '
			<<otherChaosStitch[i].chaosExtent<<' '
			<<otherChaosStitch[i].theta<<' '
			<<otherChaosStitch[i].beta<<endl;
	}

	fout<<otherOrderlessStitch.size()<<endl;
	for(i=0;i<otherOrderlessStitch.size();i++)
	{
		fout<<otherOrderlessStitch[i].stitchName<<endl;
		fout<<otherOrderlessStitch[i].density<<' '
			<<otherOrderlessStitch[i].length<<' '
			<<otherOrderlessStitch[i].chaosExtent<<' '
			<<otherOrderlessStitch[i].theta<<' '
			<<otherOrderlessStitch[i].beta<<endl;
	}

	fout.close();
}

void CMagicCabsineStitchLibrary::LoadStitchFile()
{
	ifstream fin(pathOfConfig.c_str());

	const int SizeOfStr=300;
	char str[SizeOfStr];

	fin.getline(str,SizeOfStr);
	fin>>chaosVerticalCross.densityDefault
		>>chaosVerticalCross.lengthDefault
		>>chaosVerticalCross.chaosExtentMin
		>>chaosVerticalCross.chaosExtentMax
		>>chaosVerticalCross.chaosExtentDefault
		>>chaosVerticalCross.thetaMin
		>>chaosVerticalCross.thetaMax
		>>chaosVerticalCross.thetaDefault
		>>chaosVerticalCross.betaMin
		>>chaosVerticalCross.betaMax
		>>chaosVerticalCross.betaDefault;
	fin.getline(str,SizeOfStr);

	fin.getline(str,SizeOfStr);
	fin>>chaosHorizontalCross.densityDefault
		>>chaosHorizontalCross.lengthDefault
		>>chaosHorizontalCross.chaosExtentMin
		>>chaosHorizontalCross.chaosExtentMax
		>>chaosHorizontalCross.chaosExtentDefault
		>>chaosHorizontalCross.thetaMin
		>>chaosHorizontalCross.thetaMax
		>>chaosHorizontalCross.thetaDefault
		>>chaosHorizontalCross.betaMin
		>>chaosHorizontalCross.betaMax
		>>chaosHorizontalCross.betaDefault;
	fin.getline(str,SizeOfStr);

	fin.getline(str,SizeOfStr);
	fin>>chaosVectorFieldCross.densityDefault
		>>chaosVectorFieldCross.lengthDefault
		>>chaosVectorFieldCross.chaosExtentMin
		>>chaosVectorFieldCross.chaosExtentMax
		>>chaosVectorFieldCross.chaosExtentDefault
		>>chaosVectorFieldCross.thetaMin
		>>chaosVectorFieldCross.thetaMax
		>>chaosVectorFieldCross.thetaDefault
		>>chaosVectorFieldCross.betaMin
		>>chaosVectorFieldCross.betaMax
		>>chaosVectorFieldCross.betaDefault;
	fin.getline(str,SizeOfStr);

	fin.getline(str,SizeOfStr);
	fin>>orderlessCross.densityDefault
		>>orderlessCross.lengthDefault
		>>orderlessCross.chaosExtentMin
		>>orderlessCross.chaosExtentMax
		>>orderlessCross.chaosExtentDefault
		>>orderlessCross.thetaMin
		>>orderlessCross.thetaMax
		>>orderlessCross.thetaDefault
		>>orderlessCross.betaMin
		>>orderlessCross.betaMax
		>>orderlessCross.betaDefault;
	fin.getline(str,SizeOfStr);

	fin.getline(str,SizeOfStr);
	int i,len;
	ChaosStitch tempChaosStitch;
	otherChaosStitchName.clear();
	otherChaosStitch.clear();
	fin>>len;
	fin.getline(str,SizeOfStr);
	for(i=0;i<len;i++)
	{
		fin.getline(str,SizeOfStr);
		tempChaosStitch.stitchName = string(str);
		fin>>tempChaosStitch.density
			>>tempChaosStitch.length
			>>tempChaosStitch.chaosExtent
			>>tempChaosStitch.theta
			>>tempChaosStitch.beta;
		fin.getline(str,SizeOfStr);
		otherChaosStitch.push_back(tempChaosStitch);
	}
	
	OrderlessStitch tempOrderlessStitch;
	otherOrderlessStitchName.clear();
	otherOrderlessStitch.clear();
	fin>>len;
	fin.getline(str,SizeOfStr);
	for(i=0;i<len;i++)
	{
		fin.getline(str,SizeOfStr);
		tempOrderlessStitch.stitchName = string(str);
		fin>>tempOrderlessStitch.density
			>>tempOrderlessStitch.length
			>>tempOrderlessStitch.chaosExtent
			>>tempOrderlessStitch.theta
			>>tempOrderlessStitch.beta;
		fin.getline(str,SizeOfStr);
		otherOrderlessStitch.push_back(tempOrderlessStitch);
	}
	
	fin.close();
}

void CMagicCabsineStitchLibrary::GetOtherChaosStitch(vector<ChaosStitch> &tempChaosStitch)
{
	tempChaosStitch=otherChaosStitch;
}

void CMagicCabsineStitchLibrary::SetOtherChaosStitch(const vector<ChaosStitch> &tempChaosStitch)
{
	otherChaosStitch=tempChaosStitch;
}

void CMagicCabsineStitchLibrary::GetOtherOrderlessStitch(vector<OrderlessStitch> &tempOrderlessStitch)
{
	tempOrderlessStitch=otherOrderlessStitch;
}

void CMagicCabsineStitchLibrary::SetOtherOrderlessStitch(const vector<OrderlessStitch> &tempOrderlessStitch)
{
	otherOrderlessStitch=tempOrderlessStitch;
}

bool CMagicCabsineStitchLibrary::CheckParameters(ChaosStitch tempStitch,STITCH_TYPE tempType)
{
	if(tempStitch.density<0.0||tempStitch.length<0.0)
	{
		return false;
	}
	if(tempType==STITCH_ChaosVerticalCross)
	{
		if(tempStitch.chaosExtent<chaosVerticalCross.chaosExtentMin)
		{
			return false;
		}
		if(tempStitch.chaosExtent>chaosVerticalCross.chaosExtentMax)
		{
			return false;
		}
		if(tempStitch.theta<chaosVerticalCross.thetaMin)
		{
			return false;
		}
		if(tempStitch.theta>chaosVerticalCross.thetaMax)
		{
			return false;
		}
		if(tempStitch.beta<chaosVerticalCross.betaMin)
		{
			return false;
		}
		if(tempStitch.beta>chaosVerticalCross.betaMax)
		{
			return false;
		}
	}
	else if(tempType==STITCH_ChaosHorizontalCross)
	{
		if(tempStitch.chaosExtent<chaosHorizontalCross.chaosExtentMin)
		{
			return false;
		}
		if(tempStitch.chaosExtent>chaosHorizontalCross.chaosExtentMax)
		{
			return false;
		}
		if(tempStitch.theta<chaosHorizontalCross.thetaMin)
		{
			return false;
		}
		if(tempStitch.theta>chaosHorizontalCross.thetaMax)
		{
			return false;
		}
		if(tempStitch.beta<chaosHorizontalCross.betaMin)
		{
			return false;
		}
		if(tempStitch.beta>chaosHorizontalCross.betaMax)
		{
			return false;
		}
	}
	else if(tempType==STITCH_ChaosVectorFieldCross)
	{
		if(tempStitch.chaosExtent<chaosVectorFieldCross.chaosExtentMin)
		{
			return false;
		}
		if(tempStitch.chaosExtent>chaosVectorFieldCross.chaosExtentMax)
		{
			return false;
		}
		if(tempStitch.theta<chaosVectorFieldCross.thetaMin)
		{
			return false;
		}
		if(tempStitch.theta>chaosVectorFieldCross.thetaMax)
		{
			return false;
		}
		if(tempStitch.beta<chaosVectorFieldCross.betaMin)
		{
			return false;
		}
		if(tempStitch.beta>chaosVectorFieldCross.betaMax)
		{
			return false;
		}
	}
	else
	{
		return false;
	}
	return true;
}

bool CMagicCabsineStitchLibrary::CheckParameters(OrderlessStitch tempStitch,STITCH_TYPE tempType)
{
	if(tempStitch.density<0.0||tempStitch.length<0.0)
	{
		return false;
	}
	if(tempType==STITCH_OrderlessCross)
	{
		if(tempStitch.chaosExtent<orderlessCross.chaosExtentMin)
		{
			return false;
		}
		if(tempStitch.chaosExtent>orderlessCross.chaosExtentMax)
		{
			return false;
		}
		if(tempStitch.theta<orderlessCross.thetaMin)
		{
			return false;
		}
		if(tempStitch.theta>orderlessCross.thetaMax)
		{
			return false;
		}
		if(tempStitch.beta<orderlessCross.betaMin)
		{
			return false;
		}
		if(tempStitch.beta>orderlessCross.betaMax)
		{
			return false;
		}
	}
	else
	{
		return false;
	}
	return true;
}

//��Ҫͨ��load�������г�ʼ��
void CMagicCabsineStitchLibrary::Initialization()
{
	LoadStitchFile();

	/*
	//�����ǽ���ʼ��д�ڳ�����,�����Ǵ��ļ��ж�ȡ
	//��ʼ��������������Ĳ���
	//�ܶ�,Ĭ��ֵ0.5
	//����,Ĭ��ֵ10.0
	//���Ҷ�,ȡֵ��Χ[0.05,0.3],Ĭ��ֵ0.15,���Խ�������
	//thetaֵ,ȡֵ��Χ[pi*7/18,pi*11/18],Ĭ��ֵpi/2,���ܽ�������
	//betaֵ,ȡֵ��Χ[pi/18,pi/6],Ĭ��ֵpi/12,���ܽ�������
	chaosVerticalCross.densityDefault=0.5;
	chaosVerticalCross.lengthDefault=10.0;
	chaosVerticalCross.chaosExtentMin=0.05;
	chaosVerticalCross.chaosExtentMax=0.3;
	chaosVerticalCross.chaosExtentDefault=0.15;
	chaosVerticalCross.thetaMin=pi*70/180;
	chaosVerticalCross.thetaMax=pi*110/180;
	chaosVerticalCross.thetaDefault=pi/2;
	chaosVerticalCross.betaMin=pi*10/180;
	chaosVerticalCross.betaMax=pi*30/180;
	chaosVerticalCross.betaDefault=pi*15/180;

	//��ʼ��������ύ��Ĳ���
	//�ܶ�,Ĭ��ֵ0.5
	//����,Ĭ��ֵ10.0
	//���Ҷ�,ȡֵ��Χ[0.05,0.3],Ĭ��ֵ0.15,���Խ�������
	//thetaֵ,ȡֵ��Χ[-pi/9,pi/9],Ĭ��ֵ0,���ܽ�������
	//betaֵ,ȡֵ��Χ[pi/18,pi/6],Ĭ��ֵpi/12,���ܽ�������
	chaosHorizontalCross.densityDefault=0.5;
	chaosHorizontalCross.lengthDefault=10.0;
	chaosHorizontalCross.chaosExtentMin=0.05;
	chaosHorizontalCross.chaosExtentMax=0.3;
	chaosHorizontalCross.chaosExtentDefault=0.15;
	chaosHorizontalCross.thetaMin=-pi*20/180;
	chaosHorizontalCross.thetaMax=pi*20/180;
	chaosHorizontalCross.thetaDefault=0.0;
	chaosHorizontalCross.betaMin=pi*10/180;
	chaosHorizontalCross.betaMax=pi*30/180;
	chaosHorizontalCross.betaDefault=pi*15/180;

	//��ʼ��������ʸ��������Ĳ���
	//�ܶ�,Ĭ��ֵ0.5
	//����,Ĭ��ֵ10.0
	//���Ҷ�,ȡֵ��Χ[0.05,0.3],Ĭ��ֵ0.15,���Խ�������
	//thetaֵ,ȡֵ��Χ[pi/6,pi/3],Ĭ��ֵpi/4,���ܽ�������
	//betaֵ,ȡֵ��Χ[pi/18,pi/6],Ĭ��ֵpi/7.2,���ܽ�������
	chaosVectorFieldCross.densityDefault=0.5;
	chaosVectorFieldCross.lengthDefault=10.0;
	chaosVectorFieldCross.chaosExtentMin=0.05;
	chaosVectorFieldCross.chaosExtentMax=0.3;
	chaosVectorFieldCross.chaosExtentDefault=0.15;
	chaosVectorFieldCross.thetaMin=pi*30/180;
	chaosVectorFieldCross.thetaMax=pi*60/180;
	chaosVectorFieldCross.thetaDefault=pi*45/180;
	chaosVectorFieldCross.betaMin=pi*10/180;
	chaosVectorFieldCross.betaMax=pi*30/180;
	chaosVectorFieldCross.betaDefault=pi*25/180;

	//��ʼ��С����Ĳ���
	//�ܶ�,Ĭ��ֵ0.5
	//����,Ĭ��ֵ10.0
	//���Ҷ�,ȡֵ��Χ[0.8,1.0],Ĭ��ֵ0.9,���ܽ�������
	//thetaֵ,ȡֵ��Χ[0,pi],Ĭ��ֵpi/4,���ܽ�������
	//betaֵ,ȡֵ��Χ[0,pi/2],Ĭ��ֵpi/4,���ܽ�������
	orderlessCross.densityDefault=0.5;
	orderlessCross.lengthDefault=10.0;
	orderlessCross.chaosExtentMin=0.8;
	orderlessCross.chaosExtentMax=1.0;
	orderlessCross.chaosExtentDefault=0.9;
	orderlessCross.thetaMin=0.0;
	orderlessCross.thetaMax=pi;
	orderlessCross.thetaDefault=pi/4;
	orderlessCross.betaMin=0.0;
	orderlessCross.betaMax=pi/2;
	orderlessCross.betaDefault=pi/4;

	otherChaosStitch.clear();
	otherOrderlessStitch.clear();
	*/
}
