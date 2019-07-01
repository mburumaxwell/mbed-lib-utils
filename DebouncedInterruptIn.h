#ifndef __DEBOUNCED_INTERRUPT_IN_H
#define __DEBOUNCED_INTERRUPT_IN_H

#include "mbed.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef DEBOUNCED_INTERRUPT_IN_DEBOUNCE_MS
#define DEBOUNCED_INTERRUPT_IN_DEBOUNCE_MS 50
#endif

#ifdef __cplusplus
}
#endif

class DebouncedInterruptIn {
public:
    DebouncedInterruptIn(PinName pin, int debounce_ms = DEBOUNCED_INTERRUPT_IN_DEBOUNCE_MS);
    DebouncedInterruptIn(PinName pin, PinMode mode, int debounce_ms = DEBOUNCED_INTERRUPT_IN_DEBOUNCE_MS);

    int read();
    operator int();

    void rise(Callback<void()> func);
    void fall(Callback<void()> func);
    void mode(PinMode mode);
    void enable_irq();
    void disable_irq();

protected:
    InterruptIn _iin;
    Timer _timer;
    int debounce_cycles;

    Callback<void()> _rise;
    Callback<void()> _fall;

    void _inner_rise(void);
    void _inner_fall(void);
    void _inner_irq(int expected, Callback<void()> c);
};

#endif /* __DEBOUNCED_INTERRUPT_IN_H */
