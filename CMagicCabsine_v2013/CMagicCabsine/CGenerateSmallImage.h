#pragma once
#include <vector>
#include <cv.h>
#include <highgui.h>
#include "analogdisplay.h"
#define PI  3.14159f
using namespace std;
class CGenerateSmallImage
{
public:
	CGenerateSmallImage(/*int w,int h*/);
	~CGenerateSmallImage();
	double FillContour(IplImage* contour,double percentage,double alpha1,double alpha2,double ratio);
	void processLine(vector<CvPoint>* line,IplImage * contour, int left, int top, int right, int bottom, int k);
	void AddStitch1(CvPoint p1, CvPoint p2);
	void AddStitch2(CvPoint p1, CvPoint p2);
	IplImage* GetImg1(double density, double length, double chaosextent, double theta, double beta);
	IplImage* GetImg2(double density, double length, double chaosextent, double theta, double beta);
	float** VectorField;

public:
	int width;
	int height;	
	vector<vector<CvPoint>> stitches1;
	vector<vector<CvPoint>> stitches2;
	vector<vector<CvPoint>> StitchSet1;										
	vector<vector<CvPoint>> StitchSet2;
	CAnalogdisplay realimg;
	bool isvector;
	IplImage* src;
};