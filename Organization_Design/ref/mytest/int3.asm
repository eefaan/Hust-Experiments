
#############################################################################################
#�жϷ����ӳ���3��Ϊ3���ж϶�Ӧ���жϷ������
#����Ϊ����3������Ʋ���
##########################################################################################################
.text



#mfc0 $k0,$1           #����EPC��ֵ
#addiu $gp,$gp,-4     #����EPC��ֵ
#sw $k0,0($gp)

#addiu $k1,$0,0  #���ж�
#mtc0 $k1,$0

addiu $sp,$sp,-4   #��ջ�������ֳ�
sw $s0,0($sp)
addiu $sp,$sp,-4
sw $s2,0($sp)
addiu $sp,$sp,-4
sw $s3,0($sp)
addiu $sp,$sp,-4
sw $t0,0($sp)
addiu $sp,$sp,-4
sw $t1,0($sp)
addiu $sp,$sp,-4
sw $a0,0($sp)
addiu $sp,$sp,-4
sw $v0,0($sp)
addiu $sp,$sp,-4
sw $t8,0($sp)

#addiu $k1,$0,0
#mtc0 $k1,$0      #���ж�

addi $s0,$zero,1
sll $s3, $s0, 31      # $s3=0x80000000
sra $s3, $s3, 31      # $s3=0xFFFFFFFF
addu $s0,$zero,$zero   # $s0=0
addi $s2,$zero,12



addiu $s0, $s0, 3    #������һ������Ƶ�����
andi $s0, $s0, 15

#######################################
addi $t0,$0,8
addi $t1,$0,1
left3:

sll $s3, $s3, 4   #���������
or $s3, $s3, $s0

add    $a0,$0,$s3       # display $s3
addi   $v0,$0,34         # system call for LED display
syscall                 # display

sub $t0,$t0,$t1
bne $t0,$0,left3
#######################################

addi $s0, $s0, 1   #������һ������Ƶ�����
addi $t8,$0,15
and $s0, $s0, $t8
sll $s0, $s0, 28

addi $t0,$0,8
addi $t1,$0,1

zmd_right3:

srl $s3, $s3, 4  #���������
or $s3, $s3, $s0

addu    $a0,$0,$s3       # display $s3
addi   $v0,$0,34         # system call for LED display
syscall                 # display

sub $t0,$t0,$t1
bne $t0,$0,zmd_right3
srl $s0, $s0, 28
#######################################



exit3:

add $t0,$0,$0
nor $t0,$t0,$t0      #test nor  ori
sll $t0,$t0,16
ori $t0,$t0,0xffff

addu   $a0,$0,$t0       # display $t0
addi   $v0,$0,34         # system call for LED display
syscall                 # display

#addiu $k1,$0,1  #���ж�
#mtc0 $k1,$0
lw $t8,0($sp)   #��ջ���ָ��ֳ�
addiu $sp,$sp,4
lw $v0,0($sp)
addiu $sp,$sp,4
lw $a0,0($sp)
addiu $sp,$sp,4
lw $t1,0($sp)
addiu $sp,$sp,4
lw $t0,0($sp)
addiu $sp,$sp,4
lw $s3,0($sp)
addiu $sp,$sp,4
lw $s2,0($sp)
addiu $sp,$sp,4
lw $s0,0($sp)
addiu $sp,$sp,4
#lw $k0,0($gp)  #EPC��ֵ
#addiu $gp,$gp,4
#mtc0 $k0,$1    #д��EPC

eret
