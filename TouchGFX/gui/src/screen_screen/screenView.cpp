#include <gui/screen_screen/screenView.hpp>
#include "math.h"

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
  tick_cnt++;
  if(tick_cnt%3 == 0){
    graph_t.addDataPoint(sinf(tick_cnt*0.1));
  }
}
