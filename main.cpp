#include <stdint.h>
#include <pru_cfg.h>

#include "intrinsic.h"
#include "resource_table_empty.h"
#include "prugpio.h"


unsigned int volatile * const GPIO1_SET = (unsigned int *)(GPIO1 + GPIO_SETDATAOUT);
unsigned int volatile * const GPIO1_CLEAR = (unsigned int *)(GPIO1 + GPIO_CLEARDATAOUT);

int main() {
     int i;
    /* Configure GPI and GPO as Mode 0 (Direct Connect) */
    CT_CFG.GPCFG0 = 0x0000;

    for (i = 0; i < 50; i++) {
        *GPIO1_SET = (USR3 | USR2);
        __delay_cycles(100000000); // half-second delay
        *GPIO1_CLEAR = (USR3 | USR2);
        __delay_cycles(100000000); // half-second delay
    }

    __halt();

    return 0;
}
