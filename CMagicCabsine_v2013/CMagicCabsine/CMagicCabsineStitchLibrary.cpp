#include "stdafx.h"

#include "CMagicCabsineStitchLibrary.h"

/*
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

//需要通过load函数进行初始化
void CMagicCabsineStitchLibrary::Initialization()
{
	LoadStitchFile();

	/*
	//下述是将初始化写在程序中,而不是从文件中读取
	//初始化大乱针竖交叉的参数
	//密度,默认值0.5
	//长度,默认值10.0
	//混乱度,取值范围[0.05,0.3],默认值0.15,可以交互调节
	//theta值,取值范围[pi*7/18,pi*11/18],默认值pi/2,不能交互调节
	//beta值,取值范围[pi/18,pi/6],默认值pi/12,不能交互调节
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

	//初始化大乱针横交叉的参数
	//密度,默认值0.5
	//长度,默认值10.0
	//混乱度,取值范围[0.05,0.3],默认值0.15,可以交互调节
	//theta值,取值范围[-pi/9,pi/9],默认值0,不能交互调节
	//beta值,取值范围[pi/18,pi/6],默认值pi/12,不能交互调节
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

	//初始化大乱针矢量场交叉的参数
	//密度,默认值0.5
	//长度,默认值10.0
	//混乱度,取值范围[0.05,0.3],默认值0.15,可以交互调节
	//theta值,取值范围[pi/6,pi/3],默认值pi/4,不能交互调节
	//beta值,取值范围[pi/18,pi/6],默认值pi/7.2,不能交互调节
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

	//初始化小乱针的参数
	//密度,默认值0.5
	//长度,默认值10.0
	//混乱度,取值范围[0.8,1.0],默认值0.9,不能交互调节
	//theta值,取值范围[0,pi],默认值pi/4,不能交互调节
	//beta值,取值范围[0,pi/2],默认值pi/4,不能交互调节
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
