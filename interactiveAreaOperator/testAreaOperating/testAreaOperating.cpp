#include <iostream>
#include <vector>
#include <fstream>
using namespace std;
#include "cv.h"
#include "highgui.h"

#include "ImageRegionUndoStack.h"
#include "ImageRegionOperator.h"

IplImage *srcImage;
IplImage *displayImage;
bool isDrawingLines=false;
CvPoint lastCvPoint;

vector<CvPoint> pointSequence;

ImageRegionOperator *myRegionOperator;

ImageRegionUndoStack *undoStack;

void PutPointInScale(int &xx,int &yy)
{
	if(xx<0||xx>32767)
	{
		xx=0;
	}
	if(xx>=(displayImage->width))
	{
		xx=displayImage->width-1;
	}
	if(yy<0||yy>32767)
	{
		yy=0;
	}
	if(yy>=(displayImage->height))
	{
		yy=displayImage->height-1;
	}
}

void drawPoint(IplImage *img,CvPoint &thePoint,CvScalar &theColor)
{
	if(img==NULL)
	{
		return;
	}
	if(thePoint.x<0||thePoint.x>=img->width)
	{
		return;
	}
	if(thePoint.y<0||thePoint.y>=img->height)
	{
		return;
	}
	cvSet2D(img,thePoint.y,thePoint.x,theColor);
}

void myMouseCallback_Merge(int event,int x,int y,int flags,void *param)
{
	CvScalar blueColor=cvScalar(255,0,0);//所标记线条的颜色
	int thinkness=1;//所标记线条的宽度
	
	switch(event)
	{
	case CV_EVENT_LBUTTONDOWN:
		{
			PutPointInScale(x,y);
			
			lastCvPoint.x=x;
			lastCvPoint.y=y;
			drawPoint(displayImage,lastCvPoint,blueColor);
			isDrawingLines=true;
			pointSequence.push_back(cvPoint(y,x));
		}
		break;
	case CV_EVENT_MOUSEMOVE:
		{
			PutPointInScale(x,y);

			if(isDrawingLines)
			{
				cvLine(displayImage,lastCvPoint,cvPoint(x,y),blueColor,thinkness);
				lastCvPoint.x=x;
				lastCvPoint.y=y;
				pointSequence.push_back(cvPoint(y,x));
			}
		}
		break;
	case CV_EVENT_LBUTTONUP:
		{
			PutPointInScale(x,y);

			isDrawingLines=false;
			drawPoint(displayImage,cvPoint(x,y),blueColor);
			pointSequence.push_back(cvPoint(y,x));

			myRegionOperator->BresenhamDrawLine(pointSequence);
			myRegionOperator->RegionMerge(pointSequence);
			pointSequence.clear();
			if(displayImage!=NULL)
			{
				cvReleaseImage(&displayImage);
			}
			displayImage=cvCloneImage(myRegionOperator->GetDisplayImage());
			
			vector< vector<int> > areaMat;
			myRegionOperator->GetAreaMatrix(areaMat);
			SegmentationData *currentState=new SegmentationData(areaMat,displayImage);
			undoStack->pushState(currentState);
		}
		break;
	}
	cvShowImage("Interactive",displayImage);
}

void myMouseCallback_Split(int event,int x,int y,int flags,void *param)
{
	CvScalar blueColor=cvScalar(255,0,0);//所标记线条的颜色
	int thinkness=1;//所标记线条的宽度
	
	switch(event)
	{
	case CV_EVENT_LBUTTONDOWN:
		{
			PutPointInScale(x,y);
			
			lastCvPoint.x=x;
			lastCvPoint.y=y;
			drawPoint(displayImage,lastCvPoint,blueColor);
			isDrawingLines=true;
			pointSequence.push_back(cvPoint(y,x));
		}
		break;
	case CV_EVENT_MOUSEMOVE:
		{
			PutPointInScale(x,y);
			
			if(isDrawingLines)
			{
				cvLine(displayImage,lastCvPoint,cvPoint(x,y),blueColor,thinkness);
				lastCvPoint.x=x;
				lastCvPoint.y=y;
				pointSequence.push_back(cvPoint(y,x));
			}
		}
		break;
	case CV_EVENT_LBUTTONUP:
		{			
			PutPointInScale(x,y);
			
			isDrawingLines=false;
			drawPoint(displayImage,cvPoint(x,y),blueColor);
			pointSequence.push_back(cvPoint(y,x));
			
			myRegionOperator->BresenhamDrawLine(pointSequence);
			myRegionOperator->RegionSplit(pointSequence);
			pointSequence.clear();
			if(displayImage!=NULL)
			{
				cvReleaseImage(&displayImage);
			}
			displayImage=cvCloneImage(myRegionOperator->GetDisplayImage());

			vector< vector<int> > areaMat;
			myRegionOperator->GetAreaMatrix(areaMat);
			SegmentationData *currentState=new SegmentationData(areaMat,displayImage);
			undoStack->pushState(currentState);
		}
		break;
	}
	cvShowImage("Interactive",displayImage);
}

void myMouseCallback_Circle(int event,int x,int y,int flags,void *param)
{
	CvScalar blueColor=cvScalar(255,0,0);//所标记线条的颜色
	int thinkness=1;//所标记线条的宽度
	
	switch(event)
	{
	case CV_EVENT_LBUTTONDOWN:
		{
			PutPointInScale(x,y);
			
			lastCvPoint.x=x;
			lastCvPoint.y=y;
			drawPoint(displayImage,lastCvPoint,blueColor);
			isDrawingLines=true;
			pointSequence.push_back(cvPoint(y,x));
		}
		break;
	case CV_EVENT_MOUSEMOVE:
		{
			PutPointInScale(x,y);
			
			if(isDrawingLines)
			{
				cvLine(displayImage,lastCvPoint,cvPoint(x,y),blueColor,thinkness);
				lastCvPoint.x=x;
				lastCvPoint.y=y;
				pointSequence.push_back(cvPoint(y,x));
			}
		}
		break;
	case CV_EVENT_LBUTTONUP:
		{
			PutPointInScale(x,y);
			
			isDrawingLines=false;
			drawPoint(displayImage,cvPoint(x,y),blueColor);
			pointSequence.push_back(cvPoint(y,x));
			
			myRegionOperator->BresenhamDrawLine(pointSequence);
			myRegionOperator->RegionCircle(pointSequence);
			pointSequence.clear();
			if(displayImage!=NULL)
			{
				cvReleaseImage(&displayImage);
			}
			displayImage=cvCloneImage(myRegionOperator->GetDisplayImage());
			
			vector< vector<int> > areaMat;
			myRegionOperator->GetAreaMatrix(areaMat);
			SegmentationData *currentState=new SegmentationData(areaMat,displayImage);
			undoStack->pushState(currentState);
		}
		break;
	}
	cvShowImage("Interactive",displayImage);
}

void myMouseCallback_ModifyBoundary(int event,int x,int y,int flags,void *param)
{
	CvScalar blueColor=cvScalar(255,0,0);//所标记线条的颜色
	int thinkness=1;//所标记线条的宽度
	
	switch(event)
	{
	case CV_EVENT_LBUTTONDOWN:
		{
			PutPointInScale(x,y);
			
			lastCvPoint.x=x;
			lastCvPoint.y=y;
			drawPoint(displayImage,lastCvPoint,blueColor);
			isDrawingLines=true;
			pointSequence.push_back(cvPoint(y,x));
		}
		break;
	case CV_EVENT_MOUSEMOVE:
		{
			PutPointInScale(x,y);
			
			if(isDrawingLines)
			{
				cvLine(displayImage,lastCvPoint,cvPoint(x,y),blueColor,thinkness);
				lastCvPoint.x=x;
				lastCvPoint.y=y;
				pointSequence.push_back(cvPoint(y,x));
			}
		}
		break;
	case CV_EVENT_LBUTTONUP:
		{
			PutPointInScale(x,y);
			
			isDrawingLines=false;
			drawPoint(displayImage,cvPoint(x,y),blueColor);
			pointSequence.push_back(cvPoint(y,x));
			
			myRegionOperator->BresenhamDrawLine(pointSequence);
			myRegionOperator->RegionModifyBoundary(pointSequence);
			pointSequence.clear();
			if(displayImage!=NULL)
			{
				cvReleaseImage(&displayImage);
			}
			displayImage=cvCloneImage(myRegionOperator->GetDisplayImage());
			
			vector< vector<int> > areaMat;
			myRegionOperator->GetAreaMatrix(areaMat);
			SegmentationData *currentState=new SegmentationData(areaMat,displayImage);
			undoStack->pushState(currentState);
		}
		break;
	}
	cvShowImage("Interactive",displayImage);
}


int main()
{
	IplImage *srcImage=cvLoadImage("124084.jpg");

// 	CvScalar redColor=cvScalar(0,0,255);
// 	CvScalar greenColor=cvScalar(0,255,0);
// 	CvScalar blueColor=cvScalar(255,0,0);

	vector<int> tempVector(srcImage->width,0);
	vector< vector<int> > areaMatrix(srcImage->height,tempVector);

	int i,j;
	ifstream fin("mat.txt");
	for(i=0;i<srcImage->height;i++)
	{
		for(j=0;j<srcImage->width;j++)
		{
			fin>>areaMatrix[i][j];
		}
	}
	fin.close();

	myRegionOperator=new ImageRegionOperator(srcImage,areaMatrix);
	myRegionOperator->CalcAverageColor();
	displayImage=cvCloneImage(myRegionOperator->GetDisplayImage());
	
	cvNamedWindow("Original",CV_WINDOW_AUTOSIZE);
	cvMoveWindow("Original",100,100);
	cvNamedWindow("Interactive",CV_WINDOW_AUTOSIZE);
	cvMoveWindow("Interactive",100+srcImage->width+13,100);
	cvShowImage("Original",srcImage);
	cvShowImage("Interactive",displayImage);

	cout<<"欢迎使用图像区域交互软件。"<<endl;
	cout<<"本软件是乱针绣系统中图像(分割后)区域交互模块的原型软件，提供用户区域交互的功能"<<endl;
	cout<<endl;
	cout<<"使用方法："<<endl
		<<"在出现的交互窗口(Interactive)中，"<<endl
		<<"软件通过区域平均色来标识各个区域"<<endl
		<<"请通过字母按键选择要执行的操作，"<<endl
		<<"再通过在窗口中按下鼠标左键并拖曳鼠标的方式输入交互线条。"<<endl
		<<"交互将立即执行，结果将显示在窗口中。"
		<<endl;
	cout<<endl;
	cout<<"按键'F':区域分割:将所输入交互线条作为区域边界进行区域分割"<<endl;
	cout<<"按键'G':区域合并:将输入交互线条掠过的区域合并"<<endl;
	cout<<"按键'H':圈选区域:当输入交互线条为封闭区域时，将该封闭区域作为新的区域"<<endl;
	cout<<"按键'J':边界修改:当输入交互线条符合\"从A区域到B区域再返回A区域\"条件时，将线条掠过        的B区域部分并入A区域中"<<endl;
	cout<<"按键'Z':撤销上一次操作"<<endl;
	cout<<"按键'Y':重做撤销的上一次操作"<<endl;
	cout<<"按键'E':退出"<<endl;

	SegmentationData *currentState=new SegmentationData(areaMatrix,displayImage);
	undoStack=new ImageRegionUndoStack(currentState);
	currentState=NULL;

	char ch;
	while(1)
	{
		ch=cvWaitKey();
		if(ch=='e'||ch=='E')
		{
			break;
		}
		else if(ch=='f'||ch=='F')
		{
			cvSetMouseCallback("Interactive",myMouseCallback_Split,NULL);
		}
		else if(ch=='g'||ch=='G')
		{
			cvSetMouseCallback("Interactive",myMouseCallback_Merge,NULL);
		}
		else if(ch=='h'||ch=='H')
		{
			cvSetMouseCallback("Interactive",myMouseCallback_Circle,NULL);
		}
		else if(ch=='j'||ch=='J')
		{
			cvSetMouseCallback("Interactive",myMouseCallback_ModifyBoundary,NULL);
		}
		else if(ch=='z'||ch=='Z')
		{
			if(undoStack->Undo())
			{
				SegmentationData *currentState=undoStack->getCurrentPoint();
				myRegionOperator->SetAreaMatrix(currentState->splitMatrix);
				cvReleaseImage(&displayImage);
				displayImage=cvCloneImage(currentState->regionImage);
				cvShowImage("Interactive",displayImage);
				currentState=NULL;
			}
		}
		else if(ch=='y'||ch=='Y')
		{
			if(undoStack->Redo())
			{
				SegmentationData *currentState=undoStack->getCurrentPoint();
				myRegionOperator->SetAreaMatrix(currentState->splitMatrix);
				cvReleaseImage(&displayImage);
				displayImage=cvCloneImage(currentState->regionImage);
				cvShowImage("Interactive",displayImage);
				currentState=NULL;
			}
		}
	}

	myRegionOperator->RearrangeRegionNum();

	cvReleaseImage(&srcImage);
	cvReleaseImage(&displayImage);
	cvDestroyWindow("Original");
	cvDestroyWindow("Interactive");
	delete myRegionOperator;
	myRegionOperator=NULL;
	delete undoStack;
	undoStack=NULL;

	return 0;
}
