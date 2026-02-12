#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include "xparameters.h"
#include "xil_io.h"

#include "xintc.h"
#include "xil_exception.h"

// memory address definitions
#define LEDS_ADDR   XPAR_APB_LED_CTL_0_BASEADDR
#define RGB0_ADDR   (LEDS_ADDR + 4*1)
#define RGB1_ADDR   (LEDS_ADDR + 4*2)

#define SWITCHES_ADDR XPAR_AXI_GPIO_0_BASEADDR

// global variables
volatile u8 rgb0_value = 0;
volatile u8 rgb1_value = 0;
volatile int timer_tick = 0;

// Timer ISR
void TimerISR(void *CallBackRef)
{
    static u8 color = 0;

    // modify rgb0 and rgb1 color value here

    timer_tick = 1;  // flag main loop to update RGB registers
    
    // debug: to help you see if interrupt is working
    xil_printf("Interrupt occurred!\r\n");
}


// Interrupt controller setup
int SetupInterrupts(void)
{
	XIntc InterruptController;
	int Status;
	// Initialize the interrupt controller driver
	Status = XIntc_Initialize(&InterruptController, XPAR_INTC_0_DEVICE_ID);
	// Connect the interrupt handler to the ISR
	Status = XIntc_Connect(&InterruptController, 0,
	(XInterruptHandler)TimerISR, 0);
	// Start the interrupt controller
	Status = XIntc_Start(&InterruptController, XIN_REAL_MODE);
	// Enable interrupts in the MicroBlaze processor
	XIntc_Enable(&InterruptController, 0);
	Xil_ExceptionInit();
	Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_INT,
	(Xil_ExceptionHandler)XIntc_InterruptHandler,
	&InterruptController);
	Xil_ExceptionEnable();
    return XST_SUCCESS;
}

/* ============================================================
 * Main
 * ============================================================ */
int main()
{
    init_platform();

    xil_printf("Starting Application\r\n");

    if (SetupInterrupts() != XST_SUCCESS) {
        xil_printf("Interrupt setup failed\r\n");
        return -1;
    }

    while (1) {
        u32 switches;
        u32 leds;

        // Poll switches → LEDs
        switches = Xil_In32(SWITCHES_ADDR);
        leds     = switches & 0xFFFF;
        Xil_Out32(LEDS_ADDR, leds);

        // Update RGBs when ISR fires
        if (timer_tick) {
            timer_tick = 0;
            Xil_Out32(RGB0_ADDR, rgb0_value);
            Xil_Out32(RGB1_ADDR, rgb1_value);
        }
    }

    cleanup_platform();
    return 0;
}
