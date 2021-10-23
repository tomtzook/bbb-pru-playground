extern "C" {
#include <stdint.h>
#include <pru_cfg.h>
#include <pru_intc.h>
#include <rsc_types.h>
#include <pru_rpmsg.h>
}

#include "intrinsic.h"
#include "prudefs.h"
#include "rp/rpmsg.h"
#include "prugpiocxx.h"
#include "pruegpiocxx.h"

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

/*
 * Used to make sure the Linux drivers are ready for RPMsg communication
 * Found at linux-x.y.z/include/uapi/linux/virtio_config.h
 */
#define VIRTIO_CONFIG_S_DRIVER_OK	4


uint8_t payload[RPMSG_MESSAGE_SIZE];

volatile unsigned int* shared = (unsigned int*)(PRU0_DRAM);

int main() {
    shared[0] = CHAN_PORT;

    // int i;
    /* Configure GPI and GPO as Mode 0 (Direct Connect) */
    CT_CFG.GPCFG0 = 0x0000;

    uint16_t src, dst, len;

    /* Allow OCP master port access by the PRU so the PRU can read external memories */
    CT_CFG.SYSCFG_bit.STANDBY_INIT = 0;

    /* Clear the status of the PRU-ICSS system event that the ARM will use to 'kick' us */
    CT_INTC.SICR_bit.STS_CLR_IDX = FROM_ARM_HOST;

    /* Make sure the Linux drivers are ready for RPMsg communication */
    pru::rpmsg::wait_until_ready(resourceTable.rpmsg_vdev);

    pru::rpmsg::channel rpmsg(&resourceTable.rpmsg_vring0, &resourceTable.rpmsg_vring1,
                              TO_ARM_HOST, FROM_ARM_HOST,
                              CHAN_NAME, CHAN_DESC, CHAN_PORT);

    int i = 0;
    while (1) {
        /* Check bit 31 of register R31 to see if the ARM has kicked us */
        if (pru::read_reg<pru::r31>() & PRU0_R31_FROM_HOST_INT) {
            /* Clear the event status */
            CT_INTC.SICR_bit.STS_CLR_IDX = FROM_ARM_HOST;
            /* Receive all available messages, multiple messages can be sent per kick */
            while (PRU_RPMSG_SUCCESS == rpmsg.receive(&src, &dst, payload, &len)) {
                __delay_ms(1000);
                /* Echo the message back to the same address from which we just received */
                i++;
                payload[0] = i * 5;
                rpmsg.send(dst, src, payload, 1);
            }
        }
    }

    __halt();

    return 0;
}
