#ifndef __COUNTER_H
#define __COUNTER_H

#include "mbed.h"

class Counter {
public:
    Counter(int limit) { set(0, limit); }

    void attach(Callback<void()> c) { this->c = c; }

    void set(int current, int limit)
    {
        current %= limit;
        if (limit <= current) limit = current + 1; // ensure we can increment by one

        this->limit = limit;
        this->current = current;
    }

    void set(int current) { set(current, this->limit); }
    
    void reset() { set(0); }

    void count()
    {
        current++;
        if (current >= limit && c) c();
    }

private:
    int limit, current;
    Callback<void()> c;

};

#endif /* __COUNTER_H */
