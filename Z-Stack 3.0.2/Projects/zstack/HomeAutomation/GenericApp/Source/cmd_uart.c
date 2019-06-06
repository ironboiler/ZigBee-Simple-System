#include "cmd_uart.h"
#include "printf.h"
#include "OSAL.h"
#include "cmd_control.h"


uint8 RxBuffer[CMD_BUFF_MAX] = {0};
uint8 uart_state = CHECK_C;

static void CMD_UartProcess(uint8 port, uint8 event);
static void CMD_UartHandle(uint8 *msg);
static void CMD_Handle(cmd_form *cmd_msg);
static uint8 ch_to_num(uint8 *msg);

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

static void CMD_UartProcess(uint8 port, uint8 event)
{
  uint8 ch;
  uint8 len=0;
  (void)event;

  while(Hal_UART_RxBufLen(port))
  {
    HalUARTRead (port, &ch, 1);
    
    switch(uart_state)
    {
    case CHECK_C:
      if(ch=='C')       uart_state=CHECK_M;
      break;
      
    case CHECK_M:
      if(ch=='M')       uart_state=CHECK_D;
      else if(ch=='C')  uart_state=CHECK_M;
      else              uart_state=CHECK_C;
      break;
      
    case CHECK_D:
      if(ch=='D')       uart_state=CHECK_MINUS;
      else if(ch=='C')  uart_state=CHECK_M;
      else              uart_state=CHECK_C;
      break;
      
    case CHECK_MINUS:
      if(ch=='-')       uart_state=CHECK_WRAP;
      else if(ch=='C')  uart_state=CHECK_M;
      else              uart_state=CHECK_C;
      break;
      
    case CHECK_WRAP:
      if(ch=='\r')
      {
        RxBuffer[len]='\r';
        uart_state=HANDLE_CMD;
      }
      else              RxBuffer[len++]=ch;
      break;
      
    case HANDLE_CMD:
      CMD_UartHandle(RxBuffer);
      uart_state=CHECK_C;
      break;
      
    default:
      break;
      
    }
  }
  if(RxBuffer[len]!='\r')
    printf("ERROW:COMMAND HAS NO LINE BREAK!\r\n");
  
  osal_memset(RxBuffer, 0, CMD_BUFF_MAX);
  RxBuffer[0] = '\r';
}

static void CMD_UartHandle(uint8 *msg)
{
  cmd_form cmd_msg={{0},0,0};
  uint8 i=0;
  int bit=0;
  while((msg[i]!=':')&&(msg[i]!='\r'))
  {
    cmd_msg.cmd[i] = msg[i];
    i++;
  }
  if(msg[i++]==':')
  {
    for(bit=3;bit>=0;bit--)
    {
      cmd_msg.para_1 |= ch_to_num(&msg[i++])<<bit*4;
    }
    
    if(msg[i]!='\r')
    {
      cmd_msg.para_2 = ch_to_num(&msg[++i]);
    }
  }
  CMD_Handle(&cmd_msg);
}  

static void CMD_Handle(cmd_form *cmd_msg)
{
  if(cmd_msg->cmd[0]=='F'&&cmd_msg->cmd[1]=='T'&&cmd_msg->cmd[2]=='N'&&cmd_msg->cmd[3]=='W')
    Factory_New();
  else if(cmd_msg->cmd[0]=='R'&&cmd_msg->cmd[1]=='E'&&cmd_msg->cmd[2]=='L'&&cmd_msg->cmd[3]=='A'&&cmd_msg->cmd[4]=='Y')
    Relay_Control(cmd_msg);
  else if(cmd_msg->cmd[0]=='T'&&cmd_msg->cmd[1]=='E'&&cmd_msg->cmd[2]=='M'&&cmd_msg->cmd[3]=='P')
    Read_Temp(cmd_msg);
  else  printf("ERROW:WRONG COMMAND!\r\n");
}

static uint8 ch_to_num(uint8 *msg)
{
  char ch=*msg;
  
  if(ch>='A'&&ch<='F')
    return ch-'A'+10; 
  else if(ch>='0'&&ch<='9')
    return ch-'0';
  else  printf("ERROW:ILLEGAL INPUT!\r\n");
    return 0;
}