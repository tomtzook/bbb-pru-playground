
#include <stdint.h>
#include <pru_intc.h>

#include "intc.h"


namespace pru {
namespace intc {

void clear_event(unsigned event) {
    CT_INTC.SICR_bit.STS_CLR_IDX = event;
}

}
}
