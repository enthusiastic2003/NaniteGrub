#ifndef MULTIBOOT_H
#define MULTIBOOT_H
#include<stdint.h>
struct multiboot_header {
    uint32_t magic;
    uint32_t flags;
    uint32_t checksum;
    uint32_t header_addr;
    uint32_t load_addr;
    uint32_t load_end_addr;
    uint32_t bss_end_addr;
    uint32_t entry_addr;
} __attribute__((packed, section("multiboot_header")));

#define MULTIBOOT_HEADER_MAGIC 0x1BADB002

// Flags for Multiboot header
#define MULTIBOOT_HEADER_FLAGS (1 << 0) | (1 << 16)

#endif