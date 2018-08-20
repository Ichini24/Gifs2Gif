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


void glueGifs()
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
}

void dumpbytes(const std::vector<char>& v)
{
	//std::ofstream f("D:\\giffs\\new\\s3.txt");
	for (int i = 0; i<v.size(); ++i)
	{
		if (i > v.size()*0.8)
		{
			//f<< v[i];
			printf("%u ", (unsigned char)v[i]);
			if ((i + 1) % 16 == 0)
			{
				printf("\n");
				//f << "\n";
			}
		}
	}
	printf("\n");
	//f<<("\n");
}

void dumphex(const std::vector<char>& v)
{
	const int N = 16;
	const char hex[] = "0123456789ABCDEF";
	char buf[N * 4 + 5 + 2];
	for (int i = 0; i < v.size(); ++i)
	{
		int n = i % N;
		if (n == 0)
		{
			if (i)
				puts(buf);
			memset(buf, 0x20, sizeof(buf));
			buf[sizeof(buf) - 2] = '\n';
			buf[sizeof(buf) - 1] = '\0';
		}
		unsigned char c = (unsigned char)v[i];
		buf[n * 3 + 0] = hex[c / 16];
		buf[n * 3 + 1] = hex[c % 16];
		buf[3 * N + 5 + n] = (c >= ' ' && c <= '~') ? c : '.';
	}
	puts(buf);
}

std::vector<std::string> compare(std::ifstream &f1, std::ifstream &f2)
{
	std::string s1 = "", s2 = "";
	while (!f1.eof())
	{
		char c1, c2;
		f1.get(c1);
		f2.get(c2);
		if (c1 == c2)
		{
			printf("%u ", (unsigned char)c1);
		}
		else
		{
			break;
		}

	}

	//std::vector<std::string> str1, str2, str;
	//if (f1)
	//{
	//	std::string s1;
	//	std::getline(f1, s1);
	//	str1.push_back(s1);
	//}

	//if (f2)
	//{
	//	std::string s2;
	//	std::getline(f2, s2);
	//	str2.push_back(s2);
	//}

	//for (int i = 0; i < str1.size(); i++)
	//{
	//	if (str1[i] == str2[i])
	//	{
	//		str.push_back(str1[i]);
	//	}
	//	else
	//	{
	//		break;
	//	}
	//}


	////std::cout << "is size eq: " << (buffer1.size() == buffer2.size()) << std::endl;
	////std::cout << "size: " << buffer1.size();

	////for (int i = 0; i < buffer1.size(); i++)
	////{
	////	char c1 = buffer1[i];
	////	char c2 = buffer2[i];
	////	std::cout << c1 << '=' <<c2 << std::endl;

	////	if (c1 == c2)
	////	{
	////		str += c1;
	////	}
	////	else
	////	{
	////		break;
	////	}
	////}
	//return str;
	return std::vector<std::string>{"gfds"};
}


void gluevideos()
{
	tic();
	cv::VideoCapture t("D:\\giffs\\new\\0.gif");
	cv::Mat frame;
	t >> frame;

	cv::VideoCapture cap1("D:\\giffs\\new\\0.gif");
	cv::VideoCapture cap2("D:\\giffs\\new\\1.gif");

	cv::VideoWriter outputVideo;
	outputVideo.open("D:\\giffs\\new\\01.mp4", cv::VideoWriter::fourcc('M', 'P', '4', '2'), 24, frame.size());

	for (; ; )
	{
		cap1 >> frame;
		if (frame.empty())
		{
			break;
		}
		outputVideo << frame;
	}

	for (; ; )
	{
		cap2 >> frame;
		if (frame.empty())
		{
			break;
		}
		outputVideo << frame;
	}
	toc();
}

void clip()
{
	std::ofstream out("D:\\giffs\\new\\out.gif", std::ios_base::binary);
	std::ifstream f1("D:\\giffs\\new\\0.gif", std::ios_base::binary);
	std::ifstream f2("D:\\giffs\\new\\1.gif", std::ios_base::binary);


	out << f1.rdbuf() << f2.rdbuf();

	//int size1 = f1.tellg();
	//f1.seekg(0, std::ios::beg);
	//std::vector<char> buffer1, buffer2, buffer3;
	//buffer1.resize(size1);
	//f1.read(buffer1.data(), size1);

	//int size2 = f2.tellg();
	//f2.seekg(0, std::ios::beg);
	//buffer2.resize(size2);
	//f2.read(buffer2.data(), size2);

	//int size3 = size1 + size2 - 15;
	//buffer3.resize(size3);

	//for (int i = 0; i<buffer1.size() - 2; i++)
	//{
	//	buffer3[i] = buffer1[i];
	//}

	//for (int i = 13; i < buffer2.size(); i++)
	//{
	//	buffer3[i - 13 + size1 - 2] = buffer2[i];
	//}

	//char *buf = new char[buffer3.size()];
	//for (int i = 0; i < buffer3.size(); i++)
	//{
	//	buf[i] = buffer3[i];
	//}

	//std::cout << "size1: " << buffer1.size() << "\nsize2: " << buffer2.size() << "\nsize3: " << buffer3.size() << std::endl;
	//out.write(buf, sizeof buf);
}