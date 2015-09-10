#pragma once
#include <Windows.h>
#include "Global.h"

class CGameWindow
{
private:
	HINSTANCE m_hInstance;		        /* ??nh danh c?a ?ng d?ng */
	HWND	  m_hWnd;			        /* ??nh danh c?a c?a s? */
	static CGameWindow* s_instance;     /* Con tr? ??n th?c th? c?a s? duy nh?t c?a l?p */
public:
	CGameWindow();
	~CGameWindow();
	/*M+==================================================================
	Method:	    CGameWindow::Init

	Summary:	Ph??ng th?c t?o ra CGameWindow.
	==================================================================-M*/
	int Init(HINSTANCE hInstance);

	/*M+==================================================================
	Method:	    CGameWindow::WinProc

	Summary:	Ph??ng th?c x? lý thông ?i?p c?a s?.
	==================================================================-M*/
	static LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	/*M+==================================================================
	Method:	    CGameWindow::GetHInstance

	Summary:	Ph??ng th?c l?y ??i t??ng Handle Instance.
	==================================================================-M*/
	HINSTANCE GetHInstance();

	/*M+==================================================================
	Method:	    CGameWindow::GetHWND

	Summary:	Ph??ng th?c l?y ??i t??ng HWND.
	==================================================================-M*/
	HWND GetHWND();

	/*M+==================================================================
	Method:	    CGameWindow::GetInstance

	Summary:	Ph??ng th?c l?y th?c th? duy nh?t c?a l?p.
	==================================================================-M*/
	static CGameWindow* GetInstance();
};