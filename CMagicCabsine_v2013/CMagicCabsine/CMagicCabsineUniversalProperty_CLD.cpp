#include "stdafx.h"

#include "imatrix.h"
#include "ETF.h"
#include "fdog.h"
#include "myvec.h"
#include "CMagicCabsineUniversalProperty_CLD.h"

CMagicCabsineUniversalProperty_CLD::CMagicCabsineUniversalProperty_CLD(const IplImage *tempSrcImage)
	:CMagicCabsineUniversalProperty(tempSrcImage)
{
	propertyName=string("CLD");
	if(tempSrcImage!=NULL)
	{
		height=tempSrcImage->height;
		width=tempSrcImage->width;
	}
	ansMatrix.clear();
	ansMatrix.resize(height);
	for (int i=0; i<height; i++)
	{
		ansMatrix[i].resize(width);
	}
}

CMagicCabsineUniversalProperty_CLD::~CMagicCabsineUniversalProperty_CLD()
{
	DeleteProperty();
	height=0;
	width=0;
}

void CMagicCabsineUniversalProperty_CLD::ComputeProperty()
{
	imatrix img(this->srcImage->width,this->srcImage->height);
	IplImage* dst = cvCreateImage(cvGetSize(this->srcImage),this->srcImage->depth,1);
	cvCvtColor(this->srcImage,dst,CV_BGR2GRAY);
	CvScalar s;
	for(int i=0;i<this->srcImage->width;i++)
	{
		for(int j=0;j<this->srcImage->height;j++)
		{
			s=cvGet2D(dst,j,i);
			img[i][j]=(int)(s.val[0]);
		}
	}	
	int image_x = img.getRow();
	int image_y = img.getCol();
	ETF e;
	e.init(image_x, image_y);
	e.set2(img);
	e.Smooth(4, 2);
	double tao = 0.99;
	double thres = 0.7;
	GetFDoG(img, e, 1.0, 3.0, tao); 	
	GrayThresholding(img, thres);
	for(int i=0;i<this->srcImage->width;i++)
	{
		for(int j=0;j<this->srcImage->height;j++)
		{
			ansMatrix[j][i]=img[i][j];
		}
	}

	cvReleaseImage(&dst);

	CvSize size;
	size.width=this->srcImage->width;
	size.height=this->srcImage->height;
	this->displayImage=cvCreateImage(size,this->srcImage->depth,1);
	for(int i=0;i<width;i++)
	{
		for(int j=0;j<height;j++)
		{
			cvSetReal2D(displayImage,j,i,ansMatrix[j][i]);
		}
	}

	isCalced = true;
}

void CMagicCabsineUniversalProperty_CLD::SaveProperty()
{
	//目前暂时保存在文件中
// 	SavePropertyFile(theApp.GetDefaultPath()+"CLDres.txt");
	SavePropertyFile(theApp.GetProjectPath()+"CLDres.txt");
}

void CMagicCabsineUniversalProperty_CLD::LoadProperty()
{
	//目前暂时先从文件中读取
// 	LoadPropertyFile(theApp.GetDefaultPath()+"CLDres.txt");
	LoadPropertyFile(theApp.GetProjectPath()+"CLDres.txt");
}

void CMagicCabsineUniversalProperty_CLD::SavePropertyFile(string filepath)
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

void CMagicCabsineUniversalProperty_CLD::LoadPropertyFile(string filepath)
{
	int i,j;
	ifstream fin(filepath);
	fin>>height>>width;
	height=srcImage->height;
	width=srcImage->width;
	vector<int> tempVector(width);
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

void CMagicCabsineUniversalProperty_CLD::DeleteProperty()
{
	ansMatrix.clear();
}

void CMagicCabsineUniversalProperty_CLD::GetProperty(vector< vector<int> > &tempMatrix)
{
	tempMatrix=ansMatrix;
}
