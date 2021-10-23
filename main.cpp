extern "C" {
#include <stdint.h>
#include <pru_cfg.h>
#include <pru_intc.h>
#include <rsc_types.h>
#include <pru_rpmsg.h>
}

#include "prudefs.h"
#include "intrinsic.h"
#include "config.h"
#include "iep.h"
#include "intc.h"
#include "rp/rpmsg.h"
#include "gpio.h"
#include "egpio.h"

//#include "resource_table_empty.h"
#include "resource_table_0.h"


/* Host-0 Interrupt sets bit 30 in register R31 */
//#define HOST_INT			((uint32_t) 1 << 30)

/* The PRU-ICSS system events used for RPMsg are defined in the Linux device tree
 * PRU0 uses system event 16 (To ARM) and 17 (From ARM)
 * PRU1 uses system event 18 (To ARM) and 19 (From ARM)
 */
#define TO_ARM_HOST			16
#define FROM_ARM_HOST			17

/*
 * Using the name 'rpmsg-pru' will probe the rpmsg_pru driver found
 * at linux-x.y.z/drivers/rpmsg/rpmsg_pru.c
 */
#define CHAN_NAME			"rpmsg-pru"
#define CHAN_DESC			"Channel 30"
#define CHAN_PORT			30


uint8_t payload[RPMSG_MESSAGE_SIZE];

struct {
    unsigned int count;
    bool overflow;
} message;

volatile unsigned int* shared = (unsigned int*)(PRU_LOCAL_DRAM);

int main() {
    shared[0] = CHAN_PORT;
    shared[1] = true;

    // int i;
    /* Configure GPI and GPO as Mode 0 (Direct Connect) */
    CT_CFG.GPCFG0 = 0x0000;

    uint16_t src, dst, len;

    /* Allow OCP master port access by the PRU so the PRU can read external memories */
    pru::ocp_init();

    /* Clear the status of the PRU-ICSS system event that the ARM will use to 'kick' us */
    pru::intc::pru0::clear_host_interrupt();

    /* Make sure the Linux drivers are ready for RPMsg communication */
    pru::rpmsg::wait_until_ready(resourceTable.rpmsg_vdev);

    pru::rpmsg::channel rpmsg(&resourceTable.rpmsg_vring0, &resourceTable.rpmsg_vring1,
                              pru::intc::pru0::pru_to_arm_event(),
                              pru::intc::pru0::arm_to_pru_event(),
                              CHAN_NAME, CHAN_DESC, CHAN_PORT);

    pru::iep::set_counter(0);
    pru::iep::set_counter_compensation(0, 0);
    pru::iep::enable_counter();

    shared[1] = true;
    while (shared[1]) {
        if (pru::intc::pru0::did_host_interrupt()) {
            pru::intc::pru0::clear_host_interrupt();

            while (PRU_RPMSG_SUCCESS == rpmsg.receive(&src, &dst, payload, &len)) {
                message.count = pru::iep::read_counter();
                rpmsg.send(dst, src, &message, sizeof(message));

                pru::iep::set_counter(0);
            }

            __delay_ms(500);
        }

        shared[1] = true;
    }

    __halt();

    return 0;
}
