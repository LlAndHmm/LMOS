#include "multiboot.h"
#include "pmm.h"
#include "debug.h"

//物理内存页面管理的栈
static uint32_t pmm_stack[PAGE_MAX_SIZE + 1];

// 物理内存管理的栈指针
static uint32_t pmm_stack_top = -1;

// 物理内存页的数量
uint32_t phy_page_count;



void show_memory_map() {
	uint32_t mmap_addr = glb_mboot_ptr->mmap_addr;
	uint32_t mmap_length = glb_mboot_ptr->mmap_length;
	
	printk("Memory map:\n");
	//printk("%x\n", mmap_length);
	mmap_entry_t *mmap = (mmap_entry_t *)mmap_addr;
	
	for (; (uint32_t)mmap < mmap_addr + mmap_length; mmap++) {
		printk("base_addr = %x %x, length = %x %x, type = %x\n", 
			(uint32_t)mmap->base_addr_high, (uint32_t)mmap->base_addr_low,
            (uint32_t)mmap->length_high, (uint32_t)mmap->length_low,
            (uint32_t)mmap->type);
	}
}

void init_pmm() {
	mmap_entry_t* mmap_start_addr = (mmap_entry_t *)glb_mboot_ptr->mmap_addr;
	mmap_entry_t* mmap_end_addr = (mmap_entry_t *)glb_mboot_ptr->mmap_addr + glb_mboot_ptr->mmap_length;
	
	mmap_entry_t* map_entry;
	for (map_entry = mmap_start_addr; map_entry < mmap_end_addr; map_entry++) {
	
		if (map_entry->type == 1 && map_entry->base_addr_low == 0x100000) {
			uint32_t page_addr = map_entry->base_addr_low + (uint32_t)(kern_end - kern_start);
			//printk("%x\n", page_addr);
			uint32_t length = map_entry->base_addr_low + map_entry->length_low;
			
			while (page_addr < length && page_addr <= PMM_MAX_SIZE) {
				pmm_free_page(page_addr);
				page_addr += PMM_PAGE_SIZE;
				phy_page_count++;
			}
		}
	}
}

void pmm_free_page(uint32_t p) {

	if (pmm_stack_top != PAGE_MAX_SIZE) {
		pmm_stack[++pmm_stack_top] = p;
	} else {
		printk("out of pmm_stack stack");
	}	
}

uint32_t pmm_allo_page() {
	uint32_t page;
	
	if (pmm_stack_top >= 0) {
		page = pmm_stack[pmm_stack_top--];
	} else {
		printk("out of momery");
	}
	
	return page;
}












