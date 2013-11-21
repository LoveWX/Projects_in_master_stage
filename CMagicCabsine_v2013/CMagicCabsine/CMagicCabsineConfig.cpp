#include "stdafx.h"

#include "CMagicCabsineConfig.h"


CMagicCabsineConfig::CMagicCabsineConfig(IMAGE_TYPE tempImageType)
{
	imageType=tempImageType;
	FindoutPathOfConfig();
	universalPropertySelected.clear();
	portionPropertySelected.clear();

	LoadConfigFromFile();
}

CMagicCabsineConfig::~CMagicCabsineConfig()
{
	numOfUniversalProperty = 0;
	numOfPortionProperty = 0;
	universalPropertySelected.clear();
	portionPropertySelected.clear();
	pathOfConfig = string("");
}

int CMagicCabsineConfig::GetNumOfUniversalProperty()const
{
	return numOfUniversalProperty;
}

int CMagicCabsineConfig::GetNumOfPortionProperty()const
{
	return numOfPortionProperty;
}

void CMagicCabsineConfig::FindoutPathOfConfig()
{
	//设置配置文件夹的路径
	//string defaultConfigPath="D:\\zzzzz\\CMagicCabsine\\CMagicCabsine\\ConfigFile\\";//绝对路径

	//设置配置文件夹的相对路径
	string defaultConfigPath=theApp.GetDefaultPath()+"ConfigFile\\";

	switch (imageType)
	{
	case IMAGE_HUMAN:
		pathOfConfig="conf_human.config";
		break;
	case IMAGE_SCENERY:
		pathOfConfig="conf_scenery.config";
		break;
	case IMAGE_ANIMAL:
		pathOfConfig="conf_animal.config";
		break;
	case IMAGE_CUSTOM:
		pathOfConfig="conf_custom.config";
		break;
	default:
		AfxMessageBox("Could not find out image type.");
		return;
	}
	pathOfConfig=defaultConfigPath+pathOfConfig;
}

// void CMagicCabsineConfig::LoadConfigFromFile()
// {
// 	FILE *fp=NULL;
// 	if((fp=fopen(pathOfConfig.c_str(),"r"))==NULL)
// 	{
// 		AfxMessageBox("Could not open the config file!");
// 		return;
// 	}
// 	universalPropertySelected.clear();
// 	portionPropertySelected.clear();
// 
// 	int i,j;
// 	const int SizeOfStr=300;
// 	char str[SizeOfStr];
// 	//读取全局特征的配置信息
// 	fgets(str,SizeOfStr,fp);
// 	for(i=0;i<SizeOfStr&&str[i]!=':';i++);
// 	sscanf(str+i+1,"%d",&numOfUniversalProperty);
// 	for(i=0;i<numOfUniversalProperty;i++)
// 	{
// 		fscanf(fp,"%d",&j);
// 		if(j==1)
// 		{
// 			universalPropertySelected.push_back(true);
// 		}
// 		else
// 		{
// 			universalPropertySelected.push_back(false);
// 		}
// 	}
// 	fscanf(fp,"%c",&str[0]);
// 
// 	//读取分割方法的配置信息
// 	fgets(str,SizeOfStr,fp);
// 	for(i=strlen(str)-1;i>=0&&(str[i]==' '||str[i]=='\n');i--);
// 	str[i+1]='\0';
// 	for(i=0;i<SizeOfStr&&str[i]!=':';i++);
// 	pathOfSplitData=(str+i+1);
// 
// 	//读取局部特征的配置信息
// 	fgets(str,SizeOfStr,fp);
// 	for(i=0;i<SizeOfStr&&str[i]!=':';i++);
// 	sscanf(str+i+1,"%d",&numOfPortionProperty);
// 	for(i=0;i<numOfPortionProperty;i++)
// 	{
// 		fscanf(fp,"%d",&j);
// 		if(j==1)
// 		{
// 			portionPropertySelected.push_back(true);
// 		}
// 		else
// 		{
// 			portionPropertySelected.push_back(false);
// 		}
// 	}
// 	fscanf(fp,"%c",&str[0]);
// 
// 	//读取模拟方法的配置信息
// 	fgets(str,SizeOfStr,fp);
// 	for(i=strlen(str)-1;i>=0&&(str[i]==' '||str[i]=='\n');i--);
// 	str[i+1]='\0';
// 	for(i=0;i<SizeOfStr&&str[i]!=':';i++);
// 	pathOfSimulateData=(str+i+1);
// 
// 	fclose(fp);
// 	fp=NULL;
// }

void CMagicCabsineConfig::LoadConfigFromFile()
{
	ifstream fin(pathOfConfig.c_str());
	universalPropertySelected.clear();
	portionPropertySelected.clear();

	int i,j;
	const int SizeOfStr=300;
	char str[SizeOfStr];
	//读取全局特征的配置信息
	fin.getline(str,SizeOfStr,':');
	fin>>numOfUniversalProperty;
	fin.getline(str,SizeOfStr);
	for(i=0;i<numOfUniversalProperty;i++)
	{
		fin>>j;
		if(j==1)
		{
			universalPropertySelected.push_back(true);
		}
		else
		{
			universalPropertySelected.push_back(false);
		}
	}
	fin.getline(str,SizeOfStr);

	//读取分割方法的配置信息
	string tname;
	fin >> tname;
	if (tname != "Split_Data:")
	{
		exit(0);
	}
	int tempSplitID;
	fin >> tempSplitID;
	splitName = (SPLIT_METHOD_NAME)tempSplitID;
	//读取局部特征的配置信息
	fin.getline(str,SizeOfStr,':');
	fin>>numOfPortionProperty;
	fin.getline(str,SizeOfStr);
	for(i=0;i<numOfPortionProperty;i++)
	{
		fin>>j;
		if(j==1)
		{
			portionPropertySelected.push_back(true);
		}
		else
		{
			portionPropertySelected.push_back(false);
		}
	}
	fin.getline(str,SizeOfStr);

// 	//读取模拟方法的配置信息
// 	fin.getline(str,SizeOfStr);
// 	for(i=0;i<SizeOfStr&&str[i]!=':';i++);
// 	pathOfSimulateData=(str+i+1);

	fin.close();
}


void CMagicCabsineConfig::SaveConfigToFile()
{
	ofstream fout(pathOfConfig.c_str());

	//写全局特征的配置信息
	fout<<"Universal_Property:"<<numOfUniversalProperty<<endl;
	int i;
	for(i=0;i<numOfUniversalProperty;i++)
	{
		if(universalPropertySelected[i])
		{
			fout<<'1'<<endl;
		}
		else
		{
			fout<<'0'<<endl;
		}
	}

	//写分割方法的配置信息
	fout<<"Split_Data:"<<endl;
	fout <<splitName << endl;

	//写局部特征的配置信息
	fout<<"Portion_Property:"<<numOfPortionProperty<<endl;
	for(i=0;i<numOfPortionProperty;i++)
	{
		if(portionPropertySelected[i])
		{
			fout<<'1'<<endl;
		}
		else
		{
			fout<<'0'<<endl;
		}
	}

// 	//写模拟方法的配置信息
// 	fout<<"Simulata_Data:"<<pathOfSimulateData<<endl;

	fout.close();
}

IMAGE_TYPE CMagicCabsineConfig::GetImageType()
{
	return imageType;
}

void CMagicCabsineConfig::SetImageType(const IMAGE_TYPE tempImageType)
{
	imageType=tempImageType;
}

void CMagicCabsineConfig::GetSeleted(vector<bool> &tempUniversal,vector<bool> &tempPortion)const
{
	tempUniversal=universalPropertySelected;
	tempPortion=portionPropertySelected;
}

void CMagicCabsineConfig::SetSeleted(const vector<bool> &tempUniversal,const vector<bool> &tempPortion)
{
	universalPropertySelected=tempUniversal;
	portionPropertySelected=tempPortion;
	numOfUniversalProperty=tempUniversal.size();
	numOfPortionProperty=tempPortion.size();
}
