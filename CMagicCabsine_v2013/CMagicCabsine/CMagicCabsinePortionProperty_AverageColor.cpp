#include "stdafx.h"

#include "CMagicCabsinePortionProperty_AverageColor.h"

/*
class CMagicCabsinePortionProperty_AverageColor:public CMagicCabsinePortionProperty
{
public:
	//���๹�캯��
	CMagicCabsinePortionProperty_AverageColor(	const IplImage *tempSrcImage,
		vector< vector<int> > &tempSplitMatrix,
		vector< vector< vector<int> > > &tempRegionMasks);
	~CMagicCabsinePortionProperty_AverageColor();//��������,�����DeleteProperty()
	void ComputeProperty();			//ʵ�ֻ����д��麯��,��ɾֲ������ļ���,��isCalcedΪtrue
	void LoadProperty();			//ʵ�ֻ����д��麯��,�����ݿ���ļ���������Ҫ������
	void SaveProperty();			//ʵ�ֻ����д��麯��,���������ݱ��������ݿ���ļ���
	void DeleteProperty();			//ʵ�ֻ����д��麯��,ɾ�������е�����

protected:
	int height;						//ͼ��ĸ߶�,�������е�srcImage�߶Ⱦ���
	int width;						//ͼ��Ŀ��,�������е�srcImage��Ⱦ���
	int numOfRegion;				//�ָ�����в�ͬ���������
	vector<int> numOfRegionPoints;	//��ͬ����ĵ���,�±��1��ʼ
	vector<int> averageBlue;		//ĳ������ɫ��ƽ��ֵ,�±��1��ʼ
	vector<int> averageGreen;		//ĳ������ɫ��ƽ��ֵ,�±��1��ʼ
	vector<int> averageRed;			//ĳ�����ɫ��ƽ��ֵ,�±��1��ʼ
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
	//Ŀǰ��ʱ�������ļ���
// 	SavePropertyFile(theApp.GetDefaultPath()+"AVERAGECOLORres.txt");
	SavePropertyFile(theApp.GetProjectPath()+"AVERAGECOLORres.txt");
}

void CMagicCabsinePortionProperty_AverageColor::LoadProperty()
{
	//Ŀǰ��ʱ�ȴ��ļ��ж�ȡ
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
