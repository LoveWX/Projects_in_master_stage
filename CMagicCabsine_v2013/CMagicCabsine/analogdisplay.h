#ifndef _ANALOGDISPLAY_H
#define _ANALOGDISPLAY_H
#include <cv.h>
#include <cxcore.h>
#include "TextureSynthesis.h"
using namespace std;
class CAnalogdisplay
{
public:
	//Graphics::TBitmap *realBMP;
	CTextureSynthesis textureSyn;
	void drawRealStitch(IplImage * dst,int fromX, int fromY, int toX, int toY, COLORREF color);	
};

#endif