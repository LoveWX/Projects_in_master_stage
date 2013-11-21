#include "stdafx.h"
#include "ImageRegionOperator.h"

/*
class ImageRegionOperator
{
public:
	ImageRegionOperator();//构造函数,需要调用SetImageAndMatrix()进行初始化
	ImageRegionOperator(IplImage *theImage,const vector< vector<int> > &theMatrix);//含参构造函数
	~ImageRegionOperator();//析构函数
	void SetImageAndMatrix(IplImage *theImage,const vector< vector<int> > &theMatrix);//将图片和对应的区域矩阵传入类中
	
	IplImage* GetDisplayImage();							//获取显示用的结果图片
	void GetAreaMatrix(vector< vector<int> > &theMatrix);	//获得当前区域矩阵
	//获得最大区域号,如果先调用RearrangeRegionNum()重新排列区域号,则该区域号等于区域数
	int GetNumOfRegions();
	
	//获得区域掩码,选中的区域置1,其它区域置0
	void CalcMasks(int regionNum,vector< vector<int> > &theMasks);					//选择由区域号regionNum指定的区域
	void CalcMasks(const CvPoint &thePoint,vector< vector<int> > &theMasks);		//选择thePoint所在的区域
	void CalcMasks(const vector<CvPoint> &thePoints,vector< vector<int> > &theMasks);//选择thePoints扫过的所有区域
	
	void CalcAverageColor();//按照areaMatrix计算平均色
	
	//调用BresenhamConnectPoints()在pointSequence相邻点间插入点以将pointSequence连成8邻接的线
	void BresenhamDrawLine(vector<CvPoint> &pointSequence);
	
	
	void RegionMerge(const vector<CvPoint> &pointSequence);			//区域合并,合并pointSequence扫过的所有区域
	void RegionSplit(const vector<CvPoint> &pointSequence);			//区域分割,pointSequence作为新的边界进行区域分割
	void RegionCircle(const vector<CvPoint> &pointSequence);		//圈选区域,pointSequence圈中的区域成为新区域
	void RegionModifyBoundary(const vector<CvPoint> &pointSequence);//边界修改
	
	void RearrangeRegionNum();//重新排列区域号,使其为[1,maxRegionNum]
	
protected:
	IplImage *srcImage;//与区域矩阵对应的原始图像
	IplImage *displayImage;//显示用结果图片,每次区域操作后会进行更新
	int height;//图像高度,区域矩阵第一维长度
	int width;//图像宽度,区域矩阵第二维长度
	vector< vector<int> > areaMatrix;//区域矩阵
	int maxRegionNum;//当前最大区域号
	
	//使用Bresenham方法在连接(xa,ya)和(xb,yb),产生的点按序插入points中
	void BresenhamConnectPoints(vector<CvPoint> &points,int xa,int ya,int xb,int yb);
	int GetMaxRegionNum();					//获得当前最大区域号,仅供类内部调用
	bool IsInScale(CvPoint thePoint);		//判断thePoint是否在区域矩阵内
	void PutPointInScale(CvPoint &thePoint);//将thePoint放回区域矩阵内
	
	//专用的调用函数,在某些代码细节上会有差异
	//区域填充,仅供RegionSplit()调用
	void FillingRegion(vector< vector<int> > &theMasks,CvPoint seedPoint,int newRegionNum);
	//获得圈中的区域,仅供RegionCircle()和RegionModifyBoundaryRegionModifyBoundary()调用
	void GetCircleRegionMasks(vector< vector<int> > &theMasks,CvPoint seedPoint);
	//获得填充并计算像素点个数,仅供RegionModifyBoundary()调用
	int FillingRegionCountingPoints(vector< vector<int> > &theMasks,CvPoint seedPoint,int newNum);
	
	//以下为测试用函数,可以删除
public:
	void printImage();
	void testRegion(vector< vector<int> > &theMatrix);
	void testMasks(vector< vector<int> > &masks);
	void printMatrix(vector< vector<int> > &theMatrix);
};
*/

ImageRegionOperator::ImageRegionOperator()
{
	srcImage=NULL;
	displayImage=NULL;
	height=0;
	width=0;
	areaMatrix.clear();
	maxRegionNum=-1;
}

ImageRegionOperator::ImageRegionOperator(const IplImage *theImage,const vector< vector<int> > &theMatrix)
{
	srcImage=cvCloneImage(theImage);
	displayImage=NULL;
	height=srcImage->height;
	width=srcImage->width;
	areaMatrix=theMatrix;
	maxRegionNum=GetMaxRegionNum();
}

ImageRegionOperator::~ImageRegionOperator()
{
	if(srcImage!=NULL)
	{
		cvReleaseImage(&srcImage);
		srcImage=NULL;
	}
	if(displayImage!=NULL)
	{
		cvReleaseImage(&displayImage);
		displayImage=NULL;
	}
	height=0;
	width=0;
	areaMatrix.clear();
	maxRegionNum=-1;
}

void ImageRegionOperator::SetImageAndMatrix(const IplImage *theImage,const vector< vector<int> > &theMatrix)
{
	if(srcImage!=NULL)
	{
		cvReleaseImage(&srcImage);
		srcImage=NULL;
	}
	srcImage=cvCloneImage(theImage);
	if(displayImage!=NULL)
	{
		cvReleaseImage(&displayImage);
		displayImage=NULL;
	}
	height=srcImage->height;
	width=srcImage->width;
	areaMatrix=theMatrix;
	maxRegionNum=GetMaxRegionNum();
}

IplImage* ImageRegionOperator::GetDisplayImage()
{
	return displayImage;
}

int ImageRegionOperator::GetNumOfRegions()
{
	return maxRegionNum;
}

void ImageRegionOperator::GetAreaMatrix(vector< vector<int> > &theMatrix)
{
	theMatrix=areaMatrix;
}

void ImageRegionOperator::SetAreaMatrix(vector< vector<int> > &theMatrix)
{
	areaMatrix=theMatrix;
}

void ImageRegionOperator::CalcMasks(int regionNum,vector< vector<int> > &theMasks)
{
	int i,j;
	vector<int> tempVector(width,0);
	vector< vector<int> > tempMasks(height,tempVector);
	for(i=0;i<height;i++)
	{
		for(j=0;j<width;j++)
		{
			if(areaMatrix[i][j]==regionNum)
			{
				tempMasks[i][j]=1;
			}
		}
	}
	theMasks=tempMasks;
}

void ImageRegionOperator::CalcMasks(const CvPoint &thePoint,vector< vector<int> > &theMasks)
{
	if(!IsInScale(thePoint))
	{
		return;
	}
	CalcMasks(areaMatrix[thePoint.x][thePoint.y],theMasks);
}

void ImageRegionOperator::CalcMasks(const vector<CvPoint> &thePoints,vector< vector<int> > &theMasks)
{
	int i,j;
	vector<int> tempVector(width,0);
	vector< vector<int> > tempMasks(height,tempVector);
	vector<bool> regionSelected(maxRegionNum+1,false);
	for(i=0;i<thePoints.size();i++)
	{
		j=areaMatrix[thePoints[i].x][thePoints[i].y];
		regionSelected[j]=true;
	}
	for(i=0;i<height;i++)
	{
		for(j=0;j<width;j++)
		{
			if(regionSelected[areaMatrix[i][j]])
			{
				tempMasks[i][j]=1;
			}
		}
	}
	theMasks=tempMasks;
}

void ImageRegionOperator::CalcAverageColor()
{
	if(displayImage==NULL)
	{
		displayImage=cvCloneImage(srcImage);
	}
	else if(displayImage->height!=height||displayImage->width!=width)
	{
		cvReleaseImage(&displayImage);
		displayImage=cvCloneImage(srcImage);
	}
	
	int i,j;
	int currentRegionNum;
	vector<int> tempVector(maxRegionNum+1,0);
	vector<int> numOfRegionPoints=tempVector;
	vector<int> averageBlue=tempVector;
	vector<int> averageGreen=tempVector;
	vector<int> averageRed=tempVector;
	CvScalar tempColor=cvScalar(0,0,0);
	vector<CvScalar> tempColorVector(maxRegionNum+1,tempColor);
	for(i=0;i<height;i++)
	{
		for(j=0;j<width;j++)
		{
			currentRegionNum=areaMatrix[i][j];
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
			currentRegionNum=areaMatrix[i][j];
			cvSet2D(displayImage,i,j,tempColorVector[currentRegionNum]);
		}
	}
}

void ImageRegionOperator::BresenhamDrawLine(vector<CvPoint> &pointSequence)
{
	if(pointSequence.size()<=1)
	{
		return;
	}
// 	vector<CvPoint> points=pointSequence;
// 	pointSequence.clear();
// 	int i,lastx=points[0].x,lasty=points[0].y;
// 	pointSequence.push_back(points[0]);
// 	for(i=1;i<points.size();i++)
// 	{
// 		BresenhamConnectPoints(pointSequence,lastx,lasty,points[i].x,points[i].y);
// 		pointSequence.push_back(points[i]);
// 		lastx=points[i].x;
// 		lasty=points[i].y;
// 	}
	vector<CvPoint> points;
	int i,lastx=pointSequence[0].x,lasty=pointSequence[0].y;
	for(i=1;i<pointSequence.size();i++)
	{
		points.push_back(pointSequence[i-1]);
		BresenhamConnectPoints(points,lastx,lasty,pointSequence[i].x,pointSequence[i].y);
		points.push_back(pointSequence[i]);
		lastx=pointSequence[i].x;
		lasty=pointSequence[i].y;
	}
	pointSequence.clear();
	pointSequence.push_back(points[0]);
	for(i=1;i<points.size();i++)
	{
 		//PutPointInScale(points[i]);//如果保证传入点坐标不会越界则不用本语句
		if(points[i].x==points[i-1].x&&points[i].y==points[i-1].y)
		{
			continue;
		}
		pointSequence.push_back(points[i]);
	}
}

void ImageRegionOperator::BresenhamConnectPoints(vector<CvPoint> &points,int xa,int ya,int xb,int yb)
{
	int tx=1,ty=1,dx=xb-xa,dy=yb-ya,inc1,inc2,d,itag=0;
	if(dx<0)
	{
		tx=-1;
		dx=-dx;
	}
	if(dy<0)
	{
		ty=-1;
		dy=-dy;
	}
	if(dx<dy)
	{
		itag=1;
		inc1=xa;
		xa=ya;
		ya=inc1;
		inc1=xb;
		xb=yb;
		yb=inc1;
		inc1=dx;
		dx=dy;
		dy=inc1;
		inc1=tx;
		tx=ty;
		ty=inc1;
	}
	inc1=dy+dy;
	d=inc1-dx;
	inc2=d-dx;
	while(xa!=xb)
	{
		if(d<0)
			d+=inc1;
		else
		{
			ya+=ty;
			d+=inc2;	
		}
		if(itag==1)
		{
			points.push_back(cvPoint(ya,xa));
		}
		else
		{
			points.push_back(cvPoint(xa,ya));
		}
		xa+=tx;
	}
}

void ImageRegionOperator::RegionMerge(const vector<CvPoint> &pointSequence)
{
	if(pointSequence.size()<=1)
	{
		return;
	}

	int i,j;
	int targetRegion=areaMatrix[pointSequence[0].x][pointSequence[0].y];
	vector<bool> regionNeedToChange(maxRegionNum+1,false);
	for(i=1;i<pointSequence.size();i++)
	{
		j=areaMatrix[pointSequence[i].x][pointSequence[i].y];
		regionNeedToChange[j]=true;
	}
	regionNeedToChange[targetRegion]=false;

	j=0;
	for(i=0;i<regionNeedToChange.size();i++)
	{
		if(regionNeedToChange[i])
		{
			j=1;
			break;
		}
	}
	if(j==0)
	{
		return;
	}

	for(i=0;i<height;i++)
	{
		for(j=0;j<width;j++)
		{
			if(regionNeedToChange[areaMatrix[i][j]])
			{
				areaMatrix[i][j]=targetRegion;
			}
		}
	}
	CalcAverageColor();
}

void ImageRegionOperator::FillingRegion(vector< vector<int> > &theMasks,CvPoint seedPoint,int newRegionNum)
{
	if(seedPoint.x<0||seedPoint.x>=height
		||seedPoint.y<0||seedPoint.y>=width
		||theMasks[seedPoint.x][seedPoint.y]!=1||newRegionNum<=0)
	{
		return;
	}

	/*theMasks中各种值代表的意义
	// 0 :不需要处理的点
	// 1 :需要处理但还未处理的点
	// 2 :新区域的编号
	// 3 :分割线上的点
	// 4 :已经在标记队列中的点
	*/

	int i,j,xx,yy;
	int originalRegionNum=areaMatrix[seedPoint.x][seedPoint.y];
	queue<CvPoint> queueOfPointToFill;
	CvPoint currentPoint,tempPoint;
	queueOfPointToFill.push(seedPoint);
	while(!queueOfPointToFill.empty())
	{
		currentPoint=queueOfPointToFill.front();
		queueOfPointToFill.pop();
		xx=currentPoint.x;
		yy=currentPoint.y;

		if(theMasks[xx][yy]!=1&&theMasks[xx][yy]!=4)
		{
			continue;
		}
		
		//处理当前点
		areaMatrix[xx][yy]=newRegionNum;
		theMasks[xx][yy]=2;//标示该点已经标记
		
		//将当前点上方的点加入队列,直到已经处理过的点或者已经加入队列中的点为止
		tempPoint.x=xx;
		tempPoint.y=yy;
		for(i=xx-1;i>=0;i--)
		{
			if(theMasks[i][yy]==3&&areaMatrix[i][yy]==originalRegionNum)
			{
				areaMatrix[i][yy]=newRegionNum;
				break;
			}
			if(theMasks[i][yy]!=1||areaMatrix[i][yy]!=originalRegionNum)
			{
				break;
			}
			tempPoint.x=i;
			queueOfPointToFill.push(tempPoint);
			theMasks[i][yy]=4;//标示为该点已经在处理队列中
		}
		
		//将当前点左边的点加入队列,直到已经处理过的点或者已经加入队列中的点为止
		tempPoint.x=xx;
		tempPoint.y=yy;
		for(j=yy-1;j>=0;j--)
		{
			if(theMasks[xx][j]==3&&areaMatrix[xx][j]==originalRegionNum)
			{
				areaMatrix[xx][j]=newRegionNum;
				break;
			}
			if(theMasks[xx][j]!=1||areaMatrix[xx][j]!=originalRegionNum)
			{
				break;
			}
			tempPoint.y=j;
			queueOfPointToFill.push(tempPoint);
			theMasks[xx][j]=4;//标示为该点已经在处理队列中
		}
		
		//将当前点下方的点加入队列,直到已经处理过的点或者已经加入队列中的点为止
		tempPoint.x=xx;
		tempPoint.y=yy;
		for(i=xx+1;i<height;i++)
		{
			if(theMasks[i][yy]==3&&areaMatrix[i][yy]==originalRegionNum)
			{
				areaMatrix[i][yy]=newRegionNum;
				break;
			}
			if(theMasks[i][yy]!=1||areaMatrix[i][yy]!=originalRegionNum)
			{
				break;
			}
			tempPoint.x=i;
			queueOfPointToFill.push(tempPoint);
			theMasks[i][yy]=4;//标示为该点已经在处理队列中
		}
		
		//将当前点右边的点加入队列,直到已经处理过的点或者已经加入队列中的点为止
		tempPoint.x=xx;
		tempPoint.y=yy;
		for(j=yy+1;j<width;j++)
		{
			if(theMasks[xx][j]==3&&areaMatrix[xx][j]==originalRegionNum)
			{
				areaMatrix[xx][j]=newRegionNum;
				break;
			}
			if(theMasks[xx][j]!=1||areaMatrix[xx][j]!=originalRegionNum)
			{
				break;
			}
			tempPoint.y=j;
			queueOfPointToFill.push(tempPoint);
			theMasks[xx][j]=4;//标示为该点已经在处理队列中
		}
	}
}

void ImageRegionOperator::RegionSplit(const vector<CvPoint> &pointSequence)
{
	if(pointSequence.size()==0)
	{
		return;
	}

	/*theMasks中各种值代表的意义
	// 0 :不需要处理的点
	// 1 :需要处理但还未处理的点
	// 2 :新区域的编号
	// 3 :分割线上的点
	// 4 :已经在标记队列中的点
	*/
	
	int i,xx,yy;
	vector<int> tempVector(width,0);
	vector< vector<int> > theMasks(height,tempVector);
	CalcMasks(pointSequence,theMasks);

	for(i=0;i<pointSequence.size();i++)
	{
		xx=pointSequence[i].x;
		yy=pointSequence[i].y;
		theMasks[xx][yy]=3;
	}

	int tempRegionNum;
	CvPoint tempPoint;
	for(i=0;i<pointSequence.size();i++)
	{
		tempPoint=pointSequence[i];
		tempRegionNum=areaMatrix[tempPoint.x][tempPoint.y];

		//检测该点上方的点是否可以作为种子点
		xx=tempPoint.x-1;
		yy=tempPoint.y;
		if(xx>=0&&theMasks[xx][yy]==1
			&&areaMatrix[tempPoint.x][tempPoint.y]==tempRegionNum)
		{
			FillingRegion(theMasks,cvPoint(xx,yy),++maxRegionNum);
		}
		//检测该点左边的点是否可以作为种子点
		xx=tempPoint.x;
		yy=tempPoint.y-1;
		if(yy>=0&&theMasks[xx][yy]==1
			&&areaMatrix[tempPoint.x][tempPoint.y]==tempRegionNum)
		{
			FillingRegion(theMasks,cvPoint(xx,yy),++maxRegionNum);
		}
		//检测该点下方的点是否可以作为种子点
		xx=tempPoint.x+1;
		yy=tempPoint.y;
		if(xx<height&&theMasks[xx][yy]==1
			&&areaMatrix[tempPoint.x][tempPoint.y]==tempRegionNum)
		{
			FillingRegion(theMasks,cvPoint(xx,yy),++maxRegionNum);
		}
		//检测该点右方的点是否可以作为种子点
		xx=tempPoint.x;
		yy=tempPoint.y+1;
		if(yy<width&&theMasks[xx][yy]==1
			&&areaMatrix[tempPoint.x][tempPoint.y]==tempRegionNum)
		{
			FillingRegion(theMasks,cvPoint(xx,yy),++maxRegionNum);
		}
	}

	/*
	//下一段代码处理与选中区域8连通但不4连通的像素点
	int j;
	for(i=0;i<height;i++)
	{
		for(j=0;j<width;j++)
		{
			if(theMasks[i][j]==1)
			{
				//若遇到未处理的点,检测其{8邻域-4邻域}中有无已经处理的点
				
				//检测该点左上的点是否已被处理过
				xx=i-1;
				yy=j-1;
				if(xx>=0&&yy>=0&&theMasks[xx][yy]==2)
				{
					FillingRegion(theMasks,cvPoint(xx,yy),areaMatrix[xx][yy]);
				}
				//检测该点右上的点是否已被处理过
				xx=i-1;
				yy=j+1;
				if(xx>=0&&yy<width&&theMasks[xx][yy]==2)
				{
					FillingRegion(theMasks,cvPoint(xx,yy),areaMatrix[xx][yy]);
				}
				//检测该点左下的点是否已被处理过
				xx=i+1;
				yy=j-1;
				if(xx<height&&yy>=0&&theMasks[xx][yy]==2)
				{
					FillingRegion(theMasks,cvPoint(xx,yy),areaMatrix[xx][yy]);
				}
				//检测该点右下的点是否已被处理过
				xx=i+1;
				yy=j+1;
				if(xx<height&&yy<width&&theMasks[xx][yy]==2)
				{
					FillingRegion(theMasks,cvPoint(xx,yy),areaMatrix[xx][yy]);
				}
			}
		}
	}
*/
	CalcAverageColor();
}

void ImageRegionOperator::GetCircleRegionMasks(vector< vector<int> > &theMasks,CvPoint seedPoint)
{
	int row=theMasks.size();
	int col=theMasks[0].size();
	if(seedPoint.x<0||seedPoint.x>=row
		||seedPoint.y<0||seedPoint.y>=col)
	{
		return;
	}
	
	/*theMasks中各种值代表的意义(需要处理整个矩阵)
	// 0 :需要处理但还未处理的点
	// 1 :处理完成时新区域的点
	// 2 :
	// 3 :分割线上的点
	// 4 :已经在标记队列中的点
	*/

	int i,j,xx,yy;
	queue<CvPoint> queueOfPointToFill;
	CvPoint currentPoint,tempPoint;
	queueOfPointToFill.push(seedPoint);
	while(!queueOfPointToFill.empty())
	{
		currentPoint=queueOfPointToFill.front();
		queueOfPointToFill.pop();
		xx=currentPoint.x;
		yy=currentPoint.y;
		
		if(theMasks[xx][yy]!=0&&theMasks[xx][yy]!=4)
		{
			continue;
		}
		
		//处理当前点
		theMasks[xx][yy]=1;//标示该点已经标记
		
		//将当前点上方的点加入队列,直到已经处理过的点或者已经加入队列中的点为止
		tempPoint.x=xx;
		tempPoint.y=yy;
		for(i=xx-1;i>=0;i--)
		{
			if(theMasks[i][yy]!=0)
			{
				break;
			}
			tempPoint.x=i;
			queueOfPointToFill.push(tempPoint);
			theMasks[i][yy]=4;//标示为该点已经在处理队列中
		}
		
		//将当前点左边的点加入队列,直到已经处理过的点或者已经加入队列中的点为止
		tempPoint.x=xx;
		tempPoint.y=yy;
		for(j=yy-1;j>=0;j--)
		{
			if(theMasks[xx][j]!=0)
			{
				break;
			}
			tempPoint.y=j;
			queueOfPointToFill.push(tempPoint);
			theMasks[xx][j]=4;//标示为该点已经在处理队列中
		}
		
		//将当前点下方的点加入队列,直到已经处理过的点或者已经加入队列中的点为止
		tempPoint.x=xx;
		tempPoint.y=yy;
		for(i=xx+1;i<row;i++)
		{
			if(theMasks[i][yy]!=0)
			{
				break;
			}
			tempPoint.x=i;
			queueOfPointToFill.push(tempPoint);
			theMasks[i][yy]=4;//标示为该点已经在处理队列中
		}
		
		//将当前点右边的点加入队列,直到已经处理过的点或者已经加入队列中的点为止
		tempPoint.x=xx;
		tempPoint.y=yy;
		for(j=yy+1;j<col;j++)
		{
			if(theMasks[xx][j]!=0)
			{
				break;
			}
			tempPoint.y=j;
			queueOfPointToFill.push(tempPoint);
			theMasks[xx][j]=4;//标示为该点已经在处理队列中
		}
	}
}

void ImageRegionOperator::RegionCircle(const vector<CvPoint> &pointSequence)
{
	if(pointSequence.size()<=1)
	{
		return;
	}

	vector<int> tempVector(width+2,0);
	vector< vector<int> > tempMasks(height+2,tempVector);
	int row=height+2,col=width+2;
	
	int i,j,xx,yy;
	for(i=0;i<pointSequence.size();i++)
	{
		xx=pointSequence[i].x;
		yy=pointSequence[i].y;
		tempMasks[xx+1][yy+1]=3;
	}
	GetCircleRegionMasks(tempMasks,cvPoint(0,0));
	for(i=0;i<pointSequence.size();i++)
	{
		xx=pointSequence[i].x;
		yy=pointSequence[i].y;
		tempMasks[xx+1][yy+1]=1;
	}

	maxRegionNum++;
	for(i=0;i<height;i++)
	{
		for(j=0;j<width;j++)
		{
			if(tempMasks[i+1][j+1]==0)
			{
				areaMatrix[i][j]=maxRegionNum;
			}
		}
	}
	CalcAverageColor();
}

int ImageRegionOperator::CountingRegionPoints(const vector<CvPoint> &pointsequence)
{
	vector<int> tempVector(width,0);
	vector< vector<int> > theMasks(height,tempVector);
	CalcMasks(pointsequence,theMasks);

	/*theMasks中各种值代表的意义
	// 0 :不需要统计的点
	// 1 :需要统计但还没有统计的点
	// 2 :已经统计过的点
	// 3 :分割线上的点
	// 4 :已经在标记队列中的点
	*/

	int i,j,xx,yy,numOfPoints=0;
	queue<CvPoint> queueOfPointToFill;
	CvPoint currentPoint,tempPoint;
	for(i=0;i<pointsequence.size();i++)
	{
		xx=pointsequence[i].x;
		yy=pointsequence[i].y;
		queueOfPointToFill.push(pointsequence[i]);
		theMasks[xx][yy]=4;
	}
	while(!queueOfPointToFill.empty())
	{
		currentPoint=queueOfPointToFill.front();
		queueOfPointToFill.pop();
		xx=currentPoint.x;
		yy=currentPoint.y;
		
		if(theMasks[xx][yy]!=1&&theMasks[xx][yy]!=4)
		{
			continue;
		}
		
		//处理当前点
		numOfPoints++;
		theMasks[xx][yy]=2;//该点标记为已经统计过

		//将当前点上方的点加入队列,直到已经处理过的点或者已经加入队列中的点为止
		tempPoint.x=xx;
		tempPoint.y=yy;
		for(i=xx-1;i>=0;i--)
		{
			if(theMasks[i][yy]!=1)
			{
				break;
			}
			tempPoint.x=i;
			queueOfPointToFill.push(tempPoint);
			theMasks[i][yy]=4;//标示为该点已经在处理队列中
		}
		
		//将当前点左边的点加入队列,直到已经处理过的点或者已经加入队列中的点为止
		tempPoint.x=xx;
		tempPoint.y=yy;
		for(j=yy-1;j>=0;j--)
		{
			if(theMasks[xx][j]!=1)
			{
				break;
			}
			tempPoint.y=j;
			queueOfPointToFill.push(tempPoint);
			theMasks[xx][j]=4;//标示为该点已经在处理队列中
		}
		
		//将当前点下方的点加入队列,直到已经处理过的点或者已经加入队列中的点为止
		tempPoint.x=xx;
		tempPoint.y=yy;
		for(i=xx+1;i<height;i++)
		{
			if(theMasks[i][yy]!=1)
			{
				break;
			}
			tempPoint.x=i;
			queueOfPointToFill.push(tempPoint);
			theMasks[i][yy]=4;//标示为该点已经在处理队列中
		}
		
		//将当前点右边的点加入队列,直到已经处理过的点或者已经加入队列中的点为止
		tempPoint.x=xx;
		tempPoint.y=yy;
		for(j=yy+1;j<width;j++)
		{
			if(theMasks[xx][j]!=1)
			{
				break;
			}
			tempPoint.y=j;
			queueOfPointToFill.push(tempPoint);
			theMasks[xx][j]=4;//标示为该点已经在处理队列中
		}
	}
	return numOfPoints;
}

int ImageRegionOperator::FillingRegionCountingPoints(vector< vector<int> > &theMasks,CvPoint seedPoint,int newNum)
{
	int row=theMasks.size();
	int col=theMasks[0].size();
	if(seedPoint.x<0||seedPoint.x>=row
		||seedPoint.y<0||seedPoint.y>=col)
	{
		return 0;
	}
	
	/*theMasks中各种值代表的意义(需要处理整个矩阵)
	// 0 :需要处理但还未处理的点
	// 1 :处理完成时新区域的点
	// 2 :
	// 3 :分割线上的点
	// 4 :已经在标记队列中的点
	// >5:newNum指定的区域编号
	*/

	int i,j,xx,yy,numOfPoints=0;
	queue<CvPoint> queueOfPointToFill;
	CvPoint currentPoint,tempPoint;
	queueOfPointToFill.push(seedPoint);
	while(!queueOfPointToFill.empty())
	{
		currentPoint=queueOfPointToFill.front();
		queueOfPointToFill.pop();
		xx=currentPoint.x;
		yy=currentPoint.y;
		
		if(theMasks[xx][yy]!=0&&theMasks[xx][yy]!=4)
		{
			continue;
		}
		
		//处理当前点
		numOfPoints++;
		theMasks[xx][yy]=newNum;//该点标记为newNum指定的区域号
		
		//将当前点上方的点加入队列,直到已经处理过的点或者已经加入队列中的点为止
		tempPoint.x=xx;
		tempPoint.y=yy;
		for(i=xx-1;i>=0;i--)
		{
			if(theMasks[i][yy]!=0)
			{
				break;
			}
			tempPoint.x=i;
			queueOfPointToFill.push(tempPoint);
			theMasks[i][yy]=4;//标示为该点已经在处理队列中
		}
		
		//将当前点左边的点加入队列,直到已经处理过的点或者已经加入队列中的点为止
		tempPoint.x=xx;
		tempPoint.y=yy;
		for(j=yy-1;j>=0;j--)
		{
			if(theMasks[xx][j]!=0)
			{
				break;
			}
			tempPoint.y=j;
			queueOfPointToFill.push(tempPoint);
			theMasks[xx][j]=4;//标示为该点已经在处理队列中
		}
		
		//将当前点下方的点加入队列,直到已经处理过的点或者已经加入队列中的点为止
		tempPoint.x=xx;
		tempPoint.y=yy;
		for(i=xx+1;i<row;i++)
		{
			if(theMasks[i][yy]!=0)
			{
				break;
			}
			tempPoint.x=i;
			queueOfPointToFill.push(tempPoint);
			theMasks[i][yy]=4;//标示为该点已经在处理队列中
		}
		
		//将当前点右边的点加入队列,直到已经处理过的点或者已经加入队列中的点为止
		tempPoint.x=xx;
		tempPoint.y=yy;
		for(j=yy+1;j<col;j++)
		{
			if(theMasks[xx][j]!=0)
			{
				break;
			}
			tempPoint.y=j;
			queueOfPointToFill.push(tempPoint);
			theMasks[xx][j]=4;//标示为该点已经在处理队列中
		}
	}
	return numOfPoints;
}

void ImageRegionOperator::RegionModifyBoundary(const vector<CvPoint> &pointSequence)
{
	if(pointSequence.size()<=1)
	{
		return;
	}
	int i,j,xx,yy;
	vector<CvPoint> thePoints;
	int firstRegionNum=areaMatrix[pointSequence[0].x][pointSequence[0].y];
	for(i=1;i<pointSequence.size();i++)
	{
		xx=pointSequence[i].x;
		yy=pointSequence[i].y;
		if(areaMatrix[xx][yy]!=firstRegionNum)
		{
			j=i;
			break;
		}
	}
	if(i>=pointSequence.size())
	{
		return;
	}

	for(i=j;i<pointSequence.size();i++)
	{
		xx=pointSequence[i].x;
		yy=pointSequence[i].y;
		if(areaMatrix[xx][yy]!=firstRegionNum)
		{
			thePoints.push_back(cvPoint(xx,yy));
		}
		else
		{
			break;
		}
	}
	if(i>=pointSequence.size())
	{
		return;
	}
	//统计所扫过的四连通区域的总像素个数
	int numOfPointsToModify=CountingRegionPoints(thePoints);

	int row=height+2,col=width+2;
	vector<int> tempVector(width,0);
	vector< vector<int> > tempMasks1(height,tempVector);//第一区域掩码
	vector< vector<int> > tempMasks3(height,tempVector);//第二区域掩码
	tempVector.push_back(0);
	tempVector.push_back(0);
	vector< vector<int> > tempMasks2(row,tempVector);

	CalcMasks(thePoints,tempMasks3);
	CalcMasks(firstRegionNum,tempMasks1);
	for(i=0;i<height;i++)
	{
		for(j=0;j<width;j++)
		{
			if(tempMasks1[i][j]==1)
			{
				tempMasks2[i+1][j+1]=3;
			}
			if(tempMasks3[i][j]!=1)
			{
				//没有扫过这些点,但是也无法处理包括但未扫过一整块区域的情况
				tempMasks2[i+1][j+1]=2;
			}
		}
	}
	for(i=0;i<thePoints.size();i++)
	{
		xx=thePoints[i].x;
		yy=thePoints[i].y;
		tempMasks2[xx+1][yy+1]=3;
	}
// 	GetCircleRegionMasks(tempMasks2,cvPoint(0,0));

	CvPoint tempPoint;
	int tempRegion=6;//起始的新区域编号,会动态增加
	vector<int> possibleRegion,numOfPoints;
	for(i=0;i<thePoints.size();i++)
	{
		tempPoint=thePoints[i];
		tempPoint.x++;
		tempPoint.y++;

		//检测该点上方的点是否可以作为种子点
		xx=tempPoint.x-1;
		yy=tempPoint.y;
		if(xx>=0&&tempMasks2[xx][yy]==0)
		{
			j=FillingRegionCountingPoints(tempMasks2,cvPoint(xx,yy),tempRegion);
			if(j>0)
			{
				possibleRegion.push_back(tempRegion);
				numOfPoints.push_back(j);
			}
			tempRegion++;
		}
		//检测该点左边的点是否可以作为种子点
		xx=tempPoint.x;
		yy=tempPoint.y-1;
		if(yy>=0&&tempMasks2[xx][yy]==0)
		{
			j=FillingRegionCountingPoints(tempMasks2,cvPoint(xx,yy),tempRegion);
			if(j>0)
			{
				possibleRegion.push_back(tempRegion);
				numOfPoints.push_back(j);
			}
			tempRegion++;
		}
		//检测该点下方的点是否可以作为种子点
		xx=tempPoint.x+1;
		yy=tempPoint.y;
		if(xx<row&&tempMasks2[xx][yy]==0)
		{
			j=FillingRegionCountingPoints(tempMasks2,cvPoint(xx,yy),tempRegion);
			if(j>0)
			{
				possibleRegion.push_back(tempRegion);
				numOfPoints.push_back(j);
			}
			tempRegion++;
		}
		//检测该点右边的点是否可以作为种子点
		xx=tempPoint.x;
		yy=tempPoint.y+1;
		if(yy<col&&tempMasks2[xx][yy]==0)
		{
			j=FillingRegionCountingPoints(tempMasks2,cvPoint(xx,yy),tempRegion);
			if(j>0)
			{
				possibleRegion.push_back(tempRegion);
				numOfPoints.push_back(j);
			}
			tempRegion++;
		}
	}
	if(possibleRegion.size()==0)
	{
		return;
	}
	if(possibleRegion.size()==1)
	{
		if(numOfPoints[0]+thePoints.size()==numOfPointsToModify)
		{
			return;//修饰线仅仅通过新区域边界上的点
		}
	}
	
	j=row*col+1;
	tempRegion=-1;
	for(i=0;i<possibleRegion.size();i++)
	{
		if(numOfPoints[i]<j)
		{
			tempRegion=possibleRegion[i];
			j=numOfPoints[i];
		}
	}
	if(tempRegion==-1)
	{
		return;
	}

	for(i=0;i<height;i++)
	{
		for(j=0;j<width;j++)
		{
			if(tempMasks2[i+1][j+1]==tempRegion)
			{
				areaMatrix[i][j]=firstRegionNum;
			}
		}
	}

	CalcAverageColor();
}

void ImageRegionOperator::RearrangeRegionNum()
{
	int i,j,regionNum,newRegionNum=1;
	vector<int> numToChange(maxRegionNum+1,0);

	for(i=0;i<height;i++)
	{
		for(j=0;j<width;j++)
		{
			regionNum=areaMatrix[i][j];
			if(numToChange[regionNum]==0)
			{
				numToChange[regionNum]=newRegionNum++;
			}
		}
	}
	for(i=0;i<height;i++)
	{
		for(j=0;j<width;j++)
		{
			regionNum=areaMatrix[i][j];
			areaMatrix[i][j]=numToChange[regionNum];
		}
	}
	maxRegionNum=newRegionNum-1;
}

int ImageRegionOperator::GetMaxRegionNum()
{
	int i,j,maxRegionNum=-1;
	for(i=0;i<height;i++)
	{
		for(j=0;j<width;j++)
		{
			if(areaMatrix[i][j]>maxRegionNum)
			{
				maxRegionNum=areaMatrix[i][j];
			}
		}
	}
	return maxRegionNum;
}

bool ImageRegionOperator::IsInScale(CvPoint thePoint)
{
	if(thePoint.x<0||thePoint.x>=height)
	{
		return false;
	}
	if(thePoint.y<0||thePoint.y>=width)
	{
		return false;
	}
	return true;
}

void ImageRegionOperator::PutPointInScale(CvPoint &thePoint)
{
	//可能OpenCV的点坐标使用16bit无符号整数,所以转换为int时需要根据版本进行修改
	if(thePoint.x<0||thePoint.x>32767)
	{
		thePoint.x=0;
	}
	if(thePoint.x>=height)
	{
		thePoint.x=height-1;
	}
	if(thePoint.y<0||thePoint.y>32767)
	{
		thePoint.y=0;
	}
	if(thePoint.y>=width)
	{
		thePoint.y=width-1;
	}
}

