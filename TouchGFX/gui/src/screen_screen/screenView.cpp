#include <gui/screen_screen/screenView.hpp>
#include <stdio.h>
#include <math.h>
#include "stm32746g_discovery_audio.h"
#include "usbd_def.h"

// Externs
extern __IO uint32_t uwTick;                      // forwarded from stm32f7xx_hal.c
extern uint16_t VU_Level_Left, VU_Level_Right;    // forwarded from stm32746g_discovery_audio.c
extern USBD_HandleTypeDef hUsbDeviceFS;           // forwarded from usb_device.c

screenView::screenView()
{
  tick_cnt = 0;
}

void screenView::setupScreen()
{
  screenViewBase::setupScreen();
}

void screenView::tearDownScreen()
{
  screenViewBase::tearDownScreen();
}

void screenView::handleTickEvent(){
  static uint32_t tk_graph = 0;
  static uint32_t tk_ctl = 0;
  static int volume = 50;
  if(uwTick - tk_graph > 40){
    tk_graph = uwTick;
    graph_t.addDataPoint(sinf(uwTick*0.004));
  }
  if(uwTick - tk_ctl > 100){
    tk_ctl = uwTick;

    // Update volume if USB connected
    int usb_conn_state = hUsbDeviceFS.dev_state;
    printf("usb_conn_state:%d\r\n", usb_conn_state);
    switch(usb_conn_state){
      case USBD_STATE_DEFAULT:
        break;
      case USBD_STATE_ADDRESSED:
        slider1.setValue(0);
        break;
      case USBD_STATE_CONFIGURED:
        if(volume != slider1.getValue())
          BSP_AUDIO_OUT_SetVolume(slider1.getValue());
        break;
      case USBD_STATE_SUSPENDED:
        BSP_AUDIO_OUT_DeInit();
        slider1.setValue(0);
      default:;
    }
  }
}
