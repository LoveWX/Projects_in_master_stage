#include "stdafx.h"

#include "CMagicCabsinePortionProperty_AverageColor.h"

/*
class CMagicCabsinePortionProperty_AverageColor:public CMagicCabsinePortionProperty
{
public:
	//子类构造函数
	CMagicCabsinePortionProperty_AverageColor(	const IplImage *tempSrcImage,
		vector< vector<int> > &tempSplitMatrix,
		vector< vector< vector<int> > > &tempRegionMasks);
	~CMagicCabsinePortionProperty_AverageColor();//析构函数,会调用DeleteProperty()
	void ComputeProperty();			//实现基类中纯虚函数,完成局部特征的计算,置isCalced为true
	void LoadProperty();			//实现基类中纯虚函数,从数据库或文件读入所需要的数据
	void SaveProperty();			//实现基类中纯虚函数,将各种数据保存在数据库或文件中
	void DeleteProperty();			//实现基类中纯虚函数,删除该类中的数据

protected:
	int height;						//图像的高度,由子类中的srcImage高度决定
	int width;						//图像的宽度,由子类中的srcImage宽度决定
	int numOfRegion;				//分割矩阵中不同区域的数量
	vector<int> numOfRegionPoints;	//不同区域的点数,下标从1开始
	vector<int> averageBlue;		//某区域蓝色的平均值,下标从1开始
	vector<int> averageGreen;		//某区域绿色的平均值,下标从1开始
	vector<int> averageRed;			//某区域红色的平均值,下标从1开始
};
*/

CMagicCabsinePortionProperty_AverageColor::CMagicCabsinePortionProperty_AverageColor(const IplImage *tempSrcImage, 
																					 vector< vector<int> > &tempSplitMatrix, 
																					 vector< vector< vector<int> > > &tempRegionMasks)
	:CMagicCabsinePortionProperty(tempSrcImage,tempSplitMatrix,tempRegionMasks)
{
	propertyName=string("AverageColor");
	numOfRegion=tempRegionMasks.size()-1;
	if(numOfRegion>0)
	{
		isSplited=true;
	}
	if(tempSrcImage!=NULL)
	{
		height=tempSrcImage->height;
		width=tempSrcImage->width;
	}
	numOfRegionPoints.clear();
	averageBlue.clear();
	averageGreen.clear();
	averageRed.clear();
}

CMagicCabsinePortionProperty_AverageColor::~CMagicCabsinePortionProperty_AverageColor()
{
	DeleteProperty();
	numOfRegion=0;
	height=0;
	width=0;
}

void CMagicCabsinePortionProperty_AverageColor::ComputeProperty()
{
	if(!isSplited)
	{
		return;
	}
	if(displayImage!=NULL)
	{
		cvReleaseImage(&displayImage);
		displayImage=NULL;
	}
	displayImage=cvCloneImage(srcImage);

	int i,j;
	int currentRegionNum;
	vector<int> tempVector(numOfRegion+1,0);
	numOfRegionPoints=tempVector;
	averageBlue=tempVector;
	averageGreen=tempVector;
	averageRed=tempVector;
	CvScalar tempColor=cvScalar(0,0,0);
	vector<CvScalar> tempColorVector(numOfRegion+1,tempColor);
	for(i=0;i<height;i++)
	{
		for(j=0;j<width;j++)
		{
			currentRegionNum=splitMatrix[i][j];
			tempColor=cvGet2D(srcImage,i,j);
			numOfRegionPoints[currentRegionNum]++;
			averageBlue[currentRegionNum]+=(int)(tempColor.val[0]);
			averageGreen[currentRegionNum]+=(int)(tempColor.val[1]);
			averageRed[currentRegionNum]+=(int)(tempColor.val[2]);
		}
	}
	for(i=1;i<numOfRegionPoints.size();i++)
	{
		if(numOfRegionPoints[i]>0)
		{
			averageBlue[i]/=numOfRegionPoints[i];
			averageGreen[i]/=numOfRegionPoints[i];
			averageRed[i]/=numOfRegionPoints[i];
		}
		tempColorVector[i].val[0]=averageBlue[i];
		tempColorVector[i].val[1]=averageGreen[i];
		tempColorVector[i].val[2]=averageRed[i];
	}
	for(i=0;i<height;i++)
	{
		for(j=0;j<width;j++)
		{
			currentRegionNum=splitMatrix[i][j];
			cvSet2D(displayImage,i,j,tempColorVector[currentRegionNum]);
		}
	}
	isCalced=true;
	tempVector.clear();
	tempColorVector.clear();
}

void CMagicCabsinePortionProperty_AverageColor::SaveProperty()
{
	//目前暂时保存在文件中
// 	SavePropertyFile(theApp.GetDefaultPath()+"AVERAGECOLORres.txt");
	SavePropertyFile(theApp.GetProjectPath()+"AVERAGECOLORres.txt");
}

void CMagicCabsinePortionProperty_AverageColor::LoadProperty()
{
	//目前暂时先从文件中读取
// 	LoadPropertyFile(theApp.GetDefaultPath()+"AVERAGECOLORres.txt");
	LoadPropertyFile(theApp.GetProjectPath()+"AVERAGECOLORres.txt");
}
void CMagicCabsinePortionProperty_AverageColor::SavePropertyFile(string filepath)
{
	if(!isCalced)
	{
		ComputeProperty();
	}
	ofstream fout(filepath);
	int i,j;
	fout<<height<<' '<<width<<endl;
	for(i=0;i<height;i++)
	{
		for(j=0;j<width;j++)
		{
			fout<<splitMatrix[i][j]<<' ';
		}
		fout<<endl;
	}
	fout<<numOfRegion<<endl;
	for(i=1;i<=numOfRegion;i++)
	{
		fout<<numOfRegionPoints[i]<<' '<<averageBlue[i]<<' '<<averageGreen[i]<<' '<<averageRed[i]<<endl;
	}
	fout.close();
}

void CMagicCabsinePortionProperty_AverageColor::LoadPropertyFile(string filepath)
{
	ifstream fin(filepath);
	int i,j,tempInt1,tempInt2,tempInt3;
	fin>>height>>width;
	for(i=0;i<height;i++)
	{
		for(j=0;j<width;j++)
		{
			fin>>splitMatrix[i][j];
		}
	}
	isSplited=true;

	fin>>numOfRegion;
	CvScalar tempColor=cvScalar(0,0,0);
	vector<CvScalar> tempColorVector(numOfRegion+1,tempColor);

	for(i=1;i<=numOfRegion;i++)
	{
		fin>>numOfRegionPoints[i]>>tempInt1>>tempInt2>>tempInt3;
		averageBlue[i]=tempInt1;
		averageGreen[i]=tempInt2;
		averageRed[i]=tempInt3;
		tempColorVector[i].val[0]=tempInt1;
		tempColorVector[i].val[1]=tempInt2;
		tempColorVector[i].val[2]=tempInt3;
	}
	for(i=0;i<height;i++)
	{
		for(j=0;j<width;j++)
		{
			cvSet2D(displayImage,i,j,tempColorVector[splitMatrix[i][j]]);
		}
	}
	isCalced=true;
	fin.close();
}

void CMagicCabsinePortionProperty_AverageColor::DeleteProperty()
{
	numOfRegionPoints.clear();
	averageBlue.clear();
	averageGreen.clear();
	averageRed.clear();
}
