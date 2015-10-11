#include "docanny.h"

#define debug_matcanny NOTHING
#define debug_Iplcanny NOTHING

IplImage* docannyIpl(
	IplImage* in,
	double lowThresh,
	double highThresh,
	int aperture)
{
	//Canny only have scale image
	if (in->nChannels == 1)
	{
		return 0;
	}
	//Create new image
	IplImage* out = cvCreateImage(
		CvSize(cvGetSize(in)),
		IPL_DEPTH_8U,
		1);
#if debug_Iplcanny==CREATEIpl
	cvNamedWindow("Debug");
	cvShowImage("Debug",out);
	cvWaitKey(0);
	cvDestroyWindow("Debug");
#endif
	//Canny
  	cvCanny(in, out, lowThresh, highThresh, aperture);
#if debug_Iplcanny==CANNY_I
	cvNamedWindow("Debug");
	cvShowImage("Debug",out);
	cvWaitKey(0);
	cvDestroyWindow("Debug");
#endif
	//
	printf("the canny is OK!\r\n");
	//
	return out;
};

CvMat* docannyMat(
	CvMat* in,
	double lowThresh,
	double hignThresh,
	int aperture
	)
{
	//Get the IplImage
	IplImage* intemp = cvCreateImage(cvGetSize(in), IPL_DEPTH_8U, 1);
	IplImage* outtemp = cvCloneImage(intemp);
	CvMat* out = cvCreateMat(in->rows, in->cols, in->type);
	//
	cvGetImage(in, intemp);
#if debug_matcanny==MATToIMAGE
	cvNamedWindow("Debug");
	cvShowImage("Debug", intemp);
	cvWaitKey(0);
	cvDestroyWindow("Debug");
#endif
	//canny
	cvCanny(intemp, outtemp, lowThresh, hignThresh, aperture);
#if debug_matcanny==CANNY_M
	cvNamedWindow("Debug");
	cvShowImage("Debug", outtemp);
	cvWaitKey(0);
	cvDestroyWindow("Debug");
#endif
	//Change the DataStructure
	cvGetMat(outtemp, out);
#if debug_matcanny==IMAGEToMAT
	cvNamedWindow("Debug");
	cvShowImage("Debug", out);
	cvWaitKey(0);
	cvDestroyWindow("Debug");
#endif
	//Release the temp IplImage
	//cvReleaseImage(&outtemp);
	//return 
	return out;
};
