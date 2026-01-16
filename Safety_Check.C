#include <windows.h>
#include <stdio.h>

// This is the safety check i was talking about. 
// basically, windows has this thing called PPL which is like a shield 
// for important apps like antivirus. if the level is > 0, our 
// "thread breaker" code is gonna fail even if we have admin.

void CheckIfProtected(HANDLE hProcess) {
    // this struct is where the OS stores the "protection" info
    PROCESS_PROTECTION_LEVEL_INFORMATION ppl;
    
    // we gotta ask the kernel for the info using this weird function name
    // GetProcessInformation is like the "ID checker" of the OS
    if (GetProcessInformation(hProcess, ProcessProtectionLevelInfo, &ppl, sizeof(ppl))) {
        
        printf("DEBUG: Found protection level -> %d\n", ppl.ProtectionLevel);
        
        if (ppl.ProtectionLevel > 0) {
            // if we see a number here, it means its protected
            // probly shouldn't try to inject here or the EDR will kill us lol
            printf("RESULT: Target is PROTECTED (PPL). Skip this one.\n");
        } else {
            printf("RESULT: Target is UNPROTECTED. Experimenting is okay here.\n");
        }
        
    } else {
        // if this fails, we might not have enough permissions to even LOOK 
        // at the process info. happens alot with system stuff.
        printf("Error: Couldnt get info. Code: %lu\n", GetLastError());
    }
}
