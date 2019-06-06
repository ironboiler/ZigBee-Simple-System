#ifndef CMD_UART_H
#define CMD_UART_H

#include "hal_uart.h"
#include "hal_types.h"

#define CMD_UART_THRESHOLD	 5
#define CMD_UART_RX_BUFF_MAX     150
#define CMD_UART_TX_BUFF_MAX     170
#define CMD_UART_IDLE_TIMEOUT    5
#define CMD_BUFF_MAX             150

#define CHECK_C         1
#define CHECK_M         2
#define CHECK_D         3
#define CHECK_MINUS     4
#define CHECK_WRAP      5
#define HANDLE_CMD      6

typedef struct
{
  uint8  cmd[10];
  uint16 para_1;
  uint8  para_2;
} cmd_form;

uint8 uart_init( void );

#endif