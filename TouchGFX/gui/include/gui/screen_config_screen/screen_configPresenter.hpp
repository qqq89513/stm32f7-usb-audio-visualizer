#ifndef SCREEN_CONFIGPRESENTER_HPP
#define SCREEN_CONFIGPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class screen_configView;

class screen_configPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    screen_configPresenter(screen_configView& v);

    /**
     * The activate function is called automatically when this screen is "switched in"
     * (ie. made active). Initialization logic can be placed here.
     */
    virtual void activate();

    /**
     * The deactivate function is called automatically when this screen is "switched out"
     * (ie. made inactive). Teardown functionality can be placed here.
     */
    virtual void deactivate();

    virtual ~screen_configPresenter() {};

private:
    screen_configPresenter();

    screen_configView& view;
};

#endif // SCREEN_CONFIGPRESENTER_HPP
