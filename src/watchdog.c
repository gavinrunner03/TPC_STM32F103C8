#include "watchdog.h"
#include "stm32f1xx.h"

int WATCHDOG_INIT(void)
{
    // Initialize the watchdog timer to a timeout of 1 second.
    IWDG->KR = 0xCCCC; // Start the watchdog
    IWDG->KR = 0x5555; // Unlock the write protection
    IWDG->PR = 0x04;  // Set the prescaler to divide by 64
    IWDG->RLR = 625; // Set the reload value for 1 second timeout
    while (IWDG->SR & (IWDG_SR_PVU | IWDG_SR_RVU)) 
    {
        // Block until Prescaler Value Update (PVU) and Reload Value Update (RVU) clear
    }
    IWDG->KR = 0xAAAA; // Reload the counter
    return 0;
}