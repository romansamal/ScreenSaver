#pragma once
#include <Windows.h>
#include <atlimage.h>
#include <gdiplus.h>
#include <string>
#include <ctime>
using namespace Gdiplus;
using namespace std;
#pragma comment (lib, "Gdi32.lib")
#pragma comment (lib, "Gdiplus.lib")

class ScreenshotMaker
{
private:
	string getFileName();
public:
	ScreenshotMaker();
	~ScreenshotMaker();
	HBITMAP takeScreen();
	void saveAsPng(HBITMAP hBmp, std::string sPath);
};

