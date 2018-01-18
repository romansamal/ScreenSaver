#include "HookMaster.h"

HHOOK HookMaster::hookHandle = NULL;
HookMaster *HookMaster::instance = NULL;

HookMaster::HookMaster()
{
}

void HookMaster::setupHook()
{
	this->hookHandle = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, 0, 0);
}

HookMaster::~HookMaster()
{
	if (instance)
		delete instance;
}

LRESULT CALLBACK HookMaster::KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	return CallNextHookEx(hookHandle, nCode, wParam, lParam);
}

HookMaster *HookMaster::getInstance()
{
	if (!instance)
		instance = new HookMaster();
	return instance;
}