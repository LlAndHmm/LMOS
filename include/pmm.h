#ifndef INCLUDE_PMM_H
#define INCLUDE_PMM_H

#include "multiboot.h"

extern uint8_t kern_start[];
extern uint8_t kern_end[];

//输出BIOS提供的物理内存布局
void show_memory_map();

#endif	//INCLUDE_PMM_H
