//����������DFT

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
	void ComputeProperty();//����ȫ������,�������н�������ݵ�׼��
	void SaveProperty();//��������
	void LoadProperty();//��ȡ����
	void SavePropertyFile(string filepath);//��������
	void LoadPropertyFile(string filepath);//��ȡ����
	void DeleteProperty();//ɾ������Ҫ������


	float FT_Entropy(CvArr* src_arr);//����FT����
	float FT_Energy(CvArr* src_arr);//����FT������
	float FT_Inertia(CvArr* src_arr);//����FT�Ĺ���


		/*
	 *iMu		�Ƕȣ�		iMu*PI/8
	 *iNu		�߶�
	 *dSigma	sigma
	 *dF		�ռ�Ƶ��
	 *dPhi		�Ƕ�
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
	IplImage * image_Re_save;//���

	IplImage * srcImage_grayscale;//Դͼ��ת���ĻҶ�ͼ��

	double Sigma;   //��˹���ڿ��
	double F;       //�ռ�Ƶ��
	double Kmax;   
	double K;
	double Phi;      //Gabor���ȷ���
	bool bInitialised;
	bool bKernel;
	long Width;     //���ڿ��
	CvMat *Imag;    //ʵ������
	CvMat *Real;    //�鲿����

private:
	void creat_kernel();

};

#endif