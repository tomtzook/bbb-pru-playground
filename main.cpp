#include <stdint.h>
#include <stddef.h>
#include <rsc_types.h>  /* provides struct resource_table */
#include <vector>

#include "intrinsic.h"

#define CYCLES_PER_SECOND 200000000 /* PRU has 200 MHz clock */

#define P9_31 (1 << 0) /* R30 at 0x1 = pru1_pru0_pru_r30_0 = ball A13 = P9_31 */

volatile register uint32_t __R30; /* output register for PRU */

int main() {
    //std::vector<int> v;
    //v.push_back(5);
    //__asm("     HALT");
    ASM("   HALT");

    __delay_cycles(5);


    __halt();

    return 0;
}
