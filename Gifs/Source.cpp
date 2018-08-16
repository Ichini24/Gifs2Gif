#include "Header.h"

int main()
{ 
	std::string path = "D:\\giffs\\new\\";
	cv::VideoCapture tc(path + std::to_string(0) + ".gif");
	cv::Mat frame;
	tc >> frame;

	GifWriter writer;
	
	uint32_t ww = frame.cols, wh = frame.rows;
	tic();
	GifBegin(&writer, "D:\\giffs\\new\\output.gif", ww, wh, 3);
	for (int i = 0; i < 6; i++)
	{
		cv::VideoCapture cap(path + std::to_string(i) + ".gif");
		for (; ; )
		{
			cap >> frame;
			if (frame.empty())
			{
				break;
			}
			cv::cvtColor(frame, frame, cv::COLOR_BGR2RGBA);
			GifWriteFrame(&writer, frame.data, ww, wh, 3);
		}
	}
	GifEnd(&writer);
	toc();


	return 1;
}