/**
  ******************************************************************************
  * File Name          : TouchGFXGeneratedHAL.cpp
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */

#include <TouchGFXGeneratedHAL.hpp>
#include <touchgfx/hal/OSWrappers.hpp>
#include <gui/common/FrontendHeap.hpp>
#include <touchgfx/hal/GPIO.hpp>

#include "stm32f7xx.h"
#include "stm32f7xx_hal_ltdc.h"

using namespace touchgfx;

namespace {
    static uint16_t lcd_int_active_line;
    static uint16_t lcd_int_porch_line;
}

void TouchGFXGeneratedHAL::initialize()
{
    HAL::initialize();

    registerEventListener(*(Application::getInstance()));
    registerTaskDelayFunction(&OSWrappers::taskDelay);
    setFrameRefreshStrategy(HAL::REFRESH_STRATEGY_OPTIM_SINGLE_BUFFER_TFT_CTRL);
    enableLCDControllerInterrupt();
    enableInterrupts();
    setFrameBufferStartAddresses((void*)0xC0000000, (void*)0, (void*)0);
    /*
     * Set whether the DMA transfers are locked to the TFT update cycle. If
     * locked, DMA transfer will not begin until the TFT controller has finished
     * updating the display. If not locked, DMA transfers will begin as soon as
     * possible. Default is true (DMA is locked with TFT).
     */
    lockDMAToFrontPorch(true);
}

void TouchGFXGeneratedHAL::configureInterrupts()
{
    NVIC_SetPriority(DMA2D_IRQn, 9);
    NVIC_SetPriority(LTDC_IRQn, 9);
}

void TouchGFXGeneratedHAL::enableInterrupts()
{
    NVIC_EnableIRQ(DMA2D_IRQn);
    NVIC_EnableIRQ(LTDC_IRQn);
}

void TouchGFXGeneratedHAL::disableInterrupts()
{
    NVIC_DisableIRQ(DMA2D_IRQn);
    NVIC_DisableIRQ(LTDC_IRQn);
}

void TouchGFXGeneratedHAL::enableLCDControllerInterrupt()
{
    lcd_int_active_line = (LTDC->BPCR & 0x7FF) - 1;
    lcd_int_porch_line = (LTDC->AWCR & 0x7FF) - 1;

    /* Sets the Line Interrupt position */
    LTDC->LIPCR = lcd_int_active_line;
    /* Line Interrupt Enable            */
    LTDC->IER |= LTDC_IER_LIE;
}

uint16_t* TouchGFXGeneratedHAL::getTFTFrameBuffer() const
{
    return (uint16_t*)LTDC_Layer1->CFBAR;
}

void TouchGFXGeneratedHAL::setTFTFrameBuffer(uint16_t* adr)
{
    LTDC_Layer1->CFBAR = (uint32_t)adr;

    /* Reload immediate */
    LTDC->SRCR = (uint32_t)LTDC_SRCR_IMR;
}

void TouchGFXGeneratedHAL::flushFrameBuffer(const touchgfx::Rect& rect)
{
  HAL::flushFrameBuffer(rect);
}

bool TouchGFXGeneratedHAL::blockCopy(void* RESTRICT dest, const void* RESTRICT src, uint32_t numBytes)
{
  return HAL::blockCopy(dest, src, numBytes);
}

uint16_t TouchGFXGeneratedHAL::getTFTCurrentLine()
{
    // This function only requires an implementation if single buffering
    // on LTDC display is being used (REFRESH_STRATEGY_OPTIM_SINGLE_BUFFER_TFT_CTRL).

    // The CPSR register (bits 15:0) specify current line of TFT controller.
    uint16_t curr = (uint16_t)(LTDC->CPSR & 0xffff);
    uint16_t backPorchY = (uint16_t)(LTDC->BPCR & 0x7FF) + 1;

    // The semantics of the getTFTCurrentLine() function is to return a value
    // in the range of 0-totalheight. If we are still in back porch area, return 0.
    return (curr < backPorchY) ? 0 : (curr - backPorchY);
}

extern "C"
{
    void HAL_LTDC_LineEventCallback(LTDC_HandleTypeDef *hltdc)
    {
        if (LTDC->LIPCR == lcd_int_active_line)
        {
            //entering active area
            HAL_LTDC_ProgramLineEvent(hltdc, lcd_int_porch_line);
            HAL::getInstance()->vSync();
            OSWrappers::signalVSync();
            // Swap frame buffers immediately instead of waiting for the task to be scheduled in.
            // Note: task will also swap when it wakes up, but that operation is guarded and will not have
            // any effect if already swapped.
            HAL::getInstance()->swapFrameBuffers();
            GPIO::set(GPIO::VSYNC_FREQ);
        }
        else
        {
            //exiting active area
            HAL_LTDC_ProgramLineEvent(hltdc, lcd_int_active_line);
            GPIO::clear(GPIO::VSYNC_FREQ);
            HAL::getInstance()->frontPorchEntered();
        }
    }
}
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
