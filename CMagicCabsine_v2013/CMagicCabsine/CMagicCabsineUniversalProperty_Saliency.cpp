#include "stdafx.h"
#include "Saliency.h"

#include "CMagicCabsineUniversalProperty_Saliency.h"

CMagicCabsineUniversalProperty_Saliency::CMagicCabsineUniversalProperty_Saliency(const IplImage *tempSrcImage)
	:CMagicCabsineUniversalProperty(tempSrcImage)
{
	propertyName=string("Saliency");
	if(tempSrcImage!=NULL)
	{
		height=tempSrcImage->height;
		width=tempSrcImage->width;
	}
	ansMatrix.clear();

	ansMatrix.resize(height);
	for(int i=0; i<height; i++)
	{
		ansMatrix[i].resize(width);
	}
}

CMagicCabsineUniversalProperty_Saliency::~CMagicCabsineUniversalProperty_Saliency()
{
	DeleteProperty();
	height=0;
	width=0;
}

void CMagicCabsineUniversalProperty_Saliency::ComputeProperty()
{
	Saliency sal;
	//m_pRCMap = sal.Get(m_srcImgName.GetBuffer(0));
	displayImage = sal.Get(srcImage);

	for(int row=0;row<displayImage->height;row++)
	{
		for(int col=0;col<displayImage->width;col++)
		{
			ansMatrix[row][col] = cvGetReal2D(displayImage,row,col);
		}
	}

	isCalced = true;
}

void CMagicCabsineUniversalProperty_Saliency::SaveProperty()
{
	//目前暂时保存在文件中
// 	SavePropertyFile(theApp.GetDefaultPath()+"SALIENCYres.txt");
	SavePropertyFile(theApp.GetProjectPath()+"SALIENCYres.txt");
}

void CMagicCabsineUniversalProperty_Saliency::LoadProperty()
{
	//目前暂时先从文件中读取
// 	LoadPropertyFile(theApp.GetDefaultPath()+"SALIENCYres.txt");
	LoadPropertyFile(theApp.GetProjectPath()+"SALIENCYres.txt");
}

void CMagicCabsineUniversalProperty_Saliency::SavePropertyFile(string filepath)
{
	int i,j;
	ofstream fout(filepath);
	fout<<height<<' '<<width<<endl;
	for(i=0;i<height;i++)
	{
		for(j=0;j<width;j++)
		{
			fout<<ansMatrix[i][j]<<' ';
		}
		fout<<endl;
	}
	fout.close();

	string tempPath=filepath.substr(0,filepath.size()-4);
	tempPath+=string(".jpg");

	cvSaveImage(tempPath.c_str(),displayImage);
}

void CMagicCabsineUniversalProperty_Saliency::LoadPropertyFile(string filepath)
{
	int i,j;
	ifstream fin(filepath);
	fin>>height>>width;
	height=srcImage->height;
	width=srcImage->width;
	vector<float> tempVector(width);
	ansMatrix.clear();
	for(i=0;i<height;i++)
	{
		for(j=0;j<width;j++)
		{
			fin>>tempVector[j];
		}
		ansMatrix.push_back(tempVector);
	}
	fin.close();

	string tempPath=filepath.substr(0,filepath.size()-4);
	tempPath+=string(".jpg");

	displayImage=cvLoadImage(tempPath.c_str(),1);
	isCalced=true;
}

void CMagicCabsineUniversalProperty_Saliency::DeleteProperty()
{
	ansMatrix.clear();
}

void CMagicCabsineUniversalProperty_Saliency::GetProperty(vector< vector<float> > &tempMatrix)
{
	tempMatrix=ansMatrix;
}
