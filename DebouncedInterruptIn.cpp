#include "DebouncedInterruptIn.h"

DebouncedInterruptIn::DebouncedInterruptIn(PinName pin, int debounce_ms) :
    _iin(pin),
    _rise(NULL),
    _fall(NULL)
{
    // calculate debounce_cycles from SystemCoreClock (cycles per second or cycles per 1000ms)
    this->debounce_cycles = (SystemCoreClock * debounce_ms) / 1000;
}

DebouncedInterruptIn::DebouncedInterruptIn(PinName pin, PinMode mode, int debounce_ms) :
    _iin(pin, mode),
    _rise(NULL),
    _fall(NULL)
{
    // calculate debounce_cycles from SystemCoreClock (cycles per second or cycles per 1000ms)
    this->debounce_cycles = (SystemCoreClock * debounce_ms) / 1000;
}

int DebouncedInterruptIn::read() { return _iin.read(); }
DebouncedInterruptIn::operator int() { return _iin; }

void DebouncedInterruptIn::rise(Callback<void()> func)
{
    // enable inner rise if only the function is provided
    if (func)
    {
        _rise = func;
        _iin.rise(callback(this, &DebouncedInterruptIn::_inner_rise));
    }
    else
    {
        _rise = NULL;
        _iin.rise(NULL);
    }
}

void DebouncedInterruptIn::fall(Callback<void()> func)
{
    // enable inner fall if only the function is provided
    if (func)
    {
        _fall = func;
        _iin.fall(callback(this, &DebouncedInterruptIn::_inner_fall));
    }
    else
    {
        _fall = NULL;
        _iin.fall(NULL);
    }
}

void DebouncedInterruptIn::mode(PinMode mode) { _iin.mode(mode); }
void DebouncedInterruptIn::enable_irq() { _iin.enable_irq(); }
void DebouncedInterruptIn::disable_irq() { _iin.disable_irq(); }

void DebouncedInterruptIn::_inner_irq(int expected, Callback<void()> c)
{
    // wait for the debounce period
    int i = debounce_cycles;
    while (i--) __NOP();

    // if the pin is in the expected state and the callback is not null then invoke the callback
    if (_iin.read() == expected && c) 
    {
        c();
    }
}

void DebouncedInterruptIn::_inner_rise(void) { _inner_irq(1, _rise); }
void DebouncedInterruptIn::_inner_fall(void) { _inner_irq(0, _fall); }
