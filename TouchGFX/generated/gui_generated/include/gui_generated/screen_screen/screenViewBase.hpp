/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#ifndef SCREENVIEWBASE_HPP
#define SCREENVIEWBASE_HPP

#include <gui/common/FrontendApplication.hpp>
#include <mvp/View.hpp>
#include <gui/screen_screen/screenPresenter.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/containers/buttons/Buttons.hpp>
#include <touchgfx/widgets/graph/GraphWrapAndOverwrite.hpp>
#include <touchgfx/widgets/graph/GraphElements.hpp>
#include <touchgfx/containers/Slider.hpp>
#include <touchgfx/containers/progress_indicators/LineProgress.hpp>
#include <touchgfx/widgets/canvas/PainterRGB565Bitmap.hpp>

class screenViewBase : public touchgfx::View<screenPresenter>
{
public:
    screenViewBase();
    virtual ~screenViewBase() {}
    virtual void setupScreen();

protected:
    FrontendApplication& application() {
        return *static_cast<FrontendApplication*>(touchgfx::Application::getInstance());
    }

    /*
     * Member Declarations
     */
    touchgfx::Box __background;
    touchgfx::BoxWithBorderButtonStyle< touchgfx::ClickButtonTrigger > btn_test;
    touchgfx::GraphWrapAndOverwrite<400> graph_t;
    touchgfx::GraphElementHistogram graph_tHistogram1;
    touchgfx::Slider slider1;
    touchgfx::LineProgress vu_L;
    touchgfx::PainterRGB565Bitmap vu_LPainter;
    touchgfx::LineProgress vu_R;
    touchgfx::PainterRGB565Bitmap vu_RPainter;

private:

    /*
     * Canvas Buffer Size
     */
    static const uint16_t CANVAS_BUFFER_SIZE = 7200;
    uint8_t canvasBuffer[CANVAS_BUFFER_SIZE];
};

#endif // SCREENVIEWBASE_HPP
