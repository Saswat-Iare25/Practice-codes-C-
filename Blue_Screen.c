#include <windows.h>  // pre-processor directive for the main header file for windows API
#include <winternl.h> // this is windows internal definitions 
 typedef NTSTATUS (NTAPI *pNtRaiseHardError)(NTSTATUS ErrorStatus, ULONG NumberOfParameters, ULONG UnicodeStringParameterMask, PULONG_PTR Parameters, ULONG ValidResponseOptions, PULONG Response); 
/* the above line, typedef ...  is where we're creating a nick for a type, 
NTAPI is calling using window's internal calling style *pNtRaiseHarderror is a pointer to a funtion, 
basically pointing to a windows function
NT statuc, ulong are just numbers and pointers to numbers
ULONG is unsigned int
PULONG is pointer to unsigned int
_PTR holds a pointer
NTSTATUS is status code
that whole line means:
pNtRaiseHardError is a pointer to a Windows internal function 
that takes some numbers and pointers and returns a status code
*/
int main()
  { 
    HMODULE ntdll = GetModuleHandleA("ntdll.dll"); pNtRaiseHardError NtRaiseHardError = (pNtRaiseHardError)GetProcAddress(ntdll, "NtRaiseHardError"); 
   /*
   HMODULE is handle to a loaded Windows module (a .dll)
   ntdll.dll is a core windows library that contains NT functions
   GetProcAddress(ntdll, "NtRaiseHardError");  this part means finding the memory address of the function named NtRaiseHardError in ntdll.dll(raw address)
   The whole line means: giving a reference to windows sys library that is ntdll.dll
   */
    if (NtRaiseHardError) //if block for successful finding of the function, if not found then the pointer is NULL
    { 
        ULONG response; // just a variable that is an unsigned integer
        NtRaiseHardError(STATUS_ASSERTION_FAILURE, 0, 0, NULL, 6, &response); // funtion call via pointer
    } 
    return 0; 

}
