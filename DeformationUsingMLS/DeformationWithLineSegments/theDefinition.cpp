#include "theDefinition.h"

Point operator -(const Point &pa,const Point &pb)
{
	Point temp;
	temp.xx=pa.xx-pb.xx;
	temp.yy=pa.yy-pb.yy;
	return temp;
}

bool operator ==(const Point &pa,const Point &pb)
{
	double t1=pa.xx-pb.xx,t2=pa.yy-pb.yy;
	double eps=1e-8;
	if(t1<0)
	{
		t1=-t1;
	}
	if(t2<0)
	{
		t2=-t2;
	}
	return (t1<eps) && (t2<eps);
}

double DotProduct(Point pa,Point pb)
{
	return pa.xx*pb.xx+pa.yy*pb.yy;
}

double GetLengthOfVector(Point pa)
{
	return sqrt(pa.xx*pa.xx+pa.yy*pa.yy);
}

Point GetVerticalVector(Point pa)
{
	Point temp;
	temp.xx=-pa.yy;
	temp.yy=pa.xx;
	return temp;
}
