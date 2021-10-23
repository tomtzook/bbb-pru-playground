
#include <stdint.h>
#include <pru_iep.h>

#include "iep.h"


namespace pru {
namespace iep {

// counter = counts on ticks of iep_clock (200 MHz)
// TMR_GLB_CFG
//  CNT_EN - enable/disable counter
//  DEFAULT_INC - counter increment per tick
// TMR_CNT - count
// TMR_GLB_STS
//  CNT_OVF - 1 = overflow of counter
// TMR_COMPEN
//  COMPEN_CNT - counts to use compensation

void enable_counter(unsigned increment_value) {
    CT_IEP.TMR_GLB_CFG_bit.CNT_EN = 1;
    CT_IEP.TMR_GLB_CFG_bit.DEFAULT_INC = increment_value;
}

void set_counter(unsigned value) {
    CT_IEP.TMR_CNT = value;
}

unsigned read_counter() {
    return CT_IEP.TMR_CNT;
}

void enable_counter_overflow(bool enabled) {
    CT_IEP.TMR_GLB_STS_bit.CNT_OVF = enabled ? 1 : 0;
}

void set_counter_compensation(unsigned value, unsigned count) {
    CT_IEP.TMR_GLB_CFG_bit.CMP_INC = value;
    CT_IEP.TMR_COMPEN_bit.COMPEN_CNT = count;
}

}
}
