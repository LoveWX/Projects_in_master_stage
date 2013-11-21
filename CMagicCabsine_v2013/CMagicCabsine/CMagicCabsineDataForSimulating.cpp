#include "stdafx.h"

#include "CMagicCabsineDataForSimulating.h"

/*
class CMagicCabsineDataForSimulating
{
public:
	CMagicCabsineDataForSimulating();										//���캯��
	CMagicCabsineDataForSimulating(IplImage *theImage);						//���ι��캯��
	~CMagicCabsineDataForSimulating();										//��������
	void SetSrcImage(IplImage *theImage);									//����Դͼ��,ֻ�޸�Դͼ��,�����޸Ķ�Ӧ����������ֵ
	
	void PrepareDataForSimulating();										//ͨ�����ø���Load������ȡ������������
	
	void LoadSplitMatrix();													//���ļ������ݿ��ȡ�ָ��������
	void LoadUniversalProperty_CLD();										//���ļ������ݿ��ȡȫ������CLD�Ľ��
	void LoadUniversalProperty_Saliency();									//���ļ������ݿ��ȡȫ�����������ԵĽ��
	void LoadUniversalProperty_VectorField();								//���ļ������ݿ��ȡȫ������ʸ�����Ľ��
	void LoadPortionProperty_AverageColor();								//���ļ������ݿ��ȡ�ֲ���������ƽ��ɫ�Ľ��
	
	void GetSplitMatrix(vector< vector<int> > &theMatrix);					//��÷ָ��������
	void GetUniversalProperty_CLD(vector< vector<int> > &theMatrix);		//���ȫ������CLD�Ľ��
	void GetUniversalProperty_Saliency(vector< vector<int> > &theMatrix);	//���ȫ�����������ԵĽ��
	void GetUniversalProperty_VectorField(vector< vector<double> > &theMatrix);//���ȫ������ʸ�����Ľ��
	void GetPortionProperty_AverageColor(vector<CvScalar> &theColorList);	//��þֲ���������ƽ��ɫ�Ľ��
	
	void CalcRegionMasks();													//ͨ���ָ��������splitMatrix�������������
	void GetRegionMasks(vector< vector< vector<int> > > &tempRegionMasks);	//��ø�����������
	
protected:
	IplImage *srcImage;														//Դͼ��
	
	vector< vector<int> > splitMatrix;						//�ָ��������
	vector< vector< vector<int> > > regionMasks;			//�����������ļ���
	
	vector< vector<int> > universalProperty_CLD;			//ȫ������CLD�Ľ������
	vector< vector<int> > universalProperty_Saliency;		//ȫ�����������ԵĽ������
	vector< vector<double> > universalProperty_VectorField;	//ȫ������ʸ�����Ľ������
	
	vector<int> portionProperty_AverageColorBlue;			//ĳ������ɫ��ƽ��ֵ,�����±��1��ʼ
	vector<int> portionProperty_AverageColorGreen;			//ĳ������ɫ��ƽ��ֵ,�����±��1��ʼ
	vector<int> portionProperty_AverageColorRed;			//ĳ�����ɫ��ƽ��ֵ,�����±��1��ʼ
	
	void LoadMatrix(string filename,vector< vector<int> > &theMatrix);		//���ļ�filename�ж�������theMatrix��ֵ
	void LoadMatrix(string filename,vector< vector<double> > &theMatrix);	//���ļ�filename�ж�������theMatrix��ֵ
	
	//����ѡ���б�
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
	maxRegionNum+=idNums;//����ǰ��������
	int tempID = 0;
	for(i=0; i<idNums; i++)
	{
		fin >> tempID;
		frontIDs.insert(tempID);
	}

	fin >> idNums;
	maxRegionNum+=idNums;//���ӱ���������
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
			fin>>tempInt1;//����ȥ��ǰ��ķָ������Ϣ
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
	//��Ϊû�������Ϊ0������,�����±�Ϊ0��Ԫ��Ϊȫ0�ľ���
	regionMasks.push_back(tempMatrix);
	for(i=0;i<height;i++)
	{
		for(j=0;j<width;j++)
		{
			currentRegionNum=splitMatrix[i][j];
			//û���������Ŷ�Ӧ������
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

bool CMagicCabsineDataForSimulating::IsRegionFront(int regionID)//�ж���������������������Ƿ���ǰ��
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
