#include "stdafx.h"

#include "CMagicCabsineUniversalProperty_feature_texture_spectral_gabor.h"

CMagicCabsineUniversalProperty_feature_texture_spectral_gabor::CMagicCabsineUniversalProperty_feature_texture_spectral_gabor(const IplImage *tempSrcImage)
	:CMagicCabsineUniversalProperty(tempSrcImage)
{
	image_Re_save = cvCreateImage(cvGetSize(srcImage),IPL_DEPTH_8U,1);//存储图像
	srcImage_grayscale = cvCreateImage(cvGetSize(srcImage),IPL_DEPTH_8U,1);//源图像灰度图
	IplImage * srcImage_cvt = cvCreateImage(cvGetSize(srcImage),IPL_DEPTH_8U,3);//临时转换图
	
	cvConvertScale(srcImage,srcImage_cvt);
	cvCvtColor(srcImage_cvt,srcImage_grayscale,CV_BGR2GRAY);

	cvReleaseImage(&srcImage_cvt);
}

CMagicCabsineUniversalProperty_feature_texture_spectral_gabor::~CMagicCabsineUniversalProperty_feature_texture_spectral_gabor()
{
	cvReleaseMat( &Real );
	cvReleaseMat( &Imag );

	DeleteProperty();
}

void CMagicCabsineUniversalProperty_feature_texture_spectral_gabor::ComputeProperty()
{
		gabor(0,11,2*PI,sqrt(2.0));
		conv_img(srcImage_grayscale,image_Re_save,CV_GABOR_REAL);
}

void CMagicCabsineUniversalProperty_feature_texture_spectral_gabor::SaveProperty()
{

	cvSaveImage("D:\\Gabortest.jpg",image_Re_save,NULL);
}

void CMagicCabsineUniversalProperty_feature_texture_spectral_gabor::SavePropertyFile(string filepath)
{

	cvSaveImage(filepath.c_str(),image_Re_save,NULL);
}

void CMagicCabsineUniversalProperty_feature_texture_spectral_gabor::LoadProperty()
{
}

void CMagicCabsineUniversalProperty_feature_texture_spectral_gabor::LoadPropertyFile(string filepath)
{

}

void CMagicCabsineUniversalProperty_feature_texture_spectral_gabor::DeleteProperty()
{
	cvReleaseImage(&image_Re_save);
	cvReleaseImage(&srcImage_grayscale);
}

float CMagicCabsineUniversalProperty_feature_texture_spectral_gabor::FT_Entropy(CvArr* src_arr)
{
	return 0;
}

float CMagicCabsineUniversalProperty_feature_texture_spectral_gabor::FT_Energy(CvArr* src_arr)
{
	return 0;
}

float CMagicCabsineUniversalProperty_feature_texture_spectral_gabor::FT_Inertia(CvArr* src_arr)
{
	return 0;
}





/*!
    \fn CvGabor::CvGabor(int iMu, int iNu, double dSigma)
Construct a gabor

Parameters:
    	iMu		The orientation iMu*PI/8,    //方向（8个方向的Gabor核）
    	iNu 		The scale,               //尺度大小
	dSigma 		The sigma value of Gabor,    //Gabor的sigma

Returns:
	None

Create a gabor with a orientation iMu*PI/8, a scale iNu, and a sigma value dSigma. The spatial frequence (F) is set to sqrt(2) defaultly. It calls Init() to generate parameters and kernels.
 */
void CMagicCabsineUniversalProperty_feature_texture_spectral_gabor::gabor(int iMu, int iNu, double dSigma)
{ 
    F = sqrt(2.0);    //空间频率缺省值设置为sqrt(2.0)
    Init(iMu, iNu, dSigma, F);   //初始化，产生参数和核
}


/*!
    \fn CvGabor::CvGabor(int iMu, int iNu, double dSigma, double dF)
Construct a gabor

Parameters:
    	iMu		The orientation iMu*PI/8
    	iNu 		The scale
	dSigma 		The sigma value of Gabor
	dF		The spatial frequency        //空间频率 dF

Returns:
	None

Create a gabor with a orientation iMu*PI/8, a scale iNu, a sigma value dSigma, and a spatial frequence dF. It calls Init() to generate parameters and kernels.
 */
void CMagicCabsineUniversalProperty_feature_texture_spectral_gabor::gabor(int iMu, int iNu, double dSigma, double dF)   //空间频率和sigma都是用户自己设置的。
{

    Init(iMu, iNu, dSigma, dF);
    
}


/*!
    \fn CvGabor::CvGabor(double dPhi, int iNu)
Construct a gabor

Parameters:
    	dPhi		The orientation in arc   
    	iNu 		The scale

Returns:
	None

Create a gabor with a orientation dPhi, and with a scale iNu. The sigma (Sigma) and the spatial frequence (F) are set to 2*PI and sqrt(2) defaultly. It calls Init() to generate parameters and kernels.
 */
void CMagicCabsineUniversalProperty_feature_texture_spectral_gabor::gabor(double dPhi, int iNu)   //方向和尺度都是用户自己设置的，空间频率和sigma分别取：sqrt(2.0),2*PI
{
    Sigma = 2*PI;
    F = sqrt(2.0);
    Init(dPhi, iNu, Sigma, F);
}


/*!
    \fn CvGabor::CvGabor(double dPhi, int iNu, double dSigma)
Construct a gabor

Parameters:
    	dPhi		The orientation in arc
    	iNu 		The scale
	dSigma		The sigma value of Gabor

Returns:
	None
    
Create a gabor with a orientation dPhi, a scale iNu, and a sigma value dSigma. The spatial frequence (F) is set to sqrt(2) defaultly. It calls Init() to generate parameters and kernels.
 */
void CMagicCabsineUniversalProperty_feature_texture_spectral_gabor::gabor(double dPhi, int iNu, double dSigma) //方向、尺寸大小和sigma都是用户自己设定，空间频率用缺省值sqrt(2.0)
{

    F = sqrt(2.0);
    Init(dPhi, iNu, dSigma, F);
}


/*!
    \fn CvGabor::CvGabor(double dPhi, int iNu, double dSigma, double dF)
Construct a gabor

Parameters:
    	dPhi		The orientation in arc
    	iNu 		The scale
	dSigma 		The sigma value of Gabor
	dF		The spatial frequency 

Returns:
	None

Create a gabor with a orientation dPhi, a scale iNu, a sigma value dSigma, and a spatial frequence dF. It calls Init() to generate parameters and kernels.
 */
void CMagicCabsineUniversalProperty_feature_texture_spectral_gabor::gabor(double dPhi, int iNu, double dSigma, double dF)  //所有的都是用户自己设定。
{

   Init(dPhi, iNu, dSigma,dF);
}

/*!
    \fn CvGabor::IsInit()
Determine the gabor is initilised or not

Parameters:
	None

Returns:
	a boolean value, TRUE is initilised or FALSE is non-initilised.

Determine whether the gabor has been initlized - variables F, K, Kmax, Phi, Sigma are filled.
 */
bool CMagicCabsineUniversalProperty_feature_texture_spectral_gabor::IsInit()
{

    return bInitialised;
}

/*!
    \fn CvGabor::mask_width()
Give out the width of the mask

Parameters:
	None

Returns:
	The long type show the width.

Return the width of mask (should be NxN) by the value of Sigma and iNu.
 */
long CMagicCabsineUniversalProperty_feature_texture_spectral_gabor::mask_width()  //确定mask的宽度 （N*N窗口）
{

    long lWidth;
    if (IsInit() == false)  {
       perror ("Error: The Object has not been initilised in mask_width()!\n");
       return 0;
    }
    else {
       //determine the width of Mask
      double dModSigma = Sigma/K;
      double dWidth = (int)(dModSigma*6 + 1);
      //test whether dWidth is an odd.
      if (fmod(dWidth, 2.0)==0.0) dWidth++;
      lWidth = (long)dWidth;

      return lWidth;
    }
}


/*!
    \fn CvGabor::creat_kernel()
Create gabor kernel

Parameters:
	None

Returns:
	None

Create 2 gabor kernels - REAL and IMAG, with an orientation and a scale 
 */
void CMagicCabsineUniversalProperty_feature_texture_spectral_gabor::creat_kernel()   //创建gabor核
{
    
    if (IsInit() == false) {perror("Error: The Object has not been initilised in creat_kernel()!\n");}
    else {
      CvMat *mReal, *mImag;
      mReal = cvCreateMat( Width, Width, CV_32FC1);  //实部窗口框的大小
      mImag = cvCreateMat( Width, Width, CV_32FC1);  //虚部窗口框的大小
      
      /**************************** Gabor Function ****************************/ 
      int x, y;
      double dReal;
      double dImag;
      double dTemp1, dTemp2, dTemp3;

      for (int i = 0; i < Width; i++)
      {
          for (int j = 0; j < Width; j++)
          {
              x = i-(Width-1)/2;
              y = j-(Width-1)/2;
              dTemp1 = (pow(K,2)/pow(Sigma,2))*exp(-(pow((double)x,2)+pow((double)y,2))*pow(K,2)/(2*pow(Sigma,2)));//高斯窗口函数
              dTemp2 = cos(K*cos(Phi)*x + K*sin(Phi)*y) - exp(-(pow(Sigma,2)/2));  //实部，去噪
              dTemp3 = sin(K*cos(Phi)*x + K*sin(Phi)*y);  //虚部
              dReal = dTemp1*dTemp2;    //求得的实部
              dImag = dTemp1*dTemp3;    //求得的虚部
              //gan_mat_set_el(pmReal, i, j, dReal);
	      //cvmSet( (CvMat*)mReal, i, j, dReal );
		cvSetReal2D((CvMat*)mReal, i, j, dReal ); //存储求得的结果
              //gan_mat_set_el(pmImag, i, j, dImag);
              //cvmSet( (CvMat*)mImag, i, j, dImag );
		cvSetReal2D((CvMat*)mImag, i, j, dImag );

          } 
       }//FOR
       /**************************** Gabor Function ****************************/
       bKernel = true;
       cvCopy(mReal, Real, NULL);  //拷贝求得的结果
       cvCopy(mImag, Imag, NULL);
      //printf("A %d x %d Gabor kernel with %f PI in arc is created.\n", Width, Width, Phi/PI);
       cvReleaseMat( &mReal );
       cvReleaseMat( &mImag );
     }
}


/*!
    \fn CvGabor::get_image(int Type)
Get the speific type of image of Gabor

Parameters:
	Type		The Type of gabor kernel, e.g. REAL, IMAG, MAG, PHASE   

Returns:
	Pointer to image structure, or NULL on failure	

Return an Image (gandalf image class) with a specific Type   "REAL"	"IMAG" "MAG" "PHASE"  
 */
IplImage* CMagicCabsineUniversalProperty_feature_texture_spectral_gabor::get_image(int Type)
{

    if(IsKernelCreate() == false)
    { 
      perror("Error: the Gabor kernel has not been created in get_image()!\n");
      return NULL;
    }
    else
    {  
    IplImage* pImage;
    IplImage *newimage;
    newimage = cvCreateImage(cvSize(Width,Width), IPL_DEPTH_8U, 1 );
    //printf("Width is %d.\n",(int)Width);
    //printf("Sigma is %f.\n", Sigma);
    //printf("F is %f.\n", F);
    //printf("Phi is %f.\n", Phi);
    
    //pImage = gan_image_alloc_gl_d(Width, Width);
    pImage = cvCreateImage( cvSize(Width,Width), IPL_DEPTH_32F, 1 );
    
    
    CvMat* kernel = cvCreateMat(Width, Width, CV_32FC1);
    double ve;
//    CvScalar S;
    CvSize size = cvGetSize( kernel );
    int rows = size.height;
    int cols = size.width;
    switch(Type)
    {
        case 1:  //Real

           cvCopy( (CvMat*)Real, (CvMat*)kernel, NULL );
            //pImage = cvGetImage( (CvMat*)kernel, pImageGL );
           for (int i = 0; i < rows; i++)
    	   {
              for (int j = 0; j < cols; j++)
              {
                   ve = cvGetReal2D((CvMat*)kernel, i, j);
                   cvSetReal2D( (IplImage*)pImage, j, i, ve );
              }
           }
           break;
        case 2:  //Imag
           cvCopy( (CvMat*)Imag, (CvMat*)kernel, NULL );
           //pImage = cvGetImage( (CvMat*)kernel, pImageGL );
           for (int i = 0; i < rows; i++)
    	   {
              for (int j = 0; j < cols; j++)
              {
                   ve = cvGetReal2D((CvMat*)kernel, i, j);
                   cvSetReal2D( (IplImage*)pImage, j, i, ve );
              }
           }
           break; 
        case 3:  //Magnitude
           ///@todo  
           break;
        case 4:  //Phase
          ///@todo
           break;
    }
   
    cvNormalize((IplImage*)pImage, (IplImage*)pImage, 0, 255, CV_MINMAX, NULL );


    cvConvertScaleAbs( (IplImage*)pImage, (IplImage*)newimage, 1, 0 );

    cvReleaseMat(&kernel);

    cvReleaseImage(&pImage);

    return newimage;
    }
}


/*!
    \fn CvGabor::IsKernelCreate()
Determine the gabor kernel is created or not

Parameters:
	None

Returns:
	a boolean value, TRUE is created or FALSE is non-created.

Determine whether a gabor kernel is created.
 */
bool CMagicCabsineUniversalProperty_feature_texture_spectral_gabor::IsKernelCreate()
{

    return bKernel;
}


/*!
    \fn CvGabor::get_mask_width()
Reads the width of Mask

Parameters:
    None

Returns:
    Pointer to long type width of mask.
 */
long CMagicCabsineUniversalProperty_feature_texture_spectral_gabor::get_mask_width()
{
  return Width;
}


/*!
    \fn CvGabor::Init(int iMu, int iNu, double dSigma, double dF)
Initilize the.gabor

Parameters:
    	iMu 	The orientations which is iMu*PI.8
    	iNu 	The scale can be from -5 to infinit
    	dSigma 	The Sigma value of gabor, Normally set to 2*PI
    	dF 	The spatial frequence , normally is sqrt(2)

Returns:

Initilize the.gabor with the orientation iMu, the scale iNu, the sigma dSigma, the frequency dF, it will call the function creat_kernel(); So a gabor is created.
 */
void CMagicCabsineUniversalProperty_feature_texture_spectral_gabor::Init(int iMu, int iNu, double dSigma, double dF)
{
  //Initilise the parameters 
    bInitialised = false;
    bKernel = false;

    Sigma = dSigma;
    F = dF;
    
    Kmax = PI/2;
    
    // Absolute value of K
    K = Kmax / pow(F, (double)iNu);
    Phi = PI*iMu/8;
    bInitialised = true;
    Width = mask_width();
    Real = cvCreateMat( Width, Width, CV_32FC1);
    Imag = cvCreateMat( Width, Width, CV_32FC1);
    creat_kernel();  
}

/*!
    \fn CvGabor::Init(double dPhi, int iNu, double dSigma, double dF)
Initilize the.gabor

Parameters:
    	dPhi 	The orientations 
    	iNu 	The scale can be from -5 to infinit
    	dSigma 	The Sigma value of gabor, Normally set to 2*PI
    	dF 	The spatial frequence , normally is sqrt(2)

Returns:
	None

Initilize the.gabor with the orientation dPhi, the scale iNu, the sigma dSigma, the frequency dF, it will call the function creat_kernel(); So a gabor is created.filename 	The name of the image file
    	file_format 	The format of the file, e.g. GAN_PNG_FORMAT
    	image 	The image structure to be written to the file
    	octrlstr 	Format-dependent control structure

 */
void CMagicCabsineUniversalProperty_feature_texture_spectral_gabor::Init(double dPhi, int iNu, double dSigma, double dF)
{

    bInitialised = false;
    bKernel = false;
    Sigma = dSigma;
    F = dF;
    
    Kmax = PI/2;
    
    // Absolute value of K
    K = Kmax / pow(F, (double)iNu);
    Phi = dPhi;
    bInitialised = true;
    Width = mask_width();
    Real = cvCreateMat( Width, Width, CV_32FC1);
    Imag = cvCreateMat( Width, Width, CV_32FC1);
    creat_kernel();  
}



/*!
    \fn CvGabor::get_matrix(int Type)
Get a matrix by the type of kernel

Parameters:
    	Type		The type of kernel, e.g. REAL, IMAG, MAG, PHASE

Returns:
    	Pointer to matrix structure, or NULL on failure.

Return the gabor kernel.
 */
CvMat* CMagicCabsineUniversalProperty_feature_texture_spectral_gabor::get_matrix(int Type)
{
    if (!IsKernelCreate()) {perror("Error: the gabor kernel has not been created!\n"); return NULL;}
    switch (Type)
    {
      case CV_GABOR_REAL:
        return Real;
        break;
      case CV_GABOR_IMAG:
        return Imag;
        break;
      case CV_GABOR_MAG:
        return NULL;
        break;
      case CV_GABOR_PHASE:
        return NULL;
	  default:
		return NULL;
        break;
    }
}




/*!
    \fn CvGabor::output_file(const char *filename, Gan_ImageFileFormat file_format, int Type)
Writes a gabor kernel as an image file.

Parameters:
    	filename 	The name of the image file
    	file_format 	The format of the file, e.g. GAN_PNG_FORMAT
    	Type		The Type of gabor kernel, e.g. REAL, IMAG, MAG, PHASE   
Returns:
	None

Writes an image from the provided image structure into the given file and the type of gabor kernel.
 */
void CMagicCabsineUniversalProperty_feature_texture_spectral_gabor::output_file(const char *filename, int Type)
{
  IplImage *pImage;
  pImage = get_image(Type);
  if(pImage != NULL)
  {
    if( cvSaveImage(filename, pImage )) printf("%s has been written successfully!\n", filename);
    else printf("Error: writting %s has failed!\n", filename);
  }
  else 
    perror("Error: the image is empty in output_file()!\n"); 

  cvReleaseImage(&pImage);
}






/*!
    \fn CvGabor::show(int Type)
 */
void CMagicCabsineUniversalProperty_feature_texture_spectral_gabor::show(int Type)
{
    if(!IsInit()) {
        perror("Error: the gabor kernel has not been created!\n");
    }
    else {
          IplImage *pImage;
      pImage = get_image(Type);
      cvNamedWindow("Testing",1);
      cvShowImage("Testing",pImage);
      cvWaitKey(0);
      cvDestroyWindow("Testing");
      cvReleaseImage(&pImage);
    }

}




/*!
    \fn CvGabor::conv_img_a(IplImage *src, IplImage *dst, int Type)
 */
void CMagicCabsineUniversalProperty_feature_texture_spectral_gabor::conv_img_a(IplImage *src, IplImage *dst, int Type)   //图像做gabor卷积  函数名：conv_img_a
{
    double ve, re,im;
  
	
    int width = src->width;
    int height = src->height;
    CvMat *mat = cvCreateMat(src->width, src->height, CV_32FC1);
    
    for (int i = 0; i < width; i++)  //对整幅图像进行图像坐标转换
    {
       for (int j = 0; j < height; j++)
       {
              ve = cvGetReal2D(src, j, i);
              cvSetReal2D( (CvMat*)mat, i, j, ve );
       }
    }

    CvMat *rmat = cvCreateMat(width, height, CV_32FC1);  //存实部
    CvMat *imat = cvCreateMat(width, height, CV_32FC1);  //存虚部

    CvMat *kernel = cvCreateMat( Width, Width, CV_32FC1 ); //创建核函数窗口

    switch (Type)
    {
      case CV_GABOR_REAL:		//实部卷积
        cvCopy( (CvMat*)Real, (CvMat*)kernel, NULL );
        cvFilter2D( (CvMat*)mat, (CvMat*)mat, (CvMat*)kernel, cvPoint( (Width-1)/2, (Width-1)/2));
        break;
      case CV_GABOR_IMAG:      //虚部卷积
        cvCopy( (CvMat*)Imag, (CvMat*)kernel, NULL );
        cvFilter2D( (CvMat*)mat, (CvMat*)mat, (CvMat*)kernel, cvPoint( (Width-1)/2, (Width-1)/2));
        break;
      case CV_GABOR_MAG:   //实部与虚部卷积
        /* Real Response */
        cvCopy( (CvMat*)Real, (CvMat*)kernel, NULL );
        cvFilter2D( (CvMat*)mat, (CvMat*)rmat, (CvMat*)kernel, cvPoint( (Width-1)/2, (Width-1)/2));
        /* Imag Response */
        cvCopy( (CvMat*)Imag, (CvMat*)kernel, NULL );
        cvFilter2D( (CvMat*)mat, (CvMat*)imat, (CvMat*)kernel, cvPoint( (Width-1)/2, (Width-1)/2));
        /* Magnitude response is the square root of the sum of the square of real response and imaginary response */
        for (int i = 0; i < width; i++)
        {
           for (int j = 0; j < height; j++)
           {
               re = cvGetReal2D((CvMat*)rmat, i, j);
               im = cvGetReal2D((CvMat*)imat, i, j);
               ve = sqrt(re*re + im*im);
               cvSetReal2D( (CvMat*)mat, i, j, ve );
           }
        }       
        break;
      case CV_GABOR_PHASE:
        break;
    }
    
    if (dst->depth == IPL_DEPTH_8U)  //归一化
    {
        cvNormalize((CvMat*)mat, (CvMat*)mat, 0, 255, CV_MINMAX, NULL);
    	for (int i = 0; i < width; i++)
    	{
            for (int j = 0; j < height; j++)
            {
                ve = cvGetReal2D((CvMat*)mat, i, j);
                ve = cvRound(ve);
                cvSetReal2D( (IplImage*)dst, j, i, ve );
            }
        }
     }

     if (dst->depth == IPL_DEPTH_32F)
     {
         for (int i = 0; i < width; i++)
    	 {
            for (int j = 0; j < height; j++)
            {
                ve = cvGetReal2D((CvMat*)mat, i, j);
                cvSetReal2D( (IplImage*)dst, j, i, ve );
            }
         }
     } 

    cvReleaseMat(&kernel);
    cvReleaseMat(&imat);
    cvReleaseMat(&rmat);
    cvReleaseMat(&mat);
}


/*!
    \fn CvGabor::CvGabor(int iMu, int iNu)
 */
 void CMagicCabsineUniversalProperty_feature_texture_spectral_gabor::gabor(int iMu, int iNu)
{
  double dSigma = 2*PI; 
  F = sqrt(2.0);
  Init(iMu, iNu, dSigma, F);
}


/*!
    \fn CvGabor::normalize( const CvArr* src, CvArr* dst, double a, double b, int norm_type, const CvArr* mask )
 */
void CMagicCabsineUniversalProperty_feature_texture_spectral_gabor::normalize( const CvArr* src, CvArr* dst, double a, double b, int norm_type, const CvArr* mask )
{
    CvMat* tmp = 0;
    //__BEGIN__;

    double scale, shift;
    
    if( norm_type == CV_MINMAX )
    {
        double smin = 0, smax = 0;
        double dmin = MIN( a, b ), dmax = MAX( a, b );
        cvMinMaxLoc( src, &smin, &smax, 0, 0, mask );
        scale = (dmax - dmin)*(smax - smin > DBL_EPSILON ? 1./(smax - smin) : 0);
        shift = dmin - smin*scale;
    }
    else if( norm_type == CV_L2 || norm_type == CV_L1 || norm_type == CV_C )
    {
        CvMat *s = (CvMat*)src, *d = (CvMat*)dst;

        scale = cvNorm( src, 0, norm_type, mask );
        scale = scale > DBL_EPSILON ? 1./scale : 0.;
        shift = 0;
    }
    else {}

       
    
    if( !mask )
        cvConvertScale( src, dst, scale, shift );
    else
    {
       // CvMat stub, *dmat;
       
        cvConvertScale( src, tmp, scale, shift );
        cvCopy( tmp, dst, mask );
    }

    //__END__;

    if( tmp )
        cvReleaseMat( &tmp );
}


/*!
    \fn CvGabor::conv_img(IplImage *src, IplImage *dst, int Type)
 */
void CMagicCabsineUniversalProperty_feature_texture_spectral_gabor::conv_img(IplImage *src, IplImage *dst, int Type)   //函数名：conv_img
{
//  double ve, re,im;
	double ve;
  
   CvMat *mat = cvCreateMat(src->width, src->height, CV_32FC1);
  for (int i = 0; i < src->width; i++)
  {
    for (int j = 0; j < src->height; j++)
    {
      ve = CV_IMAGE_ELEM(src, uchar, j, i);   //CV_IMAGE_ELEM 是取图像（j，i）位置的像素值
      CV_MAT_ELEM(*mat, float, i, j) = (float)ve;  //转化成float 类型
    }
  }
  
  CvMat *rmat = cvCreateMat(src->width, src->height, CV_32FC1);
  CvMat *imat = cvCreateMat(src->width, src->height, CV_32FC1);
  
  switch (Type)
  {
  case CV_GABOR_REAL:
    cvFilter2D( (CvMat*)mat, (CvMat*)mat, (CvMat*)Real, cvPoint( (Width-1)/2, (Width-1)/2));
    break;
  case CV_GABOR_IMAG:
    cvFilter2D( (CvMat*)mat, (CvMat*)mat, (CvMat*)Imag, cvPoint( (Width-1)/2, (Width-1)/2));
    break;
  case CV_GABOR_MAG:
    cvFilter2D( (CvMat*)mat, (CvMat*)rmat, (CvMat*)Real, cvPoint( (Width-1)/2, (Width-1)/2));
    cvFilter2D( (CvMat*)mat, (CvMat*)imat, (CvMat*)Imag, cvPoint( (Width-1)/2, (Width-1)/2));
    
    cvPow(rmat,rmat,2); 
    cvPow(imat,imat,2);
    cvAdd(imat,rmat,mat); 
    cvPow(mat,mat,0.5); 
    break;
  case CV_GABOR_PHASE:
    break;
  }
  
  if (dst->depth == IPL_DEPTH_8U)
  {
    cvNormalize((CvMat*)mat, (CvMat*)mat, 0, 255, CV_MINMAX);
    for (int i = 0; i < mat->rows; i++)
    {
      for (int j = 0; j < mat->cols; j++)
      {
        ve = CV_MAT_ELEM(*mat, float, i, j);
        CV_IMAGE_ELEM(dst, uchar, j, i) = (uchar)cvRound(ve);
      }
    }
  }
  
  if (dst->depth == IPL_DEPTH_32F)
  {
    for (int i = 0; i < mat->rows; i++)
    {
      for (int j = 0; j < mat->cols; j++)
      {
        ve = cvGetReal2D((CvMat*)mat, i, j);
        cvSetReal2D( (IplImage*)dst, j, i, ve );
      }
    }
  }
  cvReleaseMat(&imat);
  cvReleaseMat(&rmat);
  cvReleaseMat(&mat);
}
