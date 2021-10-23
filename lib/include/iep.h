#pragma once


namespace pru {
namespace iep {

void enable_counter(unsigned increment_value=1);
void set_counter(unsigned value);
unsigned read_counter();
void set_counter_overflow_enabled(bool enabled);
void set_counter_compensation(unsigned value, unsigned count);

}
}
