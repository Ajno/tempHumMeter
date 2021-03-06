#include "system.h"
#include "base.h"
#include "time.h"
#include "lcd.h"
#include "buttons.h"
#include "pwr_mgmt.h"
#include "temperature.h"
#include "oscillator.h"

static pAppCallback_t pApp;

void baseInstallApp(pAppCallback_t const pCallback)
{
    if (0 != pCallback) 
    {
        pApp = pCallback;
    }
}

void main(void)
{
	systemEnableInterrupts();
	timersInit();
	lcdInit();
	buttonsInit();
	pwrMgmtInit();
	temperatureInit();
	oscillatorInit();
	baseInitApp();
	
	for (;;)
	{		
        if (0 != pApp) 
        {
            (*pApp)();
        }
		systemResetWatchdog();
	} /* loop forever */
	/* please make sure that you never leave main */
}
