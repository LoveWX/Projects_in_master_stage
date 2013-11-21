#include "StdAfx.h"
#include "CMagicCabsineSplitData_Meanshift.h"
#include <fstream>
#include <cv.h>
#include <highgui.h>
using namespace std;

CMagicCabsineSplitData_Meanshift::CMagicCabsineSplitData_Meanshift(const IplImage *tempSrcImage)
			:	CMagicCabsineSplitData(tempSrcImage)
{
	methodType = SPLIT_MARK_NONE;
	splitName=string("MeanShift");
	splitTips=string("请对前景区域和背景区域进行标记");
	if(tempSrcImage==NULL)
	{
		exit(0);
	}
}

CMagicCabsineSplitData_Meanshift::~CMagicCabsineSplitData_Meanshift(void)
{
	DeleteSplitData();
}



void CMagicCabsineSplitData_Meanshift::DrawMarks()//将用户标记绘制在源图像上,结果保存在markImage中
{
	//此处分割方法是自动分割，不考虑标记数据
}

void CMagicCabsineSplitData_Meanshift::LoadSplitData()
{
	//目前暂时先从文件中读取
// 	LoadSplitDataFile(theApp.GetDefaultPath() + "SPLITres.txt");
	LoadSplitDataFile(theApp.GetProjectPath() + "SPLITres.txt");
}

void CMagicCabsineSplitData_Meanshift::SaveSplitData()
{
	//目前暂时保存在文件中
// 	SaveSplitDataFile(theApp.GetDefaultPath() + "SPLITres.txt");
	SaveSplitDataFile(theApp.GetProjectPath() + "SPLITres.txt");
}

void CMagicCabsineSplitData_Meanshift::LoadSplitDataFile(string filepath)
{
	isCalced=true;

	int i,j;
	int height,width;

	ifstream fin(filepath);
	fin>>height>>width;
	//注意这里height和width两个变量可能出现同时为0的情况
	//这种情况表示保存的信息中只有用户标记没有计算分割矩阵
	for(i=0;i<height;i++)
	{
		for(j=0;j<width;j++)
		{
			fin>>splitMatrix[i][j];
		}
	}

	ComputeRegionMask();

	int frontIDNum;
	int tempRegionID;
	fin >> frontIDNum;
	for (int k=0; k<frontIDNum; k++)
	{
		fin >> tempRegionID;
		frontIDs.insert(tempRegionID);
	}

	int backIDNum;
	fin >> backIDNum;
	for (int k=0; k<backIDNum; k++)
	{
		fin >> tempRegionID;
		backIDs.insert(tempRegionID);
	}

	fin.close();

	if(height==0&&width==0)
	{
		isCalced=false;
		return;
	}

	string tempPath=filepath.substr(0,filepath.size()-10)+"BOUNDARYresult.jpg";
	boundaryImage=cvLoadImage(tempPath.c_str(),1);
	tempPath=filepath.substr(0,filepath.size()-10)+"result.jpg";
	displayImage=cvLoadImage(tempPath.c_str(),1);
	tempPath=filepath.substr(0,filepath.size()-10)+"frontBack.jpg";
	frontBackImg=cvLoadImage(tempPath.c_str(),1);

	CMagicCabsineSplitData::LoadSplitData();
}

void CMagicCabsineSplitData_Meanshift::SaveSplitDataFile(string filepath)
{
	int i,j;
	string tempPath;
	int height = srcImage->height;
	int width = srcImage->width;

	//有可能有用户标记但是没有计算出分割结果的情况
	//这种情况下分割矩阵的长宽置为0,没有其它数据输出,load时需先判断这两个值
	ofstream fout(filepath);
	if(!isCalced)//只有用户标记,没有计算分割矩阵
	{
		fout<<"0 0"<<endl;
		fout.close();
		return;
	}
	fout<<height<<' '<<width<<endl;
	for(i=0;i<height;i++)
	{
		for(j=0;j<width;j++)
		{
			fout<<splitMatrix[i][j]<<' ';
		}
		fout<<endl;
	}

	int frontIDNum = frontIDs.size();
	int tempRegionID;
	fout << frontIDNum << endl;
	for (set<int>::iterator ite=frontIDs.begin(); ite!=frontIDs.end(); ite++)
	{
		tempRegionID = *ite;
		fout << tempRegionID << ' ';
	}
	fout << endl;

	int backIDNum = backIDs.size();
	fout << backIDNum << endl;
	for (set<int>::iterator ite=backIDs.begin(); ite!=backIDs.end(); ite++)
	{
		tempRegionID = *ite;
		fout << tempRegionID << ' ';
	}
	fout << endl;

	fout.close();

	tempPath=filepath.substr(0,filepath.size()-10)+"BOUNDARYresult.jpg";
	cvSaveImage(tempPath.c_str(),boundaryImage);
	tempPath=filepath.substr(0,filepath.size()-10)+"result.jpg";
	cvSaveImage(tempPath.c_str(),displayImage);
	tempPath=filepath.substr(0,filepath.size()-10)+"frontBack.jpg";
	cvSaveImage(tempPath.c_str(),frontBackImg);
}

//纯虚函数,子类实现该函数以完成某一全局特征的计算,计算完成后置isCalced=true
void CMagicCabsineSplitData_Meanshift::ComputeSplitData()
{
	vector<UINT> img(0);// or UINT* imgBuffer;
	int width = srcImage->width;
	int height = srcImage->height;
	int sz = width*height;
	img.resize(sz);

	CvSize tempSize;
	tempSize.width = width;
	tempSize.height = height;
	for (int i=0; i<height; i++)
	{
		for (int j=0; j<width; j++)
		{
			UINT temp = 0;

			int b =  (int)(cvGet2D(srcImage,i,j).val[0]);
			int g =  (int)(cvGet2D(srcImage,i, j).val[1]);
			int r =  (int)(cvGet2D(srcImage,i, j).val[2]);

			temp = temp | b;
			temp = temp << 8;
			temp = temp | g;
			temp = temp << 8;
			temp = temp | r;

			img[i*width+j] = temp;
		}
	}

	vector<UINT> segimg;
	vector<int> labels(0);
	int numlabels(0);

	int segmaS = 7;
	int segmaR = 10;

	//可允许开发者调节参数
	int minRegion = 1000;

	DoMeanShiftSegmentation(img, width, height, segimg, segmaS, segmaR, minRegion, labels, numlabels);

	splitMatrix.resize(height);
	for (int i=0; i<height; i++)
	{
		splitMatrix[i].resize(width);
	}
	map<UINT, int> regionMap;

	regionMap.clear();
	int regionID = 0;
	int tempIndex;
	for (int i=0; i<height; i++)
	{
		for (int j=0; j<width; j++)
		{
			tempIndex = i*width+j;
			if (regionMap.find(segimg[tempIndex])== regionMap.end())
			{
				regionMap.insert(pair<UINT, int>(segimg[tempIndex], regionID++));
			}
			splitMatrix[i][j] = regionMap.find(segimg[tempIndex])->second;
		}
	}

	isCalced = true;

	CMagicCabsineSplitData::ComputeSplitData();
}

//删除分割数据,所有动态申请的空间都应在此函数中释放并将指针置为空,子类析构函数中可调用其类中对该函数的实现用于析构
void CMagicCabsineSplitData_Meanshift::DeleteSplitData()
{
	splitMatrix.clear();
	regionMasks.clear();
	cvReleaseImage(&boundaryImage);
	cvReleaseImage(&displayImage);
}

//===========================================================================
//	DoMeanShiftSegmentation
//===========================================================================
void CMagicCabsineSplitData_Meanshift::DoMeanShiftSegmentation(
							 const vector<UINT>&					inputImg,
							 const int&								width,
							 const int&								height,
							 vector<UINT>&							segimg,
							 const int&								sigmaS,
							 const float&							sigmaR,
							 const int&								minRegion,
							 vector<int>&							labels,
							 int&									numlabels)
{
	int sz = width*height;
	_byte* _bytebuff = new _byte[sz*3];
	{int i(0);
	for( int p = 0; p < sz; p++ )
	{
		_bytebuff[i+0] = inputImg[p] >> 16 & 0xff;
		_bytebuff[i+1] = inputImg[p] >>  8 & 0xff;
		_bytebuff[i+2] = inputImg[p]       & 0xff;
		i += 3;
	}}
	msImageProcessor mss;
	mss.DefineImage(_bytebuff, COLOR, height, width);		
	mss.Segment(sigmaS, sigmaR, minRegion, HIGH_SPEEDUP);
	mss.GetResults(_bytebuff);

	int* p_labels = new int[sz];
	/*numlabels = */mss.GetLabels(p_labels);
	labels.resize(sz);
	for( int n = 0; n < sz; n++ ) labels[n] = p_labels[n];
	if(p_labels) delete [] p_labels;

	segimg.resize(sz);
	int bsz = sz*3;
	{int i(0);
	for( int p = 0; p < bsz; p += 3 )
	{
		segimg[i] = _bytebuff[p] << 16 | _bytebuff[p+1] << 8 | _bytebuff[p+2];
		i++;
	}}
	if(_bytebuff) delete [] _bytebuff;
}

//画轮廓边界
void CMagicCabsineSplitData_Meanshift::DrawContoursAroundSegments(
								vector<UINT>&							segmentedImage,
								const int&								width,
								const int&								height,
								const UINT&								color)
{
	// Pixel offsets around the centre pixels starting from left, going clockwise
	const int dx8[8] = {-1, -1,  0,  1, 1, 1, 0, -1};
	const int dy8[8] = { 0, -1, -1, -1, 0, 1, 1,  1};

	int sz = segmentedImage.size();
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
					int index = y*width + x;
					if( false == istaken[index] )
					{
						if( (int)segmentedImage[mainindex] != (int)segmentedImage[index] ) np++;
					}
				}
			}
			if( np > 2 )//1 for thicker lines and 2 for thinner lines
			{
				segmentedImage[j*width + k] = color;
				istaken[mainindex] = true;
			}
			mainindex++;
		}
	}
}
