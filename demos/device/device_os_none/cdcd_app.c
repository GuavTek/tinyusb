/**************************************************************************/
/*!
    @file     cdcd_app.c
    @author   hathach (tinyusb.org)

    @section LICENSE

    Software License Agreement (BSD License)

    Copyright (c) 2013, hathach (tinyusb.org)
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:
    1. Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.
    3. Neither the name of the copyright holders nor the
    names of its contributors may be used to endorse or promote products
    derived from this software without specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ''AS IS'' AND ANY
    EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
    WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
    DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE FOR ANY
    DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
    (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
    LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
    ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
    SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

    This file is part of the tinyusb stack.
*/
/**************************************************************************/

#include "cdcd_app.h"

#if TUSB_CFG_DEVICE_CDC

#include "common/fifo.h" // TODO refractor

//--------------------------------------------------------------------+
// INCLUDE
//--------------------------------------------------------------------+
enum {
  CDCD_APP_BUFFER_SIZE = 16
};

//--------------------------------------------------------------------+
// MACRO CONSTANT TYPEDEF
//--------------------------------------------------------------------+
OSAL_TASK_DEF(cdcd_serial_app_task, 128, CDCD_SERIAL_APP_TASK_PRIO);
OSAL_SEM_DEF(cdcd_semaphore);

static osal_semaphore_handle_t sem_hdl;

ATTR_USB_MIN_ALIGNMENT static uint8_t serial_rx_buffer[CDCD_APP_BUFFER_SIZE] TUSB_CFG_ATTR_USBRAM;
ATTR_USB_MIN_ALIGNMENT static uint8_t serial_tx_buffer[CDCD_APP_BUFFER_SIZE] TUSB_CFG_ATTR_USBRAM;

//--------------------------------------------------------------------+
// INTERNAL OBJECT & FUNCTION DECLARATION
//--------------------------------------------------------------------+
FIFO_DEF(fifo_serial, CDCD_APP_BUFFER_SIZE, uint8_t, true);

//--------------------------------------------------------------------+
// IMPLEMENTATION
void cdcd_serial_app_init(void)
{
  sem_hdl = osal_semaphore_create( OSAL_SEM_REF(cdcd_semaphore) );
  ASSERT_PTR( sem_hdl, VOID_RETURN);

  ASSERT( TUSB_ERROR_NONE == osal_task_create( OSAL_TASK_REF(cdcd_serial_app_task) ), VOID_RETURN);
}

void tusbd_cdc_mounted_cb(uint8_t coreid)
{
  osal_semaphore_reset(sem_hdl);

  tusbd_cdc_receive(coreid, serial_rx_buffer, CDCD_APP_BUFFER_SIZE, true);
}

void tusbd_cdc_xfer_isr(uint8_t coreid, tusb_event_t event, cdc_pipeid_t pipe_id, uint32_t xferred_bytes)
{
  switch ( pipe_id )
  {
    case CDC_PIPE_DATA_OUT:
      switch(event)
      {
        case TUSB_EVENT_XFER_COMPLETE:
          for(uint8_t i=0; i<xferred_bytes; i++)
          {
            fifo_write(&fifo_serial, serial_rx_buffer+i);
          }
          osal_semaphore_post(sem_hdl);  // notify main task
        break;

        case TUSB_EVENT_XFER_ERROR:
          xferred_bytes = 0; // ignore
        break;

        case TUSB_EVENT_XFER_STALLED:
        default :
          ASSERT(false, VOID_RETURN);
          break;
      }
    break;

    case CDC_PIPE_DATA_IN:
    case CDC_PIPE_NOTIFICATION:
    default:
    break;
  }
}

OSAL_TASK_FUNCTION( cdcd_serial_app_task ) (void* p_task_para)
{
  tusb_error_t error;

  OSAL_TASK_LOOP_BEGIN

  osal_semaphore_wait(sem_hdl, OSAL_TIMEOUT_WAIT_FOREVER, &error);

  if ( tusbd_cdc_is_configured(0) )
  {
    // echo back data in the fifo
    if ( !tusbd_cdc_is_busy(0, CDC_PIPE_DATA_IN) )
    {
      uint16_t count=0;
      while( fifo_read(&fifo_serial, &serial_tx_buffer[count]) )
      {
        count++;
      }

      if (count)
      {
        tusbd_cdc_send(0, serial_tx_buffer, count, false);
      }
    }

    // getting next data from host
    tusbd_cdc_receive(0, serial_rx_buffer, CDCD_APP_BUFFER_SIZE, true);
  }

  OSAL_TASK_LOOP_END
}

#endif
