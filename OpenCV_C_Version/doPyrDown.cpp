#include "doPyrDown.h"

IplImage* dopyrdownIpl(IplImage* in, int filter)
{
	assert((in->width % 2 == 0) && (in->height % 2 == 0));

	IplImage* out = cvCreateImage(
		cvSize(in->width / 2, in->height / 2),
		in->depth,
		in->nChannels);
	//PyrDown
	cvPyrDown(in, out, filter);
	//return 
	return out;
};

CvMat* dopydownMat(CvMat* in, int filer)
{
	assert((in->width % 2 == 0) && (in->height % 2 == 0));

	CvMat* out = cvCreateMat(in->rows / 2, in->cols / 2, in->type);
	//PyrDown
	cvPyrDown(in, out, filer);
	//return 
	return out;
};

