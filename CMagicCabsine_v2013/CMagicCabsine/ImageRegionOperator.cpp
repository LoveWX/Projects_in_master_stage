#include "stdafx.h"
#include "ImageRegionOperator.h"

/*
class ImageRegionOperator
{
public:
	ImageRegionOperator();//���캯��,��Ҫ����SetImageAndMatrix()���г�ʼ��
	ImageRegionOperator(IplImage *theImage,const vector< vector<int> > &theMatrix);//���ι��캯��
	~ImageRegionOperator();//��������
	void SetImageAndMatrix(IplImage *theImage,const vector< vector<int> > &theMatrix);//��ͼƬ�Ͷ�Ӧ���������������
	
	IplImage* GetDisplayImage();							//��ȡ��ʾ�õĽ��ͼƬ
	void GetAreaMatrix(vector< vector<int> > &theMatrix);	//��õ�ǰ�������
	//�����������,����ȵ���RearrangeRegionNum()�������������,�������ŵ���������
	int GetNumOfRegions();
	
	//�����������,ѡ�е�������1,����������0
	void CalcMasks(int regionNum,vector< vector<int> > &theMasks);					//ѡ���������regionNumָ��������
	void CalcMasks(const CvPoint &thePoint,vector< vector<int> > &theMasks);		//ѡ��thePoint���ڵ�����
	void CalcMasks(const vector<CvPoint> &thePoints,vector< vector<int> > &theMasks);//ѡ��thePointsɨ������������
	
	void CalcAverageColor();//����areaMatrix����ƽ��ɫ
	
	//����BresenhamConnectPoints()��pointSequence���ڵ�������Խ�pointSequence����8�ڽӵ���
	void BresenhamDrawLine(vector<CvPoint> &pointSequence);
	
	
	void RegionMerge(const vector<CvPoint> &pointSequence);			//����ϲ�,�ϲ�pointSequenceɨ������������
	void RegionSplit(const vector<CvPoint> &pointSequence);			//����ָ�,pointSequence��Ϊ�µı߽��������ָ�
	void RegionCircle(const vector<CvPoint> &pointSequence);		//Ȧѡ����,pointSequenceȦ�е������Ϊ������
	void RegionModifyBoundary(const vector<CvPoint> &pointSequence);//�߽��޸�
	
	void RearrangeRegionNum();//�������������,ʹ��Ϊ[1,maxRegionNum]
	
protected:
	IplImage *srcImage;//����������Ӧ��ԭʼͼ��
	IplImage *displayImage;//��ʾ�ý��ͼƬ,ÿ��������������и���
	int height;//ͼ��߶�,��������һά����
	int width;//ͼ����,�������ڶ�ά����
	vector< vector<int> > areaMatrix;//�������
	int maxRegionNum;//��ǰ��������
	
	//ʹ��Bresenham����������(xa,ya)��(xb,yb),�����ĵ㰴�����points��
	void BresenhamConnectPoints(vector<CvPoint> &points,int xa,int ya,int xb,int yb);
	int GetMaxRegionNum();					//��õ�ǰ��������,�������ڲ�����
	bool IsInScale(CvPoint thePoint);		//�ж�thePoint�Ƿ������������
	void PutPointInScale(CvPoint &thePoint);//��thePoint�Ż����������
	
	//ר�õĵ��ú���,��ĳЩ����ϸ���ϻ��в���
	//�������,����RegionSplit()����
	void FillingRegion(vector< vector<int> > &theMasks,CvPoint seedPoint,int newRegionNum);
	//���Ȧ�е�����,����RegionCircle()��RegionModifyBoundaryRegionModifyBoundary()����
	void GetCircleRegionMasks(vector< vector<int> > &theMasks,CvPoint seedPoint);
	//�����䲢�������ص����,����RegionModifyBoundary()����
	int FillingRegionCountingPoints(vector< vector<int> > &theMasks,CvPoint seedPoint,int newNum);
	
	//����Ϊ�����ú���,����ɾ��
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
 		//PutPointInScale(points[i]);//�����֤��������겻��Խ�����ñ����
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

	/*theMasks�и���ֵ���������
	// 0 :����Ҫ����ĵ�
	// 1 :��Ҫ������δ����ĵ�
	// 2 :������ı��
	// 3 :�ָ����ϵĵ�
	// 4 :�Ѿ��ڱ�Ƕ����еĵ�
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
		
		//����ǰ��
		areaMatrix[xx][yy]=newRegionNum;
		theMasks[xx][yy]=2;//��ʾ�õ��Ѿ����
		
		//����ǰ���Ϸ��ĵ�������,ֱ���Ѿ�������ĵ�����Ѿ���������еĵ�Ϊֹ
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
			theMasks[i][yy]=4;//��ʾΪ�õ��Ѿ��ڴ��������
		}
		
		//����ǰ����ߵĵ�������,ֱ���Ѿ�������ĵ�����Ѿ���������еĵ�Ϊֹ
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
			theMasks[xx][j]=4;//��ʾΪ�õ��Ѿ��ڴ��������
		}
		
		//����ǰ���·��ĵ�������,ֱ���Ѿ�������ĵ�����Ѿ���������еĵ�Ϊֹ
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
			theMasks[i][yy]=4;//��ʾΪ�õ��Ѿ��ڴ��������
		}
		
		//����ǰ���ұߵĵ�������,ֱ���Ѿ�������ĵ�����Ѿ���������еĵ�Ϊֹ
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
			theMasks[xx][j]=4;//��ʾΪ�õ��Ѿ��ڴ��������
		}
	}
}

void ImageRegionOperator::RegionSplit(const vector<CvPoint> &pointSequence)
{
	if(pointSequence.size()==0)
	{
		return;
	}

	/*theMasks�и���ֵ���������
	// 0 :����Ҫ����ĵ�
	// 1 :��Ҫ������δ����ĵ�
	// 2 :������ı��
	// 3 :�ָ����ϵĵ�
	// 4 :�Ѿ��ڱ�Ƕ����еĵ�
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

		//���õ��Ϸ��ĵ��Ƿ������Ϊ���ӵ�
		xx=tempPoint.x-1;
		yy=tempPoint.y;
		if(xx>=0&&theMasks[xx][yy]==1
			&&areaMatrix[tempPoint.x][tempPoint.y]==tempRegionNum)
		{
			FillingRegion(theMasks,cvPoint(xx,yy),++maxRegionNum);
		}
		//���õ���ߵĵ��Ƿ������Ϊ���ӵ�
		xx=tempPoint.x;
		yy=tempPoint.y-1;
		if(yy>=0&&theMasks[xx][yy]==1
			&&areaMatrix[tempPoint.x][tempPoint.y]==tempRegionNum)
		{
			FillingRegion(theMasks,cvPoint(xx,yy),++maxRegionNum);
		}
		//���õ��·��ĵ��Ƿ������Ϊ���ӵ�
		xx=tempPoint.x+1;
		yy=tempPoint.y;
		if(xx<height&&theMasks[xx][yy]==1
			&&areaMatrix[tempPoint.x][tempPoint.y]==tempRegionNum)
		{
			FillingRegion(theMasks,cvPoint(xx,yy),++maxRegionNum);
		}
		//���õ��ҷ��ĵ��Ƿ������Ϊ���ӵ�
		xx=tempPoint.x;
		yy=tempPoint.y+1;
		if(yy<width&&theMasks[xx][yy]==1
			&&areaMatrix[tempPoint.x][tempPoint.y]==tempRegionNum)
		{
			FillingRegion(theMasks,cvPoint(xx,yy),++maxRegionNum);
		}
	}

	/*
	//��һ�δ��봦����ѡ������8��ͨ����4��ͨ�����ص�
	int j;
	for(i=0;i<height;i++)
	{
		for(j=0;j<width;j++)
		{
			if(theMasks[i][j]==1)
			{
				//������δ����ĵ�,�����{8����-4����}�������Ѿ�����ĵ�
				
				//���õ����ϵĵ��Ƿ��ѱ������
				xx=i-1;
				yy=j-1;
				if(xx>=0&&yy>=0&&theMasks[xx][yy]==2)
				{
					FillingRegion(theMasks,cvPoint(xx,yy),areaMatrix[xx][yy]);
				}
				//���õ����ϵĵ��Ƿ��ѱ������
				xx=i-1;
				yy=j+1;
				if(xx>=0&&yy<width&&theMasks[xx][yy]==2)
				{
					FillingRegion(theMasks,cvPoint(xx,yy),areaMatrix[xx][yy]);
				}
				//���õ����µĵ��Ƿ��ѱ������
				xx=i+1;
				yy=j-1;
				if(xx<height&&yy>=0&&theMasks[xx][yy]==2)
				{
					FillingRegion(theMasks,cvPoint(xx,yy),areaMatrix[xx][yy]);
				}
				//���õ����µĵ��Ƿ��ѱ������
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
	
	/*theMasks�и���ֵ���������(��Ҫ������������)
	// 0 :��Ҫ������δ����ĵ�
	// 1 :�������ʱ������ĵ�
	// 2 :
	// 3 :�ָ����ϵĵ�
	// 4 :�Ѿ��ڱ�Ƕ����еĵ�
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
		
		//����ǰ��
		theMasks[xx][yy]=1;//��ʾ�õ��Ѿ����
		
		//����ǰ���Ϸ��ĵ�������,ֱ���Ѿ�������ĵ�����Ѿ���������еĵ�Ϊֹ
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
			theMasks[i][yy]=4;//��ʾΪ�õ��Ѿ��ڴ��������
		}
		
		//����ǰ����ߵĵ�������,ֱ���Ѿ�������ĵ�����Ѿ���������еĵ�Ϊֹ
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
			theMasks[xx][j]=4;//��ʾΪ�õ��Ѿ��ڴ��������
		}
		
		//����ǰ���·��ĵ�������,ֱ���Ѿ�������ĵ�����Ѿ���������еĵ�Ϊֹ
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
			theMasks[i][yy]=4;//��ʾΪ�õ��Ѿ��ڴ��������
		}
		
		//����ǰ���ұߵĵ�������,ֱ���Ѿ�������ĵ�����Ѿ���������еĵ�Ϊֹ
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
			theMasks[xx][j]=4;//��ʾΪ�õ��Ѿ��ڴ��������
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

	/*theMasks�и���ֵ���������
	// 0 :����Ҫͳ�Ƶĵ�
	// 1 :��Ҫͳ�Ƶ���û��ͳ�Ƶĵ�
	// 2 :�Ѿ�ͳ�ƹ��ĵ�
	// 3 :�ָ����ϵĵ�
	// 4 :�Ѿ��ڱ�Ƕ����еĵ�
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
		
		//����ǰ��
		numOfPoints++;
		theMasks[xx][yy]=2;//�õ���Ϊ�Ѿ�ͳ�ƹ�

		//����ǰ���Ϸ��ĵ�������,ֱ���Ѿ�������ĵ�����Ѿ���������еĵ�Ϊֹ
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
			theMasks[i][yy]=4;//��ʾΪ�õ��Ѿ��ڴ��������
		}
		
		//����ǰ����ߵĵ�������,ֱ���Ѿ�������ĵ�����Ѿ���������еĵ�Ϊֹ
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
			theMasks[xx][j]=4;//��ʾΪ�õ��Ѿ��ڴ��������
		}
		
		//����ǰ���·��ĵ�������,ֱ���Ѿ�������ĵ�����Ѿ���������еĵ�Ϊֹ
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
			theMasks[i][yy]=4;//��ʾΪ�õ��Ѿ��ڴ��������
		}
		
		//����ǰ���ұߵĵ�������,ֱ���Ѿ�������ĵ�����Ѿ���������еĵ�Ϊֹ
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
			theMasks[xx][j]=4;//��ʾΪ�õ��Ѿ��ڴ��������
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
	
	/*theMasks�и���ֵ���������(��Ҫ������������)
	// 0 :��Ҫ������δ����ĵ�
	// 1 :�������ʱ������ĵ�
	// 2 :
	// 3 :�ָ����ϵĵ�
	// 4 :�Ѿ��ڱ�Ƕ����еĵ�
	// >5:newNumָ����������
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
		
		//����ǰ��
		numOfPoints++;
		theMasks[xx][yy]=newNum;//�õ���ΪnewNumָ���������
		
		//����ǰ���Ϸ��ĵ�������,ֱ���Ѿ�������ĵ�����Ѿ���������еĵ�Ϊֹ
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
			theMasks[i][yy]=4;//��ʾΪ�õ��Ѿ��ڴ��������
		}
		
		//����ǰ����ߵĵ�������,ֱ���Ѿ�������ĵ�����Ѿ���������еĵ�Ϊֹ
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
			theMasks[xx][j]=4;//��ʾΪ�õ��Ѿ��ڴ��������
		}
		
		//����ǰ���·��ĵ�������,ֱ���Ѿ�������ĵ�����Ѿ���������еĵ�Ϊֹ
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
			theMasks[i][yy]=4;//��ʾΪ�õ��Ѿ��ڴ��������
		}
		
		//����ǰ���ұߵĵ�������,ֱ���Ѿ�������ĵ�����Ѿ���������еĵ�Ϊֹ
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
			theMasks[xx][j]=4;//��ʾΪ�õ��Ѿ��ڴ��������
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
	//ͳ����ɨ��������ͨ����������ظ���
	int numOfPointsToModify=CountingRegionPoints(thePoints);

	int row=height+2,col=width+2;
	vector<int> tempVector(width,0);
	vector< vector<int> > tempMasks1(height,tempVector);//��һ��������
	vector< vector<int> > tempMasks3(height,tempVector);//�ڶ���������
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
				//û��ɨ����Щ��,����Ҳ�޷����������δɨ��һ������������
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
	int tempRegion=6;//��ʼ����������,�ᶯ̬����
	vector<int> possibleRegion,numOfPoints;
	for(i=0;i<thePoints.size();i++)
	{
		tempPoint=thePoints[i];
		tempPoint.x++;
		tempPoint.y++;

		//���õ��Ϸ��ĵ��Ƿ������Ϊ���ӵ�
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
		//���õ���ߵĵ��Ƿ������Ϊ���ӵ�
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
		//���õ��·��ĵ��Ƿ������Ϊ���ӵ�
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
		//���õ��ұߵĵ��Ƿ������Ϊ���ӵ�
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
			return;//�����߽���ͨ��������߽��ϵĵ�
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
	//����OpenCV�ĵ�����ʹ��16bit�޷�������,����ת��Ϊintʱ��Ҫ���ݰ汾�����޸�
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

