	.arch msp4302553
	.p2align 1,0
	.text

	.global asPeriod

asPeriod:
	sub #2, R1
	mov #1501, 0(R1)
	mov R12, R13
	cmp R12, 0(R1)
	jc else
	sub #200, R13
	jmp return
else:
	add #200, R13
	jmp return
return:
	add #2, R1
	mov R13, R12
	pop R0 			
