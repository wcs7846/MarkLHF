#pragma once

#ifndef __DOCANNY_H
#define __DOCANNY_H

//IplCanny
#define CREATEIpl   0x4
#define CANNY_I     0x5
//MatCanny
#define NOTHING     0x0
#define MATToIMAGE  0x1
#define CANNY_M     0x2
#define IMAGEToMAT  0x3

#include "main.h"

IplImage* docannyIpl(
	IplImage* in,
	double lowThresh,
	double highThresh,
	int aperture
	);

CvMat* docannyMat(
	CvMat* in,
	double lowThresh,
	double hignThresh,
	int aperture = 3
	);

#endif