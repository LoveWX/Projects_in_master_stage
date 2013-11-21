//谱纹理特征DFT

#ifndef cmagiccabsineuniversalpropertyFeatureTextureSpectralDFT
#define cmagiccabsineuniversalpropertyFeatureTextureSpectralDFT

#include <vector>
#include <cstring>
using namespace std;
#include <cv.h>
#include <highgui.h>

#include "CMagicCabsineUniversalProperty.h"
#include "stdafx.h"


class CMagicCabsineUniversalProperty_feature_texture_spectral_DFT:public CMagicCabsineUniversalProperty
{
public:
	CMagicCabsineUniversalProperty_feature_texture_spectral_DFT(const IplImage *tempSrcImage);
	~CMagicCabsineUniversalProperty_feature_texture_spectral_DFT();
	void ComputeProperty();//计算全局特征,测试类中仅完成数据的准备
	void SaveProperty();//保存数据
	void LoadProperty();//读取数据
	void SavePropertyFile(string filepath);//保存数据
	void LoadPropertyFile(string filepath);//读取数据
	void DeleteProperty();//删除不需要的数据

	// Rearrange the quadrants of Fourier image so that the origin is at
	// the image center
	// src & dst arrays of equal size & type
	void cvShiftDFT(CvArr * src_arr, CvArr * dst_arr );

	float FT_Entropy(CvArr* src_arr);//计算FT的熵
	float FT_Energy(CvArr* src_arr);//计算FT的能量
	float FT_Inertia(CvArr* src_arr);//计算FT的惯性

	void SplitImage(const IplImage *imgSrc, const int n, vector<IplImage*> &subImgs);


protected:
	IplImage * image_Re_save;



};

#endif