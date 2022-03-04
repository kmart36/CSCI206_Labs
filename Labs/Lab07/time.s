	.globl   add_second
	.text
add_second:
	li 	a1, 59
	li 	a2, 23
	lw 	t2, 0(a0)
	lw 	t3, 4(a0)
	lw	t4, 8(a0)
	beq	t2, a1, add_minute
	addi	t2, t2, 1
	sw	t2, 0(a0)
	jr	ra

add_minute:
	li	t2, 0
	beq	t3, a1, add_hour
	addi	t3, t3, 1
	sw	t2, 0(a0)
	sw	t3, 4(a0)
	jr	ra

add_hour:
	li	t2, 0
	li	t3, 0
	beq	t4, a2, roll_over
	addi	t4, t4, 1
	sw	t2, 0(a0)
	sw	t3, 4(a0)
	sw 	t4, 8(a0)
	jr ra

roll_over:
	sw	zero, 0(a0)
	sw	zero, 4(a0)
	sw	zero, 8(a0)
	jr	ra

