#pragma once

#include "prudefs.h"
#include "regs.h"


namespace pru {
namespace egpio {

template<reg_t reg, unsigned mask>
struct egpio_out_pin_t {
    inline static void set() {
        auto value = read_reg<reg>();
        value |= mask;
        write_reg<reg>(value);
    }
    inline static void clear() {
        auto value = read_reg<reg>();
        value &= ~mask;
        write_reg<reg>(value);
    }
};

template<reg_t reg, unsigned mask>
struct egpio_in_pin_t {
    inline static bool read() {
        auto value = read_reg<reg>();
        return (value & mask) != 0;
    }
};

template<unsigned mask>
struct r30_pin_t {
    inline static void set() {
        egpio_out_pin_t<r30, mask>::set();
    }
    inline static void clear() {
        egpio_out_pin_t<r30, mask>::clear();
    }
};
template<unsigned mask>
struct r31_pin_t {
    inline static bool read() {
        return egpio_in_pin_t<r31, mask>::read();
    }
};


typedef r30_pin_t<PRU0_R30_P9_31> pru0_pru_r30_0; // mode5
typedef r30_pin_t<PRU0_R30_P9_29> pru0_pru_r30_1; // mode5
typedef r30_pin_t<PRU0_R30_P9_30> pru0_pru_r30_2; // mode5
typedef r30_pin_t<PRU0_R30_P9_28> pru0_pru_r30_3; // mode5
typedef r30_pin_t<PRU0_R30_P9_42B> pru0_pru_r30_4; // mode5
typedef r30_pin_t<PRU0_R30_P9_27> pru0_pru_r30_5; // mode5
typedef r30_pin_t<PRU0_R30_P9_41B> pru0_pru_r30_6; // mode5
typedef r30_pin_t<PRU0_R30_P9_25> pru0_pru_r30_7; // mode5
typedef r30_pin_t<PRU0_R30_P8_12> pru0_pru_r30_14; // mode6
typedef r30_pin_t<PRU0_R30_P8_11> pru0_pru_r30_15; // mode6

typedef r30_pin_t<PRU1_R30_P8_45> pru1_pru_r30_0; // mode5
typedef r30_pin_t<PRU1_R30_P8_46> pru1_pru_r30_1; // mode5
typedef r30_pin_t<PRU1_R30_P8_43> pru1_pru_r30_2; // mode5
typedef r30_pin_t<PRU1_R30_P8_44> pru1_pru_r30_3; // mode5
typedef r30_pin_t<PRU1_R30_P8_41> pru1_pru_r30_4; // mode5
typedef r30_pin_t<PRU1_R30_P8_42> pru1_pru_r30_5; // mode5
typedef r30_pin_t<PRU1_R30_P8_39> pru1_pru_r30_6; // mode5
typedef r30_pin_t<PRU1_R30_P8_40> pru1_pru_r30_7; // mode5
typedef r30_pin_t<PRU1_R30_P8_27> pru1_pru_r30_8; // mode5
typedef r30_pin_t<PRU1_R30_P8_29> pru1_pru_r30_9; // mode5
typedef r30_pin_t<PRU1_R30_P8_28> pru1_pru_r30_10; // mode5
typedef r30_pin_t<PRU1_R30_P8_30> pru1_pru_r30_11; // mode5
typedef r30_pin_t<PRU1_R30_P8_21> pru1_pru_r30_12; // mode5
typedef r30_pin_t<PRU1_R30_P8_20> pru1_pru_r30_13; // mode5

typedef r31_pin_t<PRU0_R31_P9_31> pru0_pru_r31_0; // mode6
typedef r31_pin_t<PRU0_R31_P9_29> pru0_pru_r31_1; // mode6
typedef r31_pin_t<PRU0_R31_P9_30> pru0_pru_r31_2; // mode6
typedef r31_pin_t<PRU0_R31_P9_28> pru0_pru_r31_3; // mode6
typedef r31_pin_t<PRU0_R31_P9_42B> pru0_pru_r31_4; // mode6
typedef r31_pin_t<PRU0_R31_P9_27> pru0_pru_r31_5; // mode6
typedef r31_pin_t<PRU0_R31_P9_41B> pru0_pru_r31_6; // mode6
typedef r31_pin_t<PRU0_R31_P9_25> pru0_pru_r31_7; // mode6

typedef r31_pin_t<PRU0_R31_P8_16> pru0_pru_r31_14; // mode6
typedef r31_pin_t<PRU0_R31_P8_15> pru0_pru_r31_15; // mode6
typedef r31_pin_t<PRU0_R31_P9_24> pru0_pru_r31_16; // mode6
//typedef r31_pin_t<PRU0_R31_P9_41A> pru0_pru_r31_16; // mode5

typedef r31_pin_t<PRU1_R31_P8_45> pru1_pru_r31_0; // mode6
typedef r31_pin_t<PRU1_R31_P8_46> pru1_pru_r31_1; // mode6
typedef r31_pin_t<PRU1_R31_P8_43> pru1_pru_r31_2; // mode6
typedef r31_pin_t<PRU1_R31_P8_44> pru1_pru_r31_3; // mode6
typedef r31_pin_t<PRU1_R31_P8_41> pru1_pru_r31_4; // mode6
typedef r31_pin_t<PRU1_R31_P8_42> pru1_pru_r31_5; // mode6
typedef r31_pin_t<PRU1_R31_P8_39> pru1_pru_r31_6; // mode6
typedef r31_pin_t<PRU1_R31_P8_40> pru1_pru_r31_7; // mode6
typedef r31_pin_t<PRU1_R31_P8_27> pru1_pru_r31_8; // mode6
typedef r31_pin_t<PRU1_R31_P8_29> pru1_pru_r31_9; // mode6
typedef r31_pin_t<PRU1_R31_P8_28> pru1_pru_r31_10; // mode6
typedef r31_pin_t<PRU1_R31_P8_30> pru1_pru_r31_11; // mode6
typedef r31_pin_t<PRU1_R31_P8_21> pru1_pru_r31_12; // mode6
typedef r31_pin_t<PRU1_R31_P8_20> pru1_pru_r31_13; // mode6
typedef r31_pin_t<PRU1_R31_P9_26> pru1_pru_r31_16; // mode6

}
}
