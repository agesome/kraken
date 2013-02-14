ISONAME = kraken.iso
GIFLAGS = -R -b boot/grub/stage2_eltorito -no-emul-boot -boot-load-size 4 -boot-info-table -quiet -o  $(ISONAME) iso/
GI = genisoimage $(GIFLAGS)

all:
	@make -C kernel/
	@cp kernel/kernel iso/boot/kernel
	@$(GI)

clean:
	@make clean -C kernel/

qemu:	all
	@qemu-system-i386 -cdrom $(ISONAME)