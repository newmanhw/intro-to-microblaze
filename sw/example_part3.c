#include "xuartlite.h"
#include "xparameters.h"

#define UART_DEVICE_ID XPAR_AXI_UARTLITE_0_DEVICE_ID

XUartLite Uart;

void setup_uart() {
    XUartLite_Initialize(&Uart, UART_DEVICE_ID);
}

int main() {
    setup_uart();
    u8 c;

    while (1) {
        // Poll UART for input
        if (XUartLite_Recv(&Uart, &c, 1)) {
            // Character received, do something
            xil_printf("Got char: %c\n", c);
        }
    }
}
