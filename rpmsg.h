#pragma once

extern "C" {
#include <pru_rpmsg.h>
}


namespace pru {
namespace rpmsg {

class channel {
public:
    channel(fw_rsc_vdev_vring* vring0, fw_rsc_vdev_vring* vring1,
            uint32_t to_arm_event, uint32_t from_arm_event,
            char* name, char* desc, int32_t port);

    int16_t receive(uint16_t* src, uint16_t* dst, void* data, uint16_t* len);
    int16_t send(uint32_t src, uint32_t dst, void* data, uint16_t len);

private:
    pru_rpmsg_transport m_transport;
};

}
}
