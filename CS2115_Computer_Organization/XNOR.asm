.data  #all the variables
	SID: .word  55199998
	stdbit: .word 100000000
	prompt: .asciiz "Enter a number please: "
	message1: .asciiz "\nThe result is: "
	message2: .asciiz "\nSorry, please input a smaller number"
	newline: .asciiz "\n"
	
	arr: .space 32
        divide: .word 10
	
.text  #all the instructions
	main:
		# Prompt the user to enter a number
		li $v0, 4  		# load the instruction to print string
		la $a0, prompt		# load the prompt string
		syscall
	
		# Get the user's input
		li $v0, 5		    # load the instruction to input integer, store it in v0
		syscall
		# Store the value in t0
		move $t0, $v0
	
	
		lw $t1, SID($zero)	# load the student id into register

		#judge
		lw $t2, stdbit($zero)
		
		bge $t0, $t2, displayError
		blt $t0, $t2, calculation
		
		
		
	# End of program
	li $v0, 10
	syscall

	calculation:
		
		# Display message
		li $v0, 4
		la $a0, message1
		syscall
		
		
		addi $t3, $zero, 0	# $t3 is index
		lw $t4, divide($zero)	# $t4 is the division number
		
		while:
			# the break condition
			
			beq $t3, 32, exit 
			
			# divide 2 number by 10 respectively
			div $t0, $t4
			mflo $s0
			mfhi $s1
			
			div $t1, $t4
			mflo $s2
			mfhi $s3
			
			#judge store 1 or store 0
			beq $s1,$s3,storeOne
			bne $s1,$s3,storeZero
		After:
			# change the number to the remaining part
			addi $t0,$s0,0
			addi $t1,$s2,0
			addi $t3,$t3,4
			
			j while

		exit:
		
			jal printAll
			li $v0, 10
			syscall
		
	storeZero:
		
		addi $s4,$zero,0
		sb  $s4,arr($t3)
		j After
	
	storeOne:
		
		addi $s4,$zero,1
		sb  $s4,arr($t3)
		j After
	
	printAll:
		addi $t3, $zero, 28	# $t3 is index
		loop2:
			blt $t3, 0, exit2 
			lb $t6, arr($t3)
			
			li $v0, 1
			move $a0,$t6
			syscall

			subi $t3,$t3,4
			j loop2

		exit2:
			li $v0, 10
			syscall
		
	
	displayError:
		# Display message
		li $v0, 4
		la $a0, message2
		syscall
