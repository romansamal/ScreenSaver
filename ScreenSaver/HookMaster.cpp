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
	//Check for Alt+Win+PrtScr
	if (hookedKey.vkCode == VK_SNAPSHOT && wParam == WM_SYSKEYDOWN && (GetAsyncKeyState(VK_LWIN) & (1 << 15)))
	{
		SendMessage(instance->hParentWnd, instance->HOOKMASTER_SHOW_HIDE_CODE, NULL, NULL);
	}
	else if (wParam == WM_KEYDOWN)
	{
		if (instance->nScreenKey == hookedKey.vkCode)
		{
			SendMessage(instance->hParentWnd, instance->HOOKMASTER_MAKE_SCREENSHOT, NULL, NULL);
		}
		else if (ScreenSaver::PressKeyForm::IsWaiting)
		{
			ScreenSaver::PressKeyForm::CloseForm();
			SendMessage(instance->hParentWnd, instance->HOOKMASTER_NEW_SCREEN_KEY, NULL, hookedKey.vkCode);
			instance->nScreenKey = hookedKey.vkCode;
		}
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