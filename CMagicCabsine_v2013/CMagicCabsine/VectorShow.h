#pragma once
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <cv.h>
#include <highgui.h>
#include <vector>
using namespace std;


#define  SQUARE_FLOW_FIELD_SZ	400
#define	 DISCRETE_FILTER_SIZE	2048
#define  LOWPASS_FILTR_LENGTH	10.00000f
#define	 LINE_SQUARE_CLIP_MAX	100000.0f
#define	 VECTOR_COMPONENT_MIN   0.050000f 
class VectorShow
{
public:
	int n_xres,n_yres;
	float*			pVectr ;
	float*			p_LUT0 ;
	float*			p_LUT1 ;
	unsigned char*	pNoise ;
	unsigned char*	pImage ;
	VectorShow(int width, int height)
	{
		n_xres=width;
		n_yres=height;
		pVectr = (float*         ) malloc( sizeof(float        ) * n_xres * n_yres * 2 );
		p_LUT0 = (float*		 ) malloc( sizeof(float        ) * DISCRETE_FILTER_SIZE);
		p_LUT1 = (float*		 ) malloc( sizeof(float        ) * DISCRETE_FILTER_SIZE);
		pNoise = (unsigned char* ) malloc( sizeof(unsigned char) * n_xres * n_yres     );
		pImage = (unsigned char* ) malloc( sizeof(unsigned char) * n_xres * n_yres     );
	}
	~VectorShow(void);
	void SyntheszVector(vector<vector<double>>& vectorfield);
	void NormalizVectrs();
	void GenBoxFiltrLUT(int  LUTsiz);
	void MakeWhiteNoise();
	void FlowImagingLIC(float  krnlen);	
};
