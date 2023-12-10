#include <stdint.h>
#include "stdio.h"
#include "memory.h"
#include <hal/hal.h>
#include <debug.h>
#include<multiboot.h>
void kernel_main(multiboot_info_t* mbd, uint32_t magic)
{
    HAL_Initialize();
    printf("HAL Initialised \n");
    printf("Hello World!\n");
    log_info("Main","\nKernel start: 0x Kernel End:  ");
    if(magic != MULTIBOOT_BOOTLOADER_MAGIC) {
        printf("invalid magic number!\n");
        goto end;
    }
    else{
        printf("Healthy Magic number\n");
        if(!(mbd->flags >> 6 & 0x1)) {
        printf("invalid memory map given by GRUB bootloader");
        goto end;
    }
    else{
        printf("Healthy Memorymap!\n");
    }
    }
    printf("Hello: %d, %d, %d, %d \n",1,2,3,4);
 
    /* Loop through the memory map and display the values */
    int i;
    for(i = 0; i < mbd->mmap_length; 
        i += sizeof(multiboot_memory_map_t)) 
    {
        multiboot_memory_map_t* mmmt = 
            (multiboot_memory_map_t*) (mbd->mmap_addr + i);
        uint32_t len=mmmt->len_low;
        uint32_t type=mmmt->type;
        uint32_t size=mmmt->size;
        uint32_t start_addr=mmmt->addr_low;
        printf("Start Addr: %x | Length: %x | Size: %x | Type: %d\n",
            start_addr, len, size, type);
       
    }
    printf("\n\n");
    for(i = 0; i < mbd->mmap_length; 
        i += sizeof(multiboot_memory_map_t)) 
    {
    multiboot_memory_map_t* mmmt = 
            (multiboot_memory_map_t*) (mbd->mmap_addr + i);
        if(mmmt->type == MULTIBOOT_MEMORY_AVAILABLE) {
            /* 
             * Do something with this memory block!
             * BE WARNED that some of memory shown as availiable is actually 
             * actively being used by the kernel! You'll need to take that
             * into account before writing to memory!
             */

        }
    }

    
end:
    for (;;);
}
