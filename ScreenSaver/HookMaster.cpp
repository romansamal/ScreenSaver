#include "HookMaster.h"

HookMaster *HookMaster::instance = NULL;

HookMaster::HookMaster(HWND hParent)
{
	this->hParentWnd = hParent;
}

void HookMaster::setupHook()
{
	this->hHook = SetWindowsHookEx(WH_KEYBOARD_LL, keyboardProc, 0, 0);
}

HookMaster::~HookMaster()
{
	if (instance)
		delete instance;
}

LRESULT CALLBACK HookMaster::keyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	KBDLLHOOKSTRUCT hookedKey = *((KBDLLHOOKSTRUCT*)lParam);
	if (ScreenSaver::PressKeyForm::IsWaiting)
	{
		ScreenSaver::PressKeyForm::CloseForm();
		SendMessage(instance->hParentWnd, instance->HOOKMASTER_NEW_SCREEN_KEY, NULL, hookedKey.vkCode);
	}
	//Check for Alt+Win+PrtScr
	if (hookedKey.vkCode == VK_SNAPSHOT && wParam == WM_SYSKEYDOWN && (GetAsyncKeyState(VK_LWIN) & (1 << 15)))
	{
		SendMessage(instance->hParentWnd, instance->HOOKMASTER_SHOW_HIDE_CODE, NULL, NULL);
	}
	return CallNextHookEx(instance->hHook, nCode, wParam, lParam);
}

HookMaster *HookMaster::getInstance()
{
	return instance;
}

HookMaster *HookMaster::createInstance(HWND hParent)
{
	if (!instance)
		instance = new HookMaster(hParent);
	return instance;
}