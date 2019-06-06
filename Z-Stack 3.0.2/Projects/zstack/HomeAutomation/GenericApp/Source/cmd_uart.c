#include "cmd_uart.h"

uint8 RxBuffer[CMD_BUFF_MAX] = {0};

uint8 uart_init( void )
{
  halUARTCfg_t cmd_uart_cfg;
  
  cmd_uart_cfg.configured           = TRUE;
  cmd_uart_cfg.baudRate             = HAL_UART_BR_9600;
  cmd_uart_cfg.flowControl          = FALSE;
  cmd_uart_cfg.flowControlThreshold = CMD_UART_THRESHOLD;
  cmd_uart_cfg.rx.maxBufSize        = CMD_UART_RX_BUFF_MAX;
  cmd_uart_cfg.tx.maxBufSize        = CMD_UART_TX_BUFF_MAX;
  cmd_uart_cfg.idleTimeout          = CMD_UART_IDLE_TIMEOUT;
  cmd_uart_cfg.intEnable            = TRUE;
  cmd_uart_cfg.callBackFunc         = CMD_UartProcess;

  RxBuffer[0] = '\r';

  return HalUARTOpen(HAL_UART_PORT_0, &cmd_uart_cfg);
}