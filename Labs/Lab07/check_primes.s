	.globl check_primes
	.text
check_primes:
	# a0 is left
	# a1 is right
	# a2 is result pointer
	
	addi	sp, sp, -4		# Allocating space on the stack
	
prime_loop:
	bge	a0, a1, end_loop	# Breaks if left >= right
	sw 	ra, 0(sp)		# Store return address on stack
	
	jal 	is_prime		# Call is_prime on a0
	
	sw	t2, 0(a2)		# Stores the result of is_prime into the return address
	addi	a2, a2, 4		# Increments the return array by the index
	addi	a0, a0, 1		# Increments left
	lw 	ra, 0(sp) 		# Restore ra
	j	prime_loop		
end_loop:
    	addi 	sp, sp, 4		# Deallocate space, pop the stack
    	jr 	ra	        	# Return	
    	
is_prime:
	li	t1, 2			# i
	li	t2, 1			# yes
		
loop: 	bge	t1, a0, done_yes	# If i is greater than or equal to n, the loop breaks to done_yes and returns 1
	rem	t4, a0, t1		# n % i = t4
	beqz	t4, done_no		# If the remainder of i % n is 0, it will break and return 0
	addi	t1, t1, 1		# Increment i
	j 	loop
done_yes: 
	#addi	a0, t2, 0
	jr 	ra
done_no:
	li	t2, 0
	#addi	a0, t2, 0
	jr 	ra
