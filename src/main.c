#include "comport.h"

#include <math.h>
#include <stdio.h>
#include <windows.h>
#include <xinput.h>

int main()
{
	// You need to link to Xinput.lib to use these functions:
	// Project > Linker > Input > Additional Dependencies > edit
	XINPUT_CAPABILITIES capabilities;
	XInputGetCapabilities(0, XINPUT_FLAG_GAMEPAD, &capabilities);

	COMPORT* port = portOpen(9);

	while (1)
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
	}
}