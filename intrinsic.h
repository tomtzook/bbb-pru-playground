#pragma once

#define CYCLES_PER_SECOND 200000000 /* PRU has 200 MHz clock */

#define PRAGMA(X) _Pragma(#X)
#define ASM(X) __asm(X)

// some bit manipulation

#define CHECK_BIT(var, bit) ((var >> bit) & 1U)
#define SET_BIT(var, bit) (var |= (1U << bit))
#define CLEAR_BIT(var, bit) (var &= ~(1U << bit))
#define TOGGLE_BIT(var, bit) (var ^= (1U << bit))

// PRU compiler intrinsics

inline void __xin(unsigned int device_id,
           unsigned int base_register,
           unsigned int use_remapping,
           unsigned& object);

inline void __xout(unsigned int device_id,
           unsigned int base_register,
           unsigned int use_remapping,
           unsigned& object);

inline void __sxin(unsigned int device_id,
            unsigned int base_register,
            unsigned int use_remapping,
            unsigned& object);

inline void __sxout(unsigned int device_id,
            unsigned int base_register,
            unsigned int use_remapping,
            unsigned& object);

inline void __sxchg(unsigned int device_id,
            unsigned int base_register,
            unsigned int use_remapping,
            unsigned& object);

inline unsigned int __lmbd(unsigned int src,
                    unsigned int pattern);

inline void __halt();

inline void __delay_cycles(unsigned int cycles);
