#pragma once

#include "prudefs.h"

namespace pru {
namespace gpio {

template<unsigned BASE>
struct gpio_base_t {
    inline static void set(unsigned bits) {
        *((unsigned int volatile*) (BASE + GPIO_SETDATAOUT)) |= bits;
    }
    inline static void clear(unsigned bits) {
        *((unsigned int volatile*) (BASE + GPIO_CLEARDATAOUT)) |= bits;
    }
};

template<typename GPIO_BASE, unsigned BIT>
struct gpio_pin_t {
    inline static void set() {
        GPIO_BASE::set(BIT);
    }
    inline static void clear() {
        GPIO_BASE::clear(BIT);
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
