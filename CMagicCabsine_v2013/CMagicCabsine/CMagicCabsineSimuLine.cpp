#include "stdafx.h"

#include "CMagicCabsineSimuLine.h"

SimuLine::SimuLine()
{
	startPoint=cvPoint(0,0);
	endPoint=cvPoint(0,0);
	color=cvScalar(0,0,0);
	thickness=1;
}

SimuLine::SimuLine(CvPoint sPoint,CvPoint ePoint)
{
	startPoint=sPoint;
	endPoint=ePoint;
	color=cvScalar(0,0,0);
	thickness=1;
}

SimuLine::SimuLine(CvPoint sPoint,CvPoint ePoint,CvScalar col,int thick)
{
	startPoint=sPoint;
	endPoint=ePoint;
	color=col;
	thickness=thick;
}

SimuLine::SimuLine(const SimuLine &tempLine)
{
	startPoint=tempLine.startPoint;
	endPoint=tempLine.endPoint;
	color=tempLine.color;
	thickness=tempLine.thickness;
}

SimuLine& SimuLine::operator =(const SimuLine& tempLine)
{
	this->startPoint=tempLine.startPoint;
	this->endPoint=tempLine.endPoint;
	this->color=tempLine.color;
	this->thickness=tempLine.thickness;
	return *this;
}
