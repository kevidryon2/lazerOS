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
	
	;decompress logo string
	mov si, logo
	mov di, large_buffer0
	mov bl, ' '
	mov bh, 0xdb
	call ascii_decompress_alt
	
	mov si, large_buffer0
	mov bl, 12
	call puts
	
	;decompress line string
	mov si, line
	mov di, large_buffer0
	call ascii_decompress
	
	mov si, large_buffer0
	mov bl, 12
	call puts
	
	mov al, [drive_num]
	
	shr al, 7
	
	jz .floppy

.hdd:
	jmp hang

.floppy:
	mov si, menutext_floppy
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
	mov al, 0
	stosb
	
	pop dx
	pop cx
	pop ax
	ret

menutext_floppy: db "Welcome to lazerOS!", 13, 10, 13, 10, " Press 'r' to run the OS, or press 'i' to install.", 13, 10, 13, 10, ' ', 0

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
db 2

db 1
db 1
db 1
db 10
db 1
db 1
db 1
db 12
db 1
db 12
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
db 1
db 12
db 1
db 12
db 1
db 1
db 12
db 12
db 1
db 11
db 82

db 0, 0xee

line:
db 0xc4, 78
db ' ', 82
db 0xee, 0

;si: text to decompress
;di: decompression buffer
ascii_decompress:
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