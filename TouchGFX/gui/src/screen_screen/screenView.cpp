#include <gui/screen_screen/screenView.hpp>
#include <stdio.h>
#include <math.h>
#include "stm32746g_discovery_audio.h"

// Externs
extern __IO uint32_t uwTick;                      // forwarded from stm32f7xx_hal.c
extern uint16_t VU_Level_Left, VU_Level_Right;    // forwarded from stm32746g_discovery_audio.c

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

    // Update volume
    if(volume != slider1.getValue())
      BSP_AUDIO_OUT_SetVolume(slider1.getValue());
  }
}
