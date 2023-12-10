export
ASM_SOURCEFILES=$(wildcard *.s)
ASM_OBJS=$(ASM_SOURCEFILES:.asm=.o)

all: folder_req boot $(ASM_OBJECTS)
boot: 
	$(GAS) boot.s -o $(BUILD_DIR)/boot/boot.o

$(ASM_OBJECTS):  %.o: %.asm
	$(NASM) $(ASFLAGS) $< -o $(BUILD_DIR)/boot/$@


folder_req:
	$(shell mkdir -p $(BUILD_DIR)/boot)
