#pragma comment (lib, "dwmapi.lib")

#include <iostream>
#include <dwmapi.h>

#include "windows/win32_window.h"

namespace opticus {

LRESULT CALLBACK Win32Window::window_process(HWND hWnd, UINT message, WPARAM wparam, LPARAM lparam) {
  switch (message) {
  case WM_DESTROY:
	  PostQuitMessage(0);
	  break;
  }

  return DefWindowProc(hWnd, message, wparam, lparam);
}

void Win32Window::open_window() {
  wcscpy_s(window_class, TEXT("OPT_CLASS"));
  wcscpy_s(title, TEXT("Sample"));

  WNDCLASSEX wcex;

  wcex.cbSize = sizeof(WNDCLASSEX);
  wcex.style = CS_HREDRAW | CS_VREDRAW;
  wcex.cbClsExtra = 0;
  wcex.cbWndExtra = 0;
  wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
  wcex.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);
  wcex.hIcon = LoadIcon(0, IDI_APPLICATION);
  wcex.hIconSm = LoadIcon(0, IDI_APPLICATION);
  wcex.lpszClassName = window_class;
  wcex.lpszMenuName = nullptr;
  wcex.hInstance = GetModuleHandle(NULL);
  wcex.lpfnWndProc = DefWindowProc;

  RegisterClassEx(&wcex);


  // Create and Display our Window.
  hWnd = CreateWindow(window_class, title, WS_OVERLAPPEDWINDOW,
	                         CW_USEDEFAULT, 0, width, height, nullptr, 
						               nullptr, GetModuleHandle(NULL), nullptr);

  COLORREF DARK_COLOR = 0x202020;
  BOOL SET_CAPTION_COLOR = SUCCEEDED(DwmSetWindowAttribute(
  hWnd, DWMWINDOWATTRIBUTE::DWMWA_CAPTION_COLOR,
  &DARK_COLOR, sizeof(DARK_COLOR)));
                           
  if (!hWnd) MessageBox(0, L"Failed to Create Win32 Window.", 0, 0);

  ShowWindow(hWnd, SW_SHOW);
}

void Win32Window::update_window() {
  while (msg.message != WM_QUIT) {
	  if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) {
	    TranslateMessage(&msg);
	    DispatchMessage(&msg);
	  }
  }
}

} // namespace opticus