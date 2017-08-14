#include "types.h"
#include "console.h"
#include "debug.h"
#include "pmm.h"

int kern_entry()
{
	init_gdt();
    console_clear();
    printk("Hello, OS kernel!\n");
    
    printk("kernel in memory start: 0x%x\n", kern_start);
    printk("kernel in memory end: 0x%x\n", kern_end);
    
    //printk("test: 0x%x\n", 179688);
    show_memory_map();
    
    return 0;
}
