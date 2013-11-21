#include "stdafx.h"

#include "CMagicCabsinePortionProperty.h"

CMagicCabsinePortionProperty::CMagicCabsinePortionProperty(const IplImage *tempSrcImage, 
														   vector< vector<int> > &tempSplitMatrix, 
														   vector< vector< vector<int> > > &tempRegionMasks)
{
	srcImage=tempSrcImage;
	splitMatrix=tempSplitMatrix;
	regionMasks=tempRegionMasks;
	displayImage=NULL;
	isCalced=false;
	if(tempSplitMatrix.size()>0&&tempSplitMatrix[0].size()>0)
	{
		isSplited=true;
	}
	else
	{
		isSplited=false;
	}
}

CMagicCabsinePortionProperty::~CMagicCabsinePortionProperty()
{
	srcImage=NULL;
	if(displayImage!=NULL)
	{
		cvReleaseImage(&displayImage);
		displayImage=NULL;
	}
	isCalced=false;
	isSplited=false;
	splitMatrix.clear();
	regionMasks.clear();
}

void CMagicCabsinePortionProperty::GetPropertyName(string &tempName)const
{
	tempName=propertyName;
}

void CMagicCabsinePortionProperty::SetPropertyName(const string &tempName)
{
	propertyName=tempName;
}

IplImage* CMagicCabsinePortionProperty::GetDisplayImage()
{
	if(!isCalced)
	{
		ComputeProperty();
	}
	return displayImage;
}
