#ifndef __COUNTER_TO_RESET_H
#define __COUNTER_TO_RESET_H

#include "Counter.h"

class CounterToReset : public Counter {
public:
    CounterToReset(int limit, int reset_delay_ms = 3000) : Counter::Counter(limit)
    {
        this->reset_delay_ms = reset_delay_ms;
        attach(callback(this, &CounterToReset::do_reset));
    }

private:
    int reset_delay_ms;
    void do_reset(void)
    {
        wait_ms(reset_delay_ms);
        NVIC_SystemReset();
    }
};

#endif /* __COUNTER_TO_RESET_H */
