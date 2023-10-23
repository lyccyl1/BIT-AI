#ifndef MEMORYINFO_H
#define MEMORYINFO_H

#include <stdio.h>
#include <windows.h>
#include <cstdio>
#include <iostream>
#include "shlwapi.h"
#include "tlhelp32.h"
#include "psapi.h"
#include <QStringList>

#define DIV_GB (1024 * 1024 * 1024)
#define DIV_KB (1024)
class MemoryInfo
{
public:
    MemoryInfo();
    MEMORYSTATUSEX GetMemoryInfo();
    SYSTEM_INFO GetSystemInfo1();
    PERFORMANCE_INFORMATION GetPerformanceInfo1();
    QStringList ShowAllProcessInfo();
    int *PIDlist;
    inline bool TestSet(DWORD dwTarget, DWORD dwMask);
    void ShowProtection(DWORD dwTarget,QString& line);
    QStringList processVirtualMemoryInfo(int pid);

};

#endif // MEMORYINFO_H
