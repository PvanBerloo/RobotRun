#pragma once
#include "windows.h"

typedef struct COMPORT {
	HANDLE handle;
} COMPORT;

COMPORT* portOpen(int portNumber);
void portClose(COMPORT* port);
void portWriteByte(COMPORT* port, char byte);
void portWriteBytes(COMPORT* port, char* buffer, int size);
void portWriteString(COMPORT* port, char* str);
char portReadByte(COMPORT* port);
void portReadBytes(COMPORT* port, char* buffer, int size);
void portReadString(COMPORT* port, char* buffer, int size);
int portBytesAvailable(COMPORT* port);