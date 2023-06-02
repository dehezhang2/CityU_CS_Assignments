# CS2115: Computer Organization

This course introduced basic knowledge of the computer organization. According to the course website, this course aims to introduce the logic design techniques and principles in the operation and construction of the functional parts of CPU and fundamental components. The course demonstrates computer architecture and programming model using CISC processor as example. It also introduces the techniques on low level assembly language programming.

This assignment uses MIPs to implement fundamental operations including addition, subtraction, and XNOR. 

## General Information

This part is about three programs are written by using the processor MIPS.  There are some similar operations among these three programs.

*  **Basic structure**

  ```assembly
  .data  #all the variables
  	SID: .word  55199998
  	stdbit: .word 100000000
  	prompt: .asciiz "Enter a number please: "
  	message1: .asciiz "\nThe result is: "
  	message2: .asciiz "\nSorry, please input a smaller number"
  	
  .text  #all the instructions
  ```

  where `.data` is followed by all data initially stored in the main memory. `.text` is followed by the instructions of the program.

*  **Output an ASCII string/integer**

  ```assembly
  li $v0, 4  		# load the instruction to print string
  la $a0, prompt		# load the prompt string
  syscall
  ```

* **Input(read) an integer (and store it in $t0)**

  ```assembly
  # load the instruction to input integer, store it in v0
  li $v0, 5		
  syscall	
  # Store the value in t0
  move $t0, $v0
  ```

* **Branch**

  ```assembly
  bge $t0, $t2, displayError
  blt $t0, $t2, calculation
  ```

* **Basic operations**

  * Prompt the user to enter a number by output a string to the screen
  * Get the input from users
  * Store the input value into the register `$t0`
  * Load the SID stored in the main memory
  * Do the judgment and the calculation
  * If there is no error, output the right message and answer, else output the error message

## Addition/Subtraction

While using MIPS, since reading an integer and doing n-digits addition and subtraction are allowed, the implementations of topic 3 and 4 are simple, I will just do a brief introduction of the addition/subtraction steps.

* Addition

```assembly
#addtion
add $t2,$t0,$t1
#judge
lw $t3, stdbit($zero)
blt $t2, $t3, displayAnswer
bge $t2, $t3, displayError
```

* Subtraction

```assembly
#subtraction
sub $t2,$t1,$t0
#judge
blt $t1,$t0,displayError
bge $t1,$t0,displayAnswer
```

`stdbit` stores the number 100000000 is used to judge whether the summation of the 2 numbers exceeds 8 bits in the addition (and XNOR) program. And the subtraction program has to check whether the input is larger than SID. 

## XNOR

To implement XNOR, the program needs to check the digits of SID and input one by one from lower digit to higher digit, and output them reversely. In order to achieve this target, we choose array(arr) to store the answer of every digit, and output together, and stores number 10 in the main memory to do the division. 

The XNOR calculation can be divided into 2 parts: (1) Calculate and store the answer in an array. (2) Output the answer.

### Calculate and store

A “While-loop” is used to check the digits one by one and increase the index of the array. 

* **Initialize the index of the array**

  ```assembly
  addi $t3, $zero, 0	# $t3 is index
  lw $t4, divide($zero)	# $t4 is the division number
  ```

* **The structure of “while-loop”**

  ```assembly
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
  ```

  * **Break Condition**:`$t3` is not only the index of the array but also the break condition of the while-loop, it is increased by 4 (32bits) each time. 
  * **How to implement the loop**: Each time after increasing the index, the program will jump to while again.
  * **How to check the digits**: For each iteration, the SID and input number are divided by 10. And replace the original numbers by the quotient
  * **How to store the data into the array**: If remainders are the same, store 1, else store 0. Data is stored by jumping to the function `storeZero` (or `storeOne`). After finishing the function, the program jumps back to `After `to do the index increment and change the original SID and input to their remainders

* **How to print the answer**: The answer is printed by another loop which traversing the array from the tail to the head. 

  ```assembly
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
  ```

  
