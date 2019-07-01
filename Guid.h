#ifndef __GUID_H
#define __GUID_H

#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

#define GUID_STRING_FORMAT  "%08lx-%04x-%04x-%04x-%02x%02x%02x%02x%02x%02x"
#define GUID_STRING_LENGTH  (36)
#define GUID_BYTES_LENGTH   (16)

#ifdef __cplusplus
}
#endif

class Guid {
public:
    Guid();
    Guid(uint32_t a, uint16_t b, uint16_t c, uint16_t d, uint8_t e1, uint8_t e2, uint8_t e3, uint8_t e4, uint8_t e5, uint8_t e6);
    Guid(int32_t a, int16_t b, int16_t c, int16_t d, int8_t e1, int8_t e2, int8_t e3, int8_t e4, int8_t e5, int8_t e6);
    Guid(uint8_t *arr);

    void to_string(char *dest, const size_t dlen, size_t *wlen);
    void to_string(char *dest, const size_t dlen);
    void to_bytes(void *dest, const size_t dlen, size_t *wlen);
    void randomize();

    static Guid* make();

private:
    uint8_t data[GUID_BYTES_LENGTH];
};


#endif /* __GUID_H */