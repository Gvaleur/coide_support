#include <stdbool.h>
#include <stdint.h>
#include "hw_memmap.h"
#include "debug.h"
#include "gpio.h"
#include "sysctl.h"

int main(void)
{
    //
    // Enable the GPIO module.
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    SysCtlDelay(1);

    //
    // Configure PA1 as an output.
    //
    GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, GPIO_PIN_7);

    //
    // Loop forever.
    //
    while(1)
    {
        //
        // Set the GPIO high.
        //
        GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_7, GPIO_PIN_7);

        //
        // Delay for a while.
        //
        SysCtlDelay(1000000);

        //
        // Set the GPIO low.
        //
        GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_7, 0);

        //
        // Delay for a while.
        //
        SysCtlDelay(1000000);
    }
}
