//*****************************************************************************
//
// pwm.c - Example demonstrating timer-based PWM on a 16-bit CCP.
//
// Copyright (c) 2010-2013 Texas Instruments Incorporated.  All rights reserved.
// Software License Agreement
// 
//   Redistribution and use in source and binary forms, with or without
//   modification, are permitted provided that the following conditions
//   are met:
// 
//   Redistributions of source code must retain the above copyright
//   notice, this list of conditions and the following disclaimer.
// 
//   Redistributions in binary form must reproduce the above copyright
//   notice, this list of conditions and the following disclaimer in the
//   documentation and/or other materials provided with the  
//   distribution.
// 
//   Neither the name of Texas Instruments Incorporated nor the names of
//   its contributors may be used to endorse or promote products derived
//   from this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// 
// This is part of revision 1.1 of the Tiva Firmware Development Package.
//
//*****************************************************************************

#include <stdbool.h>
#include <stdint.h>
#include "include/hw_gpio.h"
#include "include/hw_ints.h"
#include "include/hw_memmap.h"
#include "include/hw_timer.h"
#include "include/hw_types.h"
#include "include/gpio.h"
#include "include/interrupt.h"
#include "include/pin_map.h"
#include "include/sysctl.h"
#include "include/timer.h"
#include "include/uart.h"
#include "include/uartstdio.h"

//*****************************************************************************
//
//! \addtogroup timer_examples_list
//! <h1>PWM using Timer (pwm)</h1>
//!
//! This example shows how to configure Timer1B to generate a PWM signal on the
//! timer's CCP pin.
//!
//! This example uses the following peripherals and I/O signals.  You must
//! review these and change as needed for your own board:
//! - TIMER1 peripheral
//! - GPIO Port B peripheral (for T1CCP1 pin)
//! - T1CCP1 - PB5
//!
//! This example uses the following interrupt handlers.  To use this example
//! in your own application you must add these interrupt handlers to your
//! vector table.
//! - None.
//
//*****************************************************************************


//*****************************************************************************
//
// Configure Timer1B as a 16-bit PWM with a duty cycle of 66%.
//
//*****************************************************************************
int
main(void)
{
    //
    // Set the clocking to run directly from the external crystal/oscillator.
    // TODO: The SYSCTL_XTAL_ value must be changed to match the value of the
    // crystal on your board.
    //
    SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN |
                   SYSCTL_XTAL_16MHZ);

    //
    // The Timer1 peripheral must be enabled for use.
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER1);

    //
    // For this example T1CCP1 is used with port B pin 5.
    // The actual port and pins used may be different on your part, consult
    // the data sheet for more information.
    // GPIO port B needs to be enabled so these pins can be used.
    // TODO: change this to whichever GPIO port you are using.
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);

    //
    // Configure the GPIO pin muxing for the Timer/CCP function.
    // This is only necessary if your part supports GPIO pin function muxing.
    // Study the data sheet to see which functions are allocated per pin.
    // TODO: change this to select the port/pin you are using
    //
    GPIOPinConfigure(GPIO_PB5_T1CCP1);

    //
    // Configure the ccp settings for CCP pin.  This function also gives
    // control of these pins to the SSI hardware.  Consult the data sheet to
    // see which functions are allocated per pin.
    // TODO: change this to select the port/pin you are using.
    //
    GPIOPinTypeTimer(GPIO_PORTB_BASE, GPIO_PIN_5);

    //
    // Configure Timer1B as a 16-bit periodic timer.
    //
    TimerConfigure(TIMER1_BASE, TIMER_CFG_SPLIT_PAIR | TIMER_CFG_B_PWM);

    //
    // Set the Timer1B load value to 50000.  For this example a 66% duty cycle
    // PWM signal will be generated.  From the load value (i.e. 50000) down to
    // match value (set below) the signal will be high.  From the match value
    // to 0 the timer will be low.
    //
    TimerLoadSet(TIMER1_BASE, TIMER_B, 50000);

    //
    // Set the Timer1B match value to load value / 3.
    //
    TimerMatchSet(TIMER1_BASE, TIMER_B,
                  TimerLoadGet(TIMER1_BASE, TIMER_B) / 3);

    //
    // Enable Timer1B.
    //
    TimerEnable(TIMER1_BASE, TIMER_B);

    //
    // Loop forever while the Timer1B PWM runs.
    //
    while(1)
    {
    }
}
