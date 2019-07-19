#include <iostream>
#include "include/Game.h"
#include <stdexcept>

#ifdef _WIN32
#include <Windows.h>
#endif




using namespace std;

int main() {

#ifdef _WIN32
    // Set console code page to UTF-8 so console known how to interpret string data
    SetConsoleOutputCP(CP_UTF8);
    // Enable buffering to prevent VS from chopping up UTF-8 byte sequences
    setvbuf(stdout, nullptr, _IOFBF, 1000);
#endif

    try {

        Game::newGame().run();
    } catch (const std::exception &e) {

        cerr << "Exception: " << e.what() << '\n';
    } catch (...) {
        cerr << "Unknown Exception" << '\n';
    }
    return 0;
}