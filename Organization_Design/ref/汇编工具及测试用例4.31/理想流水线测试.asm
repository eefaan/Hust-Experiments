#������ˮ�߲��ԣ�����ָ���������ԣ�һ��17��ָ�5����ˮ��ִ��������Ӧ����5+(17-1��=21
addi $s0,$zero, 0
addi $s1,$zero, 1
addi $s2,$zero, 2
addi $s3,$zero, 3
ori $s0,$s0, 0
ori $s1,$s1, 1
ori $s2,$s2, 2
ori $s3,$s3, 3
sw $s0, 0($s0)            # write data memory
sw $s1, 4($s0)
sw $s2, 8($s0)
sw $s3, 12($s0)
addi $v0,$zero,10         # system call for exit
nop                       # bubbles for data hazard
nop
nop
syscall                   # we are out of here.   