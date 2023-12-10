.global x86_outb
x86_outb:
    movw 4(%esp), %dx
    movb 8(%esp), %al
    outb %al, %dx
    ret

.global x86_inb
x86_inb:
    movw 4(%esp), %dx
    xorl %eax, %eax
    inb %dx, %al
    ret
