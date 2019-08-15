#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <fstream>
#include <thread>
#include <mutex>
#include <windows.h>
#include <TlHelp32.h>

#ifdef BUILD_DLL
    #define DLL_EXPORT __declspec(dllexport)
#else
    #define DLL_EXPORT __declspec(dllimport)
#endif

#endif // MAIN_H