#include "pch-il2cpp.h"
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <iostream>
#include "il2cpp-appdata.h"
#include "helpers.h"
#include "MinHook.h"

using namespace app;

extern const LPCWSTR LOG_FILE = L"il2cpp-log.txt";

int32_t (*original_ObscuredInt_InternalDecrypt)(ObscuredInt__Boxed*, MethodInfo*);

int32_t __stdcall hooked_ObscuredInt_InternalDecrypt(ObscuredInt__Boxed* thisObscuredInt, MethodInfo* method)
{
	int32_t Result = original_ObscuredInt_InternalDecrypt(thisObscuredInt, method);
	
	Result = 9999999;

	return Result;
}

void InitializeHook()
{
	if (MH_Initialize() != MH_OK)
	{
		printf("Failed to initialize MinHook.\n");
		return;
	}


	if (MH_CreateHook(
			reinterpret_cast<void*>(ObscuredInt_InternalDecrypt),
			&hooked_ObscuredInt_InternalDecrypt,
			reinterpret_cast<void**>(&original_ObscuredInt_InternalDecrypt)) == MH_OK)
		{
		MH_EnableHook(reinterpret_cast<void*>(ObscuredInt_InternalDecrypt));
		}
	else
	{
		printf("Failed to create decryptInt Hook.\n");
	}
}

void Run()
{
	il2cpp_thread_attach(il2cpp_domain_get());
	il2cppi_new_console();
	InitializeHook();
}

