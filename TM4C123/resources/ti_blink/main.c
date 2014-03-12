#include <stdbool.h>
#include <stdint.h>
#include "include/hw_memmap.h"
#include "include/debug.h"
#include "include/gpio.h"
#include "include/rom.h"
#include "include/sysctl.h"

int main(void)
{
    //
    // Enable the GPIO module.
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    SysCtlDelay(1);

    //
    // Configure PF1 as an output.
    //
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1);

    //
    // Loop forever.
    //
    while(1)
    {
        //
        // Set the GPIO high.
        //
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, GPIO_PIN_1);

        //
        // Delay for a while.
        //
        SysCtlDelay(1000000);

        //
        // Set the GPIO low.
        //
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0);

        //
        // Delay for a while.
        //
        SysCtlDelay(1000000);
    }
}
