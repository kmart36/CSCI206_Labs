
# CSCI 206 Computer Organization & Programming
# Date: 2019-10-26
# Copyright (c) 2019 Bucknell University
#
# Permission is hereby granted, free of charge, to any individual or
# institution obtaining a copy of this software and associated
# documentation files (the "Software"), to use, copy, modify, and
# distribute without restriction, provided that this copyright and
# permission notice is maintained, intact, in all copies and
# supporting
# documentation.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY
# KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
# WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
# NONINFRINGEMENT. IN NO EVENT SHALL BUCKNELL UNIVERSITY BE LIABLE FOR ANY
# CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
# TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH
# THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
#
#
# Student name:


	.data
	
unused:	.word 0xFEEDBEEF			
						
x:	.word 89				
						
	.text	
main:					# This tells the simulator
						# where start your program

	
	add		t0, zero, zero		# Setting t0 to be 0. Starting point for the counter. 
	add		s2, zero, zero		# Setting s2 to be 0. Starting point for the summation. 

loop:
	add		s2, s2, t0		# Adding t0 to s2. s2 becomes the summation of 10. 
	addi		t0, t0, 1		# Incrementing t0 by 1. t2 keeps track of how many times the loop occurs (11 times). 
	addi		t3, t0, -10		# t3 becomes t0 -10. This value will cause the loop to break when t0 becomes 11. 
	blez		t3, loop		# Will continue to loop until t3 is greater than zero. This stops the loop when s2 is the summation of 10. 

	la		t2, x			# Loads the address of label x into t2. This is so we can say the equivalent of x = (whatever is in s2)
	sw		s2, 0(t2)		# Stores the contents of s2, into the address contained in t2 with an offset of 0. This completes the x = summation of 10 logic. 
	
	add		a0, zero, s2		# Move result into a0 for return code
	li		a7, 93			# Code (93) for system call Exit2
	ecall					# Exit!
	ebreak					# Break if something went wrong (should not get here!)

