#include "main.h"

volatile int hello = 0;
void SystemInit(void){
    
}

int main(void) {
    // Basic infinite loop for an embedded target
    while(1) {
        hello++;
    }

}
