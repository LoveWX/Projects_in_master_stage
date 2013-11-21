#ifndef __BRESENHAM_H
#define __BRESENHAM_H
#include <cv.h>

#include <vector>
using namespace std;

//使用bresenham直线生成算法计算一针经过的点，存入pArr
void bresenham (vector<CvPoint>  *pArr,int x1, int y1, int x2, int y2);
void bresenham (vector<CPoint>  *pArr,int x1, int y1, int x2, int y2);
void BresenhamDrawLine(vector<CvPoint> &pointSequence);


void BresenhamConnectPoints(vector<CvPoint> &points,int xa,int ya,int xb,int yb);
#endif