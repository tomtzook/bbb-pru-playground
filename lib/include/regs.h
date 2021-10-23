#pragma once

#include <inttypes.h>


namespace pru {

typedef unsigned int regval_t;

enum reg_t {
    r30,
    r31
};

template<reg_t reg>
void write_reg(regval_t value);

template<reg_t reg>
regval_t read_reg();


template<>
void write_reg<r30>(regval_t value);
template<>
regval_t read_reg<r30>();

template<>
void write_reg<r31>(regval_t value);
template<>
regval_t read_reg<r31>();

}
