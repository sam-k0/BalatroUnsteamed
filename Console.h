#pragma once


namespace Console {
#define LOGLEVEL 1

    void RedirectStdout()
    {
        // hide the main window

        if (!AllocConsole()) {
            // Add some error handling here.
            // You can call GetLastError() to get more info about the error.
            return;
        }

        // std::cout, std::clog, std::cerr, std::cin
        FILE* fDummy;
        freopen_s(&fDummy, "CONOUT$", "w", stdout);
        freopen_s(&fDummy, "CONOUT$", "w", stderr);
        freopen_s(&fDummy, "CONIN$", "r", stdin);
        std::cout.clear();
        std::clog.clear();
        std::cerr.clear();
        std::cin.clear();

        // std::wcout, std::wclog, std::wcerr, std::wcin
        HANDLE hConOut = CreateFileA(("CONOUT$"), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
        HANDLE hConIn = CreateFileA(("CONIN$"), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
        SetStdHandle(STD_OUTPUT_HANDLE, hConOut);
        SetStdHandle(STD_ERROR_HANDLE, hConOut);
        SetStdHandle(STD_INPUT_HANDLE, hConIn);
        std::wcout.clear();
        std::wclog.clear();
        std::wcerr.clear();
        std::wcin.clear();

    }

    void Print(std::string message, int level = 0)
    {
        if (level < LOGLEVEL)
			return;
        std::string prefix = "";
        switch (level)
        {
        case 0:
            prefix = "[INFO] ";
            break;
        case 1:
            prefix = "[WARNING] ";
            break;
        case 2:
            prefix = "[ERROR] ";
            break;
        default:
            prefix = "[INFO] ";
            break;
        }
        std::cout << prefix << message << std::endl;
    }
}