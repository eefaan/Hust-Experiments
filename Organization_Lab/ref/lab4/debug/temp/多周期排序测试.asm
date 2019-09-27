 addi $s0,$0,-1   #sort_init:
 addi $s1,$0,0
 sw $s0,128($s1)
 addi $s0,$s0,1
 addi $s1,$s1,4
 sw $s0,128($s1)
 addi $s0,$s0,1
 addi $s1,$s1,4
 sw $s0,128($s1)
 addi $s0,$s0,1
 addi $s1,$s1,4
 sw $s0,128($s1)
 addi $s0,$s0,1
 addi $s1,$s1,4
 sw $s0,128($s1)
 addi $s0,$s0,1
 addi $s1,$s1,4
 sw $s0,128($s1)
 addi $s0,$s0,1
 addi $s1,$s1,4
 sw $s0,128($s1)
 addi $s0,$s0,1
 addi $s1,$s1,4
 sw $s0,128($s1)
 add $s0,$zero,$zero   # ' '
 addi $s1,$zero,28   #≈≈–Ú«¯º‰
 lw $s3,128($s0)     #sort_loop:
 lw $s4,128($s1)
 slt $t0,$s3,$s4
 beq $t0,$0,sort_next   #Ωµ–Ú≈≈–Ú
 sw $s3, 128($s1)
 sw $s4, 128($s0)
 addi $s1, $s1, -4  #sort_next:
 bne $s0, $s1, sort_loop  # ' '
 addi $s0,$s0,4
 addi $s1,$zero,28
 bne $s0, $s1, sort_loop
 addi   $v0,$zero,10         # system call for exit
 syscall                  # we are out of here.   
