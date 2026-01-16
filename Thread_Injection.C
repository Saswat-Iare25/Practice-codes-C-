#include <windows.h>
#include <stdio.h>
#include <tlhelp32.h>

// okay so this is the "thread breaker" i was talking about.
// basically we are gonna find notepad and force it to kill itself 
// by injecting a thread. its kinda like inception but for code lol.

int main() {
    // 1. first we gotta find where notepad is hiding. 
    // we take a "snapshot" of everythin running right now.
    DWORD pid = 0;
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    PROCESSENTRY32 entry;
    entry.dwSize = sizeof(PROCESSENTRY32);

    if (Process32First(snapshot, &entry)) {
        do {
            // checking the name... i used notepad cuz its safe to crash.
            if (strcmp(entry.szExeFile, "notepad.exe") == 0) {
                pid = entry.th32ProcessID;
                break;
            }
        } while (Process32Next(snapshot, &entry));
    }

    if (pid == 0) {
        printf("cant find notepad. make sure its open first!\n");
        return 1;
    }

    // 2. THE BREAK IN. 
    // we ask windows for "PROCESS_ALL_ACCESS". 
    // this is the part where permissions usually block us if we arent admin.
    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);

    if (hProcess != NULL) {
        // 3. THE TRICK.
        // we find where 'ExitProcess' lives in the system. 
        // since its a system dll, its usually at the same spot for everyone.
        LPVOID exitFunc = (LPVOID)GetProcAddress(GetModuleHandleA("kernel32.dll"), "ExitProcess");

        // 4. THE INJECTION.
        // here we tell the OS: "hey, start a new thread inside notepad... 
        // and tell it to run that Exit function."
        // notepad thinks its closing itself but its actually us doing it.
        CreateRemoteThread(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)exitFunc, NULL, 0, NULL);

        printf("injected the thread into pid %d... notepad should be gone now.\n", pid);
        CloseHandle(hProcess);
    } else {
        printf("access denied. windows permissions are actually working lol.\n");
    }

    return 0;
}
