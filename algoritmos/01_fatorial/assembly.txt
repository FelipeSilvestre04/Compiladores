JUMP main
fact:
LOAD_STACK $at
STORE $at, n, 0
STORE_STACK $ra
LOAD $t0, n
ADDI $t1, $zero, 0
BGT $t0, $t1, L0
ADDI $t0, $zero, 1
LOAD_STACK $ra
STORE_STACK $t0
JR $ra
JUMP L1
L0:
L1:
LOAD $t0, n
LOAD $at, n, 0
STORE_STACK $at
STORE_STACK $t0
LOAD $t1, n
ADDI $t2, $zero, 1
SUB $t3, $t1, $t2
STORE_STACK $t3
JAL $ra, fact
LOAD_STACK $t1
LOAD_STACK $t0
LOAD_STACK $at
STORE $at, n, 0
MULT $t2, $t0, $t1
LOAD_STACK $ra
STORE_STACK $t2
JR $ra
LOAD_STACK $ra
JR $ra
main:
STORE_STACK $ra
IN $t0
STORE -, $t0, n
LOAD $at, n, 0
STORE_STACK $at
LOAD $t0, n
STORE_STACK $t0
JAL $ra, fact
LOAD_STACK $t0
LOAD_STACK $at
STORE $at, n, 0
OUT $t0
HALT -
