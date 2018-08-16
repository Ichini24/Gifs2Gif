#pragma once
#include <opencv2/opencv.hpp>
#include <iostream>
#include "gif.h"
double tt_tic = 0;

void tic() {
	tt_tic = cv::getTickCount();
}
void toc() {
	double tt_toc = (cv::getTickCount() - tt_tic) / (cv::getTickFrequency());
	printf("toc: %4.3f sn\n", tt_toc);
} 