#include "serial.h"

#ifdef _WIN32

#include "comport.h"

COMPORT* port;

void serialOpen(int portNumber)
{
	port = portOpen(portNumber);
}

void serialClose()
{
	portClose(port);
}

void serialWriteByte(char byte)
{
	portWriteByte(port, byte);
}

void serialWriteBytes(char* buffer, unsigned char size)
{
	portWriteBytes(port, buffer, size);
}

void serialWriteString(char* str)
{
	portWriteString(port, str);
}

char serialReadByte()
{
	return portReadByte(port);
}

void serialReadBytes(char* buffer, unsigned char size)
{
	return portReadBytes(port, buffer, size);
}

void serialReadString(char* buffer, unsigned char size)
{
	portReadString(port, buffer, size);
}

int serialBytesAvailable()
{
	return portBytesAvailable(port);
}

#else

#include <pololu/3pi.h>
#include <string.h>

void serialOpen(unsigned long baudrate)
{
	serial_set_baud_rate(baudrate);
	serial_set_mode(SERIAL_CHECK);
}

void serialClose()
{

}

void serialWriteByte(char byte)
{
	char buffer[1];
	buffer[0] = byte;
	serialWriteBytes(buffer, sizeof(char));
}

void serialWriteBytes(char* buffer, unsigned char size)
{
	serial_send_blocking(buffer, size);
}

void serialWriteString(char* str)
{
	serial_send_blocking(str, strlen(str) + 1);
}

char serialReadByte()
{
	char byte;
	serial_receive_blocking(&byte, sizeof(byte), 0xFFFF);
	return byte;
}

void serialReadBytes(char* buffer, unsigned char size)
{
	serial_receive_blocking(buffer, size, 0xFFFF);
}

void serialReadString(char* buffer, unsigned char size)
{
	int i = 0;
	char c;

	do
	{
		c = serialReadByte();
		buffer[i] = c;
		i++;
	} while (c != '\0');
}

unsigned int serialBytesAvailable()
{
	return serial_get_received_bytes();
}
#endif