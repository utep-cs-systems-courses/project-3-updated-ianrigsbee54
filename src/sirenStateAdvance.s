	.arch msp4302553
	.p2align 1, 0
	.text

	
jt:
	.word case0
	.word case1
	
	.extern sirenState
	
	.global sirenStateAdvance

sirenStateAdvance:
	cmp.b #2, &sirenState
	jc end
	mov.b &sirenState, R12
	mov.b &sirenState, R13
	add.b R12, R12
	mov.b jt(R12), R0

case0:
	call #siren
	call #sirenShapeAdvance
	add.b #1, &sirenState
	jmp end
case1:
	call #siren
	call #sirenShapeAdvance
	sub.b #1, &sirenState
	jmp end
end:
	pop R0
