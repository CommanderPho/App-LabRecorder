#pragma once

#ifdef _WIN32
#include <windows.h>
#include <cstdio>
#endif

// Runtime Windows console control helper. No-ops on non-Windows.

inline void showConsoleWindow() {
#ifdef _WIN32
	// If already attached, just show it; otherwise allocate a new console.
	HWND hWnd = GetConsoleWindow();
	if (!hWnd) {
		// Try attaching to parent process console first; if that fails, allocate new.
		if (!AttachConsole(ATTACH_PARENT_PROCESS)) {
			AllocConsole();
		}
		// Rebind stdout/stderr so qInfo()/printf work.
		FILE *fp;
		freopen_s(&fp, "CONOUT$", "w", stdout);
		freopen_s(&fp, "CONOUT$", "w", stderr);
		hWnd = GetConsoleWindow();
	}
	if (hWnd) ShowWindow(hWnd, SW_SHOW);
#endif
}

inline void hideConsoleWindow() {
#ifdef _WIN32
	HWND hWnd = GetConsoleWindow();
	if (hWnd) {
		// Hide but keep attached so stdout/stderr remain valid and output is retained.
		ShowWindow(hWnd, SW_HIDE);
	}
#endif
}

inline bool isConsoleWindowVisible() {
#ifdef _WIN32
	HWND hWnd = GetConsoleWindow();
	if (!hWnd) return false;
	return IsWindowVisible(hWnd) != 0;
#else
	return false;
#endif
}


