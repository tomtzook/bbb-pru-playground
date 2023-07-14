
#include <stdint.h>
#include <pru_iep.h>

#include "iep.h"


namespace pru {
namespace iep {

// counter = counts on ticks of iep_clock (200 MHz)
//          5 ns per tick
// TMR_GLB_CFG
//  CNT_EN - enable/disable counter
//  DEFAULT_INC - counter increment per tick
// TMR_CNT - count
// TMR_GLB_STS
//  CNT_OVF - 1 = overflow of counter
// TMR_COMPEN
//  COMPEN_CNT - counts to use compensation
// TMR_CMP_STS - status for event hits
// TMR_CMP_CFG - enable/disable events

void enable_counter(unsigned increment_value) {
    CT_IEP.TMR_GLB_CFG_bit.DEFAULT_INC = increment_value;
    CT_IEP.TMR_GLB_CFG_bit.CNT_EN = 1;
}

void set_counter(unsigned value) {
    CT_IEP.TMR_CNT = value;
}

unsigned int read_counter() {
    return CT_IEP.TMR_CNT;
}

void enable_counter_overflow(bool enabled) {
    CT_IEP.TMR_GLB_STS_bit.CNT_OVF = enabled ? 1 : 0;
}

void set_counter_compensation(unsigned value, unsigned count) {
    CT_IEP.TMR_GLB_CFG_bit.CMP_INC = value;
    CT_IEP.TMR_COMPEN_bit.COMPEN_CNT = count;
}

void enable_event(unsigned event_id, unsigned int compare_value) {
    switch (event_id) {
        case 0:
            CT_IEP.TMR_CMP0_bit.CMP0 = compare_value;
            break;
        case 1:
            CT_IEP.TMR_CMP1_bit.CMP1 = compare_value;
            break;
        case 2:
            CT_IEP.TMR_CMP2_bit.CMP2 = compare_value;
            break;
        case 3:
            CT_IEP.TMR_CMP3_bit.CMP3 = compare_value;
            break;
        case 4:
            CT_IEP.TMR_CMP4_bit.CMP4 = compare_value;
            break;
        case 5:
            CT_IEP.TMR_CMP5_bit.CMP5 = compare_value;
            break;
        case 6:
            CT_IEP.TMR_CMP6_bit.CMP6 = compare_value;
            break;
        case 7:
            CT_IEP.TMR_CMP7_bit.CMP7 = compare_value;
            break;
    }

    CT_IEP.TMR_CMP_CFG_bit.CMP_EN |= (1 << event_id);
}

void disable_event(unsigned event_id) {
    CT_IEP.TMR_CMP_CFG_bit.CMP_EN &= ~(1 << event_id);
}

void set_event0_reset_enabled(bool enabled) {
    CT_IEP.TMR_CMP_CFG_bit.CMP0_RST_CNT_EN = enabled ? 1 : 0;
}

bool is_event_hit(unsigned event_id, bool clear) {
    bool hit = (CT_IEP.TMR_CMP_STS_bit.CMP_HIT & (1 << event_id)) > 0;
    if (hit && clear) {
        clear_event(event_id);
    }

    return hit;
}

void clear_event(unsigned event_id) {
    CT_IEP.TMR_CMP_STS_bit.CMP_HIT |= (1 << event_id);
}

}
}
