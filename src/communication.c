#include "communication.h"

#include "serial.h"

void sendDebugMessage(char* str) 
{
	serialWriteByte(MESSAGE_DEBUG);
	serialWriteString(str);
}

void sendErrorMessage(char* str)
{
	serialWriteByte(MESSAGE_ERROR);
	serialWriteString(str);
}

void askForInstructionMessage()
{
	serialWriteByte(MESSAGE_ASKFORINSTRUCTION);
}

void sendOrderPickMessage(char x, char y)
{
	serialWriteByte(MESSAGE_INSTRUCTION_ORDER_PICK);
	serialWriteByte(x);
	serialWriteByte(y);
}

void enableManualModeMessage()
{
	serialWriteByte(MESSAGE_INSTRUCTION_MANUAL);
}

void quitManualModeMessage()
{
	serialWriteByte(MESSAGE_QUIT_MANUAL);
}

void sendLowBatteryMessage()
{
	serialWriteByte(MESSAGE_LOW_BATTERY);
}

void sendMotorStatus(char left, char right)
{
	serialWriteByte(MESSAGE_MOTOR_STATUS);
	serialWriteByte(left);
	serialWriteByte(right);
}

Message readMessage() 
{
	Message message = {0};

	message.type = serialReadByte();

	switch (message.type)
	{
	case MESSAGE_DEBUG:
	case MESSAGE_ERROR:
		serialReadString(message.string, MAX_STRING_LENGTH);
		break;

	case MESSAGE_INSTRUCTION_ORDER_PICK:
		message.order.x = serialReadByte();
		message.order.y = serialReadByte();
		break;

	case MESSAGE_MOTOR_STATUS:
		message.motorstatus.left = serialReadByte();
		message.motorstatus.right = serialReadByte();
		break;

		// Messages with no content do not have to read more data.
	case MESSAGE_ASKFORINSTRUCTION:
	case MESSAGE_INSTRUCTION_MANUAL:
	case MESSAGE_LOW_BATTERY:
	case MESSAGE_QUIT_MANUAL:
	case MESSAGE_STARTUP:
		break;

		// Set type to invaled if we dont recognize the type.
	default:
		message.type = MESSAGE_INVALID;
		break;
	}

	return message;
}