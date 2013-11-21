#include "StdAfx.h"
#include <cv.h>
#include <cxcore.h>
#include "TextureSynthesis.h"
#include "analogdisplay.h"

void CAnalogdisplay::drawRealStitch(IplImage * dst,int fromX, int fromY, int toX, int toY, COLORREF color)
{
	if(fromX>toX)
	{
		int tx=fromX,ty=fromY;
		fromX=toX;fromY=toY;
		toX=tx;toY=ty;
	}
	//计算绣线长度
	double dx= toX-fromX ;
	double dy= toY-fromY ;
	double dLength=sqrt((fabs(dx)+1)*(fabs(dx)+1)+(fabs(dy)+1)*(fabs(dy)+1));

	int iLength =(dLength*textureSyn.getThreadWidth());

	//生成绣线纹理图

	IplImage * imgThread = textureSyn.newThread(iLength,color);
	//旋转
	//if(dy==0){
	//       for(int i=0;i<imgThread->height;i++){
	//               for(int j=0;j<imgThread->width;j++){
	//                       int x2=0,y2=0;
	//                       x2=fromX*imgThread->height+j;
	//                       y2=fromY*imgThread->height+i;
	//                       CvScalar s= cvGet2D(imgThread,i,j);
	//                       int R=s.val[2];int G=s.val[1];int B=s.val[0];
	//                       //realImage->Canvas->Pixels[x2][y2] = RGB(R,G,B);
	//                       //realBMP->Canvas->Pixels[x2][y2] = RGB(R,G,B);
	//					if(y2<0)
	//						y2=0;
	//					if(y2>=dst->height)
	//						y2=dst->height-1;
	//					if(x2<0)
	//						x2=0;
	//					if(x2>=dst->width)
	//						x2=dst->width-1;
	//					cvSet2D(dst,y2,x2,s);
	//			}
	//		}
	//}
	//else if(dx==0){
	//       for(int i=0;i<imgThread->height;i++){
	//               for(int j=0;j<imgThread->width;j++){
	//                       int x2=0,y2=0;
	//                       x2=fromX*imgThread->height+i;
	//                       y2=fromY*imgThread->height+j;
	//                       CvScalar s= cvGet2D(imgThread,i,j);
	//                       int R=s.val[2];int G=s.val[1];int B=s.val[0];
	//                       //realImage->Canvas->Pixels[x2][y2] = RGB(R,G,B);
	//                       //realBMP->Canvas->Pixels[x2][y2] = RGB(R,G,B);
	//					if(y2<0)
	//						y2=0;
	//					if(y2>=dst->height)
	//						y2=dst->height-1;
	//					if(x2<0)
	//						x2=0;
	//					if(x2>=dst->width)
	//						x2=dst->width-1;
	//					cvSet2D(dst,y2,x2,s);
	//               }
	//       }
	//}
	//else{
	//       if(dy>0){
	//               double cosa=dx/dLength;
	//               double sina=dy/dLength;
	//               double shiftx = sina*(textureSyn.getThreadWidth()-1);
	//			int nn;
	//			int nnn;
	//               for(int j=0;j<(dy+1)*imgThread->height;j++){
	//                       for(int i=0;i<(dx+1)*imgThread->height;i++){
	//                               //根据i,j计算原来的位置
	//                               int x =(i-shiftx)*cosa+j*sina+0.5;
	//                               int y =-(i-shiftx)*sina+j*cosa+0.5;
	//                               if(x>=0&&x<imgThread->width&&y>=0&&y<imgThread->height){
	//                                       CvScalar s= cvGet2D(imgThread,y,x);
	//                                       int R=s.val[2];int G=s.val[1];int B=s.val[0];
	//                                       //realImage->Canvas->Pixels[i+fromX*imgThread->height][j+fromY*imgThread->height] = RGB(R,G,B);
	//                                      // realBMP->Canvas->Pixels[i+fromX*imgThread->height][j+fromY*imgThread->height] = RGB(R,G,B);
	//									nn=i+fromX*imgThread->height;
	//									nnn=j+fromY*imgThread->height;
	//									if(nnn<0)
	//										nnn=0;
	//									if(nnn>=dst->height)
	//										nnn=dst->height-1;
	//									if(nn<0)
	//										nn=0;
	//									if(nn>=dst->width)
	//										nn=dst->width-1;
	//									cvSet2D(dst,nnn,nn,s);
	//                               }
	//                       }
	//               }
	//       }
	//       else{
	//               double cosa=dx/dLength;
	//               double sina=dy/dLength;
	//               double shifty = cosa*(textureSyn.getThreadWidth()-1);

	//               for(int j=0;j>(dy-1)*imgThread->height;j--){
	//                       for(int i=0;i<(dx+1)*imgThread->height;i++){
	//                               //根据i,j计算原来的位置
	//                               int x =(i)*cosa+(j+shifty)*sina+0.5;
	//                               int y =-(i)*sina+(j+shifty)*cosa+0.5;
	//                               if(x>=0&&x<imgThread->width&&y>=0&&y<imgThread->height){
	//                                       CvScalar s= cvGet2D(imgThread,y,x);
	//                                       int R=s.val[2];int G=s.val[1];int B=s.val[0];
	//                                       //realImage->Canvas->Pixels[i+fromX*imgThread->height][j+fromY*imgThread->height] = RGB(R,G,B);
	//                                       //realBMP->Canvas->Pixels[i+fromX*imgThread->height][j+fromY*imgThread->height] = RGB(R,G,B);
	//									int x2=0,y2=0;
	//									x2=i+fromX*imgThread->height;
	//									y2=j+fromY*imgThread->height;
	//									if(y2<0)
	//										y2=0;
	//									if(y2>=dst->height)
	//										y2=dst->height-1;
	//									if(x2<0)
	//										x2=0;
	//									if(x2>=dst->width)
	//										x2=dst->width-1;
	//									cvSet2D(dst,y2,x2,s);

	//                               }
	//                       }
	//               }

	//       }
	//}
	if(dy==0){
		for(int i=0;i<imgThread->height;i++){
			for(int j=0;j<imgThread->width;j++){
				int x2=0,y2=0;
				x2=fromX*textureSyn.getThreadWidth()+j;
				y2=fromY*textureSyn.getThreadWidth()+i;
				CvScalar s= cvGet2D(imgThread,i,j);
				int R=s.val[2];int G=s.val[1];int B=s.val[0];
				//realImage->Canvas->Pixels[x2][y2] = RGB(R,G,B);
				//realBMP->Canvas->Pixels[x2][y2] = RGB(R,G,B);
				if(y2<0)
					y2=0;
				if(y2>=dst->height)
					y2=dst->height-1;
				if(x2<0)
					x2=0;
				if(x2>=dst->width)
					x2=dst->width-1;
				cvSet2D(dst,y2,x2,s);
			}
		}
	}
	else if(dx==0){
		for(int i=0;i<imgThread->height;i++){
			for(int j=0;j<imgThread->width;j++){
				int x2=0,y2=0;
				x2=fromX*textureSyn.getThreadWidth()+i;
				y2=fromY*textureSyn.getThreadWidth()+j;
				CvScalar s= cvGet2D(imgThread,i,j);
				int R=s.val[2];int G=s.val[1];int B=s.val[0];
				//realImage->Canvas->Pixels[x2][y2] = RGB(R,G,B);
				//realBMP->Canvas->Pixels[x2][y2] = RGB(R,G,B);
				if(y2<0)
					y2=0;
				if(y2>=dst->height)
					y2=dst->height-1;
				if(x2<0)
					x2=0;
				if(x2>=dst->width)
					x2=dst->width-1;
				cvSet2D(dst,y2,x2,s);
			}
		}
	}
	else{
		if(dy>0){
			double cosa=dx/dLength;
			double sina=dy/dLength;
			double shiftx = sina*(textureSyn.getThreadWidth()-1);
			int nn;
			int nnn;
			for(int j=0;j<(dy+1)*textureSyn.getThreadWidth();j++){
				for(int i=0;i<(dx+1)*textureSyn.getThreadWidth();i++){
					//根据i,j计算原来的位置
					int x =(i-shiftx)*cosa+j*sina+0.5;
					int y =-(i-shiftx)*sina+j*cosa+0.5;
					if(x>=0&&x<imgThread->width&&y>=0&&y<imgThread->height){
						CvScalar s= cvGet2D(imgThread,y,x);
						int R=s.val[2];int G=s.val[1];int B=s.val[0];
						//realImage->Canvas->Pixels[i+fromX*imgThread->height][j+fromY*imgThread->height] = RGB(R,G,B);
						// realBMP->Canvas->Pixels[i+fromX*imgThread->height][j+fromY*imgThread->height] = RGB(R,G,B);
						nn=i+fromX*textureSyn.getThreadWidth();
						nnn=j+fromY*textureSyn.getThreadWidth();
						if(nnn<0)
							nnn=0;
						if(nnn>=dst->height)
							nnn=dst->height-1;
						if(nn<0)
							nn=0;
						if(nn>=dst->width)
							nn=dst->width-1;
						cvSet2D(dst,nnn,nn,s);
					}
				}
			}
		}
		else{
			double cosa=dx/dLength;
			double sina=dy/dLength;
			double shifty = cosa*(textureSyn.getThreadWidth()-1);

			for(int j=0;j>(dy-1)*textureSyn.getThreadWidth();j--){
				for(int i=0;i<(dx+1)*textureSyn.getThreadWidth();i++){
					//根据i,j计算原来的位置
					int x =(i)*cosa+(j+shifty)*sina+0.5;
					int y =-(i)*sina+(j+shifty)*cosa+0.5;
					if(x>=0&&x<imgThread->width&&y>=0&&y<imgThread->height){
						CvScalar s= cvGet2D(imgThread,y,x);
						int R=s.val[2];int G=s.val[1];int B=s.val[0];
						//realImage->Canvas->Pixels[i+fromX*imgThread->height][j+fromY*imgThread->height] = RGB(R,G,B);
						//realBMP->Canvas->Pixels[i+fromX*imgThread->height][j+fromY*imgThread->height] = RGB(R,G,B);
						int x2=0,y2=0;
						x2=i+fromX*textureSyn.getThreadWidth();
						y2=j+fromY*textureSyn.getThreadWidth();
						if(y2<0)
							y2=0;
						if(y2>=dst->height)
							y2=dst->height-1;
						if(x2<0)
							x2=0;
						if(x2>=dst->width)
							x2=dst->width-1;
						cvSet2D(dst,y2,x2,s);

					}
				}
			}

		}
	}
	cvReleaseImage(&imgThread);
}