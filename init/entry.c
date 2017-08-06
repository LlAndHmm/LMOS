#include "types.h"
#include "console.h"
#include "debug.h"

int kern_entry()
{
    console_clear();
    printk("A");
    printk("\n");
    printk("%d", 52432);
    printk("\n");
    char c = 'c';
	char l = 'l';
    int value = 5;
    printk("%c 's value is %d, and my name is %c", c, value, l);
    return 0;
}
