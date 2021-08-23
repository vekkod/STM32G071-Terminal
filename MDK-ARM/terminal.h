#ifndef TERMINAL_H
#define TERMINAL_H

#define NUMBER_OF_COMMANDS 9
#define COMMANDS_LENGTH 21
#define MAX_ARGUMENT_LENGTH 20
#define TRANSMIT_TIMEOUT 10 /*10ms*/
#define RECEIVE_TIMEOUT 100 /*100ms*/
#define MAX_STRING_LENGTH 64

void terminal_init(void);

void parse(void);

void LED(void);

void Help(void);

void T_ADC(void);

void PWM(void);

void execCommand(void);

#endif
