#include "cmd_control.h"
#include "printf.h"
#include "bdb_interface.h"
#include "AF.h"
#include "APS.h"
#include "zcl_genericapp.h"

void Factory_New(void)
{
  bdb_resetLocalAction();
  printf("Factory New\r\n");
}

void Relay_Control(cmd_form *cmd_msg)
{
  afAddrType_t GenericApp_DstAddr;
  endPointDesc_t *GenericApp_epDesc;
  uint8 *buf = osal_mem_alloc(1);
  *buf = cmd_msg->para_2;
  
  GenericApp_DstAddr.addrMode = (afAddrMode_t)Addr16Bit;
  GenericApp_DstAddr.endPoint = GENERICAPP_ENDPOINT;
  GenericApp_epDesc = afFindEndPointDesc( GENERICAPP_ENDPOINT );
  
  GenericApp_DstAddr.addr.shortAddr = cmd_msg->para_1;
  
  if(cmd_msg->para_2==1||cmd_msg->para_2==2||cmd_msg->para_2==3)
  {
    AF_DataRequest(&GenericApp_DstAddr,
                     GenericApp_epDesc,
                     GENERICAPP_CLUSTERID,
                     1,
                     (byte *)buf,
                     &APS_Counter,
                     AF_ACK_REQUEST,
                     AF_DEFAULT_RADIUS
                     );
    printf("OK!\r\n");
  }
  else  
  {
    printf("ERROW:ILLEGAL INPUT!\r\n");
  }
  
  osal_mem_free(buf);
}

void Read_Temp(cmd_form *cmd_msg)
{
  afAddrType_t GenericApp_DstAddr;
  endPointDesc_t *GenericApp_epDesc;
  uint8 *buf = osal_mem_alloc(1);
  *buf = 9;

  GenericApp_DstAddr.addrMode = (afAddrMode_t)Addr16Bit;
  GenericApp_DstAddr.endPoint = GENERICAPP_ENDPOINT;
  GenericApp_epDesc = afFindEndPointDesc( GENERICAPP_ENDPOINT );

  GenericApp_DstAddr.addr.shortAddr = cmd_msg->para_1;

  AF_DataRequest(&GenericApp_DstAddr,
                     GenericApp_epDesc,
                     GENERICAPP_CLUSTERID,
                     1,
                     (byte *)buf,
                     &APS_Counter,
                     AF_ACK_REQUEST,
                     AF_DEFAULT_RADIUS
                     );
  printf("OK!\r\n");
  osal_mem_free(buf);
}