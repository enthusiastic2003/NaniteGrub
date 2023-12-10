SUBDIRS := kernel boot
LD = "$(HOME)/toolchains/bin/i686-elf-gcc"
CC1="$(HOME)/toolchains/bin/i686-elf-gcc"
NASM="nasm"
GAS="$(HOME)/toolchains/bin/i686-elf-as"
LDFLAGS = -ffreestanding -O2 -nostdlib
ISO_NAME = NaniteOS.iso
ISO_MOUNT_DIR = isodir
BUILD_DIR=$(PWD)/build
export
.PHONY: iso clean $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C src/ link


iso: $(SUBDIRS)

	mkdir -p $(ISO_MOUNT_DIR)/boot/grub
	cp build/Nanite.bin $(ISO_MOUNT_DIR)/boot/
	cp grub.cfg $(ISO_MOUNT_DIR)/boot/grub/
	grub-mkrescue -o build/$(ISO_NAME) $(ISO_MOUNT_DIR)

clean:
	rm -rf build/
run: iso 
	$(shell ./run.sh)
