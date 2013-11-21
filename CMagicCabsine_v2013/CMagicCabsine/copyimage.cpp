#include "StdAfx.h"
#include <cv.h>
#include <highgui.h>
#include <cxcore.h>

#include "copyimage.h"

#include <cstdlib>

using namespace std;

void copySubImage(IplImage * from, IplImage * to,CvRect rect)
{
        //TODO: Add your source code here
        to->origin = from->origin;
        int pBytes = from->widthStep/from->width;
        //int pBytes = 3;

        if(rect.x+rect.width-1>from->width-1){
          throw 1;
        }
        for(int i=0;i<rect.height;i++){
                char * lineStart,  *lineTo;
                if(from->origin==0){
                  lineStart = from->imageData+(rect.y+i)*from->widthStep+pBytes*rect.x;
                  lineTo = to->imageData+i*to->widthStep;
                }
                else{
                  lineStart = from->imageData+(from->height-1-rect.y-i)*from->widthStep+pBytes*rect.x;
                  lineTo = to->imageData+(to->height-1-i)*to->widthStep;
                }
                try{
                memcpy(lineTo,lineStart,rect.width*pBytes);
                }
                catch(...)
                {
                  return;
                }
        }
}
