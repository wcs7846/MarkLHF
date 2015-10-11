
#include "main.h"

#define TEST WIDTHSTEPTEST

int main()
{
//	IplImage* img = cvLoadImage("PictureSource1.jpg");
//	IplImage* temp = 0;
//	/*---------------------------------------------------------------------------------------------------*/
//	cvNamedWindow("Testing");
//	temp = dopyrdownIpl(img);
//	cvShowImage("Testing",temp);
	/*---------------------------------------------------------------------------------------------------*/
	CvMat* mattesting = cvLoadImageM("PictureSource1.jpg");;
	CvMat* matpyr = 0;
	matpyr = dopydownMat(mattesting);
	cvNamedWindow("MatPYR", CV_WINDOW_AUTOSIZE);
	cvShowImage("MatPYR", matpyr);
	/*---------------------------------------------------------------------------------------------------*/
#if TEST==RECTANGLE
	CvMat* Mattemp = 0;
	Mattemp = cvCloneMat(matpyr);
	cvRectangle(Mattemp, cvPoint(5, 10), cvPoint(255, 255), cvScalar(255, 255, 255));
	cvNamedWindow("MatClone", CV_WINDOW_AUTOSIZE);
	cvShowImage("MatClone", Mattemp);
	cvWaitKey(0);
	cvDestroyWindow("MatClone");
	cvReleaseMat(&Mattemp);
#endif
	/*---------------------------------------------------------------------------------------------------*/
#if TEST==CANNY
	CvMat* MatCannyIn;
	CvMat* MatCannyOut = cvCreateMat(matpyr->rows, matpyr->cols, matpyr->type);
	MatCannyIn = cvCloneMat(matpyr);
	MatCannyOut = docannyMat(MatCannyIn, 10, 100);

	cvNamedWindow("MatCanny");
	cvShowImage("MatCanny",MatCannyOut);
	cvWaitKey(0);
	cvDestroyWindow("MatCanny");
	cvReleaseMat(&MatCannyIn);
	cvReleaseMat(&MatCannyOut);
#endif
	/*---------------------------------------------------------------------------------------------------*/ 
#if TEST==MAT_ELEM
	CvMat* MatELEM = cvCreateMat(matpyr->rows, matpyr->cols, matpyr->type);
	float element_test = CV_MAT_ELEM(*MatELEM, float, matpyr->rows-2, matpyr->rows-3);
	printf("element_test = %f\r\n", element_test);
	cvWaitKey(0);
	cvNamedWindow("MatELEM");
	cvShowImage("MatELEM", MatELEM);
	cvWaitKey(0);
 	cvDestroyWindow("MatELEM");
#endif
	/*---------------------------------- -----------------------------------------------------------------*/
#if TEST==GETMATPointData
	float val[] = { 0.86,-0.5,0.5,0.84,0, 0.86,-0.5,0.5,0.84,0, 0.86,-0.5,0.5,0.84,0, 0.86,-0.5,0.5,0.84,0, 0.86,-0.5,0.5,0.84,0 };
	float* Point = 0;
	float SUMResult = 0;
	CvMat* MatSUM = cvCreateMat(5, 3, CV_32FC1);
	cvInitMatHeader(MatSUM,MatSUM->rows,MatSUM->cols,MatSUM->type,&val);
	for (size_t row = 0; row < MatSUM->rows; row++)
	{
		Point = (float*)(MatSUM->data.ptr + row*MatSUM->step);
		for (size_t col = 0; col < MatSUM->cols; col++)
		{
			printf("%f\t",*Point); 
			SUMResult += *(Point);
			Point++;
		}
		printf("\r\n");
	}
	printf("TheSUMResult=%f\r\n",SUMResult);
	printf("MatSUM->rows=%d\r\n", MatSUM->rows);
	printf("MatSUM->cols=%d\r\n ", MatSUM->cols);
	
	cvWaitKey(0);
	cvReleaseMat(&MatSUM);
#endif
	/*---------------------------------- -----------------------------------------------------------------*/
#if TEST==ROITEST
	/*
		Using the ROI to come true 
	*/
	IplImage* MatToImage = cvCreateImage(cvGetSize(matpyr), IPL_DEPTH_8U, 3);
	cvGetImage(matpyr, MatToImage);
	cvNamedWindow("MatToImage");
	cvShowImage("MatToImage", MatToImage);
	cvWaitKey(0);

	cvSetImageROI(MatToImage, cvRect(10, 10, matpyr->rows - 30, matpyr->cols - 60));
	cvAddS(MatToImage, cvScalar(200), MatToImage);
	cvResetImageROI(MatToImage);
	
	cvNamedWindow("ROITEST");
	cvShowImage("ROITEST", MatToImage);
	cvWaitKey(0);
	cvDestroyWindow("ROITEST");
#endif
	/*---------------------------------- -----------------------------------------------------------------*/
#if TEST==WIDTHSTEPTEST
	/*
		Using WidthStep to come true
	*/
	//The picture source is matpyr
	
#endif
	/*---------------------------------- -----------------------------------------------------------------*/
	printf("\tEND\t \r\n");
	cvWaitKey(0);
//	cvReleaseImage(&img); 
//	cvReleaseImage(&temp);
	cvReleaseMat(&matpyr);
	cvReleaseMat(&mattesting);
	cvDestroyAllWindows();
}


//键盘响应回调函数
