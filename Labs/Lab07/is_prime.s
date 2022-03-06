	.globl is_prime
	.text

is_prime:
	li	t1, 2			# i
	li	t2, 1			# yes
		
loop: 	bgt	t1, a0, done_no		# If i is greater than n, the loop breaks to done_no and returns 1
	beq	t1, a0, done_no		# Breaks if equal
	rem	t4, a0, t1		# n % i = t4
	beq	t4, zero, done_yes	# If the remainder of i % n is 0, it will break and return 0
	addi	t1, t1, 1		# Increment i
	j 	loop
done_no: 
	addi	a0, t2, 0
	jr 	ra
done_yes:
	li	t2, 0
	addi	a0, t2, 0
	jr 	ra
