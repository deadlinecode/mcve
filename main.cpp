#include <cstdint>
#include <iostream>
#include <thread>
#include <mutex>
#include <Windows.h>

typedef bool (*CallbackFunc)(int32_t);

void* cb = NULL;
std::mutex cb_mutex;
bool stopT1 = false;

void threadFunction() {
    while (!stopT1) {
        Sleep(1000);
        std::cout << "Thread running..." << std::endl;

        CallbackFunc func = nullptr;
        {
            std::lock_guard<std::mutex> lock(cb_mutex);
            func = reinterpret_cast<CallbackFunc>(cb);
        }

        if (func) {
            std::cout << "Calling callback..." << std::endl;
            func(22);
        }
        else {
            std::cout << "Callback is NULL." << std::endl;
        }
    }
    std::cout << "Thread exiting..." << std::endl;
}

std::thread t1(threadFunction);

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
    switch (fdwReason) {
    case DLL_PROCESS_DETACH:
        // sig thread ==> stop
        stopT1 = true;

        // join thread ==> unload
        t1.join();
        break;
    }
    return TRUE;
}

extern "C" __declspec(dllexport) bool onChange(void* callback) {
    std::lock_guard<std::mutex> lock(cb_mutex);
    cb = callback;

    return true;
}