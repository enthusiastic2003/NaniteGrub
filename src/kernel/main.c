#include <stdint.h>
#include "stdio.h"
#include "memory.h"

extern uint8_t __bss_start;
extern uint8_t __end;

void kernel_main(void)
{
    //memset(&__bss_start, 0, (&__end) - (&__bss_start));
    printf("Hello World!");

end:
    for (;;);
}
