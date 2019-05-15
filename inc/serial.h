#pragma once

#ifdef _WIN32
void serialOpen(int portNumber); // windows application needs port number
#else
void serialOpen(unsigned long baudrate);
#endif
void serialClose();
void serialWriteByte(char byte);
void serialWriteBytes(char* buffer, unsigned char size);
void serialWriteString(char* str);
char serialReadByte();
void serialReadBytes(char* buffer, unsigned char size);
void serialReadString(char* buffer, unsigned char size);
unsigned int serialBytesAvailable();