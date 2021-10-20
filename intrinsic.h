#pragma once

#define PRAGMA(X) _Pragma(#X)
#define ASM(X) __asm(X)

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
