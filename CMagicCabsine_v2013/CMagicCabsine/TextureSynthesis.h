#ifndef _TEXTURESYNTHESIS_H
#define _TEXTURESYNTHESIS_H

#include <cv.h>
#include <highgui.h>
#include <cxcore.h>
#include <vector>
#include <windows.h>
using namespace std;

class CTextureSynthesis
{
public:
	CTextureSynthesis(void);
	virtual ~CTextureSynthesis(void);
private:
	// 样图
	IplImage *imgSample;
	// 样图绣线宽度
	int iThreadWidth;
	// 样图绣线长度
	int iSampleLength;
public:
	// 获取绣线宽度
	int getThreadWidth(void);
	// 合成绣线，参数为合成绣线的长度（像素数）
	IplImage * newThread(int iLength,COLORREF color);
	// 装入样图
	void loadSample(const char * filename);
private:
	// 已合成的绣线
	IplImage *imgSynthesis;
	int iWindowSize;
	vector<int> endCircle;
};
vector<int> circle(int r);

#endif