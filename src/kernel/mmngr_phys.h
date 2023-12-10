#ifndef __MMNGR_PHYS_H
#define __MMNGR_PHYS_H
#include <stdint.h>
#include <stddef.h>
//Physical Memory manager
typedef uint32_t physical_addr;
//! initialize the physical memory manager
void	pmmngr_init(size_t, physical_addr);

//! enables a physical memory region for use
void	pmmngr_init_region (physical_addr, size_t);

//! disables a physical memory region as in use (unuseable)
void	pmmngr_deinit_region (physical_addr base, size_t);

//! allocates a single memory block
void*	pmmngr_alloc_block ();

//! releases a memory block
void	pmmngr_free_block (void*);

//! allocates blocks of memory
void*	pmmngr_alloc_blocks (size_t);

//! frees blocks of memory
void	pmmngr_free_blocks (void*, size_t);

//! returns amount of physical memory the manager is set to use
size_t pmmngr_get_memory_size ();

//! returns number of blocks currently in use
uint32_t pmmngr_get_use_block_count ();

//! returns number of blocks not in use
uint32_t pmmngr_get_free_block_count ();

//! returns number of memory blocks
uint32_t pmmngr_get_block_count ();

//! returns default memory block size in bytes
uint32_t pmmngr_get_block_size ();

//! enable or disable paging
void __attribute__((cdecl))	pmmngr_paging_enable (bool);

//! test if paging is enabled
bool __attribute__((cdecl))	pmmngr_is_paging ();

//! loads the page directory base register (PDBR)
void __attribute__((cdecl))	pmmngr_load_PDBR (unsigned int *);

//! get PDBR physical address
physical_addr __attribute__((cdecl)) pmmngr_get_PDBR ();

//! Paging Details
#ifndef PAGING_H
#define PAGING_H

#define NUM_PAGES 1024
#define PAGE_FRAME_SIZE 4096

#define PRESENT         1
#define PAGE_READONLY   0
#define PAGE_READWRITE  1
#define PAGE_USER       1
#define PAGE_KERNEL     0
#define PAGE_SIZE_4KB   0
#define PAGE_SIZE_4MB   1

typedef struct page
{
   unsigned int present    : 1;   // Page present in memory
   unsigned int rw         : 1;   // Read-only if clear, readwrite if set
   unsigned int user       : 1;   // Supervisor level only if clear
   unsigned int accessed   : 1;   // Has the page been accessed since last refresh?
   unsigned int dirty      : 1;   // Has the page been written to since last refresh?
   unsigned int unused     : 7;   // Amalgamation of unused and reserved bits
   unsigned int frame      : 20;  // Frame address (shifted right 12 bits)
} page_t;

typedef struct page_table
{
   page_t pages[1024] __attribute__((aligned(4096)));
} page_table_t;

typedef struct page_directory
{
   /**
      Array of pointers to pagetables.
   **/
   page_table_t *tables[1024];
   /**
      Array of pointers to the pagetables above, but gives their *physical*
      location, for loading into the CR3 register.
   **/
   unsigned int tablesPhysical[1024];
   /**
      The physical address of tablesPhysical. This comes into play
      when we get our kernel heap allocated and the directory
      may be in a different location in virtual memory.
   **/
   unsigned int physicalAddr;
} page_directory_t;
void init_paging();
#endif

//============================================================================
//    INTERFACE OBJECT CLASS DEFINITIONS
//============================================================================
//============================================================================
//    INTERFACE TRAILING HEADERS
//============================================================================
//****************************asdasdasd************************************************
//**
//**    END [mmngr_phys.h]
//**
//****************************************************************************
#endif
