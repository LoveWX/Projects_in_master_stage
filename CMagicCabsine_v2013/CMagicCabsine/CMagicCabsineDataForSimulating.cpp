#include "stdafx.h"

#include "CMagicCabsineDataForSimulating.h"

/*
class CMagicCabsineDataForSimulating
{
public:
	CMagicCabsineDataForSimulating();										//构造函数
	CMagicCabsineDataForSimulating(IplImage *theImage);						//含参构造函数
	~CMagicCabsineDataForSimulating();										//析构函数
	void SetSrcImage(IplImage *theImage);									//设置源图像,只修改源图像,而不修改对应的其它特征值
	
	void PrepareDataForSimulating();										//通过调用各个Load函数读取所有特征数据
	
	void LoadSplitMatrix();													//从文件或数据库读取分割区域矩阵
	void LoadUniversalProperty_CLD();										//从文件或数据库读取全局特征CLD的结果
	void LoadUniversalProperty_Saliency();									//从文件或数据库读取全局特征显著性的结果
	void LoadUniversalProperty_VectorField();								//从文件或数据库读取全局特征矢量场的结果
	void LoadPortionProperty_AverageColor();								//从文件或数据库读取局部特征区域平均色的结果
	
	void GetSplitMatrix(vector< vector<int> > &theMatrix);					//获得分割区域矩阵
	void GetUniversalProperty_CLD(vector< vector<int> > &theMatrix);		//获得全局特征CLD的结果
	void GetUniversalProperty_Saliency(vector< vector<int> > &theMatrix);	//获得全局特征显著性的结果
	void GetUniversalProperty_VectorField(vector< vector<double> > &theMatrix);//获得全局特征矢量场的结果
	void GetPortionProperty_AverageColor(vector<CvScalar> &theColorList);	//获得局部特征区域平均色的结果
	
	void CalcRegionMasks();													//通过分割区域矩阵splitMatrix计算各区域掩码
	void GetRegionMasks(vector< vector< vector<int> > > &tempRegionMasks);	//获得各个区域掩码
	
protected:
	IplImage *srcImage;														//源图像
	
	vector< vector<int> > splitMatrix;						//分割区域矩阵
	vector< vector< vector<int> > > regionMasks;			//区域掩码矩阵的集合
	
	vector< vector<int> > universalProperty_CLD;			//全局特征CLD的结果矩阵
	vector< vector<int> > universalProperty_Saliency;		//全局特征显著性的结果矩阵
	vector< vector<double> > universalProperty_VectorField;	//全局特征矢量场的结果矩阵
	
	vector<int> portionProperty_AverageColorBlue;			//某区域蓝色的平均值,区域下标从1开始
	vector<int> portionProperty_AverageColorGreen;			//某区域绿色的平均值,区域下标从1开始
	vector<int> portionProperty_AverageColorRed;			//某区域红色的平均值,区域下标从1开始
	
	void LoadMatrix(string filename,vector< vector<int> > &theMatrix);		//从文件filename中读出矩阵theMatrix的值
	void LoadMatrix(string filename,vector< vector<double> > &theMatrix);	//从文件filename中读出矩阵theMatrix的值
	
	//特征选择列表
	// 	vector<bool> universalPropertySelected;
	// 	vector<bool> portionPropertySelected;
};
*/

CMagicCabsineDataForSimulating::CMagicCabsineDataForSimulating()
{
	srcImage=NULL;
	height=0;
	width=0;
	splitMatrix.clear();
	regionMasks.clear();
	universalProperty_CLD.clear();
	universalProperty_Saliency.clear();
	universalProperty_VectorField.clear();
	portionProperty_AverageColorBlue.clear();
	portionProperty_AverageColorGreen.clear();
	portionProperty_AverageColorRed.clear();
	maxRegionNum=0;
}

CMagicCabsineDataForSimulating::CMagicCabsineDataForSimulating(IplImage *theImage)
{
	srcImage=cvCloneImage(theImage);
	height=srcImage->height;
	width=srcImage->width;
	splitMatrix.clear();
	regionMasks.clear();
	universalProperty_CLD.clear();
	universalProperty_Saliency.clear();
	universalProperty_VectorField.clear();
	portionProperty_AverageColorBlue.clear();
	portionProperty_AverageColorGreen.clear();
	portionProperty_AverageColorRed.clear();
	maxRegionNum=0;
}

CMagicCabsineDataForSimulating::~CMagicCabsineDataForSimulating()
{
	if(srcImage!=NULL)
	{
		cvReleaseImage(&srcImage);
		srcImage=NULL;
	}
	height=0;
	width=0;
	splitMatrix.clear();
	regionMasks.clear();
	universalProperty_CLD.clear();
	universalProperty_Saliency.clear();
	universalProperty_VectorField.clear();
	portionProperty_AverageColorBlue.clear();
	portionProperty_AverageColorGreen.clear();
	portionProperty_AverageColorRed.clear();
	maxRegionNum=0;
}

void CMagicCabsineDataForSimulating::SetSrcImage(IplImage *theImage)
{
	if(srcImage!=NULL)
	{
		cvReleaseImage(&srcImage);
		srcImage=NULL;
	}
	srcImage=cvCloneImage(theImage);
	height=srcImage->height;
	width=srcImage->width;
	splitMatrix.clear();
	regionMasks.clear();
	universalProperty_CLD.clear();
	universalProperty_Saliency.clear();
	universalProperty_VectorField.clear();
	portionProperty_AverageColorBlue.clear();
	portionProperty_AverageColorGreen.clear();
	portionProperty_AverageColorRed.clear();
	maxRegionNum=0;
}

void CMagicCabsineDataForSimulating::PrepareDataForSimulating()
{
	if(srcImage==NULL)
	{
		return;
	}
	LoadSplitMatrix();
	LoadUniversalProperty_CLD();
	LoadUniversalProperty_Saliency();
	LoadUniversalProperty_VectorField();
	LoadPortionProperty_AverageColor();
}

void CMagicCabsineDataForSimulating::LoadSplitMatrix()
{
// 	string filename = theApp.GetDefaultPath()+"SPLITres.txt";
	string filename = theApp.GetProjectPath()+"SPLITres.txt";
	
	int i,j;
	vector<int> tempVector(width,0);
	vector< vector<int> > tempMatrix(height,tempVector);
	splitMatrix=tempMatrix;

	ifstream fin(filename.c_str());
	fin>>i>>j;
	for(i=0;i<height;i++)
	{
		for(j=0;j<width;j++)
		{
			fin>>splitMatrix[i][j];
		}
	}

	maxRegionNum=0;
	int idNums = 0;
	fin >> idNums;
	maxRegionNum+=idNums;//增加前景区域数
	int tempID = 0;
	for(i=0; i<idNums; i++)
	{
		fin >> tempID;
		frontIDs.insert(tempID);
	}

	fin >> idNums;
	maxRegionNum+=idNums;//增加背景区域数
	for(i=0; i<idNums; i++)
	{
		fin >> tempID;
		backIDs.insert(tempID);
	}
	
	fin.close();

	regionMasks.clear();
	for(i=0;i<=maxRegionNum;i++)
	{
		regionMasks.push_back(tempMatrix);
	}
	CalcRegionMasks();
}

void CMagicCabsineDataForSimulating::LoadUniversalProperty_CLD()
{
	vector<int> tempVector(width,0);
	vector< vector<int> > tempMatrix(height,tempVector);
	universalProperty_CLD=tempMatrix;
// 	LoadMatrix(theApp.GetDefaultPath()+"CLDres.txt",universalProperty_CLD);
	LoadMatrix(theApp.GetProjectPath()+"CLDres.txt",universalProperty_CLD);
}

void CMagicCabsineDataForSimulating::LoadUniversalProperty_Saliency()
{
	vector<int> tempVector(width,0);
	vector< vector<int> > tempMatrix(height,tempVector);
	universalProperty_Saliency=tempMatrix;
// 	LoadMatrix(theApp.GetDefaultPath()+"Saliencyres.txt",universalProperty_Saliency);
	LoadMatrix(theApp.GetProjectPath()+"Saliencyres.txt",universalProperty_Saliency);
}

void CMagicCabsineDataForSimulating::LoadUniversalProperty_VectorField()
{
	vector<double> tempVector(width,0);
	vector< vector<double> > tempMatrix(height,tempVector);
	universalProperty_VectorField=tempMatrix;
// 	LoadMatrix(theApp.GetDefaultPath()+"VectorFieldres.txt",universalProperty_VectorField);
	LoadMatrix(theApp.GetProjectPath()+"VectorFieldres.txt",universalProperty_VectorField);
}

void CMagicCabsineDataForSimulating::LoadPortionProperty_AverageColor()
{
// 	string tempPath=theApp.GetDefaultPath()+"AverageColorres.txt";
	string tempPath=theApp.GetProjectPath()+"AverageColorres.txt";
	ifstream fin(tempPath.c_str());
	int i,j,numOfRegion,tempInt1,tempInt2,tempInt3;
	fin>>tempInt1>>tempInt2;
	for(i=0;i<height;i++)
	{
		for(j=0;j<width;j++)
		{
			fin>>tempInt1;//仅仅去掉前面的分割矩阵信息
		}
	}
	regionArea.clear();
	regionArea.push_back(0);
	portionProperty_AverageColorBlue.clear();
	portionProperty_AverageColorBlue.push_back(0);
	portionProperty_AverageColorGreen.clear();
	portionProperty_AverageColorGreen.push_back(0);
	portionProperty_AverageColorRed.clear();
	portionProperty_AverageColorRed.push_back(0);
	fin>>numOfRegion;
	for(i=1;i<=numOfRegion;i++)
	{
		fin>>tempInt1;
		regionArea.push_back(tempInt1);
		fin>>tempInt1>>tempInt2>>tempInt3;
		portionProperty_AverageColorBlue.push_back(tempInt1);
		portionProperty_AverageColorGreen.push_back(tempInt2);
		portionProperty_AverageColorRed.push_back(tempInt3);
	}
	fin.close();
}

void CMagicCabsineDataForSimulating::GetRegionArea(vector<int> &theRegionArea)
{
	theRegionArea=regionArea;
}

void CMagicCabsineDataForSimulating::GetSplitMatrix(vector< vector<int> > &theMatrix)
{
	theMatrix=splitMatrix;
}

void CMagicCabsineDataForSimulating::GetUniversalProperty_CLD(vector< vector<int> > &theMatrix)
{
	theMatrix=universalProperty_CLD;
}

void CMagicCabsineDataForSimulating::GetUniversalProperty_Saliency(vector< vector<int> > &theMatrix)
{
	theMatrix=universalProperty_Saliency;
}

void CMagicCabsineDataForSimulating::GetUniversalProperty_VectorField(vector< vector<double> > &theMatrix)
{
	theMatrix=universalProperty_VectorField;
}

void CMagicCabsineDataForSimulating::GetPortionProperty_AverageColor(vector<CvScalar> &theColorList)
{
	theColorList.clear();
	int i;
	CvScalar col;
	for(i=0;i<portionProperty_AverageColorBlue.size();i++)
	{
		col.val[0]=portionProperty_AverageColorBlue[i];
		col.val[1]=portionProperty_AverageColorGreen[i];
		col.val[2]=portionProperty_AverageColorRed[i];
		theColorList.push_back(col);
	}
}

void CMagicCabsineDataForSimulating::CalcRegionMasks()
{
	int i,j,k;
	int currentRegionNum;
	vector<int> tempVector(width,0);
	vector< vector<int> > tempMatrix(height,tempVector);
	
	regionMasks.clear();
	//因为没有区域号为0的区域,所以下标为0的元素为全0的矩阵
	regionMasks.push_back(tempMatrix);
	for(i=0;i<height;i++)
	{
		for(j=0;j<width;j++)
		{
			currentRegionNum=splitMatrix[i][j];
			//没有这个区域号对应的区域
			if(currentRegionNum>regionMasks.size()-1)
			{
				for(k=regionMasks.size();k<=currentRegionNum;k++)
				{
					regionMasks.push_back(regionMasks[0]);
				}
			}
			regionMasks[currentRegionNum][i][j]=1;
		}
	}
}

void CMagicCabsineDataForSimulating::GetRegionMasks(vector< vector< vector<int> > > &tempRegionMasks)
{
	if(regionMasks.size()==0)
	{
		CalcRegionMasks();
	}
	tempRegionMasks=regionMasks;
}

void CMagicCabsineDataForSimulating::GetRegionMask(int numOfRegion,vector< vector<int> > &tempRegionMask)
{
	if(regionMasks.size()==0)
	{
		CalcRegionMasks();
	}
	if(numOfRegion<=0||numOfRegion>maxRegionNum)
	{
		return;
	}
	tempRegionMask=regionMasks[numOfRegion];
}

void CMagicCabsineDataForSimulating::LoadMatrix(string filename,vector< vector<int> > &theMatrix)
{
	ifstream fin(filename.c_str());
	int i,j;
	fin>>i>>j;
	for(i=0;i<height;i++)
	{
		for(j=0;j<width;j++)
		{
			fin>>theMatrix[i][j];
		}
	}
	fin.close();
}

void CMagicCabsineDataForSimulating::LoadMatrix(string filename,vector< vector<double> > &theMatrix)
{
	ifstream fin(filename.c_str());
	int i,j;
	fin>>i>>j;
	for(i=0;i<height;i++)
	{
		for(j=0;j<width;j++)
		{
			fin>>theMatrix[i][j];
		}
	}
	fin.close();
}

bool CMagicCabsineDataForSimulating::IsRegionFront(int regionID)//判断这个区域号所代表的区域是否是前景
{
	if(frontIDs.find(regionID) != frontIDs.end())
	{
		return true;
	}
	else
	{
		return false;
	}
}
