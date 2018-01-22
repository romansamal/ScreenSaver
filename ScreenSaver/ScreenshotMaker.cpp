#include "ScreenshotMaker.h"


ScreenshotMaker::ScreenshotMaker()
{
}


ScreenshotMaker::~ScreenshotMaker()
{
}


HBITMAP ScreenshotMaker::takeScreen()
{
	HDC hScreenDC = CreateDCA("DISPLAY", NULL, NULL, NULL);
	int width = GetDeviceCaps(hScreenDC, HORZRES);
	int height = GetDeviceCaps(hScreenDC, VERTRES);
	HDC hMemoryDC = CreateCompatibleDC(hScreenDC);
	HBITMAP hBitmap = CreateCompatibleBitmap(hScreenDC, width, height);
	HBITMAP hOldBitmap = (HBITMAP)SelectObject(hMemoryDC, hBitmap);

	BitBlt(hMemoryDC, 0, 0, width, height, hScreenDC, 0, 0, SRCCOPY);
	hBitmap = (HBITMAP)SelectObject(hMemoryDC, hOldBitmap);
	DeleteDC(hMemoryDC);
	DeleteDC(hScreenDC);
	return hBitmap;
}

void ScreenshotMaker::saveAsPng(HBITMAP hBmp, string sPath)
{
	CImage img;
	img.Attach(hBmp);
	string sPathFinal(sPath + "\\" + getFileName() + ".png");
	CString cPath(sPathFinal.c_str());
	img.Save(cPath, ImageFormatPNG);
	return;
}

string ScreenshotMaker::getFileName()
{
	time_t rawtime;
	struct tm * timeinfo;
	char buffer[80] = { 0 };
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	strftime(buffer, sizeof(buffer), "%d-%m-%Y %I_%M_%S", timeinfo);
	string str(buffer);
	return str;
}