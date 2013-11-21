#include "StdAfx.h"
#include "CMagicCabsineSplitData_GraphBase.h"
#include <fstream>
using namespace std;

CMagicCabsineSplitData_GraphBase::CMagicCabsineSplitData_GraphBase(const IplImage *tempSrcImage)
	:CMagicCabsineSplitData(tempSrcImage)
{
	methodType = SPLIT_MARK_NONE;
	splitName=string("GraphBase");
	splitTips=string("��ʼ��ͼ��ָ�:\n�Զ��ָ��GraphBase������Ҫ��ע");
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

void CMagicCabsineSplitData_GraphBase::DrawMarks()//���û���ǻ�����Դͼ����,���������markImage��
{

}


void CMagicCabsineSplitData_GraphBase::LoadSplitData()//���麯��,�����ݿ���ļ���������Ҫ������
{
	LoadSplitDataFile(theApp.GetProjectPath() + "SPLITres.txt");
}

void CMagicCabsineSplitData_GraphBase::SaveSplitData()//���麯��,���������ݱ��������ݿ���ļ���
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
	//ע������height��width�����������ܳ���ͬʱΪ0�����
	//���������ʾ�������Ϣ��ֻ���û����û�м���ָ����
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

	//�п������û���ǵ���û�м�����ָ��������
	//��������·ָ����ĳ�����Ϊ0,û�������������,loadʱ�����ж�������ֵ
	ofstream fout(filepath);
	if(!isCalced)//ֻ���û����,û�м���ָ����
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


//���麯��,����ʵ�ָú��������ĳһȫ�������ļ���,������ɺ���isCalced=true
void CMagicCabsineSplitData_GraphBase::ComputeSplitData()
{
	Mat img3f(srcImage);		//ԭʼͼ�����

	img3f.convertTo(img3f, CV_32FC3, 1.0/255);//ͼƬת����������0-255֮��ת����0-1֮�䣬��һ��


	GetRC(img3f, 0.4, 1000, 50, 0.5);		//Note:������������RegionNum��ָʾ��С�����������

	//paintRegionResult();

	img3f.release();

	isCalced = true;

	ComputeRegionMask();
	CMagicCabsineSplitData::ComputeSplitData();
}

//ɾ���ָ�����,���ж�̬����Ŀռ䶼Ӧ�ڴ˺������ͷŲ���ָ����Ϊ��,�������������пɵ��������жԸú�����ʵ����������
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
	if (Quantize(img3f, colorIdx1i, color3fv, tmp) <= 2) // Color quantization��ɫ����
		return Mat::zeros(img3f.size(), CV_32F);//����ֵС��2 �ͷ��ؿյ�ͼ��

	cvtColor(img3f, _img3f, CV_BGR2Lab);

	cvtColor(color3fv, color3fv, CV_BGR2Lab);

	//�ָ�ͼ��regNum�Ƿָ��������Ŀ
	regNum = SegmentImage(_img3f, regIdx1i, segSigma, segK, segMinSize);	

	//��ȡ�ָ����
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
	//��_color3f �� color ��colornumȫ�����ļ����֪����ʲô��
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
