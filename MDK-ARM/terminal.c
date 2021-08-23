#include "main.h"
#include "terminal.h"
#include "stm32g0xx_hal.h"
#include "uart.h"
#include "adc.h"
#include "dma.h"
#include "string.h"
#include "timer.h"
#include "gpio.h"
#include "rcc.h"
#include "pwm.h"
#include "dac.h"
#include "i2c.h"
#include <stdlib.h>
#include <stdio.h>

void terminal_init(void)
{
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_DMA_Init();
    MX_ADC1_Init();
    MX_USART2_UART_Init();
    MX_TIM16_Init();
    MX_TIM2_Init();
    MX_DAC1_Init();
    MX_I2C1_Init();
    char msg[] = "Greetings, enter \"help\" to see the list of commands\r\n";
    UART_Transmit((uint8_t*)msg, strlen(msg), TRANSMIT_TIMEOUT);
}

enum ecommand
{
    ecommand_led=0,
    ecommand_help=1,
    ecommand_echo=2,
    ecommand_adc=3,
    ecommand_adcdma=4,
    ecommand_time=5,
    ecommand_pwm=6,
    ecommand_dac=7,
    ecommand_mem=8
};

enum enTokenCategory
{
    tc = 0,
    ta1 = 1,
    ta2 = 2,
    ta3 = 3
};

char newline[] = "\r\n";
char operation[COMMANDS_LENGTH];
char a1[MAX_ARGUMENT_LENGTH];
char a2[MAX_ARGUMENT_LENGTH];
int8_t comnum=tc;
char msg[100];
char commArr[NUMBER_OF_COMMANDS][COMMANDS_LENGTH] = 
    {
        {"led"}, {"help"}, {"echo"}, {"adc"}, {"adcdma"}, {"time"}, {"pwm"}, {"dac"}, {"mem"}
    };



void parse(void)
{
    char line[MAX_ARGUMENT_LENGTH+1];
    char *token;
    int category=0;
    UART_Receive((uint8_t*)line, MAX_ARGUMENT_LENGTH, RECEIVE_TIMEOUT);
    token=strtok(line," \t\n\r");
    
    while(token!=NULL)
    {
        switch(category)
        {
            case tc:
            {
            strcpy(operation, token);
            break;
            }
            case ta1:
            {
            strcpy(a1, token);
            break;
            }
            case ta2:
            {
            strcpy(a2, token);
            break;
            }
            case ta3:
            {
            break;
            }
        }
        category++;
        token=strtok(NULL, " \t\n\r");
    }
    for(comnum=0;comnum<NUMBER_OF_COMMANDS;comnum++)
    {
        if(line[0]==0)
        {
            comnum=-1;
            break;
        }
        if(strcmp(commArr[comnum],operation)==0)
        {
            memset(line,0,sizeof(line));
            break;
        }
    }
}

void toggleLED(void)
{
    UART_Transmit((uint8_t*)newline, strlen(newline), TRANSMIT_TIMEOUT);
    for(int i=0; i<10; i++)
      {
        HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
        HAL_Delay(10);
        i++;
      }
}

void showHelp(void)
{
    for (int i = 0; i<NUMBER_OF_COMMANDS; i++)
    {
        UART_Transmit((uint8_t*)commArr[i], strlen(commArr[i]), TRANSMIT_TIMEOUT);
        UART_Transmit((uint8_t*)newline, strlen(newline), TRANSMIT_TIMEOUT);
    }
}

void sendEcho(void)
{
    UART_Transmit((uint8_t*)a1, strlen(a1), TRANSMIT_TIMEOUT);
    UART_Transmit((uint8_t*)newline, strlen(newline), TRANSMIT_TIMEOUT);
}

void showADC_Values(void)
{
    ADC_GetValue(10);
    sprintf(msg, "%d\r\n", ADC_GetValue(10));
    UART_Transmit((uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);
    UART_Transmit((uint8_t*)newline, strlen(newline), TRANSMIT_TIMEOUT);
    memset(msg,NULL,sizeof(msg));
}

void showADC_DMA_Values(void)
{
    uint32_t num;
    //sscanf(a1,"%u",&num);
    num = atoi(a1);
    uint32_t adcdma[10];
    ADC_DMA_Start_Acquisition(adcdma, num);
    HAL_Delay(10);
    for(int i=0; i<num; i++)
    {
        ADC_Start();
        sprintf(msg, "Value#%d: %d\n\r", i+1, adcdma[i]);
        UART_Transmit((uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);
        UART_Transmit((uint8_t*)newline, strlen(newline), TRANSMIT_TIMEOUT);
        HAL_Delay(10);
    }
    memset(msg,NULL,sizeof(msg));
    ADC_DMA_Stop_Acquisition();
}

void showProgramRunningTime(void)
{
    sprintf(msg,"Program is running %.0f seconds",TIMER_time());
    UART_Transmit((uint8_t*)msg, strlen(msg),100);    
    UART_Transmit((uint8_t*)newline, strlen(newline), TRANSMIT_TIMEOUT);    
}

void setPWMDutyCycle(void)
{
    uint32_t dutyCycle;
    sscanf(a1,"%u",&dutyCycle);
    PWM_Start(dutyCycle);
    sprintf(msg,"%u%%", dutyCycle);
    UART_Transmit((uint8_t*)msg, strlen(msg), TRANSMIT_TIMEOUT);
    UART_Transmit((uint8_t*)newline, strlen(newline), TRANSMIT_TIMEOUT);
    memset(msg,NULL,sizeof(msg));
}

void t_dac(void)
{
    float volt_value;
    sscanf(a1,"%f",&volt_value);
    DAC_Start();
    DAC_SetValue(volt_value);
    sprintf(msg,"DAC value:%d",DAC_GetValue());
    UART_Transmit((uint8_t*)msg,strlen(msg),TRANSMIT_TIMEOUT);
    UART_Transmit((uint8_t*)newline, strlen(newline), TRANSMIT_TIMEOUT);
    memset(msg,NULL,sizeof(msg));
    DAC_Stop();
}
void memoryWriteRead(void)
{
    uint16_t devAddress = 0x50;
    uint16_t memAddress = 0x00;
    if(strcmp(a1, "write")==0)
    {
        UART_Transmit((uint8_t*)"Writing...\n\r", 12,TRANSMIT_TIMEOUT);
        uint8_t writeData[strlen(a2)];
        sprintf((char*)writeData,a2);
        memWrite(devAddress,memAddress,(uint8_t*)writeData,sizeof(writeData));
        sprintf(msg,"Writing is complete. You wrote: %s\n\r", writeData);
        UART_Transmit((uint8_t*)msg,strlen(msg),TRANSMIT_TIMEOUT);
        UART_Transmit((uint8_t*)newline, strlen(newline), TRANSMIT_TIMEOUT);
    }
    else if(strcmp(a1, "read")==0)
    {
        UART_Transmit((uint8_t*)"Reading...\n\r",12,TRANSMIT_TIMEOUT);
        int symb = atoi(a2);
        uint8_t readData[symb];
        uint8_t transmitData[symb];
        memRead(devAddress,memAddress,readData,symb);
        memcpy(transmitData, readData,sizeof(readData));
        UART_Transmit(transmitData,sizeof(transmitData),TRANSMIT_TIMEOUT);
        UART_Transmit((uint8_t*)newline, strlen(newline), TRANSMIT_TIMEOUT);
    }
    else
    {
        UART_Transmit((uint8_t*)"Wrong command",13,TRANSMIT_TIMEOUT);
    }
}

void execCommand(void)
{
    switch(comnum)
    {
        case ecommand_led:
        {
            toggleLED();
            break;
        }
        case ecommand_help:
        {
            showHelp();
            break;
        }
        case ecommand_echo:
        {
            sendEcho();
            break;
        }
        case ecommand_adc:
        {
            showADC_Values();
            break;
                    
        }
        case ecommand_adcdma:
        {
            showADC_DMA_Values();
            break;
        }
        case ecommand_time:
        {
            showProgramRunningTime();
            break;
        }
        case ecommand_pwm:
        {
            setPWMDutyCycle();
            break;
        }
        case ecommand_dac:
        {
            t_dac();
            break;
        }
        case ecommand_mem:
        {
            memoryWriteRead();
            break;
        }
        default:
        {
            break;
        }
    }
    comnum = -1;
}
