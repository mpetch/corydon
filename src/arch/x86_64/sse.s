globaL sse_enable
sse_enable:
    ; compatibility check is redundent since
    ; every procesor since pentium III has
    ; sse support
    mov rax, cr0
	and ax, 0xFFFB		; clear coprocessor emulation CR0.EM
	or ax, 0x2			; set coprocessor monitoring CR0.MP
	mov cr0, rax
	mov rax, cr4
	or ax, 3 << 9		; set CR4.OSFXSR and CR4.OSXMMEXCPT at the same time
	mov cr4, rax
	ret
