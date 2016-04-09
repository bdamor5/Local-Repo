	.file	"lab2.1.c"
	.section	.rodata
	.align 8
.LC0:
	.string	"[BEFORE] buffer2 is at location %p and contains %s\n"
	.align 8
.LC1:
	.string	"[BEFORE] buffer1 is at location %p and contains %s\n"
	.align 8
.LC2:
	.string	"[BEFORE] value is at location %p and contains %d 0x%08x\n"
	.align 8
.LC3:
	.string	"[AFTER] buffer2 is at location %p and contains %s\n"
	.align 8
.LC4:
	.string	"[AFTER] buffer1 is at location %p and contains %s\n"
	.align 8
.LC5:
	.string	"[AFTER] value is at location %p and contains %d 0x%08x\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$72, %rsp
	.cfi_offset 3, -24
	movl	%edi, -68(%rbp)
	movq	%rsi, -80(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -24(%rbp)
	xorl	%eax, %eax
	movl	$5, -52(%rbp)
	leaq	-48(%rbp), %rax
	movl	$6647407, (%rax)
	leaq	-32(%rbp), %rax
	movl	$7305076, (%rax)
	leaq	-32(%rbp), %rdx
	leaq	-32(%rbp), %rax
	movq	%rax, %rsi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
	leaq	-48(%rbp), %rdx
	leaq	-48(%rbp), %rax
	movq	%rax, %rsi
	movl	$.LC1, %edi
	movl	$0, %eax
	call	printf
	movl	-52(%rbp), %ecx
	movl	-52(%rbp), %edx
	leaq	-52(%rbp), %rax
	movq	%rax, %rsi
	movl	$.LC2, %edi
	movl	$0, %eax
	call	printf
	movq	-80(%rbp), %rax
	addq	$8, %rax
	movq	(%rax), %rdx
	leaq	-48(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	strcpy
	leaq	-32(%rbp), %rdx
	leaq	-32(%rbp), %rax
	movq	%rax, %rsi
	movl	$.LC3, %edi
	movl	$0, %eax
	call	printf
	leaq	-48(%rbp), %rdx
	leaq	-48(%rbp), %rax
	movq	%rax, %rsi
	movl	$.LC4, %edi
	movl	$0, %eax
	call	printf
	movl	-52(%rbp), %ecx
	movl	-52(%rbp), %edx
	leaq	-52(%rbp), %rax
	movq	%rax, %rsi
	movl	$.LC5, %edi
	movl	$0, %eax
	call	printf
	movl	$0, %eax
	movq	-24(%rbp), %rbx
	xorq	%fs:40, %rbx
	je	.L3
	call	__stack_chk_fail
.L3:
	addq	$72, %rsp
	popq	%rbx
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 4.8.4-2ubuntu1~14.04) 4.8.4"
	.section	.note.GNU-stack,"",@progbits
