SUBDIRS := kernel boot
LDFLAGS = -ffreestanding -O2 -nostdlib
LD_LIBS = -lgcc
OBJFILES= $(wildcard $(BUILD_DIR)/*.o)
OBJ_PAIRS := $(addprefix $(BUILD_DIR)/,$(notdir $(OBJFILES)))
BUILD_FILES_WITH_PATH_KERNEL := $(wildcard $(BUILD_DIR)/kernel/*)
BUILD_FILES_WITH_PATH_BOOT := $(wildcard $(BUILD_DIR)/boot/*)
# Append the paths to a variable
OBJ_PAIRS_KERNEL := $(addprefix $(BUILD_DIR)/kernel/,$(notdir $(BUILD_FILES_WITH_PATH_KERNEL)))
OBJ_PAIRS_BOOT := $(addprefix $(BUILD_DIR)/boot/,$(notdir $(BUILD_FILES_WITH_PATH_BOOT)))

export
.PHONY: obj link clean $(SUBDIRS)


link: obj
	$(LD) -T linker.ld -o $(BUILD_DIR)/Nanite.bin $(LDFLAGS) $(OBJ_PAIRS_BOOT) $(OBJ_PAIRS_KERNEL) $(LD_LIBS)


obj: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@ BUILD_DIR=$(BUILD_DIR)



