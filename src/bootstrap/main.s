bits 16
org 0x7c00

start:
	;set up 'em segments
	mov bx, 0
	mov ds, bx
	mov es, bx
	mov sp, start
	mov ss, bx

	;save drive number (we'll need this later)
	mov [drive_num], dl

	;set video mode
	mov ah, 0x00
	mov al, 0x03
	int 0x10
	
	;query ram amount
	clc
	int 0x12
	jc hang
	
	mov di, buffer0+15
	
	;convert to decimal
	push ax
	mov al, 0xff
	mov di, buffer0
	mov cx, 16
	call memset
	pop ax
	mov di, buffer0+15
	call convert_to_decimal
	
	;print "<ram>kb low memory"
	mov bl, 0xd
	mov si, buffer0 ;contains RAM in KB
	call puts
	mov si, kb
	call puts
	
	mov bl, 0xf
	mov si, low_memory
	call puts
	
	;load extended boot sector (20 sectors, to 0x7e00)
	
	mov ah, 0x02
	mov al, 20
	mov ch, 0
	mov cl, 2
	mov dh, 0
	mov bx, 0x7e00
	mov dl, [drive_num]
	int 0x13
	jc .load_fail
	
	;print read thing
	;push ax
	;mov al, 0xff
	;mov di, buffer0
	;mov cx, 16
	;call memset
	;pop ax
	;mov ax, [0x7e00] ;verify magic bytes are present
	;mov di, buffer0+14
	;call convert_to_decimal
	;mov si, buffer0
	;call puts
	
	;test magic bytes
	mov ax, [0x7e00]
	cmp ax, 0x4eb7
	
	je .load_success
	
.load_fail:
	mov si, load_failed
	call puts
	jmp hang
	
.load_success:
	mov si, load_success
	call puts
	jmp phase2_bootloader

hang:
	hlt
	jmp hang

;buffer in DI
;length in CX
;value in AL
memset:
	rep stosb
	ret

;string in SI
puts:
	push ax
	mov ah, 0x0e
.loop:
	lodsb
	cmp al, 0
	je .end
	cmp al, 0xff
	je .loop
	int 0x10
	jmp .loop
.end:
	pop ax
	ret


;memory pointer to string end in DI; should be at least 4 bytes
;number in AX
;THIS FUNCTION DOES NOT SUPPORT NEGATIVE NUMBERS
convert_to_decimal:
	std
	push bx
	push cx
	push dx
	
	mov bx, 10

.loop:
	;divide AL by 10
	mov dx, 0
	div bx
	
	;DX = digit
	;AX = number
	
	xchg ax, dx
	add al, '0'
	stosb
	xchg ax, dx
	
	cmp ax, 0
	
	jne .loop
	
.end:
	pop dx
	pop cx
	pop bx
	cld
	ret

;STRINGS

hello_world: db "Hello, World!", 13, 10, 0
load_failed2: db "load fail (magic bytes invalid) :(", 13, 10, 0
load_success: db "load success", 13, 10, 0
load_failed: db "load fail :(", 13, 10, 0
kb: db "kb ", 0
low_memory: db "low memory.", 13, 10, 0

times 510-($-$$) db 0
db 0x55, 0xaa

;Extra space
%include "src/bootstrap/extra.s"

times 2048-($-$$) db 0

%include "src/bootstrap/ram.s"