#include "stdafx.h"
#include "MainFrm.h"
#include "CMagicCabsineDoc.h"
#include "CMagicCabsineUniversalProperty_VectorField.h"
#include "VectorShow.h"
#include "bresenham.h"

#include "imatrix.h"
#include "ETF.h"
#include "fdog.h"
#include "myvec.h"

#define PI 3.14159265358979

// CMagicCabsineUniversalProperty_VectorField::CMagicCabsineUniversalProperty_VectorField(const IplImage *tempSrcImage)
// 	:CMagicCabsineUniversalProperty(tempSrcImage)
// {
// 	propertyName=string("VectorField");
// 	pointOfCLD = NULL;
// }

CMagicCabsineUniversalProperty_VectorField::CMagicCabsineUniversalProperty_VectorField(const IplImage *tempSrcImage)
	:CMagicCabsineUniversalProperty(tempSrcImage)
{
	propertyName=string("VectorField");
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

	pointOfCLD = NULL;
	cldImage = NULL;
	isCLDnewed=false;
// 	//首先查看cld特征是否已经计算出来了，如果计算出来了，在此处用计算的结果初始化cldImage
// 	MainFrame *mainFrame=(MainFrame*)AfxGetMainWnd();
// 	CMagicCabsineDoc* pDoc=(CMagicCabsineDoc*)(mainFrame->GetActiveDocument());
// 	vector<CMagicCabsineUniversalProperty *>&  propSet  = pDoc->theProject->getUniversalProperties();
// 	if (propSet[0] != NULL )
// 	{
// 		string strName;
// 		propSet[0]->GetPropertyName(strName);
// 		if (strName == "CLD")
// 			cldImage = propSet[0]->GetDisplayImage();
// 		else
// 			cldImage = NULL;
// 	}
// 	else
// 		cldImage = NULL;
// 
// 	//如果没有计算出来，在此处计算cld特征并初始化cldImage
// 	if (cldImage == NULL)
// 	{
// 		CMagicCabsineUniversalProperty_CLD *tp0=new CMagicCabsineUniversalProperty_CLD(srcImage);
// 		tp0->ComputeProperty();
// 		cldImage = tp0->GetDisplayImage();
// 	}
}

CMagicCabsineUniversalProperty_VectorField::CMagicCabsineUniversalProperty_VectorField(const IplImage *tempSrcImage,
	CMagicCabsineUniversalProperty_CLD *tempCLDPoint):CMagicCabsineUniversalProperty(tempSrcImage)
{
	propertyName=string("VectorField");
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

	pointOfCLD = tempCLDPoint;
	cldImage = NULL;
	isCLDnewed=false;
// 	//首先查看cld特征是否已经计算出来了，如果计算出来了，在此处用计算的结果初始化cldImage
// 	MainFrame *mainFrame=(MainFrame*)AfxGetMainWnd();
// 	CMagicCabsineDoc* pDoc=(CMagicCabsineDoc*)(mainFrame->GetActiveDocument());
// 	vector<CMagicCabsineUniversalProperty *>&  propSet  = pDoc->theProject->getUniversalProperties();
// 	if (propSet[0] != NULL )
// 	{
// 		string strName;
// 		propSet[0]->GetPropertyName(strName);
// 		if (strName == "CLD")
// 			cldImage = propSet[0]->GetDisplayImage();
// 		else
// 			cldImage = NULL;
// 	}
// 	else
// 		cldImage = NULL;
// 
// 	//如果没有计算出来，在此处计算cld特征并初始化cldImage
// 	if (cldImage == NULL)
// 	{
// 		CMagicCabsineUniversalProperty_CLD *tp0=new CMagicCabsineUniversalProperty_CLD(srcImage);
// 		tp0->ComputeProperty();
// 		cldImage = tp0->GetDisplayImage();
// 	}
}

CMagicCabsineUniversalProperty_VectorField::~CMagicCabsineUniversalProperty_VectorField()
{
	DeleteProperty();
	height=0;
	width=0;
	cldImage=NULL;
	if(isCLDnewed&&pointOfCLD!=NULL)
	{
		delete pointOfCLD;
		pointOfCLD=NULL;
	}
	isCLDnewed=false;
}

void CMagicCabsineUniversalProperty_VectorField::ComputeProperty()
{
	imatrix img(srcImage->height,srcImage->width);
	IplImage* dst = cvCreateImage(cvGetSize(srcImage),srcImage->depth,1);
	cvCvtColor(srcImage,dst,CV_BGR2GRAY);
	CvScalar s;
	for(int r=0;r<srcImage->height;r++)
	{
		for(int c=0;c<srcImage->width;c++)
		{
			s=cvGet2D(dst,r,c);
			img[r][c]=s.val[0];
		}
	}	
	int image_r = img.getRow();
	int image_c = img.getCol();
	ETF e;
	e.init(image_r, image_c);
	e.set2(img);
	e.Smooth(6, 3);

	cv::Mat result;
	result.create(srcImage->height,srcImage->width,CV_32FC1);
	for (int r=0;r<img.getRow();r++)
	{
		for (int c=0;c<img.getCol();c++)
		{
			Vect vec = e.get(r,c);
			double tx = vec.tx;
			double ty = vec.ty;

			float angle;
			if (ty==0)
			{
				angle = 0.0;
			}
			else angle = atan(tx/ty);
			//angle = 2*3/PI;
			if(angle<0)		angle=PI+angle;
			if(angle>PI)	angle=angle-PI;

			result.at<float>(r,c) = angle;
		}
	}
	//获取最终结果矢量场矩阵的数据
	for (int row=0;row<height;row++)
	{
		for (int col=0;col<width;col++)
		{
			ansMatrix[row][col] = (double)(result.at<float>(row,col));
		}
	}


	//获取最终结果矢量场的显示图像
	VectorShow VecShow=VectorShow(width,height);
	VecShow.SyntheszVector(ansMatrix);
	VecShow.NormalizVectrs();
	VecShow.GenBoxFiltrLUT(DISCRETE_FILTER_SIZE);
	VecShow.MakeWhiteNoise();
	VecShow.FlowImagingLIC(LOWPASS_FILTR_LENGTH);
	CvSize size;
	size.width=width;
	size.height=height;
	IplImage* tempshowImage;
	tempshowImage=cvCreateImage(size,IPL_DEPTH_8U,1);
	for(int i=0;i<width;i++)
	{
		for(int j=0;j<height;j++)
		{
			CvScalar col;
			col.val[0]=0;
			cvSet2D(tempshowImage,j,i,col);
		}
	}
	for(int  j = 0;  j < height;  j ++)
	{
		for(int  i = 0;  i < width;  i ++)
		{
			CvScalar col;
			col.val[0]=VecShow.pImage[j * width + i];
			cvSet2D(tempshowImage,j,i,col);
		}
	}
	//propShow->getImage()=tempshowImage;
	if(displayImage!=NULL)
	{
		delete displayImage;
		displayImage=NULL;
	}
	displayImage = tempshowImage;

	isCalced=true;

// 	SaveProperty();

	return;







//	if (pointOfCLD != NULL)
//	{
//		cldImage = pointOfCLD->GetDisplayImage();
//		if (cldImage == NULL)
//		{
//			pointOfCLD->ComputeProperty();
//			cldImage = pointOfCLD->GetDisplayImage();
//		}
//	}
//	else
//	{
//		isCLDnewed=true;
//		pointOfCLD = new CMagicCabsineUniversalProperty_CLD(srcImage);
//		pointOfCLD->ComputeProperty();
//		cldImage = pointOfCLD->GetDisplayImage();
//	}
//
//	CvMat* imMat = cvCreateMat(height,width,CV_32FC1);
//	for (int row=0;row<cldImage->height;row++)
//	{
//		for (int col=0;col<cldImage->width;col++)
//		{
//			cvmSet(imMat,row,col,/*255-*/cvGetReal2D(cldImage,row,col));
//		}
//	}
//	cvNormalize(imMat,imMat,1,0,CV_MINMAX,NULL);
//	CvMat* gdMat = cvCreateMat(height, width,CV_32FC1);
//
//	//灰度化
//	IplImage *imTemp = cvCreateImage(cvGetSize(srcImage),IPL_DEPTH_8U,1);
//	cvCvtColor(srcImage, imTemp,CV_RGB2GRAY);
//	//求梯度
//	IplImage *dest_dx, *dest_dy;
//	dest_dx = cvCreateImage(cvGetSize(srcImage),IPL_DEPTH_16S,1);
//	dest_dy = cvCreateImage(cvGetSize(srcImage),IPL_DEPTH_16S,1);
//	cvSobel( imTemp, dest_dx, 1, 0, 3);
//	cvSobel( imTemp, dest_dy, 0, 1, 3);
//
//
//	for (int row=0;row<srcImage->height;row++)
//	{
//		for (int col=0;col<srcImage->width;col++)
//		{
//			double dx = cvGetReal2D(dest_dx,row,col);
//			double dy = cvGetReal2D(dest_dy,row,col);
//			double gd = sqrt(dx*dx+dy*dy);
//			cvmSet(gdMat,row,col,gd);
//		}
//	}
//
//
//	IplImage *tan_dx,*tan_dy;
//	tan_dx = cvCloneImage(dest_dy);
//	tan_dy = cvCloneImage(dest_dx);
//	CvMat* tan_gdx = cvCreateMat(srcImage->height,srcImage->width,CV_32FC1);
//	CvMat* tan_gdy = cvCreateMat(srcImage->height,srcImage->width,CV_32FC1);
//	for (int row=0;row<tan_dx->height;row++)
//	{
//		for (int col=0;col<tan_dx->width;col++)
//		{
//			double val = -cvGet2D(dest_dy,row,col).val[0];
//			cvSetReal2D(tan_dx,row,col,val);
//
//			double dx = cvGetReal2D(dest_dx,row,col);
//			double dy = cvGetReal2D(dest_dy,row,col);
//			double tanx,tany;
//			if (dx==0 && dy==0)
//			{
//				tanx = 0;
//				tany = 0;
//			}
//			else{
//				tanx = -dy/sqrt(dx*dx+dy*dy);
//				tany = dx/sqrt(dx*dx+dy*dy);
//			}
//			cvmSet(tan_gdx,row,col,tanx);
//			cvmSet(tan_gdy,row,col,tany);
//		}
//	}
//
//	CvMat* dirMat = cvCreateMat(srcImage->height,srcImage->width,CV_32FC1);
//	cvZero(dirMat);
//	CvMat* dirMatT = cvCreateMat(srcImage->height,srcImage->width,CV_32FC1);
//	cvZero(dirMatT);
//	CvMat* dirX = cvCreateMat(srcImage->height,srcImage->width,CV_32FC1);
//	cvZero(dirX);
//	CvMat* dirY = cvCreateMat(srcImage->height,srcImage->width,CV_32FC1);
//	cvZero(dirY);
//	for (int row=0;row<srcImage->height;row++)
//	{
//		for (int col=0;col<srcImage->width;col++)
//		{
//			int cr = row;
//			int cc = col;
//			int ns = (int)(5 + (15-5)*cvmGet(imMat,cr,cc));
//			int k = ns/2;
//			double sum = 0;
//			vector<double> v1,v2,v3,v4;
//			for (int tr=cr-k;tr<cr+k;tr++)
//			{
//				for (int tc=cc-k;tc<cc+k;tc++)
//				{
//					if (tr>=0&&tr<srcImage->height&&tc>=0&&tc<srcImage->width&&tr!=cr&&tc!=cc)
//					{
//						double w1 = ClosenessWeight(imMat,cr,cc,tr,tc);
//						double w2 = FeatureWeight(gdMat,cr,cc,tr,tc);
//						v1.push_back(w1);
//						v2.push_back(w2);
//						sum += ClosenessWeight(imMat,cr,cc,tr,tc)*FeatureWeight(gdMat,cr,cc,tr,tc);
//					}
//				}
//			}
//			double upx = 0;
//			double upy = 0;
//			for (int tr=cr-k;tr<cr+k;tr++)
//			{
//				for (int tc=cc-k;tc<cc+k;tc++)
//				{
//					if (tr>=0&&tr<srcImage->height&&tc>=0&&tc<srcImage->width&&tr!=cr&&tc!=cc)
//					{
//						double w1 = ClosenessWeight(imMat,cr,cc,tr,tc);
//						double w2 = FeatureWeight(gdMat,cr,cc,tr,tc);
//						double w3 = cvGetReal2D(tan_dx,tr,tc);
//						double w4 = cvGetReal2D(tan_dy,tr,tc);
//						v3.push_back(w3);
//						v4.push_back(w4);
//
//						upx += cvmGet(tan_gdx,tr,tc)*ClosenessWeight(imMat,cr,cc,tr,tc)*FeatureWeight(gdMat,cr,cc,tr,tc);
//						upy += cvmGet(tan_gdy,tr,tc)*ClosenessWeight(imMat,cr,cc,tr,tc)*FeatureWeight(gdMat,cr,cc,tr,tc);
//					}
//				}
//			}
//			double dx = upx/sum;
//			double dy = upy/sum;
//			double angle;
//			if (dx==0)
//			{
//				angle = 0.0;
//			}
//			else angle = atan(dy/dx)*180/PI;
//			cvmSet(dirX,cr,cc,cos(angle*PI/180));
//			cvmSet(dirY,cr,cc,sin(angle*PI/180));
//			cvmSet(dirMat,cr,cc,angle);
//			cvmSet(dirMatT,cr,cc,angle*PI/180);
//
//			double a = cos(angle*PI/180);
//			double b = sin(angle*PI/180);
//			if (a!=0 && b!=0)
//			{
//				int c = (int)(a+b);
//			}
//		}
//	}
//	//获取最终结果矢量场矩阵的数据
//	for (int row=0;row<height;row++)
//	{
//		for (int col=0;col<width;col++)
//		{
//			ansMatrix[row][col] = cvmGet(dirMatT,row,col);
//		}
//	}
//
//
//	//获取最终结果矢量场的显示图像
//	VectorShow VecShow=VectorShow(width,height);
//	VecShow.SyntheszVector(ansMatrix);
//	VecShow.NormalizVectrs();
//	VecShow.GenBoxFiltrLUT(DISCRETE_FILTER_SIZE);
//	VecShow.MakeWhiteNoise();
//	VecShow.FlowImagingLIC(LOWPASS_FILTR_LENGTH);
//	CvSize size;
//	size.width=width;
//	size.height=height;
//	IplImage* tempshowImage;
//	tempshowImage=cvCreateImage(size,IPL_DEPTH_8U,1);
//	for(int i=0;i<width;i++)
//	{
//		for(int j=0;j<height;j++)
//		{
//			CvScalar col;
//			col.val[0]=0;
//			cvSet2D(tempshowImage,j,i,col);
//		}
//	}
//	for(int  j = 0;  j < height;  j ++)
//	{
//		for(int  i = 0;  i < width;  i ++)
//		{
//			CvScalar col;
//			col.val[0]=VecShow.pImage[j * width + i];
//			cvSet2D(tempshowImage,j,i,col);
//		}
//	}
//	//propShow->getImage()=tempshowImage;
//	if(displayImage!=NULL)
//	{
//		delete displayImage;
//		displayImage=NULL;
//	}
//	displayImage = tempshowImage;
//	
//	isCalced=true;
//	
//	SaveProperty();
}

void CMagicCabsineUniversalProperty_VectorField::SaveProperty()
{
	//目前暂时保存在文件中
// 	SavePropertyFile(theApp.GetDefaultPath()+"VECTORFIELDres.txt");
	SavePropertyFile(theApp.GetProjectPath()+"VECTORFIELDres.txt");
}

void CMagicCabsineUniversalProperty_VectorField::LoadProperty()
{
	//目前暂时先从文件中读取
// 	LoadPropertyFile(theApp.GetDefaultPath()+"VECTORFIELDres.txt");
	LoadPropertyFile(theApp.GetProjectPath()+"VECTORFIELDres.txt");
}

void CMagicCabsineUniversalProperty_VectorField::SavePropertyFile(string filepath)
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

void CMagicCabsineUniversalProperty_VectorField::LoadPropertyFile(string filepath)
{
	int i,j;
	ifstream fin(filepath);
	fin>>height>>width;
	height=srcImage->height;
	width=srcImage->width;
	vector<double> tempVector(width);
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

void CMagicCabsineUniversalProperty_VectorField::DeleteProperty()
{
	ansMatrix.clear();
}

void CMagicCabsineUniversalProperty_VectorField::GetProperty(vector< vector<double> > &tempMatrix)
{
	tempMatrix=ansMatrix;
}

double CMagicCabsineUniversalProperty_VectorField::ClosenessWeight(CvMat* imMat,int r1,int c1,int r2,int c2)
{
	double dis = (r1-r2)*(r1-r2)+(c1-c2)*(c1-c2);
	double sigma = 5+cvmGet(imMat,r1,c1);
	return exp(-dis/(2*sigma*sigma));
}
double CMagicCabsineUniversalProperty_VectorField::FeatureWeight(CvMat* gdMat,int r1,int c1,int r2,int c2)
{
	double gd1 = cvmGet(gdMat,r1,c1);
	double gd2 = cvmGet(gdMat,r2,c2);
	double sigma = 5;
	return exp((gd2-gd1)/(sigma*sigma));
}
