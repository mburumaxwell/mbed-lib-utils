#include "Guid.h"

Guid::Guid()
{
    memset(data, 0, sizeof(data));
}

Guid::Guid(uint32_t a, uint16_t b, uint16_t c, uint16_t d, uint8_t e1, uint8_t e2, uint8_t e3, uint8_t e4, uint8_t e5, uint8_t e6)
{
    uint16_t bcd[3] = { b, c, d};
    uint8_t e16[6] = { e1, e2, e3, e4, e5, e6 };
    memcpy(data + 00,  &a, 4);
    memcpy(data + 04, bcd, 6);
    memcpy(data + 10, e16, 6);
}

Guid::Guid(int32_t a, int16_t b, int16_t c, int16_t d, int8_t e1, int8_t e2, int8_t e3, int8_t e4, int8_t e5, int8_t e6)
{
    int16_t bcd[3] = { b, c, d};
    int8_t e16[6] = { e1, e2, e3, e4, e5, e6 };
    memcpy(data + 00,  &a, 4);
    memcpy(data + 04, bcd, 6);
    memcpy(data + 10, e16, 6);
}

Guid::Guid(uint8_t *arr)
{
    memcpy(data, arr, sizeof(data));        
}

void Guid::to_string(char *dest, const size_t dlen, size_t *wlen)
{
    uint8_t *b = data;
    *wlen = snprintf(dest, dlen, GUID_STRING_FORMAT,
                                    *((uint32_t *)(b + 0)),
                                    *((uint16_t *)(b + 4)),
                                    *((uint16_t *)(b + 6)),
                                    *((uint16_t *)(b + 8)),
                                    *((uint8_t  *)(b + 10)),
                                    *((uint8_t  *)(b + 11)),
                                    *((uint8_t  *)(b + 12)),
                                    *((uint8_t  *)(b + 13)),
                                    *((uint8_t  *)(b + 14)),
                                    *((uint8_t  *)(b + 15)));
}

void Guid::to_string(char *dest, const size_t dlen)
{
    size_t wlen = 0;
    to_string(dest, dlen, &wlen);
}

void Guid::to_bytes(void *dest, const size_t dlen, size_t *wlen)
{
    *wlen = sizeof(data);
    if (dlen < *wlen) return;
    memcpy(dest, data, sizeof(data));
}

void Guid::randomize()
{
    uint32_t *data_s32 = (uint32_t *)data;
    const size_t s32 = sizeof(data) / sizeof(uint32_t);
    for (size_t i = 0; i < s32; i++)
    {
        data_s32[i] = (uint32_t)rand();
    }
}

Guid* Guid::make()
{
    Guid *g = new Guid();
    g->randomize();
    return g;
}