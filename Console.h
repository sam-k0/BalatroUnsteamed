#pragma once

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"
#define LOGLEVEL 0
#define LOG_INFO 0
#define LOG_WARNING 1
#define LOG_ERROR 2

namespace Console {


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

    void PrintRainbow(const std::string& text) {
        int colors[] = {
            FOREGROUND_RED | FOREGROUND_INTENSITY,         // Red
            FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY, // Yellow
            FOREGROUND_GREEN | FOREGROUND_INTENSITY,       // Green
            FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY, // Cyan
            FOREGROUND_BLUE | FOREGROUND_INTENSITY,        // Blue
            FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY  // Magenta
        };
        int numColors = sizeof(colors) / sizeof(colors[0]);

        for (size_t i = 0; i < text.size(); ++i) {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colors[i % numColors]);
            std::cout << text[i];
        }
        std::cout << std::endl;
        // Reset console color
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // White
    }

    void Print(const std::string& message, int level = LOG_INFO) {
        if (level < LOGLEVEL)
            return;

        std::string prefix;

        switch (level) {
        case LOG_INFO:
            prefix = "[INFO] ";
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // White
            break;
        case LOG_WARNING:
            prefix = "[WARNING] ";
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN); // Yellow
            break;
        case LOG_ERROR:
            prefix = "[ERROR] ";
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED); // Red
            break;
        default:
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN); // Green
            prefix = "[INFO] ";
            break;
        }

        // Print message with color
        std::cout << prefix << message << std::endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // White
    }
}