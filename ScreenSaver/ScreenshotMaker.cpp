#include "ScreenshotMaker.h"


ScreenshotMaker::ScreenshotMaker()
{
}


ScreenshotMaker::~ScreenshotMaker()
{
}


void ScreenshotMaker::takeScreen()
{/*
	HDC hScreenDC = CreateDCA("DISPLAY", NULL, NULL, NULL);
	int width = GetDeviceCaps(hScreenDC, HORZRES);
	int height = GetDeviceCaps(hScreenDC, VERTRES);
	HDC hMemoryDC = CreateCompatibleDC(hScreenDC);
	HBITMAP hBitmap = CreateCompatibleBitmap(hScreenDC, width, height);
	HBITMAP hOldBitmap = (HBITMAP)SelectObject(hMemoryDC, hBitmap);

	BitBlt(hMemoryDC, 0, 0, width, height, hScreenDC, 0, 0, SRCCOPY);
	hBitmap = (HBITMAP)SelectObject(hMemoryDC, hOldBitmap);
	DeleteDC(hMemoryDC);
	DeleteDC(hScreenDC);*/
}