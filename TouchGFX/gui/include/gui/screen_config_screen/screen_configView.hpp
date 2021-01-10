#ifndef SCREEN_CONFIGVIEW_HPP
#define SCREEN_CONFIGVIEW_HPP

#include <gui_generated/screen_config_screen/screen_configViewBase.hpp>
#include <gui/screen_config_screen/screen_configPresenter.hpp>

class screen_configView : public screen_configViewBase
{
public:
    screen_configView();
    virtual ~screen_configView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
};

#endif // SCREEN_CONFIGVIEW_HPP
