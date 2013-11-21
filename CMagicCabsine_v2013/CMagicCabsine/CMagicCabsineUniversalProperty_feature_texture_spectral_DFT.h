//����������DFT

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
	void ComputeProperty();//����ȫ������,�������н�������ݵ�׼��
	void SaveProperty();//��������
	void LoadProperty();//��ȡ����
	void SavePropertyFile(string filepath);//��������
	void LoadPropertyFile(string filepath);//��ȡ����
	void DeleteProperty();//ɾ������Ҫ������

	// Rearrange the quadrants of Fourier image so that the origin is at
	// the image center
	// src & dst arrays of equal size & type
	void cvShiftDFT(CvArr * src_arr, CvArr * dst_arr );

	float FT_Entropy(CvArr* src_arr);//����FT����
	float FT_Energy(CvArr* src_arr);//����FT������
	float FT_Inertia(CvArr* src_arr);//����FT�Ĺ���

	void SplitImage(const IplImage *imgSrc, const int n, vector<IplImage*> &subImgs);


protected:
	IplImage * image_Re_save;



};

#endif