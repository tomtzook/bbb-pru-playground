#pragma once

#include "prudefs.h"


#define GPIO(base, mask) pru::gpio::gpio_pin_t<pru::gpio::base, mask>
#define DEFINE_GPIO(base, mask, name) typedef GPIO(module, mask) name;

namespace pru {
namespace gpio {

enum gpio_dir_t {
    dir_out,
    dir_in
};

template<unsigned module>
struct gpio_module_t {
    inline static gpio_dir_t direction(unsigned mask) {
        return (*((unsigned int volatile*) (module + GPIO_OE)) & mask) ?
               dir_in :
               dir_out;
    }

    inline static void set_direction(unsigned mask, gpio_dir_t direction) {
        switch (direction) {
            case dir_out:
                *((unsigned int volatile*) (module + GPIO_OE)) &= ~mask;
                break;
            case dir_in:
                *((unsigned int volatile*) (module + GPIO_OE)) |= mask;
                break;
        }
    }

    inline static void set(unsigned mask) {
        *((unsigned int volatile*) (module + GPIO_SETDATAOUT)) |= mask;
    }

    inline static void clear(unsigned mask) {
        *((unsigned int volatile*) (module + GPIO_CLEARDATAOUT)) |= mask;
    }

    inline static bool read(unsigned mask) {
        if (dir_in == direction(mask)) {
            return (*((unsigned int volatile*) (module + GPIO_DATAIN)) & mask) != 0;
        } else {
            return (*((unsigned int volatile*) (module + GPIO_DATAOUT)) & mask) != 0;
        }
    }
};

template<typename gpio_module, unsigned mask>
struct gpio_pin_t {
    inline static gpio_dir_t direction() {
        return gpio_module::direction(mask);
    }

    inline static void set_direction(gpio_dir_t direction) {
        gpio_module::set_direction(mask, direction);
    }

    inline static void set() {
        gpio_module::set(mask);
    }

    inline static void clear() {
        gpio_module::clear(mask);
    }

    inline static bool read() {
        return gpio_module::read(mask);
    }
};

// GPIO0
typedef gpio_module_t<GPIO0> gpio0;


// GPIO1
typedef gpio_module_t<GPIO1> gpio1;

typedef gpio_pin_t<gpio1, USR0> usr0;
typedef gpio_pin_t<gpio1, USR1> usr1;
typedef gpio_pin_t<gpio1, USR2> usr2;
typedef gpio_pin_t<gpio1, USR3> usr3;

// GPIO2
typedef gpio_module_t<GPIO2> gpio2;


// GPIO3
typedef gpio_module_t<GPIO3> gpio3;

}
}
