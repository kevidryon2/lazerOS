db 0xb7, 0x4e


phase2_bootloader:
	;change video mode to 8-bit graphics
	mov ah, 0x00
	;mov al, 0x0e
	;mov al, 0x12
	;mov al, 0x10
	;mov al, 0x04
	mov al, 0x10
	int 0x10
	
	;test the mode
	mov cx, 256
	
	mov ah, 0x0e
	mov al, '/'
	
.test_loop:
	inc bl
	int 0x10
	jmp .test_loop
	
	jmp hang

helloworld_compressed: db 0x5f, 0x00, "Hello, World!", 0x00, 0xee, 0x00

;si: text to decompress
;di: decompression buffer
ascii_decompess:
	push ax
	
.loop:
	lodsw
	;ah = char
	;al = repeat length
	cmp al, 0
	je .special
	mov cl, al
	xor ch, ch

.repeat:
	loop .repeat
	jmp .loop
	
.special:
	

.end:
	pop ax
	ret