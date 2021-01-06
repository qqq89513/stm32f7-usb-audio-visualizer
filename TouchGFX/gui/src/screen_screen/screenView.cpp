#include <gui/screen_screen/screenView.hpp>
#include "math.h"

extern uint32_t uwTick;

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
  if(uwTick - tk_graph > 40){
    tk_graph = uwTick;
    graph_t.addDataPoint(sinf(uwTick*0.004));
  }
  if(uwTick - tk_ctl > 100){

  }
}
