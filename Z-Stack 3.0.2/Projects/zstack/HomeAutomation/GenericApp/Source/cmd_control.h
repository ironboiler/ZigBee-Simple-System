#ifndef __CMD_CONTROL_H
#define __CMD_CONTROL_H

#include "cmd_uart.h"

void Factory_New(void);
void Relay_Control(cmd_form *cmd_msg);
void Read_Temp(cmd_form *cmd_msg);

#endif