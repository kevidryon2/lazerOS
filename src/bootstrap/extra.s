db 0xb7, 0x4e


phase2_bootloader:
	;change video mode to 8-bit graphics
	mov ah, 0x00
	;mov al, 0x0e
	;mov al, 0x12
	;mov al, 0x10
	;mov al, 0x04
	mov al, 0x03
	int 0x10
	
	;decompress hello world string
	mov si, logo
	mov di, large_buffer0
	mov bl, ' '
	mov bh, '#'
	call ascii_decompress_alt
	
	mov si, large_buffer0
	mov bl, 12
	call puts
	
	mov si, hello_world
	mov bl, 12
	call puts
	
	jmp hang

;si: text to decompress
;di: decompression buffer
;bh: first character
;bl: second character
ascii_decompress_alt:
	push ax
	push cx
	push dx
	
	mov dx, 255
	
.loop:
	inc dx
	lodsb
	;0: special
	cmp al, 0
	je .cmd
	mov cl, al
	and dl, 1
	jz .repeat_b
	
.repeat_a:
	mov al, bh
	stosb
	loop .repeat_a
	jmp .loop
	
.repeat_b:
	mov al, bl
	stosb
	loop .repeat_b
	jmp .loop

.cmd:
	lodsb
	cmp al, 0xee
	je .end
	jmp .loop

.end:
	pop dx
	pop cx
	pop ax
	ret

;compressed logo
logo:
db 161

db 1
db 53
db 12
db 1
db 11
db 2

db 1
db 53
db 1
db 10
db 1
db 1
db 1
db 12

db 1
db 53
db 1
db 10
db 1
db 1
db 1
db 12

db 1
db 1
db 12
db 1
db 12
db 1
db 12
db 1
db 12
db 1
db 1
db 10
db 1
db 1
db 11
db 2

db 1
db 12
db 1
db 12
db 1
db 1
db 1
db 10
db 1
db 1
db 1
db 12
db 1
db 10
db 1
db 11
db 1
db 2

db 1
db 1
db 12
db 2
db 10
db 2
db 12
db 1
db 1
db 12
db 1
db 10
db 1
db 11
db 1

db 0, 0xee
