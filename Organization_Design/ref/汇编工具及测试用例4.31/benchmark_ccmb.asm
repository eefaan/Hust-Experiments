#############################################################
#����j,jal,jrָ�����Ҫ�ɷֿ����ԣ�ִ������Ӧ����15������ revise date 2015/12/17 tiger
#############################################################
.text
benchmark_start:
 addi $s1,$zero, 1   #����j,jal,jrָ�����Ҫ�ɷֿ����ԣ�ִ������Ӧ����15������
 j jmp_next1
 addi $s1,$zero, 1
 addi $s2,$zero, 2
 addi $s3,$zero, 3
jmp_next1:
 j jmp_next2
 addi $s1,$zero, 1
 addi $s2,$zero, 2
 addi $s3,$zero, 3
jmp_next2:
 j jmp_next3
 addi $s1,$zero, 1
 addi $s2,$zero, 2
 addi $s3,$zero, 3
jmp_next3:
 j jmp_next4
 addi $s1,$zero, 1
 addi $s2,$zero, 2
 addi $s3,$zero, 3
jmp_next4:jal jmp_count

######################################


#��λ����  ��Ҫ֧�ֳ�addi,sll,add,syscall,srl,sll,sra,beq,j,syscall    revise date:2015/12/16 tiger

.text
addi $s0,$zero,1     #����λ��ѭ�����ԣ�0��������ʾ���ǳ�ʼֵ1����1λ�ظ�15�ε�ֵ��1���������ۼ�ֵ
addi $s1,$zero,1
sll $s1, $s1, 31   #�߼�����31λ $s1=0x80000000


###################################################################
#                �߼����Ʋ���
# ��ʾ����������ʾ0x80000000 0x20000000 0x08000000 0x02000000 0x00800000 0x00200000 0x00080000 0x00020000 0x00008000 0x00002000 0x00000800 0x00000200 0x00000080 0x00000020 0x00000008 0x00000002 0x00000000
###################################################################
LogicalRightShift:            #�߼����Ʋ��ԣ������λ1��λ��������ֱ�����Ϊ��

add    $a0,$0,$s1       #display $s1    #�߼����Ʋ��ԣ������λ1��λ��������ֱ�����Ϊ��
addi   $v0,$0,34        # display hex
syscall                 # we are out of here.

srl $s1, $s1, 2
beq $s1, $zero, shift_next1
j LogicalRightShift

shift_next1:

add    $a0,$0,$s1       #display $s1
addi   $v0,$0,34         # display hex
syscall                 # we are out of here.


###################################################################
#                �߼����Ʋ���
# ��ʾ����������ʾ0x00000004 0x00000010 0x00000040 0x00000100 0x00000400 0x00001000 0x00004000 0x00010000 0x00040000 0x00100000 0x00400000 0x01000000 0x04000000 0x10000000 0x40000000 0x00000000
###################################################################

addi $s1,$zero, 1        #                �߼����Ʋ���
LogicalLeftShift:         #�߼����Ʋ��ԣ������λ1��λ������ֱ�����Ϊ��
sll $s1, $s1, 2

add    $a0,$0,$s1       #display $s1
addi   $v0,$0,34         # display hex
syscall                 # we are out of here.

beq $s1, $zero, ArithRightShift
j LogicalLeftShift


###################################################################
#                �������Ʋ���
# ��ʾ����������ʾ0x80000000 0xf0000000 0xff000000 0xfff00000 0xffff0000 0xfffff000 0xffffff00 0xfffffff0 0xffffffff
###################################################################
ArithRightShift:          #�������Ʋ��ԣ�#������λ���ԣ�80000000�������ƣ�������ʾΪF0000000,FF000000,FFF00000,FFFF0000ֱ��FFFFFFFF

addi $s1,$zero,1     #                �������Ʋ���
sll $s1, $s1, 31   #�߼�����31λ $s1=0x80000000

add    $a0,$0,$s1       #display $s1
addi   $v0,$0,34         # display hex
syscall                 # we are out of here.

sra $s1, $s1, 3    #$s1=0X80000000-->0XF0000000

add    $a0,$0,$s1       #display $s1
addi   $v0,$0,34         # display hex
syscall                 # we are out of here.


sra $s1, $s1, 4    #0XF0000000-->0XFF000000

add    $a0,$0,$s1       #display $s1
addi   $v0,$0,34         # display hex
syscall                 # we are out of here.


sra $s1, $s1, 4    #0XFF000000-->0XFFF00000

add    $a0,$0,$s1       #display $s1
addi   $v0,$0,34         # display hex
syscall                 # we are out of here.

sra $s1, $s1, 4

add    $a0,$0,$s1       #display $s1
addi   $v0,$0,34         # display hex
syscall                 # we are out of here.

sra $s1, $s1, 4

add    $a0,$0,$s1       #display $s1
addi   $v0,$0,34         # display hex
syscall                 # we are out of here.


sra $s1, $s1, 4

add    $a0,$0,$s1       #display $s1
addi   $v0,$0,34         # display hex
syscall                 # we are out of here.


sra $s1, $s1, 4

add    $a0,$0,$s1       #display $s1
addi   $v0,$0,34         # display hex
syscall                 # we are out of here.


sra $s1, $s1, 4


add    $a0,$0,$s1       #display $s1
addi   $v0,$0,34         # display hex
syscall                 # we are out of here.

#############################################################
#����Ʋ���,����addi,andi,sll,srl,sra,or,ori,nor,syscall  LED������Ʒ�ʽ������ʾ����
#############################################################

.text
addi $s0,$zero,1
sll $s3, $s0, 31      # $s3=0x80000000
sra $s3, $s3, 31      # $s3=0xFFFFFFFF
addu $s0,$zero,$zero   # $s0=0
addi $s2,$zero,12

addiu $s6,$0,3  #����Ƽ���
zmd_loop:

addiu $s0, $s0, 1    #������һ������Ƶ�����
andi $s0, $s0, 15

#######################################
addi $t0,$0,8
addi $t1,$0,1
left:

sll $s3, $s3, 4   #���������
or $s3, $s3, $s0

add    $a0,$0,$s3       # display $s3
addi   $v0,$0,34         # system call for LED display
syscall                 # display

sub $t0,$t0,$t1
bne $t0,$0,left
#######################################

addi $s0, $s0, 1   #������һ������Ƶ�����
addi $t8,$0,15
and $s0, $s0, $t8
sll $s0, $s0, 28

addi $t0,$0,8
addi $t1,$0,1

zmd_right:

srl $s3, $s3, 4  #���������
or $s3, $s3, $s0

addu    $a0,$0,$s3       # display $s3
addi   $v0,$0,34         # system call for LED display
syscall                 # display

sub $t0,$t0,$t1
bne $t0,$0,zmd_right
srl $s0, $s0, 28
#######################################

sub $s6,$s6,$t1
beq $s6,$0, exit
j zmd_loop

exit:

add $t0,$0,$0
nor $t0,$t0,$t0      #test nor  ori
sll $t0,$t0,16
ori $t0,$t0,0xffff

addu   $a0,$0,$t0       # display $t0
addi   $v0,$0,34         # system call for LED display
syscall                 # display
#################################################################################
#������ʵ��0-15���ֵ�Ԫ�Ľ�������,�˳������mars mips������������
#����ʱ�뽫Mars Setting�е�Memory Configuration����ΪCompact��data at address 0
#
#################################################################################
 .text
sort_init:
 addi $s0,$0,-1
 addi $s1,$0,0

 sw $s0,0($s1)
 addi $s0,$s0,1
 addi $s1,$s1,4
 sw $s0,0($s1)
 addi $s0,$s0,1
 addi $s1,$s1,4
 sw $s0,0($s1)
 addi $s0,$s0,1
 addi $s1,$s1,4
 sw $s0,0($s1)
 addi $s0,$s0,1
 addi $s1,$s1,4
 sw $s0,0($s1)
 addi $s0,$s0,1
 addi $s1,$s1,4
 sw $s0,0($s1)
 addi $s0,$s0,1
 addi $s1,$s1,4
 sw $s0,0($s1)
 addi $s0,$s0,1
 addi $s1,$s1,4
 sw $s0,0($s1)
 addi $s0,$s0,1
 addi $s1,$s1,4
  sw $s0,0($s1)
 addi $s0,$s0,1
 addi $s1,$s1,4
  sw $s0,0($s1)
 addi $s0,$s0,1
 addi $s1,$s1,4
 sw $s0,0($s1)
 addi $s0,$s0,1
 addi $s1,$s1,4
  sw $s0,0($s1)
 addi $s0,$s0,1
 addi $s1,$s1,4
  sw $s0,0($s1)
 addi $s0,$s0,1
 addi $s1,$s1,4
  sw $s0,0($s1)
 addi $s0,$s0,1
 addi $s1,$s1,4
  sw $s0,0($s1)
 addi $s0,$s0,1
 addi $s1,$s1,4
    sw $s0,0($s1)
 addi $s0,$s0,1
 addi $s1,$s1,4

 addi $s0,$s0,1

 add $s0,$zero,$zero
 addi $s1,$zero,60   #��������
sort_loop:
 lw $s3,0($s0)
 lw $s4,0($s1)
 slt $t0,$s3,$s4
 beq $t0,$0,sort_next   #��������
 sw $s3, 0($s1)
 sw $s4, 0($s0)
sort_next:
 addi $s1, $s1, -4
 bne $s0, $s1, sort_loop

 add    $a0,$0,$s0       #display $s0
 addi   $v0,$0,34         # display hex
 syscall                 # we are out of here.  DISP: disp $r0, 0

 addi $s0,$s0,4
 addi $s1,$zero,60
 bne $s0, $s1, sort_loop

 addi   $v0,$zero,50         # system call for pause
 syscall                  # we are out of here.


#############################################
# insert your ccmb benchmark program here!!!
#############################################

# j benchmark_start       #delete this instruction for ccmb bencmark

#C1 instruction benchmark
.text
#SLLV��λ����    revise date:2018/3/12 tiger
#�������  0x00000876 0x00008760 0x00087600 0x00876000 0x08760000 0x87600000 0x76000000 0x60000000 0x00000000
addi $t0,$zero,1
addi $t1,$zero,3
addi $s1,$zero,  0x876

add $a0,$0,$s1
addi $v0,$zero,34         # system call for print
syscall                  # print

addi $t3,$zero,8

sllv_branch:
sllv $s1,$s1,$t0     #����ָ��
sllv $s1,$s1,$t1     #����ָ��
add $a0,$0,$s1
addi $v0,$zero,34         # system call for print
syscall                  # print
addi $t3,$t3, -1
bne $t3,$zero,sllv_branch

addi   $v0,$zero,10         # system call for exit
syscall                  # we are out of here.



#C2 instruction benchmark
.text
#XOR����    revise date:2018/3/12 tiger
# 0x00007777 xor   0xffffffff =  0xffff8888
# 0xffff8888 xor   0xffffffff =  0x00007777
#������� 0x00007777 0xffff8888 0x0000777
addi $t0,$zero,-1     #
addi $s1,$zero, 0x7777     #

add $a0,$0,$s1
addi $v0,$zero,34         # system call for print
syscall                  # print

addi $t3,$zero, 0x10

xor_branch:
xor $s1,$s1,$t0     #����1λ
add $a0,$0,$s1
addi $v0,$zero,34         # system call for print
syscall                  # print
addi $t3,$t3, -1
bne $t3,$zero,xor_branch   #ѭ��8��

addi   $v0,$zero,10         # system call for exit
syscall                  # we are out of here.



#Mem instruction benchmark
.text
#SB ����    revise date:2018/3/14 tiger
#�������   0x00000000 0x00000001 0x00000002 0x00000003 0x00000004 0x00000005 0x00000006 0x00000007 0x00000008 0x00000009 0x0000000a 0x0000000b 0x0000000c 0x0000000d 0x0000000e 0x0000000f 0x00000010 0x00000011 0x00000012 0x00000013 0x00000014 0x00000015 0x00000016 0x00000017 0x00000018 0x00000019 0x0000001a 0x0000001b 0x0000001c 0x0000001d 0x0000001e 0x0000001f 0x03020100 0x07060504 0x0b0a0908 0x0f0e0d0c 0x13121110 0x17161514 0x1b1a1918 0x1f1e1d1c
addi $t1,$zero,0     #init_addr
addi $t3,$zero,32     #counter

#sbд�� 01,02,03,04
addi $s1,$zero, 0x00  #
addi $s2,$zero, 0x01  #

sb_store:
sb $s1,($t1)
add $a0,$0,$s1
addi $v0,$zero,34        # system call for print
syscall                  # print

add $s1,$s1,$s2          #data +1
addi $t1,$t1,1           # addr ++
addi $t3,$t3,-1          #counter
bne $t3,$zero,sb_store

addi $t3,$zero,8
addi $t1,$zero,0    # addr
sb_branch:
lw $s1,($t1)       #��������
add $a0,$0,$s1
addi $v0,$zero,34        # system call for print
syscall                  # print
addi $t1,$t1,4
addi $t3,$t3, -1
bne $t3,$zero,sb_branch

addi   $v0,$zero,10      # system call for exit
syscall                  # we are out of here.




#Branch instruction benchmark
.text
#bltz ����    С��0��ת   �ۼ����㣬�Ӹ�����ʼ�������� revise date:2018/3/12 tiger
#�������0xfffffff1 0xfffffff2 0xfffffff3 0xfffffff4 0xfffffff5 0xfffffff6 0xfffffff7 0xfffffff8 0xfffffff9 0xfffffffa 0xfffffffb 0xfffffffc 0xfffffffd 0xfffffffe 0xffffffff
addi $s1,$zero,-15       #��ʼֵ
bltz_branch:
add $a0,$0,$s1
addi $v0,$zero,34
syscall                  #�����ǰֵ
addi $s1,$s1,1
bltz $s1,bltz_branch     #��ǰָ��


addi   $v0,$zero,10
syscall                  #��ͣ���˳�



 addi   $v0,$zero,10         # system call for exit
 syscall                  # we are out of here.

 #MIPS������ʵ��������ͣ��ָ��ʵ��syscall

jmp_count: addi $s0,$zero, 0
       addi $s0,$s0, 1
       add    $a0,$0,$s0
       addi   $v0,$0,34         # display hex
       syscall                 # we are out of here.

       addi $s0,$s0, 2
       add    $a0,$0,$s0
       addi   $v0,$0,34         # display hex
       syscall                 # we are out of here.

       addi $s0,$s0, 3
       add    $a0,$0,$s0
       addi   $v0,$0,34         # display hex
       syscall                 # we are out of here.

       addi $s0,$s0, 4
       add    $a0,$0,$s0
       addi   $v0,$0,34         # display hex
       syscall                 # we are out of here.

       addi $s0,$s0, 5
       add    $a0,$0,$s0
       addi   $v0,$0,34         # display hex
       syscall                 # we are out of here.

       addi $s0,$s0, 6
       add    $a0,$0,$s0
       addi   $v0,$0,34         # display hex
       syscall                 # we are out of here.

       addi $s0,$s0, 7
       add    $a0,$0,$s0
       addi   $v0,$0,34         # display hex
       syscall                 # we are out of here.

       addi $s0,$s0, 8
       add    $a0,$0,$s0
       addi   $v0,$0,34         # display hex
       addi   $v0,$0,34         # display hex
       syscall                 # we are out of here.


       jr $31
