
#include <stdint.h>
#include <pru_cfg.h>

#include "config.h"


namespace pru {

void ocp_init() {
    CT_CFG.SYSCFG_bit.STANDBY_INIT = 0;
}

}
