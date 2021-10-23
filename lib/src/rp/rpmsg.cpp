#include "rp/rpmsg.h"

/*
 * Used to make sure the Linux drivers are ready for RPMsg communication
 * Found at linux-x.y.z/include/uapi/linux/virtio_config.h
 */
#define VIRTIO_CONFIG_S_DRIVER_OK	4

namespace pru {
namespace rpmsg {

channel::channel(fw_rsc_vdev_vring* vring0, fw_rsc_vdev_vring* vring1,
        uint32_t to_arm_event, uint32_t from_arm_event,
        char* name, char* desc, int32_t port) {
    pru_rpmsg_init(&m_transport, vring0, vring1,
                   to_arm_event, from_arm_event);

    while (pru_rpmsg_channel(RPMSG_NS_CREATE,
                             &m_transport,
                             name, desc, port) != PRU_RPMSG_SUCCESS);
}

int16_t channel::receive(uint16_t* src, uint16_t* dst, void* data, uint16_t* len) {
    return pru_rpmsg_receive(&m_transport, src, dst, data, len);
}

int16_t channel::send(uint32_t src, uint32_t dst, void* data, uint16_t len) {
    return pru_rpmsg_send(&m_transport, src, dst, data, len);
}

void wait_until_ready(fw_rsc_vdev& vdev) {
    volatile uint8_t *status = &vdev.status;
    while (!(*status & VIRTIO_CONFIG_S_DRIVER_OK));
}

}
}
