/*
 * display_test.cpp
 *
 *  Created on: Sep 11, 2015
 *      Author: z0037ysj
 */

#include "display_test.h"
#include "timer.h"
#include "buttons.h"

void test_display_shiftAndBackLight_init()
{
    displayOnOffControl_t onOffSetting;

    timersInit();
    displayInit();
    buttonsInit();

    displayBackLightOn(TRUE);

    // Display on
    onOffSetting.bDisplayOn = TRUE;
    onOffSetting.bCursorOn = TRUE;
    onOffSetting.bBlinkingCursor = TRUE;
    displayOnOffControl(onOffSetting);

    //Display clear
    displayClear();

    displayWrite("vrchnym tlacitkom zmen smer");
    displayMoveCursor(cDisplayAddressMax/2);
    displayWrite("spodnym tlacitkom vypni/zapni LED");
}

void test_display_shiftAndBackLight_run()
{
    static displayMovingDirection_t dir = {TRUE, TRUE};
    static Word cntr = 0;
    static Bool bBacklightOn = TRUE;
    buttonState_t stateLower;
    buttonState_t stateUpper;
    
    waitX100us(500); // wait 50 ms
    buttonStateDetection(cButton_Lower,&stateLower);
    buttonStateDetection(cButton_Upper,&stateUpper);
    cntr++;
    if (cButtonState_JustPressed == stateUpper)
    {
        dir.bShiftRightInsteadOfLeft = 
                (dir.bShiftRightInsteadOfLeft ? FALSE : TRUE );
    }
    if (cButtonState_JustPressed == stateLower)
    {
        bBacklightOn = (bBacklightOn ? FALSE : TRUE );
        displayBackLightOn(bBacklightOn);
    }
    if (cntr >= 5)
    {        
        dir.bShiftScreenInsteadOfCursor = TRUE;   
        displayOrCursorShift(dir);
        cntr = 0;
    }
}

void test_display_contrast_init()
{
    displayOnOffControl_t onOffSetting;

    timersInit();
    buttonsInit();

    displayBackLightOn(TRUE);

    // Display on
    onOffSetting.bDisplayOn = TRUE;
    onOffSetting.bCursorOn = TRUE;
    onOffSetting.bBlinkingCursor = TRUE;
    displayOnOffControl(onOffSetting);

    //Display clear
    displayClear();

    displayWrite("contrast:");
    displayMoveCursor(cDisplayAddressMax/2);
    displayWrite("red(+), black(-)");
}

void test_display_contrast_run()
{
    static Word contrastOut = 50;
    static Word contrastIn = 0;
    buttonState_t stateLower;
    buttonState_t stateUpper;
    
    buttonStateDetection(cButton_Lower,&stateLower);
    buttonStateDetection(cButton_Upper,&stateUpper);
    if (cButtonState_JustPressed == stateUpper)
    {
        if (100 != contrastOut) 
        {
            contrastOut = contrastOut + 5;            
            displaySetContrast(contrastOut);
            contrastIn = displayGetContrast();
        }
    }
    if (cButtonState_JustPressed == stateLower)
    {
        if (0 != contrastOut) 
        {
            contrastOut = contrastOut - 5;   
            displaySetContrast(contrastOut);
            contrastIn = displayGetContrast();
        }
    }
}
