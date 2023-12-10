#include <stdint.h>
#include "stdio.h"
#include "memory.h"
#include <hal/hal.h>
#include <debug.h>
#include<multiboot.h>

extern uint8_t _start;  // Assuming 'start' is a byte (char) address
extern uint8_t _end_kernel;

void kernel_main(multiboot_info_t* mbd, uint32_t magic)
{
    HAL_Initialize();
    printf("HAL Initialised \n");
    printf("Hello World!\n");
    uintptr_t load_kernel_addr = (uintptr_t)&_start;
    uintptr_t end_kernel_addr = (uintptr_t)&_end_kernel;
    log_info("Main","\nKernel start: 0x%x Kernel End:  0x%x",load_kernel_addr,end_kernel_addr);
    size_t kernelSize=end_kernel_addr- load_kernel_addr;
    size_t loadAddressKB = load_kernel_addr / 1024;
    size_t endAddressKB = end_kernel_addr / 1024;
    printf("Kernel Load Address: %u KB\n", loadAddressKB);
    printf("Kernel End Address: %u KB\n",endAddressKB);
    printf("Kernel Size: %u bytes\n",kernelSize);
    uint32_t lo_mem=mbd->mem_lower;
    uint32_t hi_mem=mbd->mem_upper;
    uint32_t NetMem=1024+hi_mem*64+lo_mem;
    printf("Lower Memory: %u KB\n", lo_mem);
    printf("Upper Memory: %u KB\n", hi_mem);    
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
            uint32_t len=mmmt->len_low;
            uint32_t type=mmmt->type;
            uint32_t size=mmmt->size;
            uint32_t start_addr=mmmt->addr_low;
            if (load_kernel_addr>=start_addr){
                if(end_kernel_addr<=start_addr+len){
                    printf("Kernel located in this region: \nStart Addr: %x | Length: %x | Size: %x | Type: %d\n",
            start_addr, len, size, type);
                }
            }
        }
    }

    
end:
    for (;;);
}
