#include "comport.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

COMPORT* portOpen(int portNumber)
{
	COMPORT* port = (COMPORT*)malloc(sizeof(COMPORT));

	char portName[32];
	sprintf(portName, "\\\\.\\COM%i", portNumber);

	port->handle = CreateFileA(	portName,						// port name
								GENERIC_READ | GENERIC_WRITE,	// Read/Write
								0,								// This port is not allowed to be opened while we are using it.
								NULL,							// Only this process is allowed to use this handle.
								OPEN_EXISTING,					// Only open the port if it exists.
								0,								// Flags
								NULL);							// Null for Comm Devices

	if (port->handle == INVALID_HANDLE_VALUE)
	{ 
		// Failed to open port
		free(port);
		return NULL;
	}
	else
	{
		DCB settings = { 0 };
		settings.DCBlength = sizeof(DCB);
		settings.BaudRate = CBR_115200;
		settings.ByteSize = 8;
		settings.StopBits = ONESTOPBIT;

		SetCommState(port->handle, &settings);

		return port;
	}
}

void portClose(COMPORT* port)
{
	CloseHandle(port->handle);
	free(port);
}

void portWriteByte(COMPORT* port, char byte)
{
	DWORD numberofbytes;

	WriteFile(port->handle, &byte, 1, &numberofbytes, NULL);
}

void portWriteBytes(COMPORT* port, char* buffer, int size)
{
	DWORD numberofbytes;

	WriteFile(port->handle,	buffer, size,	&numberofbytes, NULL);
}

void portWriteString(COMPORT* port, char* str)
{
	DWORD numberofbytes;

	WriteFile(port->handle, str, strlen(str) + 1, &numberofbytes, NULL);
}

char portReadByte(COMPORT* port)
{
	char c;
	DWORD numberofbytes;
	ReadFile(port->handle, &c, 1, &numberofbytes, NULL);
	return c;
}

void portReadBytes(COMPORT* port, char* buffer, int size)
{
	DWORD numberofbytes;

	ReadFile(port->handle, buffer, size, &numberofbytes, NULL);
}

void portReadString(COMPORT* port, char* buffer, int size)
{
	char c;
	DWORD numberofbytes;
	int index = 0;

	do
	{
		ReadFile(port->handle, &c, 1, &numberofbytes, NULL);
		buffer[index++] = c;
	} while (c != '\0' || index == size);
}

int portBytesAvailable(COMPORT* port)
{
	DWORD error = 0;
	COMSTAT stats;
	ClearCommError(port->handle, &error, &stats);

	return stats.cbInQue;
}