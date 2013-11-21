#include "stdafx.h"

#include "CMagicCabsineUniversalProperty_feature_texture_spectral_DFT.h"

CMagicCabsineUniversalProperty_feature_texture_spectral_DFT::CMagicCabsineUniversalProperty_feature_texture_spectral_DFT(const IplImage *tempSrcImage)
	:CMagicCabsineUniversalProperty(tempSrcImage)
{
	image_Re_save = NULL;
}

CMagicCabsineUniversalProperty_feature_texture_spectral_DFT::~CMagicCabsineUniversalProperty_feature_texture_spectral_DFT()
{
	DeleteProperty();
}

void CMagicCabsineUniversalProperty_feature_texture_spectral_DFT::ComputeProperty()
{

	IplImage * im;//����ͼ������ǻҶ�ͼ��
	
	
	IplImage * realInput;
	IplImage * imaginaryInput;
	IplImage * complexInput;
	int dft_M, dft_N;
	CvMat* dft_A, tmp;
	IplImage * image_Im;
	IplImage * image_Re;

	double m, M;
	
	//�Ҷ�ͼת��
	IplImage *srcimg_cvt = cvCreateImage(cvGetSize(srcImage),IPL_DEPTH_8U,3);//Դͼ���ʽ��ͼ��
	im = cvCreateImage(cvGetSize(srcImage),IPL_DEPTH_8U,1);
	cvConvertScale(srcImage,srcimg_cvt);//Դͼ���ʽ�� ת���� IPL_DEPTH_32F 3ͨ��
	cvCvtColor(srcImage,im,CV_BGR2GRAY);//Դͼ��ת���ɻҶ�ͼ
	cvReleaseImage(&srcimg_cvt);

	realInput = cvCreateImage( cvGetSize(srcImage), IPL_DEPTH_64F, 1);//�Ҷ�ͼ��
	imaginaryInput = cvCreateImage( cvGetSize(srcImage), IPL_DEPTH_64F, 1);//�Ҷ�ͼ��
	complexInput = cvCreateImage( cvGetSize(srcImage), IPL_DEPTH_64F, 2);

	cvScale(im, realInput, 1.0, 0.0);//��8uת����32f ��߾���
	cvZero(imaginaryInput);
	//����ͨ��ͼ��ϲ��ɶ�ͨ��ͼ�񣨽�realInput��imageinaryImput�ϲ���˫ͨ��ͼ��complexInput��
	cvMerge(realInput, imaginaryInput, NULL, NULL, complexInput);

	/*dft_M = cvGetOptimalDFTSize( im->height - 1 );
	dft_N = cvGetOptimalDFTSize( im->width - 1 );*/

	dft_M = im->height;
	dft_N = im->width;
	dft_A = cvCreateMat( dft_M, dft_N, CV_64FC2 );
	image_Re = cvCreateImage( cvSize(dft_N, dft_M), IPL_DEPTH_64F, 1);//DFT��ѳߴ��ͼ��
	image_Im = cvCreateImage( cvSize(dft_N, dft_M), IPL_DEPTH_64F, 1);

	// copy A to dft_A and pad dft_A with zeros
	cvGetSubRect( dft_A, &tmp, cvRect(0,0, im->width, im->height));
	cvCopy( complexInput, &tmp, NULL );
	if( dft_A->cols > im->width )
	{
		cvGetSubRect( dft_A, &tmp, cvRect(im->width,0, dft_A->cols - im->width, im->height));
		cvZero( &tmp );
	}

	// no need to pad bottom part of dft_A with zeros because of
	// use nonzero_rows parameter in cvDFT() call below

	cvDFT( dft_A, dft_A, CV_DXT_FORWARD, complexInput->height );
	

	// Split Fourier in real and imaginary parts
	cvSplit( dft_A, image_Re, image_Im, 0, 0 );
	
	// Compute the magnitude of the spectrum Mag = sqrt(Re^2 + Im^2)
	cvPow( image_Re, image_Re, 2.0);
	cvPow( image_Im, image_Im, 2.0);
	cvAdd( image_Re, image_Im, image_Re, NULL);
	cvPow( image_Re, image_Re, 0.5 );

	// Compute log(1 + Mag)
	cvAddS( image_Re, cvScalarAll(1.0), image_Re, NULL ); // 1 + Mag
	cvLog( image_Re, image_Re ); // log(1 + Mag)
		
	// Rearrange the quadrants of Fourier image so that the origin is at
	// the image center
	cvShiftDFT( image_Re, image_Re );
	cvMinMaxLoc(image_Re, &m, &M, NULL, NULL, NULL);
	cvScale(image_Re, image_Re, 1.0/(M-m), 1.0*(-m)/(M-m));
	//cvShowImage("magnitude", image_Re);

	//���滯����Ҷ�任ͼ��ʹ����Ա��洢
	image_Re_save = cvCreateImage(cvSize(dft_N,dft_M),IPL_DEPTH_64F,1);//ע�Ȿ��Ӧ���ڳ�ʼ���д������������ڴ�С�����޷����ƹ��ڴ˴�����Ҫ������������release
	cvNormalize(image_Re,image_Re_save,255,0,CV_MINMAX,NULL);



	cvReleaseImage(&im);
	cvReleaseImage(&realInput);
	cvReleaseImage(&imaginaryInput);
	cvReleaseImage(&complexInput);
	cvReleaseImage(&image_Re);
	cvReleaseImage(&image_Im);

	////�Ը���Ҷ�������滯ʹ��L2(ŷ�����)��ʽ��ȡ���滯����Ҷϵ��NFP,�Լ���3������Ҷϵ��,δ�Ӿ���ֵ
	//cvNormalize(image_Re,image_Re,1,0,CV_L2,NULL);

	////test
	//cvMinMaxLoc(image_Re, &m, &M, NULL, NULL, NULL);
	////�Ը���ҶNFPȡ����ֵ
	//cvAbs(image_Re,image_Re);

	////test
	//cvMinMaxLoc(image_Re, &m, &M, NULL, NULL, NULL);



	////���㸵��Ҷϵ����
	//double h = FT_Entropy(image_Re, dft_N, dft_M);

	//double e = FT_Energy(image_Re, dft_N, dft_M);

	//double i = FT_Inertia(image_Re, dft_N, dft_M);


	////�洢����
	//featurefilename+=".txt";
	//
	//FILE* file = fopen(featurefilename.c_str(),"w");
	//fprintf_s(file,"%.6f\n",h);
	//fprintf_s(file,"%.6f\n",e);
	//fprintf_s(file,"%.6f\n",i);
	//fclose(file);
	//return 0;
}

void CMagicCabsineUniversalProperty_feature_texture_spectral_DFT::SaveProperty()
{

	cvSaveImage("D:\\FTtest.jpg",image_Re_save,NULL);
}

void CMagicCabsineUniversalProperty_feature_texture_spectral_DFT::SavePropertyFile(string filepath)
{

	cvSaveImage(filepath.c_str(),image_Re_save,NULL);
}

void CMagicCabsineUniversalProperty_feature_texture_spectral_DFT::LoadProperty()
{
}

void CMagicCabsineUniversalProperty_feature_texture_spectral_DFT::LoadPropertyFile(string filepath)
{

}

void CMagicCabsineUniversalProperty_feature_texture_spectral_DFT::DeleteProperty()
{
	cvReleaseImage(&image_Re_save);
}

void CMagicCabsineUniversalProperty_feature_texture_spectral_DFT::cvShiftDFT(CvArr * src_arr, CvArr * dst_arr )
{
	CvMat * tmp;
	CvMat q1stub, q2stub;
	CvMat q3stub, q4stub;
	CvMat d1stub, d2stub;
	CvMat d3stub, d4stub;
	CvMat * q1, * q2, * q3, * q4;
	CvMat * d1, * d2, * d3, * d4;

	CvSize size = cvGetSize(src_arr);
	CvSize dst_size = cvGetSize(dst_arr);
	int cx, cy;

	if(dst_size.width != size.width || 
		dst_size.height != size.height){
			cvError( CV_StsUnmatchedSizes, "cvShiftDFT", "Source and Destination arrays must have equal sizes", __FILE__, __LINE__ );   
	}

	if(src_arr==dst_arr){
		tmp = cvCreateMat(size.height/2, size.width/2, cvGetElemType(src_arr));
	}

	cx = size.width/2;
	cy = size.height/2; // image center

	q1 = cvGetSubRect( src_arr, &q1stub, cvRect(0,0,cx, cy) );
	q2 = cvGetSubRect( src_arr, &q2stub, cvRect(cx,0,cx,cy) );
	q3 = cvGetSubRect( src_arr, &q3stub, cvRect(cx,cy,cx,cy) );
	q4 = cvGetSubRect( src_arr, &q4stub, cvRect(0,cy,cx,cy) );
	d1 = cvGetSubRect( dst_arr, &d1stub, cvRect(0,0,cx,cy) );
	d2 = cvGetSubRect( dst_arr, &d2stub, cvRect(cx,0,cx,cy) );
	d3 = cvGetSubRect( dst_arr, &d3stub, cvRect(cx,cy,cx,cy) );
	d4 = cvGetSubRect( dst_arr, &d4stub, cvRect(0,cy,cx,cy) );

	if(src_arr!=dst_arr){
		if( !CV_ARE_TYPES_EQ( q1, d1 )){
			cvError( CV_StsUnmatchedFormats, "cvShiftDFT", "Source and Destination arrays must have the same format", __FILE__, __LINE__ ); 
		}
		cvCopy(q3, d1, 0);
		cvCopy(q4, d2, 0);
		cvCopy(q1, d3, 0);
		cvCopy(q2, d4, 0);
	}
	else{
		cvCopy(q3, tmp, 0);
		cvCopy(q1, q3, 0);
		cvCopy(tmp, q1, 0);
		cvCopy(q4, tmp, 0);
		cvCopy(q2, q4, 0);
		cvCopy(tmp, q2, 0);
	}
}

void CMagicCabsineUniversalProperty_feature_texture_spectral_DFT::SplitImage(const IplImage *imgSrc, const int n, vector<IplImage*> &subImgs)
{
	IplImage *img = cvCloneImage(imgSrc);
	int subWidth  = cvFloor(img->width/n);
	int subHeight = cvFloor(img->height/n);
	for(int y=0; y<n; y++)//from top to bottom, left to right
	{
		for(int x=0; x<n; x++)
		{
			cvSetImageROI(img, cvRect(x*subWidth, y*subHeight, subWidth, subHeight));
			IplImage *roiImg = cvCreateImage(cvSize(subWidth,subHeight),img->depth,3);
			cvCopy(img, roiImg, 0);
			subImgs.push_back(roiImg);
			cvResetImageROI(img);
		}
	}
	cvReleaseImage(&img);
}

float CMagicCabsineUniversalProperty_feature_texture_spectral_DFT::FT_Entropy(CvArr* src_arr)
{
	return 0;
}

float CMagicCabsineUniversalProperty_feature_texture_spectral_DFT::FT_Energy(CvArr* src_arr)
{
	return 0;
}

float CMagicCabsineUniversalProperty_feature_texture_spectral_DFT::FT_Inertia(CvArr* src_arr)
{
	return 0;
}