#pragma once

#include "prudefs.h"
#include "regs.h"


namespace pru {
namespace intc {

void clear_event(unsigned event);

template<unsigned host_intc_mask,
        unsigned _pru_to_arm_event, unsigned _arm_to_pru_event>
struct pru_intc {
public:
    inline static unsigned pru_to_arm_event() {
        return _pru_to_arm_event;
    }

    inline static unsigned arm_to_pru_event() {
        return _arm_to_pru_event;
    }

    inline static bool did_host_interrupt() {
        auto value = read_reg<r31>();
        return value & host_intc_mask;
    }

    inline static void clear_host_interrupt() {
        clear_event(_arm_to_pru_event);
    }
};

typedef pru_intc<PRU0_R31_FROM_HOST_INT, EVENT_PRU0_TO_ARM, EVENT_ARM_TO_PRU0> pru0;
typedef pru_intc<PRU1_R31_FROM_HOST_INT, EVENT_PRU1_TO_ARM, EVENT_ARM_TO_PRU1> pru1;

}
}
