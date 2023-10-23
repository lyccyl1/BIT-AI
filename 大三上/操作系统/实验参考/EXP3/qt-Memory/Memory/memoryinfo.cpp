#include "memoryinfo.h"
#include <QDebug>
#define SHOWMASK(dwTarget, type)          \
    if (TestSet(dwTarget, PAGE_##type)) { \
        line.append("|"+QString::fromLatin1(#type));             \
    }


MemoryInfo::MemoryInfo()
{
    PIDlist = new int[2048];
}

MEMORYSTATUSEX MemoryInfo::GetMemoryInfo() {
    MEMORYSTATUSEX statex;
    statex.dwLength = sizeof(statex);
    GlobalMemoryStatusEx(&statex);
    return statex;
}

SYSTEM_INFO MemoryInfo::GetSystemInfo1(){
    SYSTEM_INFO si;
    ZeroMemory(&si, sizeof(si));
    GetSystemInfo(&si);
    return si;
}

PERFORMANCE_INFORMATION MemoryInfo::GetPerformanceInfo1(){
    PERFORMANCE_INFORMATION pi;
    pi.cb = sizeof(pi);
    GetPerformanceInfo(&pi, sizeof(pi));
    return pi;
}

QStringList MemoryInfo::ShowAllProcessInfo(){
    int index = 0;
    QStringList sList;
    PROCESSENTRY32 pe;
    pe.dwSize = sizeof(pe);
    //获取系统中所有进程快照
    HANDLE hProcessSnap = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    //获取快照中第一个进程的相关信息
    BOOL bMore = ::Process32First(hProcessSnap, &pe);
    //遍历所有进程
    while (bMore) {
        //打开进程，获取句柄
        HANDLE hP = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pe.th32ProcessID);
        PROCESS_MEMORY_COUNTERS pmc;
        ZeroMemory(&pmc, sizeof(pmc));
        //获取相关信息，如工作集大小
        if (GetProcessMemoryInfo(hP, &pmc, sizeof(pmc))) {
            PIDlist[index++] = pe.th32ProcessID;
            QString name = QString::fromWCharArray(pe.szExeFile);
            QString output = "PID:"+QString("%1").arg(pe.th32ProcessID, 5, 10, QLatin1Char('0'))+"\t 执行文件名:"+name+ "\t\t工作集大小:"+QString::number((float)pmc.WorkingSetSize / (1024*1024),'f',2)+"MB\t\t"+"线程数为："+QString::number(pe.cntThreads);
            sList.append(output);
        }
        //获取下一个进程信息
        bMore = ::Process32Next(hProcessSnap, &pe);
    }
    CloseHandle(hProcessSnap);
    return sList;
}





inline bool MemoryInfo::TestSet(DWORD dwTarget, DWORD dwMask) {
    return ((dwTarget & dwMask) == dwMask);
}


void MemoryInfo::ShowProtection(DWORD dwTarget,QString& line) {
    SHOWMASK(dwTarget, READONLY);
    SHOWMASK(dwTarget, GUARD);
    SHOWMASK(dwTarget, NOCACHE);
    SHOWMASK(dwTarget, READWRITE);
    SHOWMASK(dwTarget, WRITECOPY);
    SHOWMASK(dwTarget, EXECUTE_READ);
    SHOWMASK(dwTarget, EXECUTE);
    SHOWMASK(dwTarget, EXECUTE_READWRITE);
    SHOWMASK(dwTarget, EXECUTE_WRITECOPY);
    SHOWMASK(dwTarget, NOACCESS);
};

QStringList MemoryInfo:: processVirtualMemoryInfo(int pid){
    QStringList sList;
    SYSTEM_INFO si;
    ZeroMemory(&si, sizeof(si));
    //获取系统信息
    GetSystemInfo(&si);
    HANDLE hProcess;
    //获得指定pid的进程句柄
    hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
    MEMORY_BASIC_INFORMATION mbi;
    ZeroMemory(&mbi, sizeof(mbi));
    //虚拟内存的起始地址
    LPCVOID pBlock = (LPVOID)si.lpMinimumApplicationAddress;
    sList.append("Address\t\t\t | Size\t\t | State\t \t | Protect\t \t | Type\t\t | "
                 "Module");
    //遍历整个虚拟内存空间
    while (pBlock < si.lpMaximumApplicationAddress) {
        if (VirtualQueryEx(hProcess, pBlock, &mbi, sizeof(mbi)) == sizeof(mbi)) {
            //获取这段内存的结束地址
            LPCVOID pEnd = (PBYTE)pBlock + mbi.RegionSize;
            TCHAR szSize[MAX_PATH];
            //获取这段内存的大小
            StrFormatByteSize(mbi.RegionSize, szSize, MAX_PATH);
            QString line = QString::number((DWORD)pBlock,16).sprintf("%.8x",(DWORD)pBlock).toUpper()+"-"+QString::number((DWORD)pEnd,16).sprintf("%.8x",(DWORD)pEnd).toUpper()+"\t";
            line.append("| "+ QString::fromWCharArray(szSize)+"  \t");
            //获取这段内存的状态
            switch (mbi.State) {
                case MEM_COMMIT:
                    line.append("| Commited\t");
                    break;
                case MEM_FREE:
                    line.append("| Free\t\t");
                    break;
                case MEM_RESERVE:
                    line.append("| Reserved\t");
                    break;
                default:
                    break;
            }
            if (mbi.Protect == 0 && mbi.State != MEM_FREE) {
                mbi.Protect = PAGE_READONLY;
            }
            //获取这段内存的保护状态
            ShowProtection(mbi.Protect,line);
            //获取这段内存的类型
            line.append("\t");
            switch (mbi.Type) {
                case MEM_IMAGE:
                    line.append("| Image\t");
                    break;
                case MEM_MAPPED:
                    line.append("| Mapped\t");
                    break;
                case MEM_PRIVATE:
                    line.append("| Private\t");
                    break;
                default:
                    break;
            }
            TCHAR szFilename[MAX_PATH];
            //获取模块文件名称
            if (GetModuleFileName((HINSTANCE)pBlock, szFilename, MAX_PATH) >
                0) {
                PathStripPath(szFilename);
                line.append("\t| "+QString::fromWCharArray(szFilename));
            }
            pBlock = pEnd;
            sList.append(line);
        }

    }
    return sList;
}

