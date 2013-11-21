#include "stdafx.h"

#include "CMagicCabsineSimulateData.h"

CMagicCabsineSimulateData::CMagicCabsineSimulateData(const IplImage *tempSrcImage)
{
	srcImage=cvCloneImage(tempSrcImage);
	displayImage=NULL;
	displayLevelImage.clear();
	isPrepared=false;
	isCalced=false;
	splitMatrix.clear();
	theMakeTable=NULL;
	theStitchLibrary=NULL;
}

CMagicCabsineSimulateData::~CMagicCabsineSimulateData()
{
	if(srcImage!=NULL)
	{
		cvReleaseImage(&srcImage);
		srcImage=NULL;
	}
	if(displayImage!=NULL)
	{
		cvReleaseImage(&displayImage);
		displayImage=NULL;
	}
	int i;
	for(i=0;i<displayLevelImage.size();i++)
	{
		if(displayLevelImage[i]!=NULL)
		{
			cvReleaseImage(&displayLevelImage[i]);
			displayLevelImage[i]=NULL;
		}
	}
	displayLevelImage.clear();
	isPrepared=false;
	isCalced=false;
	splitMatrix.clear();
	if(theMakeTable!=NULL)
	{
		delete theMakeTable;
		theMakeTable=NULL;
	}
	if(theStitchLibrary!=NULL)
	{
		delete theStitchLibrary;
		theStitchLibrary=NULL;
	}
}

void CMagicCabsineSimulateData::GetSimulateName(string &tempName)const
{
	tempName=simulateName;
}

void CMagicCabsineSimulateData::SetSimulateName(const string &tempName)
{
	simulateName=tempName;
}

IplImage* CMagicCabsineSimulateData::GetDisplayImage()
{
	if(!isCalced)
	{
		ComputeSimulateData();
	}
	return displayImage;
}

void CMagicCabsineSimulateData::GetLevelImage(vector<IplImage *> &tempLevelImage)
{
	tempLevelImage.clear();
	tempLevelImage=displayLevelImage;
}

IplImage* CMagicCabsineSimulateData::GetSingleLevelImage(int levelIndex)
{
	if(levelIndex<0||levelIndex>=displayLevelImage.size())
	{
		return NULL;
	}
	return displayLevelImage[levelIndex];
}

void CMagicCabsineSimulateData::SetDisplayImage(IplImage *tempImage)
{
	if(tempImage==NULL)
	{
		return;
	}
	if(displayImage!=NULL)
	{
		cvReleaseImage(&displayImage);
		displayImage=NULL;
	}
	displayImage=cvCloneImage(tempImage);
}

void CMagicCabsineSimulateData::SetLevelImage(vector<IplImage *> &tempLevelImage)
{
	int i;
	IplImage *tempImage=NULL;
	if(displayLevelImage.size()>0)
	{
		for(i=0;i<displayLevelImage.size();i++)
		{
			if(displayLevelImage[i]!=NULL)
			{
				cvReleaseImage(&(displayLevelImage[i]));
				displayLevelImage[i]=NULL;
			}
		}
		displayLevelImage.clear();
	}
	for(i=0;i<tempLevelImage.size();i++)
	{
		if(tempLevelImage[i]==NULL)
		{
			displayLevelImage.push_back(NULL);
		}
		else
		{
			tempImage=cvCloneImage(tempLevelImage[i]);
			displayLevelImage.push_back(tempImage);
			tempImage=NULL;
		}
	}
}

void CMagicCabsineSimulateData::LoadSimulateData()
{
	//虚函数基类中不实现
}

void CMagicCabsineSimulateData::SaveSimulateData()
{
	//虚函数基类中不实现
}

void CMagicCabsineSimulateData::LoadSimulateDataFile(string filepath)
{
	//虚函数基类中不实现
}

void CMagicCabsineSimulateData::SaveSimulateDataFile(string filepath)
{
	//虚函数基类中不实现
}

void CMagicCabsineSimulateData::GetSplitMatrix(vector< vector<int> > &tempMatrix)
{
	tempMatrix=splitMatrix;
}
