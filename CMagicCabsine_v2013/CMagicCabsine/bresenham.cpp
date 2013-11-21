#include "stdafx.h"
#include "bresenham.h"
#define sign(x) (x)>=0?1:-1
void bresenham (vector<CvPoint>  *pArr,int x1, int y1, int x2, int y2)
{
	int x,y,s1,s2,increx,increy,temp,interchange;
	int e,i;
	x=x1;
	y=y1;
	s1=sign(x2-x1);
	s2=sign(y2-y1);
	increx=abs(x2-x1)+1;
	increy=abs(y2-y1)+1;
	if(increx==0&&increy==0)
	{
		pArr->push_back(cvPoint(x1,y1));
		return;
	}

	if (increy>increx)
	{
		temp=increx;
		increx=increy;
		increy=temp;
		interchange=1;
	}
	else
		interchange=0;
	e=increy+increy-increx;
	for (i=1;i<=increx;i++)
	{
		pArr->push_back(cvPoint(x,y));
		if (e>=0)
		{
			if(interchange==1)
				x=x+s1;
			else
				y=y+s2;
			e=e-2*increx;
		}
		if (interchange==1)
			y=y+s2;
		else
			x=x+s1;
		e=e+increy+increy;
	}
}


void bresenham (vector<CPoint>  *pArr,int x1, int y1, int x2, int y2)
{
	int x,y,s1,s2,increx,increy,temp,interchange;
	int e,i;
	x=x1;
	y=y1;
	s1=sign(x2-x1);
	s2=sign(y2-y1);
	increx=abs(x2-x1)+1;
	increy=abs(y2-y1)+1;
	if(increx==0&&increy==0)
	{
		pArr->push_back(CPoint(x1,y1));
		return;
	}

	if (increy>increx)
	{
		temp=increx;
		increx=increy;
		increy=temp;
		interchange=1;
	}
	else
		interchange=0;
	e=increy+increy-increx;
	for (i=1;i<=increx;i++)
	{
		pArr->push_back(CPoint(x,y));
		if (e>=0)
		{
			if(interchange==1)
				x=x+s1;
			else
				y=y+s2;
			e=e-(increx+increx);
		}
		if (interchange==1)
			y=y+s2;
		else
			x=x+s1;
		e=e+(increy+increy);
	}
}



void BresenhamDrawLine(vector<CvPoint> &pointSequence)
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


void BresenhamConnectPoints(vector<CvPoint> &points,int xa,int ya,int xb,int yb)
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