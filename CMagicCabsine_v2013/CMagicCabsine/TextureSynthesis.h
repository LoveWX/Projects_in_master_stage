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
	// ��ͼ
	IplImage *imgSample;
	// ��ͼ���߿��
	int iThreadWidth;
	// ��ͼ���߳���
	int iSampleLength;
public:
	// ��ȡ���߿��
	int getThreadWidth(void);
	// �ϳ����ߣ�����Ϊ�ϳ����ߵĳ��ȣ���������
	IplImage * newThread(int iLength,COLORREF color);
	// װ����ͼ
	void loadSample(const char * filename);
private:
	// �Ѻϳɵ�����
	IplImage *imgSynthesis;
	int iWindowSize;
	vector<int> endCircle;
};
vector<int> circle(int r);

#endif