#ifndef CMD_UART_H
#define CMD_UART_H

#include "hal_uart.h"
#include "hal_types.h"

#define CMD_UART_THRESHOLD	 5
#define CMD_UART_RX_BUFF_MAX     150
#define CMD_UART_TX_BUFF_MAX     170
#define CMD_UART_IDLE_TIMEOUT    5
#define CMD_BUFF_MAX             150

uint8 uart_init( void );

#endif