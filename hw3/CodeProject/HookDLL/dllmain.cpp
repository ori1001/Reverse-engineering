#include "pch.h"
#include <Windows.h>
#include <stdio.h>
#include <fstream>
#include <iomanip>
// Add additional includes if needed
// using namespace std;

void our_decrypt(char* inp)
{
    if (inp == 0 || strlen(inp) == 0) return;
        
    char tocmp[5][200] = { "What would you like to do?",
        "[1] ECHO - ping the server with a custom message, receive the same.",
        "[2] DMSG - Download message from the server.",
        "[3] TIME - Get local time from server point of view.",
        "[4] HNKH - Request a spinning top for Hanukkah!" };
    bool dectyptqm = true; // decrypt?
    for (int i = 0; i < 5; i++)
    {
        if (strncmp(tocmp[i], inp, strlen(tocmp[i])) == 0)
        {
            dectyptqm = false;
        }
    }
    if (!dectyptqm)
    {
        return;
    }

    int i = 0; //read_idx
    int k = 0; //write idx
    while (inp[i] != '\0')
    {
        if (inp[i] > '~' || inp[i] < ' ')
        {
            inp[k] = inp[i];
            k++; i++;
        }
        else
        {
            int int_let = 0;
            for (int j = 0; j < 2; j++)
            {
                if (inp[i + 1] == '+')
                {
                    int_let += inp[i] - '0' + inp[i + 2] - '0';
                    i += 3;
                }
                else if (inp[i + 1] == '-')
                {
                    i += 3;
                }
                else if (inp[i] >= '2' && inp[i] <= '9')
                {
                    int_let += inp[i] - '0';
                    i++;
                }
                else
                {
                    switch (inp[i])
                    {
                    case 'A':
                        int_let += 1;
                        break;
                    case 'J':
                        int_let += 10;
                        break;
                    case 'Q':
                        int_let += 11;
                        break;
                    case 'K':
                        int_let += 12;
                        break;
                    default:
                        int_let += inp[i];
                    }
                    i++;
                }
                if (j == 0) {
                    int_let = int_let << 4;
                }
            }
            inp[k++] = int_let;
        }
    }
    inp[k++] = '\0';
}




// for logging. format: log_file << ... << std::endl;
 using std::ofstream;

// Typedef for the hooked function signature, such as:
// typedef INT(WINAPI* FUNC_PTR)(SOCKET, char*, int, int); (WINAPI is for _stdcall)
// or in the simple case:
typedef LPVOID FUNC_PTR;

// Ptr to the original function
FUNC_PTR original_func_address;
// Ptr to return to after hook
//LPVOID to_return_address;

// Global variables
CHAR OrigOpcode[6] = "\x90\x90\x90\x90\x90"; // Restores overriden bytes from hooked function
CHAR JmpOpcode[6] = "\xE9\x90\x90\x90\x90"; // Inserted into hooked function, in order to jmp to hook
DWORD lpProtect = 0;

// Helper function to remove the hook (for the current call):
void _stdcall remove_hook() {
	VirtualProtect((char*)original_func_address, 0x5, PAGE_EXECUTE_READWRITE, &lpProtect);
	memcpy((char*)original_func_address, &OrigOpcode, 0x5);
	VirtualProtect((char*)original_func_address, 0x5, PAGE_EXECUTE_READ, &lpProtect);
}

// Helper function to restore the hook (for the next calls)
void _stdcall restore_hook() {
	VirtualProtect((char*)original_func_address, 0x5, PAGE_EXECUTE_READWRITE, &lpProtect);
	memcpy((char*)original_func_address, &JmpOpcode, 0x5);
	VirtualProtect((char*)original_func_address, 0x5, PAGE_EXECUTE_READ, &lpProtect);
}

// Hook function. Might use helper functions in C, i.e. void _stdcall helper(int num) {}
__declspec(naked) void funcHook() {

	// Restore overriden bytes
	remove_hook();

	// Assembly part. Should call restore_hook somewhere inside, can call original_func_addr
	__asm {
        mov eax, [esp+4]
        push eax    //move buffer as parameter
        call our_decrypt
        call puts
        mov [esp], eax //save puts retval (and override parameter)
        call restore_hook
        pop eax     //restore puts retval
        ret
	}
}

void setHook() {
	//HMODULE h = GetModuleHandle(L"<dll_with_func_to_hook_name>.dll");
	HMODULE h = GetModuleHandle(L"client.exe");
	LPVOID JumpTo;

	if (h == NULL) {
		// can't find module
		return;
	}

	//original_func_address = (FUNC_PTR)GetProcAddress(h, "<func_to_hook_name>");
	original_func_address = (char*)((long)h + (long)0x466C); //TODO: test this

    //read original opcode
    memcpy(OrigOpcode, original_func_address, 0x6);
    
	//if (original_func_address == NULL) {
	//	// can't find function
	//	return;
	//}

	JumpTo = (FUNC_PTR)((char*)&funcHook - ((char*)original_func_address + 5)); // NO: The "+5" part is for the offset to be calculated relatively to the address AFTER jmp
	memcpy(JmpOpcode + 1, &JumpTo, 0x4); // prepare the jmp opcode


	// save old bytes - save this arr globally if needed to be restored in hook_func
	//memcpy(&OrigOpcode, (char*)original_func_address, 0x5); // override the first five bytes with jmp

	// override these bytes
	restore_hook();

	// save address to return to after hook. Can be used directly if hook is written in C.
	 //to_return_address = (LPVOID)((char*)original_func_address + 5); // can be changed to original_func_address+<some offset>
}


BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		setHook();
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}