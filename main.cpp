extern "C" {
#include <stdint.h>
#include <pru_cfg.h>
#include <pru_intc.h>
#include <rsc_types.h>
#include <pru_rpmsg.h>
}

#include "intrinsic.h"
#include "prudefs.h"
//#include "resource_table_empty.h"
#include "resource_table_0.h"
#include "rpmsg.h"

#include "prugpiocxx.h"
#include "pruegpiocxx.h"

#define PRU0_ARM_INTERRUPT 19


//DEFINE_GPIO(gpio1, P8_11, led);
/*typedef pru::egpio::pru0_pru_r30_15 led;


template<typename TRIG, typename ECHO>
struct ultrasonic_t {
    static void init() {
        TRIG::set_direction(pru::gpio::DIRECTION_OUTPUT);
        ECHO::set_direction(pru::gpio::DIRECTION_INPUT);
    }

    static void pulse() {
        TRIG::set();
        __delay_us(10);
        TRIG::clear();
    }

    static unsigned int wait_echo() {
        unsigned int count = 0;
        while (!ECHO::read()) {
            count++;
        }

        return count;
    }
};
typedef ultrasonic_t<GPIO(gpio1, P8_11), GPIO(gpio1, P8_12)> sonic;

typedef GPIO(gpio1, P8_11) input;*/

/* Host-0 Interrupt sets bit 30 in register R31 */
#define HOST_INT			((uint32_t) 1 << 30)

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

    //struct pru_rpmsg_transport transport;
    volatile uint8_t *status;
    uint16_t src, dst, len;

    /* Allow OCP master port access by the PRU so the PRU can read external memories */
    CT_CFG.SYSCFG_bit.STANDBY_INIT = 0;

    /* Clear the status of the PRU-ICSS system event that the ARM will use to 'kick' us */
    CT_INTC.SICR_bit.STS_CLR_IDX = FROM_ARM_HOST;

    /* Make sure the Linux drivers are ready for RPMsg communication */
    status = &resourceTable.rpmsg_vdev.status;
    while (!(*status & VIRTIO_CONFIG_S_DRIVER_OK));

    pru::rpmsg::channel rpmsg(&resourceTable.rpmsg_vring0, &resourceTable.rpmsg_vring1,
                              TO_ARM_HOST, FROM_ARM_HOST,
                              CHAN_NAME, CHAN_DESC, CHAN_PORT);

    /* Initialize the RPMsg transport structure */
    //pru_rpmsg_init(&transport, &resourceTable.rpmsg_vring0, &resourceTable.rpmsg_vring1, TO_ARM_HOST, FROM_ARM_HOST);


    int i = 0;
    /* Create the RPMsg channel between the PRU and ARM user space using the transport structure. */
    //while (pru_rpmsg_channel(RPMSG_NS_CREATE, &transport, CHAN_NAME, CHAN_DESC, CHAN_PORT) != PRU_RPMSG_SUCCESS);
    while (1) {
        /* Check bit 31 of register R31 to see if the ARM has kicked us */
        if (__R31 & HOST_INT) {
            /* Clear the event status */
            CT_INTC.SICR_bit.STS_CLR_IDX = FROM_ARM_HOST;
            /* Receive all available messages, multiple messages can be sent per kick */
            while (PRU_RPMSG_SUCCESS == rpmsg.receive(&src, &dst, payload, &len)) {
                __delay_ms(1000);
                /* Echo the message back to the same address from which we just received */
                i++;
                payload[0] = i * i;
                rpmsg.send(dst, src, payload, 1);
            }
        }
    }


    //for(i = 0; i < 10; i++) {
        /*pru::gpio::usr0::set();
        __delay_ms(100);
        pru::gpio::usr1::set();
        __delay_ms(100);
        pru::gpio::usr2::set();
        __delay_ms(100);
        pru::gpio::usr3::set();

        __delay_ms(500);

        pru::gpio::usr0::clear();
        pru::gpio::usr1::clear();
        pru::gpio::usr2::clear();
        pru::gpio::usr3::clear();

        __delay_ms(100);*/

        //shared[0] = i*i*i;
        //__delay_ms(500);
    //}

    //__R31 = 35;
    __halt();

    /*shared[0] = 0;

    for(i = 0; i < 10; i++) {
        shared[0] = i;
        __delay_ms(500);
    }*/

    /*input::set_direction(pru::gpio::DIRECTION_INPUT);
while (true) {
    bool value = input::read();
    shared[0] = value ? 1 : 0;

    __delay_ms(100);
}*/

    //__asm("mov r31.b0, 35 \n\r");

    /*__asm__ __volatile__
    (
    " MOV r31.b0, 35 \n"
    " CLR r0, r0, 4 \n"
    " SBCO &r0, C4, 4, 4 \n"
    );*/

    /*sonic::init();

    while (true) {
        sonic::pulse();
        unsigned int count = sonic::wait_echo();
        shared[0] = count;
        __delay_ms(20);
    }*/


    //led::set_direction(pru::gpio::DIRECTION_OUTPUT);
    /*led::clear();

    for (i = 0; i < 10; i++) {
        led::set();
        __delay_ms(500);
        led::clear();
        __delay_ms(500);
    }*/

    return 0;
}
