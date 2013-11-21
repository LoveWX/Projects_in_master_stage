#ifndef thedefinition
#define thedefinition

#include <vector>
#include <cmath>
using namespace std;

struct Point
{
	double xx,yy;
};

struct Segment
{
	Point pa,pb;
};

Point operator -(const Point &pa,const Point &pb);
bool operator ==(const Point &pa,const Point &pb);

double DotProduct(Point pa,Point pb);
double GetLengthOfVector(Point pa);
Point GetVerticalVector(Point pa);

struct Matrix42
{
	double Aj[4][2];
};

#endif
