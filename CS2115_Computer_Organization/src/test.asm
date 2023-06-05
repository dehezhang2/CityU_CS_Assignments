.data
	message: .asciiz "hello world\nMy name is weak\n"
	newline: .asciiz "\n"
.text
	addi $t1, $zero, 30
	addi $t2, $zero, 8
	div $t1,$t2
	
	
	mflo $s0 	#Quotient
	mfhi $s1	#Remainder
	
	li $v0, 1
	add $a0, $zero, $s1
	syscall
	
	li $v0, 4
	la $a0, newline
	syscall
	
	li $v0, 1
	add $a0, $zero, $s2
	syscall
	
	
