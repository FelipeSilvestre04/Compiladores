
gcd:
    load x20, 0(x3)
    addi x22, x0, 0
    beq x20, x21, L_gen_0
    jump L_gen_1
L_gen_0:
    addi x22, x0, 1
L_gen_1:
    beq x22, x0, L0
    load x23, 4(x3)
    jr x1
    jump L1
L0:
    load x24, 0(x3)
    mov x10, x24
    load x25, 4(x3)
    load x26, 4(x3)
    load x27, 0(x3)
    div x28, x26, x27
    load x29, 0(x3)
    mult x30, x28, x29
    sub x31, x25, x30
    mov x11, x31
    jal x1, gcd
    jr x1
L1:

main:
    in x33
    store x33, 8(x3)
    in x34
    store x34, 12(x3)
    load x35, 8(x3)
    mov x10, x35
    load x36, 12(x3)
    mov x11, x36
    jal x1, gcd
    out x37
    halt
