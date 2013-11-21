#ifndef __CVCOPYIMAGE
#define __CVCOPYIMAGE
#include <cv.h>
#include <cxcore.h>

void copySubImage(IplImage * from, IplImage * to,CvRect rect);
#endif