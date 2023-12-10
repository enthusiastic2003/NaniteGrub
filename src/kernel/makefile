
CFLAGS=-std=gnu99 -ffreestanding -O2 -Wall -Wextra -nostdlib -c
C_SOURCEFILES= $(wildcard *.c)
ASM_SOURCEFILES=$(wildcard *.asm)
C_OBJECTS = $(C_SOURCEFILES:.c=.o)
ASM_OBJECTS= $(ASM_SOURCEFILES:.asm=.o)
export
NASM="nasm"
ASFLAGS=-f elf32
all: folder_req $(C_OBJECTS) $(ASM_OBJECTS)

$(C_OBJECTS): %.o: %.c
	echo $(C_OBJECTS)
	$(CC1) $(CFLAGS) $< -o $(BUILD_DIR)/kernel/$@
	echo $(ASM_OBJECTS)

$(ASM_OBJECTS): %.o: %.asm
	echo $(ASM_OBJECTS)
	$(NASM) $(ASFLAGS) $< -o $(BUILD_DIR)/kernel/$@

folder_req:
	$(shell mkdir -p $(BUILD_DIR)/kernel)
