.text
j main

fibo :
  add $s2,$zero,$a0
  addi $t1,$zero,0
  beq $s2,$t1,label3
  j label4
label4:
  addi $t2,$zero,1
  beq $s2,$t2,label3
  j label2
label3:
  addi $t3,$zero,1
  add $v0,$zero,$t3
  jr $ra
label2:
  addi $t4,$zero,1
  add $s4,$zero,$t4
  addi $t5,$zero,1
  add $s5,$zero,$t5
  addi $t6,$zero,1
  sub $t7,$s2,$t6
  add $s2,$zero,$t7
label01:
  bne $s2,0,label9
  j label8
label9:
  add $s3,$zero,$s4
  add $s4,$zero,$s5
  add $t8,$s3,$s4
  add $s5,$zero,$t8
  addi $t9,$zero,1
  sub $t0,$s2,$t9
  add $s2,$zero,$t0
  j label01
label8:
  add $v0,$zero,$s5
  jr $ra
label1:

main :
  addi $t1,$zero,0
  add $s7,$zero,$t1
label71:
  addi $t2,$zero,9
  bne $s7,$t2,label61
  j label51
label61:
  add $a0,$zero,$s7
  jal fibo
  add $t3,$zero,$v0
  add $s0,$zero,$t3
  ######################################
  add    $a0,$0,$s0
  addi   $v0,$0,34         # display hex
  syscall                 # we are out of here.
  ######################################
  addi $t4,$zero,1
  add $t5,$s7,$t4
  add $s7,$zero,$t5
  j label71
label51:
  add $v0,$zero,$s7
  ######################################
  addi   $v0,$zero,10         # pause
  syscall                  # we are out of here.
  ######################################
  jr $ra
label41:
