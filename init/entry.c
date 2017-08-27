#include "types.h"
#include "console.h"
#include "debug.h"
#include "pmm.h"
#include "idt.h"
#include "timer.h"
#include "keyboard.h"

int kern_entry() {

	init_gdt();
    console_clear();
    printk("Hello, OS kernel!\n");
    /**
    printk("kernel in memory start: 0x%x\n", kern_start);
    printk("kernel in memory end: 0x%x\n", kern_end);
    
    //printk("test: 0x%x\n", 179688);
    show_memory_map();
    
    init_pmm();
    printk("\nThe Count of Physical Memory Page is: %d\n\n", phy_page_count);
    printk("allocte physical addr: 0x%x\n", pmm_allo_page());
    printk("allocte physical addr: 0x%x\n", pmm_allo_page());
    printk("allocte physical addr: 0x%x\n", pmm_allo_page());
   
    
    init_timer(200);
     **/
    init_idt();
    init_kb();
    asm volatile ("sti");
    return 0;
}
