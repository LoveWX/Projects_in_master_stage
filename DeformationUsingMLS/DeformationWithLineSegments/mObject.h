#ifndef MOBJECT_H
#define MOBJECT_H

#include "windows.h"
#include <gl//GL.h>
#include <vector>
#include <string>

using std::string;
using std::vector; 

class mVert
{
public:
	double X, Y, Z;

public:
	mVert();
	mVert(double x, double y, double z);
	mVert CrossProduct(const mVert & p);
	double DotProduct(const mVert &p);
	void SetPoint(double x, double y, double z);
	mVert operator - (const mVert &p);
	mVert operator + (const mVert &p);
	mVert operator / (const double div);
	mVert operator * (const double v);

	mVert & normalize();
	double magnitude();

protected:
private:
};

class mFacet
{
public:
	int indexOfPointA;
	int indexOfPointB;
	int indexOfPointC;
protected:
private:
};

class mObject
{
public:
	int numOfVerts;
	int numOfFacets;

	vector<mVert> mVerts;
	vector<mFacet> mFacets;

	mObject();
	mObject(const string &filename);

	mObject(int row, int col);

	void Draw();
	void DrawPoints();

public:
	vector<mVert> pNormal;
	vector<mVert> vNormal;

	vector<mVert> face_profile; // »À¡≥µƒÕ‚¬÷¿™
protected:
private:

};

#endif
