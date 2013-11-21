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

	IplImage * im;//输入图像必须是灰度图像
	
	
	IplImage * realInput;
	IplImage * imaginaryInput;
	IplImage * complexInput;
	int dft_M, dft_N;
	CvMat* dft_A, tmp;
	IplImage * image_Im;
	IplImage * image_Re;

	double m, M;
	
	//灰度图转化
	IplImage *srcimg_cvt = cvCreateImage(cvGetSize(srcImage),IPL_DEPTH_8U,3);//源图像格式化图像
	im = cvCreateImage(cvGetSize(srcImage),IPL_DEPTH_8U,1);
	cvConvertScale(srcImage,srcimg_cvt);//源图像格式化 转换成 IPL_DEPTH_32F 3通道
	cvCvtColor(srcImage,im,CV_BGR2GRAY);//源图像转换成灰度图
	cvReleaseImage(&srcimg_cvt);

	realInput = cvCreateImage( cvGetSize(srcImage), IPL_DEPTH_64F, 1);//灰度图像
	imaginaryInput = cvCreateImage( cvGetSize(srcImage), IPL_DEPTH_64F, 1);//灰度图像
	complexInput = cvCreateImage( cvGetSize(srcImage), IPL_DEPTH_64F, 2);

	cvScale(im, realInput, 1.0, 0.0);//从8u转换成32f 提高精度
	cvZero(imaginaryInput);
	//将单通道图像合并成多通道图像（将realInput和imageinaryImput合并到双通道图像complexInput）
	cvMerge(realInput, imaginaryInput, NULL, NULL, complexInput);

	/*dft_M = cvGetOptimalDFTSize( im->height - 1 );
	dft_N = cvGetOptimalDFTSize( im->width - 1 );*/

	dft_M = im->height;
	dft_N = im->width;
	dft_A = cvCreateMat( dft_M, dft_N, CV_64FC2 );
	image_Re = cvCreateImage( cvSize(dft_N, dft_M), IPL_DEPTH_64F, 1);//DFT最佳尺寸的图像
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

	//正规化傅里叶变换图像使其可以被存储
	image_Re_save = cvCreateImage(cvSize(dft_N,dft_M),IPL_DEPTH_64F,1);//注意本来应该在初始化中创建，但是由于大小参数无法估计故在此创建需要在析构函数中release
	cvNormalize(image_Re,image_Re_save,255,0,CV_MINMAX,NULL);



	cvReleaseImage(&im);
	cvReleaseImage(&realInput);
	cvReleaseImage(&imaginaryInput);
	cvReleaseImage(&complexInput);
	cvReleaseImage(&image_Re);
	cvReleaseImage(&image_Im);

	////对傅里叶进行正规化使用L2(欧几里得)范式获取正规化傅里叶系数NFP,以计算3个傅里叶系数,未加绝对值
	//cvNormalize(image_Re,image_Re,1,0,CV_L2,NULL);

	////test
	//cvMinMaxLoc(image_Re, &m, &M, NULL, NULL, NULL);
	////对傅里叶NFP取绝对值
	//cvAbs(image_Re,image_Re);

	////test
	//cvMinMaxLoc(image_Re, &m, &M, NULL, NULL, NULL);



	////计算傅里叶系数熵
	//double h = FT_Entropy(image_Re, dft_N, dft_M);

	//double e = FT_Energy(image_Re, dft_N, dft_M);

	//double i = FT_Inertia(image_Re, dft_N, dft_M);


	////存储特征
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