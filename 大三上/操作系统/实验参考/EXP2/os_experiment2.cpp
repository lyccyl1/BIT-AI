#include <stdio.h>
#include <time.h>
#include <windows.h>
#include <iostream>
#include <string>
#define EMPTY 6
using namespace std;
HANDLE ProcessHandle[5];

typedef struct buf
{
	char  resource[EMPTY][11];// 字符串数组
	int in;//push data 指针
	int out;//取数据指针
};
// define signal 
HANDLE mutex;
HANDLE empty;
HANDLE filled;

// base operation 
// P 
void P(HANDLE semaphore) {
    WaitForSingleObject(semaphore, INFINITE);
}
// V 
void V(HANDLE semaphore){
	ReleaseSemaphore(semaphore, 1, NULL);
}
// get random sleep time 
int GetRandomSleepTime(int mintime) {
    return (rand() + GetCurrentProcessId()) % 500 + mintime;
}
// judge the buffer full or empty
int isFullOrEmpty(struct buf* buf) {
    if (buf->in == buf->out) {
        return 1;
    } else {
        return 0;
    }
}
//get random string 
void RandomString(char* out) {
    int randomNum = ((rand() + GetCurrentProcessId()) % 9) + 1;
    // initial 
	memset(out, 0, sizeof(out));
	// get random char 
    for (int i = 0; i < randomNum; i++) {
        out[i] = (char)((rand() % 26) + 'a');
    }
}
//create process，input = now_process_num
void createClone(int num_clone) {
    TCHAR szFilename[MAX_PATH];
    GetModuleFileName(NULL, szFilename, MAX_PATH);
    TCHAR szCmdLine[MAX_PATH];
    sprintf(szCmdLine, "\"%s\" %d", szFilename, num_clone);
    STARTUPINFO si;
    ZeroMemory(reinterpret_cast<void*>(&si), sizeof(si));
    si.cb = sizeof(si);
    PROCESS_INFORMATION pi;
    BOOL bCreateOK = CreateProcess(
								szFilename, 
								szCmdLine,
								NULL,
								NULL,
								FALSE,
                      			CREATE_DEFAULT_ERROR_MODE,
								NULL,
								NULL,
								&si,
								&pi);
    ProcessHandle[num_clone] = pi.hProcess;
}


//master process
void masterprocess();
// producer
int Producer(int mintime);
// consumer 
int Consumer(int mintime);

int main(int argc, TCHAR *argv[])
{
	if (argc == 1 ){
		printf("liuyichen 1120202926 07162003\n");
		masterprocess();
	}
	else {
        int n = atoi(argv[1]);
        if (n < 2) {
            Producer(1000);
        } else {
            Consumer(2000);
        }
    }
	return 0;
}

//master operation
//master process 
void masterprocess() {
    printf("the master process begins\n");
    srand((int)time(0));
    //create shared memory 
    HANDLE hMapping = CreateFileMapping(NULL,
                                        NULL, 
                                        PAGE_READWRITE, 
                                        0,
                                        sizeof(struct buf), 
                                        "FM");
    if (hMapping != INVALID_HANDLE_VALUE) {
        LPVOID pfile = MapViewOfFile(hMapping, FILE_MAP_ALL_ACCESS, 0, 0, 0);
        if (pfile != NULL) {
            ZeroMemory(pfile, sizeof(struct buf));
        }
        struct buf* buf = reinterpret_cast<struct buf*>(pfile);
		// initial shared memory
		buf->in = 0;
        buf->out = 0;
        memset(buf->resource, 0, sizeof(buf->resource));
        //remove the map 
        UnmapViewOfFile(pfile);
        pfile = NULL;
        CloseHandle(pfile);
    }   
	//create the signal 
    mutex = CreateSemaphore(NULL, 1, 1, TEXT("MUTEX"));
    empty = CreateSemaphore(NULL, EMPTY, EMPTY, TEXT("EMPTY"));
    filled = CreateSemaphore(NULL, 0, EMPTY, TEXT("FILLED"));
    //create productor: 0, 1
    createClone(0);
    createClone(1);
    //create consumer :2, 3, 4
    createClone(2);
    createClone(3);
    createClone(4);
    //wait for son end 
    WaitForMultipleObjects(5, ProcessHandle, TRUE, INFINITE);
    // remove the signal
    CloseHandle(mutex);
    CloseHandle(empty);
    CloseHandle(filled);
    printf("master process end");
}
int Producer(int mintime) {
    //create signal 
    HANDLE full = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, TEXT("FULL"));
    HANDLE empty = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, TEXT("EMPTY"));
    HANDLE mutex = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, TEXT("MUTEX"));
    //get memory map
    HANDLE hmap = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, "FM");
    LPVOID pfile = MapViewOfFile(hmap, FILE_MAP_ALL_ACCESS, 0, 0, 0);
    struct buf* buf = reinterpret_cast<struct buf*>(pfile);
	//begin to produce 
    char* array;
    int flag;
    for (int i = 0; i < 12; i++) 
    {
        Sleep(GetRandomSleepTime(mintime));
        P(empty);
        P(mutex);
        RandomString(buf->resource[buf->in]);
     array= buf->resource[buf->in];
        //update in 
        buf->in = (buf->in + 1) % EMPTY;
        flag = isFullOrEmpty(buf);
        //out 
        time_t t = time(NULL);
        struct tm* ptm = localtime(&t);
        printf("ProducerID:%6d, put data:%10s  ", (int)GetCurrentProcessId(),
             array
        );
        for (int i = 0; i < 6; i++) 
        {
            printf("buffer[%d]:%10s  ", i, buf->resource[i]);
        }
        printf("time: %d:%d:%d  ", ptm->tm_hour, ptm->tm_min, ptm->tm_sec);
        if (flag == 1) 
        {
            printf("\nbuffer full now \n");
        } 
        else 
        {
            printf("\n");
        }
        fflush(stdout);
        V(full);
        V(mutex);
    }
    //remove memory map
    UnmapViewOfFile(pfile);
    pfile = NULL;
    CloseHandle(pfile);
    //close handle
    CloseHandle(mutex);
    CloseHandle(empty);
    CloseHandle(full);
}
int Consumer(int mintime) {
    //create signal
    HANDLE full = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, TEXT("FULL"));
    HANDLE empty = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, TEXT("EMPTY"));
    HANDLE mutex = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, TEXT("MUTEX"));
     //get memory map
    HANDLE hmap = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, "FM");
    LPVOID pfile = MapViewOfFile(hmap, FILE_MAP_ALL_ACCESS, 0, 0, 0);
    struct buf* buff = reinterpret_cast<struct buf*>(pfile);
    //consume
    char* array;
    int flag;
    for (int i = 0; i < 8; i++) 
    {
        Sleep(GetRandomSleepTime(mintime));
        P(full);
        P(mutex);
        //get data 
     array = buff->resource[buff->out];
        time_t t = time(NULL);
        struct tm* ptm = localtime(&t);
        printf("ConsumerID:%6d, get data:%10s  ", (int)GetCurrentProcessId(),
             array
        );
        //clean the buffer 
        memset(buff->resource[buff->out], 0, sizeof(buff->resource[buff->out]));
        //update 
        buff->out = (buff->out + 1) % EMPTY;
        flag = isFullOrEmpty(buff);
        //out
        for (int i = 0; i < 6; i++) 
        {
            printf("buffer[%d]:%10s  ", i, buff->resource[i]);
        }
        printf("time: %d:%d:%d  ", ptm->tm_hour, ptm->tm_min, ptm->tm_sec);
        if (flag == 1) 
        {
            printf("\n buffer empty now \n");
        } 
        else 
        {
            printf("\n");
        }
        fflush(stdout);
        V(empty);
        V(mutex);
    }
    //remove memory map
    UnmapViewOfFile(pfile);
    pfile = NULL;
    CloseHandle(pfile);
    //close handle
    CloseHandle(mutex);
    CloseHandle(empty);
    CloseHandle(full);
}
