#include "cmd_control.h"
#include "printf.h"
#include "bdb_interface.h"

void Factory_New(void)
{
  bdb_resetLocalAction();
  printf("Factory New\r\n");
}