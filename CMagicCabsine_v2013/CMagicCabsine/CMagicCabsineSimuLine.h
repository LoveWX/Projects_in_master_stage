#ifndef cmagiccabsinesimuline
#define cmagiccabsinesimuline

#include <vector>
using namespace std;
#include <cv.h>

struct SimuLine
{
	CvPoint startPoint;
	CvPoint endPoint;
	CvScalar color;
	int thickness;
	SimuLine();
	SimuLine(CvPoint sPoint,CvPoint ePoint);
	SimuLine(CvPoint sPoint,CvPoint ePoint,CvScalar col,int thick);
	SimuLine(const SimuLine &tempLine);
	SimuLine& operator= (const SimuLine& tempLine);
};

#endif
