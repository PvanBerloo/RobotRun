#pragma once

#define MAX_STRING_LENGTH 100

#define MESSAGE_STARTUP -1
#define MESSAGE_INVALID 0
#define MESSAGE_DEBUG 1
#define MESSAGE_ERROR 2
#define MESSAGE_ASKFORINSTRUCTION 3
#define MESSAGE_INSTRUCTION_MANUAL 4
#define MESSAGE_INSTRUCTION_ORDER_PICK 5
#define MESSAGE_LOW_BATTERY 6
#define MESSAGE_QUIT_MANUAL 7
#define MESSAGE_MOTOR_STATUS 8

typedef struct Order {
	char x;
	char y;
} Order;

typedef struct MotorStatus {
	char left;
	char right;
} MotorStatus;

typedef struct Message {
	char type;

	union {
		Order order;
		MotorStatus motorstatus;
		char string[MAX_STRING_LENGTH];
	};

} Message;

void sendDebugMessage(char* str);
void sendErrorMessage(char* str);
void askForInstructionMessage();
void sendOrderPickMessage(char x, char y);
void enableManualModeMessage();
void quitManualModeMessage();
void sendLowBatteryMessage();
void sendMotorStatus(char left, char right);

Message readMessage();