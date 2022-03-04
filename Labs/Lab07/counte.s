	.globl counte
	.text
	
counte:
	li 	a1, 0 # count of e's
	li	t2, 0 # default 0 value
	li	a2, 'e'
	
loop: 
	lb	t0, 0(a0)	# Loads the first byte of the word given (which is automatically loaded into a0) into t0
	beq 	t0, t2, done	# If you reached the end of the word, exit and return count
	addi	a0, a0, 1	# Increase the index in the word to the next character
	bne	t0, a2, loop	# Loop back to check the next character if the character is not 'e'
	addi	a1, a1, 1	# Increase count
	j loop
done: 
	add	a0, zero, a1
	jr 	ra
	
