.att_syntax
	
.globl gdt_flush
.type gdt_flush, @function

gdt_flush:
	movl %eax, 4(%esp)
	lgdt (%eax)      

	mov $0x10, %ax
	mov %ax, %ds      
	mov %ax, %es
	mov %ax, %fs
	mov %ax, %gs
	mov %ax, %ss
	ret

.globl idt_flush
.type idt_flush, @function

idt_flush:
	movl %eax, 4(%esp)
	lidt (%eax)      
	ret

