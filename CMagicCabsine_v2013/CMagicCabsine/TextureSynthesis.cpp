#include "StdAfx.h"
#include "TextureSynthesis.h"
#include <cstdlib>
#include <ctime>
#include "copyimage.h"
#include <vector>
//#include <windows.h>
using namespace std;

//struct PosDist{//记录样本中窗口位置与当前窗口距离的数据结构
//	int Pos;
//	double Dist;
//};

CTextureSynthesis::CTextureSynthesis(void)
: imgSample(NULL)
, iThreadWidth(0)
, iSampleLength(0)
, imgSynthesis(NULL)
, iWindowSize(10)
{
}

CTextureSynthesis::~CTextureSynthesis(void)
{
	if(imgSample!=NULL)
		cvReleaseImage(&imgSample);
	if(imgSynthesis!=NULL)
		cvReleaseImage(&imgSynthesis);
}

// 获取绣线宽度
int CTextureSynthesis::getThreadWidth(void)
{
	return iThreadWidth;
	//return 9;

}

// 合成绣线，参数为合成绣线的长度（像素数）
IplImage * CTextureSynthesis::newThread(int iLength,COLORREF color)
{
// 	iThreadWidth = 2;
	if(imgSample==NULL)
		return NULL;
	
	IplImage *imgReturn = cvCreateImage(cvSize(iLength,iThreadWidth),IPL_DEPTH_8U,3);
	IplImage *imgTempReturn = cvCreateImage(cvSize(iLength,iThreadWidth),IPL_DEPTH_32F,1);
	srand((unsigned int)time(NULL));

	if(imgSynthesis!=NULL){
		if(iLength<=imgSynthesis->width){
			//已合成的绣线长度超过要合成的长度，从已合成的绣线中复制一段
			int sPoint=0;
			if(iLength<imgSynthesis->width)
				sPoint = rand()%(imgSynthesis->width-iLength);
			copySubImage(imgSynthesis,imgTempReturn,cvRect(sPoint,0,iLength,iThreadWidth));
		}
		else{
			//创建一个新的image,宽度为新的绣线长度，将已合成的部分复制到新的image,
			int start = imgSynthesis->width;
			IplImage *newThreadImage = cvCreateImage(cvSize(iLength,iThreadWidth),IPL_DEPTH_32F,1);
			copySubImage(imgSynthesis,newThreadImage,cvRect(0,0,imgSynthesis->width,iThreadWidth));
			cvReleaseImage(&imgSynthesis);
			imgSynthesis = newThreadImage;
			//合成start到iLength-1部分
			for(int i=start;i<iLength;i++){
				//vector<PosDist> v;
				int minPos=-1;
				double mindistance;

				for(int j=0;j<iSampleLength-iWindowSize-1;j++){
					//计算样本中j开始的窗口与当前合成点窗口的距离
					double distance=0;
					double weight=0.01;
					for(int r=0;r<iThreadWidth;r++){
						for(int col=0;col<iWindowSize;col++){
							CvScalar s1,s2;
							s1=cvGet2D(imgSample,r,col+j);
							s2=cvGet2D(imgSynthesis,r,i-iWindowSize+col);
							distance+= (s1.val[0]-s2.val[0])*(s1.val[0]-s2.val[0])*weight;
							//distance+=((s1.val[0]-s2.val[0])*(s1.val[0]-s2.val[0])+(s1.val[1]-s2.val[1])*(s1.val[1]-s2.val[1])+(s1.val[2]-s2.val[2])*(s1.val[2]-s2.val[2]))*weight;
						}
						weight+=0.01;
					}
					if(minPos==-1){
								minPos=j;mindistance=distance;
					}
					else{
						if(distance<mindistance){
							minPos=j;mindistance=distance;
						}
					}
				}
				//从样本中拷贝j+iWindowSize列到合成的i列
				for(int k=0;k<iThreadWidth;k++){
					CvScalar s;
					s=cvGet2D(imgSample,k,minPos+iWindowSize);
					cvSet2D(imgSynthesis,k,i,s);
				}
			}
			//复制图像作为返回值
			copySubImage(imgSynthesis,imgTempReturn,cvRect(0,0,iLength,iThreadWidth));
		}
	}
	else{
		return NULL;
	}
	//根据imgTempReturn构造imgReturn
        //对绣线末端的亮度进行调整
        int endLength=5*iThreadWidth;//末端长度定义
        if(5*endLength>=iLength)
                endLength = iLength/2;
        double endRate = 0.25/endLength;//每次递减的亮度百分比
		//double endRate = 0/endLength;//每次递减的亮度百分比
        double startRate = 0.7;
        for(int i=0;i<endLength;i++)
        {
                for(int j=0;j<iThreadWidth;j++){
                        CvScalar s=cvGet2D(imgTempReturn,j,i);
                        CvScalar s1=cvScalar(s.val[0]*startRate);
                        cvSet2D(imgTempReturn,j,i,s1);

                        CvScalar se=cvGet2D(imgTempReturn,j,iLength-i-1);
                        CvScalar se1=cvScalar(se.val[0]*startRate);
                        cvSet2D(imgTempReturn,j,iLength-i-1,se1);
                }
                startRate+=endRate;
        }

	/*
	RGB -> YUV:

	Y = 0.30 R + 0.59 G + 0.11 B
	U = 0.62 R - 0.52 G - 0.10 B + 128
	V = -0.15 R - 0.29 G +0.44 B + 128

	YUV - > RGB:

	R = Y + 1.370 (U - 128)
	G = Y - 0.698 (U - 128) - 0.336 (V - 128)
	B = Y + 1.730 (V - 128)
	*/
	int threadR=GetRValue(color);
	int threadG=GetGValue(color);
	int threadB=GetBValue(color);
	double threadY=0.30*threadR+0.59*threadG+0.11*threadB;//绣线颜色的亮度作为平均亮度看待
	double threadU=0.62*threadR-0.52*threadG-0.10*threadB+128;
	double threadV=-0.15*threadR-0.29*threadG+0.44*threadB+128;

        if(threadY<0.1)threadY=10;//如果绣线本身亮度太小提升一下

	for(int i=0;i<iThreadWidth;i++)
		for(int j=0;j<iLength;j++){
			CvScalar s = cvGet2D(imgTempReturn,i,j);
			double pY = s.val[0]*threadY;
			double pU=threadU;
			double pV=threadV;
			int pR = (int)(pY+1.370*(pU-128));
			int pG = (int)(pY-0.698*(pU-128)-0.336*(pV-128));
			int pB = (int)(pY+1.730*(pV-128));
			CvScalar s1 = cvScalar(pB,pG,pR);
			cvSet2D(imgReturn,i,j,s1);
		}
        cvReleaseImage(&imgTempReturn);
	return imgReturn;
}

// 装入样图
void CTextureSynthesis::loadSample(const char * filename)
{
	srand((unsigned int)time(NULL));
	IplImage * imgTempSample = cvLoadImage(filename,1);//装入样本

	//取中间像素宽度为2的绣线,被强行指定使用2像素宽的图片
	IplImage* imgTempSample1 = cvCreateImage(cvSize(imgTempSample->width,2),imgTempSample->depth,imgTempSample->nChannels);
	for(int i=0;i<imgTempSample->width;i++)
	{
		CvScalar col=cvGet2D(imgTempSample,3,i);
		cvSet2D(imgTempSample1,0,i,col);
		col=cvGet2D(imgTempSample,4,i);
		cvSet2D(imgTempSample1,1,i,col);
	}
	cvReleaseImage(&imgTempSample);
	imgTempSample=imgTempSample1;
	imgTempSample1=NULL;

	if(imgTempSample!=NULL){
		iThreadWidth = imgTempSample->height;
		iSampleLength = imgTempSample->width;
		if(imgSample!=NULL)
			cvReleaseImage(&imgSample);
		imgSample = cvCreateImage(cvSize(iSampleLength,iThreadWidth),IPL_DEPTH_32F,1);

		//提取样本每个点的亮度
		double maxY=0;
                double totalY=0;
		for(int i=0;i<iThreadWidth;i++){
			for(int j=0;j<iSampleLength;j++){
				CvScalar s= cvGet2D(imgTempSample,i,j);
				int R = (int)(s.val[2]);
				int B = (int)(s.val[0]);
				int G = (int)(s.val[1]);
				double Y = 0.30* R + 0.59* G + 0.11* B;
                                totalY+=Y;
				if(Y>maxY)
					maxY=Y;
				CvScalar s1=cvScalar(Y);
				cvSet2D(imgSample,i,j,s1);
			}
		}
		cvReleaseImage(&imgTempSample);

		//计算每点亮度与平均亮度的比值
                double avgY = totalY/iThreadWidth/iSampleLength;
		if(avgY>0){
			for(int i=0;i<iThreadWidth;i++){
				for(int j=0;j<iSampleLength;j++){
					CvScalar s = cvGet2D(imgSample,i,j);
					CvScalar s1 = cvScalar(s.val[0]/avgY);
					cvSet2D(imgSample,i,j,s1);
				}
			}
		}
		if(imgSynthesis!=NULL){
			cvReleaseImage(&imgSynthesis);
		}

		imgSynthesis = cvCreateImage(cvSize(iWindowSize,iThreadWidth),IPL_DEPTH_32F,1);
		copySubImage(imgSample,imgSynthesis,cvRect(rand()%(iSampleLength-iWindowSize),0,iWindowSize,iThreadWidth));

	}
}

