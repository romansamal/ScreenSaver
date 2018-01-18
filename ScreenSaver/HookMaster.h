#pragma once
#include <Windows.h>
#include <string>
using namespace std;
#pragma comment (lib, "User32.lib")

class HookMaster
{
private:
	HWND hParentWnd;
	HHOOK hookHandle;
	static HookMaster *instance;
	HookMaster(HWND hParent);
public:
	static const LONG HOOKMASTER_SHOW_HIDE_CODE = 0xCC;
	void setupHook();
	static HookMaster *getInstance();
	static LRESULT CALLBACK keyboardProc(int nCode, WPARAM wParam, LPARAM lParam);
	static HookMaster *createInstance(HWND hParent);
	~HookMaster();
};

