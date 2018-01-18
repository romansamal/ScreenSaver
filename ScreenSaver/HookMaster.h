#pragma once
#include <Windows.h>
#pragma comment (lib, "User32.lib")

class HookMaster
{
private:
	static HHOOK hookHandle;
	static HookMaster *instance;
	HookMaster();
public:
	void setupHook();
	static HookMaster *getInstance();
	static LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);
	~HookMaster();
};

