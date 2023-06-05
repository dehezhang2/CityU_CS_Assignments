.data  #all the variables
	SID: .word  55199998
	stdbit: .word 100000000
	prompt: .asciiz "Enter a number please: "
	message1: .asciiz "\nThe result is: "
	message2: .asciiz "\nSorry, please input a smaller number"
	
.text  #all the instructions
	main:
		# Prompt the user to enter a number
		li $v0, 4  		# load the instruction to print string
		la $a0, prompt		# load the prompt string
		syscall
	
		# Get the user's input
		li $v0, 5		# load the instruction to input integer, store it in v0
		syscall
	
		# Store the value in t0
		move $t0, $v0
	
	
		lw $t1, SID($zero)	# load the student id into register

		#addtion
		add $t2,$t0,$t1
		#judge
		lw $t3, stdbit($zero)
		blt $t2, $t3, displayAnswer
		bge $t2, $t3, displayError
		
		
	# End of program
	li $v0, 10
	syscall

	displayAnswer:
		
		# Display message
		li $v0, 4
		la $a0, message1
		syscall
		
		li $v0, 1		# load instruction print integer
		move $a0,$t2
		syscall
		
		li $v0, 10
		syscall
		
	displayError:
		# Display message
		li $v0, 4
		la $a0, message2
		syscall
		
		
	
		
		
