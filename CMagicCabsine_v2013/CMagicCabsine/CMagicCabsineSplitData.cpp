#include "stdafx.h"

#include <set>
#include <highgui.h>
#include <queue>
#include "CMagicCabsineSplitData.h"
#include "bresenham.h"

using namespace std;

CMagicCabsineSplitData::CMagicCabsineSplitData(const IplImage *tempSrcImage)
{
	srcImage=tempSrcImage;

	width = srcImage->width;
	height = srcImage->height;

	displayImage=NULL;
	boundaryImage=NULL;
	markImage=NULL;
	isMarked=false;
	isCalced=false;
	regionMasks.clear();

	splitMatrix.clear();
	vector<int> tempVector(tempSrcImage->width,0);
	int i;
	for(i=0;i<tempSrcImage->height;i++)
	{
		splitMatrix.push_back(tempVector);
	}
	tempVector.clear();

	frontIDs.clear();
	backIDs.clear();
	frontBackImg = NULL;
	regionOpe = NULL;
}

CMagicCabsineSplitData::~CMagicCabsineSplitData()
{
	srcImage=NULL;
	if(displayImage!=NULL)
	{
		cvReleaseImage(&displayImage);
		displayImage=NULL;
	}
	if(boundaryImage!=NULL)
	{
		cvReleaseImage(&boundaryImage);
		boundaryImage=NULL;
	}
	if(markImage!=NULL)
	{
		cvReleaseImage(&markImage);
		markImage=NULL;
	}
	if(frontBackImg!=NULL)
	{
		cvReleaseImage(&frontBackImg);
		markImage=NULL;
	}
	if (regionOpe!=NULL)
	{
		delete regionOpe;
	}
	isCalced=false;
	isMarked=false;
	splitMatrix.clear();
	regionMasks.clear();
	frontIDs.clear();
	backIDs.clear();
	regionOpe = NULL;
}

void CMagicCabsineSplitData::GetSplitName(string &tempName)const
{
	tempName=splitName;
}

void CMagicCabsineSplitData::SetSplitName(const string &tempName)
{
	splitName=tempName;
}

void CMagicCabsineSplitData::GetSplitTips(string &tempTips)const
{
	tempTips=splitTips;
}

void CMagicCabsineSplitData::SetSplitTips(const string &tempTips)
{
	splitTips=tempTips;
}

void CMagicCabsineSplitData::SetUserMark(vector< vector<CvPoint> > &tempForeLines,vector< vector<CvPoint> > &tempBackLines)
{
	foreLines = tempForeLines;	//���ǰ��������
	backLines = tempBackLines;	//��Ǳ���������
}

void CMagicCabsineSplitData::GetUserMark(vector< vector<CvPoint> > &foreLines,vector< vector<CvPoint> > &backLines)
{
	//���麯�������в�ʵ��
}


IplImage* CMagicCabsineSplitData::GetMarkImage()const
{
	return markImage;
}

IplImage* CMagicCabsineSplitData::GetDisplayImage()const
{
	return displayImage;
}

IplImage* CMagicCabsineSplitData::GetBoundaryImage()const
{
	return boundaryImage;
}

 void CMagicCabsineSplitData::ComputeSplitData()
 {
	 if(isCalced)
	 {
		 regionOpe = new ImageRegionOperator(srcImage, splitMatrix);
		 regionOpe->RearrangeRegionNum();
		 regionOpe->CalcAverageColor();
		 cvReleaseImage(&displayImage);
		 displayImage = cvCloneImage(regionOpe->GetDisplayImage());
		 regionOpe->GetAreaMatrix(splitMatrix);
		 ComputeRegionMask();
		 computeMarkedRegionID();
		 computeBoundaryImage();
		 computeFrontBackImage();
	 }
 }

 //�����б߽��ͼ��
 void CMagicCabsineSplitData::computeBoundaryImage()
 {
	 int maxRegionNum = regionOpe->GetNumOfRegions();
	 regionOpe->GetAreaMatrix(splitMatrix);

	 vector<vector<int>> boundaryMat = splitMatrix;
	 DrawContoursAroundSegments(boundaryMat, width, height, -1);

	 boundaryImage = cvCloneImage(srcImage);

	 for (int i=0; i<height; i++)
	 {
		 for (int j=0; j<width; j++)
		 {
			 if (boundaryMat[i][j] == -1)
			 {
				 cvSet2D(boundaryImage, i, j, CV_RGB(255,255,255));
			 }			
		 }
	 }
 }

 //����ǰ����ͼƬ
 void CMagicCabsineSplitData::computeFrontBackImage()
 {
	 if (frontIDs.empty() && backIDs.empty())
	 {
		 for (int i=0; i<regionMasks.size(); i++)
		 {
			 backIDs.insert(i+1);
		 }
	 }

	 if (frontBackImg != NULL)
	 {
		 cvReleaseImage(&frontBackImg);
	 }
	 frontBackImg=cvCloneImage(srcImage);

	 int tempRegionID = 0;
	 for (int i=0; i<height; i++)
	 {
		 for (int j=0; j<width; j++)
		 {
			 tempRegionID = splitMatrix[i][j];
			 if (frontIDs.find(tempRegionID) != frontIDs.end())
			 {
				 cvSet2D(frontBackImg, i, j, CV_RGB(0,0,255));
			 }
			 else
			 {
				 cvSet2D(frontBackImg, i, j, CV_RGB(255,0,0));
			 }
		 }
	 }
 }


void CMagicCabsineSplitData::ComputeRegionMask()
{
	if(!isCalced)
	{
		ComputeSplitData();
	}
	int i,j,k;
	int height=srcImage->height;
	int width=srcImage->width;
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

void CMagicCabsineSplitData::GetSplitResult(vector< vector<int> > &tempMatrix,
											vector< vector< vector<int> > > &tempMask)
{
	ComputeRegionMask();
	tempMatrix=splitMatrix;
	tempMask=regionMasks;
}

void CMagicCabsineSplitData::splitRegion(vector<CvPoint> splitLine)
{
	if(regionOpe == NULL)
	{
		ComputeSplitData();
	}
	
	regionOpe->SetAreaMatrix(splitMatrix);//Ϊ�˽��г���������������������ӵĴ���
	regionOpe->RegionSplit(splitLine);
	displayImage = cvCloneImage(regionOpe->GetDisplayImage());
	regionOpe->GetAreaMatrix(splitMatrix);
	ComputeRegionMask();
	computeBoundaryImage();
}

//�ϲ�����
void CMagicCabsineSplitData::mergeRegion(vector<CvPoint> mergeLine)
{
	if(regionOpe == NULL)
	{
		ComputeSplitData();
	}

	regionOpe->SetAreaMatrix(splitMatrix);//Ϊ�˽��г���������������������ӵĴ���
	regionOpe->RegionMerge(mergeLine);
	displayImage = cvCloneImage(regionOpe->GetDisplayImage());
	regionOpe->GetAreaMatrix(splitMatrix);
	ComputeRegionMask();
	computeBoundaryImage();
}

void CMagicCabsineSplitData::modifyRegion(vector<CvPoint> modifyLine)
{
	if(regionOpe == NULL)
	{
		ComputeSplitData();
	}

	regionOpe->SetAreaMatrix(splitMatrix);//Ϊ�˽��г���������������������ӵĴ���
	regionOpe->RegionModifyBoundary(modifyLine);
	displayImage = cvCloneImage(regionOpe->GetDisplayImage());
	regionOpe->GetAreaMatrix(splitMatrix);
	ComputeRegionMask();
	computeBoundaryImage();
	computeFrontBackImage();
}


void CMagicCabsineSplitData::DrawContoursAroundSegments(vector< vector<int> > &segmentedImage,
														const int &width,const int &height,const int &color)
{
	// Pixel offsets around the centre pixels starting from left, going clockwise
	const int dx8[8] = {-1, -1,  0,  1, 1, 1, 0, -1};
	const int dy8[8] = { 0, -1, -1, -1, 0, 1, 1,  1};

	int sz = width * height;
	vector<bool> istaken(sz, false);
	int mainindex(0);
	for( int j = 0; j < height; j++ )
	{
		for( int k = 0; k < width; k++ )
		{
			int np(0);
			for( int i = 0; i < 8; i++ )
			{
				int x = k + dx8[i];
				int y = j + dy8[i];

				if( (x >= 0 && x < width) && (y >= 0 && y < height) )
				{
					//					int index = y*width + x;
					if( false == istaken[ y*width + x] )
					{
						if( (int)segmentedImage[j][k] != (int)segmentedImage[y][x] ) np++;
					}
				}
			}
			if( np > 2 )//1 for thicker lines and 2 for thinner lines
			{
				segmentedImage[j][k] = color;
				istaken[j*width+k] = true;
			}
		}
	}
}

//���ݱ����Ϣ����¼ǰ���ͱ����������:
//isFrontΪtrue���ʾ�����������ǰ��
//isFrontΪfalse��ʾ����������Ǳ���
void CMagicCabsineSplitData::markFrontAndBack(vector<CvPoint>& markLine, bool isFront)
{
	if(regionOpe == NULL)
	{
		ComputeSplitData();
	}

	if (regionOpe->GetMaxRegionNum() != regionOpe->GetNumOfRegions())
	{
		regionOpe->RearrangeRegionNum();
	}
	regionOpe->GetAreaMatrix(splitMatrix);
	

	set<int> temp;
	temp.clear();

	CvPoint tempPoint;
	for (int i=0; i<markLine.size(); i++)
	{
		tempPoint = markLine[i];
		temp.insert(splitMatrix[tempPoint.x][tempPoint.y]);
	}

	if (isFront)
	{
		int tempInt;
		for (set<int>::iterator ite=temp.begin(); ite!=temp.end(); ite++)
		{
			tempInt = *ite;
			frontIDs.insert(tempInt);
		}
		for (set<int>::iterator ite=temp.begin(); ite!=temp.end(); ite++)
		{
			tempInt = *ite;
			backIDs.erase(tempInt);
		}
	}
	else
	{
		int tempInt;
		for (set<int>::iterator ite=temp.begin(); ite!=temp.end(); ite++)
		{
			tempInt = *ite;
			frontIDs.erase(tempInt);
		}
		for (set<int>::iterator ite=temp.begin(); ite!=temp.end(); ite++)
		{
			tempInt = *ite;
			backIDs.insert(tempInt);
		}
	}

}


void CMagicCabsineSplitData::LoadSplitData()//�麯��,�����ݿ���ļ���������Ҫ������
{
	//Ŀǰ��ʱ�ȴ��ļ��ж�ȡ
//	LoadSplitDataFile(theApp.GetDefaultPath()+"SPLITres.txt");

	if(isCalced)
	{
		regionOpe = new ImageRegionOperator(srcImage, splitMatrix);
		regionOpe->CalcAverageColor();
		displayImage = cvCloneImage(regionOpe->GetDisplayImage());
// 		computeBoundaryImage();
// 		computeFrontBackImage();
	}
}

void CMagicCabsineSplitData::SaveSplitData()//�麯��,���������ݱ��������ݿ���ļ���
{
	//Ŀǰ��ʱ���浽�ļ���
//	SaveSplitDataFile(theApp.GetDefaultPath()+"SPLITres.txt");
}


 void CMagicCabsineSplitData::regularMarkID()		//������ָ���ߺϲ�֮�󣬱�ǵ�IDֵҲ��֮�ı�
 {
 	map<int, CvPoint> regionPoints;
 	int width = srcImage->width;
 	int height = srcImage->height;
 	int tempRegionID = 0;
 	for (int i=0; i<height; i++)
 	{
 		for (int j=0; j<width; j++)
 		{
 			tempRegionID = splitMatrix[i][j];
 			if(regionPoints.find(tempRegionID) == regionPoints.end())
 			{
 				regionPoints.insert(pair<int, CvPoint>(tempRegionID, cvPoint(i,j)));
 			}
 		}
 	}
 
 	frontIDs.clear();
 	backIDs.clear();
 	CvPoint tempPoint;
 	CvScalar tempColor;
 	for (map<int, CvPoint>::const_iterator ite=regionPoints.begin(); ite!=regionPoints.end(); ite++)
 	{
 		tempRegionID = ite->first;
 		tempPoint = ite->second;
 		tempColor = cvGet2D(frontBackImg, tempPoint.x, tempPoint.y);
 		if (tempColor.val[0] == 255 &&
 			tempColor.val[1] == 0 &&
 			tempColor.val[2] == 0)
 		{
 			frontIDs.insert(tempRegionID);
 		}
 		else
 		{
 			backIDs.insert(tempRegionID);
 		}
 	}
 	regionPoints.clear();
}


void CMagicCabsineSplitData::computeMarkedRegionID()			//���ݷָ�ǰ�ı����Ϣ������������ǰ�����Ǳ���
{
	for (int i=0; i<backLines.size(); i++)
	{
		markFrontAndBack(backLines[i], false);
	}

	for (int j=0; j<foreLines.size(); j++)
	{
		markFrontAndBack(foreLines[j], true);
	}
}


void CMagicCabsineSplitData::getForeBackData(set<int>& tempFrontIDs, set<int>& tempBackIDs)
{
	tempFrontIDs=frontIDs;
	tempBackIDs=backIDs;
}

//����һ������Ϊǰ�����߱���:���isFrontΪTRUE����Ϊǰ��������Ϊ����
void CMagicCabsineSplitData::setRegionFrontOrBack(int regionID, BOOL isFront)
{
	if (isFront==TRUE)
	{
		frontIDs.insert(regionID);
		backIDs.erase(regionID);
	}
	else
	{
		frontIDs.erase(regionID);
		backIDs.insert(regionID);
	}

	computeFrontBackImage();
}



//�ػ�һ���������ɫ��
void CMagicCabsineSplitData::rePaintDisplayImg(int regionID, int color_R, int color_G, int color_B)
{
	vector<vector<int>>& tempMask = regionMasks[regionID];
	CvScalar tempColor = CV_RGB(color_R, color_G, color_B);
	for (int i=0; i<height; i++)
	{
		for (int j=0; j<width; j++)
		{
			if (tempMask[i][j] == 1)
			{
				cvSet2D(displayImage, i, j, tempColor);
			}
		}
	}
}


void CMagicCabsineSplitData::regularAllData()
{
	regionOpe->RearrangeRegionNum();
	regionOpe->GetAreaMatrix(splitMatrix);
	ComputeRegionMask();
	regularMarkID();
}

//????
int CMagicCabsineSplitData::getMaxNum()
{
	int i,j;
	int ans=-1;
	for(i=0;i<splitMatrix.size();i++)
	{
		for(j=0;j<splitMatrix[0].size();j++)
		{
			ans=max(ans,splitMatrix[i][j]);
		}
	}
	return ans;
}