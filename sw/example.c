#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include "xparameters.h"
#include "xil_io.h"

#define LEDS_ADDR XPAR_APB_LED_CTL_0_BASEADDR
#define SWITCHES_ADDR XPAR_AXI_GPIO_0_BASEADDR

int main()
{
    init_platform();

    print("Starting Application\n\r");
    print("YOUR NAME HERE\n\r");


    while (1) {
    	u32 switches;
    	u32 leds;

    	switches = Xil_In32(SWITCHES_ADDR);
    	leds     = switches & 0xFFFF;   // only use lower 16 bits

    	Xil_Out32(LEDS_ADDR, leds); // 0x 0000 switches

    }

    cleanup_platform();
    return 0;
}
