ISONAME = kraken.iso
#GIFLAGS = -R -b boot/grub/stage2_eltorito -no-emul-boot -boot-load-size 4 -boot-info-table -quiet -o  $(ISONAME) iso/
RFLAGS = -o $(ISONAME) iso/
MKIMAGE = grub-mkrescue $(RFLAGS)

all:
	@make -C kernel/
	@cp kernel/kernel iso/boot/kernel
	@$(MKIMAGE)

clean:
	@make clean -C kernel/

qemu:	all
	@qemu-system-i386 -vga std -cdrom $(ISONAME)