#ifndef SCREENVIEW_HPP
#define SCREENVIEW_HPP

#include <gui_generated/screen_screen/screenViewBase.hpp>
#include <gui/screen_screen/screenPresenter.hpp>

class screenView : public screenViewBase
{
public:
    screenView();
    virtual ~screenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    void handleTickEvent();
    void btn_color_onclick();
    void SliderHandler(const Slider& sli, const ClickEvent& Event);

protected:
    int tick_cnt;
};

#endif // SCREENVIEW_HPP
