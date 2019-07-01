#include "hexdump.h"

void hex_dump(FILE* f, void *addr, int len)
{
    int i;
    unsigned char buff[17];
    unsigned char *pc = (unsigned char*)addr;

    if (len == 0 || len < 0) return;

    // Process every byte in the data.
    for (i = 0; i < len; i++)
    {
        // Multiple of 16 means new line (with line offset).

        if ((i % 16) == 0)
        {
            // Just don't print ASCII for the zeroth line.
            if (i != 0) fprintf(f, "  %s\n", buff);

            // Output the offset.
            fprintf(f, "  %04x: ", i);
        }

        // Now the hex code for the specific character.
        fprintf(f, " %02x", pc[i]);

        // And store a printable ASCII character for later.
        if ((pc[i] < 0x20) || (pc[i] > 0x7e)) buff[i % 16] = '.';
        else buff[i % 16] = pc[i];
        buff[(i % 16) + 1] = '\0';
    }

    // Pad out last line if not exactly 16 characters.
    while ((i % 16) != 0)
    {
        fprintf(f, "   ");
        i++;
    }

    // And print the final ASCII bit.
    fprintf(f, "  %s\n", buff);
}
