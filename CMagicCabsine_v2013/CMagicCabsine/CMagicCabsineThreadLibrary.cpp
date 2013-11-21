#include "stdafx.h"

#include "CMagicCabsineThreadLibrary.h"

/*
class CMagicCabsineThreadLibrary
{
public:
	CMagicCabsineThreadLibrary();
	~CMagicCabsineThreadLibrary();
	void GetThreads(int index,vector<Thread> &tempThread);
	void GetThreads(string factoryName,vector<Thread> &tempThread);
	void AddThreads(const vector<Thread> &tempThread,string tempName=string(""));

	void SaveConfigToFile();//将配置表信息保存至文件中
	void LoadConfigFromFile();//从文件中读取配置表信息

protected:
	vector< vector<Thread> > threadLibrary;
	vector<string> threadFactoryName;
};
*/

CMagicCabsineThreadLibrary::CMagicCabsineThreadLibrary()
{
	threadLibrary.clear();
	threadFactoryName.clear();
	pathOfConfig=theApp.GetDefaultPath()+"ConfigFile\\threadLibrary.config";

	LoadConfigFromFile();
}

CMagicCabsineThreadLibrary::~CMagicCabsineThreadLibrary()
{
	threadLibrary.clear();
	threadFactoryName.clear();
	pathOfConfig=string("");
}

int CMagicCabsineThreadLibrary::GetNumOfThreadSet()
{
	return threadFactoryName.size();
}

void CMagicCabsineThreadLibrary::GetThreadSetName(vector<string> &tempName)
{
	tempName=threadFactoryName;
}

void CMagicCabsineThreadLibrary::SetThreadSetName(vector<string> &tempName)
{
	threadFactoryName=tempName;
}

void CMagicCabsineThreadLibrary::GetThreadSet(vector< vector<Thread> > &tempThreadSet)
{
	tempThreadSet=threadLibrary;
}

void CMagicCabsineThreadLibrary::SetThreadSet(vector< vector<Thread> > &tempThreadSet)
{
	threadLibrary=tempThreadSet;
}

void CMagicCabsineThreadLibrary::GetThreads(int index,vector<Thread> &tempThread)
{
	if(index<0||index>=threadLibrary.size())
	{
		return;
	}
	tempThread=threadLibrary[index];
}

void CMagicCabsineThreadLibrary::GetThreads(string factoryName,vector<Thread> &tempThread)
{
	int i;
	for(i=0;i<threadFactoryName.size();i++)
	{
		if(factoryName==threadFactoryName[i])
		{
			break;
		}
	}
	if(i<threadFactoryName.size())
	{
		GetThreads(i,tempThread);
	}
}

void CMagicCabsineThreadLibrary::SaveConfigToFile()
{
	ofstream fout(pathOfConfig);

	fout<<threadLibrary.size()<<endl;

	int i,j;
	for(i=0;i<threadLibrary.size();i++)
	{
		fout<<threadLibrary[i].size()<<' '<<threadFactoryName[i]<<endl;
		for(j=0;j<threadLibrary[i].size();j++)
		{
			Thread &tempThread=threadLibrary[i][j];
			fout<<tempThread.threadName<<','<<tempThread.colorR<<','<<tempThread.colorG<<','<<tempThread.colorB<<endl;
		}
	}

	fout.close();
}

void CMagicCabsineThreadLibrary::LoadConfigFromFile()
{
	threadLibrary.clear();
	threadFactoryName.clear();
	const int SizeOfStr=300;
	char str[SizeOfStr];
	ifstream fin(pathOfConfig);
	int factoryNum,threadNum;
	Thread tempThread;
	vector<Thread> tempThreadVector;
	fin>>factoryNum;
	int i,j;
	for(i=0;i<factoryNum;i++)
	{
		fin>>threadNum;
		fin.getline(str,SizeOfStr,' ');
		fin.getline(str,SizeOfStr);
		threadFactoryName.push_back(str);
		tempThreadVector.clear();
		for(j=0;j<threadNum;j++)
		{
			fin.getline(str,SizeOfStr,',');
			tempThread.threadName=str;
			fin>>tempThread.colorR>>str[0]>>tempThread.colorG>>str[0]>>tempThread.colorB;
			fin.getline(str,SizeOfStr);
			tempThreadVector.push_back(tempThread);
		}
		threadLibrary.push_back(tempThreadVector);
	}

	fin.close();
}
