#include "StdAfx.h"
#include "CMagicCabsineSplitData_GraphBase.h"
#include <fstream>
using namespace std;

CMagicCabsineSplitData_GraphBase::CMagicCabsineSplitData_GraphBase(const IplImage *tempSrcImage)
	:CMagicCabsineSplitData(tempSrcImage)
{
	methodType = SPLIT_MARK_NONE;
	splitName=string("GraphBase");
	splitTips=string("初始化图像分割:\n自动分割方法GraphBase，不需要标注");
	regNum = 0;
	if(tempSrcImage==NULL)
	{
		exit(0);
	}
}


CMagicCabsineSplitData_GraphBase::~CMagicCabsineSplitData_GraphBase(void)
{
	DeleteSplitData();
}

void CMagicCabsineSplitData_GraphBase::DrawMarks()//将用户标记绘制在源图像上,结果保存在markImage中
{

}


void CMagicCabsineSplitData_GraphBase::LoadSplitData()//纯虚函数,从数据库或文件读入所需要的数据
{
	LoadSplitDataFile(theApp.GetProjectPath() + "SPLITres.txt");
}

void CMagicCabsineSplitData_GraphBase::SaveSplitData()//纯虚函数,将各种数据保存在数据库或文件中
{
	
	SaveSplitDataFile(theApp.GetProjectPath() + "SPLITres.txt");
}



void CMagicCabsineSplitData_GraphBase::LoadSplitDataFile(string filepath)
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

void CMagicCabsineSplitData_GraphBase::SaveSplitDataFile(string filepath)
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
void CMagicCabsineSplitData_GraphBase::ComputeSplitData()
{
	Mat img3f(srcImage);		//原始图像矩阵。

	img3f.convertTo(img3f, CV_32FC3, 1.0/255);//图片转换，可能是0-255之间转换到0-1之间，归一化


	GetRC(img3f, 0.4, 1000, 50, 0.5);		//Note:第三个参数是RegionNum，指示最小区域的像素数

	//paintRegionResult();

	img3f.release();

	isCalced = true;

	ComputeRegionMask();
	CMagicCabsineSplitData::ComputeSplitData();
}

//删除分割数据,所有动态申请的空间都应在此函数中释放并将指针置为空,子类析构函数中可调用其类中对该函数的实现用于析构
void CMagicCabsineSplitData_GraphBase::DeleteSplitData()
{
	splitMatrix.clear();
	regionMasks.clear();
	cvReleaseImage(&boundaryImage);
	cvReleaseImage(&displayImage);
}


Mat CMagicCabsineSplitData_GraphBase::GetRC(const Mat &img3f, double sigmaDist, double segK, int segMinSize, double segSigma)
{
	Mat regIdx1i, colorIdx1i, regSal1v, tmp, _img3f, color3fv;
	if (Quantize(img3f, colorIdx1i, color3fv, tmp) <= 2) // Color quantization颜色量化
		return Mat::zeros(img3f.size(), CV_32F);//返回值小于2 就返回空的图像

	cvtColor(img3f, _img3f, CV_BGR2Lab);

	cvtColor(color3fv, color3fv, CV_BGR2Lab);

	//分割图像，regNum是分割的区域数目
	regNum = SegmentImage(_img3f, regIdx1i, segSigma, segK, segMinSize);	

	//获取分割矩阵
	int width = regIdx1i.cols;
	int height = regIdx1i.rows;
	for (int i=0; i<height; i++)
	{
		splitMatrix[i].resize(width);
		for (int j = 0; j<width; j++)
		{
			splitMatrix[i][j] = regIdx1i.at<int>(i, j);
		}
	}
	
	return regIdx1i;
}


int CMagicCabsineSplitData_GraphBase::Quantize(const Mat& img3f, Mat &idx1i, Mat &_color3f, Mat &_colorNum, double ratio)
{
	static const int clrNums[3] = {12, 12, 12};
	static const float clrTmp[3] = {clrNums[0] - 0.0001f, clrNums[1] - 0.0001f, clrNums[2] - 0.0001f};
	static const int w[3] = {clrNums[1] * clrNums[2], clrNums[2], 1};

	CV_Assert(img3f.data != NULL);
	idx1i = Mat::zeros(img3f.size(), CV_32S);
	int rows = img3f.rows, cols = img3f.cols;
	if (img3f.isContinuous() && idx1i.isContinuous())
	{
		cols *= rows;
		rows = 1;
	}

	// Build color pallet
	map<int, int> pallet;
	for (int y = 0; y < rows; y++)
	{
		const float* imgData = img3f.ptr<float>(y);
		int* idx = idx1i.ptr<int>(y);
		for (int x = 0; x < cols; x++, imgData += 3)
		{
			idx[x] = (int)(imgData[0]*clrTmp[0])*w[0] + (int)(imgData[1]*clrTmp[1])*w[1] + (int)(imgData[2]*clrTmp[2]);
			pallet[idx[x]] ++;
		}
	}

	// Fine significant colors
	int maxNum = 0;
	{
		int count = 0;
		vector<pair<int, int>> num; // (num, color) pairs in num
		num.reserve(pallet.size());
		for (map<int, int>::iterator it = pallet.begin(); it != pallet.end(); it++)
			num.push_back(pair<int, int>(it->second, it->first)); // (color, num) pairs in pallet
		sort(num.begin(), num.end(), std::greater<pair<int, int>>());

		maxNum = (int)num.size();
		int maxDropNum = cvRound(rows * cols * (1-ratio));
		for (int crnt = num[maxNum-1].first; crnt < maxDropNum && maxNum > 1; maxNum--)
			crnt += num[maxNum - 2].first;
		maxNum = min(maxNum, 256); // To avoid very rarely case
		if (maxNum < 10)
			maxNum = min((int)pallet.size(), 100);
		pallet.clear();
		for (int i = 0; i < maxNum; i++)
			pallet[num[i].second] = i; 

		vector<Vec3i> color3i(num.size());
		for (unsigned int i = 0; i < num.size(); i++)
		{
			color3i[i][0] = num[i].second / w[0];
			color3i[i][1] = num[i].second % w[0] / w[1];
			color3i[i][2] = num[i].second % w[1];
		}

		for (unsigned int i = maxNum; i < num.size(); i++)
		{
			int simIdx = 0, simVal = INT_MAX;
			for (int j = 0; j < maxNum; j++)
			{
				int d_ij = vecSqrDist3(color3i[i], color3i[j]);
				if (d_ij < simVal)
					simVal = d_ij, simIdx = j;
			}
			pallet[num[i].second] = pallet[num[simIdx].second];
		}
	}

	_color3f = Mat::zeros(1, maxNum, CV_32FC3);
	_colorNum = Mat::zeros(_color3f.size(), CV_32S);

	Vec3f* color = (Vec3f*)(_color3f.data);
	int* colorNum = (int*)(_colorNum.data);
	for (int y = 0; y < rows; y++) 
	{
		const Vec3f* imgData = img3f.ptr<Vec3f>(y);
		int* idx = idx1i.ptr<int>(y);
		for (int x = 0; x < cols; x++)
		{
			int temp=idx[x];
			//cout<<idx[x]<<" ";
			idx[x] = pallet[temp];
			Vec3f tmpVec3f=imgData[x];
			temp=idx[x];
			//cout<<idx[x]<<" ";
			color[temp] += tmpVec3f;
			colorNum[temp] ++;
		}
	}
	//把_color3f 和 color 和colornum全部打到文件里，就知道是什么了
	for (int i = 0; i < _color3f.cols; i++)
	{
		color[i] /= colorNum[i];
		cout<<color[i].val[0]<<" "<<color[i].val[1]<<" "<<color[i].val[2]<<" "<<colorNum[i]<<endl;
	}

	cout<<_color3f.cols<<endl;
	return _color3f.cols;
}


//void CMagicCabsineSplitData_GraphBase::paintRegionResult()
//{
//	vector<double> colorR;
//	vector<double> colorG;
//	vector<double> colorB;
//	vector<int> regionSize;
//	vector<CvScalar> regionColor;
//
//	regionColor.resize(regNum);
//	regionSize.resize(regNum);
//	colorR.resize(regNum);
//	colorG.resize(regNum);
//	colorB.resize(regNum);
//	for(int i=0; i<regNum; i++)
//	{
//		colorR[i] = 0;
//		colorG[i] = 0;
//		colorB[i] = 0;
//		regionSize[i] = 0;
//	}
//
//	int regionID = -1;
//	int width = srcImage->width;
//	int height = srcImage->height;
//	CvScalar tempColor;
//	for (int i=0; i<height; i++)
//	{
//		for (int j=0; j<width; j++)
//		{
//			regionID = splitMatrix[i][j];
//			tempColor = cvGet2D(srcImage, i, j);
//			colorR[regionID] += tempColor.val[2];
//			colorG[regionID] += tempColor.val[1];
//			colorB[regionID] += tempColor.val[0];
//			regionSize[regionID]++;
//		}
//	}
//
//	for(int i=0; i<regNum; i++)
//	{
//		regionColor[i] = CV_RGB(colorR[i]/regionSize[i], colorG[i]/regionSize[i], colorB[i]/regionSize[i]);
//	}
//
//	CvSize tempSize;
//	tempSize.height = height;
//	tempSize.width = width;
//	displayImage = cvCreateImage(tempSize, IPL_DEPTH_8U, 3);
//	int colorIndex;
//	for (int i=0; i<height; i++)
//	{
//		for (int j=0; j<width; j++)
//		{
//			cvSet2D(displayImage, i, j, regionColor[splitMatrix[i][j]]);
//		}
//	}
//
//
//	vector<vector<int>> boundaryMat;
//	boundaryMat.resize(height);
//	for (int i=0; i<height; i++)
//	{
//		boundaryMat[i].resize(width);
//		for (int j=0; j<width; j++)
//		{
//			boundaryMat[i][j] = splitMatrix[i][j];
//		}
//	}
//
//	DrawContoursAroundSegments(boundaryMat, width, height, -1);
//
//	boundaryImage = cvCloneImage(displayImage);
//
//	for (int i=0; i<height; i++)
//	{
//		for (int j=0; j<width; j++)
//		{
//			if (boundaryMat[i][j] == -1)
//			{
//				cvSet2D(boundaryImage, i, j, CV_RGB(255,255,255));
//			}			
//		}
//	}
//}


void CMagicCabsineSplitData_GraphBase::DrawContoursAroundSegments(vector<vector<int>>							   &segmentedImage,
								const int&								width,
								const int&								height,
								const int&								color)
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
