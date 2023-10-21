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
	jmp .loading

.floppy:
	mov si, menutext_floppy
	call puts
	mov ah, 0x00
	int 0x16
	jmp .loading

.loading:
	mov si, loading_text
	call puts
	
	;get memory map for kernel through E820
	xor ebx, ebx
	mov di, kernel_memmap
	mov edx, 0x0534D4150
	xor bp, bp

.memory_loop:
	mov eax, 0xe820
	mov ecx, 20
	
	int 0x15
	
	mov edx, 0x0534D4150
	
	pusha
	
	mov ah, 0x0e
	mov al, '.'
	int 0x10
	
	popa
	
	jc .end_of_list
	
	inc bp
	
	xor ch, ch
	add di, cx
	
	cmp ebx, 0
	je .end_of_list
	
	jmp .memory_loop

.end_of_list:
	
	mov [kernel_memmap_size], bp
	
	;switch into protected mode
	in al, 0x92
	test al, 2
	jnz .a20_enabled
	or al, 2
	and al, 0xFE
	out 0x92, al
	
.a20_enabled:
	mov ah, 0x0e
	mov al, '.'
	int 0x10
	
	;load gdt
	cli
	lgdt [flat_gdt.desc]
	
	sti
	mov ah, 0x0e
	mov al, '.'
	int 0x10
	
	cli
	
	mov eax, cr0
	or al, 1
	mov cr0, eax
	
	;far jump into the kernel
	jmp 08h:0x8400
	
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

flat_gdt:
	;entry 0
	dq 0
	
	;32-bit code
	dw 0xffff
	dw 0
	db 0
	db 0b10011010
	db 0b11001111
	db 0
	
	;32-bit data
	dw 0xffff
	dw 0
	db 0
	db 0b10010010
	db 0b11001111
	db 0
	
	;16-bit code
	dw 0xffff
	dw 0
	db 0
	db 0b10011010
	db 0b00001111
	db 0
	
	;16-bit data
	dw 0xffff
	dw 0
	db 0
	db 0b10010010
	db 0b00001111
	db 0

.desc:
	dw .desc - flat_gdt - 1
	dd flat_gdt

loading_text: db "Loading", 0
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