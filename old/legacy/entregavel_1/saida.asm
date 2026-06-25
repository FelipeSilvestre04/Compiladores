JUMP main
gcd:
LOAD_STACK $at
STORE $at, u, 0
LOAD_STACK $at
STORE $at, v, 0
STORE_STACK $ra
LOAD $t0, v
ADDI $t1, $zero, 0
BNE $t0, $t1, L0
LOAD $t0, u
LOAD_STACK $ra
STORE_STACK $t0
JR $ra
JUMP L1
L0:
LOAD $t0, u
LOAD $t1, u
LOAD $t2, v
DIV $t3, $t1, $t2
LOAD $t1, v
MULT $t2, $t3, $t1
SUB $t1, $t0, $t2
STORE_STACK $t1
LOAD $t0, v
STORE_STACK $t0
JAL $ra, gcd
LOAD_STACK $t0
LOAD_STACK $ra
STORE_STACK $t0
JR $ra
L1:
main:
STORE_STACK $ra
IN $t0
STORE -, $t0, x
IN $t0
STORE -, $t0, y
LOAD $t0, y
STORE_STACK $t0
LOAD $t0, x
STORE_STACK $t0
JAL $ra, gcd
LOAD_STACK $t0
OUT $t0
HALT
