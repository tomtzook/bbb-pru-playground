#pragma once


namespace pru {
namespace iep {

void enable_counter(unsigned increment_value=1);
void set_counter(unsigned value);
unsigned int read_counter();
void set_counter_overflow_enabled(bool enabled);
void set_counter_compensation(unsigned value, unsigned count);

void enable_event(unsigned event_id, unsigned int compare_value);
void disable_event(unsigned event_id);
void set_event0_reset_enabled(bool enabled);
bool is_event_hit(unsigned event_id, bool clear=false);
void clear_event(unsigned event_id);

}
}
