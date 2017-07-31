#include "types.h"
#include "console.h"

int kern_entry()
{
    console_clear();
    console_putc_color('A', black, green);
    console_putc_color('\n', black, green);
    console_putc_color('B', black, green);
    console_putc_color('\n', black, green);
    console_write_dec(1234, black, red);
    return 0;
}
