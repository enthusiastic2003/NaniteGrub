ASM_SOURCEFILES=$(wildcard *.asm)
ASM_OBJS=$(ASM_SOURCEFILES:.asm=.o)
CSRC=$(wildcard *.c)
COBJS=$(CSRC:.c=.o)
CFLAGS=-std=gnu99 -ffreestanding -O2 -Wall -Wextra -nostdlib -c
all: folder_req boot $(ASM_OBJS) $(COBJS)

boot: 
	@$(GAS) boot.s -o $(BUILD_DIR)/boot/boot.o
	@echo "Compiled: boot.s"

$(ASM_OBJS):  %.o: %.asm
	@nasm -f elf32 $< -o $(BUILD_DIR)/boot/$@
	@echo "Compiled: $<"

$(COBJS): %.o: %.c
	@$(CC1) $(CFLAGS) $< -o $(BUILD_DIR)/boot/$@
	@echo "Compiled: $<"


folder_req:
	$(shell mkdir -p $(BUILD_DIR)/boot)
