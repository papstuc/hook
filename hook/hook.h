#pragma once

// address: target function start
// destination: detour function
// length: length for the jmp + address (mostly 5 or 6)
// offset: how far you wanna go from the beginning of the function start
// junk: instructions to insert before the jmp instruction (array must be the same size as offset)
// original: this will return the gateway.
void hook(void* address, void* destination, int length, int offset, unsigned char* junk, void** original);

void release(void* address, int length, int offset, void* original);