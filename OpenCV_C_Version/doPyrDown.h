#pragma once

#ifndef  __DOPYRDOWN_H
#define __DOPYRDOWN_H

#include "main.h"

IplImage* dopyrdownIpl(IplImage* in, int filter = IPL_GAUSSIAN_5x5);
CvMat* dopydownMat(CvMat* in, int filer = IPL_GAUSSIAN_5x5);

#endif
