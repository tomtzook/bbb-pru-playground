#include <stdint.h>
#include <pru_cfg.h>

#include "intrinsic.h"
#include "prudefs.h"
#include "resource_table_empty.h"

#include "prugpiocxx.h"


int main() {
     int i;
    /* Configure GPI and GPO as Mode 0 (Direct Connect) */
    CT_CFG.GPCFG0 = 0x0000;

    for (i = 0; i < 50; i++) {
        pru::gpio::usr0::set();
        __delay_cycles(100000000); // half-second delay
        pru::gpio::usr1::set();
        __delay_cycles(100000000); // half-second delay
        pru::gpio::usr2::set();
        __delay_cycles(100000000); // half-second delay
        pru::gpio::usr3::set();

        __delay_cycles(100000000); // half-second delay

        pru::gpio::usr0::clear();
        pru::gpio::usr1::clear();
        pru::gpio::usr2::clear();
        pru::gpio::usr3::clear();

        __delay_cycles(100000000); // half-second delay
    }

    __halt();

    return 0;
}
