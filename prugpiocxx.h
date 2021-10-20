#pragma once

#include "prudefs.h"


#define GPIO(base, mask) pru::gpio::gpio_pin_t<pru::gpio::base, mask>
#define DEFINE_GPIO(base, mask, name) typedef GPIO(base, mask) name;

namespace pru {
namespace gpio {

enum gpio_dir_t {
    DIRECTION_OUTPUT,
    DIRECTION_INPUT
};

template<unsigned BASE>
struct gpio_base_t {
    inline static gpio_dir_t direction(unsigned mask) {
        return (*((unsigned int volatile*) (BASE + GPIO_OE)) & mask) ?
               DIRECTION_INPUT :
               DIRECTION_OUTPUT;
    }

    inline static void set_direction(unsigned mask, gpio_dir_t direction) {
        switch (direction) {
            case DIRECTION_OUTPUT:
                *((unsigned int volatile*) (BASE + GPIO_OE)) &= ~mask;
                break;
            case DIRECTION_INPUT:
                *((unsigned int volatile*) (BASE + GPIO_OE)) |= mask;
                break;
        }
    }

    inline static void set(unsigned mask) {
        *((unsigned int volatile*) (BASE + GPIO_SETDATAOUT)) |= mask;
    }

    inline static void clear(unsigned mask) {
        *((unsigned int volatile*) (BASE + GPIO_CLEARDATAOUT)) |= mask;
    }

    inline static bool read(unsigned mask) {
        if (DIRECTION_INPUT == direction(mask)) {
            return (*((unsigned int volatile*) (BASE + GPIO_DATAIN)) & mask) != 0;
        } else {
            return (*((unsigned int volatile*) (BASE + GPIO_DATAOUT)) & mask) != 0;
        }
    }
};

template<typename GPIO_BASE, unsigned MASK>
struct gpio_pin_t {
    inline static gpio_dir_t direction() {
        return GPIO_BASE::direction(MASK);
    }

    inline static void set_direction(gpio_dir_t direction) {
        GPIO_BASE::set_direction(MASK, direction);
    }

    inline static void set() {
        GPIO_BASE::set(MASK);
    }

    inline static void clear() {
        GPIO_BASE::clear(MASK);
    }

    inline static bool read() {
        return GPIO_BASE::read(MASK);
    }
};

// GPIO0
typedef gpio_base_t<GPIO0> gpio0;


// GPIO1
typedef gpio_base_t<GPIO1> gpio1;

typedef gpio_pin_t<gpio1, USR0> usr0;
typedef gpio_pin_t<gpio1, USR1> usr1;
typedef gpio_pin_t<gpio1, USR2> usr2;
typedef gpio_pin_t<gpio1, USR3> usr3;

// GPIO2
typedef gpio_base_t<GPIO2> gpio2;


// GPIO3
typedef gpio_base_t<GPIO3> gpio3;

}
}
