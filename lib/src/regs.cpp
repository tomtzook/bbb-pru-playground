
#include "regs.h"


volatile register unsigned int __R30;
volatile register unsigned int __R31;

namespace pru {

template<>
void write_reg<r30>(regval_t value) {
    __R30 = value;
}

template<>
regval_t read_reg<r30>() {
    return __R30;
}

template<>
void write_reg<r31>(regval_t value) {
    __R31 = value;
}

template<>
regval_t read_reg<r31>() {
    return __R31;
}

}
