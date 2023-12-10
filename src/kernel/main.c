#include <stdint.h>
#include "stdio.h"
#include "memory.h"
#include <hal/hal.h>
#include <debug.h>
#include<multiboot.h>
#include<mmngr_phys.h>
extern uint8_t _start;  // Assuming 'start' is a byte (char) address
extern uint8_t _end_kernel;

void kernel_main(multiboot_info_t* mbd, uint32_t magic)
{
    HAL_Initialize();
    printf("HAL Initialised \n");
    printf("Hello World!\n");
    uintptr_t load_kernel_addr = (uintptr_t)&_start;
    uintptr_t end_kernel_addr = (uintptr_t)&_end_kernel;
    log_info("Main","\nKernel start: 0x%x Kernel End:  0x%x \n",load_kernel_addr,end_kernel_addr);
    log_info("Main","Hello Testing error:");
    size_t kernelSize=end_kernel_addr- load_kernel_addr;
    size_t loadAddressKB = load_kernel_addr / 1024;
    size_t endAddressKB = end_kernel_addr / 1024;
    printf("Kernel Load Address: %u KB\n", loadAddressKB);
    printf("Kernel End Address: %u KB\n",endAddressKB);
    printf("Kernel Size: %u bytes\n",kernelSize);
    uint32_t lo_mem=mbd->mem_lower;
    uint32_t hi_mem=mbd->mem_upper;
    printf("Lower Memory: %u KB\n", lo_mem);
    printf("Upper Memory: %u KB\n", hi_mem);    

    size_t NetMem=hi_mem+1024;
    pmmngr_init(NetMem,&_end_kernel);

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
        uint32_t MemLen=mmmt->len_low;
        uint32_t MemType=mmmt->type;
        uint32_t MemSize=mmmt->size;
        uint32_t MemStartAddr=mmmt->addr_low;
        size_t MemStartAddrKB=MemStartAddr/1024;

        printf("Start Addr: %x | Length: %u KB | Type: %d\n | AddressInKB %u KB\n",
            MemStartAddr, (size_t)(MemLen/1024), MemType, MemStartAddrKB);
        
    if ((MemType==1)){
			pmmngr_init_region (MemStartAddr, (size_t)(MemLen));
            printf("The Activated Region start address: 0x%x\n",MemStartAddr);
    }
       
    }
    pmmngr_deinit_region(0x20000c,&_end_kernel-&_start);
    printf("\n\n");
    printf("\npmm regions initialized: %i allocation blocks; used or reserved blocks: %i\nfree blocks: %i\n",
		pmmngr_get_block_count (),  pmmngr_get_use_block_count (), pmmngr_get_free_block_count () );

    uint32_t* p = (uint32_t*)pmmngr_alloc_block ();
	printf("\np allocated at 0x%x", p);
    uint32_t* p2 = (uint32_t*)pmmngr_alloc_block ();
    printf("\np2 allocated at 0x%x",p2);
	pmmngr_free_block (p);
    uint32_t* p3=(uint32_t*)pmmngr_alloc_block();
    printf("\np3 allocated at 0x%x",p3);

end:
    for (;;);
}
