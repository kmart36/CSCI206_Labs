	.file	"c_mystery.c"
	.option nopic
	.globl	unused
	.section	.sdata,"aw",@progbits
	.align	2
	.type	unused, @object
	.size	unused, 4
unused:
	.word	-17973521
	.globl	x
	.align	2
	.type	x, @object
	.size	x, 4
x:
	.word	89
	.section	.rodata
	.align	3
.LC0:
	.string	"%i"
	.text
	.align	1
	.globl	main
	.type	main, @function
main:
	addi	sp,sp,-32
	sd	ra,24(sp)
	sd	s0,16(sp)
	addi	s0,sp,32
	sw	zero,-20(s0)
	sw	zero,-24(s0)
.L2:
	lw	a4,-24(s0)
	lw	a5,-20(s0)
	addw	a5,a4,a5
	sw	a5,-24(s0)
	lw	a5,-20(s0)
	addiw	a5,a5,1
	sw	a5,-20(s0)
	lw	a5,-20(s0)
	addiw	a5,a5,-10
	sw	a5,-28(s0)
	lw	a5,-28(s0)
	sext.w	a5,a5
	blez	a5,.L2
	lui	a5,%hi(x)
	lw	a4,-24(s0)
	sw	a4,%lo(x)(a5)
	lui	a5,%hi(x)
	lw	a5,%lo(x)(a5)
	mv	a1,a5
	lui	a5,%hi(.LC0)
	addi	a0,a5,%lo(.LC0)
	call	printf
	lui	a5,%hi(unused)
	lw	a5,%lo(unused)(a5)
	mv	a1,a5
	lui	a5,%hi(.LC0)
	addi	a0,a5,%lo(.LC0)
	call	printf
	lui	a5,%hi(x)
	lw	a5,%lo(x)(a5)
	mv	a0,a5
	ld	ra,24(sp)
	ld	s0,16(sp)
	addi	sp,sp,32
	jr	ra
	.size	main, .-main
	.ident	"GCC: (GNU) 7.2.0"
