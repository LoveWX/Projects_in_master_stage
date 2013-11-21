#include "stdafx.h"

#include "CMagicCabsineUniversalProperty.h"

CMagicCabsineUniversalProperty::CMagicCabsineUniversalProperty(const IplImage *tempSrcImage)
{
	srcImage=tempSrcImage;
	displayImage=NULL;
	isCalced=false;
}

CMagicCabsineUniversalProperty::~CMagicCabsineUniversalProperty()
{
	//源图像是一个指针,由CMagicCabsineProject类负责创建和释放
	srcImage=NULL;
	if(displayImage!=NULL)
	{
		cvReleaseImage(&displayImage);
		displayImage=NULL;
	}
	isCalced=false;
}

void CMagicCabsineUniversalProperty::GetPropertyName(string &tempName)const
{
	tempName=propertyName;
}

void CMagicCabsineUniversalProperty::SetPropertyName(const string &tempName)
{
	propertyName=tempName;
}

IplImage* CMagicCabsineUniversalProperty::GetDisplayImage()
{
	if(!isCalced)
	{
		ComputeProperty();
	}
	return displayImage;
}
