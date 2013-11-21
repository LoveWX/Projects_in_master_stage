#include "stdafx.h"
#include "bresenham.h"
#include "CMagicCabsineSimulateData_Test.h"
#include "analogdisplay.h"

CMagicCabsineSimulateData_Test::CMagicCabsineSimulateData_Test(const IplImage *tempSrcImage):CMagicCabsineSimulateData(tempSrcImage)
{
	simulateName=string("SimulateData");
	simuLines.clear();
	maxRegionNum=0;
	maxLevelNum=0;
	simuLines.clear();
	blankImage=NULL;
	CreatBlankImage();
}

CMagicCabsineSimulateData_Test::~CMagicCabsineSimulateData_Test()
{
	DeleteSimulateData();
	maxRegionNum=0;
	maxLevelNum=0;
	simuLines.clear();
	if(blankImage!=NULL)
	{
		cvReleaseImage(&blankImage);
		blankImage=NULL;
	}
}

void CMagicCabsineSimulateData_Test::PrepareSimulateData()
{
	//读入分割矩阵数据,计算出maxRegionNum
	if(isPrepared)
	{
		return;
	}
	theMakeTable=new CMagicCabsineDataForSimulating(srcImage);
	theMakeTable->PrepareDataForSimulating();
	theMakeTable->GetSplitMatrix(splitMatrix);
	theStitchLibrary=new CMagicCabsineStitchLibrary();
	isPrepared=true;
}

void CMagicCabsineSimulateData_Test::FillContour(IplImage* contour,double percentage,double alpha1,double alpha2,double ratio)
{
	stitches1.clear();
	stitches2.clear();
	double distance;

	//IplImage *dx,IplImage *dy x,y方向梯度图像
	//IplImage* contour 轮廓图,IplImage *img 图,int iScale 放大倍数,CColorTable *cTable 使用的绣线颜色表
	//
	//求每个区域外接矩形、平均颜色,theta
	//int r=0,g=0,b=0,pixelCount=0;
	int left=srcImage->width-1,top=srcImage->height-1,right=0,bottom=0;
	double vx=0,vy=0;
	double gx2=0,gy2=0;
	for(int row=0;row<srcImage->height;row++)
		for(int col=0;col<srcImage->width;col++)
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
	alpha1=alpha1*pi/180;
	alpha2=alpha2*pi/180;

	if(alpha1<0)alpha1=pi+alpha1;
	if(alpha2<0)alpha2=pi+alpha2;

	if(alpha1>pi/2)alpha1=alpha1-pi;
	if(alpha2>pi/2)alpha2=alpha2-pi;

	double length1,length2;

	if(fabs(alpha1)<pi/4){
		length1=(right-left+1)/cos(alpha1);
	}
	else
	{
		length1=fabs((bottom-top+1)/sin(alpha1));
	}
	if(fabs(alpha2)<pi/4)
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
		if(fabs(alpha[k])<pi/4)
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
		if(fabs(alpha[k])<pi/4)
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
}
void CMagicCabsineSimulateData_Test::processLine(vector<CvPoint>* line,IplImage * contour, int left, int top, int right, int bottom, int k)
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
				if(startx>=srcImage->width||tox>=srcImage->width)
				{
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
				if(startx>=srcImage->width||tox>=srcImage->width)
				{
					return;
				}
			}
		}
	}
	if(flag==1)
	{
		if(startx>=srcImage->width||tox>=srcImage->width)
		{
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
void CMagicCabsineSimulateData_Test::AddStitch1(CvPoint p1, CvPoint p2)
{
	vector<CvPoint> stitch;
	stitch.push_back(p1);
	stitch.push_back(p2);
	stitches1.push_back(stitch);
}
void CMagicCabsineSimulateData_Test::AddStitch2(CvPoint p1, CvPoint p2)
{
	vector<CvPoint> stitch;
	stitch.push_back(p1);
	stitch.push_back(p2);
	stitches2.push_back(stitch);	
}
void CMagicCabsineSimulateData_Test::DrawSimuLinesInChaosRegion(const vector< vector<int> > &theRegionMask,vector<SimuLine> &simuLineSet,ChaosStitch CS)
{
	if(!isPrepared)
	{
		return;
	}
	simuLineSet.clear();
	stitches1.clear();
	stitches2.clear();
	StitchSet1.clear();										
	StitchSet2.clear();
	vector< vector<double>> VectorField;
	theMakeTable->GetUniversalProperty_VectorField(VectorField);

	
	CvSize size;
	size.height = srcImage->height;
	size.width = srcImage->width;
	IplImage* seg = cvCreateImage(size,srcImage->depth,srcImage->nChannels);
	for(int i=0;i<seg->width;i++)
	{
		for(int j=0;j<seg->height;j++)
		{
			CvScalar col;
			if(theRegionMask[j][i] == 1)
			{
				col.val[0] = 255;col.val[1] = 255;col.val[2] = 255;
				cvSet2D(seg,j,i,col);
			}
			else
			{
				col.val[0] = 0;col.val[1] = 0;col.val[2] = 0;
				cvSet2D(seg,j,i,col);
			}
		}
	}
	//IplImage* realdst = cvCreateImage(size,srcImage->depth,srcImage->nChannels);
	//for(int i=0;i<realdst->width;i++)
	//{
	//	for(int j=0;j<realdst->height;j++)
	//	{
	//		CvScalar col;
	//		col.val[0] = 255;col.val[1] = 255;col.val[2] = 255;
	//		cvSet2D(realdst,j,i,col);
	//	}
	//}
	int** contour;
	contour = new int*[srcImage->height] ;
	for( int i = 0 ; i < srcImage->height ; i ++ )
		contour[i] = new int[srcImage->width] ;
	for(int row=0;row<srcImage->height;row++)
		for(int col=0;col<srcImage->width;col++)
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
	/*RegionProcess RP = RegionProcess(srcImage,seg);
	RP.SetRegionOritation();*/

	int step;
	step = (1-7)*CS.density+7;
	CS.beta = CS.beta/2;
	CS.theta = CS.theta;
	FillContour(seg, 0.5,180-(CS.theta*180.0/pi+CS.beta*180/pi),180-(CS.theta*180.0/pi-CS.beta*180/pi),step);
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
	int jiange = (5-15)*CS.density+15;
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
		if(CS.stitchType==STITCH_ChaosVectorFieldCross)
		{
			Angle = -VectorField[StitchSet1[i][0].y/2+StitchSet1[i][1].y/2][StitchSet1[i][0].x/2+StitchSet1[i][1].x/2];
		}
		else
		{
			Angle = CS.theta;
		}
		
		double HorizontalDistance = (double)(StitchSet1[i][1].x - StitchSet1[i][0].x);
		double VerticalDistance = (double)(StitchSet1[i][1].y - StitchSet1[i][0].y);
		double Distance = CS.length;
		CvPoint middle;
		middle.x = (StitchSet1[i][1].x + StitchSet1[i][0].x)/2.0;
		middle.y = (StitchSet1[i][1].y + StitchSet1[i][0].y)/2.0;
		double p=(rand()%100)*0.01;
		int startx,starty,endx,endy;
		Angle = Angle - CS.beta+((double)(rand()%45)-22.5) * CS.chaosExtent*pi/180.0;
		startx = middle.x - Distance/2.0*(1+p)*cos(Angle);
		starty = middle.y - Distance/2.0*(1+p)*sin(Angle);
		endx = middle.x + Distance/2.0*(1+p)*cos(Angle);
		endy = middle.y + Distance/2.0*(1+p)*sin(Angle);
		if(startx<0)
			startx = 0;
		if(starty<0)
			starty = 0;
		if(startx>=srcImage->width)
			startx = srcImage->width-1;
		if(starty>= srcImage->height)
			starty = srcImage->height-1;
		if(endx<0)
			endx = 0;
		if(endy<0)
			endy = 0;
		if(endx>=srcImage->width)
			endx = srcImage->width-1;
		if(endy>= srcImage->height)
			endy = srcImage->height-1;
		
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
				if(endx>=srcImage->width)
					endx = srcImage->width-1;
				if(endy>= srcImage->height)
					endy = srcImage->height-1;
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
				if(startx>=srcImage->width)
					startx = srcImage->width-1;
				if(starty>= srcImage->height)
					starty = srcImage->height-1;
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
		if(CS.stitchType==STITCH_ChaosVectorFieldCross)
		{
			Angle = -VectorField[StitchSet2[i][0].y/2+StitchSet2[i][1].y/2][StitchSet2[i][0].x/2+StitchSet2[i][1].x/2];
		}
		else
		{
			Angle = CS.theta;
		}
		double HorizontalDistance = (double)(StitchSet2[i][1].x - StitchSet2[i][0].x);
		double VerticalDistance = (double)(StitchSet2[i][1].y - StitchSet2[i][0].y);
		double Distance = CS.length;
		CvPoint middle;
		middle.x = (StitchSet2[i][1].x + StitchSet2[i][0].x)/2.0;
		middle.y = (StitchSet2[i][1].y + StitchSet2[i][0].y)/2.0;
		double p=(rand()%100)*0.01;
		int startx,starty,endx,endy;
		Angle = Angle + CS.beta +((double)(rand()%45)-22.5) * CS.chaosExtent*pi/180.0;
		startx = middle.x - Distance/2.0*(1+p)*cos(Angle);
		starty = middle.y - Distance/2.0*(1+p)*sin(Angle);
		endx = middle.x + Distance/2.0*(1+p)*cos(Angle);
		endy = middle.y + Distance/2.0*(1+p)*sin(Angle);
		if(startx<0)
			startx = 0;
		if(starty<0)
			starty = 0;
		if(startx>=srcImage->width)
			startx = srcImage->width-1;
		if(starty>= srcImage->height)
			starty = srcImage->height-1;
		if(endx<0)
			endx = 0;
		if(endy<0)
			endy = 0;
		if(endx>=srcImage->width)
			endx = srcImage->width-1;
		if(endy>= srcImage->height)
			endy = srcImage->height-1;
		
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
				if(endx>=srcImage->width)
					endx = srcImage->width-1;
				if(endy>= srcImage->height)
					endy = srcImage->height-1;
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
				if(startx>=srcImage->width)
					startx = srcImage->width-1;
				if(starty>= srcImage->height)
					starty = srcImage->height-1;
				if(contour[starty][startx]==1)
					break;
			}
			StitchSet2[i][1].x = endx;
			StitchSet2[i][0].x = startx;
			StitchSet2[i][1].y = endy;
			StitchSet2[i][0].y = starty;
		}

	}
	for(int i=0;i<StitchSet1.size();i++)
	{
		CvScalar col,mid;
		CvPoint p1,p2;
		p1.x = StitchSet1[i][0].x;
		p1.y = StitchSet1[i][0].y;
		p2.x = StitchSet1[i][1].x;
		p2.y = StitchSet1[i][1].y;
		mid = cvGet2D(seg,(p1.y+p2.y)/2,(p1.x+p2.x)/2);
		col = cvGet2D(srcImage,(p1.y+p2.y)/2,(p1.x+p2.x)/2);
		SimuLine SL = SimuLine(p1,p2,col,1);
		simuLineSet.push_back(SL);

	}
	for(int i=0;i<StitchSet2.size();i++)
	{
		CvScalar col,mid;
		CvPoint p1,p2;
		p1.x = StitchSet2[i][0].x;
		p1.y = StitchSet2[i][0].y;
		p2.x = StitchSet2[i][1].x;
		p2.y = StitchSet2[i][1].y;
		mid = cvGet2D(seg,(p1.y+p2.y)/2,(p1.x+p2.x)/2);
		col = cvGet2D(srcImage,(p1.y+p2.y)/2,(p1.x+p2.x)/2);
		SimuLine SL = SimuLine(p1,p2,col,1);
		simuLineSet.push_back(SL);

	}
	
	//for(int k=0;k<=StitchSet1.size()-1;k++)
	//{
	//	CvScalar col,mid;
	//	CvPoint p1,p2;
	//	p1.x = StitchSet1[k][0].x;
	//	p1.y = StitchSet1[k][0].y;
	//	p2.x = StitchSet1[k][1].x;
	//	p2.y = StitchSet1[k][1].y;
	//	mid = cvGet2D(seg,(p1.y+p2.y)/2,(p1.x+p2.x)/2);
	//	col = cvGet2D(srcImage,(p1.y+p2.y)/2,(p1.x+p2.x)/2);
	//	//col1=MCT.FindNearestColor(col1);
	//	if(mid.val[0]==255)
	//	{
	//		cvLine(realdst, StitchSet1[k][0],StitchSet1[k][1],col, 1, 1, 0);
	//		//realimg.drawRealStitch(realdst,StitchSet1[k][0].x,StitchSet1[k][0].y,StitchSet1[k][1].x,StitchSet1[k][1].y,RGB(col.val[2],col.val[1],col.val[0]));
	//	}
	//}
	//for(int k=0;k<=StitchSet2.size()-1;k++)
	//{
	//	CvScalar col,mid;
	//	CvPoint p1,p2;
	//	p1.x = StitchSet2[k][0].x;
	//	p1.y = StitchSet2[k][0].y;
	//	p2.x = StitchSet2[k][1].x;
	//	p2.y = StitchSet2[k][1].y;
	//	mid = cvGet2D(seg,(p1.y+p2.y)/2,(p1.x+p2.x)/2);
	//	col = cvGet2D(srcImage,(p1.y+p2.y)/2,(p1.x+p2.x)/2);
	//	//col1=MCT.FindNearestColor(col1);
	//	if(mid.val[0]==255)
	//	{
	//		cvLine(realdst, StitchSet2[k][0],StitchSet2[k][1],col, 1, 1, 0);
	//		//realimg.drawRealStitch(realdst,StitchSet2[k][0].x,StitchSet2[k][0].y,StitchSet2[k][1].x,StitchSet2[k][1].y,RGB(col.val[2],col.val[1],col.val[0]));
	//	}
	//}
	//cvSaveImage("stitch.jpg",realdst);
	//cvReleaseImage(&realdst);
	cvReleaseImage(&seg);
	for(int i=0;i<srcImage->height;i++)
	{
		delete [srcImage->width]contour[i];
		contour[i]=NULL;
	}
	delete [srcImage->height]contour;
	contour=NULL;
	printf("Finished calculating ChaosStitch.\n");
}
void CMagicCabsineSimulateData_Test::DrawSimuLinesInOrderlessRegion(const vector< vector<int> > &theRegionMask,vector<SimuLine> &simuLineSet,OrderlessStitch OS)
{
	if(!isPrepared)
	{
		return;
	}
	simuLineSet.clear();
	stitches1.clear();
	stitches2.clear();
	StitchSet1.clear();										
	StitchSet2.clear();
	vector< vector<double>> VectorField;
	theMakeTable->GetUniversalProperty_VectorField(VectorField);

	
	CvSize size;
	size.height = srcImage->height;
	size.width = srcImage->width;
	IplImage* seg = cvCreateImage(size,srcImage->depth,srcImage->nChannels);
	for(int i=0;i<seg->width;i++)
	{
		for(int j=0;j<seg->height;j++)
		{
			CvScalar col;
			if(theRegionMask[j][i] == 1)
			{
				col.val[0] = 255;col.val[1] = 255;col.val[2] = 255;
				cvSet2D(seg,j,i,col);
			}
			else
			{
				col.val[0] = 0;col.val[1] = 0;col.val[2] = 0;
				cvSet2D(seg,j,i,col);
			}
		}
	}
	//IplImage* realdst = cvCreateImage(size,srcImage->depth,srcImage->nChannels);
	//for(int i=0;i<realdst->width;i++)
	//{
	//	for(int j=0;j<realdst->height;j++)
	//	{
	//		CvScalar col;
	//		col.val[0] = 255;col.val[1] = 255;col.val[2] = 255;
	//		cvSet2D(realdst,j,i,col);
	//	}
	//}
	int** contour;
	contour = new int*[srcImage->height] ;
	for( int i = 0 ; i < srcImage->height ; i ++ )
		contour[i] = new int[srcImage->width] ;
	for(int row=0;row<srcImage->height;row++)
		for(int col=0;col<srcImage->width;col++)
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
	/*RegionProcess RP = RegionProcess(srcImage,seg);
	RP.SetRegionOritation();*/

	int step;
	step = (1-7)*OS.density+7;
	OS.beta = OS.beta/2;
	OS.theta = OS.theta;
	FillContour(seg, 0.5,180-(OS.theta*180.0/pi+OS.beta*180.0/pi),180-(OS.theta*180.0/pi-OS.beta*180.0/pi),step);
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
	int jiange = (5-15)*OS.density+15;
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
		int xx = StitchSet1[i][0].x/2+StitchSet1[i][1].x/2;
		int yy = StitchSet1[i][0].y/2+StitchSet1[i][1].y/2;
		if(xx<0)
			xx=0;
		if(xx>=srcImage->width)
			xx = srcImage->width-1;
		if(yy<0)
			yy=0;
		if(yy>=srcImage->height)
			yy = srcImage->height-1;
		double Angle = -VectorField[yy][xx];
		double HorizontalDistance = (double)(StitchSet1[i][1].x - StitchSet1[i][0].x);
		double VerticalDistance = (double)(StitchSet1[i][1].y - StitchSet1[i][0].y);
		double Distance = OS.length;
		CvPoint middle;
		middle.x = (StitchSet1[i][1].x + StitchSet1[i][0].x)/2.0;
		middle.y = (StitchSet1[i][1].y + StitchSet1[i][0].y)/2.0;
		double p=(rand()%100)*0.01;
		int startx,starty,endx,endy;
		Angle = Angle - OS.beta+((double)(rand()%45)-22.5) * OS.chaosExtent*pi/180.0;
		startx = middle.x - Distance/2.0*(1+p)*cos(Angle);
		starty = middle.y - Distance/2.0*(1+p)*sin(Angle);
		endx = middle.x + Distance/2.0*(1+p)*cos(Angle);
		endy = middle.y + Distance/2.0*(1+p)*sin(Angle);
		if(startx<0)
			startx = 0;
		if(starty<0)
			starty = 0;
		if(startx>=srcImage->width)
			startx = srcImage->width-1;
		if(starty>= srcImage->height)
			starty = srcImage->height-1;
		if(endx<0)
			endx = 0;
		if(endy<0)
			endy = 0;
		if(endx>=srcImage->width)
			endx = srcImage->width-1;
		if(endy>= srcImage->height)
			endy = srcImage->height-1;
		
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
				if(endx>=srcImage->width)
					endx = srcImage->width-1;
				if(endy>= srcImage->height)
					endy = srcImage->height-1;
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
				if(startx>=srcImage->width)
					startx = srcImage->width-1;
				if(starty>= srcImage->height)
					starty = srcImage->height-1;
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
		
		int xx = StitchSet2[i][0].x/2+StitchSet2[i][1].x/2;
		int yy = StitchSet2[i][0].y/2+StitchSet2[i][1].y/2;
		if(xx<0)
			xx=0;
		if(xx>=srcImage->width)
			xx = srcImage->width-1;
		if(yy<0)
			yy=0;
		if(yy>=srcImage->height)
			yy = srcImage->height-1;
		double Angle = -VectorField[yy][xx];
		double HorizontalDistance = (double)(StitchSet2[i][1].x - StitchSet2[i][0].x);
		double VerticalDistance = (double)(StitchSet2[i][1].y - StitchSet2[i][0].y);
		double Distance = OS.length;
		CvPoint middle;
		middle.x = (StitchSet2[i][1].x + StitchSet2[i][0].x)/2.0;
		middle.y = (StitchSet2[i][1].y + StitchSet2[i][0].y)/2.0;
		double p=(rand()%100)*0.01;
		int startx,starty,endx,endy;
		Angle = Angle + OS.beta +((double)(rand()%45)-22.5) * OS.chaosExtent*pi/180.0;
		startx = middle.x - Distance/2.0*(1+p)*cos(Angle);
		starty = middle.y - Distance/2.0*(1+p)*sin(Angle);
		endx = middle.x + Distance/2.0*(1+p)*cos(Angle);
		endy = middle.y + Distance/2.0*(1+p)*sin(Angle);
		if(startx<0)
			startx = 0;
		if(starty<0)
			starty = 0;
		if(startx>=srcImage->width)
			startx = srcImage->width-1;
		if(starty>= srcImage->height)
			starty = srcImage->height-1;
		if(endx<0)
			endx = 0;
		if(endy<0)
			endy = 0;
		if(endx>=srcImage->width)
			endx = srcImage->width-1;
		if(endy>= srcImage->height)
			endy = srcImage->height-1;
		
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
				if(endx>=srcImage->width)
					endx = srcImage->width-1;
				if(endy>= srcImage->height)
					endy = srcImage->height-1;
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
				if(startx>=srcImage->width)
					startx = srcImage->width-1;
				if(starty>= srcImage->height)
					starty = srcImage->height-1;
				if(contour[starty][startx]==1)
					break;
			}
			StitchSet2[i][1].x = endx;
			StitchSet2[i][0].x = startx;
			StitchSet2[i][1].y = endy;
			StitchSet2[i][0].y = starty;
		}

	}
	for(int i=0;i<StitchSet1.size();i++)
	{
		CvScalar col,mid;
		CvPoint p1,p2;
		p1.x = StitchSet1[i][0].x;
		p1.y = StitchSet1[i][0].y;
		p2.x = StitchSet1[i][1].x;
		p2.y = StitchSet1[i][1].y;
		mid = cvGet2D(seg,(p1.y+p2.y)/2,(p1.x+p2.x)/2);
		col = cvGet2D(srcImage,(p1.y+p2.y)/2,(p1.x+p2.x)/2);
		SimuLine SL = SimuLine(p1,p2,col,1);
		simuLineSet.push_back(SL);

	}
	for(int i=0;i<StitchSet2.size();i++)
	{
		CvScalar col,mid;
		CvPoint p1,p2;
		p1.x = StitchSet2[i][0].x;
		p1.y = StitchSet2[i][0].y;
		p2.x = StitchSet2[i][1].x;
		p2.y = StitchSet2[i][1].y;
		mid = cvGet2D(seg,(p1.y+p2.y)/2,(p1.x+p2.x)/2);
		col = cvGet2D(srcImage,(p1.y+p2.y)/2,(p1.x+p2.x)/2);
		SimuLine SL = SimuLine(p1,p2,col,1);
		simuLineSet.push_back(SL);

	}
	
	//for(int k=0;k<=StitchSet1.size()-1;k++)
	//{
	//	CvScalar col,mid;
	//	CvPoint p1,p2;
	//	p1.x = StitchSet1[k][0].x;
	//	p1.y = StitchSet1[k][0].y;
	//	p2.x = StitchSet1[k][1].x;
	//	p2.y = StitchSet1[k][1].y;
	//	mid = cvGet2D(seg,(p1.y+p2.y)/2,(p1.x+p2.x)/2);
	//	col = cvGet2D(srcImage,(p1.y+p2.y)/2,(p1.x+p2.x)/2);
	//	//col1=MCT.FindNearestColor(col1);
	//	if(mid.val[0]==255)
	//	{
	//		cvLine(realdst, StitchSet1[k][0],StitchSet1[k][1],col, 1, 1, 0);
	//		//realimg.drawRealStitch(realdst,StitchSet1[k][0].x,StitchSet1[k][0].y,StitchSet1[k][1].x,StitchSet1[k][1].y,RGB(col.val[2],col.val[1],col.val[0]));
	//	}
	//}
	//for(int k=0;k<=StitchSet2.size()-1;k++)
	//{
	//	CvScalar col,mid;
	//	CvPoint p1,p2;
	//	p1.x = StitchSet2[k][0].x;
	//	p1.y = StitchSet2[k][0].y;
	//	p2.x = StitchSet2[k][1].x;
	//	p2.y = StitchSet2[k][1].y;
	//	mid = cvGet2D(seg,(p1.y+p2.y)/2,(p1.x+p2.x)/2);
	//	col = cvGet2D(srcImage,(p1.y+p2.y)/2,(p1.x+p2.x)/2);
	//	//col1=MCT.FindNearestColor(col1);
	//	if(mid.val[0]==255)
	//	{
	//		cvLine(realdst, StitchSet2[k][0],StitchSet2[k][1],col, 1, 1, 0);
	//		//realimg.drawRealStitch(realdst,StitchSet2[k][0].x,StitchSet2[k][0].y,StitchSet2[k][1].x,StitchSet2[k][1].y,RGB(col.val[2],col.val[1],col.val[0]));
	//	}
	//}
	//cvSaveImage("stitch.jpg",realdst);
	//cvReleaseImage(&realdst);
	cvReleaseImage(&seg);
	for(int i=0;i<srcImage->height;i++)
	{
		delete [srcImage->width]contour[i];
		contour[i]=NULL;
	}
	delete [srcImage->height]contour;
	contour=NULL;
	printf("Finished calculating OrderlessStitch.\n");
}


void CMagicCabsineSimulateData_Test::ComputeSimulateData()
{
	if(!isPrepared)
	{
		PrepareSimulateData();
	}
	simuLines.clear();
	vector<vector<vector<int>>> regionMasks;
	theMakeTable->GetRegionMasks(regionMasks);
	vector<CvScalar> regionAverageColor;
	theMakeTable->GetPortionProperty_AverageColor(regionAverageColor);
	vector<int> regionArea;
	theMakeTable->GetRegionArea(regionArea);
	maxRegionNum = regionMasks.size()-1;
	maxLevelNum = 3;
	vector<SimuLineSet> emptyset;
	simuLines.push_back(emptyset);
	for(int i = 1;i<regionMasks.size();i++)
	{
		vector<SimuLineSet> tempSet;
		for(int j=0;j<maxLevelNum;j++)
		{
			if (theMakeTable->IsRegionFront(i))
			{
				ChaosStitch* CS = new ChaosStitch;
				CS->density = (double)(j+1)/(double)maxLevelNum*0.6;
				CS->chaosExtent = 0.1;
				CS->length = 10;
				CS->theta = pi/6;
				CS->beta = 6.0*pi/180.0;
				CS->stitchName = "";
				CS->stitchType = STITCH_ChaosVectorFieldCross;
				//CS.density = CS.density * (double)(j+1)/3.0;
				SimuLineSet SS;
				SS.stitchType = STITCH_ChaosVectorFieldCross;
				SS.mainColor = regionAverageColor[i];
				SS.regionArea = regionArea[i];
				SS.threadType = THREAD_TYPE1;
				SS.stitchPoint = (void*)CS;
				DrawSimuLinesInChaosRegion(regionMasks[i],SS.lineSet,(*CS));
				tempSet.push_back(SS);
			}
			else
			{
				OrderlessStitch* OS = new OrderlessStitch;
				OS->density = (double)(j+1)/(double)maxLevelNum*0.6;
				OS->chaosExtent = 0.8;
				OS->length = 10;
				OS->theta = pi/6;
				OS->beta = pi/3;
				OS->stitchName = "";
				OS->stitchType = STITCH_OrderlessCross;
				//CS.density = CS.density * (double)(j+1)/3.0;
				SimuLineSet SS;
				SS.mainColor = regionAverageColor[i];
				SS.regionArea = regionArea[i];
				SS.threadType = THREAD_TYPE1;
				SS.stitchType = STITCH_OrderlessCross;
				SS.stitchPoint = (void*)OS;
				DrawSimuLinesInOrderlessRegion(regionMasks[i],SS.lineSet,(*OS));
				tempSet.push_back(SS);
			}
			
			
		}
		simuLines.push_back(tempSet);
	}
	//计算所有的显示图像
	
	DrawDisplayImage();
	for(int i=0;i<maxLevelNum;i++)
	{
		displayLevelImage.push_back(NULL);
		DrawLevelImage(i);
	}


	isCalced=true;
}

void CMagicCabsineSimulateData_Test::SaveSimulateData()
{
	//目前暂时保存在文件中
// 	SaveSimulateDataFile(theApp.GetDefaultPath()+"SIMULATELINESres.txt");
	SaveSimulateDataFile(theApp.GetProjectPath()+"SIMULATELINESres.txt");
}

void CMagicCabsineSimulateData_Test::LoadSimulateData()
{
	//目前暂时先从文件中读取
// 	LoadSimulateDataFile(theApp.GetDefaultPath()+"SIMULATELINESres.txt");
	LoadSimulateDataFile(theApp.GetProjectPath()+"SIMULATELINESres.txt");
}

void CMagicCabsineSimulateData_Test::SaveSimulateDataFile(string filepath)
{
	if(!isCalced)
	{
		ComputeSimulateData();
	}

	int i,j,k,tempInt1,tempInt2,tempInt3;
	ofstream fout(filepath);
	fout<<srcImage->height<<' '<<srcImage->width<<' '
		<<maxRegionNum<<' '<<maxLevelNum<<' ';
	k=0;
	for(i=1;i<=maxRegionNum;i++)
	{
		for(j=0;j<maxLevelNum;j++)
		{
			k+=simuLines[i][j].lineSet.size();
		}
	}
	fout<<k<<' '<<endl;
	for(i=0;i<srcImage->height;i++)
	{
		for(j=0;j<srcImage->width;j++)
		{
			fout<<splitMatrix[i][j]<<' ';
		}
		fout<<endl;
	}
	for(i=1;i<=maxRegionNum;i++)
	{
		tempInt1=(int)(simuLines[i][0].mainColor.val[0]);
		tempInt2=(int)(simuLines[i][0].mainColor.val[1]);
		tempInt3=(int)(simuLines[i][0].mainColor.val[2]);
		fout<<simuLines[i][0].regionArea<<' '
			<<tempInt1<<' '<<tempInt2<<' '<<tempInt3;
		if(simuLines[i][0].threadType==THREAD_TYPE1)
		{
			fout<<" 1"<<endl;
		}
		else
		{
			fout<<" 2"<<endl;
		}
		//fout<<maxLevelNum<<endl;//已经在文件开始时输出过
		for(j=0;j<maxLevelNum;j++)
		{
			ChaosStitch *tp1=NULL;
			OrderlessStitch *tp2=NULL;
			switch (simuLines[i][j].stitchType)
			{
			case STITCH_ChaosVerticalCross:
				fout<<"1 ";
				tp1=(ChaosStitch *)(simuLines[i][j].stitchPoint);
				if(tp1==NULL)
				{
					break;
				}
				fout<<tp1->density<<' '
					<<tp1->length<<' '
					<<tp1->chaosExtent<<' '
					<<tp1->theta<<' '
					<<tp1->beta<<endl;
				fout<<tp1->stitchName<<endl;
				tp1=NULL;
				break;
			case STITCH_ChaosHorizontalCross:
				fout<<"2 ";
				tp1=(ChaosStitch *)(simuLines[i][j].stitchPoint);
				if(tp1==NULL)
				{
					break;
				}
				fout<<tp1->density<<' '
					<<tp1->length<<' '
					<<tp1->chaosExtent<<' '
					<<tp1->theta<<' '
					<<tp1->beta<<endl;
				fout<<tp1->stitchName<<endl;
				tp1=NULL;
				break;
			case STITCH_ChaosVectorFieldCross:
				fout<<"3 ";
				tp1=(ChaosStitch *)(simuLines[i][j].stitchPoint);
				if(tp1==NULL)
				{
					break;
				}
				fout<<tp1->density<<' '
					<<tp1->length<<' '
					<<tp1->chaosExtent<<' '
					<<tp1->theta<<' '
					<<tp1->beta<<endl;
				fout<<tp1->stitchName<<endl;
				tp1=NULL;
				break;
			case STITCH_OrderlessCross:
				fout<<"4 ";
				tp2=(OrderlessStitch *)(simuLines[i][j].stitchPoint);
				if(tp2==NULL)
				{
					break;
				}
				fout<<tp2->density<<' '
					<<tp2->length<<' '
					<<tp2->chaosExtent<<' '
					<<tp2->theta<<' '
					<<tp2->beta<<endl;
				fout<<tp2->stitchName<<endl;
				tp2=NULL;
				break;
			case STITCH_Other:
				fout<<"5 "<<endl;
				break;
			default:
				break;
			}
		}
	}
	for(i=1;i<=maxRegionNum;i++)
	{
		for(j=0;j<maxLevelNum;j++)
		{
			vector<SimuLine> &lineset=simuLines[i][j].lineSet;
			for(k=0;k<lineset.size();k++)
			{
				fout<<lineset[k].startPoint.x<<' '
					<<lineset[k].startPoint.y<<' '
					<<lineset[k].endPoint.x<<' '
					<<lineset[k].endPoint.y<<' ';
				tempInt1=(int)(lineset[k].color.val[0]);
				tempInt2=(int)(lineset[k].color.val[1]);
				tempInt3=(int)(lineset[k].color.val[2]);
				fout<<tempInt1<<' '<<tempInt2<<' '<<tempInt3<<' ';
				fout<<lineset[k].thickness<<' '
					<<i<<' '<<j<<endl;
			}
		}
	}
	fout.close();
}

void CMagicCabsineSimulateData_Test::LoadSimulateDataFile(string filepath)
{
	//读出保存的模拟数据
	int i,j,k,numOfLines,tempInt1,tempInt2,tempInt3,tempInt4;
	ifstream fin(filepath);
	fin>>i>>j>>maxRegionNum>>maxLevelNum>>numOfLines;
	int height=srcImage->height;
	int width=srcImage->width;

	vector<int> tempIntVector(width,0);
	splitMatrix.clear();
	for(i=0;i<height;i++)
	{
		for(j=0;j<width;j++)
		{
			fin>>tempIntVector[j];
		}
		splitMatrix.push_back(tempIntVector);
	}

	SimuLine tempLine;//每一条线
	SimuLineSet tempLineSet;//[区域号][层次号]线集合
	vector<SimuLineSet> tempLineSetVector;
	simuLines.clear();
	const int SizeOfStr=300;
	char str[SizeOfStr];

	simuLines.push_back(tempLineSetVector);//区域号下标由1开始,这里先填充0下标元素
	for(i=1;i<=maxRegionNum;i++)
	{
		fin>>tempLineSet.regionArea>>tempInt1>>tempInt2>>tempInt3;
		tempLineSet.mainColor.val[0]=tempInt1;
		tempLineSet.mainColor.val[1]=tempInt2;
		tempLineSet.mainColor.val[2]=tempInt3;
		fin>>k;
		if(k==1)
		{
			tempLineSet.threadType=THREAD_TYPE1;
		}
		else
		{
			tempLineSet.threadType=THREAD_TYPE2;
		}
		for(j=0;j<maxLevelNum;j++)
		{
			fin>>k;
			ChaosStitch *tp1=NULL;
			OrderlessStitch *tp2=NULL;
			switch (k)
			{
			case 1:
				tempLineSet.stitchType=STITCH_ChaosVerticalCross;
				tp1=new ChaosStitch();
				fin>>tp1->density
					>>tp1->length
					>>tp1->chaosExtent
					>>tp1->theta
					>>tp1->beta;
				fin.getline(str,SizeOfStr);
				fin.getline(str,SizeOfStr);
				tp1->stitchName=string(str);
				tempLineSet.stitchPoint=(void *)tp1;
				tp1=NULL;
				break;
			case 2:
				tempLineSet.stitchType=STITCH_ChaosHorizontalCross;
				tp1=new ChaosStitch();
				fin>>tp1->density
					>>tp1->length
					>>tp1->chaosExtent
					>>tp1->theta
					>>tp1->beta;
				fin.getline(str,SizeOfStr);
				fin.getline(str,SizeOfStr);
				tp1->stitchName=string(str);
				tempLineSet.stitchPoint=(void *)tp1;
				tp1=NULL;
				break;
			case 3:
				tempLineSet.stitchType=STITCH_ChaosVectorFieldCross;
				tp1=new ChaosStitch();
				fin>>tp1->density
					>>tp1->length
					>>tp1->chaosExtent
					>>tp1->theta
					>>tp1->beta;
				fin.getline(str,SizeOfStr);
				fin.getline(str,SizeOfStr);
				tp1->stitchName=string(str);
				tempLineSet.stitchPoint=(void *)tp1;
				tp1=NULL;
				break;
			case 4:
				tempLineSet.stitchType=STITCH_OrderlessCross;
				tp2=new OrderlessStitch();
				fin>>tp2->density
					>>tp2->length
					>>tp2->chaosExtent
					>>tp2->theta
					>>tp2->beta;
				fin.getline(str,SizeOfStr);
				fin.getline(str,SizeOfStr);
				tp2->stitchName=string(str);
				tempLineSet.stitchPoint=(void *)tp2;
				tp2=NULL;
				break;
			default:
				tempLineSet.stitchType=STITCH_Other;
				tempLineSet.stitchPoint=NULL;
				break;
			}
		}
		vector<SimuLineSet> tempLineSetVector(maxLevelNum,tempLineSet);//[区域号]层次
		simuLines.push_back(tempLineSetVector);
	}
	for(k=0;k<numOfLines;k++)
	{
		fin>>tempInt1>>tempInt2>>tempInt3>>tempInt4;
		tempLine.startPoint=cvPoint(tempInt1,tempInt2);
		tempLine.endPoint=cvPoint(tempInt3,tempInt4);
		fin>>tempInt1>>tempInt2>>tempInt3>>tempInt4;
		tempLine.color=cvScalar(tempInt1,tempInt2,tempInt3);
		tempLine.thickness=tempInt4;
		fin>>i>>j;
		simuLines[i][j].lineSet.push_back(tempLine);
	}

	//恢复针法库和生成表的数据
	PrepareSimulateData();

	/*显示图像现在由save函数保存,不需要每次都进行计算
	//计算所有的显示图像
	DrawDisplayImage();
	for(i=0;i<maxLevelNum;i++)
	{
		displayLevelImage.push_back(NULL);
		DrawLevelImage(i);
	}
	*/
	//加下面的循环是为了程序不出错
	for(i=0;i<maxLevelNum;i++)
	{
		displayLevelImage.push_back(NULL);
	}

	fin.close();
	isPrepared=true;
	isCalced=true;
}

void CMagicCabsineSimulateData_Test::DeleteSimulateData()
{
	simuLines.clear();
}

int CMagicCabsineSimulateData_Test::GetRegionNum(int xx,int yy)
{
	if(xx<0||xx>=srcImage->height||yy<0||yy>=srcImage->width)
	{
		return 0;//坐标超出图像范围
	}
	return splitMatrix[xx][yy];
}

THREAD_TYPE CMagicCabsineSimulateData_Test::GetThreadType(int regionNum,int levelNum)const
{
	if(regionNum<1||regionNum>maxRegionNum)
	{
		return THREAD_TYPE1;//区域号超出范围
	}
	if(levelNum<0||levelNum>=simuLines[regionNum].size())
	{
		return THREAD_TYPE1;//层次号超出范围
	}
	return simuLines[regionNum][levelNum].threadType;
}

void CMagicCabsineSimulateData_Test::SetThreadType(int regionNum,int levelNum,THREAD_TYPE newType)
{
	if(regionNum<1||regionNum>maxRegionNum)
	{
		return;//区域号超出范围
	}
	if(levelNum<0||levelNum>=simuLines[regionNum].size())
	{
		return;//层次号超出范围
	}
	simuLines[regionNum][levelNum].threadType=newType;
}

int CMagicCabsineSimulateData_Test::GetRegionArea(int regionNum,int levelNum)const
{
	if(regionNum<1||regionNum>maxRegionNum)
	{
		return 0;//区域号超出范围
	}
	if(levelNum<0||levelNum>=simuLines[regionNum].size())
	{
		return 0;//层次号超出范围
	}
	return simuLines[regionNum][levelNum].regionArea;
}

CvScalar CMagicCabsineSimulateData_Test::GetMainColor(int regionNum,int levelNum)const
{
	if(regionNum<1||regionNum>maxRegionNum)
	{
		return cvScalar(0,0,0);//区域号超出范围
	}
	if(levelNum<0||levelNum>=simuLines[regionNum].size())
	{
		return cvScalar(0,0,0);//层次号超出范围
	}
	return simuLines[regionNum][levelNum].mainColor;
}

int CMagicCabsineSimulateData_Test::GetNumOfThread(int regionNum,int levelNum)const
{
	if(regionNum<1||regionNum>maxRegionNum)
	{
		return 0;//区域号超出范围
	}
	if(levelNum<0||levelNum>=simuLines[regionNum].size())
	{
		return 0;//层次号超出范围
	}
	return simuLines[regionNum][levelNum].lineSet.size();
}

void CMagicCabsineSimulateData_Test::DrawLevelImage(int levelIndex)
{
	if(levelIndex<0||levelIndex>=maxLevelNum)
	{
		return;
	}

	CAnalogdisplay realimg;
	string thePath = theApp.GetDefaultPath()+"ConfigFile\\xx5.bmp";
	realimg.textureSyn.loadSample(thePath.c_str());
	CvSize size;
	size.height=srcImage->height*realimg.textureSyn.getThreadWidth();
	size.width=srcImage->width*realimg.textureSyn.getThreadWidth();
	int i,j;
	IplImage *img=cvCreateImage(size,8,3);
	for(i = 0;i<img->width;i++)
	{
		for(j =0 ;j<img->height;j++)
		{
			CvScalar col;
			col.val[2] = 255;col.val[1] = 255;col.val[0] = 255;
			cvSet2D(img,j,i,col);
		}
	}
	
	for(i=1;i<=maxRegionNum;i++)
	{
		vector<SimuLine> &lineSet=simuLines[i][levelIndex].lineSet;
		for(j=0;j<lineSet.size();j++)
		{
			//cvLine(img,lineSet[j].startPoint,lineSet[j].endPoint,lineSet[j].color,lineSet[j].thickness);
			realimg.drawRealStitch(img,lineSet[j].startPoint.x,lineSet[j].startPoint.y,lineSet[j].endPoint.x,lineSet[j].endPoint.y,RGB(lineSet[j].color.val[2],lineSet[j].color.val[1],lineSet[j].color.val[0]));
		}
	}

	if(displayLevelImage[levelIndex]!=NULL)
	{
		cvReleaseImage(&displayLevelImage[levelIndex]);
		displayLevelImage[levelIndex]=NULL;
	}
	displayLevelImage[levelIndex]=img;
}

void CMagicCabsineSimulateData_Test::DrawDisplayImage()
{
	int i,j,k;
	if(displayImage!=NULL)
	{
		cvReleaseImage(&displayImage);
		displayImage=NULL;
	}
	
	CAnalogdisplay realimg;
	string thePath = theApp.GetDefaultPath()+"ConfigFile\\xx5.bmp";
	realimg.textureSyn.loadSample(thePath.c_str());
	CvSize size;
	size.height=srcImage->height*realimg.textureSyn.getThreadWidth();
	size.width=srcImage->width*realimg.textureSyn.getThreadWidth();
	displayImage=cvCreateImage(size,8,3);
	for(i = 0;i<displayImage->width;i++)
	{
		for(j =0 ;j<displayImage->height;j++)
		{
			CvScalar col;
			col.val[2] = 255;col.val[1] = 255;col.val[0] = 255;
			cvSet2D(displayImage,j,i,col);
		}
	}

	for(j=0;j<maxLevelNum;j++)
	{
		for(i=1;i<=maxRegionNum;i++)
		{
			vector<SimuLine> &lineSet=simuLines[i][j].lineSet;
			for(k=0;k<lineSet.size();k++)
			{
				realimg.drawRealStitch(displayImage,lineSet[k].startPoint.x,lineSet[k].startPoint.y,lineSet[k].endPoint.x,lineSet[k].endPoint.y,RGB(lineSet[k].color.val[2],lineSet[k].color.val[1],lineSet[k].color.val[0]));
			}
		}
	}
	//cvSaveImage("stitch.jpg",realdst);

	//for(j=0;j<maxLevelNum;j++)
	//{
	//	for(i=1;i<=maxRegionNum;i++)
	//	{
	//		vector<SimuLine> &lineSet=simuLines[i][j].lineSet;
	//		for(k=0;k<lineSet.size();k++)
	//		{
	//			cvLine(displayImage,lineSet[k].startPoint,lineSet[k].endPoint,lineSet[k].color,lineSet[k].thickness);
	//		}
	//	}
	//}
}

SimuLineSet* CMagicCabsineSimulateData_Test::GetPointOfSimuLineSet(int regionNum,int levelNum)
{
	if(regionNum<=0||regionNum>maxRegionNum)
	{
		return NULL;
	}
	if(levelNum<0||levelNum>=maxLevelNum)
	{
		return NULL;
	}
	return &simuLines[regionNum][levelNum];
}

void CMagicCabsineSimulateData_Test::CreatBlankImage()
{
	if(blankImage!=NULL)
	{
		cvReleaseImage(&blankImage);
		blankImage=NULL;
	}
	blankImage=cvCloneImage(srcImage);
	CvScalar whiteColor=cvScalar(255,255,255);
	int height=srcImage->height;
	int width=srcImage->width;
	int i,j;
	for(i=0;i<height;i++)
	{
		for(j=0;j<width;j++)
		{
			cvSet2D(blankImage,i,j,whiteColor);
		}
	}
}

void CMagicCabsineSimulateData_Test::ChangeMainColor(int regionNum,int levelNum,CvScalar theColor)
{
	if(regionNum<1||regionNum>maxRegionNum)
	{
		return;//区域号超出范围
	}
	if(levelNum<0||levelNum>=simuLines[regionNum].size())
	{
		return;//层次号超出范围
	}
	simuLines[regionNum][levelNum].mainColor=theColor;
	vector<SimuLine> &tempLines=simuLines[regionNum][levelNum].lineSet;
	int i;
	for(i=0;i<tempLines.size();i++)
	{
		ChangeSingleColor(tempLines[i].color,theColor);
	}

	//重绘叠加图像
	DrawDisplayImage();
	//重绘改变的层次图像
	DrawLevelImage(levelNum);
}

void CMagicCabsineSimulateData_Test::ChangeSingleColor
	(CvScalar &toChangeColor,const CvScalar &affectColor)
{
	int blueColor=(int)(toChangeColor.val[0]+affectColor.val[0]);
	int greenColor=(int)(toChangeColor.val[1]+affectColor.val[1]);
	int redColor=(int)(toChangeColor.val[2]+affectColor.val[2]);
	if(blueColor>510)
	{
		blueColor=510;
	}
	if(greenColor>510)
	{
		greenColor=510;
	}
	if(redColor>510)
	{
		redColor=510;
	}
	toChangeColor.val[0]=blueColor/2;
	toChangeColor.val[1]=greenColor/2;
	toChangeColor.val[2]=redColor/2;
}

void CMagicCabsineSimulateData_Test::DrawRegionMask(int regID,IplImage* mask)
{
	vector< vector<int> > theRegionMask;
	this->theMakeTable->GetRegionMask(regID,theRegionMask);
	CvSize size;
	size.height = theRegionMask.size();
	size.width = theRegionMask[0].size();
	for(int i=0;i<theRegionMask.size();i++)
	{
		for(int j=0;j<theRegionMask[i].size();j++)
		{
			CvScalar col;
			if(theRegionMask[i][j] == 1)
			{
				col = cvGet2D(srcImage,i,j);
				cvSet2D(mask,i,j,col);
			}
			else
			{
				col.val[0] = 255;col.val[1] = 255;col.val[2] = 255;
				cvSet2D(mask,i,j,col);
			}
		}
	}
}
