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
	
	;decompress hello world string
	mov si, helloworld_compressed
	mov di, large_buffer0
	call ascii_decompess
	
	mov si, large_buffer0
	mov bl, 15
	call puts
	
	;test the mode
	mov cx, 256
	
	mov ah, 0x0e
	mov al, '/'
	
.test_loop:
	inc bl
	int 0x10
	;jmp .test_loop
	
	jmp hang

helloworld_compressed: db 0x5f, 0x00, "Hello, World!", 0x00, 0xee, 0x00

;si: text to decompress
;di: decompression buffer
ascii_decompess:
	push ax
	
.loop:
	lodsw
	;al = char
	;ah = repeat length
	cmp ah, 0
	je .special
	mov cl, ah
	xor ch, ch

.repeat:
	stosb
	loop .repeat
	jmp .loop
	
.special:
	cmp al, 0x5f
	je .string
	cmp al, 0xee
	je .end
	jmp .loop

.string:
	lodsb
	cmp al, 0x00
	jz .loop
	stosb
	jmp .string

.end:
	mov al, 0
	stosb
	pop ax
	ret