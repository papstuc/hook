#include <cstdio>
#include <Windows.h>

#include "hook.h"

void hook(void* address, void* destination, int length, int offset, unsigned char* junk, void** original)
{
	void* gateway = VirtualAlloc(0, length + offset + 5, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	memcpy_s(gateway, length + offset, address, length + offset);

	unsigned int gateway_delta = (unsigned int)address - (unsigned int)gateway - 5;

	*((unsigned __int8*)gateway + length + offset) = 0xE9;
	*(unsigned int*)((unsigned int)gateway + length + offset + 1) = gateway_delta;

	unsigned long old_protect = 0;
	VirtualProtect(address, length + offset, PAGE_EXECUTE_READWRITE, &old_protect);

	unsigned int delta = (unsigned int)destination - (unsigned int)address - offset - 5;

	*((unsigned __int8*)address + offset) = 0xE9;
	*(unsigned int*)((unsigned __int8*)address + offset + 1) = delta;

	memcpy_s(address, offset, junk, offset);

	VirtualProtect(address, length + offset, old_protect, &old_protect);

	*original = gateway;
}

void release(void* address, int length, int offset, void* original)
{
	unsigned long old_protect = 0;
	VirtualProtect(address, length + offset, PAGE_EXECUTE_READWRITE, &old_protect);

	memcpy_s(address, length + offset, original, length + offset);

	VirtualProtect(address, length + offset, old_protect, &old_protect);

	VirtualFree(original, length + offset, MEM_RELEASE | MEM_COALESCE_PLACEHOLDERS);
}