
CFLAGS=-std=gnu99 -ffreestanding -O2 -Wall -Wextra -nostdlib -c
C_SOURCEFILES= $(wildcard *.c)
ASM_SOURCEFILES=$(wildcard *.s)
C_OBJECTS = $(C_SOURCEFILES:.c=.o)
ASM_OBJECTS= $(ASM_SOURCEFILES:.s=.o)
export
all: folder_req $(C_OBJECTS) $(ASM_OBJECTS)

$(C_OBJECTS): %.o: %.c
	echo $(C_OBJECTS)
	$(CC1) $(CFLAGS) $< -o $(BUILD_DIR)/kernel/$@
	echo $(ASM_OBJECTS)

$(ASM_OBJECTS): %.o: %.s
	echo $(ASM_OBJECTS)
	$(AS) $< -o $(BUILD_DIR)/kernel/$@

folder_req:
	$(shell mkdir -p $(BUILD_DIR)/kernel)
