SUBDIRS := $(wildcard */.)
C_SOURCEFILES= $(wildcard *.c)
ASM_SOURCEFILES=$(wildcard *.asm)
C_OBJECTS = $(C_SOURCEFILES:.c=.o)
ASM_OBJECTS= $(ASM_SOURCEFILES:.asm=.o)
export
NASM="nasm"
ASFLAGS=-f elf32
.PHONY: all $(C_OBJECTS) $(ASM_OBJECTS) folder_req $(SUBDIRS)

all: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@