#include "keyboard.h"
#include "debug.h"
#include "idt.h"
#include "types.h"
#include "common.h"


void kb_callback(pt_regs *regs) {
	uint8_t data;
	outb(0xA0,0x61);	//inform PIC "IRQ1 have done"
	data = inb(0x60);
	printk("%x\n", data);
	/**
	for (;;) {
		asm volatile("hlt");
	}
	**/
}

void init_kb() {
	register_interrupt_handler(IRQ1, kb_callback);
}
