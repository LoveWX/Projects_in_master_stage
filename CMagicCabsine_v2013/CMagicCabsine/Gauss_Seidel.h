#ifndef __GAUSS_SEIDEL_H
#define __GAUSS_SEIDEL_H
#include <cv.h>
#include <vector>
#include <cmath>
//#include "SketchLine.h"
using namespace std;
class Gauss_Seidel 
{
public:
	float **orient ;
	float **sk_orient ;
	float **smoothorient;
	int height;
	int width;
	vector<float> Nplus;
	vector<float> Nminus;
	Gauss_Seidel(int h,int w,FILE* fp2)
	{
		height=h;
		width=w;
		orient = new float*[h] ;
		for( int i = 0 ; i < h ; i ++ )
			orient[i] = new float[w] ;
		sk_orient = new float*[h] ;
		for( int i = 0 ; i < h ; i ++ )
			sk_orient[i] = new float[w] ;
		smoothorient = new float*[h] ;
		for( int i = 0 ; i < h ; i ++ )
			smoothorient[i] = new float[w] ;
////////////////////////////////////////////////
		/*int n;
		fscanf(fp1,"%d",&n);
		vector<SketchLine> SL;
		for(int i=0;i<n;i++)
		{
			SketchLine S_line;
			int m;
			fscanf(fp1,"%d ",&m);
			for(int j=0;j<m;j++)
			{
				CvPoint p;
				int x,y;
				fscanf(fp1,"%d,%d,",&x,&y);
				p.x=x;
				p.y=y;
				S_line.Line.push_back(p);
			}
			SL.push_back(S_line);
			fscanf(fp1,"/n");
		}
		fclose(fp1);*/
/////////////////////////////////////////////////////////
		for(int i=0;i<h;i++)
		{
			for(int j=0;j<w-1;j++)
		 {
			 fscanf(fp2,"%f,",&orient[i][j]);
		 }
			fscanf(fp2,"%f/n",&orient[i][w-1]);
		}
		fclose(fp2);
////////////////////////////////////////////////////////////
		for(int i=0;i<h;i++)
			for(int j=0;j<w;j++)
			{
				sk_orient[i][j]=0;
			}
		for(int i=0;i<h;i++)
			for(int j=0;j<w;j++)
			{
				smoothorient[i][j]=0;
			}
		/*for(int i=0;i<SL.size();i++)
		{
			for(int j=0;j<SL[i].Line.size()-1;j++)
			{
				vector<CvPoint> B_Line;
				bresenham (&B_Line,SL[i].Line[j].x,SL[i].Line[j].y,SL[i].Line[j+1].x,SL[i].Line[j+1].y);
				float angle=atan((float)(SL[i].Line[j].y-SL[i].Line[j+1].y)/(float)(SL[i].Line[j+1].x-SL[i].Line[j].x));
				if(angle<0)
					angle=3.14+angle;
				for(int n=0;n<B_Line.size();n++)
				{
					sk_orient[B_Line[n].y][B_Line[n].x]=angle;
				}
			}
		}*/
//////////////////////////////////////////////////////////////
		/*fp1=fopen("sketch_orient.txt","w");
		for(int i=0;i<height;i++)
		{
			for(int j=0;j<width;j++)
		 {
			 fprintf(fp1,"%f,",sk_orient[i][j]);
		 }
			fprintf(fp1,"\n");
		}
		fclose(fp1);*/
		for(int i=0;i<height;i++)
			for(int j=0;j<width;j++)
			{
				/*if(sk_orient[i][j]!=0)
					orient[i][j]=sk_orient[i][j];*/
			}
	}
	float Ccalculate(void)
	{
		float a,b;
		a=0;b=0;
		for(int i=0;i<Nplus.size();i++)
		{
			a=a+2*cos(Nplus[i]);
		}
		for(int i=0;i<Nminus.size();i++)
		{
			b=b+2*cos(Nminus[i]);
		}
		return a+b;
	}
	float Scalculate(void)
	{
		float a,b;
		a=0;b=0;
		for(int i=0;i<Nplus.size();i++)
		{
			a=a+2*sin(Nplus[i]);
		}
		for(int i=0;i<Nminus.size();i++)
		{
			b=b+2*sin(Nminus[i]);
		}
		return a+b;
	}
	void smoothvector(void)
	{
		for(int i=1;i<height-1;i++)
			for(int j=1;j<width-1;j++)
			{
				Nplus.clear();
				Nminus.clear();
				Nplus.push_back(orient[i][j+1]);
				Nplus.push_back(orient[i+1][j]);
				Nminus.push_back(orient[i-1][j]);
				Nminus.push_back(orient[i][j-1]);
				float C=Ccalculate();
				float S=Scalculate();
				float r=sqrt(C*C+S*S);
				float w;
				if(C>0&&S>=0)
				{
					w=atan(S/C);
				}
				else if(C>0&&S<0)
				{
					w=2*3.14+atan(S/C);
				}
				else if(C<0&&S>=0)
				{
					w=3.14+atan(S/C);
				}
				else if(C<0&&S<0)
				{
					w=3.14+atan(S/C);
				}
				else if(C==0&&S>=0)
				{
					w=3.14/2;
				}
				else if(C==0&&S<0)
				{
					w=3.14+3.14/2;
				}
				smoothorient[i][j]=w;
			}
		int n=0;
		float dis=1000;
		float** tmp;
		tmp = new float*[height] ;
		for( int i = 0 ; i < height ; i ++ )
			tmp[i] = new float[width] ;
		while(n<=20&&dis>=0.0036)
		{			
			for(int i=0;i<height;i++)
				for(int j=0;j<width;j++)
				{
					tmp[i][j]=smoothorient[i][j];
				}
			for(int i=1;i<height-1;i++)
				for(int j=1;j<width-1;j++)
				{
					Nplus.clear();
					Nminus.clear();
					Nplus.push_back(smoothorient[i][j+1]);
					Nplus.push_back(smoothorient[i+1][j]);
					Nminus.push_back(smoothorient[i-1][j]);
					Nminus.push_back(smoothorient[i][j-1]);
					float C=Ccalculate();
					float S=Scalculate();
					float r=sqrt(C*C+S*S);
					float w;
					if(C>0&&S>=0)
					{
						w=atan(S/C);
					}
					else if(C>0&&S<0)
					{
						w=2*3.14+atan(S/C);
					}
					else if(C<0&&S>=0)
					{
						w=3.14+atan(S/C);
					}
					else if(C<0&&S<0)
					{
						w=3.14+atan(S/C);
					}
					else if(C==0&&S>=0)
					{
						w=3.14/2;
					}
					else if(C==0&&S<0)
					{
						w=3.14+3.14/2;
					}
					smoothorient[i][j]=w+asin(0.5/r*sin(orient[i][j]-smoothorient[i][j]));
				}
				dis=Calculate_Distance(tmp,smoothorient,height,width);
				//cout<<dis<<endl;
				//cout<<n<<endl;
				n++;
		}
			
				
		FILE* fp;
		fp=fopen("smooth_orient.txt","w");
		for(int i=0;i<height;i++)
		{
			for(int j=0;j<width;j++)
			{
				fprintf(fp,"%f,",smoothorient[i][j]);
			}
			fprintf(fp,"\n");
		}
		fclose(fp);
	}
	float Calculate_Distance(float** src,float** dst,int height,int width)
	{
		float tmp1=0,tmp2=0;
		for(int i=0;i<height;i++)
			for(int j=0;j<width;j++)
			{
				tmp1=tmp1+fabs(src[i][j]-dst[i][j]);
			}
		for(int i=0;i<height;i++)
			for(int j=0;j<width;j++)
			{
				tmp2=tmp2+fabs(src[i][j]);
			}
		return tmp1/tmp2;
	}
};
#endif