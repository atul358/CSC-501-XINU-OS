
.global zfunction

.text

zfunction:
	pushl  %ebp
	movl   %esp,%ebp
	
	andl   $0xfffc01ff, 8(%ebp)
	shrl   $8, 8(%ebp)
        orl    $0xff000000, 8(%ebp)
	movl   8(%ebp), %eax
	leave
	ret 
