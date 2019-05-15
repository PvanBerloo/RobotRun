
#include "serial.h"
#include "communication.h"

#include <math.h>
#include <stdio.h>
#include <windows.h>
#include <xinput.h>

int main()
{
	serialOpen(9);

	// clear serial buffer by reading all bytes left.
	while (serialBytesAvailable() > 0)
	{
		serialReadByte();
	}

	sendOrderPickMessage(3, 7);
	
	while (1)
	{
		Message message = readMessage();

		switch (message.type)
		{
		case MESSAGE_STARTUP:
			printf("De robot is opgestart.\n");
			break;

		case MESSAGE_ASKFORINSTRUCTION:
			printf("De robot wil een commando.\n");
			break;

		default:
			printf("Onbekend bericht type\n");
			break;
		}
	}

	return 0;

	/*while (1)
	{
		XINPUT_STATE state;
		XInputGetState(0, &state);

		float x = -state.Gamepad.sThumbLX / 327.670;
		float y = state.Gamepad.sThumbLY / 327.670;

		// joystick deadzone
		if (fabs(x) < 20)
			x = 0;

		if (fabs(y) < 20)
			y = 0;
		
		// tank controls
		// http://home.kendra.com/mauser/Joystick.html
		float V = (100 - fabs(x)) * (y / 100) + y;
		float W = (100 - fabs(y)) * (x / 100) + x;

		float R = (V + W) / 2;
		float L = (V - W) / 2;

		signed char r = (signed char)(R / 101 * 127);
		signed char l = (signed char)(L / 101 * 127);

		printf("l: %i r: %i              \r", l, r);

		portWriteByte(port, l);
		portWriteByte(port, r);

		Sleep(16);
	}*/
}