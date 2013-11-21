#include "stdafx.h"
#include "CGenerateSmallImage.h"
#include "imatrix.h"
#include "ETF.h"
#include "fdog.h"
#include "time.h"
#include "bresenham.h"
#include <iostream>
using namespace std;
CGenerateSmallImage::CGenerateSmallImage(/*int w,int h*/)
{
	//width = w;
	//height = h;
	string thePath=(theApp.GetDefaultPath()+"ConfigFile\\xx5.bmp");
	realimg.textureSyn.loadSample(thePath.c_str());
	isvector = false;
	thePath=theApp.GetDefaultPath()+"ConfigFile\\src.jpg";
	src = cvLoadImage(thePath.c_str(),1);
	VectorField = new float*[src->height] ;
	for( int i = 0 ; i < src->height ; i ++ )
		VectorField[i] = new float[src->width] ;
	thePath=theApp.GetDefaultPath()+"ConfigFile\\src.txt";
	FILE* fp;
	fp = fopen(thePath.c_str(),"r");
	float a=0.0;
	for(int i=0;i<src->height;i++)
	{
		for(int j=0;j<src->width-1;j++)
		{
			fscanf(fp,"%f,",&a);
			VectorField[i][j] = a;
		}
		fscanf(fp,"%f,/n",&a);
		VectorField[i][src->width-1]=a;
	}
	//int iii=1;
}
CGenerateSmallImage::~CGenerateSmallImage()
{
	for(int i=0;i<src->height;i++)
	{
		delete [src->width]VectorField[i];
		VectorField[i]=NULL;
	}
	delete [src->height]VectorField;
	VectorField=NULL;
	if(src!=NULL)
	{
		cvReleaseImage(&src);
	}
}
double CGenerateSmallImage::FillContour(IplImage* contour,double percentage,double alpha1,double alpha2,double ratio)
{
	stitches1.clear();
	stitches2.clear();
	double distance;

	//IplImage *dx,IplImage *dy x,y方向梯度图像
	//IplImage* contour 轮廓图,IplImage *img 图,int iScale 放大倍数,CColorTable *cTable 使用的绣线颜色表
	//
	//求每个区域外接矩形、平均颜色,theta
	//int r=0,g=0,b=0,pixelCount=0;
	int left=width-1,top=height-1,right=0,bottom=0;
	double vx=0,vy=0;
	double gx2=0,gy2=0;
	for(int row=0;row<height;row++)
		for(int col=0;col<width;col++)
		{
			CvScalar s = cvGet2D(contour,row,col);
			if(s.val[0]!=0)
			{
				if(left>col)left=col;
				if(top>row)top=row;
				if(right<col)right=col;
				if(bottom<row)bottom=row;
			}
		}
		if((right-left)>(bottom-top))
		{
			distance=(double)(right-left)*ratio;
		}
		else
		{
			distance=(double)(bottom-top)*ratio;
		}
		//distance = 1 ;
		double alpha[2];
		alpha1=alpha1*PI/180;
		alpha2=alpha2*PI/180;

		if(alpha1<0)alpha1=PI+alpha1;
		if(alpha2<0)alpha2=PI+alpha2;

		if(alpha1>PI/2)alpha1=alpha1-PI;
		if(alpha2>PI/2)alpha2=alpha2-PI;

		double length1,length2;

		if(fabs(alpha1)<PI/4){
			length1=(right-left+1)/cos(alpha1);
		}
		else
		{
			length1=fabs((bottom-top+1)/sin(alpha1));
		}
		if(fabs(alpha2)<PI/4)
		{
			length2=(right-left+1)/cos(alpha2);
		}
		else
		{
			length2=fabs((bottom-top+1)/sin(alpha2));
		}

		//srand ( time(NULL) );
		//根据length1+length2的值和区域面积,iScale,预计覆盖百分比计算线数

		int lineCount = ((bottom-top+1)*(right-left+1)*percentage)/(length1+length2);

		if(lineCount==0)
			lineCount=1;

		alpha[0]=alpha1;
		alpha[1]=alpha2;
		int intervals[2];

		for(int k=0;k<2;k++)
		{
			if(fabs(alpha[k])<PI/4)
			{
				intervals[k]=distance/fabs(cos(alpha[k]));
			}
			else
			{
				intervals[k]=distance/fabs(sin(alpha[k]));
			}
		}
		///////////////////////////过小直接赋1//////////////////////////////
		for(int k=0;k<2;k++)
		{
			intervals[k] = (int)ratio;
		}	
		//按交叉角度画出两条线
		for(int k=0;k<2;k++){
			if(fabs(alpha[k])<PI/4)
			{

				if(alpha[k]<0){
					for(int start= top;start<(bottom+1)-(right-left+1)*tan(alpha[k]);start+=intervals[k])
					{
						//起点、终点坐标    //画线
						vector<CvPoint> aLine;
						bresenham(&aLine,left,start-intervals[k]/2+rand()%(intervals[k]),(right+1)-1,start-intervals[k]/2+rand()%(intervals[k])+(right-left+1)*tan(alpha[k]));
						//bresenham(&aLine,left*scale,start-intervals[k]/2,(right+1)*scale-1,start-intervals[k]/2+(right-left+1)*scale*tan(alpha[k]));
						//计算线条位于区域内的部分，作为最终针迹        
						processLine(&aLine,contour,left,top,right,bottom,k);
					}
				}
				else{
					for(int start= top-(right-left+1)*tan(alpha[k]);start<(bottom+1);start+=intervals[k])
					{
						//起点、终点坐标    //画线
						vector<CvPoint> aLine;
						bresenham(&aLine,left,start-intervals[k]/2+rand()%(intervals[k]),(right+1)-1,start-intervals[k]/2+rand()%(intervals[k])+(right-left+1)*tan(alpha[k]));
						//bresenham(&aLine,left*scale,start-intervals[k]/2,(right+1)*scale-1,start-intervals[k]/2+(right-left+1)*scale*tan(alpha[k]));
						//计算线条位于区域内的部分，作为最终针迹        
						processLine(&aLine,contour,left,top,right,bottom,k);
					}

				}
			}
			else if(alpha[k]<0){
				int start= left;
				for(;start<(right+1)-(bottom-top+1)/tan(alpha[k]);start+=intervals[k])
				{
					vector<CvPoint> aLine;
					bresenham(&aLine,start-intervals[k]/2+rand()%(intervals[k]),top,start-intervals[k]/2+rand()%(intervals[k])+(bottom-top+1)/tan(alpha[k]),(bottom+1)-1);
					//bresenham(&aLine,start-intervals[k]/2,top*scale,start-intervals[k]/2+(bottom-top+1)*scale/tan(alpha[k]),(bottom+1)*scale-1);
					//计算线条位于区域内的部分，作为最终针迹   ,
					processLine(&aLine,contour,left,top,right,bottom,k);
				}
			}
			else{
				//interval= ((right-left+1)*iScale)/(lineCount);
				int start= left-(bottom-top+1)/tan(alpha[k]);
				for(;start<(right+1);start+=intervals[k])
				{
					vector<CvPoint> aLine;
					bresenham(&aLine,start-intervals[k]/2+rand()%(intervals[k]),top,start-intervals[k]/2+rand()%(intervals[k])+(bottom-top+1)/tan(alpha[k]),(bottom+1)-1);
					//bresenham(&aLine,start-intervals[k]/2,top*scale,start-intervals[k]/2+(bottom-top+1)*scale/tan(alpha[k]),(bottom+1)*scale-1);
					//计算线条位于区域内的部分，作为最终针迹         
					processLine(&aLine,contour,left,top,right,bottom,k);
				}
			}
		}
		return fabs(alpha1-alpha2);
}
void CGenerateSmallImage::processLine(vector<CvPoint>* line,IplImage * contour, int left, int top, int right, int bottom, int k)
{
	//TODO: Add your source code here
	int flag=0;
	int startx,starty,tox,toy;
	for(int i=0;i<line->size();i++)
	{
		int x=line->operator [](i).x;
		int y=line->operator [](i).y;
		int ix=x;
		int iy=y;
		int innerflag=0;
		if(x<0||y<0){
		}
		else{
			if(ix<left||iy<top||ix>right||iy>bottom)
			{
			}
			else if(cvGet2D(contour,iy,ix).val[0]!=0){
				innerflag=1;
			}
		}
		if(innerflag==0)//不在轮廓中的点
		{
			if(flag==1)//如果前一点在轮廓中
			{
				if(startx>=width||tox>=width)
				{
					cout<<"error"<<endl;
					return;
				}
				CvPoint p1,p2;
				p1.x=startx;
				p1.y=starty;
				p2.x=tox;
				p2.y=toy;
				if(k==0)
				{
					this->AddStitch1(p1,p2);
				}
				else if(k==1)
				{
					this->AddStitch2(p1,p2);
				}	
				flag=0;
			}
		}
		else//在轮廓中的点
		{
			if(flag==0)
			{
				startx=x;starty=y;tox=x;toy=y; flag=1;
			}
			else
			{
				tox=x;toy=y;
				if(startx>=width||tox>=width)
				{
					cout<<"error"<<endl;
					return;
				}
			}
		}
	}
	if(flag==1)
	{
		if(startx>=width||tox>=width)
		{
			cout<<"error"<<endl;
			return;
		}
		CvPoint p1,p2;
		p1.x=startx;
		p1.y=starty;
		p2.x=tox;
		p2.y=toy;
		if(k==0)
		{
			this->AddStitch1(p1,p2);
		}
		else if(k==1)
		{
			this->AddStitch2(p1,p2);
		}			
	}
}
// 增加一针，选择好起点和终点后，将该针加入list
void CGenerateSmallImage::AddStitch1(CvPoint p1, CvPoint p2)
{
	vector<CvPoint> stitch;
	stitch.push_back(p1);
	stitch.push_back(p2);
	stitches1.push_back(stitch);		
}
void CGenerateSmallImage::AddStitch2(CvPoint p1, CvPoint p2)
{
	vector<CvPoint> stitch;
	stitch.push_back(p1);
	stitch.push_back(p2);
	stitches2.push_back(stitch);		
}
IplImage* CGenerateSmallImage::GetImg1(double density, double length, double chaosextent, double theta, double beta)
{
	beta = beta/2;
	int step;
	step = (1-7)*density+7;
	//srand(unsigned(time(NULL)));
	srand(GetTickCount());
	stitches1.clear();
	stitches2.clear();
	StitchSet1.clear();
	StitchSet2.clear();
	
	height = src->height;
	width = src->width;
	IplImage* seg;
	CvSize size;
	size.height=height;
	size.width=width;
	seg = cvCreateImage(size,8,3);
	for(int i=0;i<seg->width;i++)
	{
		for(int j=0;j<seg->height;j++)
		{
			CvScalar col;
			col.val[0] = 255;col.val[1] = 255;col.val[2] = 255;
			cvSet2D(seg,j,i,col);
		}
	}

	size.height=height*realimg.textureSyn.getThreadWidth();
	size.width=width*realimg.textureSyn.getThreadWidth();
	IplImage* realdst=cvCreateImage(size,8,3);
	for(int i=0;i<realdst->width;i++)
		for(int j=0;j<realdst->height;j++)
		{
			CvScalar col;
			col.val[0]=255;col.val[1]=255;col.val[2]=255;
			cvSet2D(realdst,j,i,col);
		}
	int** contour;
	contour = new int*[height] ;
	for( int i = 0 ; i < height ; i ++ )
		contour[i] = new int[width] ;
	for(int row=0;row<height;row++)
		for(int col=0;col<width;col++)
		{
			CvScalar s = cvGet2D(seg,row,col);
			if(s.val[0]==255)
			{
				contour[row][col]=1;
			}
			else
			{
				contour[row][col]=0;
			}
		}
	FillContour(seg, 0.5,180-(theta+beta),180-(theta-beta),step);
	///////////////////////两点之间插点///////////////////////////////
	vector<vector<CvPoint>> StraightLine1;
	vector<vector<CvPoint>> StraightLine2;
	for(int i=0;i<stitches1.size();i++)
	{
		vector<CvPoint> aLine;
		bresenham(&aLine,stitches1[i][0].x,stitches1[i][0].y,stitches1[i][1].x,stitches1[i][1].y);
		StraightLine1.push_back(aLine);
		vector<CvPoint>().swap(aLine);
	}
	for(int i=0;i<stitches2.size();i++)
	{
		vector<CvPoint> aLine;
		bresenham(&aLine,stitches2[i][0].x,stitches2[i][0].y,stitches2[i][1].x,stitches2[i][1].y);
		StraightLine2.push_back(aLine);
		vector<CvPoint>().swap(aLine);
	}
	int jiange = (5-15)*density+15;
	for(int i=0;i<StraightLine1.size();i=i+1)
	{
		for(int n=0;n<StraightLine1[i].size();)
		{
			vector<CvPoint> shortstitch;
			CvPoint p1,p2,pm;			
			p1.x=StraightLine1[i][n].x;
			p1.y=StraightLine1[i][n].y;
			int k;
			for(k=jiange;k>=0;k--)
			{
				if(n+k<StraightLine1[i].size())
				{
					p2.x=StraightLine1[i][n+k].x;
					p2.y=StraightLine1[i][n+k].y;
					break;
				}
			}
			shortstitch.push_back(p1);
			shortstitch.push_back(p2);
			StitchSet1.push_back(shortstitch);
			vector<CvPoint>().swap(shortstitch);
			n=n+jiange+rand()%6-3;
		}
	}
	
	for(int i=0;i<StraightLine2.size();i=i+1)
	{
		for(int n=0;n<StraightLine2[i].size();)
		{
			vector<CvPoint> shortstitch;
			CvPoint p1,p2,pm;			
			p1.x=StraightLine2[i][n].x;
			p1.y=StraightLine2[i][n].y;
			int k;
			for(k=jiange;k>=0;k--)
			{
				if(n+k<StraightLine2[i].size())
				{
					p2.x=StraightLine2[i][n+k].x;
					p2.y=StraightLine2[i][n+k].y;
					break;
				}
			}
			shortstitch.push_back(p1);
			shortstitch.push_back(p2);
			StitchSet2.push_back(shortstitch);
			vector<CvPoint>().swap(shortstitch);
			n=n+jiange+rand()%6-3;
		}
	}
	for(int i=0;i<StitchSet1.size();i++)
	{
		double Angle;
		if(isvector)
		{
			int xx = (StitchSet1[i][1].x + StitchSet1[i][0].x)/2;
			int yy = (StitchSet1[i][1].y + StitchSet1[i][0].y)/2;
			if(xx<0)
				xx = 0;
			if(xx>=src->width)
				xx = src->width-1;
			if(yy<0)
				yy = 0;
			if(yy>=src->height)
				yy = src->height-1;
			Angle = -VectorField[yy][xx];
		}
		else
		{
			Angle = -theta*PI/180.0;
		}
		double HorizontalDistance = (double)(StitchSet1[i][1].x - StitchSet1[i][0].x);
		double VerticalDistance = (double)(StitchSet1[i][1].y - StitchSet1[i][0].y);
		double Distance = length;
		CvPoint middle;
		middle.x = (StitchSet1[i][1].x + StitchSet1[i][0].x)/2.0;
		middle.y = (StitchSet1[i][1].y + StitchSet1[i][0].y)/2.0;
		double p=(rand()%100)*0.01;
		int startx,starty,endx,endy;
		Angle = Angle - beta * PI/180.0+((double)(rand()%45)-22.5) * chaosextent*PI/180.0;
		startx = middle.x - Distance/2.0*(1+p)*cos(Angle);
		starty = middle.y - Distance/2.0*(1+p)*sin(Angle);
		endx = middle.x + Distance/2.0*(1+p)*cos(Angle);
		endy = middle.y + Distance/2.0*(1+p)*sin(Angle);
		if(startx<0)
			startx = 0;
		if(starty<0)
			starty = 0;
		if(startx>=width)
			startx = width-1;
		if(starty>= height)
			starty = height-1;
		if(endx<0)
			endx = 0;
		if(endy<0)
			endy = 0;
		if(endx>=width)
			endx = width-1;
		if(endy>= height)
			endy = height-1;
		
		if(contour[starty][startx]==1&&contour[endy][endx]==1)
		{
			StitchSet1[i][1].x = endx;
			StitchSet1[i][0].x = startx;
			StitchSet1[i][1].y = endy;
			StitchSet1[i][0].y = starty;
		}
		else if(contour[starty][startx]==1&&contour[endy][endx]==0)
		{
			for(int ii=9;ii>=0;ii--)
			{
				/*endx = middle.x + Distance/2.0*(1+p)*(cosAngle)*(float)ii/10;
				endy = middle.y + Distance/2.0*(1+p)*(sinAngle)*(float)ii/10;*/
				endx = middle.x + Distance/2.0*(1+p)*cos(Angle)*(float)ii/10;
				endy = middle.y + Distance/2.0*(1+p)*sin(Angle)*(float)ii/10;
				if(endx<0)
					endx = 0;
				if(endy<0)
					endy = 0;
				if(endx>=width)
					endx = width-1;
				if(endy>= height)
					endy = height-1;
				if(contour[endy][endx]==1)
					break;
			}
			StitchSet1[i][1].x = endx;
			StitchSet1[i][0].x = startx;
			StitchSet1[i][1].y = endy;
			StitchSet1[i][0].y = starty;
		}
		else if(contour[starty][startx]==0&&contour[endy][endx]==1)
		{
			for(int ii=9;ii>=0;ii--)
			{
				/*startx = middle.x - Distance/2.0*(1+p)*(cosAngle)*(float)ii/10;
				starty = middle.y - Distance/2.0*(1+p)*(sinAngle)*(float)ii/10;*/
				startx = middle.x - Distance/2.0*(1+p)*cos(Angle)*(float)ii/10;
				starty = middle.y - Distance/2.0*(1+p)*sin(Angle)*(float)ii/10;
				if(startx<0)
					startx = 0;
				if(starty<0)
					starty = 0;
				if(startx>=width)
					startx = width-1;
				if(starty>= height)
					starty = height-1;
				if(contour[starty][startx]==1)
					break;
			}
			StitchSet1[i][1].x = endx;
			StitchSet1[i][0].x = startx;
			StitchSet1[i][1].y = endy;
			StitchSet1[i][0].y = starty;
		}

	}
	for(int i=0;i<StitchSet2.size();i++)
	{
		double Angle;
		if(isvector)
		{
			int xx = (StitchSet2[i][1].x + StitchSet2[i][0].x)/2;
			int yy = (StitchSet2[i][1].y + StitchSet2[i][0].y)/2;
			if(xx<0)
				xx = 0;
			if(xx>=src->width)
				xx = src->width-1;
			if(yy<0)
				yy = 0;
			if(yy>=src->height)
				yy = src->height-1;
			Angle = -VectorField[yy][xx];
		}
		else
		{
			Angle = -theta*PI/180.0;
		}
		double HorizontalDistance = (double)(StitchSet2[i][1].x - StitchSet2[i][0].x);
		double VerticalDistance = (double)(StitchSet2[i][1].y - StitchSet2[i][0].y);
		double Distance = length;
		CvPoint middle;
		middle.x = (StitchSet2[i][1].x + StitchSet2[i][0].x)/2.0;
		middle.y = (StitchSet2[i][1].y + StitchSet2[i][0].y)/2.0;
		double p=(rand()%100)*0.01;
		int startx,starty,endx,endy;
		Angle = Angle + beta * PI/180.0+((double)(rand()%45)-22.5) * chaosextent*PI/180.0;
		startx = middle.x - Distance/2.0*(1+p)*cos(Angle);
		starty = middle.y - Distance/2.0*(1+p)*sin(Angle);
		endx = middle.x + Distance/2.0*(1+p)*cos(Angle);
		endy = middle.y + Distance/2.0*(1+p)*sin(Angle);
		if(startx<0)
			startx = 0;
		if(starty<0)
			starty = 0;
		if(startx>=width)
			startx = width-1;
		if(starty>= height)
			starty = height-1;
		if(endx<0)
			endx = 0;
		if(endy<0)
			endy = 0;
		if(endx>=width)
			endx = width-1;
		if(endy>= height)
			endy = height-1;
		
		if(contour[starty][startx]==1&&contour[endy][endx]==1)
		{
			StitchSet2[i][1].x = endx;
			StitchSet2[i][0].x = startx;
			StitchSet2[i][1].y = endy;
			StitchSet2[i][0].y = starty;
		}
		else if(contour[starty][startx]==1&&contour[endy][endx]==0)
		{
			for(int ii=9;ii>=0;ii--)
			{
				/*endx = middle.x + Distance/2.0*(1+p)*(cosAngle)*(float)ii/10;
				endy = middle.y + Distance/2.0*(1+p)*(sinAngle)*(float)ii/10;*/
				endx = middle.x + Distance/2.0*(1+p)*cos(Angle)*(float)ii/10;
				endy = middle.y + Distance/2.0*(1+p)*sin(Angle)*(float)ii/10;
				if(endx<0)
					endx = 0;
				if(endy<0)
					endy = 0;
				if(endx>=width)
					endx = width-1;
				if(endy>= height)
					endy = height-1;
				if(contour[endy][endx]==1)
					break;
			}
			StitchSet2[i][1].x = endx;
			StitchSet2[i][0].x = startx;
			StitchSet2[i][1].y = endy;
			StitchSet2[i][0].y = starty;
		}
		else if(contour[starty][startx]==0&&contour[endy][endx]==1)
		{
			for(int ii=9;ii>=0;ii--)
			{
				/*startx = middle.x - Distance/2.0*(1+p)*(cosAngle)*(float)ii/10;
				starty = middle.y - Distance/2.0*(1+p)*(sinAngle)*(float)ii/10;*/
				startx = middle.x - Distance/2.0*(1+p)*cos(Angle)*(float)ii/10;
				starty = middle.y - Distance/2.0*(1+p)*sin(Angle)*(float)ii/10;
				if(startx<0)
					startx = 0;
				if(starty<0)
					starty = 0;
				if(startx>=width)
					startx = width-1;
				if(starty>= height)
					starty = height-1;
				if(contour[starty][startx]==1)
					break;
			}
			StitchSet2[i][1].x = endx;
			StitchSet2[i][0].x = startx;
			StitchSet2[i][1].y = endy;
			StitchSet2[i][0].y = starty;
		}

	}
	
	for(int k=0;k<=StitchSet1.size()-1;k++)
	{
		CvScalar col,mid;
		CvPoint p1,p2;
		p1.x = StitchSet1[k][0].x;
		p1.y = StitchSet1[k][0].y;
		p2.x = StitchSet1[k][1].x;
		p2.y = StitchSet1[k][1].y;
		mid = cvGet2D(seg,(p1.y+p2.y)/2,(p1.x+p2.x)/2);
		col = cvGet2D(src,(p1.y+p2.y)/2,(p1.x+p2.x)/2);
		//col1=MCT.FindNearestColor(col1);
		if(mid.val[0]==255)
		{
			//cvLine(realdst, StitchSet1[k][0],StitchSet1[k][1],col, 1, 1, 0);
			realimg.drawRealStitch(realdst,StitchSet1[k][0].x,StitchSet1[k][0].y,StitchSet1[k][1].x,StitchSet1[k][1].y,RGB(col.val[2],col.val[1],col.val[0]));
		}
	}
	for(int k=0;k<=StitchSet2.size()-1;k++)
	{
		CvScalar col,mid;
		CvPoint p1,p2;
		p1.x = StitchSet2[k][0].x;
		p1.y = StitchSet2[k][0].y;
		p2.x = StitchSet2[k][1].x;
		p2.y = StitchSet2[k][1].y;
		mid = cvGet2D(seg,(p1.y+p2.y)/2,(p1.x+p2.x)/2);
		col = cvGet2D(src,(p1.y+p2.y)/2,(p1.x+p2.x)/2);
		//col1=MCT.FindNearestColor(col1);
		if(mid.val[0]==255)
		{
			//cvLine(realdst, StitchSet2[k][0],StitchSet2[k][1],col, 1, 1, 0);
			realimg.drawRealStitch(realdst,StitchSet2[k][0].x,StitchSet2[k][0].y,StitchSet2[k][1].x,StitchSet2[k][1].y,RGB(col.val[2],col.val[1],col.val[0]));
		}
	}
	//cvSaveImage("stitch.jpg",realdst);
	for(int i=0;i<StraightLine1.size();i++)
	{
		vector<CvPoint>().swap(StraightLine1[i]);
	}
	vector<vector<CvPoint>>().swap(StraightLine1);
	for(int i=0;i<StraightLine2.size();i++)
	{
		vector<CvPoint>().swap(StraightLine2[i]);
	}
	vector<vector<CvPoint>>().swap(StraightLine2);
	cvReleaseImage(&seg);
	for(int i=0;i<height;i++)
    {
        delete [width]contour[i];
        contour[i]=NULL;
    }
    delete [height]contour;
    contour=NULL;
	return realdst;


}
IplImage* CGenerateSmallImage::GetImg2(double density, double length, double chaosextent, double theta, double beta)
{
	beta = beta/2;
	int step;
	step = (1-7)*density+7;
	srand(unsigned(time(NULL)));
	StitchSet1.clear();
	string tempPath=theApp.GetDefaultPath()+"ConfigFile\\src.jpg";
	IplImage* src;
	src = cvLoadImage(tempPath.c_str(),1);
	IplImage* seg;
	CvSize size;
	size.height=height;
	size.width=width;
	seg = cvCreateImage(size,8,3);
	for(int i=0;i<seg->width;i++)
	{
		for(int j=0;j<seg->height;j++)
		{
			CvScalar col;
			col.val[0] = 255;col.val[1] = 255;col.val[2] = 255;
			cvSet2D(seg,j,i,col);
		}
	}

	size.height=height;
	size.width=width;
	IplImage* realdst=cvCreateImage(size,8,3);
	for(int i=0;i<realdst->width;i++)
		for(int j=0;j<realdst->height;j++)
		{
			CvScalar col;
			col.val[0]=255;col.val[1]=255;col.val[2]=255;
			cvSet2D(realdst,j,i,col);
		}
	int** contour;
	contour = new int*[height] ;
	for( int i = 0 ; i < height ; i ++ )
		contour[i] = new int[width] ;
	for(int row=0;row<height;row++)
		for(int col=0;col<width;col++)
		{
			CvScalar s = cvGet2D(seg,row,col);
			if(s.val[0]==255)
			{
				contour[row][col]=1;
			}
			else
			{
				contour[row][col]=0;
			}
		}
	FillContour(seg, 0.5,180-(theta+beta),180-(theta-beta),step);
	///////////////////////两点之间插点///////////////////////////////
	vector<vector<CvPoint>> StraightLine1;
	vector<vector<CvPoint>> StraightLine2;
	for(int i=0;i<stitches1.size();i++)
	{
		vector<CvPoint> aLine;
		bresenham(&aLine,stitches1[i][0].x,stitches1[i][0].y,stitches1[i][1].x,stitches1[i][1].y);
		StraightLine1.push_back(aLine);
		vector<CvPoint>().swap(aLine);
	}
	for(int i=0;i<stitches2.size();i++)
	{
		vector<CvPoint> aLine;
		bresenham(&aLine,stitches2[i][0].x,stitches2[i][0].y,stitches2[i][1].x,stitches2[i][1].y);
		StraightLine2.push_back(aLine);
		vector<CvPoint>().swap(aLine);
	}
	int jiange = (5-15)*density+15;
	for(int i=0;i<StraightLine1.size();i=i+1)
	{
		for(int n=0;n<StraightLine1[i].size();)
		{
			vector<CvPoint> shortstitch;
			CvPoint p1,p2,pm;			
			p1.x=StraightLine1[i][n].x;
			p1.y=StraightLine1[i][n].y;
			int k;
			for(k=jiange;k>=0;k--)
			{
				if(n+k<StraightLine1[i].size())
				{
					p2.x=StraightLine1[i][n+k].x;
					p2.y=StraightLine1[i][n+k].y;
					break;
				}
			}
			shortstitch.push_back(p1);
			shortstitch.push_back(p2);
			StitchSet1.push_back(shortstitch);
			vector<CvPoint>().swap(shortstitch);
			n=n+jiange+rand()%6-3;
		}
	}
	
	for(int i=0;i<StraightLine2.size();i=i+1)
	{
		for(int n=0;n<StraightLine2[i].size();)
		{
			vector<CvPoint> shortstitch;
			CvPoint p1,p2,pm;			
			p1.x=StraightLine2[i][n].x;
			p1.y=StraightLine2[i][n].y;
			int k;
			for(k=jiange;k>=0;k--)
			{
				if(n+k<StraightLine2[i].size())
				{
					p2.x=StraightLine2[i][n+k].x;
					p2.y=StraightLine2[i][n+k].y;
					break;
				}
			}
			shortstitch.push_back(p1);
			shortstitch.push_back(p2);
			StitchSet2.push_back(shortstitch);
			vector<CvPoint>().swap(shortstitch);
			n=n+jiange+rand()%6-3;
		}
	}
	for(int i=0;i<StitchSet1.size();i++)
	{
		double Angle = -theta*PI/180.0;
		double HorizontalDistance = (double)(StitchSet1[i][1].x - StitchSet1[i][0].x);
		double VerticalDistance = (double)(StitchSet1[i][1].y - StitchSet1[i][0].y);
		double Distance = length;
		CvPoint middle;
		middle.x = (StitchSet1[i][1].x + StitchSet1[i][0].x)/2.0;
		middle.y = (StitchSet1[i][1].y + StitchSet1[i][0].y)/2.0;
		double p=(rand()%100)*0.01;
		int startx,starty,endx,endy;
		Angle = Angle - beta * PI/180.0+((double)(rand()%45)-22.5) * chaosextent*PI/180.0;
		startx = middle.x - Distance/2.0*(1+p)*cos(Angle);
		starty = middle.y - Distance/2.0*(1+p)*sin(Angle);
		endx = middle.x + Distance/2.0*(1+p)*cos(Angle);
		endy = middle.y + Distance/2.0*(1+p)*sin(Angle);
		if(startx<0)
			startx = 0;
		if(starty<0)
			starty = 0;
		if(startx>=width)
			startx = width-1;
		if(starty>= height-1)
			starty = height-1;
		if(endx<0)
			endx = 0;
		if(endy<0)
			endy = 0;
		if(endx>=width)
			endx = width-1;
		if(endy>= height)
			endy = height-1;
		
		if(contour[starty][startx]==1&&contour[endy][endx]==1)
		{
			StitchSet1[i][1].x = endx;
			StitchSet1[i][0].x = startx;
			StitchSet1[i][1].y = endy;
			StitchSet1[i][0].y = starty;
		}
		else if(contour[starty][startx]==1&&contour[endy][endx]==0)
		{
			for(int ii=9;ii>=0;ii--)
			{
				/*endx = middle.x + Distance/2.0*(1+p)*(cosAngle)*(float)ii/10;
				endy = middle.y + Distance/2.0*(1+p)*(sinAngle)*(float)ii/10;*/
				endx = middle.x + Distance/2.0*(1+p)*cos(Angle)*(float)ii/10;
				endy = middle.y + Distance/2.0*(1+p)*sin(Angle)*(float)ii/10;
				if(endx<0)
					endx = 0;
				if(endy<0)
					endy = 0;
				if(endx>=width)
					endx = width-1;
				if(endy>= height)
					endy = height-1;
				if(contour[endy][endx]==1)
					break;
			}
			StitchSet1[i][1].x = endx;
			StitchSet1[i][0].x = startx;
			StitchSet1[i][1].y = endy;
			StitchSet1[i][0].y = starty;
		}
		else if(contour[starty][startx]==0&&contour[endy][endx]==1)
		{
			for(int ii=9;ii>=0;ii--)
			{
				/*startx = middle.x - Distance/2.0*(1+p)*(cosAngle)*(float)ii/10;
				starty = middle.y - Distance/2.0*(1+p)*(sinAngle)*(float)ii/10;*/
				startx = middle.x - Distance/2.0*(1+p)*cos(Angle)*(float)ii/10;
				starty = middle.y - Distance/2.0*(1+p)*sin(Angle)*(float)ii/10;
				if(startx<0)
					startx = 0;
				if(starty<0)
					starty = 0;
				if(startx>=width)
					startx = width-1;
				if(starty>= height)
					starty = height-1;
				if(contour[starty][startx]==1)
					break;
			}
			StitchSet1[i][1].x = endx;
			StitchSet1[i][0].x = startx;
			StitchSet1[i][1].y = endy;
			StitchSet1[i][0].y = starty;
		}

	}
	for(int i=0;i<StitchSet2.size();i++)
	{
		double Angle = -theta*PI/180.0;
		double HorizontalDistance = (double)(StitchSet2[i][1].x - StitchSet2[i][0].x);
		double VerticalDistance = (double)(StitchSet2[i][1].y - StitchSet2[i][0].y);
		double Distance = length;
		CvPoint middle;
		middle.x = (StitchSet2[i][1].x + StitchSet2[i][0].x)/2.0;
		middle.y = (StitchSet2[i][1].y + StitchSet2[i][0].y)/2.0;
		double p=(rand()%100)*0.01;
		int startx,starty,endx,endy;
		Angle = Angle + beta * PI/180.0+((double)(rand()%45)-22.5) * chaosextent*PI/180.0;
		startx = middle.x - Distance/2.0*(1+p)*cos(Angle);
		starty = middle.y - Distance/2.0*(1+p)*sin(Angle);
		endx = middle.x + Distance/2.0*(1+p)*cos(Angle);
		endy = middle.y + Distance/2.0*(1+p)*sin(Angle);
		if(startx<0)
			startx = 0;
		if(starty<0)
			starty = 0;
		if(startx>=width)
			startx = width-1;
		if(starty>= height)
			starty = height-1;
		if(endx<0)
			endx = 0;
		if(endy<0)
			endy = 0;
		if(endx>=width)
			endx = width-1;
		if(endy>= height)
			endy = height-1;
		
		if(contour[starty][startx]==1&&contour[endy][endx]==1)
		{
			StitchSet2[i][1].x = endx;
			StitchSet2[i][0].x = startx;
			StitchSet2[i][1].y = endy;
			StitchSet2[i][0].y = starty;
		}
		else if(contour[starty][startx]==1&&contour[endy][endx]==0)
		{
			for(int ii=9;ii>=0;ii--)
			{
				/*endx = middle.x + Distance/2.0*(1+p)*(cosAngle)*(float)ii/10;
				endy = middle.y + Distance/2.0*(1+p)*(sinAngle)*(float)ii/10;*/
				endx = middle.x + Distance/2.0*(1+p)*cos(Angle)*(float)ii/10;
				endy = middle.y + Distance/2.0*(1+p)*sin(Angle)*(float)ii/10;
				if(endx<0)
					endx = 0;
				if(endy<0)
					endy = 0;
				if(endx>=width)
					endx = width-1;
				if(endy>= height)
					endy = height-1;
				if(contour[endy][endx]==1)
					break;
			}
			StitchSet2[i][1].x = endx;
			StitchSet2[i][0].x = startx;
			StitchSet2[i][1].y = endy;
			StitchSet2[i][0].y = starty;
		}
		else if(contour[starty][startx]==0&&contour[endy][endx]==1)
		{
			for(int ii=9;ii>=0;ii--)
			{
				/*startx = middle.x - Distance/2.0*(1+p)*(cosAngle)*(float)ii/10;
				starty = middle.y - Distance/2.0*(1+p)*(sinAngle)*(float)ii/10;*/
				startx = middle.x - Distance/2.0*(1+p)*cos(Angle)*(float)ii/10;
				starty = middle.y - Distance/2.0*(1+p)*sin(Angle)*(float)ii/10;
				if(startx<0)
					startx = 0;
				if(starty<0)
					starty = 0;
				if(startx>=width)
					startx = width-1;
				if(starty>= height)
					starty = height-1;
				if(contour[starty][startx]==1)
					break;
			}
			StitchSet2[i][1].x = endx;
			StitchSet2[i][0].x = startx;
			StitchSet2[i][1].y = endy;
			StitchSet2[i][0].y = starty;
		}

	}
	
	for(int k=0;k<=StitchSet1.size()-1;k++)
	{
		CvScalar col,mid;
		CvPoint p1,p2;
		p1.x = StitchSet1[k][0].x;
		p1.y = StitchSet1[k][0].y;
		p2.x = StitchSet1[k][1].x;
		p2.y = StitchSet1[k][1].y;
		mid = cvGet2D(seg,(p1.y+p2.y)/2,(p1.x+p2.x)/2);
		col = cvGet2D(src,(p1.y+p2.y)/2,(p1.x+p2.x)/2);
		//col1=MCT.FindNearestColor(col1);
		if(mid.val[0]==255)
		{
			cvLine(realdst, StitchSet1[k][0],StitchSet1[k][1],col, 1, 1, 0);
			//realimg.drawRealStitch(realdst,StitchSet1[k][0].x,StitchSet1[k][0].y,StitchSet1[k][1].x,StitchSet1[k][1].y,RGB(col.val[2],col.val[1],col.val[0]));
		}
	}
	for(int k=0;k<=StitchSet2.size()-1;k++)
	{
		CvScalar col,mid;
		CvPoint p1,p2;
		p1.x = StitchSet2[k][0].x;
		p1.y = StitchSet2[k][0].y;
		p2.x = StitchSet2[k][1].x;
		p2.y = StitchSet2[k][1].y;
		mid = cvGet2D(seg,(p1.y+p2.y)/2,(p1.x+p2.x)/2);
		col = cvGet2D(src,(p1.y+p2.y)/2,(p1.x+p2.x)/2);
		//col1=MCT.FindNearestColor(col1);
		if(mid.val[0]==255)
		{
			cvLine(realdst, StitchSet2[k][0],StitchSet2[k][1],col, 1, 1, 0);
			//realimg.drawRealStitch(realdst,StitchSet2[k][0].x,StitchSet2[k][0].y,StitchSet2[k][1].x,StitchSet2[k][1].y,RGB(col.val[2],col.val[1],col.val[0]));
		}
	}
	//cvSaveImage("stitch.jpg",realdst);

	for(int i=0;i<StraightLine1.size();i++)
	{
		vector<CvPoint>().swap(StraightLine1[i]);
	}
	vector<vector<CvPoint>>().swap(StraightLine1);
	for(int i=0;i<StraightLine2.size();i++)
	{
		vector<CvPoint>().swap(StraightLine2[i]);
	}
	vector<vector<CvPoint>>().swap(StraightLine2);
	cvReleaseImage(&seg);
	cvReleaseImage(&src);
	for(int i=0;i<height;i++)
    {
        delete [width]contour[i];
        contour[i]=NULL;
    }
    delete [height]contour;
    contour=NULL;
	return realdst;


}