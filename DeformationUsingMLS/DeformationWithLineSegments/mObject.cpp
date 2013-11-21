#include "mObject.h"
#include <string>
#include <fstream>
#include <iostream>
#include <math.h>
#include <stdio.h>

using std::string;
using std::fstream;
using std::iostream;


/******************************************************/
mVert::mVert()
{
	X = Y = Z = 0.0;
}
mVert::mVert(double x, double y, double z)
{
	this->X = x;
	this->Y = y;
	this->Z = z;
}

mVert mVert::CrossProduct(const mVert& p)
{
	mVert temp;
	temp.X = Y * p.Z - Z * p.Y;
	temp.Y = Z * p.X - X * p.Z;
	temp.Z = X * p.Y - Y * p.X;
	return temp;
}

double mVert::DotProduct(const mVert &p)
{
	double s = X * p.X + Y * p.Y + Z * p.Z;
	return s;
}

void mVert::SetPoint(double x, double y, double z)
{
	this->X = x;
	this->Y = y;
	this->Z = z;
}

mVert mVert::operator -(const mVert &p)
{
	mVert temp;
	temp.X = X - p.X;
	temp.Y = Y - p.Y;
	temp.Z = Z - p.Z;
	return temp;
}

mVert mVert::operator +(const mVert &p)
{
	mVert temp;
	temp.X = X + p.X;
	temp.Y = Y + p.Y;
	temp.Z = Z + p.Z;
	return temp;
}

mVert mVert::operator /(const double div)
{
	mVert temp;
	temp.X = X / div;
	temp.Y = Y / div;
	temp.Z = Z / div;
	return temp;
}

double mVert::magnitude()
{
	double s = X * X + Y * Y + Z * Z;
	s = sqrt(s);
	return s;
}

mVert & mVert::normalize()
{
	double l = magnitude();
	if (l == 0)
		return *this;

	l = 1.0 / l;
	X *= l;
	Y *= l;
	Z *= l;
	return *this;
}

mVert mVert::operator *(const double v)
{
	mVert temp;
	temp.X = X * v;
	temp.Y = Y * v;
	temp.Z = Z * v;
	return temp;
}
/*************************************************/


void mObject::Draw()
{

	glLineWidth(1.0);
	glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);

	// »­Ïß¿ò
	for (int i = 0; i < mFacets.size(); i++)
	{
		mVert v1,v2,v3;
		v1 = mVerts[mFacets[i].indexOfPointA];
		v2 = mVerts[mFacets[i].indexOfPointB];
		v3 = mVerts[mFacets[i].indexOfPointC];
		glBegin(GL_TRIANGLES);
		glVertex3f(v1.X,v1.Y,v1.Z);
		glVertex3f(v2.X,v2.Y,v2.Z);
		glVertex3f(v3.X,v3.Y,v3.Z);
		glEnd();
	}
}

mObject::mObject(int row, int col)
{
	for (int i=0; i<row; i++)
	{
		for (int j=0; j<col;j++)
		{
			mVerts.push_back(mVert(i, j, 0));
		}
	}
}
