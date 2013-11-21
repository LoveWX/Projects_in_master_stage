//谱纹理特征DFT

#ifndef cmagiccabsineuniversalpropertyFeatureTextureSpectralGabor
#define cmagiccabsineuniversalpropertyFeatureTextureSpectralGabor

#include <vector>
#include <cstring>
using namespace std;
#include <cv.h>
#include <highgui.h>

#include "CMagicCabsineUniversalProperty.h"
#include "stdafx.h"

#define PI 3.14159265
#define CV_GABOR_REAL 1
#define CV_GABOR_IMAG 2
#define CV_GABOR_MAG  3
#define CV_GABOR_PHASE 4

class CMagicCabsineUniversalProperty_feature_texture_spectral_gabor:public CMagicCabsineUniversalProperty
{
public:
	CMagicCabsineUniversalProperty_feature_texture_spectral_gabor(const IplImage *tempSrcImage);
	~CMagicCabsineUniversalProperty_feature_texture_spectral_gabor();
	void ComputeProperty();//计算全局特征,测试类中仅完成数据的准备
	void SaveProperty();//保存数据
	void LoadProperty();//读取数据
	void SavePropertyFile(string filepath);//保存数据
	void LoadPropertyFile(string filepath);//读取数据
	void DeleteProperty();//删除不需要的数据


	float FT_Entropy(CvArr* src_arr);//计算FT的熵
	float FT_Energy(CvArr* src_arr);//计算FT的能量
	float FT_Inertia(CvArr* src_arr);//计算FT的惯性


		/*
	 *iMu		角度：		iMu*PI/8
	 *iNu		尺度
	 *dSigma	sigma
	 *dF		空间频率
	 *dPhi		角度
	 */
     void gabor(int iMu, int iNu, double dSigma);
     void gabor(int iMu, int iNu, double dSigma, double dF);
     void gabor(double dPhi, int iNu);
     void gabor(double dPhi, int iNu, double dSigma);
     void gabor(double dPhi, int iNu, double dSigma, double dF);
	 void gabor(int iMu, int iNu);

    bool IsInit();
    long mask_width();
    IplImage* get_image(int Type);
    bool IsKernelCreate();
    long get_mask_width();
    void Init(int iMu, int iNu, double dSigma, double dF);
    void Init(double dPhi, int iNu, double dSigma, double dF);
    void output_file(const char *filename, int Type);
    CvMat* get_matrix(int Type);
    void show(int Type);
    void conv_img(IplImage *src, IplImage *dst, int Type);

    void normalize( const CvArr* src, CvArr* dst, double a, double b, int norm_type, const CvArr* mask );
    void conv_img_a(IplImage *src, IplImage *dst, int Type);

protected:
	IplImage * image_Re_save;//结果

	IplImage * srcImage_grayscale;//源图像转换的灰度图像

	double Sigma;   //高斯窗口宽度
	double F;       //空间频率
	double Kmax;   
	double K;
	double Phi;      //Gabor弧度方向
	bool bInitialised;
	bool bKernel;
	long Width;     //窗口宽度
	CvMat *Imag;    //实部矩阵
	CvMat *Real;    //虚部矩阵

private:
	void creat_kernel();

};

#endif