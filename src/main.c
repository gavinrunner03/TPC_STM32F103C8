#include "stm32f1xx.h"
#include "main.h"

volatile int hello = 0;
void SystemInit(void){
    /*
        Initalize the system clock to 8Mhz.
        Initialize the watchdog timer to a timeout of 1 second. 
        Initialize GPIO pins to be ADC controlled
        Initialize the ADC for analog input reading.
        

        1. Initialize the system clock to 8Mhz.
        RCC->CFGR = (RCC_CFGR &~(0xFUL << 4)) | (0xAUL << 4);
    */
}

int main(void) {
    // Basic infinite loop for an embedded target
    while(1) {
        hello++;
    }

}
